#pragma once
#include "../../workers/LTIWorker.h"
#include "../ReturnTypes.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/reachability/ReachTreev2.h"
#include "types.h"

#include <deque>

namespace hypro {

template <class Representation>
struct RefinementSuccess {
	std::vector<ReachTreeNode<Representation>*> pathSuccessors{};
};
template <class Representation>
RefinementSuccess(std::vector<ReachTreeNode<Representation>*>) -> RefinementSuccess<Representation>;

/**
 * @brief Analyzer implementation for refinement (internal)
 * @tparam Representation
 */
template <typename Representation>
class RefinementAnalyzer {
  public:
	using Number = rep_number<Representation>;
	using RefinementResult = AnalysisResult<RefinementSuccess<Representation>, Failure<Representation>>;

	RefinementAnalyzer( HybridAutomaton<Number> const& ha, Settings const& setting )
		: mHybridAutomaton( ha )
		, mAnalysisSettings( setting ) {}

	/**
	 * @brief Refinement on a specific path
	 * @param path
	 * @return REACHABILITY_RESULT
	 */
	void setRefinement( ReachTreeNode<Representation>* node, Path<Number> path ) {
		assert( mWorkQueue.empty() );
		mWorkQueue.push_front( node );
		mPath = std::move( path );
	}

	RefinementResult run();

	void addToQueue( ReachTreeNode<Representation>* node ) { mWorkQueue.push_front( node ); }

  protected:
	std::deque<ReachTreeNode<Representation>*> mWorkQueue;	///< Queue for nodes in the tree which require processing
	const HybridAutomaton<Number>& mHybridAutomaton;		///< Hybrid automaton
	Settings mAnalysisSettings;								///< Used analysis settings
	Path<Number> mPath{};
};

}  // namespace hypro

#include "RefinementAnalyzer.tpp"
