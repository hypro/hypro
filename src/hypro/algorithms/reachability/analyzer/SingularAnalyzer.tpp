#include "SingularAnalyzer.h"

namespace hypro {

template <typename Representation>
typename SingularAnalyzer<Representation>::SingularResult SingularAnalyzer<Representation>::run() {
	return forwardRun();
}

template <typename Representation>
typename SingularAnalyzer<Representation>::SingularResult SingularAnalyzer<Representation>::forwardRun() {
	SingularWorker<Representation> worker{ *mHybridAutomaton, mAnalysisSettings };
	DEBUG( "hypro.reachability", "Start singular analysis." );
	while ( !mWorkQueue.empty() ) {
		ReachTreeNode<Representation>* currentNode = mWorkQueue.front();
		mWorkQueue.pop_front();
		REACHABILITY_RESULT safetyResult;
		DEBUG( "hypro.reachability", "Compute forward time successors in node " << *currentNode );
		if ( currentNode->getDepth() < mAnalysisSettings.jumpDepth ) {
			safetyResult = worker.computeForwardReachability( *currentNode );
		} else {
			safetyResult = worker.computeTimeSuccessors( *currentNode );
		}

		// only for plotting
		auto& flowpipe = currentNode->getFlowpipe();
		flowpipe.insert( flowpipe.begin(), worker.getFlowpipe().begin(), worker.getFlowpipe().end() );
		if ( !flowpipe.empty() ) {
			DEBUG( "hypro.reachability", "Resulting state set " << flowpipe.back() );
		} else {
			DEBUG( "hypro.reachability", "Resulting state set is empty" );
		}

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return { Failure{ currentNode } };
		}

		// create jump successor tasks
		for ( const auto& [transition, stateSets] : worker.getJumpSuccessorSets() ) {
			for ( const auto jmpSucc : stateSets ) {
				// update reachTree
				// time is not considered in singular analysis so we store a dummy
				auto& childNode = currentNode->addChild( jmpSucc, carl::Interval<SegmentInd>( 0, 0 ), transition );
				DEBUG( "hypro.reachability", "Added jump successor node " << childNode );

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
