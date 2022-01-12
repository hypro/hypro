/*
 * Copyright (c) 2022.
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
#include "../fixedPointDetection.h"
#include "../workers/LTIWorker.h"
#include "./ReturnTypes.h"

#include <atomic>
#include <mutex>
#include <queue>

namespace hypro {

// indicates that the lti analysis succeeded, i.e. no
struct LTISuccess {};

template <typename State>
class LTIAnalyzer {
	using Number = typename State::NumberType;

  public:
	using LTIResult = AnalysisResult<LTISuccess, Failure<State>>;

	LTIAnalyzer( HybridAutomaton<Number> const& ha,
				 FixedAnalysisParameters const& fixedParameters,
				 AnalysisParameters const& parameters,
				 std::vector<ReachTreeNode<State>>& roots )
            : mHybridAutomaton(&ha), mFixedParameters(fixedParameters), mParameters(parameters), mRoots(roots) {
        for (auto &root: roots) {
            mWorkQueue.push_front(&root);
        }
    }

    LTIResult run();

    void addToQueue(ReachTreeNode<State> *node) {
        DEBUG("hypro.reachability", "Add node @" << node << " to the work-queue")
        mWorkQueue.push_front(node);
    }

private:
    bool detectFixedPoint(ReachTreeNode<State> &node);

protected:
    std::deque<ReachTreeNode<State> *> mWorkQueue;      ///< queue which holds tasks for time successor computation
    HybridAutomaton<Number> const *mHybridAutomaton;  ///< pointer to the hybrid automaton
    FixedAnalysisParameters mFixedParameters;          ///< parameters which are fixed for the analysis
    AnalysisParameters mParameters;                      ///< parameters which are specific for this call (relevant for CEGAR-refinement)
    std::vector<ReachTreeNode<State>> &mRoots;          ///< reference to the search tree, required for fixed-point detection
};

}  // namespace hypro

#include "LTIAnalyzer.tpp"
