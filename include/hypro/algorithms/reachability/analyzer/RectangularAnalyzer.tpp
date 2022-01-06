#include "RectangularAnalyzer.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT RectangularAnalyzer<State>::run() {
	REACHABILITY_RESULT safetyResult;
	if ( mAnalysisSettings.strategy().front().reachability_analysis_method == REACH_SETTING::FORWARD ) {
		// forward analysis
		safetyResult = forwardRun();
	}
	// else {
	//	// backward analysis
	//	safetyResult = backwardRun();
	//}

	return safetyResult;
}

template <typename State>
REACHABILITY_RESULT RectangularAnalyzer<State>::forwardRun() {
	DEBUG( "hypro.reachability.rectangular", "Start forward analysis" );
	// create reachTree if not already present
	if ( mReachTree.empty() ) {
		mReachTree = makeRoots<State>( mHybridAutomaton );
	}

	// initialize queue
	for ( auto& rtNode : mReachTree ) {
		mWorkQueue.push( &rtNode );
	}
	DEBUG( "hypro.reachability.rectangular", "Added " << mWorkQueue.size() << " initial states to the work queue" );

	RectangularWorker<State> worker{ mHybridAutomaton, mAnalysisSettings };
	while ( !mWorkQueue.empty() ) {
		ReachTreeNode<State>* currentNode = mWorkQueue.front();
		mWorkQueue.pop();
		REACHABILITY_RESULT safetyResult;
		TRACE( "hypro.reachability.rectangular", "Analyze node at depth " << currentNode->getDepth() );

		// reset worker state
		worker.clear();
		// in case the jump depth is reached, only compute time successors
		if ( currentNode->getDepth() < mAnalysisSettings.fixedParameters().jumpDepth ) {
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
				// time is not considered in rectangular analysis so we store a dummy
				auto& childNode = currentNode->addChild( jmpSucc, carl::Interval<SegmentInd>( 0, 0 ), transitionStatesPair.first );
				assert( childNode.getDepth() == currentNode->getDepth() + 1 );

				// create Task
				mWorkQueue.push( &childNode );
			}
		}
	}

	return REACHABILITY_RESULT::SAFE;
}

/*
template <typename State>
REACHABILITY_RESULT RectangularAnalyzer<State>::backwardRun() {
	// initialize queue
	for ( auto& [location, condition] : mHybridAutomaton.getLocalBadStates() ) {
		// create local bad state
		State badState{ condition.getMatrix(), condition.getVector() };

		// create node from state
		auto badNode{ ReachTreeNode<State>( location, badState, carl::Interval<SegmentInd>( 0 ) ) };
		// add to reachTree
		mReachTree.emplace_back( std::move( badNode ) );
		// add to queue
		mWorkQueue.push( &mReachTree.back() );
	}

	for ( auto& condition : mHybridAutomaton.getGlobalBadStates() ) {
		if ( condition.getMatrix().rows() != 0 ) {
			for ( auto& location : mHybridAutomaton.getLocations() ) {
				// create global bad state
				State badState{ condition.getMatrix(), condition.getVector() };

				// create node from state
				auto badNode{ ReachTreeNode<State>( location, badState, carl::Interval<SegmentInd>( 0 ) ) };
				// add to reachTree
				mReachTree.emplace_back( std::move( badNode ) );
				// add to queue
				mWorkQueue.push( &mReachTree.back() );
			}
		}
	}

	while ( !mWorkQueue.empty() ) {
		RectangularWorker<State> worker{ mHybridAutomaton, mAnalysisSettings };
		ReachTreeNode<State>* currentNode = mWorkQueue.front();
		mWorkQueue.pop();
		REACHABILITY_RESULT safetyResult;

		if ( currentNode->getDepth() < mAnalysisSettings.fixedParameters().jumpDepth ) {
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

				//	auto* parentNode = new ReachTreeNode<State>{ jmpPre };
				//	parentNode->addChild( currentNode );
				//	currentNode->setParent( parentNode );
				//
				//	// update path (global time)
				//	currentNode->addTimeStepToPath( carl::Interval<tNumber>( jmpPre.getTimestamp().lower(), worker.//getFlowpipe().begin()->getTimestamp().upper() ) );
				//	currentNode->addTransitionToPath( transitionStatesPair.first, worker.getFlowpipe().begin()->getTimestamp//() );

				// Stefan: We have changed the code such that the tree grows from the bad states down instead of growing at the root upwards.
				auto& childNode = currentNode->addChild( jmpPre, carl::Interval<SegmentInd>( 0 ), transitionStatesPair.first );

				// create Task
				mWorkQueue.push( &childNode );
			}
		}
	}

	return REACHABILITY_RESULT::SAFE;
}
*/

}  // namespace hypro
