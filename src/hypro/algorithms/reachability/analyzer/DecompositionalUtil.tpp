#include "DecompositionalUtil.h"

namespace hypro {

inline bool isClockedSubspace( const DynamicType dynamics ) {
    return ( dynamics != DynamicType::affine && dynamics != DynamicType::linear && dynamics != DynamicType::discrete );
}

template <typename State>
std::vector<Point<typename State::NumberType>> composeSubspaces( const State& segment, std::size_t dim1, std::size_t dim2, Decomposition decomposition ) {
    using Number = typename State::NumberType;

    auto [subspace1, index1] = getSubspaceIndexOfDimension( dim1, decomposition );
    auto [subspace2, index2] = getSubspaceIndexOfDimension( dim2, decomposition );
    std::vector<Point<Number>> joinedVertices;
    if ( isClockedSubspace( decomposition.subspaceTypes[ subspace1 ] ) && isClockedSubspace( decomposition.subspaceTypes[ subspace2 ] ) ) {
        // iterate over both sets of vertices and get the time point of them. Join with all 
        // vertices in the other dimension intersected with the time point
        for ( auto& vertex1 : segment.vertices( subspace1 ) ) {
            Number localTime = vertex1.rawCoordinates()[ vertex1.dimension() - 2 ];
            Number globalTime = vertex1.rawCoordinates()[ vertex1.dimension() - 1 ];
            matrix_t<Number> timeConstraints = matrix_t<Number>::Zero( 4, segment.getDimension( subspace2 ) );
            vector_t<Number> timeConstants = vector_t<Number>::Zero( 4 );
            timeConstraints( 0, segment.getDimension( subspace2 ) - 2 ) = 1;
            timeConstraints( 1, segment.getDimension( subspace2 ) - 2 ) = -1;
            timeConstraints( 2, segment.getDimension( subspace2 ) - 1 ) = 1;
            timeConstraints( 3, segment.getDimension( subspace2 ) - 1 ) = -1;
            timeConstants << localTime, -1 * localTime, globalTime, -1 * globalTime;
            for ( auto& vertex2 : segment.intersectHalfspaces( timeConstraints, timeConstants, subspace2 ).vertices( subspace2 ) ) {
                joinedVertices.push_back( Point<Number>{ vertex1.rawCoordinates()[ index1 ], vertex2.rawCoordinates()[ index2 ] } );
            }
        }

        for ( auto& vertex2 : segment.vertices( subspace2 ) ) {
            Number localTime = vertex2.rawCoordinates()[ vertex2.dimension() - 2 ];
            Number globalTime = vertex2.rawCoordinates()[ vertex2.dimension() - 1 ];
            matrix_t<Number> timeConstraints = matrix_t<Number>::Zero( 4, segment.getDimension( subspace1 ) );
            vector_t<Number> timeConstants = vector_t<Number>::Zero( 4 );
            timeConstraints( 0, segment.getDimension( subspace1 ) - 2 ) = 1;
            timeConstraints( 1, segment.getDimension( subspace1 ) - 2 ) = -1;
            timeConstraints( 2, segment.getDimension( subspace1 ) - 1 ) = 1;
            timeConstraints( 3, segment.getDimension( subspace1 ) - 1 ) = -1;
            timeConstants << localTime, -1 * localTime, globalTime, -1 * globalTime;
            for ( auto& vertex1 : segment.intersectHalfspaces( timeConstraints, timeConstants, subspace1 ).vertices( subspace1 ) ) {
                joinedVertices.push_back( Point<Number>{ vertex1.rawCoordinates()[ index1 ], vertex2.rawCoordinates()[ index2 ] } );
            }
        }
    } else {
        for ( auto& vertex1 : segment.vertices( subspace1 ) ) {
            for ( auto& vertex2 : segment.vertices( subspace2 ) ) {
                joinedVertices.push_back( Point<Number>{ vertex1.rawCoordinates()[index1], vertex2.rawCoordinates()[index2] } );
            }
        }
    }
    return joinedVertices;
}

template <typename Representation>
std::vector<std::vector<Representation>> composeFlowpipes( const std::vector<ReachTreeNode<Representation>*>& nodes, const Decomposition& decomposition, tNumber timeStep, tNumber fixedTimeStep ) {
    using Number = typename Representation::NumberType;
    assert( nodes.size() == decomposition.subspaces.size() );
    std::vector<std::vector<Representation>> res;
    bool moreSegments = true;
    while ( moreSegments ) {
        moreSegments = false;
        std::vector<Representation> segment( decomposition.subspaces.size() );
        TimeInformation<Number> timing = TimeInformation<Number>{ carl::Interval<Number>::unboundedInterval(), carl::Interval<Number>::unboundedInterval() };
        for ( std::size_t subspace = 0; subspace < decomposition.subspaces.size(); ++subspace ) {
            auto& flowpipe = nodes[ subspace ]->getFlowpipe();
            if ( !isClockedSubspace( decomposition.subspaceTypes[ subspace ] ) ) {
                if ( res.size() + 1 < flowpipe.size() ) {
                    // there are more segments
                    moreSegments = true;
                }
                assert( flowpipe.size() > res.size() );
                segment[ subspace ] = flowpipe[ res.size() ];
                tNumber segmentSize = ( nodes[ subspace ]->getTimings().upper() - nodes[ subspace ]->getTimings().lower() ) * fixedTimeStep;
                timing.localTime = carl::Interval<Number>( carl::convert<tNumber, Number>( res.size() * timeStep ),
                                                           carl::convert<tNumber, Number>( ( res.size() + 1 ) * timeStep + segmentSize ) );
                timing.globalTime = carl::Interval<Number>( 
                    carl::convert<tNumber, Number>( nodes[ subspace ]->getTimings().lower() ) * fixedTimeStep + timing.localTime.lower(),
                    carl::convert<tNumber, Number>( nodes[ subspace ]->getTimings().lower() ) * fixedTimeStep + timing.localTime.upper() );
            } else {
                segment[ subspace ] = flowpipe[ 1 ];
            }
        }
        for ( std::size_t subspace = 0; subspace < decomposition.subspaces.size(); ++subspace ) {
            if ( isClockedSubspace( decomposition.subspaceTypes[ subspace ] ) ) {
                segment[ subspace] = detail::intersectSegmentWithClock( segment[ subspace ], timing, segment[ subspace ].dimension() - 2, segment[ subspace ].dimension() - 1 );
            }
        }
        res.push_back( segment );
    }
    return res;
}


namespace detail {

template <typename Representation>
TimeInformation<typename Representation::NumberType> getClockValues( const Representation& segment, int clockIndexLocal, int clockIndexGlobal ) {
    using Number = typename Representation::NumberType;
    if ( segment.empty() ) {
        return TimeInformation<Number>{};
    }
    vector_t<Number> localClockDirection = vector_t<Number>::Zero( segment.dimension() );
    localClockDirection( clockIndexLocal ) = 1;
    Number localUpper = segment.evaluate( localClockDirection ).supportValue;
    Number localLower = -1 * segment.evaluate( -1 * localClockDirection ).supportValue;

    vector_t<Number> globalClockDirection = vector_t<Number>::Zero( segment.dimension() );
    globalClockDirection( clockIndexGlobal ) = 1;
    Number globalUpper = segment.evaluate( globalClockDirection ).supportValue;
    Number globalLower = -1 * segment.evaluate( -1 * globalClockDirection ).supportValue;

    return TimeInformation<Number> {
        carl::Interval<Number>( localLower, localUpper ),
        carl::Interval<Number>( globalLower, globalUpper ) };

}

template <typename Representation>
Representation intersectSegmentWithClock(
        const Representation& segment, TimeInformation<typename Representation::NumberType> clock, int clockIndexLocal, int clockIndexGlobal ) {
    using Number = typename Representation::NumberType;
    if ( segment.empty() ) {
        return segment;
    }
    if ( clock.localTime.isUnbounded() && clock.globalTime.isUnbounded() ) {
        return segment;
    }
    if ( clock.localTime.isEmpty() || clock.globalTime.isEmpty() ) {
        return Representation::Empty();
    }
    vector_t<Number> localClockDirection = vector_t<Number>::Zero( segment.dimension() );
    localClockDirection( clockIndexLocal ) = 1;
    Halfspace<Number> localUpper( localClockDirection, clock.localTime.upper() );
    Halfspace<Number> localLower( -1 * localClockDirection, clock.localTime.lower() );

    vector_t<Number> globalClockDirection = vector_t<Number>::Zero( segment.dimension() );
    globalClockDirection( clockIndexGlobal ) = 1;
    Halfspace<Number> globalUpper( globalClockDirection, clock.globalTime.upper() );
    Halfspace<Number> globalLower( -1 * globalClockDirection, -1 * clock.globalTime.lower() );

    HPolytope<Number> segmentAsHpol;
    Representation constrainedSegment;
    convert( segment, segmentAsHpol );
    segmentAsHpol.insert( globalUpper );
    segmentAsHpol.insert( globalLower );
    segmentAsHpol.insert( localUpper );
    segmentAsHpol.insert( localLower );
    convert( segmentAsHpol, constrainedSegment );
    return constrainedSegment;
}

template <typename Number>
TimeInformation<Number> intersectTimeInformation( const TimeInformation<Number>& clock1, const TimeInformation<Number>& clock2 ) {
    return TimeInformation<Number> {
        carl::set_intersection( clock1.localTime, clock2.localTime ),
        carl::set_intersection( clock1.globalTime, clock2.globalTime ) };
}

template <typename Representation>
Representation resetClock( const Representation& segment, std::size_t clockIndex ) {
    using Number = typename Representation::NumberType;
    if ( segment.empty() ) {
        return segment;
    }
    assert( clockIndex < segment.dimension() && "Clock index too large");
    matrix_t<Number> resetMat = matrix_t<Number>::Identity( segment.dimension(), segment.dimension() );
    resetMat( clockIndex, clockIndex ) = 0;
    return segment.linearTransformation( resetMat );
}

template <typename Number>
std::vector<Condition<Number>> collectBadStates( const HybridAutomaton<Number>* ha, const Location<Number>* loc ) {
    auto badStates = ha->getGlobalBadStates();
    auto localBadState = ha->getLocalBadStates().find( loc );
    if ( localBadState != ha->getLocalBadStates().end() ) {
        badStates.push_back( localBadState->second );
    }
    return badStates;
}
} // namespace detail
} // namespace hypro