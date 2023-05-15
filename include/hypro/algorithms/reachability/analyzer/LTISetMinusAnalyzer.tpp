/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "LTISetMinusAnalyzer.h"

#include <algorithm>
#include <vector>

namespace hypro {

    template<typename State, typename Automaton>
    auto LTISetMinusAnalyzer<State, Automaton>::run() -> LTISetMinusResult {
        // Setup settings for flowpipe construction in worker
        TimeTransformationCache<LocationT> transformationCache;
        LTISetMinusWorker<State, Automaton> worker{
                *mHybridAutomaton,
                mParameters,
                mFixedParameters.localTimeHorizon,
                transformationCache};

        while (!mWorkQueue.empty()) {
            auto *currentNode = mWorkQueue.back();
            mWorkQueue.pop_back();
            REACHABILITY_RESULT safetyResult;

            safetyResult = worker.computeTimeSuccessors(currentNode->getInitialSet(), currentNode->getLocation(),
                                                        std::back_inserter(currentNode->getFlowpipe()));
            if (safetyResult == REACHABILITY_RESULT::UNKNOWN) {
                return {Failure{currentNode}};
            }

            // Do not perform discrete jump if jump depth was reached
            if (currentNode->getDepth() == mFixedParameters.jumpDepth) continue;

            // create jump successor tasks
            for (const auto &[transition, timedValuationSets]: worker.computeJumpSuccessors(currentNode->getFlowpipe(),
                                                                                            currentNode->getLocation())) {
                for (const auto [valuationSet, segmentsInterval]: timedValuationSets) {
                    // update reachTree

                    // convert local time to global time
                    carl::Interval<SegmentInd> const &initialSetDuration = currentNode->getTimings();
                    // add one to upper to convert from segment indices to time points
                    // multiply by timeStepFactor to convert from analyzer specific timeStep to fixedTimeStep
                    carl::Interval<SegmentInd> enabledDuration{segmentsInterval.lower() * mParameters.timeStepFactor,
                                                               (segmentsInterval.upper() + 1) *
                                                               mParameters.timeStepFactor};
                    carl::Interval<TimePoint> globalDuration{initialSetDuration.lower() + enabledDuration.lower(),
                                                             initialSetDuration.upper() + enabledDuration.upper()};

                    // if desired, try to detect fixed-point
                    bool fixedPointReached = mParameters.detectJumpFixedPoints;
                    auto boundingBox = std::vector<carl::Interval<Number>>{};
                    if (mParameters.detectJumpFixedPoints) {
                        boundingBox = Converter<Number>::toBox(valuationSet).intervals();
                        fixedPointReached = detectFixedPoint(valuationSet, transition->getTarget());
                    }
                    // in any case add node to the search tree
                    auto &childNode = currentNode->addChild(valuationSet, globalDuration, transition);
                    // set bounding box to speed up search in case the option is enabled
                    if (mParameters.detectJumpFixedPoints) {
                        childNode.setBoundingBox(boundingBox);
                    }
                    // create Task, push only to queue, in case no fixed-point has been detected or detection is disabled
                    if (!fixedPointReached) {
                        mWorkQueue.push_front(&childNode);
                    }
                }
            }
        }

        return {LTISetMinusSuccess{}};
    }

    template<typename State, typename Automaton>
    bool LTISetMinusAnalyzer<State, Automaton>::detectFixedPoint(const State &valuationSet,
                                                                 const typename Automaton::LocationType *loc) {
        using Number = typename State::NumberType;
#ifdef HYPRO_STATISTICS
        START_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
        std::vector<carl::Interval<Number>> boundingBox = Converter<Number>::toBox(valuationSet).intervals();
        for (auto &root: mRoots) {
            for (auto &node: preorder(root)) {
                const auto &nodeInitialBoundingBox = node.getInitialBoundingBox();
                // if the location matches and the bounding boxes contain each other, then also perform the (possibly expensive) full containment test.
                if (nodeInitialBoundingBox && node.getLocation() == loc &&
                    std::equal(std::begin(boundingBox), std::end(boundingBox),
                               std::begin(nodeInitialBoundingBox.value()), std::end(nodeInitialBoundingBox.value()),
                               [](const auto &setBoxIntv, const auto &initBoxIntv) {
                                   return initBoxIntv.contains(setBoxIntv);
                               }) && node.getInitialSet().contains(valuationSet)) {
                    TRACE("hypro.reachability", "Fixed-point detected.");
#ifdef HYPRO_STATISTICS
                    STOP_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
                    return true;
                }
            }
        }
#ifdef HYPRO_STATISTICS
        STOP_BENCHMARK_OPERATION( "Fixed-point detection" );
#endif
        return false;
    }

}  // namespace hypro
