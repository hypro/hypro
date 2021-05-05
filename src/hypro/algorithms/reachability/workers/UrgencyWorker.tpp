#include "UrgencyWorker.h"

namespace hypro {

template <typename Representation>
REACHABILITY_RESULT UrgencyWorker<Representation>::computeTimeSuccessors( const ReachTreeNode<Representation>& task ) const {
    Location<Number>* loc = task.getLocation();
    Representation initialSet = task.getInitialSet();

    // initial set should not consider urgent guards, so it is treated separately
    auto initialInv = intersect( initialSet, loc->getInvariant() ).second;
    assert( !initialSet.empty() );
    task.getFlowpipe().push_back( initialInv );
    task.getTimings().push_back( 0 );
    if ( ltiIntersectBadStates( initialInv, loc, mHybridAutomaton ).first != CONTAINMENT::NO ) {
        return REACHABILITY_RESULT::UNKNOWN;
    }

    Representation firstSegment = constructFirstSegment( initialSet, loc->getLinearFlow(), mTrafoCache.transformationMatrix( loc, mSettings.timeStep ), mSettings.timeStep );

    auto [containment, firstSegmentInv] = intersect( firstSegment, loc->getInvariant() );
    //If the first segment did not fulfill the invariant of the location, the jump here should not have been made
    assert( containment != CONTAINMENT::NO );

    // set difference with urgent guards
    std::vector<Representation> firstSegments = urgentSetDifference( task, firstSegmentInv );
    

    for ( const auto& segment : firstSegments ) {
        if ( segment.empty() ) continue;
        task.getFlowpipe().push_back( segment );
        task.getTimings().push_back( 0 );
    }

    if ( std::any_of( firstSegments.begin(), firstSegments.end(), []( const auto& segment ) {
            return ltiIntersectBadStates( segment, loc, mHybridAutomaton ).first != CONTAINMENT::NO; } ) ) {
        return REACHABILITY_RESULT::UNKNOWN;
    }

    std::size_t flowpipeIndex = 0;
    for ( std::size_t segmentIndex = 1; segmentIndex < mNumSegments; ++segmentIndex ) {
        // iterate over all previous segments
        for ( ; task.getTimings()[ flowpipeIndex ] == segmentIndex - 1; ++ flowpipeIndex ) {
            Representation previousSegment = task.getFlowpipe()[ flowpipeIndex ];
            Representation nextSegment = applyTimeEvolution( previousSegment, mTrafoCache.transformationMatrix( loc, mSettings.timeStep ) );
            Representation nextSegmentInv = intersect( firstSegment, loc->getInvariant() ).second;
            std::vector nextSegments = urgentSetDifference( task, nextSegmentInv );
            if ( std::any_of( nextSegments.begin(), nextSegments.end(), []( const auto& segment ) {
                    return ltiIntersectBadStates( segment, loc, mHybridAutomaton ).first != CONTAINMENT::NO; } ) ) {
                return REACHABILITY_RESULT::UNKNOWN;
            }
            for ( const auto& segment : nextSegments ) {
                if ( segment.empty() ) continue;
                task.getFlowpipe().push_back( segment );
                task.getTimings().push_back( segmentIndex );
            }
        }
    }
    return REACHABILITY_RESULT::SAFE;

}

template <typename Representation>
std::vector<Representation> UrgencyWorker<Representation>::urgentSetDifference( const ReachTreeNode<Representation>& task, const Representation& segment ) {
    std::vector<Representation> segments{ segment };
    for ( const auto& transitionPtr : task.getLocation().getTransitions() ) {
        std::vector<Representation> setDifferenceSegments;
        if ( transitionPtr->isUrgent() && std::find( task.getIgnoreUrgent().begin(), task.getIgnoreUrgent().end(), transitionPtr.get() ) == task.getIgnoreUrgent().end() ) {
            while( !segments.empty() ) {
                Representation nextSegment = segments.back();
                segments.pop_back();
                std::vector<Representation> computedSetDifference = setDifference( nextSegment, transitionPtr->getGuard() );
                setDifferenceSegments.insert( setDifferenceSegments.end(), computedSetDifference.begin(), computedSetDifference.end() );
            }
        }
        segments = setDifferenceSegments;
    }
    return segments;
}

template <typename Representation>
std::vector<JumpSuccessor<Representation>> UrgencyWorker<Representation>::computeJumpSuccessors( const ReachTreeNode<Representation>& task ) const {

}