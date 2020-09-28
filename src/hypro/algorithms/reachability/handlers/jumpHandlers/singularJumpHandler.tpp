#include "singularJumpHandler.h"

namespace hypro {

template <typename Representation>
auto singularJumpHandler<Representation>::applyJump( const TransitionStateMap& states ) -> TransitionStateMap {
	// holds a mapping of transitions to already processed (i.e. aggregated, resetted and reduced) states
	TransitionStateMap processedStates;

	DEBUG( "hydra.worker", "Apply jump on " << states.size() << " transitions." );

	for ( const auto& [transitionPtr, statesVec] : states ) {
		DEBUG( "hydra.worker", "Apply jump on " << statesVec.size() << " states." );
		for ( const auto& state : statesVec ) {
			// copy state - as there is no aggregation, the containing set and timestamp is already valid
			Representation newState( state );

			// apply reset function
			applyReset( newState, transitionPtr );

			// check invariant in new location
			auto [containment, stateSet] = intersect( newState, transitionPtr->getTarget()->getInvariant() );
			if ( containment == CONTAINMENT::NO ) {
				continue;
			}

			// optional: apply reduction (future work)

			// Note: Here we misuse the state's timestamp to carry the transition timing to the next stage -> just don't reset
			// the timestamp in case no aggregation happens.

			if ( processedStates.find( transitionPtr ) == processedStates.end() ) {
				processedStates[transitionPtr] = std::vector<Representation>();
			}
			processedStates[transitionPtr].emplace_back( stateSet );
		}
	}
	return processedStates;
}

template <typename Representation>
void singularJumpHandler<Representation>::applyReset( Representation& stateSet, Transition<Number>* transitionPtr ) const {
	if ( !transitionPtr->getReset().empty() ) {
		assert( transitionPtr->getReset().getAffineReset().isIdentity() && "Singular automata do not support linear/affine resets." );

		IntervalAssignment<Number> intervalReset = transitionPtr->getReset().getIntervalReset();
		if ( !intervalReset.isIdentity() ) {
			std::vector<std::size_t> projectOutDimensions;
			HPolytope<Number> projectedSet = Converter<Number>::toHPolytope( stateSet );
			std::vector<Halfspace<Number>> newConstraints;
			for ( std::size_t i = 0; i < intervalReset.size(); ++i ) {
				if ( !intervalReset.mIntervals[i].isEmpty() ) {
					// non-empty intervals represent some reset different from identity -> project out dimension, memorize new interval bounds
					projectOutDimensions.push_back( i );
					// create and store new interval bounds
					vector_t<Number> normal = vector_t<Number>::Zero( stateSet.dimension() );
					normal( i ) = Number( 1 );
					newConstraints.emplace_back( normal, intervalReset.mIntervals[i].upper() );
					normal = -normal;
					newConstraints.emplace_back( normal, -intervalReset.mIntervals[i].lower() );
				}
			}
			// add interval bounds as new constraints
			projectedSet = projectedSet.projectOutConservative( projectOutDimensions );
			projectedSet.insert( newConstraints.begin(), newConstraints.end() );

			// convert back and assign to original representation type
			convert( projectedSet, stateSet );
		}
	}
}

template <typename Representation>
auto singularJumpHandler<Representation>::applyReverseJump( const TransitionStateMap& states, Transition<Number>* transition ) -> TransitionStateMap {
	// holds a mapping of transitions to states which need to be aggregated
	TransitionStateMap toAggregate;
	// holds a mapping of transitions to states which are ready to apply the reset function and the intersection with the invariant
	TransitionStateMap toProcess;
	// holds a mapping of transitions to already processed (i.e. aggregated, resetted and reduced) states
	TransitionStateMap processedStates;
	for ( const auto& [transitionPtr, statesVec] : states ) {
		// only handle sets related to the passed transition, in case any is passed.
		if ( transition == nullptr || transitionPtr == transition ) {
			// check aggregation settings

			auto& targetVec = toProcess[transitionPtr];
			targetVec.insert( targetVec.end(), statesVec.begin(), statesVec.end() );
		}
	}

	DEBUG( "hydra.worker", "Apply jump on " << toProcess.size() << " transitions." );

	for ( const auto& [transitionPtr, statesVec] : toProcess ) {
		DEBUG( "hydra.worker", "Apply jump on " << statesVec.size() << " states." );
		for ( const auto& state : statesVec ) {
			// copy state - as there is no aggregation, the containing set and timestamp is already valid
			// TODO: Why copy?
			assert( !state.getTimestamp().isEmpty() );
			Representation newState( state );

			// apply guard function
			applyGuard( newState, transitionPtr );

			// set target location in state set
			newState.setLocation( transitionPtr->getSource() );

			// check invariant in new location
			auto [containment, stateSet] = rectangularIntersectInvariant( newState );
			if ( containment == CONTAINMENT::NO ) {
				continue;
			}

			// reduce if possible (Currently only for support functions)
			applyReduction( stateSet );

			DEBUG( "hydra.worker.discrete", "Representation after reduction: " << stateSet );

			// Note: Here we misuse the state's timestamp to carry the transition timing to the next stage -> just don't reset
			// the timestamp in case no aggregation happens.

			if ( processedStates.find( transitionPtr ) == processedStates.end() ) {
				processedStates[transitionPtr] = std::vector<Representation>();
			}
			processedStates[transitionPtr].emplace_back( stateSet );
		}
	}
	return processedStates;
}

}  // namespace hypro
