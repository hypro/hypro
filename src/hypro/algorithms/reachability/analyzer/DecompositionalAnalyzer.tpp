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

        Box<Number> invariantSatisfyingTime( std::vector<Point<Number>>( { Point<Number>( 0 ), Point<Number>( carl::convert<tNumber, Number>( mFixedParameters.localTimeHorizon ) ) } ) );

        for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
            // Compute time successors
            WorkerVariant subspaceWorker = workers[ subspace ];
            Box<Number> timeInterval = std::visit( detail::computeTimeSuccessorVisitor<Representation>{ subspace, currentNodes, mFixedParameters.fixedTimeStep, mParameters.timeStep }, subspaceWorker );
            invariantSatisfyingTime = invariantSatisfyingTime.intersect( timeInterval );
            // todo: can continue with next in queue if invariantSatisfyingTime.empty()
        }

        for ( std::size_t subspace = 0; subspace <mDecomposition.subspaces.size(); ++subspace ) {
            // intersect each subspace with the valid time interval
            
            if ( mDecomposition.subspaceTypes[ subspace ] != DynamicType::linear && mDecomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
                // in this case the last variable is a clock
                // intersect each segment with the valid time interval by converting to hpolytope and inserting time constraints
                std::size_t subspaceDimension = mDecomposition.subspaces[ subspace ].size();
                vector_t<Number> timeVector = vector_t<Number>::Zero( subspaceDimension + 1 );
                timeVector( subspaceDimension ) = 1;
                Halfspace<Number> h1( timeVector, invariantSatisfyingTime.max().rawCoordinates()[0] );
                Halfspace<Number> h2( -1 * timeVector, invariantSatisfyingTime.min().rawCoordinates()[0] );
                auto& flowpipe = currentNodes[ subspace ]->getFlowpipe();
                for ( std::size_t i = 0; i < flowpipe.size(); ++i ) {
                    HPolytope<Number> hpol;
                    convert( flowpipe[i], hpol );
                    hpol.insert( h1 );
                    hpol.insert( h2 );
                    convert( hpol, flowpipe[i] );
                    // todo: remove empty segments
                }
            } else {
                // keep all segments corresponding to a global time interval that has non empty intersection with the invariant timing
                // compute global time of the segments via the initial timing of the node (getTimings)
                int firstSegment = floor( carl::toDouble( ( carl::toDouble( invariantSatisfyingTime.min().rawCoordinates()[0] ) - currentNodes[ subspace ]->getTimings().upper() * mFixedParameters.fixedTimeStep ) / mParameters.timeStep ) );
                int lastSegment = ceil( carl::toDouble ( ( carl::toDouble( invariantSatisfyingTime.max().rawCoordinates()[0] ) - currentNodes[ subspace ]->getTimings().lower() * mFixedParameters.fixedTimeStep ) / mParameters.timeStep ) );
                auto& flowpipe = currentNodes[ subspace ]->getFlowpipe();
                assert( firstSegment == 0 && lastSegment <= flowpipe.size() );
                // firstSegment should equal 1 because the first segment always satisfies the invariant, so just the last segments are thrown away
                // this means we don't lose track of time
                flowpipe = std::vector<Representation>( flowpipe.begin() + firstSegment, flowpipe.begin() + lastSegment );
            }

        }

    }
    return { DecompositionalSuccess{} };

}


} // namespace hypro
