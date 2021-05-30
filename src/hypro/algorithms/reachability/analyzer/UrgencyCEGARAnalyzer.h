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
    auto findRefinementNode( ReachTreeNode<Representation>* const node )
      -> RefinePoint;

    auto guardUnsafe( ReachTreeNode<Representation>* const start, const Path<Number>& pathToUnsafe, Transition<Number>* refineJump )
      -> bool;

    auto refinePath( ReachTreeNode<Representation>* refinedNode, const Path<Number>& path, std::size_t initialTimeHorizon )
      -> RefinementResult;

    auto createRefinedNode( const RefinePoint& refine )
      -> ReachTreeNode<Representation>*;

    auto createChildNode( const TimedValuationSet<Representation>& jsucc, const Transition<Number>* transition, ReachTreeNode<Representation>* parent )
      -> ReachTreeNode<Representation>*;
};

}  // namespace hypro

#include "UrgencyCEGARAnalyzer.tpp"
