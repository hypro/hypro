/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../handlers/badStateHandlers/rectangularBadStateHandler.h"
#include "../handlers/guardHandlers/rectangularGuardHandler.h"
#include "../handlers/invariantHandlers/rectangularInvariantHandler.h"
#include "../handlers/jumpHandlers/rectangularJumpHandler.h"
#include "../handlers/jumpHandlers/singularJumpHandler.h"
#include "../handlers/resetHandlers/rectangularResetHandler.h"
#include "../handlers/timeEvolutionHandlers/rectangularTimeEvolutionHandler.h"

#include <vector>

namespace hypro {

/**
 * @brief Class implementing a worker for rectangular automata.
 * @details A worker implements a method computing a time transition followed by a discrete transition. The repeated calling of a worker allows to implement a complete reachability analysis method.
 * @tparam State
 */
template <typename State, typename Automaton>
class RectangularWorker {
  private:
	using Number = typename State::NumberType;
	using LocationT = typename Automaton::LocationType;
	using JumpSuccessors = typename rectangularGuardHandler<State, LocationT>::TransitionStatesMap;
	using JumpPredecessors = typename rectangularGuardHandler<State, LocationT>::TransitionStatesMap;

  public:
	/// constructor from rectangular automaton and settings
	RectangularWorker( const Automaton& ha, const Settings& settings )
		: mHybridAutomaton( ha )
		, mSettings( settings ) {}
	/// computes a time transition followed by a discrete transition
	REACHABILITY_RESULT computeForwardReachability( ReachTreeNode<State, LocationT>& task );
	/// computes a time transition
	REACHABILITY_RESULT computeTimeSuccessors( ReachTreeNode<State, LocationT>& task );
	/// computes a discrete transition. Requires available time successors.
	void computeJumpSuccessors( const LocationT* location );
	/// getter for discrete jump successor sets
	REACHABILITY_RESULT computeBackwardReachability( ReachTreeNode<State, LocationT>& task );
	REACHABILITY_RESULT computeTimePredecessors( ReachTreeNode<State, LocationT>& task );
	REACHABILITY_RESULT underapproximateTimePredecessors( ReachTreeNode<State, LocationT>& task );

	std::pair<Location<Number>*, State> refineJumpPredecessors( ReachTreeNode<State, LocationT>& task );
	void computeJumpPredecessors();
	const JumpSuccessors& getJumpSuccessorSets() const { return mJumpSuccessorSets; }
	const JumpSuccessors& getJumpPredecessorSets() const { return mJumpPredecessorSets; }
	/// getter for time successor sets
	const Flowpipe<State>& getFlowpipe() const { return mFlowpipe; }
	/// clear state, i.e., results obtained from computation.
	void clear();

  private:
	void postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets );
	void reverseProcessJumpPredecessors( const JumpSuccessors& guardSatisfyingSets );

  protected:
	const Automaton& mHybridAutomaton;		///< Reference to the rectangular automaton
	const Settings& mSettings;				///< Reference to the used analysis settings
	JumpSuccessors mJumpSuccessorSets;		///< Storage of computed jump successors
	JumpPredecessors mJumpPredecessorSets;	///< Storage of computed jump predecessors
	Flowpipe<State> mFlowpipe;				///< Storage of computed time successors
};

}  // namespace hypro

#include "RectangularWorker.tpp"
