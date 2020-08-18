#include "SingularAnalyzer.h"

namespace hypro {

template <typename Representation>
REACHABILITY_RESULT SingularAnalyzer<Representation>::run() {
	return forwardRun();
}

template <typename Representation>
REACHABILITY_RESULT SingularAnalyzer<Representation>::forwardRun() {
	// initialize queue
	for ( auto& [location, condition] : mHybridAutomaton.getInitialStates() ) {
		// create initial state
		Representation initialStateSet{ condition.getMatrix(), condition.getVector() };

		// create node from state
		auto initialNode{ std::make_unique<ReachTreeNode<Representation>>( location, initialStateSet, carl::Interval<SegmentInd>( 0 ) ) };
		// add to reachTree
		mReachTree.emplace_back( std::move( initialNode ) );
		// add to queue
		mWorkQueue.push( mReachTree.back().get() );
	}

	while ( !mWorkQueue.empty() ) {
		SingularWorker<Representation> worker{ mHybridAutomaton, mAnalysisSettings };
		ReachTreeNode<Representation>* currentNode = mWorkQueue.front();
		mWorkQueue.pop();
		REACHABILITY_RESULT safetyResult;

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
		for ( const auto& [transition, stateSets] : worker.getJumpSuccessorSets() ) {
			for ( const auto jmpSucc : stateSets ) {
				// update reachTree
				// time is not considered in singular analysis so we store a dummy
				auto& childNode = currentNode->addChild( jmpSucc, carl::Interval<SegmentInd>( 0, 0 ), transition );

				// create Task
				mWorkQueue.push( &childNode );
			}
		}
	}

	return REACHABILITY_RESULT::SAFE;
}

}  // namespace hypro
