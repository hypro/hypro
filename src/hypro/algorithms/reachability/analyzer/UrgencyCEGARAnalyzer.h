#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../types.h"
#include "../workers/UrgencyWorker.h"
#include "./ReturnTypes.h"

#include <queue>

namespace hypro {

struct UrgencyCEGARSuccess {};

template <typename Representation>
class UrgencyCEGARAnalyzer {
    using Number = typename Representation::NumberType;

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
    auto findRefinementNode( ReachTreeNode<Representation>* node )
      -> std::pair<ReachTreeNode<Representation>*, Transition<Number>*>;

    auto refinePath( Path<Number> path, ReachTreeNode<Representation>* refineNode, Transition<Number>* refineTrans )
      -> std::tuple<bool, ReachTreeNode<Representation>*, Transition<Number>*>;
};

}  // namespace hypro

#include "UrgencyCEGARAnalyzer.tpp"
