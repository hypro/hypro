/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "timedElapseFirstSegmentHandler.h"

namespace hypro {
    template<typename State>
    void timedElapseFirstSegmentHandler<State>::handle() {
        assert(!this->mState->getTimestamp().isEmpty());
        // check if initial Valuation fulfills Invariant
        assert(this->mState->getLocation() != nullptr);

        // set trafo and translation
        int rows = this->mState->getLocation()->getLinearFlow(this->mIndex).dimension();
        this->mTrafo = matrix_t<Number>::Identity(rows - 1, rows - 1);
        this->mTranslation = vector_t<Number>::Ones(rows - 1) * carl::convert<tNumber, Number>(this->mTimeStep);
    }
}  // namespace hypro
