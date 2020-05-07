#include "LTIWorker.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT LTIWorker<State>::computeForwardReachability( const ReachTreeNode<State>& task ) {
	if ( computeTimeSuccessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpSuccessors();
	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
REACHABILITY_RESULT LTIWorker<State>::computeTimeSuccessors( const ReachTreeNode<State>& task ) {
	ltiFirstSegmentHandler<State> firstSegmentHandler;
	State firstSegment = firstSegmentHandler( task.getState(), mSettings.strategy.front().timeStep );

	auto containmentStateSetPair = ltiIntersectInvariant( firstSegment );
	if ( containmentStateSetPair.first == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	// add state to flowpipe
	mFlowpipe.addState( containmentStateSetPair.second );

	containmentStateSetPair = ltiIntersectBadStates( containmentStateSetPair.second, mHybridAutomaton );
	if ( containmentStateSetPair.first != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// while not done
	std::size_t segmentCounter = 1;
	while ( requireTimeSuccessorComputation( segmentCounter ) ) {
		State currentSegment = ltiApplyTimeEvolution( containmentStateSetPair.second, firstSegmentHandler.getTrafo(), firstSegmentHandler.getTranslation(), mSettings.strategy.front().timeStep );
		containmentStateSetPair = ltiIntersectInvariant( currentSegment );
		if ( containmentStateSetPair.first == CONTAINMENT::NO ) {
			return REACHABILITY_RESULT::SAFE;
		}

		// add state to flowpipe
		mFlowpipe.addState( containmentStateSetPair.second );
		++segmentCounter;

		containmentStateSetPair = ltiIntersectBadStates( containmentStateSetPair.second, mHybridAutomaton );
		if ( containmentStateSetPair.first != CONTAINMENT::NO ) {
			// Todo: memorize the intersecting state set and keep state.
			return REACHABILITY_RESULT::UNKNOWN;
		}
	}
	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
void LTIWorker<State>::computeJumpSuccessors() {
	ltiGuardHandler<State> guardHandler;
	for ( auto& state : mFlowpipe ) {
		guardHandler( state );
	}

	postProcessJumpSuccessors( guardHandler.getGuardSatisfyingStateSets() );
}

template <typename State>
void LTIWorker<State>::postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets ) {
	ltiJumpHandler<State> jmpHandler;
	mJumpSuccessorSets = jmpHandler.applyJump( guardSatisfyingSets, nullptr, mSettings.strategy.front() );
}

}  // namespace hypro
