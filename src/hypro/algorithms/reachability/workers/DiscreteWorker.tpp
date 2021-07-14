#include "DiscreteWorker.h"

namespace hypro {

template <typename Representation>
template <typename OutputIt>
REACHABILITY_RESULT DiscreteWorker<Representation>::computeTimeSuccessors( const Representation& initialSet, Location<Number> const* loc, OutputIt out, bool checkSafety ) const {

    auto [containment, segment] = intersect( initialSet, loc->getInvariant(), mSubspace );
    //If the first segment did not fulfill the invariant of the location, the jump here should not have been made
    assert( containment != CONTAINMENT::NO );

    // insert segment
    *out = segment;
    ++out;

    // intersect with badstates
    if ( checkSafety ) {
        std::tie( containment, std::ignore ) = ltiIntersectBadStates( segment, loc, mHybridAutomaton, mSubspace );
        if ( containment != CONTAINMENT::NO ) {
            return REACHABILITY_RESULT::UNKNOWN;
        }
    }

    return REACHABILITY_RESULT::SAFE;
}

template <typename Representation>
std::vector<JumpSuccessor<Representation>> DiscreteWorker<Representation>::computeJumpSuccessors( std::vector<Representation> const& flowpipe, Location<Number> const* loc ) const {
    TRACE( "hypro", "flowpipe: " << print( flowpipe ) );

    //transition x enabled segments, segment ind
    std::vector<EnabledSets<Representation>> enabledSegments{};

    // todo: do not add empty enabled sets
    for ( const auto& transition : loc->getTransitions() ) {
        auto& currentSucc = enabledSegments.emplace_back( EnabledSets<Representation>{ transition.get() } );

        SegmentInd cnt = 0;
        for ( auto const& valuationSet : flowpipe ) {
            auto [containment, intersected] = intersect( valuationSet, transition->getGuard() );

            if ( containment != CONTAINMENT::NO ) {
                currentSucc.valuationSets.push_back( { intersected, cnt } );
            }
            ++cnt;
        }
    }

    TRACE( "hypro", "enabledSegments: " << print( enabledSegments ) );

    std::vector<JumpSuccessor<Representation>> successors{};

    // for each transition
    for ( auto& [transition, valuationSets] : enabledSegments ) {
        assert( valuationSets.size() <= 1 );
        if ( valuationSets.size() == 1 ) {
            successors.emplace_back( JumpSuccessor<Representation>{ transition, { { valuationSets[ 0 ].valuationSet, carl::Interval<SegmentInd>( 0 ) } } } );
        }
    }

    // applyReset
    for ( auto& [transition, valuationSets] : successors ) {
        // todo: skip inner loop (valuationSets[0])
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

    return successors;
}

template<typename Representation>
std::vector<TimedValuationSet<Representation>> DiscreteWorker<Representation>::computeJumpSuccessorsForGuardEnabled( std::vector<IndexedValuationSet<Representation>>& predecessors, Transition<Number> const* transition ) const {

    assert( predecessors.size() == 1 );
    std::vector<TimedValuationSet<Representation>> valuationSets{ TimedValuationSet<Representation>{ predecessors[ 0 ].valuationSet, predecessors[ 0 ].index } };
    for ( auto it = valuationSets.begin(); it != valuationSets.end(); ) {
        it->valuationSet = applyReset( it->valuationSet, transition->getReset(), mSubspace );
        CONTAINMENT containment;
        std::tie( containment, it->valuationSet ) = intersect( it->valuationSet, transition->getTarget()->getInvariant(), mSubspace );
        if ( containment == CONTAINMENT::NO ) {
            it = valuationSets.erase( it );
        } else {
            it->valuationSet.reduceRepresentation();
            ++it;
        }
    }

    return valuationSets;
}


}  // namespace hypro
