#include "DecompositionalAnalyzer.h"

namespace hypro {

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::run() -> DecompositionalResult {
    std::vector<WorkerVariant> workers;
    /*
        Initialize workers
    */
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

        /*  
            Compute time successors
        */
        carl::Interval<Number> invariantSatisfyingTime( Number( 0 ), carl::convert<tNumber, Number>( mFixedParameters.localTimeHorizon ) );
        for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
            WorkerVariant subspaceWorker = workers[ subspace ];
            auto timeInterval = std::visit( detail::computeTimeSuccessorVisitor<Representation>{ subspace, currentNodes, mFixedParameters.fixedTimeStep, mParameters.timeStep }, subspaceWorker );
            invariantSatisfyingTime = carl::set_intersection( invariantSatisfyingTime, timeInterval );
            // todo: can continue with next in queue if invariantSatisfyingTime.isEmpty()
        }

        // intersect each subspace with the valid time interval
        for ( auto subspace : mSingularTypeSubspaces ) {
            // last variable is a clock. intersect each segment with the valid time interval
            for ( auto& segment : currentNodes[ subspace ]->getFlowpipe() ) {
                segment = detail::intersectSegmentWithTimeInterval( segment, invariantSatisfyingTime, segment.dimension() - 1 );
            }
        }
        for ( auto subspace : mLtiTypeSubspaces ) {
            // keep all segments corresponding to a global time interval that has non empty intersection with the invariant timing
            int firstSegment = floor( carl::toDouble( ( carl::toDouble( invariantSatisfyingTime.lower() ) - currentNodes[ subspace ]->getTimings().upper() * mFixedParameters.fixedTimeStep ) / mParameters.timeStep ) );
            int lastSegment = ceil( carl::toDouble ( ( carl::toDouble( invariantSatisfyingTime.upper() ) - currentNodes[ subspace ]->getTimings().lower() * mFixedParameters.fixedTimeStep ) / mParameters.timeStep ) );
            auto& flowpipe = currentNodes[ subspace ]->getFlowpipe();
            // firstSegment should equal 0 because the first segment always satisfies the invariant, so just the last segments are thrown away
            assert( firstSegment == 0 && lastSegment <= flowpipe.size() );            
            flowpipe = std::vector<Representation>( flowpipe.begin() + firstSegment, flowpipe.begin() + lastSegment );
        }


        /*
            Check safety
        */
        auto badStates = mHybridAutomaton->getGlobalBadStates();
        auto localBadState = mHybridAutomaton->getLocalBadStates().find( currentNodes[ 0 ]->getLocation() );
        if ( localBadState != mHybridAutomaton->getLocalBadStates().end() ) {
            badStates.push_back( localBadState->second );
        }

        for ( auto badState : badStates ) {
            carl::Interval<Number> badTimeInterval( Number( 0 ), carl::convert<tNumber, Number>( mFixedParameters.localTimeHorizon ) );

            // Check singular type subspaces to build the time interval with potentially reachable bad states
            for ( auto subspace : mSingularTypeSubspaces ) {
                auto flowpipe = currentNodes[ subspace ]->getFlowpipe();
                assert( flowpipe.size() == 2 );
                auto [containment, badStatesSubspace] = intersect( flowpipe[ 1 ], badState, subspace );
                if ( containment != CONTAINMENT::NO ) {
                    auto badSubspaceTime = detail::getTimeInterval( badStatesSubspace, badStatesSubspace.dimension() - 1 );
                    badTimeInterval = carl::set_intersection( badTimeInterval, badSubspaceTime );
                }                
                if ( badTimeInterval.isEmpty() ) {
                    break;
                }
            }
            if ( badTimeInterval.isEmpty() ) {
                continue;
            }

            // build set of global segment-indices that cover the previously computed time interval
            int firstSegmentToCheck = floor( carl::toDouble( carl::toDouble( badTimeInterval.lower() ) / mFixedParameters.fixedTimeStep ) );
            int lastSegmentToCheck = ceil( carl::toDouble( carl::toDouble( badTimeInterval.upper() ) / mFixedParameters.fixedTimeStep ) );            
            std::set<SegmentInd> segmentsToCheck;
            for ( int i = firstSegmentToCheck; i <= lastSegmentToCheck; ++i ) {
                segmentsToCheck.insert( i );
            }
            // check lti-type subspaces
            for ( auto subspace : mLtiTypeSubspaces ) {
                auto flowpipe = currentNodes[ subspace ]->getFlowpipe();
                int timingLower = currentNodes[ subspace ]->getTimings().lower();
                int timingUpper = currentNodes[ subspace ]->getTimings().upper();
                for ( std::size_t segmentIndex = 0; segmentIndex < flowpipe.size(); ++segmentIndex ) {
                    // if the segment covers a time period that is potentially unsafe, compute intersection with bad state
                    TRIBOOL segmentUnsafe = TRIBOOL::NSET;
                    // convert to global index by considering offset and specific time step
                    for ( std::size_t globalIndex = timingLower + segmentIndex*mParameters.timeStepFactor; globalIndex <= timingUpper + segmentIndex*mParameters.timeStepFactor; ++globalIndex ) {
                        if ( segmentsToCheck.find( globalIndex ) != segmentsToCheck.end() ) {                            
                            if ( segmentUnsafe == TRIBOOL::NSET ) {
                                if ( intersect( flowpipe[ segmentIndex ], badState, subspace ).first != CONTAINMENT::NO ) {
                                    segmentUnsafe = TRIBOOL::TRUE;
                                } else {
                                    segmentUnsafe = TRIBOOL::FALSE;
                                }
                            }
                            if ( segmentUnsafe == TRIBOOL::FALSE ) {
                                segmentsToCheck.erase( globalIndex );
                            }
                        }
                    }

                }
            }
            if ( !segmentsToCheck.empty() ) {
                // todo: figure out which set to return (maybe build a set from all subspaces?)
                return { Failure{ currentNodes[ 0 ] } };
            }
        }
        


    }
    return { DecompositionalSuccess{} };

}


} // namespace hypro
