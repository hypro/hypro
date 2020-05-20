#include "LTIAnalyzer.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT LTIAnalyzer<State>::run() {
	// initialize queue
	for ( auto& locationConditionPair : mHybridAutomaton.getInitialStates() ) {
		// create initial state
		State initialState{locationConditionPair.first};
		initialState.setSet( typename State::template nth_representation<0>{locationConditionPair.second.getMatrix(), locationConditionPair.second.getVector()} );
		initialState.setTimestamp( carl::Interval<tNumber>( 0 ) );

		// create node from state
		auto* initialNode = new ReachTreeNode<State>{initialState};
		// add to reachTree
		initialNode->setParent( mReachTree.getRoot() );
		mReachTree.getRoot()->addChild( initialNode );

		// add to queue
		mWorkQueue.push( initialNode );
	}

	while ( !mWorkQueue.empty() ) {

		LTIWorker<State> worker{mHybridAutomaton, mAnalysisSettings};
		ReachTreeNode<State>* currentNode = mWorkQueue.front();
		mWorkQueue.pop();
		REACHABILITY_RESULT safetyResult;

		//Fixed point detection for TemplatePolyhedrons
		bool skipComputation = false;
		if(currentNode->getState().getSetType(0) == hypro::representation_name::polytope_t){
			for(const auto& segment : mFirstStates){
				assert(segment.getSetType(0) == hypro::representation_name::polytope_t);
				if(segment.contains(currentNode->getState())){
					//skip the computation of this flowpipe
					COUNT("Fixpoint detected");
					skipComputation = true;
					break;
				}
			}
		}
		if(skipComputation){
			continue;
		}

		if ( currentNode->getDepth() < mAnalysisSettings.jumpDepth ) {
			safetyResult = worker.computeForwardReachability( *currentNode );
		} else {
			safetyResult = worker.computeTimeSuccessors( *currentNode );
		}

		// only for plotting
		mFlowpipes.emplace_back( worker.getFlowpipe() );
		// for fixed point detection
		mFirstStates.emplace_back( currentNode->getState() );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return safetyResult;
		}

		// create jump successor tasks
		for ( const auto& transitionStatesPair : worker.getJumpSuccessorSets() ) {
			for ( const auto jmpSucc : transitionStatesPair.second ) {
				// update reachTree
				auto* childNode = new ReachTreeNode<State>{jmpSucc};
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

}  // namespace hypro
