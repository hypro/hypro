#include "ltiTimeEvolutionHandler.h"

namespace hypro {
    template <class Representation,typename Number>
	void ltiTimeEvolutionHandler<Representation,Number>::handle() {   
        TRACE("hydra.worker","Applying timestep to " << mState->getSet(mIndex));       
        TRACE("hydra.worker","Flow trafo: \n" << mTrafo << "\n Flow translation: \n"<< mTranslation);
        State_t<Number> res = mState->partiallyApplyTimeStep(hypro::ConstraintSet<Number>(mTrafo, mTranslation), mTimeStep, mIndex);
	    mState->setSetDirect(res.getSet(mIndex),mIndex);
        mState->setSetType(res.getSetType(mIndex),mIndex);      
        #ifdef HYDRA_USE_LOGGING
        // DBG
        hypro::Box<Number> tmp = hypro::Converter<Number>::toBox(boost::get<Representation>(mState->getSet(mIndex)));
        DEBUG("hydra.worker","Set after timestep: " << tmp);
        #endif
    }
} // hypro