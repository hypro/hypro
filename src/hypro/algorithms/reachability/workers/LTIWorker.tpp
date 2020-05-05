#include "LTIWorker.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT LTIWorker<State>::computeForwardReachability( const TaskType& task ) {
	if ( computeTimeSuccessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
		return REACHABILITY_RESULT::UNKNOWN;
	}
	computeJumpSuccessors();
}

template <typename State>
REACHABILITY_RESULT LTIWorker<State>::computeTimeSuccessors( const TaskType& task ) {
	ltiFirstSegmentHandler<State> firstSegmentHandler;
	State firstSegment = firstSegmentHandler( task->getInitialStateSet(), SettingsProvider<State>::getInstance().getStrategy().getParameters().timeStep );

	auto containmentStateSetPair = ltiIntersectInvariant( firstSegment );
	if ( containmentStateSetPair.first == CONTAINMENT::NO ) {
		return REACHABILITY_RESULT::SAFE;
	}

	containmentStateSetPair = ltiIntersectBadStates( containmentStateSetPair.second );
	if ( containmentStateSetPair.first != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return REACHABILITY_RESULT::UNKNOWN;
	}

	// while not done
	std::size_t segmentCounter = 1;
	while ( requireTimeSuccessorComputation( segmentCounter ) ) {
		State currentSegment = ltiApplyTimeEvolution( containmentStateSetPair.second, firstSegmentHandler.getTransformation(), firstSegmentHandler.getTranslation(), SettingsProvider<State>::getInstance().getTimeStepSize() );
		auto containmentStateSetPair = ltiIntersectInvariant( currentSegment );
		if ( containmentStateSetPair.first == CONTAINMENT::NO ) {
			return REACHABILITY_RESULT::SAFE;
		}

		++segmentCounter;

		containmentStateSetPair = ltiIntersectBadStates( containmentStateSetPair.second );
		if ( containmentStateSetPair.first != CONTAINMENT::NO ) {
			// Todo: memorize the intersecting state set and keep state.
			return REACHABILITY_RESULT::UNKNOWN;
		}
	}
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
	mJumpSuccessorSets = jmpHandler.applyJump( guardSatisfyingSets, nullptr, SettingsProvider<State>::getInstance().getStrategy().getParameters( 0 ) );
}

}  // namespace hypro
