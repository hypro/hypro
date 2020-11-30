#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/Flowpipe.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../types.h"
#include "../workers/SingularWorker.h"
#include "../workers/LTIWorker.h"
#include "../workers/RectangularWorker.h"
#include "./ReturnTypes.h"

#include <queue>


namespace hypro {
namespace detail {

// get the time interval covered by the segment if the last variable is the clock
template <typename Representation>
auto getTimeInterval( const Representation& segment ) -> Box<typename Representation::NumberType> {
    using Number = typename Representation::NumberType;
    vector_t<Number>clockDirection = vector_t<Number>::Zero( segment.dimension() );
    clockDirection( segment.dimension() - 1 ) = 1;
    Point<Number> timeLower = Point<Number>( segment.evaluate( clockDirection ).supportValue );
    Point<Number> timeUpper = Point<Number>( segment.evaluate( -1 * clockDirection ).supportValue );
    return Box<Number>( std::vector<Point<Number>>( { timeLower, timeUpper } ) );

}


// Visitors to call worker functions
template <typename Representation>
struct computeTimeSuccessorVisitor {
  using Number = typename Representation::NumberType;
  std::size_t subspaceIndex;
  std::vector<ReachTreeNode<Representation>*> nodes;
  tNumber fixedTimeStep;
  tNumber timeStep;
    // return time interval covered by the time successors
    Box<Number> operator()( SingularWorker<Representation>& worker ) {
        worker.computeTimeSuccessors( *nodes[ subspaceIndex ] );
        auto& flowpipe = nodes[ subspaceIndex ]->getFlowpipe();
        flowpipe.insert( flowpipe.begin(), worker.getFlowpipe().begin(), worker.getFlowpipe().end() );
        // the second segment covers the entire time interval
        if ( flowpipe.size() == 0 ) {
            // invariant is initially violated
            return Box<Number>::Empty();
        }
        assert( flowpipe.size() == 2 );
        // last variable is the clock
        return getTimeInterval( flowpipe[1] );
    }
    Box<Number> operator()( LTIWorker<Representation>& worker ) {
        worker.computeTimeSuccessors( nodes[ subspaceIndex ]->getInitialSet(), nodes[ subspaceIndex ]->getLocation(), std::back_inserter( nodes[ subspaceIndex ]->getFlowpipe() ) );
        auto& flowpipe = nodes[ subspaceIndex ]->getFlowpipe();
        assert( flowpipe.size() > 0 );
        // get global time interval
        Number timeLower = carl::convert<tNumber, Number>( nodes[ subspaceIndex ]->getTimings().lower()*fixedTimeStep );
        Number timeUpper = carl::convert<tNumber, Number>( nodes[ subspaceIndex ]->getTimings().upper()*fixedTimeStep + flowpipe.size()*timeStep );
        return Box<Number>( std::vector<Point<Number>>( { Point<Number>( timeLower ), Point<Number>( timeUpper ) } ) );
    }
    Box<Number> operator()( RectangularWorker<Representation>& worker ) {
        // Todo: rectangular worker. Should be very similar to singular case
        worker.getFlowpipe();
        return Box<Number>::Empty();
    }
};



/*
template <typename Representation>
struct computeTimeSuccessorVisitorSegments {
  std::size_t subspaceIndex;
  std::vector<ReachTreeNode<Representation>*> nodes;
    REACHABILITY_RESULT operator()( SingularWorker<Representation>& worker ) {
        REACHABILITY_RESULT res = worker.computeTimeSuccessors( *nodes[ subspaceIndex ] );
        auto& flowpipe = nodes[ subspaceIndex ]->getFlowpipe();
        flowpipe.insert( flowpipe.begin(), worker.getFlowpipe().begin(), worker.getFlowpipe().end() );
        return res;
    }
    REACHABILITY_RESULT operator()( LTIWorker<Representation>& worker ) {
        return worker.computeTimeSuccessors( nodes[ subspaceIndex ]->getInitialSet(), nodes[ subspaceIndex ]->getLocation(), std::back_inserter( nodes[ subspaceIndex ]->getFlowpipe() ) );
    }
    REACHABILITY_RESULT operator()( RectangularWorker<Representation>& worker ) {
        // Todo: rectangular worker
        return REACHABILITY_RESULT::SAFE;
    }
};
*/
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
    }

    DecompositionalResult run();
    void addToQueue( NodeVector nodes ) { mWorkQueue.push_front( nodes ); }

  protected:
    std::deque<NodeVector> mWorkQueue;
    HybridAutomaton<Number> const* mHybridAutomaton;
    Decomposition mDecomposition;
    FixedAnalysisParameters mFixedParameters;
    AnalysisParameters mParameters;
};

}  // namespace hypro

#include "DecompositionalAnalyzer.tpp"