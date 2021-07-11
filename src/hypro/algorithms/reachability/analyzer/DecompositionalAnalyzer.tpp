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
                if ( clockIndex >= mClockCount - 1 ) {
                    nextIndex = 0;
                    // complexity reduction
                    Representation composedSuccessors = detail::composeSubspaces( subspaceSets, dependencies, mDecomposition, mClockCount );
                    if ( composedSuccessors.empty() ) {
                        continue;
                    }
                    dependencies = detail::getDependencies( composedSuccessors, mDecomposition );
                    subspaceSets = detail::decompose( composedSuccessors, mDecomposition, mClockCount );
                }

                // create child nodes and push to queue
                NodeVector childNodes( mDecomposition.subspaces.size() );
                for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
                    auto& subspaceChild = currentNodes[ subspace ]->addChild( subspaceSets[ subspace ], timedSuccessor.time, transition.get() );
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
    TimeInformation<Number> invariantSatTime = mGlobalTimeInterval;
    for ( std::size_t subspace = 0; subspace < mDecomposition.subspaces.size(); ++subspace ) {
        TimeInformation<Number> invariantSatTimeSubspace = std::visit( detail::computeTimeSuccessorVisitor<Representation>{
            currentNodes[ subspace ], mClockCount }, workers[ subspace ] );
        invariantSatTime = invariantSatTime.intersect( invariantSatTimeSubspace );
    }
    return invariantSatTime;
}

template <typename Representation>
void DecompositionalAnalyzer<Representation>::intersectSubspacesWithClock(
  NodeVector& currentNodes, TimeInformation<Number>& clock ) {
    for ( std::size_t subspace = 0; subspace < currentNodes.size(); ++subspace ) {
        // intersect each segment with the valid time interval
        auto& flowpipe = currentNodes[ subspace ]->getFlowpipe();
        for ( std::size_t segmentIndex = 0; segmentIndex < flowpipe.size(); ++segmentIndex ) {
            auto constraintedSegment = detail::intersectSegmentWithClock( flowpipe[ segmentIndex ], clock, mClockCount );
            if ( constraintedSegment.empty() ) {
                flowpipe.resize( segmentIndex );
            } else {
                flowpipe[ segmentIndex ] = constraintedSegment;
            }
        }
    }
}

template <typename Representation>
bool DecompositionalAnalyzer<Representation>::isSafe(
  const NodeVector& nodes, const Condition<Number>& dependencies, const Condition<Number>& badState ) {

    LtiSegmentGen segments{ nodes, mDecomposition, badState, mSegmentedSubspaces };
    RepVector subspaceSets( mDecomposition.subspaces.size() );
    for ( auto subspace : mSingularSubspaces ) {
        auto [containment, set] = intersect( nodes[ subspace ]->getFlowpipe()[ 0 ], badState, subspace );
        if ( containment == CONTAINMENT::NO ) {
            return true;
        } else {
            subspaceSets[ subspace ] = set;
        }
    }
    if ( mSegmentedSubspaces.size() == 0 ) {
        HPolytope<Number> composedPolytope = detail::composeSubspaceConstraints( subspaceSets, dependencies, mDecomposition, mClockCount );
        if ( !composedPolytope.empty() ) {
            return false;
        }
    }
    for ( auto badSegment = segments.next().second; badSegment.size() > 0; badSegment = segments.next().second ) {
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
    std::vector<std::size_t> nonZeroDimensions( segment.dimension() - mClockCount + clockIndex + 1 );
    for ( std::size_t i = 0; i < nonZeroDimensions.size(); ++i ) {
        nonZeroDimensions[ i ] = i;
    }
    segment.projectOn( nonZeroDimensions );
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getJumpSuccessors( const NodeVector& nodes, std::vector<WorkerVariant> workers, Transition<Number>* trans, std::size_t clockIndex ) -> std::vector<SubspaceJumpSuccessors<Representation>> {
    auto [ singularEnabledTime, singularSuccessors ] = getSingularJumpSuccessors( nodes, workers, trans, clockIndex ); // map for subspace
    if ( mSegmentedSubspaces.size() == 0 ) {
        return { { carl::Interval<SegmentInd>( 0 ), singularSuccessors } };
    }

    std::vector<SubspaceJumpSuccessors<Representation>> res;
    std::vector<SubspaceJumpSuccessors<Representation>> segmentedSuccessors = getSegmentedJumpSuccessors( nodes, workers, trans, clockIndex ); //only segmented

    for ( auto timedSucc : segmentedSuccessors ) {
        SubspaceJumpSuccessors<Representation> nextRes;
        nextRes.time = timedSucc.time;
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
        res.push_back( nextRes );
    }
    
    return res;
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getSingularJumpSuccessors(
  const NodeVector& nodes, std::vector<WorkerVariant>& workers, Transition<Number>* trans, std::size_t clockIndex ) -> std::pair<TimeInformation<Number>, SubspaceSets> {
    for ( auto subspace : mSingularSubspaces ) {
        // compute jump successors independently for singular subspaces
        std::visit( detail::computeSingularJumpSuccessorVisitor<Representation>{ nodes[ subspace ] }, workers[ subspace ] );
    }
    TimeInformation<Number> enabledTime = mGlobalTimeInterval;
    SubspaceSets singularSuccessors;
    for ( auto subspace : mSingularSubspaces ) {
        auto timedSucc = std::visit( detail::getJumpSuccessorVisitor<Representation>{ trans }, workers[ subspace ] );
        assert( timedSucc.size() == 1 );
        auto subspaceSuccessorSet = timedSucc[ 0 ].valuationSet;
        resetClock( subspaceSuccessorSet, clockIndex );
        singularSuccessors[ subspace ] = subspaceSuccessorSet;
        enabledTime = enabledTime.intersect( detail::getClockValues( subspaceSuccessorSet, mClockCount ) );
    }
    for ( auto subspace : mSingularSubspaces ) {
        singularSuccessors[ subspace ] = detail::intersectSegmentWithClock( singularSuccessors[ subspace ], enabledTime, mClockCount );
    }
    return std::make_pair( enabledTime, singularSuccessors );
}

template <typename Representation>
auto DecompositionalAnalyzer<Representation>::getSegmentedJumpSuccessors(
        const NodeVector& nodes, std::vector<WorkerVariant>& workers, Transition<Number>* trans, std::size_t clockIndex) -> std::vector<SubspaceJumpSuccessors<Representation>> {
    LtiSegmentGen segments{ nodes, mDecomposition, trans->getGuard(), mSegmentedSubspaces };
    std::map<std::size_t, std::vector<IndexedValuationSet<Representation>>> predecessors;
    for ( auto subspace : mSegmentedSubspaces ) {
        predecessors[ subspace ] = std::vector<IndexedValuationSet<Representation>>();
    }
    for ( auto indexedSegments = segments.next(); indexedSegments.second.size() > 0; indexedSegments = segments.next() ) {
        for ( auto subspace : mSegmentedSubspaces ) {
            resetClock( indexedSegments.second[ subspace ], clockIndex );
            predecessors[ subspace ].push_back( { indexedSegments.second[ subspace ], indexedSegments.first } );
        }
    }
    std::map<std::size_t, std::vector<TimedValuationSet<Representation>>> subspaceSuccessors;
    for ( auto subspace : mSegmentedSubspaces ) {
        subspaceSuccessors[ subspace ] = std::visit( detail::getJumpSuccessorVisitor<Representation>{ trans, predecessors[ subspace ] }, workers[ subspace ] );
    }
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
