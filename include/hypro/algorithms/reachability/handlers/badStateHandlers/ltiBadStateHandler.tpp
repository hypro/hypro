/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ltiBadStateHandler.h"

namespace hypro {

    template<typename Representation, typename Automaton>
    std::pair<CONTAINMENT, Representation>
    ltiIntersectBadStates(const Representation &valuationSet, typename Automaton::LocationType const *location,
                          const Automaton &automaton, std::size_t I) {
        auto localBadState = automaton.getLocalBadStates().find(location);
        if (localBadState != automaton.getLocalBadStates().end()) {
            if (localBadState->second.isTrue()) {
                return std::make_pair(CONTAINMENT::FULL, valuationSet);
            } else if (localBadState->second.isFalse()) {
                return std::make_pair(CONTAINMENT::NO, valuationSet);
            }
            std::pair<CONTAINMENT, Representation> badStatePair = intersect(valuationSet, localBadState->second, I);
            if (badStatePair.first != hypro::CONTAINMENT::NO) {
                DEBUG("hydra.worker",
                      "Intersection with local bad states. (intersection type " << badStatePair.first << ")");
                return badStatePair;
            }
        }

        // check global bad states
        for (const auto &badState: automaton.getGlobalBadStates()) {
            // at least one global bad Representation in this subspace
            std::pair<CONTAINMENT, Representation> badStatePair = intersect(valuationSet, badState, I);
            if (badStatePair.first != CONTAINMENT::NO) {
                DEBUG("hydra.worker", "Intersection with global bad states");
                return badStatePair;
            }
        }

        return std::make_pair(CONTAINMENT::NO, valuationSet);
    }

}  // namespace hypro
