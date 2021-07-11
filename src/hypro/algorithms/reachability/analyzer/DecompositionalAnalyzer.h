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
 * @return      The time intervals where the subspace satisfies the invariant.
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
        // the first segment covers the entire time interval
        if ( flowpipe.size() == 0 ) {
            // invariant is initially violated
            return TimeInformation<Number>( clockCount );
        }
        assert( flowpipe.size() == 1 );
        // last variables are clocks
        return detail::getClockValues( flowpipe[0], clockCount );
    }
    TimeInformation<Number> operator()( LTIWorker<Representation>& worker ) {
        worker.computeTimeSuccessors( task->getInitialSet(), task->getLocation(), std::back_inserter( task->getFlowpipe() ), false );
        if ( task->getFlowpipe().size() == 0 ) {
            return TimeInformation<Number>( clockCount );
        }
        return detail::getClockValues( task->getFlowpipe()[ 0 ], clockCount ).unite( 
               detail::getClockValues( task->getFlowpipe()[ task->getFlowpipe().size() - 1 ], clockCount ) );
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
struct getJumpSuccessorVisitor {
  using Number = typename Representation::NumberType;
  Transition<Number>* transition;
  std::vector<IndexedValuationSet<Representation>> predecessors{};
    std::vector<TimedValuationSet<Representation>> operator()( SingularWorker<Representation>& worker ) {
        auto it = worker.getJumpSuccessorSets().find( transition );
        if ( it != worker.getJumpSuccessorSets().end() ) {
            auto successorList = it->second;
            assert( successorList.size() == 1 );
            return { { successorList[ 0 ], carl::Interval<SegmentInd>( 0 ) } };
        }
        else {
            return  { { Representation::Empty(), carl::Interval<SegmentInd>( 0 ) } };
        }
    }
    std::vector<TimedValuationSet<Representation>> operator()( RectangularWorker<Representation>& ) {
        //todo
        return { { Representation::Empty(), carl::Interval<SegmentInd>( 0 ) } };
    }
    std::vector<TimedValuationSet<Representation>> operator()( LTIWorker<Representation>& worker ) {
        return worker.computeJumpSuccessorsForGuardEnabled( predecessors, transition );
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
    using SubspaceSets = std::map<std::size_t, Representation>;

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
            mWorkQueue.push_front( detail::decompositionalQueueEntry<Representation>{ 0, Condition<Number>( ConstraintSetT<Number>() ), root } );
        }
        for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
            if( isSegmentedSubspace( decomposition.subspaceTypes[ subspace ] ) ) {
                mSegmentedSubspaces.push_back( subspace );
            } else {
                mSingularSubspaces.push_back( subspace );
            }
        }
    }

    /**
     * @brief       Perform safety analysis.
     * @return      A result object indicating either success (safety) or failure (bad states reachable).
     */
    DecompositionalResult run();

  private:
    struct LtiJumpSuccessorGen;
    struct LtiSegmentGen;

    /**
     * @brief       Initialize workers for the subspaces.
     * @return      The initizalized workers as vector of variants.
     */
    auto initializeWorkers( std::vector<TimeTransformationCache<Number>>& cache ) -> std::vector<WorkerVariant>;

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
     * @param       segment         The computed segment.
     * @param       clockIndex      The current clockIndex. All clocks with higher index are reset.
     */
    void resetClock( Representation& segment, std::size_t clockIndex );


    /**
     * @brief       Intersect computed segments with clock values and update flowpipes.
     * @param       currentNodes    The current reachtree-nodes where the flowpipes are stored.
     * @param       clock           The time intervals to intersect with.
     */
    void intersectSubspacesWithClock(
        NodeVector& currentNodes,
        TimeInformation<Number>& clock );

    /**
     * @brief       Check if intersection with a bad state is empty.
     * @param       currentNodes            The current reachtree-nodes where the flowpipes are stored.
     * @param       dependencies            The dependencies on the initial variables.
     * @param       badState                The bad state condition to check.
     * @return      `true` if the bad state is not reachable and `false` otherwise.
     */
    bool isSafe(
        const NodeVector& currentNodes,
        const Condition<Number>& dependencies,
        const Condition<Number>& badState );

    /**
     * @brief       Compute jump successors and reset unused clocks to zero.
     * @param       nodes           Current nodes
     * @param       workers         The vector of worker variants to use for computation.
     * @param       transition      The transition to get successors for.
     * @param       clockIndex      The currently used clock index. Clocks with higher index are reset after the jump.
     * @return      Vector of jump successors as map { subspace (index) : reset jump successor (representation) }
     */
    auto getJumpSuccessors(
        const NodeVector& nodes,
        std::vector<WorkerVariant> workers,
        Transition<Number>* trans,
        std::size_t clockIndex )
            -> std::vector<SubspaceJumpSuccessors<Representation>>;

    /**
     * @brief       Get the singular jump successors for a transition and the clock values where all successors satisfy the invariant.
     * @param       nodes           Current nodes
     * @param       workers         The vector of worker variants to use for computation.
     * @param       transition      The transition to get successors for.
     * @param       clockIndex      The currently used clock index. Clocks with higher index are reset after the jump.
     * @return      Pair of clock values where the jump is enabled and the jump successors in the singular subspaces.
     */
    auto getSingularJumpSuccessors(
        const NodeVector& nodes,
        std::vector<WorkerVariant>& workers,
        Transition<Number>* trans,
        std::size_t clockIndex )
            -> std::pair<TimeInformation<Number>, SubspaceSets>;

    
    /**
     * @brief       Get the jump successors in the segmented subspaces for a transition.
     * @param       nodes           Current nodes
     * @param       workers         The vector of worker variants to use for computation.
     * @param       transition      The transition to get successors for.
     * @param       clockIndex      The currently used clock index. Clocks with higher index are reset after the jump.
     * @return      Vector of jump successors as map { subspace (index) : reset jump successor (representation) }
     */
    auto getSegmentedJumpSuccessors(
        const NodeVector& nodes,
        std::vector<WorkerVariant>& workers,
        Transition<Number>* trans,
        std::size_t clockIndex )
            -> std::vector<SubspaceJumpSuccessors<Representation>>;

  protected:
    std::deque<detail::decompositionalQueueEntry<Representation>> mWorkQueue;               // holds the tasks that still need to be computed
    HybridAutomaton<Number> const* mHybridAutomaton; // holds a pointer to the decomposed automaton
    Decomposition mDecomposition;                    // holds decomposition information corresponding to the automaton
    std::size_t mClockCount;                         // holds the number of additional clocks in the (singular) subspaces
    FixedAnalysisParameters mFixedParameters;        // holds common analysis parameters for all analyzers
    AnalysisParameters mParameters;                  // holds analyzer specific parameters
    std::vector<std::size_t> mSingularSubspaces;     // holds the singular subspace indices
    std::vector<std::size_t> mSegmentedSubspaces;    // holds the subspaces which have more than one segment as time successors (e.g. non-singular)

    tNumber const mGlobalTimeHorizon = ( mFixedParameters.jumpDepth + 1 )*mFixedParameters.localTimeHorizon;
    TimeInformation<Number> const mGlobalTimeInterval = TimeInformation<Number>( mClockCount, Number( 0 ), carl::convert<tNumber, Number>( mGlobalTimeHorizon ) );
};

}  // namespace hypro

#include "DecompositionalAnalyzer.tpp"