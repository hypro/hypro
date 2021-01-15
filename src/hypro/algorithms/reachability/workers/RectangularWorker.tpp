#include "RectangularWorker.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT RectangularWorker<State>::computeForwardReachability( const ReachTreeNode<State>& task ) {
	if ( computeTimeSuccessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpSuccessors( task.getLocation() );
	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
REACHABILITY_RESULT RectangularWorker<State>::computeTimeSuccessors( const ReachTreeNode<State>& task ) {
	State initialSet = task.getInitialSet();
	DEBUG( "hypro.reachability.rectangular", "Compute time successors for initial set " << initialSet << " in location " << *task.getLocation() );

	auto [containment, segment] = rectangularIntersectInvariant( initialSet, task.getLocation() );
	if ( containment == CONTAINMENT::NO ) {
		DEBUG( "hypro.reachability.rectangular", "Initial set not contained in the invariant" );
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( segment );

	std::tie( containment, segment ) = rectangularIntersectBadStates( segment, task.getLocation(), mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		DEBUG( "hypro.reachability.rectangular", "Initial set intersects bad states, abort" );
		// add state to flowpipe
		mFlowpipe.addState( segment );
		task.getFlowpipe().push_back( segment );
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// compute time successor states
	State timeSuccessors = rectangularApplyTimeEvolution( segment, task.getLocation()->getRectangularFlow() );
	auto [invariantContainment, constrainedTimeSuccessors] = rectangularIntersectInvariant( timeSuccessors, task.getLocation() );
	TRACE( "hypro.reachability.rectangular", "Time successors constrained by invariants: " << constrainedTimeSuccessors );
	if ( invariantContainment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( constrainedTimeSuccessors );

	std::tie( containment, segment ) = rectangularIntersectBadStates( constrainedTimeSuccessors, task.getLocation(), mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		DEBUG( "hypro.reachability.rectangular", "Time successors intersect bad states, abort" );
		return REACHABILITY_RESULT::UNKNOWN;
	}

	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
void RectangularWorker<State>::computeJumpSuccessors( const Location<Number>* location ) {
	// for each transition intersect each computed time successor set with the guard. If the intersection is non-empty, store for post-processing.
	rectangularGuardHandler<State> guardHandler;
	for ( auto& state : mFlowpipe ) {
		guardHandler( state, location );
	}

	// post processing: apply reset on those sets, intersect the sets with the invariant of the target location. If the resulting state set is non-empty, add it to the jump successors set.
	postProcessJumpSuccessors( guardHandler.getGuardSatisfyingStateSets() );
}

template <typename State>
void RectangularWorker<State>::postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets ) {
	singularJumpHandler<State> jmpHandler;
	mJumpSuccessorSets = jmpHandler.applyJump( guardSatisfyingSets );
}

template <typename State>
REACHABILITY_RESULT RectangularWorker<State>::computeBackwardReachability( const ReachTreeNode<State>& task ) {
	std::cout << "backward automata is " << mHybridAutomaton << std::endl;
	if ( computeTimePredecessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpPredecessors();
	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
REACHABILITY_RESULT RectangularWorker<State>::computeTimePredecessors( const ReachTreeNode<State>& task ) {
	State badSet = task.getInitialSet();

	auto [containment, segment] = rectangularIntersectInvariant( badSet, task.getLocation() );
	if ( containment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( segment );

	std::tie( containment, segment ) = rectangularBadIntersectInitialStates( segment, task.getLocation(), mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// compute time predecessors states
	State timePredecessors = rectangularApplyReverseTimeEvolution( segment, task.getLocation()->getRectangularFlow() );
	std::cout << "time" << std::endl;
	auto [invariantContainment, constrainedTimePredecessors] = rectangularIntersectInvariant( timePredecessors, task.getLocation() );
	if ( invariantContainment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( constrainedTimePredecessors );

	std::tie( containment, segment ) = rectangularBadIntersectInitialStates( constrainedTimePredecessors, task.getLocation(), mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
void RectangularWorker<State>::computeJumpPredecessors() {
	// for each state: find possible transitions and intersect the set with reset of the transitions
	rectangularResetHandler<State> resetHandler;
	for ( auto& state : mFlowpipe ) {
		std::cout << "reset check" << std::endl;
		resetHandler.rectangularIntersectReset( state, mHybridAutomaton );
	}

	// jump to source location
	reverseProcessJumpPredecessors( resetHandler.getResetSatisfyingStateSets() );
}

template <typename State>
void RectangularWorker<State>::reverseProcessJumpPredecessors( const JumpSuccessors& guardSatisfyingSets ) {
	rectangularJumpHandler<State> jmpHandler;
	mJumpPredecessorSets = jmpHandler.applyReverseJump( guardSatisfyingSets, nullptr, mSettings.strategy().front() );
}
}  // namespace hypro
