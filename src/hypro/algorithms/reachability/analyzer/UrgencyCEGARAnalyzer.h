#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../types.h"
#include "../workers/UrgencyWorker.h"
#include "./ReturnTypes.h"
#include "./impl/RefinementAnalyzer.h"

#include <queue>

namespace hypro {

struct UrgencyCEGARSuccess {};

template <typename Representation>
class UrgencyCEGARAnalyzer {
    using Number = typename Representation::NumberType;
    using RefinementResult = typename RefinementAnalyzer<Representation>::RefinementResult;

    struct RefinePoint {
        ReachTreeNode<Representation>* node;
        Transition<Number>* transition;
    };

  public:
    using UrgencyCEGARResult = AnalysisResult<UrgencyCEGARSuccess, Failure<Representation>>;

    UrgencyCEGARAnalyzer( HybridAutomaton<Number> const& ha,
                 FixedAnalysisParameters const& fixedParameters,
                 AnalysisParameters const& parameters )
        : mHybridAutomaton( &ha )
        , mFixedParameters( fixedParameters )
        , mParameters( parameters )
        , mRoots( makeRoots<Representation>( ha ) ) {
        for ( auto& root : mRoots ) {
            mWorkQueue.push_front( &root );
        }
    }

    UrgencyCEGARResult run();
    std::vector<ReachTreeNode<Representation>>& getRoots() { return mRoots; }

  protected:
    std::deque<ReachTreeNode<Representation>*> mWorkQueue;
    HybridAutomaton<Number> const* mHybridAutomaton;
    FixedAnalysisParameters mFixedParameters;
    AnalysisParameters mParameters;
    UrgencyWorker<Representation>* mRefinementWorker;
    std::vector<ReachTreeNode<Representation>> mRoots;

    size_t const mMaxSegments = size_t( std::ceil( std::nextafter( carl::convert<tNumber, double>( mFixedParameters.localTimeHorizon / mParameters.timeStep ), std::numeric_limits<double>::max() ) ) );

  private:
    /**
     * @brief Creates a new child node of parent with the given initial set.
     * @param jsucc Contains the initial set and the jump timing offset.
     * @param transition The taken discrete jump from the parent.
     * @param parent The parent node of the new node.
     * @return The newly created node.
     */
    auto createChildNode( const TimedValuationSet<Representation>& jsucc, const Transition<Number>* transition, ReachTreeNode<Representation>* parent )
      -> ReachTreeNode<Representation>*;

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

    /**
     * @brief Computes the reachable states on the given path. The initial node can have urgent transitions and may only use a limited time horizon.
     * @param refinedNode Start of the path with urgent transitions for refinement.
     * @param path Path to verify safety on.
     * @param initialTimeHorizon Bound on the time horizon in the start node. All successors use the full time horizon.
     * @return A new unsafe node if safety was not verifier or the jump successors of the path.
     */
    auto refinePath( ReachTreeNode<Representation>* refinedNode, const Path<Number>& path, std::size_t initialTimeHorizon )
      -> RefinementResult;
};

}  // namespace hypro

#include "UrgencyCEGARAnalyzer.tpp"
