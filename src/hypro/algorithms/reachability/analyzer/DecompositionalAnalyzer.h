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
// Visitors to call worker functions
template <typename Representation>
struct computeTimeSuccessorVisitor{
	std::size_t subspaceIndex;
	std::vector<ReachTreeNode<Representation>*> nodes;
    REACHABILITY_RESULT operator()( SingularWorker<Representation>& worker ) {
        REACHABILITY_RESULT res = worker.computeTimeSuccessors( nodes[ subspaceIndex ], true );
        auto& flowpipe = nodes[ subspaceIndex ]->getFlowpipe();
        flowpipe.insert( flowpipe.begin(), worker.getFlowpipe().begin(), worker.getFlowpipe().end() );
        return res;    	
    }
    REACHABILITY_RESULT operator()( LTIWorker<Representation>& worker ) {
    	return worker.computeTimeSuccessors( nodes[ subspaceIndex ]->getInitialSet(), nodes[ subspaceIndex ]->getLocation(), std::back_inserter( nodes[ subspaceIndex ]->getFlowpipe() ) );
    }
    // Todo: rectangular worker
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
                 std::vector<std::vector<ReachTreeNode<Representation>>>& roots )
        : mHybridAutomaton( &ha )
        , mDecomposition( decomposition )
        , mFixedParameters( fixedParameters )
        , mParameters( parameters ) {
        for ( auto& root : roots ) {
            mWorkQueue.push_front( &root );
        }
    }

    DecompositionalResult run();
    void addToQueue( NodeVector nodes ) { mWorkQueue.push_front( nodes ); }

  protected:
    std::deque<NodeVector> mWorkQueue;
    HybridAutomaton<Number> const* mHybridAutomaton;
    FixedAnalysisParameters mFixedParameters;
    AnalysisParameters mParameters;
    Decomposition mDecomposition;
};

}  // namespace hypro

#include "DecompositionalAnalyzer.tpp"