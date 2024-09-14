/*
 * Copyright (c) 2023-2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "rectangularSyncGuardHandler.h"

namespace hypro {

    template<typename Representation, typename Location>
    void
    rectangularSyncGuardHandler<Representation, Location>::operator()(const Representation &state, const Location *loc, const std::set<Label> &nonSyncLabels) {
        
        for (auto &transitionPtr: loc->getTransitions()) {
            // intersect
            auto [containmentResult, resultingSet] = intersect(state, transitionPtr->getGuard());

            // reduction
            resultingSet.removeRedundancy();

            if (containmentResult != CONTAINMENT::NO) { 
                //if all transition labels are included in nonSyncLabels add resultingSet to mNonSyncGuardSatisfyingStates
                // h.s. TODO: check how to handle multiple labels for one transition
                if (std::includes(nonSyncLabels.begin(), nonSyncLabels.end(), transitionPtr->getLabels().begin(), transitionPtr->getLabels().end()) || transitionPtr->getLabels().empty()){
                    mNonSyncGuardSatisfyingStates[transitionPtr.get()].emplace_back(std::move(resultingSet));
                } else {
                    mSyncGuardSatisfyingStates[transitionPtr.get()].emplace_back(std::move(resultingSet));
                }
                mGuardSatisfyingStates[transitionPtr.get()].emplace_back(std::move(resultingSet));
            }
            mGuardContainment[transitionPtr.get()] = containmentResult;
        }
    }

    template<typename Representation, typename Location>
    typename rectangularSyncGuardHandler<Representation, Location>::TransitionStatesMap
    rectangularSyncGuardHandler<Representation, Location>::intersectWithGuard(std::vector<Representation>& flowpipe, Transition<Location>* transitionPtr) {
        TransitionStatesMap result;

        for (auto &state: flowpipe) {   
            // intersect
            auto [containmentResult, resultingSet] = intersect(state, transitionPtr->getGuard());

            // reduction
            resultingSet.removeRedundancy();

            if (containmentResult != CONTAINMENT::NO) {
                result[transitionPtr].emplace_back(std::move(resultingSet));
            }
        }
        return result;
    }

}  // namespace hypro
