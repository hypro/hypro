#pragma once

#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../FlowpipeConstructionConvenience.h"
#include "../handlers/badStateHandlers/ltiBadStateHandler.h"
#include "../handlers/guardHandlers/rectangularGuardHandler.h"
#include "../handlers/jumpHandlers/singularJumpHandler.h"
#include "../handlers/resetHandlers/rectangularResetHandler.h"
#include "../handlers/timeEvolutionHandlers/singularTimeEvolutionHandler.h"

#include <vector>

namespace hypro {

/**
 * @brief Class implementing a worker for rectangular automata.
 * @details A worker implements a method computing a time transition followed by a discrete transition. The repeated calling of a worker allows to implement a complete reachability analysis method.
 * @tparam Representation
 */
template <typename Representation>
class SingularWorker {
  private:
	using Number = typename Representation::NumberType;
	using JumpSuccessors = typename rectangularGuardHandler<Representation>::TransitionStatesMap;
	using JumpPredecessors = typename rectangularGuardHandler<Representation>::TransitionStatesMap;

  public:
	/// constructor from rectangular automaton and settings
	SingularWorker( const HybridAutomaton<Number>& ha, const FixedAnalysisParameters& settings )
		: mHybridAutomaton( ha )
		, mSettings( settings ) {}
	/// computes a time transition followed by a discrete transition
	REACHABILITY_RESULT computeForwardReachability( const ReachTreeNode<Representation>& task );
	/// computes a time transition
	REACHABILITY_RESULT computeTimeSuccessors( const ReachTreeNode<Representation>& task );
	/// computes a discrete transition. Requires available time successors.
	void computeJumpSuccessors( const ReachTreeNode<Representation>& task );
	/// getter for discrete jump successor sets
	REACHABILITY_RESULT computeBackwardReachability( const ReachTreeNode<Representation>& task );
	REACHABILITY_RESULT computeTimePredecessors( const ReachTreeNode<Representation>& task );
	void computeJumpPredecessors();
	const JumpSuccessors& getJumpSuccessorSets() const { return mJumpSuccessorSets; }
	const JumpSuccessors& getJumpPredecessorSets() const { return mJumpPredecessorSets; }
	/// getter for time successor sets
	const Flowpipe<Representation>& getFlowpipe() const { return mFlowpipe; }
	/// resets all stored items
	void reset() {
		mJumpSuccessorSets.clear();
		mJumpPredecessorSets.clear();
		mFlowpipe.clear();
	}

  private:
	void postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets );
	void reverseProcessJumpPredecessors( const JumpSuccessors& guardSatisfyingSets );

  protected:
	const HybridAutomaton<Number>& mHybridAutomaton;  ///< Reference to the singular automaton
	const FixedAnalysisParameters& mSettings;		  ///< Reference to the used analysis settings
	JumpSuccessors mJumpSuccessorSets;				  ///< Storage of computed jump successors
	JumpPredecessors mJumpPredecessorSets;			  ///< Storage of computed jump predecessors
	Flowpipe<Representation> mFlowpipe;				  ///< Storage of computed time successors
};

}  // namespace hypro

#include "SingularWorker.tpp"
