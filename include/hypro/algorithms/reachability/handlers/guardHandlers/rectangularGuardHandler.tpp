#include "rectangularGuardHandler.h"

namespace hypro {

template <typename Representation>
void rectangularGuardHandler<Representation>::operator()( const Representation& state, const Location<Number>* loc ) {
	// TRACE( "hydra.worker.discrete", "Applying handler " << this->handlerName() );

	for ( auto& transitionPtr : loc->getTransitions() ) {
		/*
		Representation guard( state );
		if ( !transitionPtr->getGuard().empty() ) {
			guard = Representation{ transitionPtr->getGuard().getMatrix(), transitionPtr->getGuard().getVector() };
		}
		*/

		// intersect
		auto [containmentResult, resultingSet] = intersect( state, transitionPtr->getGuard() );

		// reduction
		resultingSet.removeRedundancy();

		if ( containmentResult != CONTAINMENT::NO ) {
			mGuardSatisfyingStates[transitionPtr.get()].emplace_back( std::move( resultingSet ) );
		}
		mGuardContainment[transitionPtr.get()] = containmentResult;
	}
}

}  // namespace hypro
