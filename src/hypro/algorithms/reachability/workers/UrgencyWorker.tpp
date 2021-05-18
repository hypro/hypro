#include "UrgencyWorker.h"

namespace hypro {

template <typename Representation>
REACHABILITY_RESULT UrgencyWorker<Representation>::computeTimeSuccessors( const ReachTreeNode<Representation>& task ) {
    Location<Number>* loc = task.getLocation();
    Representation initialSet = task.getInitialSet();

    // initial set should not consider urgent guards, so it is treated separately
    auto [containmentInitial, constraintedInitial] = intersect( initialSet, loc->getInvariant() );
    assert( containmentInitial != CONTAINMENT::NO );
    addSegment( constraintedInitial, 0 );
    if ( ltiIntersectBadStates( constraintedInitial, loc, mHybridAutomaton ).first != CONTAINMENT::NO ) {
        return REACHABILITY_RESULT::UNKNOWN;
    }

    // first segment
    Representation firstSegment = constructFirstSegment(
        initialSet,
        loc->getLinearFlow(),
        mTrafoCache.transformationMatrix( loc, mSettings.timeStep ),
        mSettings.timeStep );

    REACHABILITY_RESULT firstSegmentSafety = handleSegment( task, firstSegment, 0 );
    if ( firstSegmentSafety != REACHABILITY_RESULT::SAFE ) {
        return REACHABILITY_RESULT::UNKNOWN;
    }

    // time elapse
    PreviousSegmentGen prevGen;
    for ( std::size_t segmentIndex = 1; segmentIndex < mNumSegments; ++segmentIndex ) {
        for ( auto prevSegment = prevGen.next( segmentIndex ); prevSegment; prevSegment = prevGen.next( segmentIndex ) ) {
            Representation nextSegment = applyTimeEvolution( prevSegment, mTrafoCache.transformationMatrix( loc, mSettings.timeStep ) );
            REACHABILITY_RESULT safety = handleSegment( task, nextSegment, segmentIndex );
            if ( safety != REACHABILITY_RESULT::SAFE ) {
                return REACHABILITY_RESULT::UNKNOWN;
            }
        }
    }

    return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
REACHABILITY_RESULT UrgencyWorker<Representation>::handleSegment(
        const ReachTreeNode<Representation>& task, const Representation& segment, SegmentInd timing ) {
    Location<Number>* loc = task.getLocation();
    ltiUrgencyHandler<Representation> urgencyHandler;

    // invariant
    auto [containment, constrainedSegment] = intersect( segment, loc->getInvariant() );
    if ( containment == CONTAINMENT::NO ) {
        return REACHABILITY_RESULT::SAFE;
    }

    // urgent guards
    std::vector<Representation> nonUrgentEnabled{ constrainedSegment };
    for ( auto trans : task.getUrgent() ) {
        nonUrgentEnabled = urgencyHandler.urgentSetDifference( nonUrgentEnabled, trans );
    }
    addSegment( nonUrgentEnabled, timing );

    // safety check
    if ( std::any_of( nonUrgentEnabled.begin(), nonUrgentEnabled.end(), [ loc, this ]( const auto& splitSegment ) {
            return ltiIntersectBadStates( splitSegment, loc, mHybridAutomaton ).first != CONTAINMENT::NO; } ) ) {
        return REACHABILITY_RESULT::UNKNOWN;
    }
    return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
struct UrgencyWorker<Representation>::PreviousSegmentGen {
    std::size_t current = 1; // index 0 is initial set

    std::optional<Representation> next( SegmentInd nextSegment ) {
        if ( current < mFlowpipe.size() ) {
            auto indexedSegment = mFlowpipe.at( current );
            if ( indexedSegment.index == nextSegment - 1 ) {
                current += 1;
                return indexedSegment.valuationSet;
            }
        }
        return std::nullopt;
    }
};


template <typename Representation>
void UrgencyWorker<Representation>::computeJumpSuccessors( const ReachTreeNode<Representation>& task ) {
    Location<Number>* loc = task.getLocation();

    //transition x enabled segments, segment ind
    std::vector<EnabledSets<Representation>> enabledSegments{};
    for ( const auto& transition : loc->getTransitions() ) {
        auto& currentSucc = enabledSegments.emplace_back( EnabledSets<Representation>{ transition.get() } );

        for ( std::size_t i = 0; i < mFlowpipe.size(); ++i ) {
            auto [containment, intersected] = intersect( mFlowpipe[ i ].valuationSet, transition->getGuard() );

            if ( containment != CONTAINMENT::NO ) {
                currentSucc.valuationSets.push_back( { intersected, mFlowpipe[ i ].index } );
            }
        }
    }

    std::vector<JumpSuccessor<Representation>> successors{};

    // aggregation
    // for each transition
    for ( auto& [transition, valuationSets] : enabledSegments ) {
        // no aggregation
        std::size_t blockSize = 1;
        if ( mSettings.aggregation == AGG_SETTING::AGG ) {
            if ( mSettings.clustering > 0 ) {
                blockSize = ( valuationSets.size() + mSettings.clustering ) / mSettings.clustering;  //division rounding up
            } else {
                blockSize = valuationSets.size();
            }

        } else if ( mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() != Aggregation::none ) {
            if ( transition->getAggregation() == Aggregation::clustering ) {
                blockSize = ( blockSize + transition->getClusterBound() ) / transition->getClusterBound();  //division rounding up
            }
        }
        mJumpSuccessors.emplace_back( JumpSuccessor<Representation>{ transition, aggregate( blockSize, valuationSets ) } );
    }

    // applyReset
    for ( auto& [transition, valuationSets] : successors ) {
        for ( auto it = valuationSets.begin(); it != valuationSets.end(); ) {
            TRACE( "hypro", "valSet: " << it->valuationSet.vertices() );
            it->valuationSet = applyReset( it->valuationSet, transition->getReset() );
            TRACE( "hypro", "Reset is: " << transition->getReset() );
            TRACE( "hypro", "Reset: " << it->valuationSet.vertices() );
            CONTAINMENT containment;
            std::tie( containment, it->valuationSet ) = intersect( it->valuationSet, transition->getTarget()->getInvariant() );
            TRACE( "hypro", "Intersect: " << it->valuationSet.vertices() );
            if ( containment == CONTAINMENT::NO ) {
                it = valuationSets.erase( it );
            } else {
                it->valuationSet.reduceRepresentation();
                TRACE( "hypro", "Reduce: " << it->valuationSet.vertices() );
                ++it;
            }
        }
    }
}

template <typename Representation>
void UrgencyWorker<Representation>::addSegment( const Representation& segment, SegmentInd timing ) {
    mFlowpipe.push_back( IndexedValuationSet<Representation>{ segment, timing } );
}

template <typename Representation>
void UrgencyWorker<Representation>::addSegment( const std::vector<Representation>& segment, SegmentInd timing ) {
    for ( auto splitSegment : segment ) {
        if ( !splitSegment.empty() ) {
            mFlowpipe.push_back( IndexedValuationSet<Representation>{ splitSegment, timing } );
        }
    }
}

} // namespace hypro
