#include "timedElapseTimeEvolutionHandler.h"

namespace hypro
{
    template<typename State>
	void timedElapseTimeEvolutionHandler<State>::handle() {
		if(!mComputed){ //only compute once
            hypro::DifferenceBounds<Number> dbmBeforeElapse = boost::get<hypro::DifferenceBounds<Number>>(this->mState->getSet(this->mIndex));
            this->mState->setSet(boost::get<hypro::DifferenceBounds<Number>>(this->mState->getSet(this->mIndex)).elapse(),this->mIndex);
            hypro::DifferenceBounds<Number> dbm = boost::get<hypro::DifferenceBounds<Number>>(this->mState->getSet(this->mIndex));
            // intersect the zone in each clock direction with the timeHorizon
            if(dbm.dimension() > 0){
            	size_t numclocks = dbm.dimension();
            	for(size_t i=1; i <= numclocks; i++){
            		// x-0 <= x+timebound
            		dbm = dbm.intersectConstraint( i, 0, typename hypro::DifferenceBounds<Number>::DBMEntry(dbmBeforeElapse.getDBM()(i,0).first+carl::convert<tNumber,Number>(mTimeBound),hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ));
            	}
            }
            this->mState->setSet(dbm,this->mIndex);
            mComputed = true;
		}
        #ifdef HYDRA_USE_LOGGING
        // DBG
        hypro::Box<Number> tmp = hypro::Converter<Number>::toBox(boost::get<hypro::DifferenceBounds<Number>>(this->mState->getSet(this->mIndex)));
        DEBUG("hydra.worker","Set after timestep: " << tmp);
        #endif
    }
} // hypro
