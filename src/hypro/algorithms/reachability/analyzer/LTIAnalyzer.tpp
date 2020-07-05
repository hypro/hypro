#include "LTIAnalyzer.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT LTIAnalyzer<State>::run() {
	// initialize queue
	for ( auto& [location, condition] : mHybridAutomaton.getInitialStates() ) {
		// create initial state
		State initialSet{ condition.getMatrix(), condition.getVector() };

		auto& initialNode = mRoots.emplace_back(location, &mFlowpipes.emplace_back(), initialSet, carl::Interval{0,0});

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

		safetyResult = worker.computeTimeSuccessors( currentNode->getInitialSet(), currentNode->getLocation(), std::back_inserter( *currentNode->getFlowpipe() ) );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) return safetyResult;

		//Do not perform discrete jump if jump depth was reached
		if ( currentNode->getDepth() == mAnalysisSettings.jumpDepth ) continue;

		// create jump successor tasks
		for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( *currentNode->getFlowpipe(), currentNode->getLocation() ) ) {
			for ( const auto [valuationSet, localDuration] : timedValuationSets ) {
				// update reachTree

				// convert local time to global time
				//TODO currently assuming time step is scaled to 1
				carl::Interval<SegmentInd> const& initialSetDuration = currentNode->getTimings();
				carl::Interval<SegmentInd> globalDuration = carl::Interval( initialSetDuration.lower() + localDuration.lower(), initialSetDuration.upper() + 1 + localDuration.upper() );

				ReachTreeNode<State>& childNode = currentNode->addChild(&mFlowpipes.emplace_back(), valuationSet, globalDuration, transition);

				// create Task
				mWorkQueue.push( &childNode );
			}
		}
	}

	return REACHABILITY_RESULT::SAFE;
}

}  // namespace hypro
