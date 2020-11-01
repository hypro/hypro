#include "StochasticRectangularAnalyzer.h"

namespace hypro {

template <typename State>
void StochasticRectangularAnalyzer<State>::run() {
	// forward analysis
	forwardRun();

	// backward analysis
	backwardRun();

}

template <typename State>
void StochasticRectangularAnalyzer<State>::forwardRun() {
	std::set<ReachTreeNode<State>*> processedNode;
	// initialize queue
	for ( auto& initProb : mHybridAutomaton.getProbInitialState() ) {
		// create initial state
        auto location = initProb.first;
        auto condition = initProb.second.first;
		State initialState{ location };
		initialState.setSet( typename State::template nth_representation<0>{ condition.getMatrix(), condition.getVector() } );
		initialState.setTimestamp( carl::Interval<tNumber>( 0 ) );

		// create node from state
		auto initialNode{ std::make_unique<ReachTreeNode<State>>( location, initialState, carl::Interval<SegmentInd>( 0 ) ) };
		// add to reachTree
		mReachTree.emplace_back( std::move( initialNode ) );
		// add to queue
		mWorkQueue.push( mReachTree.back().get() );
	}

	while ( !mWorkQueue.empty() ) {
		StochasticRectangularWorker<State> worker{ mHybridAutomaton, mAnalysisSettings };
		ReachTreeNode<State>* currentNode = mWorkQueue.front();
		mWorkQueue.pop();

		processedNode.emplace( currentNode );
		std::cout << "current node: " << currentNode->getInitialSet()<< std::endl
					<< "size is : "<< mWorkQueue.size() << std::endl;

		if ( currentNode->getDepth() < mAnalysisSettings.fixedParameters().jumpDepth ) {
			worker.computeForwardReachability( *currentNode );
		} else {
			worker.computeTimeSuccessors( *currentNode );
		}

		// only for plotting
		mFlowpipes.emplace_back( worker.getFlowpipe() );

		// create jump successor tasks
		for ( const auto& transitionStatesPair : worker.getJumpSuccessorSets() ) {
			for ( const auto jmpSuccPair : transitionStatesPair.second ) {
				// update reachTree
				// time is not considered in rectangular analysis so we store a dummy
				State jmpSucc = jmpSuccPair.first;
				auto& childNode = currentNode->addChild( jmpSucc, carl::Interval<SegmentInd>( 0, 0 ), transitionStatesPair.first );
				mNodeTrans.emplace( std::make_pair( &childNode, transitionStatesPair.first ) );

				if ( jmpSuccPair.second == REACHABILITY_RESULT::SAFE ) {
					bool processed = false;
					for ( auto node : processedNode ) {
						if ( node->getInitialSet() == childNode.getInitialSet() &&
							node->getTimings() == childNode.getTimings() ){
							processed = true;
						}
					}
					if ( !processed ){
						// create Task
						mWorkQueue.push( &childNode );
					}
					std::cout << "safe node" << std::endl;
				} else {
					// unsafe nodes
					mUnsafeNodes.emplace_back( &childNode );
					std::cout << "unsafe node" << std::endl;
				}
			}
		}
	}
}

template <typename State>
void StochasticRectangularAnalyzer<State>::backwardRun() {

	while ( !mUnsafeNodes.empty() ) {

		size_t max_depth = 0;
		size_t position;
		for ( size_t i = 0 ; i < mUnsafeNodes.size() ; i++ ) {
			if ( mUnsafeNodes.at( i )->getDepth() > max_depth ) {
				max_depth = mUnsafeNodes.at( i )->getDepth();
				position = i;
			}
		}
		StochasticRectangularWorker<State> worker{ mHybridAutomaton, mAnalysisSettings };
		ReachTreeNode<State>* currentNode = mUnsafeNodes.at( position );
		mUnsafeNodes.erase( mUnsafeNodes.begin() + position );
		REACHABILITY_RESULT safetyResult;

		State badState = currentNode->getInitialSet();
		auto statePosition = mStateProbs.find( &badState  );
		if ( statePosition == mStateProbs.end() ) {
			mStateProbs.emplace( std::make_pair( &badState , 1 ) );
		}
		
		worker.computeBackwardReachability( *currentNode, mNodeTrans[currentNode], mStateProbs[&badState ] );
		
		// only for plotting
		mFlowpipes.emplace_back( worker.getFlowpipe() );

	}	
}

}  // namespace hypro
