#include "DecompositionalAnalyzer.h"

namespace hypro {

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::run() -> DecompositionalResult {
    std::vector<TimeTransformationCache<Number>> cache( mDecomposition.subspaces.size(), TimeTransformationCache<Number>() );
    auto workers = initializeWorkers( cache );

    while ( !mWorkQueue.empty() ) {
        auto nextInQueue = mWorkQueue.front();
        mWorkQueue.pop_front();
        NodeVector currentNodes = nextInQueue.nodes;
        Condition<Number> dependencies = nextInQueue.dependencies;
        std::size_t clockIndex = nextInQueue.clockIndex;
        const Location<Number>* currentLoc = currentNodes[ 0 ]->getLocation();

        if ( !checkConsistency( currentNodes ) ) {
            // empty initial set
            continue;
        }

        std::for_each( workers.begin(), workers.end(), []( WorkerVariant& worker ) {
            std::visit( detail::resetWorkerVisitor<Representation>{}, worker );
        } );

        // Time successors
        TimeInformation<Number> invariantSatisfyingTime = computeTimeSuccessorsGetEnabledTime( currentNodes, workers );
        removeRedundantSegments( currentNodes );
        intersectSubspacesWithClock( currentNodes, invariantSatisfyingTime );

        // Check safety
        for ( auto badState : detail::collectBadStates( mHybridAutomaton, currentLoc ) ) {
            if ( !isSafe( currentNodes, dependencies, badState ) ) {
                return { Failure { currentNodes[ 0 ] } };
            }
        }

        // Check jump depth
        if ( currentNodes[ 0 ]->getDepth() == mFixedParameters.jumpDepth ) {
            continue;
        }

        for ( const auto& transition : currentLoc->getTransitions() ) {
            std::vector<SubspaceJumpSuccessors<Representation>> jumpSuccessors = getJumpSuccessors( currentNodes, workers, transition.get(), clockIndex );
            for ( auto& timedSuccessor : jumpSuccessors ) {
                std::size_t nextIndex = clockIndex + 1;
                // todo: return as vector, not as map
                RepVector subspaceSets( mDecomposition.subspaces.size() );
                for ( std::size_t subspace = 0; subspace < subspaceSets.size(); ++subspace ) {
                    subspaceSets[ subspace ] = std::move( timedSuccessor.subspaceSets[ subspace ] );
                }
                if ( nextIndex >= mClockCount ) {
                    nextIndex = 0;
                    // complexity reduction
                    if ( mClockCount > 0 ) {
                        Representation composedSuccessors = detail::composeSubspaces( subspaceSets, dependencies, mDecomposition, mClockCount );
                        if ( composedSuccessors.empty() ) {
                            continue;
                        }
                        dependencies = detail::getDependencies( composedSuccessors, mDecomposition );
                        subspaceSets = detail::decompose( composedSuccessors, mDecomposition, mClockCount );
                    }
                }

                // create child nodes and push to queue
                NodeVector childNodes( mDecomposition.subspaces.size() );
                for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
                    auto& subspaceChild = currentNodes[ subspace ]->addChild( subspaceSets[ subspace ], timedSuccessor.time, transition.get(), dependencies );
                    childNodes[ subspace ] = &subspaceChild;
                }
                mWorkQueue.push_back( detail::decompositionalQueueEntry<Representation>{ nextIndex, dependencies, childNodes } );
            }
        }
    }
    return { DecompositionalSuccess{} };
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::initializeWorkers( std::vector<TimeTransformationCache<Number>>& cache ) -> std::vector<WorkerVariant> {
    std::vector<WorkerVariant> workers;
    for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
        switch( mDecomposition.subspaceTypes[ subspace ] ) {
            case DynamicType::discrete:
                workers.push_back( DiscreteWorker<Representation>{*mHybridAutomaton,
                                                                mParameters,
                                                                subspace } );
                break;
            case DynamicType::timed:
                [[fallthrough]];
            case DynamicType::singular:
                workers.push_back( SingularWorker<Representation>{ *mHybridAutomaton,
                                                                    mFixedParameters,
                                                                    subspace } );
                break;
            default:
                workers.push_back( LTIWorker<Representation>{ 
                    *mHybridAutomaton,
                    mParameters,
                    mFixedParameters.localTimeHorizon,
                    cache[ subspace ],
                    subspace } );
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
    // start with maximal time interval and shrink it after each subspace computation
    TimeInformation<Number> invariantSatTime = mGlobalTimeInterval;
    for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
        TimeInformation<Number> invariantSatTimeSubspace = std::visit( detail::computeTimeSuccessorVisitor<Representation>{
            currentNodes[ subspace ], mClockCount }, workers[ subspace ] );
        // discrete subspaces have no clocks
        if( mDecomposition.subspaceTypes[ subspace ] != DynamicType::discrete ) {
            invariantSatTime = invariantSatTime.intersect( invariantSatTimeSubspace );
        }
    }
    return invariantSatTime;
}

template <typename Representation>
void DecompositionalAnalyzer<Representation>::intersectSubspacesWithClock(
  NodeVector& currentNodes, TimeInformation<Number>& clock ) {
    for ( std::size_t subspace = 0; subspace < currentNodes.size(); ++subspace ) {
        // discrete subspaces have no clocks
        if ( mDecomposition.subspaceTypes[ subspace ] == DynamicType::discrete ) continue;
        // intersect each segment with the valid time interval
        auto& flowpipe = currentNodes[ subspace ]->getFlowpipe();
        for ( std::size_t segmentIndex = 0; segmentIndex < flowpipe.size(); ++segmentIndex ) {
            auto constraintedSegment = detail::intersectSegmentWithClock( flowpipe[ segmentIndex ], clock, mClockCount );
            if ( constraintedSegment.empty() ) {
                // delete all further segments, because they have higher clock values
                flowpipe.resize( segmentIndex );
            } else {
                flowpipe[ segmentIndex ] = constraintedSegment;
            }
        }
    }
}

template <typename Representation>
void DecompositionalAnalyzer<Representation>::removeRedundantSegments( NodeVector& currentNodes ) {
    if ( mSegmentedSubspaces.size() == 0 ) { return; }
    // get minimum number of segments that a subspace has
    std::vector<std::size_t> segmentCount( mSegmentedSubspaces );
    std::size_t i = 0;
    for ( auto subspace : mSegmentedSubspaces ) {
        segmentCount[ i ] = currentNodes[ subspace ]->getFlowpipe().size();
        ++i;
    }
    std::size_t minSegments = *( std::min_element( segmentCount.begin(), segmentCount.end() ) );
    // remove segments beyond reachable time horizon
    for ( auto subspace : mSegmentedSubspaces ) {
        currentNodes[ subspace ]->getFlowpipe().resize( minSegments );
    }
}

template <typename Representation>
bool DecompositionalAnalyzer<Representation>::isSafe(
  const NodeVector& nodes, const Condition<Number>& dependencies, const Condition<Number>& badState ) {

    // Synchronize segmented subspaces and intersect them with the bad state
    // note: only segments that have non-empty intersection with bad state in all subspaces are returned by generator
    LtiSegmentGen segments{ nodes, mDecomposition, badState, mSegmentedSubspaces };
    RepVector subspaceSets( mDecomposition.subspaces.size() );
    // each segment is paired with the single segment from each singular subspace
    for ( auto subspace : mSingularSubspaces ) {
        auto [containment, set] = intersect( nodes[ subspace ]->getFlowpipe()[ 0 ], badState, subspace );
        if ( containment == CONTAINMENT::NO ) {
            // no bad state intersection in some subspace
            return true;
        } else {
            subspaceSets[ subspace ] = set;
        }
    }
    for ( auto subspace : mDiscreteSubspaces ) {
        auto [containment, set] = intersect( nodes[ subspace ]->getFlowpipe()[ 0 ], badState, subspace );
        if ( containment == CONTAINMENT::NO ) {
            // no bad state intersection in some subspace
            return true;
        } else {
            subspaceSets[ subspace ] = set;
        }
    }
    if ( mSegmentedSubspaces.size() == 0 ) {
        if ( mClockCount == 0 ) {
            // all subspaces unsafe at some point. without synchronization we cannot tell if they are unsafe at the same time or not.
            return false;
        }
        // compose subspaces and check if synchronized set is non empty
        HPolytope<Number> composedPolytope = detail::composeSubspaceConstraints( subspaceSets, dependencies, mDecomposition, mClockCount );
        if ( !composedPolytope.empty() ) {
            return false;
        }
    }
    // iterate over each synchronized segment and check if composition is non empty
    for ( auto badSegment = segments.next().second; badSegment.size() > 0; badSegment = segments.next().second ) {
        if ( mClockCount == 0 ) {
            // all subspaces unsafe at some point. without synchronization we cannot tell if they are unsafe at the same time or not.
            return false;
        }
        for ( auto subspace : mSegmentedSubspaces ) {
            subspaceSets[ subspace ] = badSegment[ subspace ];
        }
        HPolytope<Number> composedPolytope = detail::composeSubspaceConstraints( subspaceSets, dependencies, mDecomposition, mClockCount );
        if ( !composedPolytope.empty() ) {
            return false;
        }
    }
    return true;
}

template <typename Representation>
void DecompositionalAnalyzer<Representation>::resetClock( Representation& segment, std::size_t clockIndex ) {
    if ( mClockCount == 0 ) { return; }
    assert( mClockCount > clockIndex );
    // reset clocks with higher index than clockIndex to 0
    std::vector<std::size_t> nonZeroDimensions( segment.dimension() - mClockCount + clockIndex + 1 );
    for ( std::size_t i = 0; i < nonZeroDimensions.size(); ++i ) {
        nonZeroDimensions[ i ] = i;
    }
    segment.projectOn( nonZeroDimensions );
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getJumpSuccessors(
        const NodeVector& nodes, std::vector<WorkerVariant> workers,
        Transition<Number>* trans,
        std::size_t clockIndex )
            -> std::vector<SubspaceJumpSuccessors<Representation>> {
    // res holds all synchronized jump successors
    std::vector<SubspaceJumpSuccessors<Representation>> res;
    // Collect single successor set (per subspace) for singular subspaces and synchronize them
    auto [ singularEnabledTime, singularSuccessors ] = getSingularJumpSuccessors( nodes, workers, trans, clockIndex );
    auto discreteSuccessors = getDiscreteJumpSuccessors( nodes, workers, trans );
    if ( mSegmentedSubspaces.size() == 0 ) {
        // no segmented subspace, so the segment indexes are ignored -> set them to 0
        SubspaceJumpSuccessors<Representation> succ{ carl::Interval<SegmentInd>( 0 ), singularSuccessors };
        for ( auto subspace : mDiscreteSubspaces ) {
            succ.subspaceSets[ subspace ] = discreteSuccessors[ subspace ];
        }
        return { succ };
    }
    // collect synchronized successors for segmented subspaces
    std::vector<SubspaceJumpSuccessors<Representation>> segmentedSuccessors = getSegmentedJumpSuccessors( nodes, workers, trans, clockIndex );

    // synchronize segmented subspaces with singular
    for ( auto timedSucc : segmentedSuccessors ) {
        SubspaceJumpSuccessors<Representation> nextRes;
        auto enabledTime = singularEnabledTime;
        for ( auto subspace : mSegmentedSubspaces ) {
            enabledTime = enabledTime.intersect( detail::getClockValues( timedSucc.subspaceSets[ subspace ], mClockCount ) );
        }
        if ( enabledTime.empty() ) continue;
        for ( auto subspace : mSegmentedSubspaces ) {
            nextRes.subspaceSets[ subspace ] = detail::intersectSegmentWithClock( timedSucc.subspaceSets[ subspace ], enabledTime, mClockCount );
        }
        for ( auto subspace : mSingularSubspaces ) {
            nextRes.subspaceSets[ subspace ] = detail::intersectSegmentWithClock( singularSuccessors[ subspace ], enabledTime, mClockCount );
        }
        for ( auto subspace : mDiscreteSubspaces ) {
            nextRes.subspaceSets[ subspace ] = discreteSuccessors[ subspace ];
        }
        // get time interval of jump
        nextRes.time = timedSucc.time;
        res.push_back( nextRes );
    }
    
    return res;
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getSingularJumpSuccessors(
  const NodeVector& nodes, std::vector<WorkerVariant>& workers, Transition<Number>* trans, std::size_t clockIndex ) -> std::pair<TimeInformation<Number>, SubspaceSets> {
    // compute jump successors independently
    for ( auto subspace : mSingularSubspaces ) {
        std::visit( detail::computeSingularJumpSuccessorVisitor<Representation>{ nodes[ subspace ] }, workers[ subspace ] );
    }
    // synchronize by getting the time interval where the jump is enabled across subspaces
    TimeInformation<Number> enabledTime = mGlobalTimeInterval;
    SubspaceSets singularSuccessors;
    for ( auto subspace : mSingularSubspaces ) {
        auto timedSucc = std::visit( detail::getJumpSuccessorVisitor<Representation>{ trans }, workers[ subspace ] );
        // we should always get a set, which may be empty
        assert( timedSucc.size() == 1 );
        auto subspaceSuccessorSet = timedSucc[ 0 ].valuationSet;
        resetClock( subspaceSuccessorSet, clockIndex );
        singularSuccessors[ subspace ] = subspaceSuccessorSet;
        enabledTime = enabledTime.intersect( detail::getClockValues( subspaceSuccessorSet, mClockCount ) );
    }
    // intersect each successor with the obtained enabled time interval
    for ( auto subspace : mSingularSubspaces ) {
        singularSuccessors[ subspace ] = detail::intersectSegmentWithClock( singularSuccessors[ subspace ], enabledTime, mClockCount );
    }
    return std::make_pair( enabledTime, singularSuccessors );
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getDiscreteJumpSuccessors(
  const NodeVector& nodes, std::vector<WorkerVariant>& workers, Transition<Number>* trans ) -> SubspaceSets {
    SubspaceSets succ;
    bool empty = false;
    for ( auto subspace : mDiscreteSubspaces ) {
        if ( empty ) {
            succ[ subspace ] = Representation::Empty();
            continue;
        }
        auto [containment, predecessor] = intersect( nodes[ subspace ]->getFlowpipe()[ 0 ], trans->getGuard(), subspace );
        if ( containment == CONTAINMENT::NO ) {
            empty = true;
            succ[ subspace ] = Representation::Empty();
        } else {
            succ[ subspace ] = std::visit( detail::getJumpSuccessorVisitor<Representation>{ trans, { { predecessor, 0 } } }, workers[ subspace ] )[ 0 ].valuationSet;
        }
    }
    return succ;
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getSegmentedJumpSuccessors(
        const NodeVector& nodes, std::vector<WorkerVariant>& workers, Transition<Number>* trans, std::size_t clockIndex) -> std::vector<SubspaceJumpSuccessors<Representation>> {
    // generator synchronized segments by index and intersects with the guard
    LtiSegmentGen segments{ nodes, mDecomposition, trans->getGuard(), mSegmentedSubspaces };
    // get predecessors by intersecting with guard
    std::map<std::size_t, std::vector<IndexedValuationSet<Representation>>> predecessors;
    for ( auto subspace : mSegmentedSubspaces ) {
        predecessors[ subspace ] = std::vector<IndexedValuationSet<Representation>>();
    }
    for ( auto indexedSegments = segments.next(); indexedSegments.second.size() > 0; indexedSegments = segments.next() ) {
        for ( auto subspace : mSegmentedSubspaces ) {
            // reset unused clocks to 0
            resetClock( indexedSegments.second[ subspace ], clockIndex );
            predecessors[ subspace ].push_back( { indexedSegments.second[ subspace ], indexedSegments.first } );
        }
    }
    std::map<std::size_t, std::vector<TimedValuationSet<Representation>>> subspaceSuccessors;
    for ( auto subspace : mSegmentedSubspaces ) {
        subspaceSuccessors[ subspace ] = std::visit( detail::getJumpSuccessorVisitor<Representation>{ trans, predecessors[ subspace ] }, workers[ subspace ] );
    }
    // synchronize via the time interval of the jump
    // note: every subspace has the same enabled segments and same aggregation settings, so the time intervals are the same
    LtiJumpSuccessorGen synchronizedSuccessors{ subspaceSuccessors, mSegmentedSubspaces };
    std::vector<SubspaceJumpSuccessors<Representation>> res;
    for ( auto succ = synchronizedSuccessors.next(); succ.subspaceSets.size() > 0; succ = synchronizedSuccessors.next() ) {
        res.push_back( succ );
    }
    return res;
}

template <typename Representation>
struct DecompositionalAnalyzer<Representation>::LtiSegmentGen {
    NodeVector const nodes;
    SegmentInd segmentIndex = 0;
    Decomposition decomposition;
    Condition<Number> cond = Condition<Number>( ConstraintSetT<Number>() );
    std::vector<std::size_t> subspaces;
    
    LtiSegmentGen( NodeVector const& nodes, Decomposition const& decomposition, const std::vector<std::size_t>& subspaces )
        : nodes( nodes )
        , decomposition( decomposition )
        , subspaces( subspaces ) {}
    LtiSegmentGen( NodeVector const& nodes, Decomposition const& decomposition, Condition<Number> const& cond, const std::vector<std::size_t>& subspaces )
        : nodes( nodes )
        , decomposition( decomposition )
        , cond( cond )
        , subspaces( subspaces ) {}
    std::pair<SegmentInd, SubspaceSets> next() {
        // check if more segments are available
        for ( auto subspace : subspaces ) {
            if ( segmentIndex >= (SegmentInd) nodes[ subspace ]->getFlowpipe().size() ) {
                return {};
            }
        }
        SubspaceSets res;
        for ( auto subspace : subspaces ) {
            auto& flowpipe = nodes[ subspace ]->getFlowpipe();
            assert( (SegmentInd) flowpipe.size() > segmentIndex );
            auto [containment, set] = intersect( flowpipe[ segmentIndex ], cond, subspace );
            if ( containment == CONTAINMENT::NO ) {
                segmentIndex += 1;
                return next();
            }
            res[ subspace ] = { set } ;
        }
        segmentIndex += 1;
        return std::make_pair( segmentIndex, res );
    }
};

template <typename Representation>
struct DecompositionalAnalyzer<Representation>::LtiJumpSuccessorGen {
    const std::map<std::size_t, std::vector<TimedValuationSet<Representation>>> subspaceSuccessors;
    std::vector<std::size_t> subspaces;

    std::size_t firstIndex = 0;
    LtiJumpSuccessorGen( const std::map<std::size_t, std::vector<TimedValuationSet<Representation>>>& subspaceSuccessors, const std::vector<std::size_t>& subspaces )
        : subspaceSuccessors( subspaceSuccessors )
        , subspaces( subspaces ) {}
    SubspaceJumpSuccessors<Representation> next() {
        if ( subspaces.size() == 0 ) {
            return {};
        } else if ( firstIndex >= subspaceSuccessors.at( 0 ).size() ) {
            return {};
        } else {
            const auto nextInterval = subspaceSuccessors.at( 0 )[ firstIndex ].time;
            SubspaceSets res;
            for ( auto subspace : subspaces ) {
                bool found = false;
                for ( const auto succ : subspaceSuccessors.at( subspace ) ) {
                    if ( nextInterval == succ.time ) {
                        res[ subspace ] = succ.valuationSet;
                        found = true;
                    }
                }
                if ( !found ) {
                    firstIndex += 1;
                    return next();
                }
            }
            firstIndex += 1;
            return SubspaceJumpSuccessors<Representation>{ nextInterval, res };
        }

    }
};

} // namespace hypro
