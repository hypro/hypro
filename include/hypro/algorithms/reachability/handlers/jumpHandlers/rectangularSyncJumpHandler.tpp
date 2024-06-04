/*
 * Copyright (c) 2023-2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "rectangularJumpHandler.h"

namespace hypro {

    template<typename Representation, typename Location>
    auto rectangularSyncJumpHandler<Representation, Location>::applyJump(const TransitionStateMap &states,
                                                                  Representation time, std::size_t subspace) -> TransitionStateMap {
        // holds a mapping of transitions to already processed (i.e. aggregated, resetted and reduced) states
        TransitionStateMap processedStates;

        DEBUG("hydra.worker", "Apply jump on " << states.size() << " transitions.");

        for (const auto &[transitionPtr, statesVec]: states) {
            DEBUG("hydra.worker", "Apply jump on " << statesVec.size() << " states.");
            for (const auto &state: statesVec) {
                // copy state - as there is no aggregation, the containing set and timestamp is already valid
                Representation newState(state);
                // create normal n-dimensional vector (0,0,...,-1)
                vector_t<Number> firstNormalVec = vector_t<Number>::Zero(newState.dimension());
                firstNormalVec(newState.dimension()-1) = -1;
                auto lowerBound = time.vertices().front();
                for (const auto &vertex : time.vertices()) {
                    if (vertex < lowerBound) {
                        lowerBound = vertex;
                    }
                }
                // create normal n-dimensional vector (0,0,...,1)
                vector_t<Number> secondNormalVec = vector_t<Number>::Zero(newState.dimension());
                secondNormalVec(newState.dimension()-1) = 1;
                // create halfspace with normal vector and time upper bound
                auto upperBound = time.vertices().front();
                for (const auto &vertex : time.vertices()) {
                    if (vertex > upperBound) {
                        upperBound = vertex;
                    }
                }

                // intersect newState with both halfspaces ( -1*t <= -1*lowerBound and 1*t <= upperBound)
                newState = newState.intersectHalfspace(Halfspace<Number>(firstNormalVec, -1*lowerBound.coordinate(0)));
                newState = newState.intersectHalfspace(Halfspace<Number>(secondNormalVec, upperBound.coordinate(0)));
                
                // if the state satisfying the guard, intersected with the common time interval is empty, continue with next state
                if (newState.empty()) {
                    continue;
                }

                // apply reset function
                applyReset(newState, transitionPtr, subspace);

                // check invariant in new location
                auto [containment, stateSet] = intersect(newState, transitionPtr->getTarget()->getInvariant(),
                                                         subspace);
                if (containment == CONTAINMENT::NO) {
                    continue;
                }

                // Note: Here we misuse the state's timestamp to carry the transition timing to the next stage -> just don't reset
                // the timestamp in case no aggregation happens.

                if (processedStates.find(transitionPtr) == processedStates.end()) {
                    processedStates[transitionPtr] = std::vector<Representation>();
                }
                processedStates[transitionPtr].emplace_back(stateSet);
            }
        }
        return processedStates;
    }

    template<typename Representation, typename Location>
    void rectangularSyncJumpHandler<Representation, Location>::applyReset(Representation &stateSet,
                                                                   Transition<Location> *transitionPtr,
                                                                   std::size_t subspace) const {
        if (!transitionPtr->getReset().empty()) {
            const auto &reset = transitionPtr->getReset();
            assert(reset.getAffineReset(subspace).isSingular() &&
                   "Singular automata do not support linear/affine resets.");

            auto intervalReset = transitionPtr->getReset().getIntervalReset(subspace);
            // if affine reset is singular and not identity, get constant resets
            if (!reset.getAffineReset(subspace).isIdentity()) {
                WARN("hypro.reachability",
                     "Singular reset handler with affine constant assignments. Converting to interval reset.")
                matrix_t<Number> zeroRow = matrix_t<Number>::Zero(1, reset.getMatrix(subspace).cols());
                for (Eigen::Index rowIndex = 0; rowIndex < reset.getMatrix(subspace).rows(); ++rowIndex) {
                    if (reset.getMatrix(subspace).row(rowIndex) == zeroRow) {
                        // add interval for constant reset
                        Number constant = reset.getVector(subspace)(rowIndex);
                        assert(isEmpty(intervalReset.getIntervals()[rowIndex]) &&
                               "Reset has both affine and interval assignment");
                        intervalReset.setInterval(carl::Interval<Number>(constant, constant), rowIndex);
                    }
                }
            }

            if (!intervalReset.isIdentity()) {
                auto transformedSet1 = applyResetFM(stateSet, intervalReset);

                convert(transformedSet1, stateSet);
                TRACE("hypro.reachability", "Resulting state set " << stateSet);
            }
        }
    }

} // namespace hypro