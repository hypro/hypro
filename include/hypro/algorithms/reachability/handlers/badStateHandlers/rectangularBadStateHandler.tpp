/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "rectangularBadStateHandler.h"

namespace hypro {
    template<typename State, typename Location>
    std::pair<CONTAINMENT, State> rectangularIntersectBadStates(const State &stateSet, const Location *loc,
                                                                const HybridAutomaton<typename State::NumberType> &automaton) {
        TRACE("hydra.worker.continuous",
              "Having a total of " << automaton.getLocalBadStates().size() << " local bad states.");
        auto localBadState = automaton.getLocalBadStates().find(loc);
        if (localBadState != automaton.getLocalBadStates().end()) {
            TRACE("hydra.worker.continuous", "Checking local bad state: " << localBadState->second);

            // create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
            // create carlPolytope, as intersection is defined for those
            State badStateConstraints{localBadState->second.getMatrix(), localBadState->second.getVector()};

            // intersect
            auto resultingSet = stateSet.intersect(badStateConstraints);

            // reduction
            resultingSet.removeRedundancy();

            // process containment information
            if (!resultingSet.empty()) {
                DEBUG("hydra.worker", "Intersection with local bad states.");
                return std::make_pair(CONTAINMENT::YES, resultingSet);
            }
        }

        TRACE("hydra.worker.continuous", "No intersection with local, continuous bad states");

        // check global bad states
        for (const auto &badState: automaton.getGlobalBadStates()) {
            if (badState.getMatrix().rows() != 0) {
                // at least one global bad state in this subspace
                // create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
                // create carlPolytope, as intersection is defined for those
                State badStateConstraints{badState.getMatrix(), badState.getVector()};

                // intersect
                auto resultingSet = stateSet.intersect(badStateConstraints);

                // reduction
                resultingSet.removeRedundancy();

                // set containment information
                if (!resultingSet.empty()) {
                    return std::make_pair(CONTAINMENT::YES, resultingSet);
                }
            }
        }
        return std::make_pair(CONTAINMENT::NO, stateSet);
    }

    template<typename State, typename Location>
    std::pair<CONTAINMENT, State> rectangularBadIntersectInitialStates(const State &stateSet, const Location *loc,
                                                                       const HybridAutomaton<typename State::NumberType> &automaton) {
        TRACE("hydra.worker.continuous",
              "Having a total of " << automaton.getInitialStates().size() << " initial states.");
        auto initialState = automaton.getInitialStates().find(loc);
        if (initialState != automaton.getInitialStates().end()) {
            TRACE("hydra.worker.continuous", "Checking initial state: " << initialState->second);

            // intersect with initial state set
            auto resultingSet = stateSet.intersect(
                    State{initialState->second.getMatrix(), initialState->second.getVector()});

            // reduction
            resultingSet.removeRedundancy();

            // process containment information
            if (!resultingSet.empty()) {
                DEBUG("hydra.worker", "Intersection with initial states.");
                return std::make_pair(CONTAINMENT::YES, resultingSet);
            }
        }

        TRACE("hydra.worker.continuous", "No intersection with local, continuous bad states");

        return std::make_pair(CONTAINMENT::NO, stateSet);
    }

}  // namespace hypro
