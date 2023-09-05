/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "timedBadStateHandler.h"

namespace hypro {
    template<typename State>
    void timedBadStateHandler<State>::handle() {
        // iterate over local bad states first.
        TRACE("hydra.worker.continuous", "Having a total of "
                << SettingsProvider<State>::getInstance().getHybridAutomaton().getLocalBadStates().size()
                << " local bad states.");
        auto localBadState = SettingsProvider<State>::getInstance().getHybridAutomaton().getLocalBadStates().find(
                this->mState->getLocation());
        if (localBadState != SettingsProvider<State>::getInstance().getHybridAutomaton().getLocalBadStates().end()) {
            // it may happen that the constraint set of a local bad state may be empty for our subspace, do not check
            // these empty constraints because in general, not having constraints implies full containment (eg. for invariants)
            if (localBadState->second.constraints().at(this->mIndex).dimension() != 0) {
                TRACE("hydra.worker.continuous", "Checking local bad state: " << localBadState->second);

                Condition<Number> badConditions = localBadState->second;
                if (badConditions.size() != 0) {
                    matrix_t<Number> constraints = badConditions.getMatrix(this->mIndex);
                    vector_t<Number> constants = badConditions.getVector(this->mIndex);

                    std::pair<CONTAINMENT, DifferenceBounds<Number>> badStatePair = std::get<DifferenceBounds<Number>>(
                            this->mState->getSet(this->mIndex)).intersectConstraints(constraints, constants,
                                                                                     CONTAINMENT::NO);

                    if (badStatePair.first != CONTAINMENT::NO) {
                        DEBUG("hydra.worker",
                              "Intersection with local bad states. (intersection type " << badStatePair.first << ")");
                        this->mIntersects = true;
                        return;
                    }
                }
            }
        }
        TRACE("hydra.worker.continuous", "No intersection with local, continuous bad states");

        // check global bad states
        for (const auto &badState: SettingsProvider<State>::getInstance().getHybridAutomaton().getGlobalBadStates()) {
            if (badState.size() != 0) {
                matrix_t<Number> constraints = badState.getMatrix(this->mIndex);
                vector_t<Number> constants = badState.getVector(this->mIndex);

                std::pair<CONTAINMENT, DifferenceBounds<Number>> badStatePair = std::get<DifferenceBounds<Number>>(
                        this->mState->getSet(this->mIndex)).intersectConstraints(constraints, constants,
                                                                                 CONTAINMENT::NO);

                if (badStatePair.first != CONTAINMENT::NO) {
                    DEBUG("hydra.worker", "Intersection with global bad states");
                    this->mIntersects = true;
                    return;
                }
            }
        }
        this->mIntersects = false;
    }
}  // namespace hypro
