#include "RefinementAnalyzer.h"

namespace hypro {

template <typename Representation>
auto RefinementAnalyzer<Representation>::run() -> RefinementResult {
	//Setup settings for flowpipe construction in worker
	TimeTransformationCache<Number> transformationCache;
	LTIWorker<Representation> worker{
		  mHybridAutomaton,
		  mAnalysisSettings.strategy.front(),
		  mAnalysisSettings.localTimeHorizon,
		  transformationCache };

	std::vector<ReachTreeNode<Representation>*> pathSuccessors{};

	while ( !mWorkQueue.empty() ) {
		ReachTreeNode<Representation>* currentNode = mWorkQueue.back();
		mWorkQueue.pop_back();
		REACHABILITY_RESULT safetyResult;

		//TODO ignore transition that aren't the one on the path
		safetyResult = worker.computeTimeSuccessors( currentNode->getInitialSet(), currentNode->getLocation(), std::back_inserter( currentNode->getFlowpipe() ) );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return { Failure{ currentNode } };
		}

		// do not perform discrete jump if jump depth was reached
		if ( currentNode->getDepth() == mAnalysisSettings.jumpDepth ) continue;

		// collect for return if the node is one level past the end of the path
		if ( currentNode->getDepth() == mPath.elements.size() ) {
			pathSuccessors.push_back( currentNode );
			continue;
		}

		// get path element
		auto [pathTiming, pathTransition] = mPath.elements.at( currentNode->getDepth() );

		// check against path
		// if timings don't intersect -> discard
		if ( currentNode->getTimings().upper() < pathTiming.lower() || currentNode->getTimings().lower() > pathTiming.upper() ) continue;

		bool matchedOne = false;
		for ( auto* child : currentNode->getChildren() ) {
			if ( child->getTransition() == pathTransition ) {
				matchedOne = true;
				mWorkQueue.push_front( child );
			}
		}

		if ( !matchedOne ) {
			auto jumpSuccGen = worker.getJumpSuccessors( currentNode->getFlowpipe(), pathTransition );

			while ( auto succ = jumpSuccGen.next() ) {
				auto& [valuationSet, localDuration] = *succ;

				// convert local time to global time
				//TODO currently assuming time step is scaled to 1
				carl::Interval<SegmentInd> const& initialSetDuration = currentNode->getTimings();
				carl::Interval<SegmentInd> globalDuration = carl::Interval( initialSetDuration.lower() + localDuration.lower(), initialSetDuration.upper() + 1 + localDuration.upper() );

				ReachTreeNode<Representation>& childNode = currentNode->addChild( valuationSet, globalDuration, pathTransition );

				// create Task
				mWorkQueue.push_front( &childNode );
			}
		}
	}

	return { RefinementSuccess{ pathSuccessors } };
}

}  // namespace hypro
