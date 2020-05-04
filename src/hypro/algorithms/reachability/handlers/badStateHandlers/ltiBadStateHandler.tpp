#include "ltiBadStateHandler.h"

namespace hypro {
template <typename State>
std::pair<CONTAINMENT, State> ltiIntersectBadStates( const State& stateSet ) {
	TRACE( "hydra.worker.continuous", "Having a total of " << SettingsProvider<State>::getInstance().getHybridAutomaton().getLocalBadStates().size() << " local bad states." );
	auto localBadState = SettingsProvider<State>::getInstance().getHybridAutomaton().getLocalBadStates().find( stateSet.getLocation() );
	if ( localBadState != SettingsProvider<State>::getInstance().getHybridAutomaton().getLocalBadStates().end() ) {
		TRACE( "hydra.worker.continuous", "Checking local bad state: " << localBadState->second );
		std::pair<CONTAINMENT, State> badStatePair = stateSet.partiallySatisfies( localBadState->second, mIndex );
		if ( badStatePair.first != hypro::CONTAINMENT::NO ) {
			DEBUG( "hydra.worker", "Intersection with local bad states. (intersection type " << badStatePair.first << ")" );
			return badStatePair;
		}
	}
	TRACE( "hydra.worker.continuous", "No intersection with local, continuous bad states" );

	// check global bad states
	for ( const auto& badState : SettingsProvider<State>::getInstance().getHybridAutomaton().getGlobalBadStates() ) {
		if ( badState.getMatrix( mIndex ).rows() != 0 ) {
			// at least one global bad state in this subspace
			std::pair<CONTAINMENT, State> badStatePair = stateSet.partiallySatisfies( badState, mIndex );
			if ( badStatePair.first != CONTAINMENT::NO ) {
				DEBUG( "hydra.worker", "Intersection with global bad states" );
				return badStatePair;
			}
		}
	}

	return std::make_pair<CONTAINMENT, State>( CONTAINMENT::NO, stateSet );
}
}  // namespace hypro