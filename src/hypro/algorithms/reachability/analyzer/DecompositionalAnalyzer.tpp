#include "DecompositionalAnalyzer.h"

namespace hypro {

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::run() -> DecompositionalResult {
    std::vector<TimeTransformationCache<Number>> subspaceTransformationCache( mDecomposition.subspaces.size() );
    auto workers = initializeWorkers( subspaceTransformationCache );

    while ( !mWorkQueue.empty() ) {
        NodeVector currentNodes = mWorkQueue.front();
        mWorkQueue.pop_front();

        if ( !checkConsistency( currentNodes ) ) {
            // empty initial set, skip this iteration
            continue;
        }

        auto currentLoc = currentNodes[ 0 ]->getLocation();

        // Reset workers
        std::for_each( workers.begin(), workers.end(), []( WorkerVariant& worker ) {
            std::visit( detail::resetWorkerVisitor<Representation>{}, worker );
        } );

        // Time successors
        TimeInformation<Number> invariantSatisfyingTime = computeTimeSuccessorsGetEnabledTime( currentNodes, workers );
        intersectSubspacesWithClock( currentNodes, invariantSatisfyingTime );


        // Check safety
        for ( auto badState : detail::collectBadStates( mHybridAutomaton, currentLoc ) ) {
            if ( !isSafe( currentNodes, badState, invariantSatisfyingTime ) ) {
                return { Failure {currentNodes[ 0 ] } };
            }
        }

        // Check jump depth
        if ( currentNodes[ 0 ]->getDepth() == mFixedParameters.jumpDepth ) {
            continue;
        }

        for ( auto subspace : mSingularTypeSubspaces ) {
            // compute jump successors independently for singular subspaces
            std::visit( detail::computeSingularJumpSuccessorVisitor<Representation>{ currentNodes[ subspace ] }, workers[ subspace ] );
        }

        for ( const auto& transition : currentLoc->getTransitions() ) {
            // get jump successors
            auto [transitionEnabledTime, singularJumpSuccessors] = getSingularJumpSuccessors( workers, transition.get() );
            auto ltiSuccessorCandidates = getLtiJumpSuccessors(currentNodes, workers, transition.get(), transitionEnabledTime );
            if ( ( singularJumpSuccessors.empty() && mSingularTypeSubspaces.size() > 0 ) ||
                 ( ltiSuccessorCandidates.empty() && mLtiTypeSubspaces.size() > 0 ) ) {
                continue;
            }

            // create child nodes
            if ( mLtiTypeSubspaces.size() > 0 ) {
                // case 1: there are lti subspaces -> one successor per (aggregated) segment
                for ( auto& [ successorSet, segmentInterval ] : ltiSuccessorCandidates[ mLtiTypeSubspaces[ 0 ] ] ) {
                    // check that for every subspace there is a successor with the segmentInterval, otherwise skip
                    auto prunedSuccessors = pruneLtiSuccessors( ltiSuccessorCandidates, segmentInterval );
                    if ( prunedSuccessors.has_value() ) {
                        auto childNode = makeChildrenForSegmentInterval( currentNodes, transition.get(), segmentInterval, singularJumpSuccessors, prunedSuccessors.value() );
                        mWorkQueue.push_back( childNode );
                    }
                }
            } else {
                // case 2: only singular/rectangular subspaces -> exactly one successor
                auto childNode = makeChildrenForClockValues( currentNodes, transition.get(), transitionEnabledTime, singularJumpSuccessors );
                if ( childNode.size() > 0 ) {
                    mWorkQueue.push_back( childNode );
                }
            }
        }
    }
    return { DecompositionalSuccess{} };
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::initializeWorkers(
  std::vector<TimeTransformationCache<Number>>& subspaceTransformationCache ) -> std::vector<WorkerVariant> {
    assert( subspaceTransformationCache.size() == mDecomposition.subspaces.size() );
    std::vector<WorkerVariant> workers;
    for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
        switch( mDecomposition.subspaceTypes[ subspace ] ) {
            case DynamicType::timed:
                [[fallthrough]];
            case DynamicType::singular:
                workers.push_back( SingularWorker<Representation>{ *mHybridAutomaton,
                                                                    mFixedParameters,
                                                                    subspace } );
                break;
            case DynamicType::rectangular:
                // Todo: Initialize rectangular worker
                break;
            case DynamicType::discrete:
                [[fallthrough]];
            case DynamicType::affine:
                [[fallthrough]];
            case DynamicType::linear:
                workers.push_back(
                    LTIWorker<Representation>{ *mHybridAutomaton,
                                                mParameters,
                                                mFixedParameters.localTimeHorizon,
                                                subspaceTransformationCache[subspace],
                                                subspace } );
                break;
            default:
                assert( false );
                break;
        }
    }
    return workers;
}

template <typename Representation>
bool DecompositionalAnalyzer<Representation>::checkConsistency( NodeVector& currentNodes ) {
    if ( std::any_of( currentNodes.begin(), currentNodes.end(), []( const auto& node ) {
                return node->getInitialSet().empty(); } ) ) {
        return false;
    }
    return true;
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::computeTimeSuccessorsGetEnabledTime(
  NodeVector& currentNodes, std::vector<WorkerVariant>& workers ) -> TimeInformation<Number> {
    TimeInformation<Number> invariantSatTime{
        carl::Interval<Number>( Number( 0 ), carl::convert<tNumber, Number>( mFixedParameters.localTimeHorizon ) ),
        carl::Interval<Number>( Number( 0 ), carl::convert<tNumber, Number>( mGlobalTimeHorizon ) ) };
    for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
        TimeInformation<Number> invariantSatTimeSubspace = std::visit( detail::computeTimeSuccessorVisitor<Representation>{
            currentNodes[ subspace ], mFixedParameters.fixedTimeStep, mParameters.timeStep }, workers[ subspace ] );
        invariantSatTime = detail::intersectTimeInformation( invariantSatTime, invariantSatTimeSubspace );
    }
    return invariantSatTime;
}

template <typename Representation>
void DecompositionalAnalyzer<Representation>::intersectSubspacesWithClock(
  NodeVector& currentNodes, const TimeInformation<Number>& clock ) {
    for ( auto subspace : mSingularTypeSubspaces ) {
        // last variable is a clock. intersect each segment with the valid time interval
        for ( auto& segment : currentNodes[ subspace ]->getFlowpipe() ) {
            segment = detail::intersectSegmentWithClock( segment, clock, segment.dimension() - 2, segment.dimension() - 1 );
        }
    }
    for ( auto subspace : mLtiTypeSubspaces ) {
        // keep a set of segments that covers the clock. First segment to keep is always the first
        SegmentInd timingLower = currentNodes[ subspace ]->getTimings().lower();
        SegmentInd timingUpper = currentNodes[ subspace ]->getTimings().upper();
        tNumber sizeOfSegments = ( 1 + timingUpper - timingLower ) * mFixedParameters.fixedTimeStep;
        std::size_t firstSegment = 0;
        std::size_t lastSegment = std::round( carl::toDouble( std::max(
            0,
            std::min(
                carl::ceil( ( clock.localTime.upper() - sizeOfSegments ) / mParameters.timeStep ),
                carl::ceil( ( clock.globalTime.upper() - ( timingLower*mFixedParameters.fixedTimeStep + sizeOfSegments ) ) / mParameters.timeStep )
        ) ) ) );
        auto& flowpipe = currentNodes[ subspace ]->getFlowpipe();
//#ifndef NDEBUG
//        // assert that even when calculating firstSegment == 0 (only works with exact number types)
//        if ( std::is_same_v<Number, mpq_class> ) {
//            int cFirstSegment = floor( carl::toDouble(
//                ( timeInterval.lower() - currentNodes[ subspace ]->getTimings().upper() * mFixedParameters.fixedTimeStep ) / mParameters.timeStep ) );
//            assert( cFirstSegment == 0 );
//            assert( lastSegment <= flowpipe.size() );
//        }
//#endif
        flowpipe = std::vector<Representation>( flowpipe.begin() + firstSegment, flowpipe.begin() + lastSegment + 1 );
    }
}

template <typename Representation>
bool DecompositionalAnalyzer<Representation>::isSafe(
  const NodeVector& currentNodes, const Condition<Number>& badState, const TimeInformation<Number>& invariantSatisfyingTime ) {
    auto badTime = getSingularEnabledTime( currentNodes, badState, invariantSatisfyingTime );
    if ( mLtiTypeSubspaces.size() == 0 ) {
        return ( badTime.localTime.isEmpty() || badTime.globalTime.isEmpty() );
    } else {
        auto badSegments = getLtiEnabledSegments( currentNodes, badState, badTime );
        return ( std::all_of( badSegments.begin(), badSegments.end(), []( const auto& segmentVector ) {
                return segmentVector.second.size() == 0; } ) );
    }
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getSingularEnabledTime(
  const NodeVector& currentNodes, const Condition<Number>& condition, const TimeInformation<Number>& maxEnabledTime ) -> TimeInformation<Number> {
    TimeInformation<Number> enabledTime = maxEnabledTime;
    for ( auto subspace : mSingularTypeSubspaces ) {
        auto flowpipe = currentNodes[ subspace ]->getFlowpipe();
        assert( flowpipe.size() == 2 );
        auto [containment, enabledSet] = intersect( flowpipe[ 1 ], condition, subspace );
        if ( containment == CONTAINMENT::NO ) {
            return TimeInformation<Number>{};
        }
        auto enabledTimeSubspace = detail::getClockValues( enabledSet, enabledSet.dimension() - 2, enabledSet.dimension() - 1 );
        enabledTime = detail::intersectTimeInformation( enabledTime, enabledTimeSubspace );
    }
    return enabledTime;
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getLtiEnabledSegments(
  const NodeVector& currentNodes, const Condition<Number>& condition, const TimeInformation<Number> maxEnabledTime ) -> LTIPredecessors {
    if ( maxEnabledTime.localTime.isEmpty() || maxEnabledTime.globalTime.isEmpty() ) {
        // return empty map
        return LTIPredecessors();
    }

    // build set of global segment indices (index in flowpipe + timingOffset) to check
    SegmentInd firstSegmentInGlobalTimeInterval = std::round( carl::toDouble( carl::floor( maxEnabledTime.globalTime.lower() / mFixedParameters.fixedTimeStep ) ) );
    SegmentInd lastSegmentInGlobalTimeInterval = std::round( carl::toDouble( carl::ceil( maxEnabledTime.globalTime.upper() / mFixedParameters.fixedTimeStep ) ) );
    std::set<SegmentInd> enabledSegmentIndices;
    for ( SegmentInd i = firstSegmentInGlobalTimeInterval; i <= lastSegmentInGlobalTimeInterval; ++i ) {
        enabledSegmentIndices.insert( i );
    }

    std::map<std::size_t, std::vector<IndexedValuationSet<Representation>>> enablingSegments;
    for ( auto subspace : mLtiTypeSubspaces ) {
        std::vector<IndexedValuationSet<Representation>> subspaceEnabledSegments;
        auto flowpipe = currentNodes[ subspace ]->getFlowpipe();
        SegmentInd timeOffsetLower = currentNodes[ subspace ]->getTimings().lower();
        SegmentInd timeOffsetUpper = currentNodes[ subspace ]->getTimings().upper();
        tNumber segmentSize = ( timeOffsetUpper - timeOffsetLower + 1 )*mFixedParameters.fixedTimeStep;
        // check segments that lie in enabled local time interval
        SegmentInd firstSegmentToCheck = std::max( 0,
            (SegmentInd) std::round( carl::toDouble( carl::floor( ( maxEnabledTime.localTime.lower() - segmentSize ) / mParameters.timeStep ) ) ) );
        SegmentInd lastSegmentToCheck = std::min( (int) flowpipe.size() - 1,
            (SegmentInd) std::round( carl::toDouble( carl::ceil ( ( maxEnabledTime.localTime.upper() - segmentSize ) / mParameters.timeStep ) ) ) );
        for ( SegmentInd segmentIndex = firstSegmentToCheck; segmentIndex <= lastSegmentToCheck; ++segmentIndex ) {
            // if the segment covers a time period that is potentially enabled, compute intersection with condition
            auto [containment, enabledSet] = intersect( flowpipe[ segmentIndex ], condition, subspace );
            // convert to global index by considering offset and specific time step
            SegmentInd globalIndex = timeOffsetLower + segmentIndex*mParameters.timeStepFactor;
            if ( containment != CONTAINMENT::NO ) {
                subspaceEnabledSegments.push_back( IndexedValuationSet<Representation>{ enabledSet, globalIndex } );
            } else {
                while ( globalIndex <= timeOffsetUpper + segmentIndex*mParameters.timeStepFactor ) {
                    enabledSegmentIndices.erase( globalIndex );
                    ++globalIndex;
                }
            }
        }
        enablingSegments[ subspace ] = subspaceEnabledSegments;
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

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getSingularJumpSuccessors(
  std::vector<WorkerVariant>& workers, Transition<Number>* transition ) -> std::pair<TimeInformation<Number>, JumpSuccessors> {
    TimeInformation<Number> enabledTime{
        carl::Interval<Number>( Number( 0 ), carl::convert<tNumber, Number>( mFixedParameters.localTimeHorizon ) ),
        carl::Interval<Number>( Number( 0 ), carl::convert<tNumber, Number>( mGlobalTimeHorizon ) ) };
    JumpSuccessors singularSuccessors;
    for ( auto subspace : mSingularTypeSubspaces ) {
        auto subspaceSuccessorSet = std::visit( detail::getSingularJumpSuccessorVisitor<Representation>{ transition }, workers[ subspace ] );
        singularSuccessors[ subspace ] = subspaceSuccessorSet;
        enabledTime = detail::intersectTimeInformation(
            enabledTime, detail::getClockValues( subspaceSuccessorSet, subspaceSuccessorSet.dimension() - 2, subspaceSuccessorSet.dimension() - 1 ) );
    }
    return std::make_pair( enabledTime, singularSuccessors );
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getLtiJumpSuccessors(
  NodeVector& currentNodes, std::vector<WorkerVariant>& workers,
  Transition<Number>* transition, TimeInformation<Number> singularEnabledTime ) -> LTISuccessorCandidates {
    auto ltiJumpPredecessorSets = getLtiEnabledSegments( currentNodes, transition->getGuard(), singularEnabledTime );
    if ( ltiJumpPredecessorSets.empty() ) {
        return LTISuccessorCandidates();
    }
    LTISuccessorCandidates ltiSuccessors;
    for ( auto subspace : mLtiTypeSubspaces ) {
        ltiSuccessors[ subspace ] = std::visit(
            detail::getLtiJumpSuccessorVisitor<Representation>{ transition, ltiJumpPredecessorSets[ subspace ] }, workers[ subspace ] );
    }
    return ltiSuccessors;
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::pruneLtiSuccessors(
  LTISuccessorCandidates& ltiSuccessorCandidates, const carl::Interval<SegmentInd>& segmentInterval ) -> std::optional<JumpSuccessors> {
    JumpSuccessors successors;
    bool segmentIntervalEnabled;
    for ( auto subspace : mLtiTypeSubspaces ) {
        segmentIntervalEnabled = false;
        for ( auto& [ subspaceSuccessor, segments ] : ltiSuccessorCandidates[ subspace ] ) {
            if ( segments == segmentInterval ) {
                segmentIntervalEnabled = true;
                successors[ subspace ] = subspaceSuccessor;
                break;
            }
        }
        if ( !segmentIntervalEnabled ) {
            return {};
        }
    }
    return successors;
}

template <typename Representation>
std::vector<ReachTreeNode<Representation>*> DecompositionalAnalyzer<Representation>::makeChildrenForSegmentInterval(
  NodeVector& currentNodes, const Transition<Number>* transition, const carl::Interval<SegmentInd>& segmentInterval, JumpSuccessors singularSuccessors,
  JumpSuccessors ltiSuccessors ) {
    NodeVector child( mDecomposition.subspaces.size() );
    for ( auto subspace : mLtiTypeSubspaces ) {
        auto& subspaceChild = currentNodes[ subspace ]->addChild( ltiSuccessors[ subspace ], segmentInterval, transition );
        child[ subspace ] = &subspaceChild;
    }
    carl::Interval<Number> successorTimeGlobal( carl::convert<tNumber, Number>( mFixedParameters.fixedTimeStep )*segmentInterval.lower(),
                                                carl::convert<tNumber, Number>( mFixedParameters.fixedTimeStep )*( segmentInterval.upper() + 1 ) );
    carl::Interval<Number> successorTimeLocal( Number( 0 ), carl::convert<tNumber, Number>( mFixedParameters.localTimeHorizon ) );
    auto singularChildren = makeChildrenForClockValues(
        currentNodes, transition, TimeInformation<Number>{ successorTimeLocal, successorTimeGlobal }, singularSuccessors );
    for ( auto subspace : mSingularTypeSubspaces ) {
        child[ subspace ] = singularChildren[ subspace ];
    }
    return child;
}

template <typename Representation>
std::vector<ReachTreeNode<Representation>*> DecompositionalAnalyzer<Representation>::makeChildrenForClockValues(
  NodeVector& currentNodes, const Transition<Number>* transition, const TimeInformation<Number>& timeInterval, JumpSuccessors singularSuccessors ) {
    if ( timeInterval.localTime.isEmpty() || timeInterval.globalTime.isEmpty() ) {
        return NodeVector{};
    }
    NodeVector child( mDecomposition.subspaces.size() );
    for ( auto subspace : mSingularTypeSubspaces ) {
        auto subspaceSuccessor = detail::intersectSegmentWithClock(
            singularSuccessors[ subspace ], timeInterval, singularSuccessors[ subspace ].dimension() - 2, singularSuccessors[ subspace ].dimension() - 1 );
        subspaceSuccessor = detail::resetClock( subspaceSuccessor, subspaceSuccessor.dimension() - 2 );
        auto& subspaceChild = currentNodes[ subspace ]->addChild( subspaceSuccessor, carl::Interval<SegmentInd>( 0, 0 ), transition );
        child[ subspace ] = &subspaceChild;
    }
    return child;
}
} // namespace hypro
