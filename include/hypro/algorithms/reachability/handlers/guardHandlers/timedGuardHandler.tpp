/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "timedGuardHandler.h"

namespace hypro {
    template<typename State>
    void timedGuardHandler<State>::handle() {
        TRACE("hydra.worker.discrete", "Check guard for transition " << this->mTransition->getSource()->getName() << "("
                                                                     << this->mTransition->getSource()->hash() << ")"
                                                                     << " -> "
                                                                     << this->mTransition->getTarget()->getName() << "("
                                                                     << this->mTransition->getTarget()->hash() << ")");
        TRACE("hydra.worker.discrete",
              "Check guard constraint :" << this->mTransition->getGuard().getMatrix(this->mIndex) << "\n Transition: "
                                         << this->mTransition->getGuard().getVector(this->mIndex));

        std::pair<CONTAINMENT, hypro::DifferenceBounds<Number>> res = std::get<hypro::DifferenceBounds<Number>>(
                this->mGuardSatisfyingState->getSet(this->mIndex)).intersectConstraints(
                this->mTransition->getGuard().getMatrix(this->mIndex),
                this->mTransition->getGuard().getVector(this->mIndex), hypro::CONTAINMENT::FULL);

        if (res.first == CONTAINMENT::NO) {
            TRACE("hydra.worker.discrete", "Guard violating dbm: " << res.second);
            this->mSatisfies = false;
            return;
        }

        TRACE("hydra.worker.discrete", "Guard satisfying DBM: \n"
                << res.second);
        this->mGuardSatisfyingState->setSetDirect(res.second, this->mIndex);
        this->mSatisfies = true;
    }
}  // namespace hypro
