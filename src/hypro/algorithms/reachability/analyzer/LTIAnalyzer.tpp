#include "LTIAnalyzer.h"

namespace hypro {

template <typename State>
REACHABILITY_RESULT LTIAnalyzer<State>::run() {
	// initialize queue
	for ( auto& [location, condition] : mHybridAutomaton.getInitialStates() ) {
		// create initial state
		State initialSet{ location };
		// TODO: needs update in case we switch to Representation template
		initialSet.setSet( typename State::template nth_representation<0>{ condition.getMatrix(), condition.getVector() } );
		initialSet.setTimestamp( carl::Interval<tNumber>( 0 ) );

		ReachTreeNode<State>& initialNode = mReachTree.addChild( &mReachTree, location, &mFlowpipes.emplace_back(), initialSet );

		// add to queue
		mWorkQueue.push( &initialNode );
	}

	TimeTransformationCache<Number> transformationCache;

	while ( !mWorkQueue.empty() ) {
		LTIWorker<State> worker{
			  mHybridAutomaton,
			  mAnalysisSettings.strategy.front(),
			  mAnalysisSettings.localTimeHorizon,
			  transformationCache };
		ReachTreeNode<State>* currentNode = mWorkQueue.front();
		mWorkQueue.pop();
		REACHABILITY_RESULT safetyResult;

		//Fixed point detection for TemplatePolyhedrons
		bool skipComputation = false;
		/*
		if ( currentNode->getInitialSet().getSetType( 0 ) == hypro::representation_name::polytope_t ) {
			for ( const auto& segment : mFirstStates ) {
				assert( segment.getSetType( 0 ) == hypro::representation_name::polytope_t );
				if ( segment.contains( currentNode->getInitialSet() ) ) {
					//skip the computation of this flowpipe
					COUNT( "Fixpoint detected" );
					skipComputation = true;
					break;
				}
			}
		}
		*/
		if ( skipComputation ) {
			continue;
		}

		if ( currentNode->getDepth() < mAnalysisSettings.jumpDepth ) {
			safetyResult = worker.computeForwardReachability( currentNode->getLocation(), currentNode->getInitialSet() );
		} else {
			safetyResult = worker.computeTimeSuccessors( currentNode->getLocation(), currentNode->getInitialSet() );
		}

		// only for plotting
		mFlowpipes.emplace_back( worker.getFlowpipe() );
		// for fixed point detection
		// TODO: this should be done on the tree, not in a member.
		// mFirstStates.emplace_back( currentNode->getInitialSet() );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return safetyResult;
		}

		// create jump successor tasks
		for ( const auto& [transition, timedValuationSets] : worker.getJumpSuccessorSets() ) {
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
