#include "SingularWorker.h"

namespace hypro {

template <typename Representation>
REACHABILITY_RESULT SingularWorker<Representation>::computeForwardReachability( const ReachTreeNode<Representation>& task ) {
	if ( computeTimeSuccessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpSuccessors( task );
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
REACHABILITY_RESULT SingularWorker<Representation>::computeTimeSuccessors( const ReachTreeNode<Representation>& task ) {
	using Number = typename Representation::NumberType;

	Representation initialSet = task.getInitialSet();

	auto [containment, segment] = intersect( initialSet, task.getLocation()->getInvariant() );
	if ( containment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	std::tie( containment, std::ignore ) = ltiIntersectBadStates( segment, task.getLocation(), mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// compute time successor states
	// assert singular flow
	assert( task.getLocation()->getLinearFlow().getFlowMatrix().leftCols( initialSet.dimension() ) == matrix_t<Number>::Zero( initialSet.dimension() + 1, initialSet.dimension() ) );

	// construct point describing the dynamics
	std::vector<Point<Number>> dynamics;
	// The last column of the flow matrix are the constant derivatives. Only take the head to have consistent dimensions with the initial set
	dynamics.emplace_back( vector_t<Number>( task.getLocation()->getLinearFlow().getFlowMatrix().col( initialSet.dimension() ) ).head( initialSet.dimension() ) );

	Representation timeSuccessors = singularApplyBoundedTimeEvolution( segment, dynamics, carl::convert<tNumber, Number>( mSettings.localTimeHorizon ) );
	auto [invariantContainment, constrainedTimeSuccessors] = intersect( timeSuccessors, task.getLocation()->getInvariant() );
	if ( invariantContainment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( constrainedTimeSuccessors );

	std::tie( containment, segment ) = ltiIntersectBadStates( constrainedTimeSuccessors, task.getLocation(), mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
void SingularWorker<Representation>::computeJumpSuccessors( const ReachTreeNode<Representation>& task ) {
	// for each transition intersect each computed time successor set with the guard. If the intersection is non-empty, store for post-processing.

	JumpPredecessors transitionEnablingStateSets;
	for ( auto& stateSet : mFlowpipe ) {
		for ( const auto& transitionPtr : task.getLocation()->getTransitions() ) {
			auto [containment, set] = intersect( stateSet, transitionPtr->getGuard() );
			if ( containment != CONTAINMENT::NO ) {
				transitionEnablingStateSets[transitionPtr.get()] = { set };
			}
		}
	}

	// post processing: apply reset on those sets, intersect the sets with the invariant of the target location. If the resulting state set is non-empty, add it to the jump successors set.
	postProcessJumpSuccessors( transitionEnablingStateSets );
}

template <typename Representation>
void SingularWorker<Representation>::postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets ) {
	singularJumpHandler<Representation> jmpHandler;
	mJumpSuccessorSets = jmpHandler.applyJump( guardSatisfyingSets );
}

template <typename Representation>
REACHABILITY_RESULT SingularWorker<Representation>::computeBackwardReachability( const ReachTreeNode<Representation>& task ) {
	std::cout << "backward automata is " << mHybridAutomaton << std::endl;
	if ( computeTimePredecessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpPredecessors();
	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
REACHABILITY_RESULT SingularWorker<Representation>::computeTimePredecessors( const ReachTreeNode<Representation>& task ) {
	Representation badSet = task.getState();

	auto [containment, segment] = rectangularIntersectInvariant( badSet );
	if ( containment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( segment );

	std::tie( containment, segment ) = rectangularBadIntersectInitialStates( segment, mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// compute time predecessors states
	Representation timePredecessors = rectangularApplyReverseTimeEvolution( segment, badSet.getLocation()->getRectangularFlow() );
	std::cout << "time" << std::endl;
	auto [invariantContainment, constrainedTimePredecessors] = rectangularIntersectInvariant( timePredecessors );
	if ( invariantContainment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( constrainedTimePredecessors );

	std::tie( containment, segment ) = rectangularBadIntersectInitialStates( constrainedTimePredecessors, mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
void SingularWorker<Representation>::computeJumpPredecessors() {
	// for each state: find possible transitions and intersect the set with reset of the transitions
	rectangularResetHandler<Representation> resetHandler;
	for ( auto& state : mFlowpipe ) {
		std::cout << "reset check" << std::endl;
		resetHandler.rectangularIntersectReset( state, mHybridAutomaton );
	}

	// jump to source location
	reverseProcessJumpPredecessors( resetHandler.getResetSatisfyingStateSets() );
}

template <typename Representation>
void SingularWorker<Representation>::reverseProcessJumpPredecessors( const JumpSuccessors& guardSatisfyingSets ) {
	singularJumpHandler<Representation> jmpHandler;
	mJumpPredecessorSets = jmpHandler.applyReverseJump( guardSatisfyingSets, nullptr );
}

}  // namespace hypro
