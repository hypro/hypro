/*
 * Copyright (c) 2023-2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../../types.h"
// #include "../../workers/RectangularWorker.h"
#include "../../workers/RectangularSyncWorker.h"
#include "../../../../datastructures/HybridAutomaton/Label.h"

#include <queue>

namespace hypro {

/**
 * @brief Class which implements a forward reachability analysis method for multiple rectangular automata with distinct variable sets with synchronization over labels
 * @details Requires the usage of a suitable state set representation, e.g., carlPolytope.
 * @tparam State state set representation type (must be polyhedral)
 * @tparam Automaton hybrid automaton type
 * @tparam Multithreading enable/disable multithreading
 */
template <typename State, typename Automaton, typename Multithreading = NoMultithreading>
class RectangularSyncAnalyzer {
	static_assert( std::is_same<typename State::NumberType, typename Automaton::NumberType>() );
	using Number = typename State::NumberType;
	using LocationT = typename Automaton::LocationType;

  public:
	/// default constructor (deleted)
	RectangularSyncAnalyzer() = delete;

	/// constructor from automaton and settings with additional reachTree
	RectangularSyncAnalyzer( Automaton const &ha, const Settings &setting,
							 std::vector<ReachTreeNode<State, LocationT>> &roots )
		: mHybridAutomaton( &ha )
		, mAnalysisSettings( setting )
		, mReachTree( roots ) {
	}

	/// constructor from automata and settings
	RectangularSyncAnalyzer( std::vector<Automaton> const &automata, const Settings &setting,
							 std::vector<ReachTreeNode<State, LocationT>> &roots )
		: mAnalysisSettings( setting )
		, mReachTree( roots )
		, mAutomatonReachTreeMap()
		, mLabelAutomatonMap()
		, mHybridAutomata() {
		for ( auto &automaton : automata ) {
			mHybridAutomata.push_back( &automaton );
			mAutomatonReachTreeMap.emplace( std::make_pair( &automaton, makeRoots<State, Automaton>( automaton ) ) );
			for (auto label : automaton.getLabels()) {
				mLabelAutomatonMap[label].insert(&automaton);
        	}
	        // allLabels.insert(automaton.getLabels().begin(), automaton.getLabels().end()); //TODO maybe find out how this would work. 
		}
		// // create a map from each label to a set of automata that need to synchronize on this label
		// for (auto label : allLabels) {
		// 	for (auto automaton : mHybridAutomata) {
		// 		if (automaton->getLabels().count(label)) {
		// 			mLabelAutomatonMap[label].insert(automaton);
		// 		}
		// 	}
		// }
		auto count = automata.size();
		for (typename std::map<Automaton const *, std::vector<ReachTreeNode<State, LocationT>>>::iterator it = mAutomatonReachTreeMap.begin(); it != mAutomatonReachTreeMap.end(); ++it) {
			for ( auto &rtNode : it->second ) {
				rtNode.initializeSyncNodes( count );
			}
		}
	}

	/// main method for reachability analysis
	REACHABILITY_RESULT run();

	REACHABILITY_RESULT forwardRun();

	// void addToQueue( ReachTreeNode<State, LocationT> *node ) {
	// 	mWorkQueue.push( node );
	// }

	// ReachTreeNode<State, LocationT> *getNodeFromQueue() {
	// 	auto *res = mWorkQueue.front();
	// 	mWorkQueue.pop();
	// 	return res;
	// }

	void addPairToQueue( ReachTreeNode<State, LocationT> *node, Automaton const *automaton ) {
		mWorkQueue.push( std::make_pair( node, automaton ));
	}

	std::pair<ReachTreeNode<State, LocationT> *, Automaton const *> getPairFromQueue() {
		auto res = mWorkQueue.front();
		mWorkQueue.pop();
		return res;
	}

  private:
	REACHABILITY_RESULT
	processNode( RectangularSyncWorker<State, Automaton> &worker, ReachTreeNode<State, LocationT> *node, Automaton const* automaton );

  protected:
	// std::queue<ReachTreeNode<State, LocationT> *> mWorkQueue;											 ///< Queue holds all nodes that require processing
	std::queue<std::pair<ReachTreeNode<State, LocationT> *, Automaton const *>> mWorkQueue;			 	 ///< Queue holds pairs <node, automaton> that require processing
	Automaton const *mHybridAutomaton;																	 ///< Pointer to the automaton which is analyzed		(TODO delete)
	std::vector<Automaton const *> mHybridAutomata;														 ///< Vector of pointers to the automata which are analyzed
	const Settings mAnalysisSettings;																	 ///< Settings used for analysis
	std::vector<ReachTreeNode<State, LocationT>> &mReachTree;											 ///< Forest of ReachTrees computed		(TODO delete)
	std::map<Automaton const *, std::vector<ReachTreeNode<State, LocationT>>> mAutomatonReachTreeMap{};	 ///< map (*automaton -> reachTree)
	std::map<Label, std::set<Automaton const *>> mLabelAutomatonMap{};									 ///< map (label -> automata)
};

}  // namespace hypro

#include "RectangularSyncAnalyzer.tpp"
