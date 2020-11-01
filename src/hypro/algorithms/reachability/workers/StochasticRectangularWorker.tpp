#include "StochasticRectangularWorker.h"

namespace hypro {

template <typename State>
void StochasticRectangularWorker<State>::computeForwardReachability( const ReachTreeNode<State>& task ) {
	computeTimeSuccessors( task );
	computeJumpSuccessors();
}

template <typename State>
void StochasticRectangularWorker<State>::computeTimeSuccessors( const ReachTreeNode<State>& task ) {
	State initialSet = task.getInitialSet();

	// compute time successor states
	State timeSuccessors = rectangularApplyTimeEvolution( initialSet, initialSet.getLocation()->getRectangularFlow() );
	auto [invariantContainment, constrainedTimeSuccessors] = rectangularIntersectInvariant( timeSuccessors );

	auto results = stochasticRectangularIntersectBadStates( constrainedTimeSuccessors, mHybridAutomaton );
	std::vector<std::pair<State, REACHABILITY_RESULT>> timeSuccPair;
	for ( auto [containment, segment] : results ) {
		if ( containment != CONTAINMENT::NO ) {
			timeSuccPair.emplace_back( std::make_pair( std::move( segment ), REACHABILITY_RESULT::UNSAFE) );
		} else {
			mFlowpipe.addState( segment );
		}
	}

	if ( !timeSuccPair.empty() ) {
		StochasticTransition<Number>* tau = new StochasticTransition<Number>();
		tau->setSource( initialSet.rGetLocation() );
		tau->setTarget( initialSet.rGetLocation() );
		tau->setTransitionWeight( Number(0) );
		mJumpSuccessorSets.emplace( std::make_pair( tau, timeSuccPair ) );
	}
}

template <typename State>
void StochasticRectangularWorker<State>::computeJumpSuccessors() {
	// for each transition intersect each computed time successor set with the guard. If the intersection is non-empty, store for post-processing.
	stochasticRectangularGuardHandler<State> guardHandler;
	for ( auto& state : mFlowpipe ) {
		guardHandler( state );
	}

	// post processing: apply reset on those sets, intersect the sets with the invariant of the target location. If the resulting state set is non-empty, add it to the jump successors set.
	postProcessJumpSuccessors( guardHandler.getGuardSatisfyingStateSets() );
}

template <typename State>
void StochasticRectangularWorker<State>::postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets ) {
	stochasticRectangularJumpHandler<State> jmpHandler;
	auto jumpSuccs = jmpHandler.applyJump( guardSatisfyingSets, nullptr, mSettings.strategy().front() );

	for ( auto& [transitionPtr, statesVec] : jumpSuccs ) {
		std::vector<std::pair<State, REACHABILITY_RESULT>> jumpSuccPair;
		for ( auto& state : statesVec ) {
			State newState( state );
			auto results = stochasticRectangularIntersectBadStates( newState, mHybridAutomaton );
			for ( auto [containment, segment] : results ) {
				if ( containment != CONTAINMENT::NO ) {
					jumpSuccPair.emplace_back( std::make_pair( std::move( segment ), REACHABILITY_RESULT::UNSAFE) );
				} else {
					jumpSuccPair.emplace_back( std::make_pair( std::move( segment ), REACHABILITY_RESULT::SAFE) );
					mFlowpipe.addState( segment );
				}
			}
		}

		mJumpSuccessorSets.emplace( std::make_pair( transitionPtr, jumpSuccPair ) );
	}
}


template <typename State>
void StochasticRectangularWorker<State>::computeBackwardReachability( const ReachTreeNode<State>& task, StochasticTransition<Number>* transition, Number prob ) {
	// if ( computeTimePredecessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
	// 	return REACHABILITY_RESULT::UNKNOWN;
	// }
	// computeJumpPredecessors();
	// return REACHABILITY_RESULT::SAFE;
	State badSet = task.getInitialSet();
	auto path = task.getPath();
	State parentState = task.getParent()->getInitialSet();

	// StochasticTransition<Number>* stoTransPtr( transPtr );
	State preState = reverseProcessJumpPredecessors( badSet, transition );
	State timePreState = computeTimePredecessors( preState ).intersect( parentState );

	timePreState.removeRedundancy();

	Number newProb = 1;

	if ( transition->getTransitionWeight() != 0 ) {
		stochasticRectangularProbabilityHandler<State, Number> probHandler;
		probHandler.intervalCalculation( timePreState, badSet, transition );
		auto enabledTransitions = probHandler.getEnabledTransitions();

		for ( auto pair : enabledTransitions ) {
			std::cout << "interval is: " << pair.first << std::endl;
			for ( auto ptr : pair.second ) {
				std::cout << "stoTransition is: " << *ptr << std::endl;
			}
		}

		// std::vector<carl::Interval<typename State::NumberType>> intervalSet;
		// carl::Interval<typename State::NumberType> interval = transitionInterval[ transition ];
		// for ()
	}
	// return std::make_pair( timePreState, newProb );
}

template <typename State>
State StochasticRectangularWorker<State>::computeTimePredecessors( const State& badSet ) {
	auto [containment, segment] = rectangularIntersectInvariant( badSet );
	if ( containment == CONTAINMENT::NO ) {
		return State();
	}

	// add state to flowpipe
	mFlowpipe.addState( segment );

	// compute time predecessors states
	State timePredecessors = rectangularApplyReverseTimeEvolution( segment, badSet.getLocation()->getRectangularFlow() );
	auto [invariantContainment, constrainedTimePredecessors] = rectangularIntersectInvariant( timePredecessors );
	if ( invariantContainment == CONTAINMENT::NO ) {
		return State();
	}

	// add state to flowpipe
	mFlowpipe.addState( constrainedTimePredecessors );

	return constrainedTimePredecessors;
}

template <typename State>
State StochasticRectangularWorker<State>::reverseProcessJumpPredecessors( State& state, StochasticTransition<Number>* transitionPtr ) {
	stochasticRectangularJumpHandler<State> jmpHandler;
	return jmpHandler.applyReverseJump( state, transitionPtr, mSettings.strategy().front() );
}

// void StochasticRectangularWorker<State>::intervalCalculation(State& preState, State& state, StochasticTransition<Number>* transitionPtr ) {

// }

}  // namespace hypro
