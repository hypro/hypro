#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
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
struct computeTimeSuccessorVisitor {
  using Number = typename Representation::NumberType;
  std::size_t subspaceIndex;
  std::vector<ReachTreeNode<Representation>*> nodes;
  tNumber fixedTimeStep;
  tNumber timeStep;
    // return time interval covered by the time successors
    carl::Interval<Number> operator()( SingularWorker<Representation>& worker ) {
        worker.computeTimeSuccessors( *nodes[ subspaceIndex ] );
        auto& flowpipe = nodes[ subspaceIndex ]->getFlowpipe();
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
        worker.computeTimeSuccessors( nodes[ subspaceIndex ]->getInitialSet(), nodes[ subspaceIndex ]->getLocation(), std::back_inserter( nodes[ subspaceIndex ]->getFlowpipe() ) );
        auto& flowpipe = nodes[ subspaceIndex ]->getFlowpipe();
        assert( flowpipe.size() > 0 );
        // get global time interval
        Number timeLower = carl::convert<tNumber, Number>( nodes[ subspaceIndex ]->getTimings().lower()*fixedTimeStep );
        Number timeUpper = carl::convert<tNumber, Number>( nodes[ subspaceIndex ]->getTimings().upper()*fixedTimeStep + flowpipe.size()*timeStep );
        return carl::Interval<Number>( timeLower , timeUpper );
    }
    carl::Interval<Number> operator()( RectangularWorker<Representation>& worker ) {
        // Todo: rectangular worker. Should be very similar to singular case
        worker.getFlowpipe();
        return carl::Interval<Number>::emptyInterval();
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
    using WorkerVariant = std::variant<LTIWorker<Representation>,
                                       SingularWorker<Representation>,
                                       RectangularWorker<Representation>>;

  public:
    using DecompositionalResult = AnalysisResult<DecompositionalSuccess, Failure<Representation>>;

    DecompositionalAnalyzer( HybridAutomaton<Number> const& ha,
                 Decomposition const& decomposition,
                 FixedAnalysisParameters const& fixedParameters,
                 AnalysisParameters const& parameters,
                 std::vector<std::vector<ReachTreeNode<Representation>*>>& roots )
        : mHybridAutomaton( &ha )
        , mDecomposition( decomposition )
        , mFixedParameters( fixedParameters )
        , mParameters( parameters ) {
        for ( auto& root : roots ) {
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
    void addToQueue( NodeVector nodes ) { mWorkQueue.push_front( nodes ); }

  protected:
    std::deque<NodeVector> mWorkQueue;
    HybridAutomaton<Number> const* mHybridAutomaton;
    Decomposition mDecomposition;
    FixedAnalysisParameters mFixedParameters;
    AnalysisParameters mParameters;
    std::vector<std::size_t> mSingularTypeSubspaces; // holds the subspaces that have a clock and compute all time successors at once
    std::vector<std::size_t> mLtiTypeSubspaces;      // holds the subspaces that have no clock and have multiple segments
};

}  // namespace hypro

#include "DecompositionalAnalyzer.tpp"