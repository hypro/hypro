#pragma once

#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../handlers/badStateHandlers/rectangularBadStateHandler.h"
#include "../handlers/guardHandlers/rectangularGuardHandler.h"
#include "../handlers/invariantHandlers/rectangularInvariantHandler.h"
#include "../handlers/jumpHandlers/rectangularJumpHandler.h"
#include "../handlers/resetHandlers/rectangularResetHandler.h"
#include "../handlers/timeEvolutionHandlers/rectangularTimeEvolutionHandler.h"

#include <vector>

namespace hypro {

/**
 * @brief Class implementing a worker for rectangular automata.
 * @details A worker implements a method computing a time transition followed by a discrete transition. The repeated calling of a worker allows to implement a complete reachability analysis method.
 * @tparam State
 */
template <typename State>
class RectangularWorker {
  private:
	using Number = typename State::NumberType;
	using JumpSuccessors = typename rectangularGuardHandler<State>::TransitionStatesMap;
	using JumpPredecessors = typename rectangularGuardHandler<State>::TransitionStatesMap;

  public:
	/// constructor from rectangular automaton and settings
	RectangularWorker( const HybridAutomaton<Number>& ha, const Settings& settings )
		: mHybridAutomaton( ha )
		, mSettings( settings ) {}
	/// computes a time transition followed by a discrete transition
	REACHABILITY_RESULT computeForwardReachability( const ReachTreeNode<State>& task );
	/// computes a time transition
	REACHABILITY_RESULT computeTimeSuccessors( const ReachTreeNode<State>& task );
	/// computes a discrete transition. Requires available time successors.
	void computeJumpSuccessors();
	/// getter for discrete jump successor sets
	REACHABILITY_RESULT computeBackwardReachability( const ReachTreeNode<State>& task );
	REACHABILITY_RESULT computeTimePredecessors( const ReachTreeNode<State>& task );
	void computeJumpPredecessors();
	const JumpSuccessors& getJumpSuccessorSets() const { return mJumpSuccessorSets; }
	const JumpSuccessors& getJumpPredecessorSets() const { return mJumpPredecessorSets; }
	/// getter for time successor sets
	const Flowpipe<State>& getFlowpipe() const { return mFlowpipe; }

  private:
	void postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets );
	void reverseProcessJumpPredecessors( const JumpSuccessors& guardSatisfyingSets );

  protected:
	const HybridAutomaton<Number>& mHybridAutomaton;  ///< Reference to the rectangular automaton
	const Settings& mSettings;						  ///< Reference to the used analysis settings
	JumpSuccessors mJumpSuccessorSets;				  ///< Storage of computed jump successors
	JumpPredecessors mJumpPredecessorSets;			  ///< Storage of computed jump predecessors
	Flowpipe<State> mFlowpipe;						  ///< Storage of computed time successors
};

}  // namespace hypro

#include "RectangularWorker.tpp"
