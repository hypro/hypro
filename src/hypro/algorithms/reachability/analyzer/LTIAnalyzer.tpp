#include "LTIAnalyzer.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT LTIAnalyzer<State>::run() {
	// initialize queue
	for ( auto& [location, condition] : mHybridAutomaton.getInitialStates() ) {
		// create initial state
		State initialSet{ condition.getMatrix(), condition.getVector() };

		ReachTreeNode<State>& initialNode = mReachTree.addChild( &mReachTree, location, &mFlowpipes.emplace_back(), initialSet );

		// add to queue
		mWorkQueue.push( &initialNode );
	}

	//Setup settings for flowpipe construction in worker
	TimeTransformationCache<Number> transformationCache;
	LTIWorker<State> worker{
		  mHybridAutomaton,
		  mAnalysisSettings.strategy.front(),
		  mAnalysisSettings.localTimeHorizon,
		  transformationCache };

	while ( !mWorkQueue.empty() ) {
		ReachTreeNode<State>* currentNode = mWorkQueue.front();
		mWorkQueue.pop();
		REACHABILITY_RESULT safetyResult;

		auto& newPipe = mFlowpipes.emplace_back();
		safetyResult = worker.computeTimeSuccessors( currentNode->getInitialSet(), currentNode->getLocation(), std::back_inserter( newPipe ) );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) return safetyResult;

		//Take dummy root into account
		size_t performedJumps = currentNode->getDepth() - 1;
		//Do not perform discrete jump if jump depth was reached
		if ( performedJumps == mAnalysisSettings.jumpDepth ) return REACHABILITY_RESULT::SAFE;

		// create jump successor tasks
		for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( newPipe, currentNode->getLocation() ) ) {
			for ( const auto [valuationSet, duration] : timedValuationSets ) {
				// update reachTree
				ReachTreeNode<State>& childNode = currentNode->addChild( currentNode, transition->getTarget(), &mFlowpipes.emplace_back(), valuationSet );

				// update path (global time) TODO

				// create Task
				mWorkQueue.push( &childNode );
			}
		}
	}

	return REACHABILITY_RESULT::SAFE;
}

}  // namespace hypro
