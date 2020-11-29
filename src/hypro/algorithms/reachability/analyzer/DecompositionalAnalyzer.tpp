#include "DecompositionalAnalyzer.h"

namespace hypro {

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::run() -> DecompositionalResult {
    std::vector<WorkerVariant> workers;
    // Set up workers
    std::vector<TimeTransformationCache<Number>> subspaceTransformationCache( mDecomposition.subspaces.size() );
    for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
        switch( mDecomposition.subspaceTypes[ subspace ] ) {
            case DynamicType::discrete:
                [[fallthrough]];
            case DynamicType::timed:
                [[fallthrough]];
            case DynamicType::singular:
                workers.push_back( SingularWorker<Representation>{ *mHybridAutomaton, mFixedParameters, subspace } );
                break;
            case DynamicType::rectangular:
                // Todo: Initialize rectangular worker
                break;
            case DynamicType::affine:
                [[fallthrough]];
            case DynamicType::linear:
                workers.push_back( LTIWorker<Representation>{ *mHybridAutomaton, mParameters, mFixedParameters.localTimeHorizon, subspaceTransformationCache[subspace], subspace } );
                break;
            default:
                assert( false );
                break;
        }
    }
    while ( !mWorkQueue.empty() ) {
        NodeVector currentNodes = mWorkQueue.front();
        mWorkQueue.pop_front();

        Box<Number> invariantSatisfyingTime{ Point<Number>( 0 ), Point<Number>( mFixedParameters.localTimeHorizon ) };

        for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
            // Compute time successors
            WorkerVariant subspaceWorker = workers[ subspace ];
            Box<Number> timeInterval = std::visit( detail::computeTimeSuccessorVisitor<Representation>{ subspace, currentNodes }, subspaceWorker );
            invariantSatisfyingTime = invariantSatisfyingTime.intersect( timeInterval );
            // todo: can continue with next in queue if invariantSatisfyingTime.empty()
        }

        for ( std::size_t subspace = 0; subspace <mDecomposition.subspaces.size(); ++subspace ) {
            // intersect each subspace with the valid time interval
            std::size_t subspaceDimension = mDecomposition.subspaces[ subspace ].size();
            if ( mDecomposition.subspaceTypes[ subspace ] != DynamicType::linear && mDecomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
                // in this case the last variable is a clock
                // intersect each segment with the valid time interval
                std::size_t subspaceDimension = mDecomposition.subspaces[ subspace ].size();
                matrix_t<Number> timeMatrix = matrix_t<Number>::Zero( 2, subspaceDimension + 1 );
                vector_t<Number> timeVector = vector_t<Number>::Zero( 2 );
                timeMatrix( 0, subspaceDimension ) = 1;
                timeMatrix( 1, subspaceDimension ) = -1;
                timeVector << invariantSatisfyingTime.min().rawCoordinates()[0], invariantSatisfyingTime.max().rawCoordinates()[0];
                Representation timeIntervalRep( timeMatrix, timeVector );
                auto& flowpipe = currentNodes[ subspace ]->getFlowpipe();
                for ( std::size_t i = 0; i < flowpipe.size(); ++i ) {
                    flowpipe[ i ] = flowpipe[ i ].intersect( timeIntervalRep );
                    // todo: remove empty segments
                }
            } else {
                // keep all segments corresponding to a global time interval that has non empty intersection with the invariant timing
                // compute global time of the segments via the initial timing of the node (getTimings)
                int firstSegment = lower( ( carl::toDouble( invariantSatisfyingTime.min().rawCoordinates()[0] ) - currentNodes[ subspace ].getTimings().upper() * mFixedParameters.fixedTimeStep ) / mParameters.timeStep );
                int lastSegment = upper( ( carl::toDouble( invariantSatisfyingTime.max().rawCoordinates()[0] ) - currentNodes[ subspace ].getTimings().lower() * mFixedParameters.fixedTimeStep ) / mParameters.timeStep );
                auto& flowpipe = currentNodes[ subspace ]->getFlowpipe();
                assert( firstSegment >= 0 && lastSegment <= flowpipe.size() );
                flowpipe = std::vector<Representation>( flowpipe.begin() + firstSegment, flowpipe.begin() + lastSegment );
            }

        }

    }

}

/*
template <typename Representation>
auto DecompositionalAnalyzer<Representation>::run() -> DecompositionalResult {
    std::vector<WorkerVariant> workers;
    // Set up workers
    std::vector<TimeTransformationCache<Number>> subspaceTransformationCache( mDecomposition.subspaces.size() );
    for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
        switch( mDecomposition.subspaceTypes[ subspace ] ) {
            case DynamicType::discrete:
                [[fallthrough]];
            case DynamicType::timed:
                [[fallthrough]];
            case DynamicType::singular:
                workers.push_back( SingularWorker<Representation>{ *mHybridAutomaton, mFixedParameters, subspace } );
                break;
            case DynamicType::rectangular:
                // Todo: Initialize rectangular worker
                break;
            case DynamicType::affine:
                [[fallthrough]];
            case DynamicType::linear:
                workers.push_back( LTIWorker<Representation>{ *mHybridAutomaton, mParameters, mFixedParameters.localTimeHorizon, subspaceTransformationCache[subspace], subspace } );
                break;
            default:
                assert( false );
                break;
        }
    }

    while ( !mWorkQueue.empty() ) {
        NodeVector currentNodes = mWorkQueue.front();
        mWorkQueue.pop_front();
        std::vector<std::size_t> unsafeSubspaces;
        int minimalSegmentCount = ceil( carl::toDouble ( mFixedParameters.localTimeHorizon / mFixedParameters.fixedTimeStep ) );
        int segmentCount;
        for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
            
            // 1. Call workers with currentNode->getInitialSet()[subspace]
            // 2. Create flowpipe for each subspace
            // 3. Check length of flowpipe for each subspace, take the minimum
            // 4. Remove all segments that need too much time elapse

            // 1. + 2. Call workers; create flowpipe
            WorkerVariant subspaceWorker = workers[ subspace ];
            REACHABILITY_RESULT safetyResult = std::visit( detail::computeTimeSuccessorVisitorSegments<Representation>{ subspace, currentNodes }, subspaceWorker );
            if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
                unsafeSubspaces.push_back( subspace );
            }
            // Cannot determine unsafety yet, because time to elapse might be limited by other subspaces
            // Idea for checking safety: 
            //    For all unsafe subspaces, make sure that at least one segment is
            //    removed by time constraints (as soon as an unsafe state is determined
            //    in the worker, it will return, so only the last segment is unsafe)
            //
            // 3. Get minimal segmentCount
            segmentCount = currentNodes[ subspace ]->getFlowpipe().size();
            minimalSegmentCount = segmentCount < minimalSegmentCount ? segmentCount : minimalSegmentCount;
        }
        // 4. Remove all segments that need too much time elapse
        for ( std::size_t subspace = mDecomposition.subspaces.size() - 1;; --subspace ) {
            segmentCount = currentNodes[ subspace ]->getFlowpipe().size();
            if ( segmentCount <= minimalSegmentCount ) {
                // Nothing to remove
                if ( unsafeSubspaces.size() > 0 && subspace == unsafeSubspaces.back() ) {
                    // Unsafe state is within time limit
                    return { Failure{ currentNodes[ subspace ] } };
                }
            }
            else {
                auto& flowpipes = currentNodes[subspace]->getFlowpipe();
                flowpipes.erase( flowpipes.end() - ( segmentCount - minimalSegmentCount ), flowpipes.end() );
                if ( unsafeSubspaces.size() > 0 && subspace == unsafeSubspaces.back() ) {
                    // Unsafe states were beyond time limit, so the subspace is safe
                    unsafeSubspaces.pop_back();
                }
            }
            if ( subspace == 0 ) break;
        }
    }
}
*/


} // namespace hypro