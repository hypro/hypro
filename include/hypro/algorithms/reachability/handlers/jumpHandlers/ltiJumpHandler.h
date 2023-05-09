/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../../../../datastructures/reachability/ReachTreev2.h"
#include "../../../../datastructures/reachability/Task.h"
#include "../../../../datastructures/reachability/workQueue/WorkQueue.h"
#include <hypro/flags.h>
//#include "../HandlerFactory.h"
//#include "../IHandler.h"
#include "timingUtil.h"
#include "util.h"

namespace hypro {

    template<typename State>
    class ltiJumpHandler {
        using Number = typename State::NumberType;
        using TransitionStateMap = typename std::map<Transition<Number> *, std::vector<State>>;

    public:
        TransitionStateMap
        applyJump(const TransitionStateMap &states, Transition<Number> *transition, const AnalysisParameters &strategy);

        void aggregate(TransitionStateMap &processedStates, const TransitionStateMap &toAggregate,
                       const AnalysisParameters &strategy) const;

        void applyReset(State &state, Transition<Number> *transitionPtr) const;

        // typename ReachTreeNode<State>::NodeList_t createNodesFromStates( Transition<Number>* transition, const std::vector<State>& states, std::size_t targetLevel, carl::Interval<tNumber>& coveredTimeInterval, typename ReachTreeNode<State>::Node_t parent );
    };

}  // namespace hypro

#include "ltiJumpHandler.tpp"
