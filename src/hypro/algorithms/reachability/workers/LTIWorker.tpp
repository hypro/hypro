#include "LTIWorker.h"

namespace hypro {

template <typename State>
void LTIWorker<State>::processTask( const TaskType& t ) {
	computeForwardReachability( t );
}

template <typename State>
void LTIWorker<State>::computeForwardReachability( const TaskType& task ) {
	//std::cout << "context.execOnStart()" << std::endl;

	//START_BENCHMARK_OPERATION(FIRST_SEGMENT);
	// compute first segment
	// context.execBeforeFirstSegment();
	// context.firstSegment();
	// context.execAfterFirstSegment();
	ltiFirstSegmentHandler firstSegmentHandler;
	State firstSegment = firstSegmentHandler( task->getInitialStateSet(), SettingsProvider::getInstance().getStrategy().getParameters().timeStep );
	//EVALUATE_BENCHMARK_RESULT(FIRST_SEGMENT);

	//START_BENCHMARK_OPERATION(CHECK_INVARIANT);
	// intersect with invariant
	// context.execBeforeCheckInvariant();
	// context.checkInvariant();
	// context.execAfterCheckInvariant();
	auto containmentStateSetPair = ltiIntersectInvariant( firstSegment );
	if ( containmentStateSetPair.first == CONTAINMENT::NO ) {
		return;
	}
	//EVALUATE_BENCHMARK_RESULT(CHECK_INVARIANT);

	//START_BENCHMARK_OPERATION(INTERSECT_BAD_STATES);
	// intersect with bad states
	// context.execBeforeIntersectBadStates();
	// context.intersectBadStates();
	// context.execAfterIntersectBadStates();
	containmentStateSetPair = ltiIntersectBadStates( containmentStateSetPair.second );
	if ( containmentStateSetPair.first != CONTAINMENT::NO ) {
		// Todo: memorize the intersecting state set and keep state.
		return;
	}
	//EVALUATE_BENCHMARK_RESULT(INTERSECT_BAD_STATES);

	//context.execBeforeLoop();

	// set up guard handler
	ltiGuardHandler guardHander;

	// while not done
	std::size_t segmentCounter = 1;
	while ( requireTimeSuccessorComputation( segmentCounter ) ) {
		//START_BENCHMARK_OPERATION(COMPUTE_TIMESTEP);
		//context.execOnLoopItEnter();

		//START_BENCHMARK_OPERATION(CHECK_TRANSITION);
		// intersect with transition guards
		// context.execBeforeCheckTransition();
		// context.checkTransition();
		// context.execAfterCheckTransition();
		guardHandler( containmentStateSetPair.second );
		//EVALUATE_BENCHMARK_RESULT(CHECK_TRANSITION);

		//START_BENCHMARK_OPERATION(CONTINUOUS_EVOLUTION);
		// apply continuous time step
		// context.execBeforeContinuousEvolution();
		// context.applyContinuousEvolution();
		// context.execAfterContinuousEvolution();
		State currentSegment = ltiApplyTimeEvolution( containmentStateSetPair.second, firstSegmentHandler.getTransformation(), firstSegmentHandler.getTranslation(), SettingsProvider::getInstance().getTimeStepSize() );
		//EVALUATE_BENCHMARK_RESULT(CONTINUOUS_EVOLUTION);

		//START_BENCHMARK_OPERATION(CHECK_INVARIANT);
		// intersect with invariant
		// context.execBeforeCheckInvariant();
		// context.checkInvariant();
		// context.execAfterCheckInvariant();
		auto containmentStateSetPair = ltiIntersectInvariant( currentSegment );
		if ( containmentStateSetPair.first == CONTAINMENT::NO ) {
			return;
		}
		//EVALUATE_BENCHMARK_RESULT(CHECK_INVARIANT);

		++segmentCounter;

		//START_BENCHMARK_OPERATION(INTERSECT_BAD_STATES);
		// intersect with bad states
		// context.execBeforeIntersectBadStates();
		// context.intersectBadStates();
		// context.execAfterIntersectBadStates();
		containmentStateSetPair = ltiIntersectBadStates( containmentStateSetPair.second );
		if ( containmentStateSetPair.first != CONTAINMENT::NO ) {
			// Todo: memorize the intersecting state set and keep state.
			return;
		}
		//EVALUATE_BENCHMARK_RESULT(INTERSECT_BAD_STATES);

		// context.execOnLoopItExit();
		//EVALUATE_BENCHMARK_RESULT(COMPUTE_TIMESTEP);
	}

	// context.execAfterLoop();

	//START_BENCHMARK_OPERATION(DISCRETE_SUCCESSORS);
	// create discrete successor states
	// context.execBeforeProcessDiscreteBehavior();
	// context.processDiscreteBehavior();
	//context.execBeforeProcessDiscreteBehavior();

	void postProcessJumpSuccessors( guardHandler.getGuardSatisfyingStateSets() );

	//EVALUATE_BENCHMARK_RESULT(DISCRETE_SUCCESSORS);
}

void LTIWorker<State>::postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets ) {
	ltiJumpHandler jmpHandler;
	mJumpSuccessorSets = jmpHandler.applyJump( guardSatisfyingSets, nullptr, SettingsProvider.getStrategy().getParameters( 0 ) );
}

}  // namespace hypro
