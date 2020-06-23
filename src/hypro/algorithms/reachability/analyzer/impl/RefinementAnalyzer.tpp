#include "RefinementAnalyzer.h"

namespace hypro {

template <typename Representation>
REACHABILITY_RESULT RefinementAnalyzer<Representation>::run() {
	// initialize queue
	for ( auto& [location, condition] : mHybridAutomaton.getInitialStates() ) {
		auto* fp = &mFlowpipes.emplace_back();
		fp->emplace_back( { condition.getMatrix(), condition.getVector() } );
		// create node from state
		auto* initialNode = &mRoots.emplace_back( location, fp );

		// add to queue
		mWorkQueue.push( initialNode );
	}

	while ( !mWorkQueue.empty() ) {
		LTIWorker<State> worker{ mHybridAutomaton, mAnalysisSettings };
		auto* currentNode = mWorkQueue.front();
		mWorkQueue.pop();
		REACHABILITY_RESULT safetyResult;

		if ( currentNode->getDepth() < mAnalysisSettings.jumpDepth ) {
			safetyResult = worker.computeForwardReachability( *currentNode );
		} else {
			safetyResult = worker.computeTimeSuccessors( *currentNode );
		}

		// only for plotting
		currentNode->getFlowpipe()->emplace_back( worker.getFlowpipe() );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return safetyResult;
		}

		// create jump successor tasks
		for ( const auto& [transition, states] : worker.getJumpSuccessorSets() ) {
			for ( const auto jmpSucc : states ) {
				// update reachTree
				auto* childNode = new ReachTreeNodev2<Representation>{ currentNode, jmpSucc };
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

template <typename Representation>
REACHABILITY_RESULT RefinementAnalyzer<Representation>::run( const Path<Number, SegmentInd>& path ) {
}

}  // namespace hypro
