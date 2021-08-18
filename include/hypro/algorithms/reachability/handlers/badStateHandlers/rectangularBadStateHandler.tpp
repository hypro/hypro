#include "rectangularBadStateHandler.h"

namespace hypro {
template <typename State, typename Location>
std::pair<CONTAINMENT, State> rectangularIntersectBadStates( const State& stateSet, const Location* loc, const HybridAutomaton<typename State::NumberType>& automaton ) {
	TRACE( "hydra.worker.continuous", "Having a total of " << automaton.getLocalBadStates().size() << " local bad states." );
	auto localBadState = automaton.getLocalBadStates().find( loc );
	if ( localBadState != automaton.getLocalBadStates().end() ) {
		TRACE( "hydra.worker.continuous", "Checking local bad state: " << localBadState->second );

		// create constraints for invariant. Note that we need to properly match dimension indices with variable names at some point.
		// create carlPolytope, as intersection is defined for those
		State badStateConstraints{ localBadState->second.getMatrix(), localBadState->second.getVector() };

		// intersect
		auto resultingSet = stateSet.intersect( badStateConstraints );

		// reduction
		resultingSet.removeRedundancy();

		// process containment information
		if ( !resultingSet.empty() ) {
			DEBUG( "hydra.worker", "Intersection with local bad states." );
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
			State badStateConstraints{ badState.getMatrix(), badState.getVector() };

			// intersect
			auto resultingSet = stateSet.intersect( badStateConstraints );

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

template <typename State, typename Location>
std::pair<CONTAINMENT, State> rectangularBadIntersectInitialStates( const State& stateSet, const Location* loc, const HybridAutomaton<typename State::NumberType>& automaton ) {
	TRACE( "hydra.worker.continuous", "Having a total of " << automaton.getInitialStates().size() << " initial states." );
	auto initialState = automaton.getInitialStates().find( loc );
	if ( initialState != automaton.getInitialStates().end() ) {
		TRACE( "hydra.worker.continuous", "Checking initial state: " << initialState->second );

		// create constraints for initial state set
		// create carlPolytope, as intersection is defined for those
		State initialConstraints{ initialState->second.getMatrix(), initialState->second.getVector() };

		// intersect
		auto resultingSet = stateSet.intersect( initialConstraints );

		// reduction
		resultingSet.removeRedundancy();

		// process containment information
		if ( !resultingSet.empty() ) {
			DEBUG( "hydra.worker", "Intersection with initial states." );
			return std::make_pair( CONTAINMENT::YES, resultingSet );
		}
	}

	TRACE( "hydra.worker.continuous", "No intersection with local, continuous bad states" );

	return std::make_pair( CONTAINMENT::NO, stateSet );
}

}  // namespace hypro
