/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "timedElapseAfterTickTimeEvolutionHandler.h"

namespace hypro {
    template<typename State>
    void timedElapseAfterTickTimeEvolutionHandler<State>::handle() {
        if (!mComputed) {     // only compute once
            DifferenceBounds<Number> dbmBeforeElapse = std::get<DifferenceBounds<Number>>(
                    this->mState->getSet(this->mIndex));
            this->mState->setSet(std::get<DifferenceBounds<Number>>(this->mState->getSet(this->mIndex)).elapse(),
                                 this->mIndex);
            DifferenceBounds<Number> dbm = std::get<DifferenceBounds<Number>>(this->mState->getSet(this->mIndex));
            // intersect the zone in each clock direction with the timeHorizon
            if (dbm.dimension() > 0) {
                size_t numclocks = dbm.dimension();
                for (size_t i = 1; i <= numclocks; i++) {
                    // x-0 <= x+timebound
                    dbm = dbm.intersectConstraint(i, 0, typename DifferenceBounds<Number>::DBMEntry(
                            dbmBeforeElapse.getDBM()(i, 0).first +
                            carl::convert<tNumber, Number>(mTimeBound - this->mTimeStep),
                            DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ));
                }
            }
            this->mState->setSet(dbm, this->mIndex);
            mComputed = true;
        }
#ifdef HYDRA_USE_LOGGING
        Box<Number> tmp = Converter<Number>::toBox( std::get<DifferenceBounds<Number>>( this->mState->getSet( this->mIndex ) ) );
        DEBUG( "hydra.worker", "Set after timestep: " << tmp );
#endif
    }
}  // namespace hypro
