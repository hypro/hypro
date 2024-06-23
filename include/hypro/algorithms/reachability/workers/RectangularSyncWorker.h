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
#include "../handlers/jumpHandlers/rectangularSyncJumpHandler.h"
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
	/// constructor from rectangular automaton and settings
	RectangularSyncWorker( const Automaton& ha, const Settings& settings )
		: mHybridAutomaton( ha )
		, mSettings( settings ) {}

	/// constructor from rectangular automaton, settings and synchronization dictionary
	RectangularSyncWorker( const Automaton& ha, const Settings& settings, int variablePoolIndex )
		: mHybridAutomaton( ha )
		, mSettings( settings )
		, mVariablePoolIndex( variablePoolIndex ) {}

	/// computes a time transition followed by a discrete transition
	REACHABILITY_RESULT computeForwardReachability( ReachTreeNode<State, LocationT>& task );

	/// computes a time transition
	REACHABILITY_RESULT computeTimeSuccessors( ReachTreeNode<State, LocationT>& task );

	/// computes a discrete transition. Requires available time successors.
	void computeJumpSuccessors( ReachTreeNode<State, LocationT>& task );

	/// getter for discrete jump successor sets
	const JumpSuccessors& getJumpSuccessorSets() const { return mJumpSuccessorSets; }

	/// getter for discrete synchronizing jump successor sets
	const std::set<ReachTreeNode<State, LocationT>*> getSyncJumpSuccessorTasks();

	/// getter for time successor sets
	const Flowpipe<State>& getFlowpipe() const { return mFlowpipe; }

	/// clear state, i.e., results obtained from computation.
	void clear();

	/// change to variable pool that is used in this worker
	void changeVariablePool() { hypro::VariablePool::getInstance().changeToPool( mVariablePoolIndex ); }

	/// set the syncDict2
	void setSyncDict(std::map<Label, std::set<RectangularSyncWorker<State, Automaton>* >>& syncDict2) { mSyncDict = syncDict2; }

	/// initialize the set of labels that do not require synchronization
	void initNonSyncLabels();

	// getter for VariablePoolIndex
	int getVariablePoolIndex() const { return mVariablePoolIndex; }

	// getter for the average size of the search space
	float getAverageSizeOfSearchSpace() const { return std::accumulate(mSizeOfSyncSearchSpace.begin(), mSizeOfSyncSearchSpace.end(), 0)*1.0 / mSizeOfSyncSearchSpace.size(); }

	bool isSearchSpaceEmpty() const { return mSizeOfSyncSearchSpace.empty(); }

  private:
	void postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets );

	void postProcessSyncJumpSuccessors( ReachTreeNode<State, LocationT>& task, const JumpSuccessors& guardSatisfyingSets );

	std::multimap<ReachTreeNode<State, typename Automaton::LocationType>*, State> findSyncSuccessors( ReachTreeNode<State, LocationT>& task, Transition<LocationT> transition, const std::vector<Label>& label, State syncTime, std::set<RectangularSyncWorker<State, Automaton>*> visitedWorkers );

	std::multimap<ReachTreeNode<State, LocationT>*, Transition<LocationT>> getCandidateNodes( ReachTreeNode<State, LocationT>& syncNode, const std::vector<Label>& label );

  protected:
	const Automaton& mHybridAutomaton;						  ///< Reference to the rectangular automaton
	const Settings& mSettings;								  ///< Reference to the used analysis settings
	JumpSuccessors mJumpSuccessorSets;						  ///< Storage of computed jump successors
	JumpSuccessors mSyncJumpSuccessorSets;					  ///< Storage of computed jump successors with synchronization
	Flowpipe<State> mFlowpipe;								  ///< Storage of computed time successors
	std::set<Label> mNonSyncLabels{};						  ///< set of labels that are not synchronized, local computation in the subspace
	int mVariablePoolIndex{ 0 };								  ///< index of the variable pool to use in with this worker
	std::map<Label, std::set<RectangularSyncWorker<State, Automaton>* >> mSyncDict{};  ///< map (label -> workers)
	std::set<ReachTreeNode<State, LocationT>*> mSyncChildrenToRemove{}; ///< elements of this set need to be removed from the reach tree, after a synchronizing jump has been computed. 
	std::vector<int> mSizeOfSyncSearchSpace{};
};

}  // namespace hypro

#include "RectangularSyncWorker.tpp"
