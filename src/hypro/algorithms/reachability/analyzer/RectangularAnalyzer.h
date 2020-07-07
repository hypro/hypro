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
template <typename State>
class RectangularAnalyzer {
	using Number = typename State::NumberType;

  public:
	/// default constructor (deleted)
	RectangularAnalyzer() = delete;
	/// constructor from automaton and settings
	RectangularAnalyzer( const HybridAutomaton<Number>& ha, const Settings& setting )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting )
		, mReachTree() {
	}
	/// main method for reachability analysis
	REACHABILITY_RESULT run();
	/// getter for computed flowpipes
	const std::vector<Flowpipe<State>>& getFlowpipes() const { return mFlowpipes; }

  protected:
	std::queue<ReachTreeNode<State>*> mWorkQueue;					///< Queue holds all nodes that require processing
	std::vector<Flowpipe<State>> mFlowpipes;						///< Storage for already computed flowpipes
	HybridAutomaton<Number> mHybridAutomaton;						///< Automaton which is analyzed
	Settings mAnalysisSettings;										///< Settings used for analysis
	std::vector<std::unique_ptr<ReachTreeNode<State>>> mReachTree;	///< Forest of ReachTrees computed
};

}  // namespace hypro

#include "RectangularAnalyzer.tpp"
