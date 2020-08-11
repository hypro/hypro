#include "RectangularAnalyzer.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT RectangularAnalyzer<State>::run() {

	REACHABILITY_RESULT safetyResult;
	if (mAnalysisSettings.strategy.front().reachability_analysis_method == REACH_SETTING::FORWARD ) {
		// forward analysis
		safetyResult = forwardRun();
	} else {
		// backward analysis
		safetyResult = backwardRun();
	}

	return safetyResult;
}

template <typename State>
REACHABILITY_RESULT RectangularAnalyzer<State>::forwardRun() {
	// initialize queue
	for ( auto& [location, condition] : mHybridAutomaton.getInitialStates() ) {
		// create initial state
		State initialState{ location };
		initialState.setSet( typename State::template nth_representation<0>{ condition.getMatrix(), condition.getVector() } );
		initialState.setTimestamp( carl::Interval<tNumber>( 0 ) );

		// create node from state
		auto initialNode{ std::make_unique<ReachTreeNode<State>>( initialState ) };
		// add to reachTree
		mReachTree.emplace_back( std::move( initialNode ) );
		// add to queue
		mWorkQueue.push( mReachTree.back().get() );
	}

	while ( !mWorkQueue.empty() ) {
		RectangularWorker<State> worker{ mHybridAutomaton, mAnalysisSettings };
		ReachTreeNode<State>* currentNode = mWorkQueue.front();
		mWorkQueue.pop();
		REACHABILITY_RESULT safetyResult;

		if ( currentNode->getDepth() < mAnalysisSettings.jumpDepth ) {
			safetyResult = worker.computeForwardReachability( *currentNode );
		} else {
			safetyResult = worker.computeTimeSuccessors( *currentNode );
		}

		// only for plotting
		mFlowpipes.emplace_back( worker.getFlowpipe() );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return safetyResult;
		}

		// create jump successor tasks
		for ( const auto& transitionStatesPair : worker.getJumpSuccessorSets() ) {
			for ( const auto jmpSucc : transitionStatesPair.second ) {
				// update reachTree
				auto* childNode = new ReachTreeNode<State>{ jmpSucc };
				childNode->setParent( currentNode );
				currentNode->addChild( childNode );

				// update path (global time)
				childNode->addTimeStepToPath( carl::Interval<tNumber>( worker.getFlowpipe().begin()->getTimestamp().lower(), jmpSucc.getTimestamp().upper() ) );
				childNode->addTransitionToPath( transitionStatesPair.first, jmpSucc.getTimestamp() );

				// create Task
				mWorkQueue.push( childNode );
			}
		}
	}

	return REACHABILITY_RESULT::SAFE;
}

template <typename State>
REACHABILITY_RESULT RectangularAnalyzer<State>::backwardRun() {
	// initialize queue
	for ( auto& [location, condition] : mHybridAutomaton.getLocalBadStates() ) {
		// create local bad state
		State badState{ location };
		badState.setSet( typename State::template nth_representation<0>{ condition.getMatrix(), condition.getVector() } );
		badState.setTimestamp( carl::Interval<tNumber>( 0 ) );

		// create node from state
		auto badNode{ std::make_unique<ReachTreeNode<State>>( badState ) };
		// add to reachTree
		mReachTree.emplace_back( std::move( badNode ) );
		// add to queue
		mWorkQueue.push( mReachTree.back().get() );
	}

	for ( auto& condition : mHybridAutomaton.getGlobalBadStates() ) {
		if ( condition.getMatrix().rows() != 0 ) {
			for ( auto& location : mHybridAutomaton.getLocations() ) {
				// create global bad state
				State badState{ location };
				badState.setSet( typename State::template nth_representation<0>{ condition.getMatrix(), condition.getVector() } );
				badState.setTimestamp( carl::Interval<tNumber>( 0 ) );

				// create node from state
				auto badNode{ std::make_unique<ReachTreeNode<State>>( badState ) };
				// add to reachTree
				mReachTree.emplace_back( std::move( badNode ) );
				// add to queue
				mWorkQueue.push( mReachTree.back().get() );
			}
		}
	}
	
	while ( !mWorkQueue.empty() ) {
		RectangularWorker<State> worker{ mHybridAutomaton, mAnalysisSettings };
		ReachTreeNode<State>* currentNode = mWorkQueue.front();
		mWorkQueue.pop();
		REACHABILITY_RESULT safetyResult;

		if ( currentNode->getDepth() < mAnalysisSettings.jumpDepth ) {
			safetyResult = worker.computeBackwardReachability( *currentNode );
		} else {
			safetyResult = worker.computeTimePredecessors( *currentNode );
		}

		// only for plotting
		mFlowpipes.emplace_back( worker.getFlowpipe() );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return safetyResult;
		}

		// create jump predecessors tasks
		for ( const auto& transitionStatesPair : worker.getJumpPredecessorSets() ) {
			for ( const auto jmpPre : transitionStatesPair.second ) {
				// update reachTree
				auto* parentNode = new ReachTreeNode<State>{ jmpPre };
				parentNode->addChild( currentNode );
				currentNode->setParent( parentNode );

				// update path (global time)
				currentNode->addTimeStepToPath( carl::Interval<tNumber>( jmpPre.getTimestamp().lower(), worker.getFlowpipe().begin()->getTimestamp().upper() ) );
				currentNode->addTransitionToPath( transitionStatesPair.first, worker.getFlowpipe().begin()->getTimestamp() );

				// create Task
				mWorkQueue.push( parentNode );
			}
		}
	}

	return REACHABILITY_RESULT::SAFE;
}

}  // namespace hypro
