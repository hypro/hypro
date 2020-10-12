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
	if ( !transitionPtr->getReset().empty() && !transitionPtr->getReset().isIdentity() ) {
		assert( transitionPtr->getReset().isAffineIdentity() && "Singular automata do not support linear/affine resets." );

		const IntervalAssignment<Number>& intervalReset = transitionPtr->getReset().getIntervalReset();
		if ( !intervalReset.isIdentity() ) {
			std::vector<std::size_t> projectOutDimensions;
			std::set<std::size_t> resetToZeroDimensions;
			VPolytope<Number> projectedSet = Converter<Number>::toVPolytope( stateSet );
			std::vector<Halfspace<Number>> newConstraints;
			for ( std::size_t i = 0; i < intervalReset.size(); ++i ) {
				if ( !intervalReset.mIntervals[i].isEmpty() ) {
					if ( intervalReset.mIntervals[i].lower() == 0 && intervalReset.mIntervals[i].upper() == 0 ) {
						// reset to zero: solve via linear transformation
						resetToZeroDimensions.insert( i );
					} else {
						// non-empty intervals represent some reset different from identity and from zero-> project out dimension, memorize new interval bounds
						projectOutDimensions.push_back( i );
						// create and store new interval bounds
						vector_t<Number> normal = vector_t<Number>::Zero( stateSet.dimension() );
						normal( i ) = Number( 1 );
						newConstraints.emplace_back( normal, intervalReset.mIntervals[i].upper() );
						normal = -normal;
						newConstraints.emplace_back( normal, -intervalReset.mIntervals[i].lower() );
					}
				}
			}

			// set entries in resetToZeroDimensions and projectOutDimensions to zero
			for ( auto& vertex : projectedSet.rVertices() ) {
				for ( Eigen::Index i = 0; i < vertex.rawCoordinates().rows(); ++i ) {
					if ( std::find( resetToZeroDimensions.begin(), resetToZeroDimensions.end(), std::size_t( i ) ) != resetToZeroDimensions.end() ) {
						vertex[i] = 0;
						// a selected dimension cannot be in both sets
						continue;
					}
					/*
					if ( std::find( projectOutDimensions.begin(), projectOutDimensions.end(), std::size_t( i ) ) != projectOutDimensions.end() ) {
						vertex[i] = 0;
					}
					*/
				}
			}
			HPolytope<Number> transformedSet = Converter<Number>::toHPolytope( projectedSet );

			// find bounding constraints for dimensions which are not reset to zero and remove them
			// Assumption: Those constraints do have non-zero entries in their normal vectors only for those bounding constraints
			// temporary: FM elimination
			auto [constraints, constants] = eliminateCols( transformedSet.matrix(), transformedSet.vector(), projectOutDimensions, true );
			transformedSet = HPolytope<Number>{ constraints, constants };

			// add interval bounds as new constraints
			transformedSet.insert( newConstraints.begin(), newConstraints.end() );

			// TODO convert to V-Rep., set entries in resetToZeroDimensions and projectOutDimensions to zero. Convert to H-rep, remove constraints (detect syntactically) on projectOutDimensions, insert new constraints.

			// convert back and assign to original representation type
			convert( transformedSet, stateSet );
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
