#pragma once
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../types.h"
#include "../workers/SingularWorker.h"
#include "../workers/LTIWorker.h"
#include "../workers/RectangularWorker.h"
#include "./ReturnTypes.h"
#include "./DecompositionalUtil.h"

#include <queue>


namespace hypro {
namespace detail {

// Visitors to call worker functions
template <typename Representation>
struct resetWorkerVisitor {
    void operator()( SingularWorker<Representation>& worker ) {
        worker.reset();
    }
    void operator()( RectangularWorker<Representation>& ) {
        // worker.reset();
    }
    void operator()( LTIWorker<Representation>& ) {
        return;
    }
};

template <typename Representation>
struct computeTimeSuccessorVisitor {
  using Number = typename Representation::NumberType;
  ReachTreeNode<Representation>* task;
  tNumber fixedTimeStep;
  tNumber timeStep;
    // return time interval covered by the time successors
    carl::Interval<Number> operator()( SingularWorker<Representation>& worker ) {
        worker.computeTimeSuccessors( *task, false );
        auto& flowpipe = task->getFlowpipe();
        flowpipe.insert( flowpipe.begin(), worker.getFlowpipe().begin(), worker.getFlowpipe().end() );
        // the second segment covers the entire time interval
        if ( flowpipe.size() == 0 ) {
            // invariant is initially violated
            return carl::Interval<Number>::emptyInterval();
        }
        assert( flowpipe.size() == 2 );
        // last variable is the clock
        return getTimeInterval( flowpipe[1], flowpipe[1].dimension() - 1 );
    }
    carl::Interval<Number> operator()( LTIWorker<Representation>& worker ) {
        worker.computeTimeSuccessors( task->getInitialSet(), task->getLocation(), std::back_inserter( task->getFlowpipe() ), false );
        auto& flowpipe = task->getFlowpipe();
        assert( flowpipe.size() > 0 );
        // get global time interval
        Number timeLower = carl::convert<tNumber, Number>( task->getTimings().lower()*fixedTimeStep );
        Number timeUpper = carl::convert<tNumber, Number>( task->getTimings().upper()*fixedTimeStep + flowpipe.size()*timeStep );
        return carl::Interval<Number>( timeLower , timeUpper );
    }
    carl::Interval<Number> operator()( RectangularWorker<Representation>& ) {
        // Todo: rectangular worker. Should be very similar to singular case
        return carl::Interval<Number>::emptyInterval();
    }
};

template <typename Representation>
struct computeSingularJumpSuccessorVisitor {
  ReachTreeNode<Representation>* task;
    void operator()( SingularWorker<Representation>& worker ) {
        worker.computeJumpSuccessors( *task );
    }
    void operator()( RectangularWorker<Representation>& ) {
        // todo
        return;
    }
    void operator()( LTIWorker<Representation>& ) {
        assert( false && "Singular jump successor computation called for lti subspace." );
    }
};

template <typename Representation>
struct getSingularJumpSuccessorVisitor {
  using Number = typename Representation::NumberType;
  Transition<Number>* transition;
    Representation operator()( SingularWorker<Representation>& worker ) {
        auto it = worker.getJumpSuccessorSets().find( transition );
        if ( it != worker.getJumpSuccessorSets().end() ) {
            auto successorList = it->second;
            // size 2 if initial set intersects guard, else 1. Either way, only need the last (jump with full flowpipe)
            assert( successorList.size() == 1 || successorList.size() == 2 );
            return successorList.size() == 1 ? successorList[ 0 ] : successorList[ 1 ];
        }
        else {
            return Representation::Empty();
        }
    }
    Representation operator()( RectangularWorker<Representation>& ) {
        //todo
        return Representation::Empty();
    }
    Representation operator()( LTIWorker<Representation>& ) {
        assert( false && "Singular jump successor getter called for lti subspace." );
        return Representation::Empty();
    }
};

template <typename Representation>
struct getLtiJumpSuccessorVisitor {
  using Number = typename Representation::NumberType;
  Transition<Number>* transition;
  std::vector<IndexedValuationSet<Representation>> guardEnabledSets;
    std::vector<TimedValuationSet<Representation>> operator()( SingularWorker<Representation>& ) {
        assert( false );
        return std::vector<TimedValuationSet<Representation>>();
    }
    std::vector<TimedValuationSet<Representation>> operator()( RectangularWorker<Representation>& ) {
        assert( false );
        return std::vector<TimedValuationSet<Representation>>();
    }
    std::vector<TimedValuationSet<Representation>> operator()( LTIWorker<Representation>& worker ) {
        return worker.computeJumpSuccessorsForGuardEnabled( guardEnabledSets, transition );
    }
};

} // namespace detail

// indicates that the analysis succeeded, i.e. no intersection with bad states
struct DecompositionalSuccess {};



template <typename Representation>
class DecompositionalAnalyzer {
    using Number = typename Representation::NumberType;
    using NodeVector = std::vector<ReachTreeNode<Representation>*>;
    using RepVector = std::vector<Representation>;
    using SingularSuccessors = std::map<std::size_t, Representation>;
    using LTIPredecessors = std::map<std::size_t, std::vector<IndexedValuationSet<Representation>>>;
    using LTISuccessors = std::map<std::size_t, std::vector<TimedValuationSet<Representation>>>;

  public:
    using DecompositionalResult = AnalysisResult<DecompositionalSuccess, Failure<Representation>>;
    using WorkerVariant = std::variant<LTIWorker<Representation>,
                                       SingularWorker<Representation>,
                                       RectangularWorker<Representation>>;

    DecompositionalAnalyzer( HybridAutomaton<Number> const& ha,
                 Decomposition const& decomposition,
                 FixedAnalysisParameters const& fixedParameters,
                 AnalysisParameters const& parameters,
                 std::vector<std::vector<ReachTreeNode<Representation>>>& roots )
        : mHybridAutomaton( &ha )
        , mDecomposition( decomposition )
        , mFixedParameters( fixedParameters )
        , mParameters( parameters ) {
        for ( auto& subspaceRoots : roots ) {
            NodeVector root;
            for ( int subspace = decomposition.subspaces.size() - 1; subspace >= 0; --subspace ) {
                root.push_back( &subspaceRoots[ subspace ] );
            }
            mWorkQueue.push_front( root );
        }
        for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
            if ( decomposition.subspaceTypes[ subspace ] == DynamicType::linear || decomposition.subspaceTypes[ subspace ] == DynamicType::affine ) {
                mLtiTypeSubspaces.push_back( subspace );
            } else {
                mSingularTypeSubspaces.push_back( subspace );
            }
        }
    }

    DecompositionalResult run();

  private:
    auto initializeWorkers(
        std::vector<TimeTransformationCache<Number>>& subspaceTransformationCache )
            -> std::vector<WorkerVariant>;
    auto computeTimeSuccessorsGetEnabledTime(
        NodeVector& currentNodes,
        std::vector<WorkerVariant>& workers )
            -> carl::Interval<Number>;
    void intersectSubspacesWithTimeInterval(
        NodeVector& currentNodes,
        const carl::Interval<Number>& timeInterval );
    // Compute time interval where all singular subspaces have the condition enabled as a subset of maxEnabledTime
    auto getSingularEnabledTime(
        const NodeVector& currentNodes,
        const Condition<Number>& condition,
        const carl::Interval<Number>& maxEnabledTime )
            -> carl::Interval<Number>;
    // compute indexed segments where all lti subspaces have the condition enabled as a subset of maxEnabledTime
    auto getLtiEnabledSegments(
        const NodeVector& currentNodes,
        const Condition<Number>& condition,
        const carl::Interval<Number> maxEnabledTime )
            -> LTIPredecessors;
    auto getSingularJumpSuccessors(
        std::vector<WorkerVariant>& workers,
        Transition<Number>* transition )
            -> std::pair<carl::Interval<Number>, SingularSuccessors>;
    auto getLtiJumpSuccessors(
        NodeVector& currentNodes,
        std::vector<WorkerVariant>& workers,
        Transition<Number>* transition,
        carl::Interval<Number> singularEnabledTime )
            -> LTISuccessors;
    auto makeChildrenForSegmentInterval(
        NodeVector& currentNodes,
        const Transition<Number>* transition,
        const carl::Interval<SegmentInd>& segmentInterval,
        SingularSuccessors singularSuccessors,
        LTISuccessors ltiSuccessors )
            -> std::optional<std::vector<ReachTreeNode<Representation>*>>;
    auto makeChildrenForTimeInterval(
        NodeVector& currentNodes,
        const Transition<Number>* transition,
        const carl::Interval<Number>& timeInterval,
        SingularSuccessors singularSuccessors )
            -> std::vector<ReachTreeNode<Representation>*>;




  protected:
    std::deque<NodeVector> mWorkQueue;
    HybridAutomaton<Number> const* mHybridAutomaton;
    Decomposition mDecomposition;
    FixedAnalysisParameters mFixedParameters;
    AnalysisParameters mParameters;
    std::vector<std::size_t> mSingularTypeSubspaces; // holds the subspaces that have a clock and compute all time successors at once
    std::vector<std::size_t> mLtiTypeSubspaces;      // holds the subspaces that have no clock and have multiple segments

    tNumber const mGlobalTimeHorizon = ( mFixedParameters.jumpDepth + 1 )*mFixedParameters.localTimeHorizon;
};

}  // namespace hypro

#include "DecompositionalAnalyzer.tpp"