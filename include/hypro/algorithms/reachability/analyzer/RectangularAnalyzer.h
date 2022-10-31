/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../types.h"
#include "../workers/RectangularWorker.h"

#include <queue>

namespace hypro {
/**
 * @brief Class which implements a forward reachability analysis method for rectangular automata
 * @details Requires the usage of a suitable state set representation, e.g., carlPolytope.
 * @tparam State
 */
template <typename State, typename Automaton>
class RectangularAnalyzer {
	static_assert( std::is_same<typename State::NumberType, typename Automaton::NumberType>() );
	using Number = typename State::NumberType;
	using LocationT = typename Automaton::LocationType;

  public:
	/// default constructor (deleted)
	RectangularAnalyzer() = delete;
	/// constructor from automaton and settings with additional reachTree
	RectangularAnalyzer( const Automaton& ha, const Settings& setting, std::vector<ReachTreeNode<State, LocationT>>& roots )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting )
		, mReachTree( roots ) {
	}
	/// main method for reachability analysis
	REACHABILITY_RESULT run();
	REACHABILITY_RESULT forwardRun();
	// REACHABILITY_RESULT backwardRun();
	/// getter for computed flowpipes
	const std::vector<Flowpipe<State>>& getFlowpipes() const { return mFlowpipes; }

  protected:
	std::queue<ReachTreeNode<State, LocationT>*> mWorkQueue;   ///< Queue holds all nodes that require processing
	std::vector<Flowpipe<State>> mFlowpipes;				   ///< Storage for already computed flowpipes
	HybridAutomaton<Number> mHybridAutomaton;				   ///< Automaton which is analyzed
	Settings mAnalysisSettings;								   ///< Settings used for analysis
	std::vector<ReachTreeNode<State, LocationT>>& mReachTree;  ///< Forest of ReachTrees computed
};

}  // namespace hypro

#include "RectangularAnalyzer.tpp"
