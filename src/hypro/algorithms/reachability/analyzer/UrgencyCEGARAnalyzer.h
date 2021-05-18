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
        , mParameters( parameters ) {
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

  private:
    auto findRefinementNode( const ReachTreeNode<Representation>* node )
      -> RefinePoint;

    auto refinePath( const Path<Number>& path, const RefinePoint& refine )
      -> std::pair<bool, RefinePoint>;

    auto refineNode( const RefinePoint& refine )
      -> ReachTreeNode<Representation>*;

    auto createChildNode( const TimedValuationSet<Representation>& jsucc, Transition<Number>* transition, ReachTreeNode<Representation>* parent )
      -> ReachTreeNode<Representation>*;
};

}  // namespace hypro

#include "UrgencyCEGARAnalyzer.tpp"
