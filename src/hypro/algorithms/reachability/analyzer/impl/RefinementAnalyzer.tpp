#include "RefinementAnalyzer.h"

namespace hypro {

template <typename Representation>
std::pair<REACHABILITY_RESULT, ReachTreeNode<Representation>*> RefinementAnalyzer<Representation>::run() {
	//Setup settings for flowpipe construction in worker
	TimeTransformationCache<Number> transformationCache;
	LTIWorker<Representation> worker{
		  mHybridAutomaton,
		  mAnalysisSettings.strategy.front(),
		  mAnalysisSettings.localTimeHorizon,
		  transformationCache };

	while ( !mWorkQueue.empty() ) {
		ReachTreeNode<Representation>* currentNode = mWorkQueue.back();
		mWorkQueue.pop_back();
		REACHABILITY_RESULT safetyResult;

		//TODO ignore transition that aren't the one on the path
		safetyResult = worker.computeTimeSuccessors( currentNode->getInitialSet(), currentNode->getLocation(), std::back_inserter( currentNode->getFlowpipe() ) );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return { safetyResult, currentNode };
		}

		// do not perform discrete jump if jump depth was reached
		if ( currentNode->getDepth() == mAnalysisSettings.jumpDepth ) continue;

		// get path element
		auto [pathTiming, pathTransition] = mPath.elements.at( currentNode->getDepth() );

		// create jump successor tasks
		for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( currentNode->getFlowpipe(), currentNode->getLocation() ) ) {
			// check against path
			if ( transition != pathTransition ) continue;

			for ( const auto [valuationSet, localDuration] : timedValuationSets ) {
				// update reachTree

				// convert local time to global time
				//TODO currently assuming time step is scaled to 1
				carl::Interval<SegmentInd> const& initialSetDuration = currentNode->getTimings();
				carl::Interval<SegmentInd> globalDuration = carl::Interval( initialSetDuration.lower() + localDuration.lower(), initialSetDuration.upper() + 1 + localDuration.upper() );

				// check against path
				// if timing don't intersect -> discard
				if ( globalDuration.upper() < pathTiming.lower() || globalDuration.lower() > pathTiming.upper() ) continue;

				ReachTreeNode<Representation>& childNode = currentNode->addChild( valuationSet, globalDuration, transition );

				// create Task
				mWorkQueue.push_front( &childNode );
			}
		}
	}

	return { REACHABILITY_RESULT::SAFE, nullptr };
}

}  // namespace hypro
