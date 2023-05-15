/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "timedTickTimeEvolutionHandler.h"

namespace hypro {
    template<typename State>
    void timedTickTimeEvolutionHandler<State>::handle() {
        TRACE("hydra.worker", "Before Elapse: \n"
                << std::get<hypro::DifferenceBounds<Number>>(this->mState->getSet(this->mIndex)) << std::endl);
        hypro::DifferenceBounds<Number> dbm = std::get<hypro::DifferenceBounds<Number>>(
                this->mState->getSet(this->mIndex));
        if (dbm.dimension() > 0) {
            // shift all clocks by timestep
            dbm = dbm.shift(carl::convert<tNumber, Number>(this->mTimeStep));
            this->mState->setSet(dbm, this->mIndex);
            this->mState->addTimeToClocks(this->mTimeStep);
        }
#ifdef HYPRO_USE_LOGGING
        // DBG
        // DEBUG( "hydra.worker", "Set after timestep: " << this->mState->getSet( this->mIndex ) );
        hypro::Box<Number> tmp = hypro::Converter<Number>::toBox( std::get<hypro::DifferenceBounds<Number>>( this->mState->getSet( this->mIndex ) ) );
        DEBUG( "hydra.worker", "Set after timestep(box): " << tmp );
#endif
    }
}  // namespace hypro
