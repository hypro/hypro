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
    using Number = typename Representation::NumberType;
    using RefinementResult = AnalysisResult<UrgencyRefinementSuccess<Representation>, Failure<Representation>>;

    struct RefinePoint {
        ReachTreeNode<Representation>* node = nullptr;
        Transition<Number>* transition = nullptr;
        UrgencyRefinementLevel level = UrgencyRefinementLevel::SETDIFF;
    };

    UrgencyRefinementAnalyzer( HybridAutomaton<Number> const* ha,
                               FixedAnalysisParameters const& fixedParameters,
                               AnalysisParameters const& parameters,
                               UrgencyCEGARSettings const& refinementSettings,
                               std::vector<ReachTreeNode<Representation>>& roots )
        : mHybridAutomaton( ha )
        , mFixedParameters( fixedParameters )
        , mParameters( parameters )
        , mRefinementSettings( refinementSettings )
        , mRoots( &roots ) {}

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
    struct ChildNodeGen;
    bool matchesPathTiming( ReachTreeNode<Representation>* node );
    bool matchesPathTransition( ReachTreeNode<Representation>* node );

    UrgencyRefinementLevel getNextLevel( const UrgencyRefinementLevel& level ) const;

    /**
     * @brief Finds a node and transition to refine on the path from root to the given unsafe node.
     * @param unsafeNode Node with reachable bad states.
     * @return Pair of node and transition to refine.
     */
    auto findRefinementNode( ReachTreeNode<Representation>* unsafeNode )
      -> RefinePoint;

    /**
     * @brief Checks if the refined node already exists as sibling of the unrefined node and creates it otherwise.
     * @param refine Pair of node and transition to refine.
     * @return The node with the new urgent transitions. The node is a sibling of the unrefined node and the flowpipe may or may not already be computed.
     */
    auto refineNode( const RefinePoint& refine )
      -> ReachTreeNode<Representation>*;

    bool suitableForRefinement( const RefinePoint& candidate, ReachTreeNode<Representation>* unsafeNode );

    bool pathUnsafe( ReachTreeNode<Representation>* initialNode, Path<Number> path, std::size_t initialTimeHorizon );

    std::size_t computeHeuristic( Transition<Number>* t, ReachTreeNode<Representation>* node );

    void updateHeuristics( Transition<Number>* t );

  protected:
    std::deque<ReachTreeNode<Representation>*> mWorkQueue;  ///< Queue for nodes in the tree which require processing
    HybridAutomaton<Number> const* mHybridAutomaton;        ///< Hybrid automaton
    FixedAnalysisParameters mFixedParameters;
    AnalysisParameters mParameters;  ///< Used analysis settings
    UrgencyCEGARSettings mRefinementSettings;
    Path<Number> mPath{};
    ReachTreeNode<Representation>* mFailureNode;
    std::vector<ReachTreeNode<Representation>>* mRoots;
    size_t const mMaxSegments = size_t( std::ceil( std::nextafter( carl::convert<tNumber, double>( mFixedParameters.localTimeHorizon / mParameters.timeStep ), std::numeric_limits<double>::max() ) ) );
    std::map<Transition<Number>*, std::size_t> mRefinementCache;
};

}  // namespace hypro

#include "UrgencyRefinementAnalyzer.tpp"
