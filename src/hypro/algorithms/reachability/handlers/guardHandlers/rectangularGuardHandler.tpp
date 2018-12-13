#include "rectangularGuardHandler.h"

namespace hypro {
    template<typename State>
	void rectangularGuardHandler<State>::handle() {
		assert(!mGuardSatisfyingState->getTimestamp().isEmpty());

		TRACE("hydra.worker.discrete","Applying handler " << this->handlerName());

		// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
		// create carlPolytope, as intersection is defined for those
		CarlPolytopeT<typename State::NumberType> guardConstraints{mTransition->getGuard().getMatrix(mIndex), mTransition->getGuard().getVector(mIndex)};
		// substitute variables in the formulas by the correct ones in the subspace of the state
		// 1. Determine offset
		std::size_t dimensionOffset = mState->getDimensionOffset(mIndex);
		// 2. substitute
		for(std::size_t i = 0; i < mState->getDimension(mIndex); ++i){
			guardConstraints.substituteVariable(vpool.carlVarByIndex(i), vpool.carlVarByIndex(i+dimensionOffset));
		}

		// intersect
		auto resultingSet = boost::get<CarlPolytopeT<typename State::NumberType>>(mState->getSet(mIndex)).intersect(guardConstraints);

		// determine full vs. partial containment
		if(resultingSet == boost::get<CarlPolytopeT<typename State::NumberType>>(mState->getSet(mIndex))) {
			mContainment = CONTAINMENT::FULL;
		}

		// reduction
		resultingSet.reduceRepresentation();

		// set containment information
		if(resultingSet.empty()) {
			mContainment = CONTAINMENT::NO;
		} else {
			assert(resultingSet != boost::get<CarlPolytopeT<typename State::NumberType>>(mState->getSet(mIndex)));
			mContainment = CONTAINMENT::PARTIAL;
		}
		mState->setSet(resultingSet, mIndex);
	}

	template<typename State>
	void rectangularGuardHandler<State>::reinitialize(){
		TRACE("hydra.worker.discrete","Reinitializing handler " << this->handlerName());
		mSatisfies=false;
		mContained = CONTAINMENT::NO;
	}
} // hypro
