#include "ltiInvariantHandler.h"

namespace hypro {
    template <typename State>
	void ltiInvariantHandler<State>::handle() {
		assert(!mState->getTimestamp().isEmpty());
	    // check if initial Valuation fulfills Invariant
	    assert(mState->getLocation() != nullptr);

	    TRACE("hydra.worker","Check invariant: " << mState->getLocation()->getInvariant() << " for set " << mState);
	    std::pair<CONTAINMENT,State> invariantSatisfyingPair = mState->partiallySatisfies(mState->getLocation()->getInvariant(), mIndex);
        if (invariantSatisfyingPair.first != CONTAINMENT::NO) {
	        mContainment = invariantSatisfyingPair.first;
	        mState->setSet(invariantSatisfyingPair.second.getSet(mIndex),mIndex);
            return;
        } // if set does not satisfy the invariant, return false
        else {
        	mContainment = CONTAINMENT::NO;
            return;
        }
	}
} // hypro