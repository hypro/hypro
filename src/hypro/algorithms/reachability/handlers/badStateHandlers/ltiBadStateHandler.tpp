#include "ltiBadStateHandler.h"

namespace hypro {

template <typename State>
std::pair<CONTAINMENT, State> ltiIntersectBadStates( const State& stateSet, const HybridAutomaton<typename State::NumberType>& automaton ) {
	auto localBadState = automaton.getLocalBadStates().find( stateSet.getLocation() );
	if ( localBadState != automaton.getLocalBadStates().end() ) {
		std::pair<CONTAINMENT, State> badStatePair = stateSet.partiallySatisfies( localBadState->second, 0 );
		if ( badStatePair.first != hypro::CONTAINMENT::NO ) {
			DEBUG( "hydra.worker", "Intersection with local bad states. (intersection type " << badStatePair.first << ")" );
			return badStatePair;
		}
	}

	// check global bad states
	for ( const auto& badState : automaton.getGlobalBadStates() ) {
		// at least one global bad state in this subspace
		std::pair<CONTAINMENT, State> badStatePair = stateSet.partiallySatisfies( badState, 0 );
		if ( badStatePair.first != CONTAINMENT::NO ) {
			DEBUG( "hydra.worker", "Intersection with global bad states" );
			return badStatePair;
		}
	}

	return std::make_pair( CONTAINMENT::NO, stateSet );
}

template <typename State>
std::pair<CONTAINMENT, State> ltiIntersectBadStates( const State& stateSet, const Condition<typename State::NumberType>& localBadState, const std::vector<Condition<typename State::NumberType>>& globalBadStates ) {
	//TODO @Stefan Not sure if this is right.
	size_t index = 0;

	TRACE( "hydra.worker.continuous", "Checking local bad state: " << localBadState->second );
	std::pair<CONTAINMENT, State> badStatePair = stateSet.partiallySatisfies( localBadState->second, index );
	if ( badStatePair.first != hypro::CONTAINMENT::NO ) {
		DEBUG( "hydra.worker", "Intersection with local bad states. (intersection type " << badStatePair.first << ")" );
		return badStatePair;
	}
	TRACE( "hydra.worker.continuous", "No intersection with local, continuous bad states" );

	// check global bad states
	for ( const auto& badState : globalBadStates ) {
		// at least one global bad state in this subspace
		std::pair<CONTAINMENT, State> badStatePair = stateSet.partiallySatisfies( badState, index );
		if ( badStatePair.first != CONTAINMENT::NO ) {
			DEBUG( "hydra.worker", "Intersection with global bad states" );
			return badStatePair;
		}
	}

	return std::make_pair( CONTAINMENT::NO, stateSet );
}
}  // namespace hypro