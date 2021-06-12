#include "RectangularWorker.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT RectangularWorker<State>::computeForwardReachability( ReachTreeNode<State>& task ) {
	DEBUG( "hypro.reachability.rectangular", "Start forward computation in worker" );
	if ( computeTimeSuccessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpSuccessors( task.getLocation() );
	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
REACHABILITY_RESULT RectangularWorker<State>::computeTimeSuccessors( ReachTreeNode<State>& task ) {
	State initialSet = task.getInitialSet();

	auto [containment, segment] = rectangularIntersectInvariant( initialSet, task.getLocation() );
	if ( containment == CONTAINMENT::NO ) {
		DEBUG( "hypro.reachability.rectangular", "Initial set not contained in the invariant" );
		return REACHABILITY_RESULT::SAFE;
	}

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
	State timeSuccessors{ segment };
	if ( mSettings.fixedParameters().localTimeHorizon < 0 ) {
		timeSuccessors = std::move( rectangularApplyTimeEvolution( segment, task.getLocation()->getRectangularFlow() ) );
	} else {
		timeSuccessors = std::move( rectangularApplyBoundedTimeEvolution( segment, task.getLocation()->getRectangularFlow(), mSettings.fixedParameters().localTimeHorizon ) );
	}

	TRACE( "hypro.reachability.rectangular", "Time successors: " << timeSuccessors );
	auto [invariantContainment, constrainedTimeSuccessors] = rectangularIntersectInvariant( timeSuccessors, task.getLocation() );
	TRACE( "hypro.reachability.rectangular", "Time successors constrained by invariants: " << constrainedTimeSuccessors );
	if ( invariantContainment == CONTAINMENT::NO ) {
		DEBUG( "hypro.reachability.rectangular", "Time successors are not contained in the invariant, return SAFE (This should never happen)" );
		assert( false && "It cannot happen that time successors, which include the initial set completely invalidate the invariant region, if the initial set is at least partially contained in the invariant region." );
		// add state to flowpipe
		mFlowpipe.addState( constrainedTimeSuccessors );
		task.getFlowpipe().push_back( constrainedTimeSuccessors );
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( constrainedTimeSuccessors );
	task.getFlowpipe().push_back( constrainedTimeSuccessors );

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
REACHABILITY_RESULT RectangularWorker<State>::computeBackwardReachability( ReachTreeNode<State>& task ) {
	if ( computeTimePredecessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpPredecessors();
	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
REACHABILITY_RESULT RectangularWorker<State>::computeTimePredecessors( ReachTreeNode<State>& task ) {
	State badSet = task.getInitialSet();
	auto [containment, segment] = rectangularIntersectInvariant( badSet, task.getLocation() );
	if ( containment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	std::tie( containment, segment ) = rectangularBadIntersectInitialStates( segment, task.getLocation(), mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		mFlowpipe.addState( segment );
		task.getFlowpipe().push_back( segment );
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// compute time predecessors states
	State timePredecessors = rectangularApplyReverseTimeEvolution( segment, task.getLocation()->getRectangularFlow() );
	auto [invariantContainment, constrainedTimePredecessors] = rectangularIntersectInvariant( timePredecessors, task.getLocation() );
	if ( invariantContainment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( constrainedTimePredecessors );
	task.getFlowpipe().push_back( constrainedTimePredecessors );

	std::tie( containment, segment ) = rectangularBadIntersectInitialStates( constrainedTimePredecessors, task.getLocation(), mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		mFlowpipe.addState( segment );
		task.getFlowpipe().push_back( segment );
		return REACHABILITY_RESULT::UNKNOWN;
	}

	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
void RectangularWorker<State>::computeJumpPredecessors() {
	// for each state: find possible transitions and intersect the set with reset of the transitions
	rectangularResetHandler<State> resetHandler;
	for ( auto& state : mFlowpipe ) {
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

template <typename State>
void RectangularWorker<State>::clear() {
	mFlowpipe.clear();
	mJumpPredecessorSets.clear();
	mJumpSuccessorSets.clear();
}
}  // namespace hypro
