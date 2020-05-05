#include "LTIAnalyzer.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT LTIAnalyzer<State>::run() {
	// initialize reach tree
	mReachTree( new ReachTreeNode<State>() );

	// initialize queue
	for ( auto& locationConditionPair : mHybridAutomaton.getInitialStates() ) {
		// create initial state
		State initialState{locationConditionPair.first};
		initialState.setSet( State::nth_representation<0>( locationConditionPair.second.matrix(), locationConditionPair.second.vector() ) );
		initialState.setTimestamp( carl::Interval<hydra::tNumber>( 0 ) );

		// create node from state
		ReachTreeNode<State> treeNode{initialState};
		// add to reachTree
		treeNode.setParent( mReachTree.getRoot() );
		mReachTree.getRoot().addChild( treeNode );

		// add to queue
		mWorkQueue.nonLockingEnqueue( std::move( std::make_unique<Task<State>>{treeNode} ) );
	}

	while ( !mWorkQueue.nonLockingEmpty() ) {
		LTIWorker worker;
		Task currentTask{mWorkQueue.nonLockingDequeueFront()};
		REACHABILITY_RESULT safetyResult;
		if ( currentTask.treeNode.getDepth() <= mAnalysisSettings.jumpDepth ) {
			safetyResult = worker.computeForwardReachability( currentTask );
		} else {
			safetyResult = worker.computeTimeSuccessors( currentTask );
		}

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return safetyResult;
		}

		// only for plotting
		mFlowpipes.emplace_back( worker.getFlowpipe() );

		// create jump successor tasks
		for ( const auto& transitionStatesPair : worker.getJumpSuccessorSets() ) {
			for ( const auto jmpSucc : transitionStatesPair.second ) {
				// update reachTree
				ReachTreeNode<State> treeNode{jmpSucc};
				treeNode.setParent( currentTask.treeNode );
				currentTask.treeNode.addChild( treeNode );

				// update path (global time)
				currentTask.treeNode.addTimeStepToPath( carl::Interval<tNumber>( worker.getFlowpipe().front().getTimestamp().lower(), jmpSucc.getTimestamp().upper() ) );
				treeNode.addTransitionToPath( transitionStatesPair.first, jmpSucc.getTimestamp() );

				// create Task
				mWorkingQueue.nonLockingEnqueue( std::move( std::make_unique<Task<State>>{treeNode} ) );
			}
		}
	}
	return REACHABILITY_RESULT::SAFE;
}

}  // namespace hypro
