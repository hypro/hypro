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
            Representation nextSegment = applyTimeEvolution( previousSegment, mTrafoCache.transformationMatrix( loc, mSettings.timeStep ) );
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
    if ( std::any_of( nonUrgentEnabled.begin(), nonUrgentEnabled.end(), []( const auto& splitSegment ) {
            return ltiIntersectBadStates( splitSegment, loc, mHybridAutomaton ).first != CONTAINMENT::NO } ) ) {
        return REACHABILITY_RESULT::UNKNOWN;
    }
    return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
std::vector<JumpSuccessor<Representation>> UrgencyWorker<Representation>::computeJumpSuccessors( const ReachTreeNode<Representation>& task ) const {
}

template <typename Representation>
struct UrgencyWorker<Representation>::PreviousSegmentGen {
    std::size_t current = 1; // index 0 is initial set

    std::optional<Representation> next( SegmentInd nextSegment ) {
        if ( current < mFlowpipe.size() ) {
            indexedSegment = mFlowpipe.at( current );
            if ( indexedSegment.index == nextSegment - 1 ) {
                current += 1;
                return indexedSegment.valuationSet;
            }
        }
        return std::nullopt;
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
