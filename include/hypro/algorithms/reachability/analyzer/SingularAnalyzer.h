/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../types.h"
#include "../workers/SingularWorker.h"
#include "ReturnTypes.h"

#include <queue>

namespace hypro {

/// indicates that the singular analysis succeeded, i.e. no
struct SingularSuccess {};

/**
 * @brief Class which implements a forward reachability analysis method for singular automata.
 * @details Requires the usage of a suitable state set representation, e.g., carlPolytope.
 * @tparam Representation The used state set representation.
 */
template <typename Representation, typename Automaton>
class SingularAnalyzer {
	using Number = typename Representation::NumberType;
	using LocationT = typename Automaton::LocationType;

  public:
	using SingularResult = AnalysisResult<VerificationSuccess, Failure<Representation, LocationT>>;

	/**
	 * @brief      Default constructor (deleted).
	 */
	SingularAnalyzer() = delete;

	/**
	 * @brief Construct a new Singular Analyzer object
	 *
	 * @param ha The hybrid (singular) automaton
	 * @param fixedParameters A parameter configuration (parameter timeStep is not used)
	 * @param roots The root nodes of the search tree containing the initial states of ha
	 */
	SingularAnalyzer( Automaton const& ha,
					  FixedAnalysisParameters const& fixedParameters,
					  std::vector<ReachTreeNode<Representation, LocationT>>& roots )
		: mHybridAutomaton( &ha )
		, mAnalysisSettings( fixedParameters )
		, mReachTree( roots ) {
		for ( auto& root : roots ) {
			mWorkQueue.push_back( &root );
		}
	}
	/**
	 * @brief      Main method for reachability analysis. Calls the method @ref forwardRun.
	 * @return     SAFE if no bad state intersection is found and UNKNOWN otherwise.
	 */
	SingularResult run();

	/**
	 * @brief      Execute forward reachability result.
	 * @return     SAFE if no bad state intersection is found and UNKNOWN otherwise.
	 */
	SingularResult forwardRun();

  protected:
	Automaton const* mHybridAutomaton;									///< Automaton which is analyzed
	FixedAnalysisParameters mAnalysisSettings;							///< Settings used for analysis
	std::vector<ReachTreeNode<Representation, LocationT>>& mReachTree;	///< Forest of ReachTrees computed
	std::deque<ReachTreeNode<Representation, LocationT>*> mWorkQueue;	///< Queue holds all nodes that require processing
};

}  // namespace hypro

#include "SingularAnalyzer.tpp"
