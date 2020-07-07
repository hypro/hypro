#include "RectangularWorker.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT RectangularWorker<State>::computeForwardReachability( const ReachTreeNode<State>& task ) {
	if ( computeTimeSuccessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpSuccessors();
	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
REACHABILITY_RESULT RectangularWorker<State>::computeTimeSuccessors( const ReachTreeNode<State>& task ) {
	State initialSet = task.getState();

	auto [containment, segment] = rectangularIntersectInvariant( initialSet );
	if ( containment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( segment );

	std::tie( containment, segment ) = rectangularIntersectBadStates( segment, mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// compute time successor states
	State timeSuccessors = rectangularApplyTimeEvolution( segment );
	auto [invariantContainment, timeSuccessors] = rectangularIntersectInvariant( timeSuccessors );
	if ( invariantContainment == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( segment );

	std::tie( containment, segment ) = rectangularIntersectBadStates( segment, mHybridAutomaton );
	if ( containment != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
void RectangularWorker<State>::computeJumpSuccessors() {
	std::vector<State> guardSatisfyingStateSets;
	// TODO: for each transition intersect each computed time successor set with the guard. If the intersection is non-empty, store for post-processing.

	// TODO: post processing: apply reset on those sets, intersect the sets with the invariant of the target location. If the resulting state set is non-empty, add it to the jump successors set.
}

}  // namespace hypro
