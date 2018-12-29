#include "rectangularGuardHandler.h"

namespace hypro {
    template<typename State>
	void rectangularGuardHandler<State>::handle() {
		assert(!mState->getTimestamp().isEmpty());

		TRACE("hydra.worker.discrete","Applying handler " << this->handlerName());

		auto& vpool = VariablePool::getInstance();

		// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
		// create carlPolytope, as intersection is defined for those
		CarlPolytope<typename State::NumberType> guardConstraints{mTransition->getGuard().getMatrix(mIndex), mTransition->getGuard().getVector(mIndex)};
		// substitute variables in the formulas by the correct ones in the subspace of the state
		// 1. Determine offset
		std::size_t dimensionOffset = mState->getDimensionOffset(mIndex);
		// 2. substitute
		for(std::size_t i = 0; i < mState->getDimension(mIndex); ++i){
			guardConstraints.substituteVariable(vpool.carlVarByIndex(i), vpool.carlVarByIndex(i+dimensionOffset));
		}

		// intersect
		auto resultingSet = boost::get<CarlPolytope<typename State::NumberType>>(mState->getSet(mIndex)).intersect(guardConstraints);

		// determine full vs. partial containment
		if(resultingSet == boost::get<CarlPolytope<typename State::NumberType>>(mState->getSet(mIndex))) {
			mContainment = CONTAINMENT::FULL;
		}

		// reduction
		resultingSet.removeRedundancy();

		// set containment information
		if(resultingSet.empty()) {
			mContainment = CONTAINMENT::NO;
		} else if (mContainment != CONTAINMENT::FULL) {
			//assert(resultingSet != boost::get<CarlPolytope<typename State::NumberType>>(mState->getSet(mIndex)));
			mContainment = CONTAINMENT::PARTIAL;
		}
		mState->setSet(resultingSet, mIndex);
	}

	template<typename State>
	void rectangularGuardHandler<State>::reinitialize(){
		TRACE("hydra.worker.discrete","Reinitializing handler " << this->handlerName());
		mContainment = CONTAINMENT::NO;
	}
} // hypro
