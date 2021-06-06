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
template <typename Representation>
class SingularAnalyzer {
	using Number = typename Representation::NumberType;

  public:
	using SingularResult = AnalysisResult<VerificationSuccess, Failure<Representation>>;

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
	SingularAnalyzer( HybridAutomaton<Number> const& ha,
					  FixedAnalysisParameters const& fixedParameters,
					  std::vector<ReachTreeNode<Representation>>& roots )
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
	HybridAutomaton<Number> const* mHybridAutomaton;		 ///< Automaton which is analyzed
	FixedAnalysisParameters mAnalysisSettings;				 ///< Settings used for analysis
	std::vector<ReachTreeNode<Representation>>& mReachTree;	 ///< Forest of ReachTrees computed
	std::deque<ReachTreeNode<Representation>*> mWorkQueue;	 ///< Queue holds all nodes that require processing
};

}  // namespace hypro

#include "SingularAnalyzer.tpp"
