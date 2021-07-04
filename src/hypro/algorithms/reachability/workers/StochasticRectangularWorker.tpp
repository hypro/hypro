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
			// std::cout << "unsafe results are: " << segment << std::endl;
		} else {
			mFlowpipe.addState( segment );
			// std::cout << "safe results are: " << segment << std::endl;
		}
	}

	if ( !timeSuccPair.empty() ) {
		StochasticTransition<Number>* tau = new StochasticTransition<Number>();
		tau->setSource( initialSet.rGetLocation() );
		tau->setTarget( initialSet.rGetLocation() );
		tau->setTransitionWeight( Number(0) );
		mJumpSuccessorSets.emplace( std::make_pair( tau, timeSuccPair ) );
	}

	// for ( const auto& fp : mFlowpipe ) {
	// 	std::cout << "after time segments are: " << fp << std::endl;
	// }
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
	auto tmpPredecessor = jmpHandler.getPrdecessor();

	for ( auto& [transitionPtr, statesVec] : jumpSuccs ) {
		std::vector<std::pair<State, REACHABILITY_RESULT>> jumpSuccPair;
		// std::cout << "transitionPtr and statesVec"<< std::endl;
		for ( auto& state : statesVec ) {
			State newState( state );
			State predecessorState;
			for (auto [post, pre]:tmpPredecessor){
				if (post == state){
					predecessorState = pre;
					break;
				}
			}
			//std::cout << "jump predccessor is: " << &state <<",  " << predecessorState.getLocation() << std::endl;
			auto results = stochasticRectangularIntersectBadStates( newState, mHybridAutomaton );
			for ( auto [containment, segment] : results ) {
				// std::cout << "evaluate results" << std::endl;
				if ( containment != CONTAINMENT::NO ) {
					jumpSuccPair.emplace_back( std::make_pair( std::move( segment ), REACHABILITY_RESULT::UNSAFE) );
					// std::cout << "unsafe successor: " << segment << std::endl;
				} else {
					jumpSuccPair.emplace_back( std::make_pair( std::move( segment ), REACHABILITY_RESULT::SAFE) );
					// std::cout << "safe successor: " << segment << std::endl;
					mFlowpipe.addState( segment );
				}

				mPredecessor.emplace_back( std::make_pair( segment, predecessorState ) );
			}
		}

		mJumpSuccessorSets.emplace( std::make_pair( transitionPtr, jumpSuccPair ) );
	}
}


template <typename State>
void StochasticRectangularWorker<State>::computeBackwardReachability( State badSet, const ReachTreeNode<State>& task, StochasticTransition<Number>* transition, Number prob, State preStateSet ) {
	// if ( computeTimePredecessors( task ) == REACHABILITY_RESULT::UNKNOWN ) {
	// 	return REACHABILITY_RESULT::UNKNOWN;
	// }
	// computeJumpPredecessors();
	// return REACHABILITY_RESULT::SAFE;
	// State badSet = task.getInitialSet();
	// auto path = task.getPath();
	State parentState = task.getParent()->getInitialSet();

	// std::cout << "bad state is: " << badSet << "transition is :" << *(transition->getSource()) << std::endl;

	// StochasticTransition<Number>* stoTransPtr( transPtr );
	State preState = reverseProcessJumpPredecessors( badSet, transition );
	if ( preStateSet != NULL ) {
		preState = preState.intersect( preStateSet );
		// std::cout<<"pre not null"<< std::endl;
	}

	// std::cout << "bad pre state is: " << preState << std::endl;
	State timePreState = computeTimePredecessors( preState ).intersect( parentState );
	// std::cout << "bad time pre state is: " << timePreState << std::endl;

	timePreState.removeRedundancy();

	Number newProb = 1;
	if ( prob != 0 ) {
		newProb = prob;
	}

	// std::cout << "calculation intervals" << std::endl;
	stochasticRectangularProbabilityHandler<State, Number> probHandler;
	probHandler.intervalCalculation( timePreState, badSet, transition );
	auto disjInterval = probHandler.getDisjInterval();
	auto disjTransitionSets = probHandler.getDisjTransitionSets();
    auto stateInterval = probHandler.getStateInterval();
	probHandler.calculateProbability( timePreState, transition, prob, mHybridAutomaton );
	newProb = probHandler.getProbability() ;
	
	//if ( transition->getTransitionWeight() != 0 ) {

		// std::vector<carl::Interval<typename State::NumberType>> intervalSet;
		// carl::Interval<typename State::NumberType> interval = transitionInterval[ transition ];
		// for ()
	//}
	mProbability = std::make_pair( timePreState, newProb );
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

template <typename State>
void StochasticRectangularWorker<State>::computeBackwardReachabilityProb( const ReachTreeNode<State>& task, Number prob ) {

	State badSet = task.getInitialSet();

	State timePreState = computeTimePredecessorsProb( task, prob );

	computeJumpPredecessorsProb();
	// std::vector<std::pair<StochasticTransition<Number>*,std::pair<State, Number>>> resultPair;

	for ( auto [transition, stateVec] : mJumpPredecessorSets ){
		for (auto preState : stateVec){
			preState.removeRedundancy();

			Number newProb = 1;
			if ( prob != 0 ) {
				newProb = prob;
			}

			// std::cout << "calculation intervals" << std::endl;
			stochasticRectangularProbabilityHandler<State, Number> probHandler;
			probHandler.intervalCalculation( preState, badSet, transition );
			// auto disjInterval = probHandler.getDisjInterval();
			// auto disjTransitionSets = probHandler.getDisjTransitionSets();
			// auto stateInterval = probHandler.getStateInterval();
			probHandler.calculateProbability( preState, transition, prob, mHybridAutomaton );
			newProb = probHandler.getProbability() ;
			if (newProb == 0){
				newProb = prob;
			}
			
			//if ( transition->getTransitionWeight() != 0 ) {

				// std::vector<carl::Interval<typename State::NumberType>> intervalSet;
				// carl::Interval<typename State::NumberType> interval = transitionInterval[ transition ];
				// for ()
			//}
			mTranStateProb.emplace_back( std::make_pair(transition,std::make_pair( preState, newProb )));
			// mJumpPreSets.emplace( std::make_pair( transition, preState ) );
		}
	}
}

template <typename State>
State StochasticRectangularWorker<State>::computeTimePredecessorsProb( const ReachTreeNode<State>& task, Number prob ) {
	State badSet = task.getInitialSet();
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


	auto results = stochasticRectangularBadIntersectInitialStates( constrainedTimePredecessors, mHybridAutomaton );
	// for(auto s : mHybridAutomaton.getProbInitialStates()){
	// 	std::cout<<"in worker initial location:" << *s.first<<std::endl;
	// }

	
	std::vector<std::pair<State, REACHABILITY_RESULT>> jumpPrePair;
	std::vector<State> stateVec;
	for ( auto [containment, segment] : results ) {
		if ( containment != CONTAINMENT::NO ) {
			jumpPrePair.emplace_back( std::make_pair( std::move( segment ), REACHABILITY_RESULT::UNSAFE) );
			// std::cout << "unsafe results are: " << segment << std::endl;
			State newState(badSet);
			newState.setSet(segment.getSet());
			stateVec.emplace_back(newState);
		} else {
			mFlowpipe.addState( segment );
			// std::cout << "safe results are: " << segment << std::endl;
		}
	}

	if ( jumpPrePair.empty() ) {
		mFlowpipe.addState( constrainedTimePredecessors );
	} else {
		StochasticTransition<Number>* tau = new StochasticTransition<Number>();
		tau->setSource( badSet.rGetLocation() );
		tau->setTarget( badSet.rGetLocation() );
		tau->setTransitionWeight( Number(0) );
		mJumpPredecessorSets.emplace(std::make_pair(tau,stateVec));
	}

	return constrainedTimePredecessors;
}

template <typename State>
void StochasticRectangularWorker<State>::computeJumpPredecessorsProb() {
	// for each state: find possible transitions and intersect the set with reset of the transitions
	StochasticRectangularResetHandler<State> resetHandler;
	for ( auto& state : mFlowpipe ) {
		resetHandler.rectangularIntersectReset( state, mHybridAutomaton );
	}

	// jump to source location
	reverseProcessJumpPredecessorsProb( resetHandler.getResetSatisfyingStateSets() );
}

template <typename State>
void StochasticRectangularWorker<State>::reverseProcessJumpPredecessorsProb( const JumpSuccessors& guardSatisfyingSets ) {
	stochasticRectangularJumpHandler<State> jmpHandler;
	for ( auto [transitionPtr, stateVec] : guardSatisfyingSets ) {
		std::vector<State> preStates;
		for ( auto state : stateVec) {
			auto result = jmpHandler.applyReverseJump( state, transitionPtr, mSettings.strategy().front() );
			preStates.emplace_back(result);
		}
		mJumpPredecessorSets.emplace(std::make_pair(transitionPtr,preStates));
	}
}

}  // namespace hypro
