#include "StochasticRectangularAnalyzer.h"

namespace hypro {

template <typename State>
void StochasticRectangularAnalyzer<State>::forAndBackwardRun() {
	// forward analysis
	forwardRun();

	// backward analysis
	backwardRun();
}
template <typename State>
void StochasticRectangularAnalyzer<State>::onlyBackwardRun() {
	// backward analysis
	backwardAnalysisRun();
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
		// std::cout << "current node: " << currentNode->getInitialSet()<< std::endl
		// 			<< "size is : "<< mWorkQueue.size() << std::endl;

		if ( currentNode->getDepth() < mAnalysisSettings.fixedParameters().jumpDepth ) {
			worker.computeForwardReachability( *currentNode );
		} else {
			worker.computeTimeSuccessors( *currentNode );
		}

		// only for plotting
		mFlowpipes.emplace_back( worker.getFlowpipe() );
		// for ( const auto& fp : worker.getFlowpipe() ) {
		// 	std::cout << fp << std::endl;
		// }
		auto tmpPredecessor = worker.getPrdecessor();

		// create jump successor tasks
		for ( const auto& transitionStatesPair : worker.getJumpSuccessorSets() ) {
			for ( const auto jmpSuccPair : transitionStatesPair.second ) {
				// update reachTree
				// time is not considered in rectangular analysis so we store a dummy
				State jmpSucc = jmpSuccPair.first;
				State predecessorState;
				for ( auto [post, pre] : tmpPredecessor ) {
					if ( post == jmpSucc ) {
						predecessorState = pre;
						// std::cout<<"find pre state!!"<<std::endl;
						break;
					}
				}
				auto& childNode = currentNode->addChild( jmpSucc, carl::Interval<SegmentInd>( 0, 0 ), transitionStatesPair.first );
				mNodeTrans.emplace( std::make_pair( &childNode, transitionStatesPair.first ) );
				mNodePreState.emplace( std::make_pair( &childNode, predecessorState ) );

				if ( jmpSuccPair.second == REACHABILITY_RESULT::SAFE ) {
					bool processed = false;
					for ( auto node : processedNode ) {
						if ( node->getInitialSet() == childNode.getInitialSet() &&
							 node->getTimings() == childNode.getTimings() ) {
							processed = true;
						}
					}
					if ( !processed ) {
						// create Task
						mWorkQueue.push( &childNode );
					}
					// std::cout << "safe node" << std::endl;
				} else {
					// unsafe nodes
					mUnsafeNodes.emplace_back( &childNode );
					// std::cout << "unsafe node" << &childNode << std::endl;
				}
				// std::cout<<"before end mUnsafeNodes size is : " <<mUnsafeNodes.size() <<std::endl;
			}
		}
	}
}

template <typename State>
void StochasticRectangularAnalyzer<State>::backwardAnalysisRun() {
	std::set<ReachTreeNode<State>*> processedNode;
	// initialize queue
	for ( auto& [location, condition] : mHybridAutomaton.getLocalBadStates() ) {
		State badState{ location };
		badState.setSet( typename State::template nth_representation<0>{ condition.getMatrix(), condition.getVector() } );
		badState.setTimestamp( carl::Interval<tNumber>( 0 ) );

		// create node from state
		auto badNode{ std::make_unique<ReachTreeNode<State>>( location, badState, carl::Interval<SegmentInd>( 0 ) ) };
		// add to reachTree
		mReachTree.emplace_back( std::move( badNode ) );
		// add to queue
		mWorkQueue.push( mReachTree.back().get() );
	}

	for ( auto& condition : mHybridAutomaton.getGlobalBadStates() ) {
		if ( condition.getMatrix().rows() != 0 ) {
			for ( auto& location : mHybridAutomaton.getLocations() ) {
				// create global bad state
				State badState{ location };
				badState.setSet( typename State::template nth_representation<0>{ condition.getMatrix(), condition.getVector() } );
				badState.setTimestamp( carl::Interval<tNumber>( 0 ) );

				// create node from state
				auto badNode{ std::make_unique<ReachTreeNode<State>>( location, badState, carl::Interval<SegmentInd>( 0 ) ) };
				// add to reachTree
				mReachTree.emplace_back( std::move( badNode ) );
				// add to queue
				mWorkQueue.push( mReachTree.back().get() );
			}
		}
	}

	Number finalProb = 0;

	while ( !mWorkQueue.empty() ) {
		StochasticRectangularWorker<State> worker{ mHybridAutomaton, mAnalysisSettings };
		ReachTreeNode<State>* currentNode = mWorkQueue.front();
		mWorkQueue.pop();
		std::vector<std::pair<StochasticTransition<Number>*, std::pair<State, Number>>> probResult;

		Number currentProb = 1;
		for ( auto [node, prob] : mNodeProbs ) {
			if ( currentNode->getInitialSet() == node->getInitialSet() ) {
				currentProb = prob;
			}
		}

		worker.computeBackwardReachabilityProb( *currentNode, currentProb );
		processedNode.emplace( currentNode );

		// only for plotting
		mFlowpipes.emplace_back( worker.getFlowpipe() );

		// create jump predecessors tasks
		for ( const auto& transitionStatesPair : worker.getTranStateProb() ) {
			auto [jmpPre, probability] = transitionStatesPair.second;
			// update reachTree

			// Stefan: We have changed the code such that the tree grows from the bad states down instead of growing at the root upwards.
			auto& childNode = currentNode->addChild( jmpPre, carl::Interval<SegmentInd>( 0 ), transitionStatesPair.first );

			// create Task
			// bool processed = false;
			// for (auto node : processedNode ){
			// 	if ( node->getInitialSet() == jmpPre ){
			// 		processed = true;
			// 	}
			// }
			// if( !processed ){
			if ( transitionStatesPair.first->getTransitionWeight() != 0 ) {
				mWorkQueue.push( &childNode );
			}
			// }

			for ( auto [node, prob] : mNodeProbs ) {
				if ( jmpPre == node->getInitialSet() ) {
					probability = prob + probability;
					break;
				}
			}

			mNodeProbs.emplace( std::make_pair( &childNode, probability ) );

			// StochasticTransition<Number>* tau = transitionStatesPair.first;
			if ( transitionStatesPair.first->getTransitionWeight() == 0 ) {
				for ( auto initialState : mHybridAutomaton.getProbInitialState() ) {
					if ( *jmpPre.getLocation() == *initialState.first ) {
						finalProb += probability * initialState.second.second;
					}
				}
			}
		}
	}
	std::cout << "to reach bad states probability is: " << finalProb << std::endl;
}

template <typename State>
void StochasticRectangularAnalyzer<State>::backwardRun() {
	Number finalProb = 0;

	while ( !mUnsafeNodes.empty() ) {
		size_t max_depth = 0;
		size_t position;
		for ( size_t i = 0; i < mUnsafeNodes.size(); i++ ) {
			if ( mUnsafeNodes.at( i )->getDepth() > max_depth ) {
				max_depth = mUnsafeNodes.at( i )->getDepth();
				position = i;
			}
		}
		StochasticRectangularWorker<State> worker{ mHybridAutomaton, mAnalysisSettings };
		ReachTreeNode<State>* currentNode = mUnsafeNodes.at( position );
		mUnsafeNodes.erase( mUnsafeNodes.begin() + position );
		// REACHABILITY_RESULT safetyResult;

		std::vector<State*> pathQueue;
		State badState = currentNode->getInitialSet();
		auto statePosition = mStateProbs.find( &badState );
		if ( statePosition == mStateProbs.end() ) {
			mStateProbs.emplace( std::make_pair( &badState, 1 ) );
		}

		pathQueue.emplace_back( &badState );
		State* badPtr = &badState;
		Number tmpProb = 0;

		while ( currentNode->getParent() != NULL ) {
			State preStateSet = mNodePreState.find( currentNode )->second;

			// if (preStateSet==NULL){
			// 	std::cout<<"empty"<<std::endl;
			// } else {
			// 	std::cout<<"not empty"<<std::endl;
			// }
			// std::cout<<"bad state before process is: " << badState << ", " << badPtr << std::endl;

			worker.computeBackwardReachability( badState, *currentNode, mNodeTrans[currentNode], mStateProbs[badPtr], preStateSet );

			// only for plotting
			mFlowpipes.emplace_back( worker.getFlowpipe() );
			// std::cout<<"backward begin"<<std::endl;
			// for ( const auto& fp : worker.getFlowpipe() ) {
			// 	std::cout << fp << std::endl;
			// }
			// std::cout<<"backward end"<<std::endl;

			auto [jmpPre, probability] = worker.getProbability();

			auto& parentNode = currentNode->addChild( jmpPre, carl::Interval<SegmentInd>( 0 ), mNodeTrans[currentNode] );

			mStateProbs.emplace( std::make_pair( &jmpPre, probability ) );
			currentNode = currentNode->getParent();
			// std::cout<<"pre state is: " << jmpPre << std::endl;
			badPtr = &jmpPre;
			badState = jmpPre;
			mStateProbs.emplace( std::make_pair( badPtr, probability ) );
			tmpProb = probability;

			// std::cout<<"pre state after copy: " << badPtr << std::endl;
		}

		finalProb += tmpProb;
	}
	std::cout << "to reach bad states probability is: " << finalProb << std::endl;
}

}  // namespace hypro
