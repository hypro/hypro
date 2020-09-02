#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
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
template <typename Representation>
class SingularAnalyzer {
	using Number = typename Representation::NumberType;

  public:
	using SingularResult = AnalysisResult<SingularSuccess, Failure<Representation>>;

	/**
	 * @brief      Default constructor (deleted).
	 */
	SingularAnalyzer() = delete;

	/**
	 * @brief      Constructor from automaton and analysis settings.
	 */
	SingularAnalyzer( const HybridAutomaton<Number>& ha, const Settings& setting )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting )
		, mReachTree() {
	}
	/**
	 * @brief      Main method for reachability analysis. Calls the method @ref forwardRun.
	 * @return     SAFE if no bad state intersection is found and UNKNOWN otherwise.
	 */
	REACHABILITY_RESULT run();

	/**
	 * @brief      Execute forward reachability result.
	 * @return     SAFE if no bad state intersection is found and UNKNOWN otherwise.
	 */
	REACHABILITY_RESULT forwardRun();

	/**
	 * @brief      Get the computed flowpipes.
	 * @return     A vector holding the already computed flowpipes.
	 */
	const std::vector<Flowpipe<Representation>>& getFlowpipes() const { return mFlowpipes; }

  protected:
	std::queue<ReachTreeNode<Representation>*> mWorkQueue;					 ///< Queue holds all nodes that require processing
	std::vector<Flowpipe<Representation>> mFlowpipes;						 ///< Storage for already computed flowpipes
	HybridAutomaton<Number> mHybridAutomaton;								 ///< Automaton which is analyzed
	Settings mAnalysisSettings;												 ///< Settings used for analysis
	std::vector<std::unique_ptr<ReachTreeNode<Representation>>> mReachTree;	 ///< Forest of ReachTrees computed
};

}  // namespace hypro

#include "SingularAnalyzer.tpp"
