#pragma once
#include "../../workers/LTIWorker.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/reachability/ReachTreev2.h"
#include "types.h"

#include <deque>

namespace hypro {

/**
 * @brief Analyzer implementation for refinement (internal)
 * @tparam Representation
 */
template <typename Representation>
class RefinementAnalyzer {
	using Number = typename Representation::NumberType;

  public:
	RefinementAnalyzer( HybridAutomaton<Number> const& ha, Settings const& setting, ReachTreeNode<Representation>& root, Path<Number> path )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting )
		, mPath( path ) {
		mWorkQueue.push_front( &root );
	}

	/**
	 * @brief Refinement on a specific path
	 * @param path
	 * @return REACHABILITY_RESULT
	 */
	std::pair<REACHABILITY_RESULT, ReachTreeNode<Representation>*> run();

	std::deque<ReachTreeNode<Representation>*> const& workQueue() { return mWorkQueue; }

  protected:
	std::deque<ReachTreeNode<Representation>*> mWorkQueue;	///< Queue for nodes in the tree which require processing
	const HybridAutomaton<Number>& mHybridAutomaton;		///< Hybrid automaton
	Settings mAnalysisSettings;								///< Used analysis settings
	Path<Number> mPath{};
};

}  // namespace hypro

#include "RefinementAnalyzer.tpp"
