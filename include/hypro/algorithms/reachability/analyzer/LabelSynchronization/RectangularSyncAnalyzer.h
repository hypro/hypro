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
#include "../../workers/RectangularWorker.h"

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

	/// main method for reachability analysis
	REACHABILITY_RESULT run();

	REACHABILITY_RESULT forwardRun();

	void addToQueue( ReachTreeNode<State, LocationT> *node ) {
		mWorkQueue.push( node );
	}

	ReachTreeNode<State, LocationT> *getNodeFromQueue() {
		auto *res = mWorkQueue.front();
		mWorkQueue.pop();
		return res;
	}

  private:
	REACHABILITY_RESULT
	processNode( RectangularWorker<State, Automaton> &worker, ReachTreeNode<State, LocationT> *node );

  protected:
	std::queue<ReachTreeNode<State, LocationT> *> mWorkQueue;  ///< Queue holds all nodes that require processing
	Automaton const *mHybridAutomaton;						   ///< Pointer to the automaton which is analyzed		vector of automata
	const Settings mAnalysisSettings;						   ///< Settings used for analysis
	std::vector<ReachTreeNode<State, LocationT>> &mReachTree;  ///< Forest of ReachTrees computed					map (automaton -> reachTree)
};

}  // namespace hypro

#include "RectangularSyncAnalyzer.tpp"
