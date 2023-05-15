/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../datastructures/reachability/TreeTraversal.h"
#include "../../../types.h"
#include "../workers/LTISetMinusWorker.h"
#include "./ReturnTypes.h"

#include <atomic>
#include <mutex>
#include <queue>

namespace hypro {

// indicates that the lti analysis succeeded, i.e. no
    struct LTISetMinusSuccess {
    };

    template<typename State, typename Automaton>
    class LTISetMinusAnalyzer {
        using Number = typename State::NumberType;
        using LocationT = typename Automaton::LocationType;

    public:
        using LTISetMinusResult = AnalysisResult<LTISetMinusSuccess, Failure<State, LocationT>>;

        LTISetMinusAnalyzer(Automaton const &ha,
                            FixedAnalysisParameters const &fixedParameters,
                            AnalysisParameters const &parameters,
                            std::vector<ReachTreeNode<State, LocationT>> &roots)
                : mHybridAutomaton(&ha), mFixedParameters(fixedParameters), mParameters(parameters), mRoots(roots) {
            for (auto &root: roots) {
                mWorkQueue.push_front(&root);
            }
        }

        LTISetMinusResult run();

        void addToQueue(ReachTreeNode<State, LocationT> *node) { mWorkQueue.push_front(node); }

    private:
        bool detectFixedPoint(const State &valuationSet, const typename Automaton::LocationType *loc);

    protected:
        std::deque<ReachTreeNode<State, LocationT> *> mWorkQueue;  ///< queue which holds tasks for time successor computation
        Automaton const *mHybridAutomaton;                          ///< pointer to the hybrid automaton
        FixedAnalysisParameters mFixedParameters;                  ///< parameters which are fixed for the analysis
        AnalysisParameters mParameters;                              ///< parameters which are specific for this call (relevant for CEGAR-refinement)
        std::vector<ReachTreeNode<State, LocationT>> &mRoots;      ///< reference to the search tree, required for fixed-point detection
    };

}  // namespace hypro

#include "LTISetMinusAnalyzer.tpp"
