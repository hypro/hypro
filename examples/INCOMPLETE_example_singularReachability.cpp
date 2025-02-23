/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @brief Example file which shows how to instanciate a concrete worker out of
 * context handlers.
 */

#include <hypro/algorithms/reachability/workers/ContextBasedReachabilityWorker.h>
#include <hypro/datastructures/reachability/ReachTreev2.h>
#include <hypro/datastructures/reachability/SettingsProvider.h>
#include <hypro/datastructures/reachability/Task.h>
#include <hypro/datastructures/reachability/timing/EventTimingProvider.h>
#include <hypro/datastructures/reachability/workQueue/WorkQueueManager.h>
#include <hypro/representations/GeometricObjectBase.h>

#include <iostream>

int main() {
    // typedefs
    using Number = mpq_class;
    using State = hypro::State_t<Number>;
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    // settings provider instance as reference for readability
    hypro::SettingsProvider <State> &settingsProvider =
            hypro::SettingsProvider<State>::getInstance();

    // hybrid automaton instance
    hypro::HybridAutomaton <Number> ha;

    // create 1st location
    hypro::Location <Number> loc1;
    Matrix l1dynamics = Matrix::Zero(4, 4);
    Vector l1affine = Vector::Zero(4);
    hypro::linearFlow <Number> flow(l1dynamics, l1affine);
    loc1.setFlow(flow);

    // add location
    ha.addLocation(loc1);

    // initial set is a unit box
    hypro::matrix_t <Number> constraints = hypro::matrix_t<Number>(4, 2);
    constraints << 1, 0, -1, 0, 0, 1, 0, -1;
    hypro::vector_t <Number> constants = hypro::vector_t<Number>(4);
    constants << 1, 1, 1, 1;

    // create and add initial state
    ha.addInitialState(&loc1, hypro::Condition<Number>(constraints, constants));

    // theoretically we do not need this - check if really needed.
    settingsProvider.addStrategyElement < hypro::CarlPolytope < Number >> (
            mpq_class(1) / mpq_class(100), hypro::AGG_SETTING::AGG, -1);

    // set settings
    settingsProvider.setHybridAutomaton(std::move(ha));
    hypro::ReachabilitySettings settings;
    settings.useInvariantTimingInformation = false;
    settings.useGuardTimingInformation = false;
    settings.useBadStateTimingInformation = false;
    settingsProvider.setReachabilitySettings(settings);

    // set up queues
    hypro::WorkQueueManager < std::shared_ptr < hypro::Task < State>>> queueManager;
    auto globalCEXQueue = queueManager.addQueue();
    auto globalQueue = queueManager.addQueue();

    // set up initial states to the correct representation - in this case
    // CarlPolytope
    auto initialStates = settingsProvider.getHybridAutomaton().getInitialStates();
    std::vector <hypro::State_t<Number>> initialStateData;
    for (auto stateMapIt = initialStates.begin();
         stateMapIt != initialStates.end(); ++stateMapIt) {
        hypro::State_t <Number> copyState;
        copyState.setLocation(stateMapIt->first);
        copyState.setTimestamp(carl::Interval<hypro::tNumber>(0));

        // if the decider is in use - convert subspaces according to mapping
        State::repVariant _temp;
        _temp = hypro::CarlPolytope<Number>(stateMapIt->second.getMatrix(),
                                            stateMapIt->second.getVector());

        copyState.setSet(_temp, 0);
        initialStateData.emplace_back(copyState);
    }

    // set up tree
    hypro::ReachTree <State> tree =
            hypro::ReachTree<State>(new hypro::ReachTreeNode<State>());
    std::vector < hypro::ReachTreeNode < State > * > initialNodes;
    for (const auto &state: initialStateData) {
        hypro::ReachTreeNode <State> *n =
                new hypro::ReachTreeNode<State>(state, 0, tree.getRoot());
        n->setTimestamp(0, carl::Interval<hypro::tNumber>(0));
        initialNodes.push_back(n);
        tree.getRoot()->addChild(n);
    }

    // fill task queue with initial states
    for (const auto &initialNode: initialNodes) {
        globalQueue->enqueue(std::shared_ptr < hypro::Task < State >> (
                new hypro::Task<State>(initialNode)));
    }

    // create worker
    hypro::ContextBasedReachabilityWorker <State> worker =
            hypro::ContextBasedReachabilityWorker<State>(settings);

    // data structure to store computed flowpipes
    hypro::Flowpipe <State> segments;

    while (queueManager.hasWorkable(true)) {  // locking access to queues.
        auto task = queueManager.getNextWorkable(
                true, true);     // get next task locked and dequeue from front.
        assert(task != nullptr);
        worker.processTask(task, settingsProvider.getStrategy(), globalQueue,
                           globalCEXQueue, segments);
    }

    for (const auto &segment: segments) {
        std::cout << segment << std::endl;
    }

    return 0;
}
