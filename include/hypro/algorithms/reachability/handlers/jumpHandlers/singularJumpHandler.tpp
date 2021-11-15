#include "singularJumpHandler.h"

namespace hypro {

template <typename Representation>
auto singularJumpHandler<Representation>::applyJump( const TransitionStateMap& states, std::size_t subspace ) -> TransitionStateMap {
	// holds a mapping of transitions to already processed (i.e. aggregated, resetted and reduced) states
	TransitionStateMap processedStates;

	DEBUG( "hydra.worker", "Apply jump on " << states.size() << " transitions." );

	for ( const auto& [transitionPtr, statesVec] : states ) {
		DEBUG( "hydra.worker", "Apply jump on " << statesVec.size() << " states." );
		for ( const auto& state : statesVec ) {
			// copy state - as there is no aggregation, the containing set and timestamp is already valid
			Representation newState( state );

			// apply reset function
			applyReset( newState, transitionPtr, subspace );

			// check invariant in new location
			auto [containment, stateSet] = intersect( newState, transitionPtr->getTarget()->getInvariant(), subspace );
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
void singularJumpHandler<Representation>::applyReset( Representation& stateSet, Transition<Number>* transitionPtr, std::size_t subspace ) const {
	// We have 3 different implementations for applying resets and want to check that they all give the same result.
	// Note: applyResetFM is the one that definitely works.
	// Todo: Decide for one implementation and remove other 2
	if ( !transitionPtr->getReset().empty() ) {
		Reset<Number> reset = transitionPtr->getReset();
		assert( reset.getAffineReset( subspace ).isSingular() && "Singular automata do not support linear/affine resets." );

		IntervalAssignment<Number> intervalReset = transitionPtr->getReset().getIntervalReset( subspace );
		// if affine reset is singular and not identity, get constant resets
		if ( !reset.getAffineReset( subspace ).isIdentity() ) {
			WARN( "hypro.reachability", "Singular reset handler with affine constant assignments. Converting to interval reset." )
			matrix_t<Number> zeroRow = matrix_t<Number>::Zero( 1, reset.getMatrix( subspace ).cols() );
			for ( Eigen::Index rowIndex = 0; rowIndex < reset.getMatrix( subspace ).rows(); ++rowIndex ) {
				if ( reset.getMatrix( subspace ).row( rowIndex ) == zeroRow ) {
					// add interval for constant reset
					Number constant = reset.getVector( subspace )( rowIndex );
					assert( intervalReset.getIntervals()[rowIndex].isEmpty() && "Reset has both affine and interval assignment" );
					intervalReset.setInterval( carl::Interval<Number>( constant, constant ), rowIndex );
				}
			}
		}

		if ( !intervalReset.isIdentity() ) {
			auto transformedSet1 = applyResetFM( stateSet, intervalReset );
#ifndef NDEBUG
			auto transformedSet2 = applyResetFindZeroConstraints( stateSet, intervalReset );
			auto transformedSet3 = applyResetProjectAndExpand( stateSet, intervalReset );
			assert( transformedSet1.contains( transformedSet2 ) );
			//assert( transformedSet2.contains( transformedSet1 ) ); // TODO there is a bug in this approach
			assert( transformedSet1.contains( transformedSet3 ) );
			//assert( transformedSet3.contains( transformedSet1 ) ); // TODO there might be a bug here as well
#endif
			convert( transformedSet1, stateSet );
			TRACE( "hypro.reachability", "Resulting state set " << stateSet );
		}
	}
}

template <typename Representation, typename Number>
HPolytope<Number> applyResetFM( Representation& stateSet, IntervalAssignment<Number> intervalReset ) {
	// Apply reset using FM (definitely works, is slow)
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

	return projectedSet.removeRedundancy();
}

template <typename Representation, typename Number>
HPolytope<Number> applyResetFindZeroConstraints( Representation& stateSet, IntervalAssignment<Number> intervalReset ) {
	// Apply reset by identifying 0-constraints of variables reset to non-zero value
	// Uses FM right now (should work, relatively slow)

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

	return transformedSet;
}

template <typename Representation, typename Number>
HPolytope<Number> applyResetProjectAndExpand( Representation& stateSet, IntervalAssignment<Number> intervalReset ) {
	// Apply reset by projecting reset-dimensions to 0 and removing all constraints on them
	// Fastest, want to test in practice to confirm that it works

	std::vector<std::size_t> resetDimensions;
	std::vector<std::size_t> resetToNonZeroDimensions;
	std::vector<Halfspace<Number>> newConstraints;
	for ( std::size_t i = 0; i < intervalReset.size(); ++i ) {
		if ( !intervalReset.mIntervals[i].isEmpty() ) {
			resetDimensions.push_back( i );
			if ( intervalReset.mIntervals[i].lower() != 0 || intervalReset.mIntervals[i].upper() != 0 ) {
				// reset to zero is solved via linear transformation
				resetToNonZeroDimensions.push_back( i );
				vector_t<Number> normal = vector_t<Number>::Zero( stateSet.dimension() );
				normal( i ) = Number( 1 );
				newConstraints.emplace_back( normal, intervalReset.mIntervals[i].upper() );
				normal = -normal;
				newConstraints.emplace_back( normal, -intervalReset.mIntervals[i].lower() );
			}
		}
	}

	// set entries in resetDimensions to zero: Convert to VPolytope, set dimensions to 0, convert back
	VPolytope<Number> projectedSet = Converter<Number>::toVPolytope( stateSet );
	for ( auto& vertex : projectedSet.rVertices() ) {
		for ( auto i : resetDimensions ) {
			vertex[i] = 0;
		}
	}

	HPolytope<Number> transformedSet = Converter<Number>::toHPolytope( projectedSet );

	// Remove constraints on dimensions that are not reset to 0
	auto constraintMatrix = transformedSet.matrix();
	auto constraintVector = transformedSet.vector();
	for ( Eigen::Index row = 0; row < constraintMatrix.rows(); ++row ) {
		for ( auto i : resetToNonZeroDimensions ) {
			constraintMatrix( row, i ) = 0;
		}
	}

	// remove redundant constraints. This also removes zero-rows in the constraint matrix
	Optimizer<Number> opt( constraintMatrix, constraintVector );
	auto redundant = opt.redundantConstraints();
	constraintMatrix = removeRows( constraintMatrix, redundant );
	constraintVector = removeRows( constraintVector, redundant );

	transformedSet = HPolytope<Number>{ constraintMatrix, constraintVector };
	// add interval bounds as new constraints
	transformedSet.insert( newConstraints.begin(), newConstraints.end() );

	return transformedSet;
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
