/*
 * Copyright (c) 2023-2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../datastructures/HybridAutomaton/Label.h"
#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../handlers/badStateHandlers/rectangularBadStateHandler.h"
#include "../handlers/guardHandlers/rectangularSyncGuardHandler.h"
#include "../handlers/invariantHandlers/rectangularInvariantHandler.h"
#include "../handlers/jumpHandlers/rectangularJumpHandler.h"
#include "../handlers/jumpHandlers/singularJumpHandler.h"
#include "../handlers/resetHandlers/rectangularResetHandler.h"
#include "../handlers/timeEvolutionHandlers/rectangularTimeEvolutionHandler.h"

#include <vector>

namespace hypro {

/**
 * @brief Class implementing a worker for rectangular automata in analysis with label synchronization.
 * @details A worker implements a method computing a time transition followed by a discrete transition. The repeated calling of a worker allows to implement a complete reachability analysis method.
 * @tparam State
 * @tparam Automaton
 */
template <typename State, typename Automaton>
class RectangularSyncWorker {
  private:
	using Number = typename State::NumberType;
	using LocationT = typename Automaton::LocationType;
	using JumpSuccessors = typename rectangularSyncGuardHandler<State, LocationT>::TransitionStatesMap;
	using JumpPredecessors = typename rectangularSyncGuardHandler<State, LocationT>::TransitionStatesMap;

  public:
	/// constructor from rectangular automaton and settings TODO: delete this constructor
	RectangularSyncWorker( const Automaton& ha, const Settings& settings )
		: mHybridAutomaton( ha )
		, mSettings( settings ) {}

	/// constructor from rectangular automaton, settings and synchronization dictionary
	RectangularSyncWorker( const Automaton& ha, const Settings& settings, std::map<Label, std::set<Automaton const*>>& syncDict, int variablePoolIndex )
		: mHybridAutomaton( ha )
		, mSettings( settings )
		, mSyncDict( syncDict )
		, mVariablePoolIndex( variablePoolIndex )
		, mNonSyncLabels() {
		for ( auto label : mHybridAutomaton.getLabels() ) {
			if ( syncDict.at( label ).size() == 1 && syncDict.at( label ).count( &mHybridAutomaton ) == 1 ) {
				mNonSyncLabels.insert( label );
			}
		}
	}

	/// computes a time transition followed by a discrete transition
	REACHABILITY_RESULT computeForwardReachability( ReachTreeNode<State, LocationT>& task );

	/// computes a time transition
	REACHABILITY_RESULT computeTimeSuccessors( ReachTreeNode<State, LocationT>& task );

	/// computes a discrete transition. Requires available time successors.
	void computeJumpSuccessors( const LocationT* location );

	/// getter for discrete jump successor sets
	const JumpSuccessors& getJumpSuccessorSets() const { return mJumpSuccessorSets; }

	/// getter for time successor sets
	const Flowpipe<State>& getFlowpipe() const { return mFlowpipe; }

	/// clear state, i.e., results obtained from computation.
	void clear();

  private:
	void postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets );

  protected:
	const Automaton& mHybridAutomaton;						  ///< Reference to the rectangular automaton
	const Settings& mSettings;								  ///< Reference to the used analysis settings
	JumpSuccessors mJumpSuccessorSets;						  ///< Storage of computed jump successors
	Flowpipe<State> mFlowpipe;								  ///< Storage of computed time successors
	std::map<Label, std::set<Automaton const*>>& mSyncDict{};  ///< map (label -> automata)
	std::set<Label> mNonSyncLabels{};						  ///< set of labels that are not synchronized, local computation in the subspace
	int mVariablePoolIndex{ 0 };								  ///< index of the variable pool to use in with this worker
};

}  // namespace hypro

#include "RectangularSyncWorker.tpp"
