/*
 * Copyright (c) 2023-2023.
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

#include <hypro/algorithms/reachability/analyzer/RectangularAnalyzer.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <iostream>

int main() {
    // typedefs
    using Number = double;
    using Representation = hypro::HPolytope<Number>;
    using State = hypro::State<Number, Representation>;
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    // variables
    carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex(0);
    carl::Variable y = hypro::VariablePool::getInstance().carlVarByIndex(1);
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> dynamics;
    dynamics.emplace(std::make_pair(x, carl::Interval<Number>(1, 2)));
    dynamics.emplace(std::make_pair(y, carl::Interval<Number>(2, 3)));
    std::map<carl::Variable, carl::Interval<Number>> dynamics2;
    dynamics2.emplace(std::make_pair(x, carl::Interval<Number>(3, 5)));
    dynamics2.emplace(std::make_pair(y, carl::Interval<Number>(2, 4)));

    // hybrid automaton instance
    hypro::HybridAutomaton<Number> ha;

    // create locations with rectangular flow
    hypro::Location<Number> *loc1 = ha.createLocation();
    hypro::rectangularFlow<Number> flow(dynamics);
    loc1->setRectangularFlow(flow);
    hypro::Location<Number> *loc2 = ha.createLocation();
    hypro::rectangularFlow<Number> flow2(dynamics2);
    loc2->setRectangularFlow(flow2);

    // create transitions
    hypro::Transition<hypro::Location<Number>> *trans = loc1->createTransition(loc2);
    // guard
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(4, 2);
    guardConstraints << 1, 0, -1, 0, 0, 0, 0, 0;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(4);
    guardConstants << 3, -1, 0, 0;
    hypro::Condition<Number> guard(guardConstraints, guardConstants);

    // reset function

    // interval representation
    // std::vector<carl::Interval<Number>> intervalReset;
    // intervalReset.emplace_back( carl::Interval<Number>( -2, 2 ) );
    // intervalReset.emplace_back( carl::Interval<Number>( -3, 3 ) );
    // hypro::Reset<Number> reset;
    // reset.setIntervals( intervalReset );

    // matrix representation
    hypro::matrix_t<Number> resetConstraints = hypro::matrix_t<Number>(4, 2);
    resetConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
    hypro::vector_t<Number> resetConstants = hypro::vector_t<Number>(4);
    resetConstants << 2, 2, 3, 3;
    hypro::Reset<Number> reset(resetConstraints, resetConstants);

    // setup transition
    trans->setGuard(guard);
    trans->setReset(reset);

    // initial set is a unit box
    hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>(4, 2);
    constraints << 1, 0, -1, 0, 0, 1, 0, -1;
    hypro::vector_t<Number> constants = hypro::vector_t<Number>(4);
    constants << 1, 1, 1, 1;

    // create and add initial state
    ha.addInitialState(loc1, hypro::Condition<Number>(constraints, constants));

    // setup local bad state
    hypro::matrix_t<Number> localBadConstraints = hypro::matrix_t<Number>(4, 2);
    localBadConstraints << 1, 0, 0, 0, 0, 0, 0, 0;
    hypro::vector_t<Number> localBadConstants = hypro::vector_t<Number>(4);
    localBadConstants << -10, 0, 0, 0;
    ha.addLocalBadStates(loc2, hypro::Condition<Number>(localBadConstraints, localBadConstants));

    // setup global bad state
    hypro::matrix_t<Number> globalBadConstraints = hypro::matrix_t<Number>(4, 2);
    globalBadConstraints << 0, 0, -1, 0, 0, 0, 0, 0;
    hypro::vector_t<Number> globalBadConstants = hypro::vector_t<Number>(4);
    globalBadConstants << 0, -10, 0, 0;
    // ha.addGlobalBadStates( hypro::Condition<Number>( globalBadConstraints, globalBadConstants ) );

    // std::cout << "HA is: " << ha << std::endl;

    // create settings
    std::vector<hypro::AnalysisParameters> strategy;
    strategy.emplace_back(hypro::AnalysisParameters{mpq_class(1) / mpq_class(100), hypro::AGG_SETTING::AGG, -1,
                                                    hypro::representation_name::carl_polytope, 0, false,
                                                    hypro::REACH_SETTING::FORWARD});
    
    hypro::Settings settings;
    settings.setStrategy(strategy);

    // call to analysis core
    auto roots = hypro::makeRoots<Representation>(ha);
    hypro::RectangularAnalyzer<Representation, hypro::HybridAutomaton<Number>> analyzer{ha, settings, roots};
    auto result = analyzer.run();

    if (result == hypro::REACHABILITY_RESULT::UNKNOWN) {
        std::cout << "Could not verify safety." << std::endl;
    } else {
        std::cout << "The model is safe." << std::endl;
    }

    // output computed sets
    for (const auto &fp: hypro::getFlowpipes(roots)) {
        for (const auto &segment: fp) {
            std::cout << segment << std::endl;
        }
    }

    return 0;
}
