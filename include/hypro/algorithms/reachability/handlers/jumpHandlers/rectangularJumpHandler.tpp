#include "rectangularJumpHandler.h"

namespace hypro {

template <typename State>
auto rectangularJumpHandler<State>::applyJump( const TransitionStateMap& states, Transition<Number>* transition, const AnalysisParameters& strategy, bool reverse ) -> TransitionStateMap {
	// holds a mapping of transitions to states which need to be aggregated
	TransitionStateMap toAggregate;
	// holds a mapping of transitions to states which are ready to apply the reset function and the intersection with the invariant
	TransitionStateMap toProcess = filter( states, transition );
	// holds a mapping of transitions to already processed (i.e. aggregated, resetted and reduced) states
	TransitionStateMap processedStates;

	DEBUG( "hydra.worker", "Apply jump on " << toProcess.size() << " transitions." );

	for ( const auto& [transitionPtr, statesVec] : toProcess ) {
		DEBUG( "hydra.worker", "Apply jump on " << statesVec.size() << " states." );
		for ( const auto& state : statesVec ) {
			// copy state - as there is no aggregation, the containing set and timestamp is already valid
			// TODO: Why copy?
			assert( !state.getTimestamp().isEmpty() );
			State newState( state );

			if ( reverse ) {
				// apply guard function
				applyGuard( newState, transitionPtr );
				// set source location in state set
				newState.setLocation( transitionPtr->getSource() );
			} else {
				// apply reset function
				applyReset( newState, transitionPtr );
				// set target location in state set
				newState.setLocation( transitionPtr->getTarget() );
			}

			// check invariant in new location
			auto [containment, stateSet] = rectangularIntersectInvariant( newState );
			if ( containment == CONTAINMENT::NO ) {
				continue;
			}

			// reduce if possible (Currently only for support functions)
			stateSet.reduceRepresentation();

			DEBUG( "hydra.worker.discrete", "State after reduction: " << stateSet );

			if ( processedStates.find( transitionPtr ) == processedStates.end() ) {
				processedStates[transitionPtr] = std::vector<State>();
			}
			processedStates[transitionPtr].emplace_back( stateSet );
		}
	}
	return processedStates;
}

template <typename State>
void rectangularJumpHandler<State>::applyReset( State& state, Transition<Number>* transitionPtr ) const {
	if ( !transitionPtr->getReset().empty() ) {
		if ( transitionPtr->getReset().getMatrix().size() > 0 ) {
			state = State{ CarlPolytope<typename State::NumberType>{ transitionPtr->getReset().getMatrix(), transitionPtr->getReset().getVector() } };
		} else {
			for ( size_t i = 0; i < state.getNumberSets(); i++ ) {
				IntervalAssignment<Number> intervalReset = transitionPtr->getReset().getIntervalReset( i );
				state = state.partialIntervalAssignment( intervalReset.mIntervals, i );
			}
		}
	}
}

template <typename State>
auto rectangularJumpHandler<State>::applyReverseJump( const TransitionStateMap& states, Transition<Number>* transition, const AnalysisParameters& strategy ) -> TransitionStateMap {
	return applyJump( states, transition, strategy, true );
}

template <typename State>
void rectangularJumpHandler<State>::applyGuard( State& state, Transition<Number>* transitionPtr ) const {
	if ( !transitionPtr->getGuard().empty() ) {
		state.setSet( typename State::template nth_representation<0>{ transitionPtr->getGuard().getMatrix(), transitionPtr->getGuard().getVector() } );
	}
}
template <typename State>
auto rectangularJumpHandler<State>::filter( const TransitionStateMap& states, Transition<Number>* transition ) const -> TransitionStateMap {
	TransitionStateMap res;
	for ( const auto& [transitionPtr, statesVec] : states ) {
		// only handle sets related to the passed transition, in case any is passed.
		if ( transition == nullptr || transitionPtr == transition ) {
			// check aggregation settings

			auto& targetVec = res[transitionPtr];
			targetVec.insert( targetVec.end(), statesVec.begin(), statesVec.end() );
		}
	}
	return res;
}
}  // namespace hypro
