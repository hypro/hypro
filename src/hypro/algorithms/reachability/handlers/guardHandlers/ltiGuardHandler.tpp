#include "ltiGuardHandler.h"

namespace hypro {
    template <class Representation, typename Number>
	void ltiGuardHandler<Representation,Number>::handle() {
		assert(!mGuardSatisfyingState->getTimestamp().isEmpty());

		TRACE("hydra.worker.discrete","Applying handler " << this->handlerName());	
	    std::pair<CONTAINMENT,State_t<Number>> statePair = mGuardSatisfyingState->partiallySatisfies(mTransition->getGuard(), mIndex);

	    if(statePair.first == CONTAINMENT::NO) {
	    	mSatisfies = false;
	    	return;
	    }
	    mGuardSatisfyingState->setSetDirect(statePair.second.getSet(mIndex), mIndex);
	    mGuardSatisfyingState->setSetType(statePair.second.getSetType(mIndex),mIndex);
	    mSatisfies =  true;
	}

	template <class Representation, typename Number>
	void ltiGuardHandler<Representation,Number>::reinitialize(){
		TRACE("hydra.worker.discrete","Reinitializing handler " << this->handlerName());	
		mSatisfies=false;
		//mGuardSatisfyingState->setSetDirect(currentState.getSet(mIndex),mIndex);
		//mGuardSatisfyingState->setSetType(currentState.getSetType(mIndex),mIndex);
	}
} // hypro