#include "ltiInvariantHandler.h"

namespace hypro {
    template <class Representation,typename Number>
	void ltiInvariantHandler<Representation,Number>::handle() {
		assert(!mState->getTimestamp().isEmpty());
	    // check if initial Valuation fulfills Invariant
	    assert(mState->getLocation() != nullptr);
		
	    TRACE("hydra.worker","Check invariant: " << mState->getLocation()->getInvariant() << " for set " << mState);

	    std::pair<CONTAINMENT,State_t<Number>> invariantSatisfyingPair = mState->partiallySatisfies(mState->getLocation()->getInvariant(), mIndex);
        if (invariantSatisfyingPair.first != CONTAINMENT::NO) {
		
        	#ifdef HYDRA_USE_LOGGING
        	// DBG
	        Box<Number> tmp = Converter<Number>::toBox(boost::get<Representation>(invariantSatisfyingPair.second.getSet(mIndex)));
	        DEBUG("hydra.worker","Invariant satisfying segment: " << tmp);
	        #endif

	        mContainment = invariantSatisfyingPair.first;
	        mState->setSet(boost::get<Representation>(invariantSatisfyingPair.second.getSet(mIndex)),mIndex);
            return;
        } // if set does not satisfy the invariant, return false 
        else {
        	mContainment = CONTAINMENT::NO;
            return;
        }
	}
} // hypro