#include "rectangularGuardHandler.h"

namespace hypro {
template <typename State>
void rectangularGuardHandler<State>::operator()( const State& state ) {
	assert( !state.getTimestamp().isEmpty() );

	// TRACE( "hydra.worker.discrete", "Applying handler " << this->handlerName() );

	for ( auto& transitionPtr : state.getLocation()->getTransitions() ) {
		CONTAINMENT containmentResult = CONTAINMENT::BOT;
		State guard(state);
		if ( !transitionPtr->getGuard().empty() ){
			guard = State{ CarlPolytope<typename State::NumberType>{ transitionPtr->getGuard().getMatrix(), transitionPtr->getGuard().getVector() } };
		}

		// intersect
		auto resultingSet = state.intersect( guard );

		// determine full vs. partial containment
		if ( resultingSet == state ) {
			containmentResult = CONTAINMENT::FULL;
		}

		// reduction
		resultingSet.removeRedundancy();

		// return containment information
		if ( resultingSet.isEmpty() ) {
			containmentResult = CONTAINMENT::NO;
		} else if ( containmentResult != CONTAINMENT::FULL ) {
			containmentResult = CONTAINMENT::PARTIAL;
		} else {
			containmentResult = CONTAINMENT::FULL;
		}

		if ( containmentResult != CONTAINMENT::NO ) {
			mGuardSatisfyingStates[transitionPtr.get()].emplace_back( std::move( resultingSet ) );
		}
		mGuardContainment[transitionPtr.get()] = containmentResult;
	}
}

}  // namespace hypro
