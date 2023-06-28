/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "timedInvariantHandler.h"

namespace hypro {
    template<typename State>
    void timedInvariantHandler<State>::handle() {
        // check if initial Valuation fulfills Invariant
        DEBUG("hydra.worker", "Check invariant: " << this->mState->getLocation()->getInvariant());
        // DEBUG( "hydra.worker", "Set before intersection with invariant:\n: " << this->mState->getSet( this->mIndex ) );

        Condition<Number> invariant = this->mState->getLocation()->getInvariant();

        matrix_t<Number> constraints = this->mState->getLocation()->getInvariant().getMatrix(this->mIndex);
        vector_t<Number> constants = this->mState->getLocation()->getInvariant().getVector(this->mIndex);

        std::pair<CONTAINMENT, DifferenceBounds<Number>> res = std::get<DifferenceBounds<Number>>(
                this->mState->getSet(this->mIndex)).intersectConstraints(
                this->mState->getLocation()->getInvariant().getMatrix(this->mIndex),
                this->mState->getLocation()->getInvariant().getVector(this->mIndex), CONTAINMENT::FULL);
        DEBUG("hydra.worker", "Set after intersection with invariant:\n"
                << res.second);
        if (res.first != CONTAINMENT::NO) {
#ifdef HYDRA_USE_LOGGING
            // DBG
            DEBUG( "hydra.worker", "Invariant satisfying segment: " << res.second );
            Box<Number> tmp = Converter<Number>::toBox( res.second );
            DEBUG( "hydra.worker", "Invariant satisfying segment (box): " << tmp );
#endif

            this->mContainment = res.first;
            this->mState->setSetDirect(res.second, this->mIndex);
            return;
        }  // if set does not satisfy the invariant, return false
        else {
            this->mContainment = CONTAINMENT::NO;
            return;
        }
    }
}  // namespace hypro
