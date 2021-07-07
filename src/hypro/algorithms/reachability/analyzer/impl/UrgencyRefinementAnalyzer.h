#pragma once
#include "../../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../../datastructures/reachability/ReachTreev2.h"
#include "../../../../types.h"
#include "../../workers/UrgencyWorker.h"
#include "../ReturnTypes.h"

#include <deque>

namespace hypro {

template <class Representation>
struct UrgencyRefinementSuccess {
    std::vector<ReachTreeNode<Representation>*> pathSuccessors{};
};
template <class Representation>
UrgencyRefinementSuccess( std::vector<ReachTreeNode<Representation>*> ) -> UrgencyRefinementSuccess<Representation>;

/**
 * @brief Analyzer implementation for refinement (internal)
 * @tparam Representation
 */
template <typename Representation>
class UrgencyRefinementAnalyzer {
  public:
    using Number = rep_number<Representation>;
    using RefinementResult = AnalysisResult<UrgencyRefinementSuccess<Representation>, Failure<Representation>>;

    struct RefinePoint {
        ReachTreeNode<Representation>* node;
        Transition<Number>* transition;
    };

    UrgencyRefinementAnalyzer( HybridAutomaton<Number> const& ha,
                               FixedAnalysisParameters const& fixedParameters,
                               AnalysisParameters const& parameters,
                               std::vector<ReachTreeNode<Representation>>& roots )
        : mHybridAutomaton( ha )
        , mFixedParameters( fixedParameters )
        , mParameters( parameters )
        , mRoots( roots ) {}

    /**
     * @brief Refinement on a specific path
     * @param path
     * @return REACHABILITY_RESULT
     */
    void setRefinement( ReachTreeNode<Representation>* failureNode ) {
        assert( mWorkQueue.empty() );
        mFailureNode = failureNode;
        mPath = failureNode->getPath();
    }

    RefinementResult run();

  private:
    bool matchesPathTiming( ReachTreeNode<Representation>* node );
    bool matchesPathTransition( ReachTreeNode<Representation>* node );

    /**
     * @brief Finds a node and transition to refine on the path from root to the given unsafe node.
     * @param unsafeNode Node with reachable bad states.
     * @return Pair of node and transition to refine.
     */
    auto findRefinementNode( ReachTreeNode<Representation>* const unsafeNode )
      -> RefinePoint;

    /**
     * @brief Checks if the refined node already exists as sibling of the unrefined node and creates it otherwise.
     * @param refine Pair of node and transition to refine.
     * @return The node with the new urgent transitions. The node is a sibling of the unrefined node and the flowpipe may or may not already be computed.
     */
    auto createRefinedNode( const RefinePoint& refine )
      -> ReachTreeNode<Representation>*;

    /**
     * @brief Computes successors of the guard of the given transition on the given path starting with the given node and returns the safety result.
     * @param start Candidate node for refinement.
     * @param pathToUnsafe path starting from start which is unsafe without refinement.
     * @param refineJump Candidate transition for refinement.
     * @return `true` if successors of the guard is unsafe and `false` otherwise.
     */
    auto guardUnsafe( ReachTreeNode<Representation>* const start, const Path<Number>& pathToUnsafe, Transition<Number>* refineJump )
      -> bool;

  protected:
    std::deque<ReachTreeNode<Representation>*> mWorkQueue;  ///< Queue for nodes in the tree which require processing
    const HybridAutomaton<Number>& mHybridAutomaton;        ///< Hybrid automaton
    FixedAnalysisParameters mFixedParameters;
    AnalysisParameters mParameters;  ///< Used analysis settings
    Path<Number> mPath{};
    ReachTreeNode<Representation>* mFailureNode;
    std::vector<ReachTreeNode<Representation>> mRoots;
};

}  // namespace hypro

#include "UrgencyRefinementAnalyzer.tpp"
