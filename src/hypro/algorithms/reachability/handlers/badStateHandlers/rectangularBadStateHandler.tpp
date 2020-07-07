#include "rectangularBadStateHandler.h"

namespace hypro {
template <typename State>
std::pair<CONTAINMENT, State> rectangularIntersectBadStates( const State& stateSet, const HybridAutomaton<typename State::NumberType>& automaton ) {
	auto& vpool = hypro::VariablePool::getInstance();

	TRACE( "hydra.worker.continuous", "Having a total of " << automaton.getLocalBadStates().size() << " local bad states." );
	auto localBadState = automaton.getLocalBadStates().find( stateSet.getLocation() );
	if ( localBadState != automaton.getLocalBadStates().end() ) {
		TRACE( "hydra.worker.continuous", "Checking local bad state: " << localBadState->second );

		// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
		// create carlPolytope, as intersection is defined for those
		CarlPolytope<typename State::NumberType> badStateConstraints{ localBadState->second.getMatrix(), localBadState->second.getVector() };

		// intersect
		auto resultingSet = std::get<CarlPolytope<typename State::NumberType>>( stateSet.getSet() ).intersect( badStateConstraints );

		// reduction
		resultingSet.removeRedundancy();

		// process containment information
		if ( !resultingSet.empty() ) {
			DEBUG( "hydra.worker", "Intersection with local bad states. (intersection type " << mContainment << ")" );
			return std::make_pair( CONTAINMENT::YES, resultingSet );
		}
	}

	TRACE( "hydra.worker.continuous", "No intersection with local, continuous bad states" );

	// check global bad states
	for ( const auto& badState : automaton.getGlobalBadStates() ) {
		if ( badState.getMatrix().rows() != 0 ) {
			// at least one global bad state in this subspace
			// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
			// create carlPolytope, as intersection is defined for those
			CarlPolytope<typename State::NumberType> badStateConstraints{ badState.getMatrix(), badState.getVector() };

			// intersect
			auto resultingSet = std::get<CarlPolytope<typename State::NumberType>>( stateSet.getSet() ).intersect( badStateConstraints );

			// reduction
			resultingSet.removeRedundancy();

			// set containment information
			if ( !resultingSet.empty() ) {
				return std::make_pair( CONTAINMENT::YES, resultingSet );
			}
		}
	}
	return std::make_pair( CONTAINMENT::NO, stateSet );
}

}  // namespace hypro
