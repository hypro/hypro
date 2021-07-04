#pragma once
//#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/HybridAutomaton/StochasticHybridAutomaton.h"
#include "../../../types.h"
#include "../workers/StochasticRectangularWorker.h"

#include <queue>

namespace hypro {
/**
 * @brief Class which implements a forward reachability analysis method for rectangular automata
 * @details Requires the usage of a suitable state set representation, e.g., carlPolytope.
 * @tparam State
 */
template <typename State>
class StochasticRectangularAnalyzer {
	using Number = typename State::NumberType;
	using ProbMapping = std::map<State*,Number>;
	using ProbNodeMapping = std::map<ReachTreeNode<State>*,Number>;
	using NodeTransitionPair = std::map<ReachTreeNode<State>*, StochasticTransition<Number>*>;
	using StatePair = std::vector<std::pair<Number,State>>;
	using NodeStatePair = std::map<ReachTreeNode<State>*, State>;

  public:
	/// default constructor (deleted)
	StochasticRectangularAnalyzer() = delete;
	/// constructor from automaton and settings
	StochasticRectangularAnalyzer( const StochasticHybridAutomaton<Number>& ha, const Settings& setting )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting )
		, mReachTree() {
	}
	/// main method for reachability analysis
	void forAndBackwardRun();
	void onlyBackwardRun();
	void forwardRun();
	void backwardRun();
	void backwardAnalysisRun();
	/// getter for computed flowpipes
	const std::vector<Flowpipe<State>>& getFlowpipes() const { return mFlowpipes; }
	const std::vector<ReachTreeNode<State>*>& getUnsafeNodes() const { return mUnsafeNodes; }

  protected:
	std::queue<ReachTreeNode<State>*> mWorkQueue;					///< Queue holds all nodes that require processing
	std::vector<Flowpipe<State>> mFlowpipes;						///< Storage for already computed flowpipes
	StochasticHybridAutomaton<Number> mHybridAutomaton;						///< Automaton which is analyzed
	Settings mAnalysisSettings;										///< Settings used for analysis
	std::vector<std::unique_ptr<ReachTreeNode<State>>> mReachTree;	///< Forest of ReachTrees computed
	std::vector<ReachTreeNode<State>*> mUnsafeNodes;                 ///< Storage of unsafe states
	ProbMapping mStateProbs;										///< Storage of state probability
	ProbNodeMapping mNodeProbs;
	NodeTransitionPair mNodeTrans;									///< Storage of node and transition pair
	NodeStatePair mNodePreState;									///< Storage of predecessor state
};

}  // namespace hypro

#include "StochasticRectangularAnalyzer.tpp"
