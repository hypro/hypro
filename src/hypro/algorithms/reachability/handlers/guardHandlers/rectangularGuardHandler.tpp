#include "rectangularGuardHandler.h"

namespace hypro {
template <typename State>
CONTAINMENT rectangularGuardHandler<State>::operator()( const State& state ) {
	assert( !state->getTimestamp().isEmpty() );

	TRACE( "hydra.worker.discrete", "Applying handler " << this->handlerName() );

	auto& vpool = VariablePool::getInstance();

	// create constraints for the guard. Note that we need to properly match dimension indices with variable names at some point.
	// create carlPolytope, as intersection is defined for those
	CarlPolytope<typename State::NumberType> guardConstraints{mTransition->getGuard().getMatrix(), mTransition->getGuard().getVector()};
	// substitute variables in the formulas by the correct ones in the subspace of the state
	// 1. Determine offset
	std::size_t dimensionOffset = state->getDimensionOffset();
	// 2. substitute
	for ( std::size_t i = 0; i < state->getDimension(); ++i ) {
		guardConstraints.substituteVariable( vpool.carlVarByIndex( i ), vpool.carlVarByIndex( i + dimensionOffset ) );
	}

	// intersect
	auto resultingSet = std::get<CarlPolytope<typename State::NumberType>>( state->getSet() ).intersect( guardConstraints );

	// determine full vs. partial containment
	if ( resultingSet == std::get<CarlPolytope<typename State::NumberType>>( state->getSet() ) ) {
		mContainment = CONTAINMENT::FULL;
	}

	// reduction
	resultingSet.removeRedundancy();

	// set containment information
	if ( resultingSet.empty() ) {
		mContainment = CONTAINMENT::NO;
	} else if ( mContainment != CONTAINMENT::FULL ) {
		//assert(resultingSet != std::get<CarlPolytope<typename State::NumberType>>(mState->getSet(mIndex)));
		mContainment = CONTAINMENT::PARTIAL;
	}

	mState->setSet( resultingSet );
	return mContainment;
}

template <typename State>
void rectangularGuardHandler<State>::reinitialize() {
	TRACE( "hydra.worker.discrete", "Reinitializing handler " << this->handlerName() );
	mContainment = CONTAINMENT::BOT;
}
}  // namespace hypro
