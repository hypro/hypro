/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "rectangularJumpHandler.h"

namespace hypro {

    template<typename State, typename TransitionT>
    auto
    rectangularJumpHandler<State, TransitionT>::applyJump(const TransitionStateMap &states, TransitionT *transition,
                                                          const AnalysisParameters &strategy,
                                                          bool reverse) -> TransitionStateMap {
        // holds a mapping of transitions to states which need to be aggregated
        TransitionStateMap toAggregate;
        // holds a mapping of transitions to states which are ready to apply the reset function and the intersection with the invariant
        TransitionStateMap toProcess = filter(states, transition);
        // holds a mapping of transitions to already processed (i.e. aggregated, resetted and reduced) states
        TransitionStateMap processedStates;

        DEBUG("hydra.worker", "Apply jump on " << toProcess.size() << " transitions.");

        for (const auto &[transitionPtr, statesVec]: toProcess) {
            DEBUG("hydra.worker", "Apply jump on " << statesVec.size() << " states.");
            for (const auto &state: statesVec) {
                // copy state - as there is no aggregation, the containing set and timestamp is already valid
                // TODO: Why copy?
                assert(!state.getTimestamp().isEmpty());
                State newState(state);

                if (reverse) {
                    // apply guard function
                    applyGuard(newState, transitionPtr);
                    // set source location in state set
                    newState.setLocation(transitionPtr->getSource());
                } else {
                    // apply reset function
                    applyReset(newState, transitionPtr);
                    // set target location in state set
                    newState.setLocation(transitionPtr->getTarget());
                }

                // check invariant in new location
                auto [containment, stateSet] = rectangularIntersectInvariant(newState);
                if (containment == CONTAINMENT::NO) {
                    continue;
                }

                // reduce if possible (Currently only for support functions)
                stateSet.reduceRepresentation();

                DEBUG("hydra.worker.discrete", "State after reduction: " << stateSet);

                if (processedStates.find(transitionPtr) == processedStates.end()) {
                    processedStates[transitionPtr] = std::vector<State>();
                }
                processedStates[transitionPtr].emplace_back(stateSet);
            }
        }
        return processedStates;
    }

    template<typename State, typename TransitionT>
    void rectangularJumpHandler<State, TransitionT>::applyReset(State &state, TransitionT *transitionPtr) const {
        if (!transitionPtr->getReset().empty()) {
            if (transitionPtr->getReset().getMatrix().size() > 0) {
                state = State{CarlPolytope<typename State::NumberType>{transitionPtr->getReset().getMatrix(),
                                                                       transitionPtr->getReset().getVector()}};
            } else {
                for (size_t i = 0; i < state.getNumberSets(); i++) {
                    IntervalAssignment<Number> intervalReset = transitionPtr->getReset().getIntervalReset(i);
                    state = state.partialIntervalAssignment(intervalReset.mIntervals, i);
                }
            }
        }
    }

    template<typename State, typename TransitionT>
    auto rectangularJumpHandler<State, TransitionT>::applyReverseJump(const TransitionStateMap &states,
                                                                      TransitionT *transition,
                                                                      const AnalysisParameters &strategy) -> TransitionStateMap {
        return applyJump(states, transition, strategy, true);
    }

    template<typename State, typename TransitionT>
    void rectangularJumpHandler<State, TransitionT>::applyGuard(State &state, TransitionT *transitionPtr) const {
        if (!transitionPtr->getGuard().empty()) {
            state.setSet(typename State::template nth_representation<0>{transitionPtr->getGuard().getMatrix(),
                                                                        transitionPtr->getGuard().getVector()});
        }
    }

    template<typename State, typename TransitionT>
    auto rectangularJumpHandler<State, TransitionT>::filter(const TransitionStateMap &states,
                                                            TransitionT *transition) const -> TransitionStateMap {
        TransitionStateMap res;
        for (const auto &[transitionPtr, statesVec]: states) {
            // only handle sets related to the passed transition, in case any is passed.
            if (transition == nullptr || transitionPtr == transition) {
                // check aggregation settings

                auto &targetVec = res[transitionPtr];
                targetVec.insert(targetVec.end(), statesVec.begin(), statesVec.end());
            }
        }
        return res;
    }
}  // namespace hypro
