#pragma once
#include "../../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../../datastructures/reachability/ReachTreev2.h"
#include "../../../../types.h"
#include "../../workers/LTIWorker.h"
#include "../ReturnTypes.h"

#include <deque>

namespace hypro {

template <class Representation, class Location>
struct RefinementSuccess {
	static_assert( is_location_type<Location>() );
	std::vector<ReachTreeNode<Representation, Location>*> pathSuccessors{};
};
template <class Representation, class Location>
RefinementSuccess( std::vector<ReachTreeNode<Representation, Location>*> ) -> RefinementSuccess<Representation, Location>;

/**
 * @brief Analyzer implementation for refinement (internal)
 * @tparam Representation
 */
template <typename Representation, typename Automaton>
class RefinementAnalyzer {
  public:
	using Number = rep_number<Representation>;
	using LocationType = typename Automaton::LocationType;
	using RefinementResult = AnalysisResult<RefinementSuccess<Representation, LocationType>, Failure<Representation, LocationType>>;

	RefinementAnalyzer( Automaton const& ha,
						FixedAnalysisParameters const& fixedParameters,
						AnalysisParameters const& parameters )
		: mHybridAutomaton( ha )
		, mFixedParameters( fixedParameters )
		, mParameters( parameters ) {}

	/**
	 * @brief Refinement on a specific path
	 * @param path
	 * @return REACHABILITY_RESULT
	 */
	void setRefinement( ReachTreeNode<Representation, LocationType>* node, Path<Number, LocationType> path ) {
		assert( mWorkQueue.empty() );
		mWorkQueue.push_front( node );
		mPath = std::move( path );
	}

	RefinementResult run();

	void addToQueue( ReachTreeNode<Representation, LocationType>* node ) {
		// add node if it's past the end of the path or otherwise matches the path
		if ( node->getDepth() > mPath.elements.size() || ( matchesPathTiming( node ) && matchesPathTransition( node ) ) ) {
			mWorkQueue.push_front( node );
		}
	}

	void addPastPath( ReachTreeNode<Representation, LocationType>* node ) {
		mWorkQueue.push_front( node );
	}

  private:
	bool matchesPathTiming( ReachTreeNode<Representation, LocationType>* node );
	bool matchesPathTransition( ReachTreeNode<Representation, LocationType>* node );

  protected:
	std::deque<ReachTreeNode<Representation, LocationType>*> mWorkQueue;  ///< Queue for nodes in the tree which require processing
	const HybridAutomaton<Number>& mHybridAutomaton;					  ///< Hybrid automaton
	FixedAnalysisParameters mFixedParameters;
	AnalysisParameters mParameters;	 ///< Used analysis settings
	Path<Number, LocationType> mPath{};
};

}  // namespace hypro

#include "RefinementAnalyzer.tpp"
