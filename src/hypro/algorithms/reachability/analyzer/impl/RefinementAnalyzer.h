#pragma once
#include "../../workers/LTIWorker.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/reachability/ReachTreev2.h"
#include "types.h"

#include <queue>

namespace hypro {

/**
 * @brief Analyzer implementation for refinement (internal)
 * @tparam Representation
 */
template <typename Representation>
class RefinementAnalyzer {
	using Number = typename Representation::NumberType;

  public:
	RefinementAnalyzer() = delete;
	RefinementAnalyzer( const RefinementAnalyzer& other ) = delete;

	/**
	 * @brief Construct a new Refinement Analyzer object
	 * @param ha
	 * @param setting
	 */
	RefinementAnalyzer( const HybridAutomaton<Number>& ha, const Settings& setting )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting )
		, mRoots() {
	}

	/**
	 * @brief Starts forward reachability analysis
	 * @return REACHABILITY_RESULT
	 */
	REACHABILITY_RESULT run();

	/**
	 * @brief Refinement on a specific path
	 * @param path
	 * @return REACHABILITY_RESULT
	 */
	REACHABILITY_RESULT run( const Path<Number, SegmentInd>& path );

	/**
	 * @brief Get the computed flowpipes
	 * @return const std::vector<Representation>&
	 */
	const std::vector<Representation>& getFlowpipes() const { return mFlowpipes; }

  protected:
	std::queue<ReachTreeNode<Representation>*> mWorkQueue;	///< Queue for nodes in the tree which require processing
	std::list<std::vector<Representation>> mFlowpipes;		///< Computed flowpipe segments
	const HybridAutomaton<Number>& mHybridAutomaton;		///< Hybrid automaton
	Settings mAnalysisSettings;								///< Used analysis settings
	std::vector<ReachTreeNode<Representation>> mRoots{};	///< Root nodes of the internal reachability tree
};

}  // namespace hypro

#include "RefinementAnalyzer.tpp"
