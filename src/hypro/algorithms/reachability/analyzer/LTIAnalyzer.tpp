#include "LTIAnalyzer.h"

namespace hypro {

template <typename State>
std::pair<REACHABILITY_RESULT, ReachTreeNode<State>*> LTIAnalyzer<State>::run() {
	//Setup settings for flowpipe construction in worker
	TimeTransformationCache<Number> transformationCache;
	LTIWorker<State> worker{
		  mHybridAutomaton,
		  mAnalysisSettings.strategy.front(),
		  mAnalysisSettings.localTimeHorizon,
		  transformationCache };

	while ( !mWorkQueue.empty() ) {
		ReachTreeNode<State>* currentNode = mWorkQueue.back();
		mWorkQueue.pop_back();
		REACHABILITY_RESULT safetyResult;

		safetyResult = worker.computeTimeSuccessors( currentNode->getInitialSet(), currentNode->getLocation(), std::back_inserter( currentNode->getFlowpipe() ) );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return { safetyResult, currentNode };
		}

		//Do not perform discrete jump if jump depth was reached
		if ( currentNode->getDepth() == mAnalysisSettings.jumpDepth ) continue;

		// create jump successor tasks
		for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( currentNode->getFlowpipe(), currentNode->getLocation() ) ) {
			for ( const auto [valuationSet, localDuration] : timedValuationSets ) {
				// update reachTree

				// convert local time to global time
				//TODO currently assuming time step is scaled to 1
				carl::Interval<SegmentInd> const& initialSetDuration = currentNode->getTimings();
				carl::Interval<SegmentInd> globalDuration = carl::Interval( initialSetDuration.lower() + localDuration.lower(), initialSetDuration.upper() + 1 + localDuration.upper() );

				ReachTreeNode<State>& childNode = currentNode->addChild( valuationSet, globalDuration, transition );

				// create Task
				mWorkQueue.push_front( &childNode );
			}
		}
	}

	return { REACHABILITY_RESULT::SAFE, nullptr };
}

}  // namespace hypro
