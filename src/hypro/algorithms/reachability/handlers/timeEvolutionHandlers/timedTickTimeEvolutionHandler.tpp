#include "timedTickTimeEvolutionHandler.h"

namespace hypro {
    template <class Representation,typename Number>
	void timedTickTimeEvolutionHandler<Representation,Number>::handle() {
		TRACE("hydra.worker",  "Before Elapse: \n" << boost::get<hypro::DifferenceBounds<Number>>(this->mState->getSet(this->mIndex))  << std::endl);
		hypro::DifferenceBounds<Number> dbm = boost::get<hypro::DifferenceBounds<Number>>(this->mState->getSet(this->mIndex));
        if(dbm.dimension() > 0){
        	// shift all clocks by timestep
        	dbm = dbm.shift(carl::convert<tNumber,Number>(this->mTimeStep));
        	this->mState->setSet(dbm,this->mIndex);
        }
        #ifdef HYDRA_USE_LOGGING
        // DBG
        DEBUG("hydra.worker","Set after timestep: " << this->mState->getSet(this->mIndex));
        hypro::Box<Number> tmp = hypro::Converter<Number>::toBox(boost::get<hypro::DifferenceBounds<Number>>(this->mState->getSet(this->mIndex)));
        DEBUG("hydra.worker","Set after timestep(box): " << tmp);
        #endif
    }
} // hypro