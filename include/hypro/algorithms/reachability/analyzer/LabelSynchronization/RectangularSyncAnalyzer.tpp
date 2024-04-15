/*
 * Copyright (c) 2023-2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "RectangularSyncAnalyzer.h"

namespace hypro {

template <typename State, typename Automaton, typename Multithreading>
REACHABILITY_RESULT RectangularSyncAnalyzer<State, Automaton, Multithreading>::run() {
	// create reachTree if not already present
	if ( mReachTree.empty() ) {
		mReachTree = makeRoots<State, Automaton>( *mHybridAutomaton );
	}
	// initialize queue
	for ( auto& automaton : mHybridAutomata ) {
		for ( auto& rtNode : mAutomatonReachTreeMap[automaton] ) {
			mWorkQueue.push( std::make_pair( &rtNode, automaton ) );
			// mPairWorkQueue.push( std::make_pair( &rtNode, automaton ) );
		}
	}
	// maybe we can do with one mReachTree, without the map
	// for ( auto &rtNode : mReachTree ) {
	// 	mWorkQueue.push( &rtNode );
	// }
	DEBUG( "hypro.reachability.rectangular", "Added " << mWorkQueue.size() << " initial states to the work queue" );

	REACHABILITY_RESULT safetyResult;
	assert( mAnalysisSettings.strategy().front().reachability_analysis_method == REACH_SETTING::FORWARD );
	// forward analysis
	safetyResult = forwardRun();

	return safetyResult;
}

template <typename State, typename Automaton, typename Multithreading>
REACHABILITY_RESULT RectangularSyncAnalyzer<State, Automaton, Multithreading>::forwardRun() {
	DEBUG( "hypro.reachability.rectangular", "Start forward analysis" );
	// create a rectangular worker for each automaton
	// std::vector<RectangularWorker<State, Automaton>> workerVector;
	// for ( auto &automaton : mHybridAutomata ) {
	// 	workerVector.push_back(RectangularWorker<State, Automaton>{ *automaton, mAnalysisSettings });
	// }
	std::map<Automaton const*, RectangularSyncWorker<State, Automaton>> automatonWorkerMap;
	int varPoolIndex = 0;
	for ( auto automaton : mHybridAutomata ) {
		automatonWorkerMap.emplace( std::make_pair( automaton, RectangularSyncWorker<State, Automaton>{ *automaton, mAnalysisSettings, mLabelAutomatonMap, varPoolIndex } ) );
		varPoolIndex++;
	}
	// RectangularWorker<State, Automaton> worker{ *mHybridAutomaton, mAnalysisSettings };

	while ( !mWorkQueue.empty() ) {
		// auto *currentNode = getNodeFromQueue();
		// DEBUG( "hypro.reachability",
		// 	   "Process node (@" << currentNode << ") with location " << currentNode->getLocation()->getName()
		// 						 << " with path " << currentNode->getTreePath() );

		// process with sync
		auto nodeAutoPair = getPairFromQueue();
		auto* node = nodeAutoPair.first;
		auto* automaton = nodeAutoPair.second;
		DEBUG( "hypro.reachability",
			   "Process node (@" << node << ") with location " << node->getLocation()->getName()
								 << " with path " << node->getTreePath() );
		auto result = processNode( automatonWorkerMap.at( automaton ), node, automaton );
		if ( result != REACHABILITY_RESULT::SAFE ) {
			DEBUG( "hypro.reachability", "End Rectangular Reachability Analysis." );
			return result;
		}
	}

	return REACHABILITY_RESULT::SAFE;
}

template <typename State, typename Automaton, typename Multithreading>
REACHABILITY_RESULT
RectangularSyncAnalyzer<State, Automaton, Multithreading>::processNode( RectangularSyncWorker<State, Automaton>& worker,
																		ReachTreeNode<State, LocationT>* node, Automaton const* automaton ) {
	REACHABILITY_RESULT safetyResult;
	TRACE( "hypro.reachability.rectangular", "Analyze node at depth " << node->getDepth() );

	// reset worker state
	worker.clear();
	// change the variable pool
	worker.changeVariablePool();
	// in case the jump depth is reached, only compute time successors
	if ( node->getDepth() < mAnalysisSettings.fixedParameters().jumpDepth ) {
		safetyResult = worker.computeForwardReachability( *node );
	} else {
		safetyResult = worker.computeTimeSuccessors( *node );
	}

	if ( safetyResult != REACHABILITY_RESULT::SAFE ) {
		return safetyResult;
	}

	// create jump successor tasks
	for ( const auto& transitionStatesPair : worker.getJumpSuccessorSets() ) {
		for ( const auto jmpSucc : transitionStatesPair.second ) {
			// update reachTree
			// time is not considered in rectangular analysis so we store a dummy
			auto& childNode = node->addChild( jmpSucc, carl::Interval<SegmentInd>( 0, 0 ), transitionStatesPair.first );
			assert( childNode.getDepth() == node->getDepth() + 1 );

			// create Task for jump successors (local computation)
			addPairToQueue( &childNode, automaton );
		}
	}
	return REACHABILITY_RESULT::SAFE;
}

}  // namespace hypro
