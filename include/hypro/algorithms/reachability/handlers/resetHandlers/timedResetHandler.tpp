/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "timedResetHandler.h"

namespace hypro {
    template<typename State>
    void timedResetHandler<State>::handle() {
        TRACE("hydra.worker", "Applying Reset trafo: \n"
                << this->mTrafo << "\n Reset translation: \n"
                << this->mTranslation << "to" << this->mIndex);
        hypro::DifferenceBounds<Number> dbm = std::get<hypro::DifferenceBounds<Number>>(
                this->mState->getSet(this->mIndex));
        for (int i = 0; i < this->mTrafo.rows(); i++) {
            // if the diagonal entry of a clock is 0.0, reset that clock
            if (this->mTrafo(i, i) + 0.0 == 0.0) {
                dbm = dbm.reset(i + 1, 0.0);
            }
        }
        this->mState->setSetDirect(dbm, this->mIndex);
    }
}  // namespace hypro
