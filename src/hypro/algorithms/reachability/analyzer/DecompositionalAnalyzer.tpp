#include "DecompositionalAnalyzer.h"

namespace hypro {

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::run() -> DecompositionalResult {
    std::vector<TimeTransformationCache<Number>> subspaceTransformationCache( mDecomposition.subspaces.size() );
    auto workers = initializeWorkers( subspaceTransformationCache );

    while ( !mWorkQueue.empty() ) {
        NodeVector currentNodes = mWorkQueue.front();
        mWorkQueue.pop_front();

        auto currentLoc = currentNodes[ 0 ]->getLocation();

        // Reset workers
        std::for_each( workers.begin(), workers.end(), []( WorkerVariant& worker ) {
            std::visit( detail::resetWorkerVisitor<Representation>{}, worker );
        } );

        // Time successors
        auto invariantSatisfyingTime = computeTimeSuccessorsGetEnabledTime( currentNodes, workers );
        intersectSubspacesWithTimeInterval( currentNodes, invariantSatisfyingTime );


        // Check safety
        for ( auto badState : detail::collectBadStates( mHybridAutomaton, currentLoc ) ) {
            auto badTimeInterval = getSingularEnabledTime( currentNodes, badState, invariantSatisfyingTime );
            auto badSegments = getLtiEnabledSegments( currentNodes, badState, badTimeInterval );
            if ( std::any_of( badSegments.begin(), badSegments.end(), []( const auto& segmentVector ) {
                    return segmentVector.second.size() > 0; } ) ) {
                return { Failure{ currentNodes[ 0 ] } };
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
            auto ltiJumpSuccessors = getLtiJumpSuccessors(currentNodes, workers, transition.get(), transitionEnabledTime );
            if ( ( singularJumpSuccessors.empty() && mSingularTypeSubspaces.size() > 0 ) ||
                 ( ltiJumpSuccessors.empty() && mLtiTypeSubspaces.size() > 0 ) ) {
                continue;
            }

            // create child nodes
            if ( mLtiTypeSubspaces.size() > 0 ) {
                // case 1: there are lti subspaces -> one successor per (aggregated) segment
                for ( auto& [ successorSet, segmentInterval ] : ltiJumpSuccessors[ mLtiTypeSubspaces[ 0 ] ] ) {
                    auto childNode = makeChildrenForSegmentInterval( currentNodes, transition.get(), segmentInterval, singularJumpSuccessors, ltiJumpSuccessors );
                    if ( childNode.has_value() ) {
                        mWorkQueue.push_back( childNode.value() );
                    }
                }
            } else {
                // case 2: only singular/rectangular subspaces -> exactly one successor
                auto childNode = makeChildrenForTimeInterval( currentNodes, transition.get(), transitionEnabledTime, singularJumpSuccessors );
                mWorkQueue.push_back( childNode );
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
auto DecompositionalAnalyzer<Representation>::computeTimeSuccessorsGetEnabledTime(
  NodeVector& currentNodes, std::vector<WorkerVariant>& workers ) -> carl::Interval<Number> {
    carl::Interval<Number> invariantSatisfyingTime( Number( 0 ), carl::convert<tNumber, Number>( mGlobalTimeHorizon ) );
    for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
        auto globalTimeInterval = std::visit( detail::computeTimeSuccessorVisitor<Representation>{
            currentNodes[ subspace ], mFixedParameters.fixedTimeStep, mParameters.timeStep }, workers[ subspace ] );
        invariantSatisfyingTime = carl::set_intersection( invariantSatisfyingTime, globalTimeInterval );
    }
    return invariantSatisfyingTime;
}

template <typename Representation>
void DecompositionalAnalyzer<Representation>::intersectSubspacesWithTimeInterval(
  NodeVector& currentNodes, const carl::Interval<Number>& timeInterval ) {
    for ( auto subspace : mSingularTypeSubspaces ) {
        // last variable is a clock. intersect each segment with the valid time interval
        for ( auto& segment : currentNodes[ subspace ]->getFlowpipe() ) {
            segment = detail::intersectSegmentWithTimeInterval( segment, timeInterval, segment.dimension() - 1 );
        }
    }
    for ( auto subspace : mLtiTypeSubspaces ) {
        // keep all segments corresponding to a global time interval that has non empty intersection with the invariant timing
        std::size_t firstSegment = 0;
        std::size_t lastSegment = ceil( carl::toDouble (
            ( timeInterval.upper() - currentNodes[ subspace ]->getTimings().lower() * mFixedParameters.fixedTimeStep ) / mParameters.timeStep ) );
        auto& flowpipe = currentNodes[ subspace ]->getFlowpipe();
#ifndef NDEBUG
        // firstSegment should equal 0 because the first segment always satisfies the invariant, so just the last segments are thrown away
        if ( std::is_same_v<Number, mpq_class> ) {
            int cFirstSegment = floor( carl::toDouble(
                ( timeInterval.lower() - currentNodes[ subspace ]->getTimings().upper() * mFixedParameters.fixedTimeStep ) / mParameters.timeStep ) );
            assert( cFirstSegment == 0 );
            assert( lastSegment <= flowpipe.size() );
        }
#endif
        flowpipe = std::vector<Representation>( flowpipe.begin() + firstSegment, flowpipe.begin() + lastSegment );
    }
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getSingularEnabledTime(
  const NodeVector& currentNodes, const Condition<Number>& condition, const carl::Interval<Number>& maxEnabledTime ) -> carl::Interval<Number> {
    carl::Interval<Number> enabledTime = maxEnabledTime;
    for ( auto subspace : mSingularTypeSubspaces ) {
        auto flowpipe = currentNodes[ subspace ]->getFlowpipe();
        assert( flowpipe.size() == 2 );
        auto [containment, enabledSet] = intersect( flowpipe[ 1 ], condition, subspace );
        if ( containment == CONTAINMENT::NO ) {
            return carl::Interval<Number>::emptyInterval();
        }
        auto enabledTimeSubspace = detail::getTimeInterval( enabledSet, enabledSet.dimension() - 1 );
        enabledTime = carl::set_intersection( enabledTime, enabledTimeSubspace );
    }
    return enabledTime;
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getLtiEnabledSegments(
  const NodeVector& currentNodes, const Condition<Number>& condition, const carl::Interval<Number> maxEnabledTime ) -> LTIPredecessors {
    // build set of global segment-indices that cover the previously computed time interval
    if ( maxEnabledTime.isEmpty() ) {
        // return empty map
        return LTIPredecessors();
    }
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

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getSingularJumpSuccessors(
  std::vector<WorkerVariant>& workers, Transition<Number>* transition ) -> std::pair<carl::Interval<Number>, SingularSuccessors> {
    carl::Interval<Number> enabledTimeInterval( Number( 0 ), carl::convert<tNumber, Number>( mGlobalTimeHorizon ) );
    SingularSuccessors singularSuccessors;
    for ( auto subspace : mSingularTypeSubspaces ) {
        auto subspaceSuccessorSet = std::visit( detail::getSingularJumpSuccessorVisitor<Representation>{ transition }, workers[ subspace ] );
        singularSuccessors[ subspace ] = subspaceSuccessorSet;
        enabledTimeInterval = carl::set_intersection( enabledTimeInterval, detail::getTimeInterval( subspaceSuccessorSet, subspaceSuccessorSet.dimension() - 1 ) );
    }
    return std::make_pair( enabledTimeInterval, singularSuccessors );
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getLtiJumpSuccessors(
  NodeVector& currentNodes, std::vector<WorkerVariant>& workers,
  Transition<Number>* transition, carl::Interval<Number> singularEnabledTime ) -> LTISuccessors {
    auto ltiJumpPredecessorSets = getLtiEnabledSegments( currentNodes, transition->getGuard(), singularEnabledTime );
    if ( ltiJumpPredecessorSets.empty() ) {
        return LTISuccessors();
    }
    LTISuccessors ltiSuccessors;
    for ( auto subspace : mLtiTypeSubspaces ) {
        ltiSuccessors[ subspace ] = std::visit(
            detail::getLtiJumpSuccessorVisitor<Representation>{ transition, ltiJumpPredecessorSets[ subspace ] }, workers[ subspace ] );
    }
    return ltiSuccessors;
}

template <typename Representation>
std::optional<std::vector<ReachTreeNode<Representation>*>> DecompositionalAnalyzer<Representation>::makeChildrenForSegmentInterval(
  NodeVector& currentNodes, const Transition<Number>* transition, const carl::Interval<SegmentInd>& segmentInterval, SingularSuccessors singularSuccessors,
  LTISuccessors ltiSuccessors ) {
    bool segmentEnabled;
    NodeVector child( mDecomposition.subspaces.size() );
    for ( auto subspace : mLtiTypeSubspaces ) {
        segmentEnabled = false;
        for ( auto& [ subspaceSuccessor, segments ] : ltiSuccessors[ subspace ] ) {
            if ( segments == segmentInterval ) {
                // todo: child nodes are created even if not all subspaces are enabled. This should be unproblematic
                //       because the workqueue will not be pushed to but could be done better.
                segmentEnabled = true;
                auto& subspaceChild = currentNodes[ subspace ]->addChild( subspaceSuccessor, segmentInterval, transition );
                child[ subspace ] = &subspaceChild;
                break;
            }
        }
        if ( !segmentEnabled ) {
            return {};
        }
    }
    carl::Interval<Number> successorTime( carl::convert<tNumber, Number>( mFixedParameters.fixedTimeStep )*segmentInterval.lower(),
                                          carl::convert<tNumber, Number>( mFixedParameters.fixedTimeStep )*( segmentInterval.upper() + 1 ) );
    auto singularChildren = makeChildrenForTimeInterval( currentNodes, transition, successorTime, singularSuccessors );
    for ( auto subspace : mSingularTypeSubspaces ) {
        child[ subspace ] = singularChildren[ subspace ];
    }
    return child;
}

template <typename Representation>
std::vector<ReachTreeNode<Representation>*> DecompositionalAnalyzer<Representation>::makeChildrenForTimeInterval(
  NodeVector& currentNodes, const Transition<Number>* transition, const carl::Interval<Number>& timeInterval, SingularSuccessors singularSuccessors ) {
    NodeVector child( mDecomposition.subspaces.size() );
    for ( auto subspace : mSingularTypeSubspaces ) {
        auto subspaceSuccessor = detail::intersectSegmentWithTimeInterval( singularSuccessors[ subspace ], timeInterval, singularSuccessors[ subspace ].dimension() - 1 );
        auto& subspaceChild = currentNodes[ subspace ]->addChild( subspaceSuccessor, carl::Interval<SegmentInd>(0, 0), transition );
        child[ subspace ] = &subspaceChild;
    }
    return child;
}
} // namespace hypro
