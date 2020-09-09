#include "SingularAnalyzer.h"

namespace hypro {

template <typename Representation>
typename SingularAnalyzer<Representation>::SingularResult SingularAnalyzer<Representation>::run() {
	return forwardRun();
}

template <typename Representation>
typename SingularAnalyzer<Representation>::SingularResult SingularAnalyzer<Representation>::forwardRun() {
	SingularWorker<Representation> worker{ mHybridAutomaton, mAnalysisSettings };

	while ( !mWorkQueue.empty() ) {
		ReachTreeNode<Representation>* currentNode = mWorkQueue.front();
		mWorkQueue.pop_front();
		REACHABILITY_RESULT safetyResult;

		if ( currentNode->getDepth() < mAnalysisSettings.jumpDepth ) {
			safetyResult = worker.computeForwardReachability( *currentNode );
		} else {
			safetyResult = worker.computeTimeSuccessors( *currentNode );
		}

		// only for plotting
		auto& flowpipe = currentNode->getFlowpipe();
		flowpipe.insert( flowpipe.begin(), worker.getFlowpipe().begin(), worker.getFlowpipe().end() );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return { Failure{ currentNode } };
		}

		// create jump successor tasks
		for ( const auto& [transition, stateSets] : worker.getJumpSuccessorSets() ) {
			for ( const auto jmpSucc : stateSets ) {
				// update reachTree
				// time is not considered in singular analysis so we store a dummy
				auto& childNode = currentNode->addChild( jmpSucc, carl::Interval<SegmentInd>( 0, 0 ), transition );

				// create Task
				mWorkQueue.push_back( &childNode );
			}
		}
		// reset worker for next task
		worker.reset();
	}

	return { VerificationSuccess{} };
}

}  // namespace hypro
