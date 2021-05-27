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

    struct RefinePoint {
        ReachTreeNode<Representation>* node;
        Transition<Number>* transition;
    };

  public:
    using UrgencyCEGARResult = AnalysisResult<UrgencyCEGARSuccess, Failure<Representation>>;

    UrgencyCEGARAnalyzer( HybridAutomaton<Number> const& ha,
                 FixedAnalysisParameters const& fixedParameters,
                 AnalysisParameters const& parameters,
                 std::vector<ReachTreeNode<Representation>>& roots )
        : mHybridAutomaton( &ha )
        , mFixedParameters( fixedParameters )
        , mParameters( parameters )
        , mRefinementAnalyzer( *mHybridAutomaton, mFixedParameters, mParameters ) {
        for ( auto& root : roots ) {
            mWorkQueue.push_front( &root );
        }
    }

    UrgencyCEGARResult run();

  protected:
    std::deque<ReachTreeNode<Representation>*> mWorkQueue;
    HybridAutomaton<Number> const* mHybridAutomaton;
    FixedAnalysisParameters mFixedParameters;
    AnalysisParameters mParameters;
    RefinementAnalyzer<Representation> mRefinementAnalyzer;
    UrgencyWorker<Representation>* mRefinementWorker;

    size_t const mMaxSegments = size_t( std::ceil( std::nextafter( carl::convert<tNumber, double>( mFixedParameters.localTimeHorizon / mParameters.timeStep ), std::numeric_limits<double>::max() ) ) );

  private:
    auto findRefinementNode( ReachTreeNode<Representation>* const node )
      -> RefinePoint;

    auto checkGuard(
        ReachTreeNode<Representation>* const node, Transition<Number>* trans, const Path<Number>& path )
      -> REACHABILITY_RESULT;

    auto refinePath( const Path<Number>& path, const RefinePoint& refine )
      -> std::pair<bool, RefinePoint>;

    auto refineNode( const RefinePoint& refine )
      -> ReachTreeNode<Representation>*;

    auto createChildNode( const TimedValuationSet<Representation>& jsucc, const Transition<Number>* transition, ReachTreeNode<Representation>* parent )
      -> ReachTreeNode<Representation>*;
};

}  // namespace hypro

#include "UrgencyCEGARAnalyzer.tpp"
