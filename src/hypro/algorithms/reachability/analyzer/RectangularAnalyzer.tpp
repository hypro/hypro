#include "RectangularAnalyzer.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT RectangularAnalyzer<State>::run() {
	// initialize queue
	for ( auto& [location, condition] : mHybridAutomaton.getInitialStates() ) {
		// create initial state
		State initialState{ location };
		initialState.setSet( typename State::template nth_representation<0>{ condition.getMatrix(), condition.getVector() } );
		initialState.setTimestamp( carl::Interval<tNumber>( 0 ) );

		// create node from state
		auto initialNode{ std::make_unique<ReachTreeNode<State>>( initialState ) };
		// add to reachTree
		initialNode->setParent( nullptr );
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

}  // namespace hypro
