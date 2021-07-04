#pragma once

#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../handlers/badStateHandlers/stochasticRectangularBadStateHandler.h"
#include "../handlers/guardHandlers/stochasticRectangularGuardHandler.h"
#include "../handlers/invariantHandlers/rectangularInvariantHandler.h"
#include "../handlers/jumpHandlers/stochasticRectangularJumpHandler.h"
#include "../handlers/resetHandlers/rectangularResetHandler.h"
#include "../handlers/timeEvolutionHandlers/rectangularTimeEvolutionHandler.h"
#include "../handlers/probabilityHandlers/stochasticRectangularProbabilityHandler.h"
#include "../handlers/resetHandlers/StochasticRectangularResetHandler.h"

#include <vector>

namespace hypro {

/**
 * @brief Class implementing a worker for rectangular automata.
 * @details A worker implements a method computing a time transition followed by a discrete transition. The repeated calling of a worker allows to implement a complete reachability analysis method.
 * @tparam State
 */
template <typename State>
class StochasticRectangularWorker {
  private:
	using Number = typename State::NumberType;
	using JumpSuccessors = std::map<StochasticTransition<Number>*, std::vector<State>>;
	using JumpSuccPairs = std::map<StochasticTransition<Number>*, std::vector<std::pair<State, REACHABILITY_RESULT>>>;
	using JumpPredecessors = std::map<StochasticTransition<Number>*, std::vector<State>>;
	using JumpPrePairs = std::map<StochasticTransition<Number>*, std::vector<std::pair<State, REACHABILITY_RESULT>>>;
	using StatePair = std::vector<std::pair<State, State>>;
	using StateProb = std::pair<State, Number>;
	using TranStateProb = std::vector<std::pair<StochasticTransition<Number>*,std::pair<State, Number>>>;

  public:
	/// constructor from rectangular automaton and settings
	StochasticRectangularWorker( const StochasticHybridAutomaton<Number>& ha, const Settings& settings )
		: mHybridAutomaton( ha )
		, mSettings( settings ) {}
	/// computes a time transition followed by a discrete transition
	void computeForwardReachability( const ReachTreeNode<State>& task );
	/// computes a time transition
	void computeTimeSuccessors( const ReachTreeNode<State>& task );
	/// computes a discrete transition. Requires available time successors.
	void computeJumpSuccessors();
	/// getter for discrete jump successor sets
	void computeBackwardReachability( State badSet, const ReachTreeNode<State>& task, StochasticTransition<Number>* transition, Number pro, State preStateSet );
	void computeBackwardReachabilityProb( const ReachTreeNode<State>& task, Number pro );
	State computeTimePredecessors( const State& badSet );
	void computeJumpPredecessors();
	State computeTimePredecessorsProb( const ReachTreeNode<State>& task, Number prob );
	void computeJumpPredecessorsProb();
	const JumpSuccPairs& getJumpSuccessorSets() const { return mJumpSuccessorSets; }
	const JumpPredecessors& getJumpPredecessorSets() const { return mJumpPredecessorSets; }
	carl::Interval<Number> timeInterval( const State& preStateSet, State& state, const rectangularFlow<Number>& flow, StochasticTransition<Number>* transitionPtr );
	/// getter for time successor sets
	const Flowpipe<State>& getFlowpipe() const { return mFlowpipe; }
	const StatePair& getPrdecessor() const { return mPredecessor; }
	const StateProb& getProbability() const { return mProbability; }
	const TranStateProb& getTranStateProb() const { return mTranStateProb; }

  private:
	void postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets );
	State reverseProcessJumpPredecessors( State& state, StochasticTransition<Number>* transitionPtr );
	void reverseProcessJumpPredecessorsProb( const JumpSuccessors& guardSatisfyingSets );

  protected:
	const StochasticHybridAutomaton<Number>& mHybridAutomaton;  ///< Reference to the rectangular automaton
	const Settings& mSettings;						  ///< Reference to the used analysis settings
	JumpSuccPairs mJumpSuccessorSets;				  ///< Storage of computed jump successors
	JumpPredecessors mJumpPredecessorSets;			  ///< Storage of computed jump predecessors
	JumpPrePairs mJumpPreSets;
	Flowpipe<State> mFlowpipe;						  ///< Storage of computed time successors
	StatePair mPredecessor;
	StateProb mProbability;
	TranStateProb mTranStateProb;
};

}  // namespace hypro

#include "StochasticRectangularWorker.tpp"
