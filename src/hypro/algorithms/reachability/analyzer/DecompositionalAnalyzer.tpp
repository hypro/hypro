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
    /*
        Analysis
    */
    while ( !mWorkQueue.empty() ) {
        NodeVector currentNodes = mWorkQueue.front();
        mWorkQueue.pop_front();

        /*
            Reset workers
        */
        for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
            std::visit( detail::resetWorkerVisitor<Representation>{}, workers[ subspace ] );
        }

        /*  
            Compute time successors
        */
        carl::Interval<Number> invariantSatisfyingTime( Number( 0 ), carl::convert<tNumber, Number>( ( mFixedParameters.jumpDepth + 1 )*mFixedParameters.localTimeHorizon ) );
        for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
            auto globalTimeInterval = std::visit( detail::computeTimeSuccessorVisitor<Representation>{ currentNodes[ subspace ], mFixedParameters.fixedTimeStep, mParameters.timeStep }, workers[ subspace ] );
            invariantSatisfyingTime = carl::set_intersection( invariantSatisfyingTime, globalTimeInterval );
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
            std::size_t firstSegment = 0;
            std::size_t lastSegment = ceil( carl::toDouble ( ( carl::toDouble( invariantSatisfyingTime.upper() ) - currentNodes[ subspace ]->getTimings().lower() * mFixedParameters.fixedTimeStep ) / mParameters.timeStep ) );
            auto& flowpipe = currentNodes[ subspace ]->getFlowpipe();
#ifndef NDEBUG
            // firstSegment should equal 0 because the first segment always satisfies the invariant, so just the last segments are thrown away
            if ( std::is_same_v<Number, mpq_class> ) {
                int cFirstSegment = floor( carl::toDouble( ( invariantSatisfyingTime.lower() - currentNodes[ subspace ]->getTimings().upper() * mFixedParameters.fixedTimeStep ) / mParameters.timeStep ) );
                assert( cFirstSegment == 0 );
                assert( lastSegment <= flowpipe.size() );
            }
#endif
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
            carl::Interval<Number> badTimeInterval = getSingularEnabledTime( badState, invariantSatisfyingTime, currentNodes );
            if ( badTimeInterval.isEmpty() ) {
                continue;
            }
            auto badSegments = getLtiEnabledSegments( badState, badTimeInterval, currentNodes );
            for ( auto subspace : mLtiTypeSubspaces ) {
                if ( badSegments[ subspace ].size() > 0 ) {
                    // todo: figure out what to return (maybe build sets from all subspaces?)
                    return { Failure{ currentNodes[ 0 ] } };
                }
            }
        }

        /*
            Check jump depth
        */
        if ( currentNodes[ 0 ]->getDepth() == mFixedParameters.jumpDepth ) {
            continue;
        }

        /*
            Jumps
        */
        // 1. compute guard intersection, reset and new invariant intersection with all singular subspaces
        // 2. get time interval from these sets
        // 3. for each segment, if the guard is enabled and it is in the above time interval, compute guard intersection
        // 4. for each segment index that is enabled in all subspaces compute reset (with aggregation)
        // 5. check invariant intersection. If nonempty, intersect singular type subspaces with time interval from segments (aggregated)
        //      and add them as new child node (with timing from segment indices)


        for ( auto subspace : mSingularTypeSubspaces ) {
            // intersect with guard, apply reset and intersect with invariant (successors stored in the worker) for all transitions
            std::visit( detail::computeSingularJumpSuccessorVisitor<Representation>{ currentNodes[ subspace ] }, workers[ subspace ] );
        }

        for ( const auto& transition : currentNodes[ 0 ]->getLocation()->getTransitions() ) {
            // Get singular successors and their enabled time interval
            std::map<std::size_t, Representation> singularSuccessors;
            carl::Interval<Number> enabledTimeInterval = invariantSatisfyingTime;
            for ( auto subspace : mSingularTypeSubspaces ) {
                auto subspaceSuccessorSet = std::visit( detail::getSingularJumpSuccessorVisitor<Representation>{ transition.get() }, workers[ subspace ] );
                singularSuccessors[ subspace ] = subspaceSuccessorSet;
                enabledTimeInterval = carl::set_intersection( enabledTimeInterval, detail::getTimeInterval( subspaceSuccessorSet, subspaceSuccessorSet.dimension() - 1 ) );
            }

            // compute successors for lti subspaces
            auto ltiJumpPredecessorSets = getLtiEnabledSegments( transition->getGuard(), enabledTimeInterval, currentNodes );
            std::map<std::size_t, std::vector<TimedValuationSet<Representation>>> ltiSuccessors;
            for ( auto subspace : mLtiTypeSubspaces ) {
                ltiSuccessors[ subspace ] = std::visit( detail::getLtiJumpSuccessorVisitor<Representation>{ transition.get(), ltiJumpPredecessorSets[ subspace ] }, workers[ subspace ] );
            }

            /*
                Create child nodes
            */
            if ( mLtiTypeSubspaces.size() > 0 ) {
                for ( auto& [ successorSet, segmentInterval ] : ltiSuccessors[ mLtiTypeSubspaces[ 0 ] ] ) {
                    // create successor for segmentInterval if all subspaces have a successor here
                    bool segmentEnabled;
                    NodeVector child( mDecomposition.subspaces.size() );
                    for ( auto subspace : mLtiTypeSubspaces ) {
                        segmentEnabled = false;
                        for ( auto& [ subspaceSuccessor, segments ] : ltiSuccessors[ subspace ] ) {
                            if ( segments == segmentInterval ) {
                                segmentEnabled = true;
                                auto& subspaceChild = currentNodes[ subspace ]->addChild( subspaceSuccessor, segmentInterval, transition.get() );
                                child[ subspace ] = &subspaceChild;
                            }
                        }
                        if ( !segmentEnabled ) {
                            break;
                        }
                    }
                    if ( !segmentEnabled ) {
                        // some subspace doesn't have a successor with the time interval
                        continue;
                    }
                    // segment n covers time interval [n*timeStep + (n+1)*timeStep]
                    carl::Interval<Number> successorTime( carl::convert<tNumber, Number>( mFixedParameters.fixedTimeStep )*segmentInterval.lower(),
                                                          carl::convert<tNumber, Number>( mFixedParameters.fixedTimeStep )*( segmentInterval.upper() + 1 ) );
                    for ( auto subspace : mSingularTypeSubspaces ) {
                        auto subspaceSuccessor = detail::intersectSegmentWithTimeInterval( singularSuccessors[ subspace ], successorTime, singularSuccessors[ subspace ].dimension() - 1 );
                        auto& subspaceChild = currentNodes[ subspace ]->addChild( subspaceSuccessor, segmentInterval, transition.get() );
                        child[ subspace ] = &subspaceChild;
                    }
                    mWorkQueue.push_back( child );
                }
            } else {
                // only singular subspaces -> only one successor time interval
                NodeVector child( mDecomposition.subspaces.size() );
                carl::Interval<Number> successorTime = enabledTimeInterval;
                for ( auto subspace : mSingularTypeSubspaces ) {
                    auto subspaceSuccessor = detail::intersectSegmentWithTimeInterval( singularSuccessors[ subspace ], successorTime, singularSuccessors[ subspace ].dimension() - 1 );
                    auto& subspaceChild = currentNodes[ subspace ]->addChild( subspaceSuccessor, carl::Interval<SegmentInd>(0, 0), transition.get() );
                    child[ subspace ] = &subspaceChild;
                }
                mWorkQueue.push_back( child );
            }
        }

    }
    return { DecompositionalSuccess{} };

}

template <typename Representation>
carl::Interval<typename Representation::NumberType> DecompositionalAnalyzer<Representation>::getSingularEnabledTime( const Condition<Number>& condition, const carl::Interval<Number>& maxEnabledTime, const NodeVector& currentNodes ) {
    carl::Interval<Number> enabledTime = maxEnabledTime;
    for ( auto subspace : mSingularTypeSubspaces ) {
        auto flowpipe = currentNodes[ subspace ]->getFlowpipe();
        assert( flowpipe.size() == 2 );
        auto [containment, enabledSet] = intersect( flowpipe[ 1 ], condition, subspace );
        auto enabledTimeSubspace = detail::getTimeInterval( enabledSet, enabledSet.dimension() - 1 );
        enabledTime = carl::set_intersection( enabledTime, enabledTimeSubspace );
        if ( enabledTime.isEmpty() ) {
            break;
        }
    }
    return enabledTime;
}

template <typename Representation>
std::map<std::size_t, std::vector<IndexedValuationSet<Representation>>> DecompositionalAnalyzer<Representation>::getLtiEnabledSegments( const Condition<Number>& condition, const carl::Interval<Number> maxEnabledTime, const NodeVector& currentNodes ) {
    // build set of global segment-indices that cover the previously computed time interval
    int firstSegmentToCheck = floor( carl::toDouble( carl::toDouble( maxEnabledTime.lower() ) / mFixedParameters.fixedTimeStep ) );
    int lastSegmentToCheck = ceil( carl::toDouble( carl::toDouble( maxEnabledTime.upper() ) / mFixedParameters.fixedTimeStep ) );
    std::set<SegmentInd> enabledSegmentIndices;
    for ( int i = firstSegmentToCheck; i <= lastSegmentToCheck; ++i ) {
        enabledSegmentIndices.insert( i );
    }

    std::map<std::size_t, std::vector<IndexedValuationSet<Representation>>> enablingSegments;
    for ( auto subspace : mLtiTypeSubspaces ) {
        std::vector<IndexedValuationSet<Representation>> subspaceEnablingSegments;
        auto flowpipe = currentNodes[ subspace ]->getFlowpipe();
        int timingLower = currentNodes[ subspace ]->getTimings().lower();
        int timingUpper = currentNodes[ subspace ]->getTimings().upper();
        for ( std::size_t segmentIndex = 0; segmentIndex < flowpipe.size(); ++segmentIndex ) {
            // if the segment covers a time period that is potentially enabled, compute intersection with condition
            auto [containment, enabledSet] = intersect( flowpipe[ segmentIndex ], condition, subspace );
            // convert to global index by considering offset and specific time step
            int globalIndex = timingLower + segmentIndex*mParameters.timeStepFactor;
            if ( containment != CONTAINMENT::NO ) {
                subspaceEnablingSegments.push_back( IndexedValuationSet<Representation>{ enabledSet, globalIndex } );
            } else {
                while ( globalIndex <= timingUpper + segmentIndex*mParameters.timeStepFactor ) {
                    enabledSegmentIndices.erase( globalIndex );
                    ++globalIndex;
                }
            }
        }
        enablingSegments[ subspace ] = subspaceEnablingSegments;
    }

    for ( auto subspace : mLtiTypeSubspaces ) {
        std::vector<IndexedValuationSet<Representation>> prunedSegments;
        for ( auto indexedSegment : enablingSegments[ subspace ] ) {
            if ( enabledSegmentIndices.find( indexedSegment.index ) != enabledSegmentIndices.end() ) {
                prunedSegments.push_back( indexedSegment );
            }
        }
        enablingSegments[ subspace ] = prunedSegments;
    }

    return enablingSegments;
}


} // namespace hypro
