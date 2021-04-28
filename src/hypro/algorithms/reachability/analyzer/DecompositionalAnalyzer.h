#pragma once
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/Flowpipe.h>
#include <hypro/datastructures/reachability/ReachTreev2.h>
#include <hypro/types.h>
#include <hypro/algorithms/reachability/types.h>
#include <hypro/algorithms/reachability/workers/SingularWorker.h>
#include <hypro/algorithms/reachability/workers/LTIWorker.h>
#include <hypro/algorithms/reachability/workers/RectangularWorker.h>
#include <hypro/algorithms/reachability/analyzer/ReturnTypes.h>
#include <hypro/algorithms/reachability/analyzer/DecompositionalUtil.h>
#include <carl/numbers/numbers.h>

#include <queue>


namespace hypro {
namespace detail {

template <typename Representation>
struct decompositionalQueueEntry {
  std::size_t clockIndex;
  Condition<typename Representation::NumberType> dependencies;
  std::vector<ReachTreeNode<Representation>*> nodes;
};

/**
 * @brief       Worker-visitor to reset workers for new task.
 * @tparam      Representation      The used state set representation type.
 */
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

/**
 * @brief       Worker-visitor to compute the time successors for the given task.
 * @tparam      Representation      The used state set representation type.
 * @param       task                The current task.
 * @param       clockCount          Number of used clocks
 * @return      The time interval where the subspace satisfies the invariant.
 */
template <typename Representation>
struct computeTimeSuccessorVisitor {
  using Number = typename Representation::NumberType;
  ReachTreeNode<Representation>* task;
  std::size_t clockCount; // number of clocks
    TimeInformation<Number> operator()( SingularWorker<Representation>& worker ) {
        worker.computeTimeSuccessors( *task, false );
        auto& flowpipe = task->getFlowpipe();
        flowpipe.insert( flowpipe.begin(), worker.getFlowpipe().begin(), worker.getFlowpipe().end() );
        // the second segment covers the entire time interval
        if ( flowpipe.size() == 0 ) {
            // invariant is initially violated
            return TimeInformation<Number>( clockCount );
        }
        assert( flowpipe.size() == 1 );
        // last variables are clocks
        return detail::getClockValues( flowpipe[0], clockCount );
    }
    TimeInformation<Number> operator()( LTIWorker<Representation>& worker ) {
        assert( false && "Only singular dynamics supported for decompositional analysis" );
        return TimeInformation<Number>{};
    }
    TimeInformation<Number> operator()( RectangularWorker<Representation>& ) {
        // Todo: rectangular worker. Should be very similar to singular case
        assert( false && "Only singular dynamics supported for decompositional analysis" );
        return TimeInformation<Number>{}; 
    }
};

/**
 * @brief       Worker-visitor to compute the jump successors for the given task.
 * @tparam      Representation      The used state set representation type.
 * @param       task                The current task.
 */
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
        assert( false && "Singular jump successor computation called for non-singular subspace." );
    }
};


/**
 * @brief       Worker-visitor to get the jump successors for the given transition in singular subspaces.
 * @tparam      Representation      The used state set representation type.
 * @param       transition          The transition for which to get successors.
 * @return      The jump successor as Representation set.
 */
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
        assert( false && "Singular jump successor getter called for non-singular subspace." );
        return Representation::Empty();
    }
};

} // namespace detail

// indicates that the analysis succeeded, i.e. no intersection with bad states
struct DecompositionalSuccess {};


/**
 * @brief      Class implementing a reachability analysis algorithm for decomposed hybrid automata.
 * @tparam     Representation  The used state set representation type.
 */
template <typename Representation>
class DecompositionalAnalyzer {
    using Number = typename Representation::NumberType;
    using NodeVector = std::vector<ReachTreeNode<Representation>*>;
    using RepVector = std::vector<Representation>;
    using LTIPredecessors = std::map<std::size_t, std::vector<IndexedValuationSet<Representation>>>;
    using LTISuccessorCandidates = std::map<std::size_t, std::vector<TimedValuationSet<Representation>>>;

  public:
    using DecompositionalResult = AnalysisResult<DecompositionalSuccess, Failure<Representation>>;
    using WorkerVariant = std::variant<LTIWorker<Representation>,
                                       SingularWorker<Representation>,
                                       RectangularWorker<Representation>>;

    /**
     * @brief       Construct a new DecompositionalAnalyzer object.
     * @details     The given automaton is expected to be decomposed into independent subspaces
     *              given by the decomposition argument. The initial sets are assumed to have clocks which
     *              are used for synchronization of the subspaces.
     *              Decomposition can be achieved with the decomposeAutomaton function and clocks can be
     *              added to the decomposed automaton with the addClockToAutomaton function.
     * @param       ha                  The decomposed hybrid automaton to analyze.
     * @param       decomposition       The decomposition information corresponding to the ha.
     * @param       clockCount          The number of clocks used for synchronization
     * @param       fixedParameters     The fixed analysis parameters.
     * @param       parameters          The analyzer specific parameters (for using multiple analyzers).
     * @param       roots               The roots for the analysis tree (one root for each subspace).
     */
    DecompositionalAnalyzer( HybridAutomaton<Number> const& ha,
                 Decomposition const& decomposition,
                 std::size_t clockCount,
                 FixedAnalysisParameters const& fixedParameters,
                 AnalysisParameters const& parameters,
                 std::vector<std::vector<ReachTreeNode<Representation>>>& roots )
        : mHybridAutomaton( &ha )
        , mDecomposition( decomposition )
        , mClockCount( clockCount )
        , mFixedParameters( fixedParameters )
        , mParameters( parameters ) {
        for ( auto& subspaceRoots : roots ) {
            NodeVector root;
            for ( std::size_t subspace = 0; subspace < decomposition.subspaces.size(); ++subspace ) {
                root.push_back( &subspaceRoots[ subspace ] );
            }
            mWorkQueue.push_front( detail::decompositionalQueueEntry<Representation>{ 0, Condition<Number>(), root } );
        }
        for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
            assert( isClockedSubspace( decomposition.subspaceTypes[ subspace ] ) && "Only singular dynamics supported with decompositional analysis" );
            mSingularSubspaces.push_back( subspace );
        }
    }

    /**
     * @brief       Perform safety analysis.
     * @return      A result object indicating either success (safety) or failure (bad states reachable).
     */
    DecompositionalResult run();

  private:
    /**
     * @brief       Initialize workers for the subspaces.
     * @return      The initizalized workers as vector of variants.
     */
    auto initializeWorkers() -> std::vector<WorkerVariant>;

    /**
     * @brief       Pre-computational check that nodes are consistent (e.g. no initial set is empty).
     * @param       currentNodes    The current reachtree-nodes to analyze.
     * @return      `true` if all checks pass, `false` otherwise.
     */
    bool checkConsistency( NodeVector& currentNodes );

    /**
     * @brief       Compute time successors in all subspaces.
     * @param       currentNodes    The current reachtree-nodes to store the successor sets.
     * @param       workers         The vector of worker variants to use for computation.
     * @return      The clock intervals where all subspaces satisfy their respective invariants.
     */
    auto computeTimeSuccessorsGetEnabledTime(
        NodeVector& currentNodes,
        std::vector<WorkerVariant>& workers )
            -> TimeInformation<Number>;

    /**
     * @brief       Reset unused clocks to zero.
     * @param       currentNodes    The current reachtree-nodes with the computed flowpipes.
     * @param       clockIndex      The current clockIndex. All clocks with higher index are reset.
     */
    void resetClocks( NodeVector& currentNodes, std::size_t clockIndex );

    /**
     * @brief       Intersect computed segments with clock values and update flowpipes.
     * @param       currentNodes    The current reachtree-nodes where the flowpipes are stored.
     * @param       clock           The local/global time intervals to intersect with.
     */
    void intersectSubspacesWithClock(
        NodeVector& currentNodes,
        TimeInformation<Number>& clock );

    /**
     * @brief       Check if intersection with a bad state is empty.
     * @param       currentNodes            The current reachtree-nodes where the flowpipes are stored.
     * @param       badState                The bad state condition to check.
     * @param       dependencies            The dependencies on the initial variables.
     * @return      `true` if the bad state is not reachable and `false` otherwise.
     */
    bool isSafe(
        const NodeVector& currentNodes,
        const Condition<Number>& dependencies,
        const Condition<Number>& badState );

    /**
     * @brief       Get the singular jump successors for a transition and the clock values where all successors satisfy the invariant.
     * @param       workers         The vector of worker variants to use for computation.
     * @param       transition      The transition to get successors for.
     * @return      Pair of clock values where the jump can be taken in all subspaces and the unconstrained successors
                    for each subspace.
     */
    auto getSingularJumpSuccessors(
        std::vector<WorkerVariant>& workers,
        Transition<Number>* transition )
            -> std::pair<TimeInformation<Number>, RepVector>;

    /**
     * @brief       Create children in all singular-subspace-trees for local/global clock values.
     * @param       currentNodes        The current reachtree-nodes to store child-nodes.
     * @param       transition          The transition to make child-nodes for.
     * @param       clock               The local/global time intervals in which to take the transition.
     * @param       singularSuccessors  The (unconstrained) successor sets of the transition for the singular subspaces.
     * @return      The created child-nodes
     */
    auto makeChildrenForClockValues(
        NodeVector& currentNodes,
        const Transition<Number>* transition,
        const TimeInformation<Number>& clock,
        const RepVector& singularSuccessors )
            -> std::vector<ReachTreeNode<Representation>*>;

  protected:
    std::deque<detail::decompositionalQueueEntry<Representation>> mWorkQueue;               // holds the tasks that still need to be computed
    HybridAutomaton<Number> const* mHybridAutomaton; // holds a pointer to the decomposed automaton
    Decomposition mDecomposition;                    // holds decomposition information corresponding to the automaton
    std::size_t mClockCount;                         // holds the number of additional clocks in the (singular) subspaces
    FixedAnalysisParameters mFixedParameters;        // holds common analysis parameters for all analyzers
    AnalysisParameters mParameters;                  // holds analyzer specific parameters
    std::vector<std::size_t> mSingularSubspaces;     // holds the singular subspace indices

    tNumber const mGlobalTimeHorizon = ( mFixedParameters.jumpDepth + 1 )*mFixedParameters.localTimeHorizon;
};

}  // namespace hypro

#include "DecompositionalAnalyzer.tpp"