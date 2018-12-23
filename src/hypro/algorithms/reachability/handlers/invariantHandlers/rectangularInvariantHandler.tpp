#include "rectangularInvariantHandler.h"

namespace hypro {
    template <typename State>
	void rectangularInvariantHandler<State>::handle() {
		assert(!mState->getTimestamp().isEmpty());
	    // check if initial Valuation fulfills Invariant
	    assert(mState->getLocation() != nullptr);
		auto& vpool = hypro::VariablePool::getInstance();

	    TRACE("hydra.worker","Check invariant: " << mState->getLocation()->getInvariant() << " for set " << mState);

		// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
		// create carlPolytope, as intersection is defined for those
		CarlPolytope<typename State::NumberType> invariantConstraints{mState->getLocation()->getInvariant().getMatrix(mIndex), mState->getLocation()->getInvariant().getVector(mIndex)};
		// substitute variables in the formulas by the correct ones in the subspace of the state
		// 1. Determine offset
		std::size_t dimensionOffset = mState->getDimensionOffset(mIndex);
		// 2. substitute
		for(std::size_t i = 0; i < mState->getDimension(mIndex); ++i){
			invariantConstraints.substituteVariable(vpool.carlVarByIndex(i), vpool.carlVarByIndex(i+dimensionOffset));
		}

		// intersect
		auto resultingSet = boost::get<CarlPolytope<typename State::NumberType>>(mState->getSet(mIndex)).intersect(invariantConstraints);

		// determine full vs. partial containment
		if(resultingSet == boost::get<CarlPolytope<typename State::NumberType>>(mState->getSet(mIndex))) {
			mContainment = CONTAINMENT::FULL;
		}

		// reduction
		resultingSet.removeRedundancy();

		// set containment information
		if(resultingSet.empty()) {
			mContainment = CONTAINMENT::NO;
		} else if( mContainment != CONTAINMENT::FULL ) {
			mContainment = CONTAINMENT::PARTIAL;
		}

		mState->setSet(resultingSet, mIndex);
	}
} // hypro
