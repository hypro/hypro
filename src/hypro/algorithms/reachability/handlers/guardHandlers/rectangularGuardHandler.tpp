#include "rectangularGuardHandler.h"

namespace hypro {

template <typename Representation>
void rectangularGuardHandler<Representation>::operator()( const Representation& state, const Location<Number>* loc ) {
	// TRACE( "hydra.worker.discrete", "Applying handler " << this->handlerName() );

	for ( auto& transitionPtr : loc->getTransitions() ) {
		CONTAINMENT containmentResult = CONTAINMENT::BOT;
		Representation guard( state );
		if ( !transitionPtr->getGuard().empty() ) {
			guard = Representation{ transitionPtr->getGuard().getMatrix(), transitionPtr->getGuard().getVector() };
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
		if ( resultingSet.empty() ) {
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
