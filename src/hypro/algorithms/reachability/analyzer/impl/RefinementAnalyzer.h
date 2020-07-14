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
	RefinementAnalyzer( HybridAutomaton<Number> const& ha, Settings const& setting )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting ) {}

	/**
	 * @brief Refinement on a specific path
	 * @param path
	 * @return REACHABILITY_RESULT
	 */
	std::pair<REACHABILITY_RESULT, ReachTreeNode<Representation>*> run();

	std::deque<ReachTreeNode<Representation>*> const& workQueue() { return mWorkQueue; }
	void addToQueue( ReachTreeNode<Representation>* node ) { mWorkQueue.push_front( node ); }

	void setPath( Path<Number> path ) { mPath = path; }

  protected:
	std::deque<ReachTreeNode<Representation>*> mWorkQueue;	///< Queue for nodes in the tree which require processing
	const HybridAutomaton<Number>& mHybridAutomaton;		///< Hybrid automaton
	Settings mAnalysisSettings;								///< Used analysis settings
	Path<Number> mPath{};
};

}  // namespace hypro

#include "RefinementAnalyzer.tpp"
