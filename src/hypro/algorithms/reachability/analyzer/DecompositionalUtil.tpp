#include "DecompositionalUtil.h"

namespace hypro {

inline bool isClockedSubspace( const DynamicType dynamics ) {
    return ( dynamics != DynamicType::affine && dynamics != DynamicType::linear && dynamics != DynamicType::discrete );
}

template <typename State>
std::vector<Point<typename State::NumberType>> composeSubspaces( const State& segment, std::size_t dim1, std::size_t dim2, Decomposition decomposition, std::size_t clockCount ) {
    using Number = typename State::NumberType;

    auto [subspace1, index1] = getSubspaceIndexOfDimension( dim1, decomposition );
    auto [subspace2, index2] = getSubspaceIndexOfDimension( dim2, decomposition );
    std::vector<Point<Number>> joinedVertices;
    if ( isClockedSubspace( decomposition.subspaceTypes[ subspace1 ] ) && isClockedSubspace( decomposition.subspaceTypes[ subspace2 ] ) ) {
        // iterate over both sets of vertices and get the time point of them. Join with all 
        // vertices in the other dimension intersected with the time point

        for ( auto& vertex1 : segment.vertices( subspace1 ) ) {
            matrix_t<Number> timeConstraints = matrix_t<Number>::Zero( 2 * clockCount, segment.getDimension( subspace2 ) );
            vector_t<Number> timeConstants = vector_t<Number>::Zero( 2 * clockCount );
            for ( std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex ) {
                timeConstraints( 2 * clockIndex, segment.getDimension( subspace2 ) - clockCount + clockIndex ) = 1;
                timeConstraints( 2 * clockIndex + 1, segment.getDimension( subspace2 ) - clockCount + clockIndex ) = -1;
                timeConstants( 2 * clockIndex ) = vertex1.rawCoordinates()[ vertex1.dimension() - clockCount + clockIndex ];
                timeConstants( 2 * clockIndex + 1 ) = -1 * vertex1.rawCoordinates()[ vertex1.dimension() - clockCount + clockIndex ];
            }
            for ( auto& vertex2 : segment.intersectHalfspaces( timeConstraints, timeConstants, subspace2 ).vertices( subspace2 ) ) {
                joinedVertices.push_back( Point<Number>{ vertex1.rawCoordinates()[ index1 ], vertex2.rawCoordinates()[ index2 ] } );
            }
        }

        for ( auto& vertex2 : segment.vertices( subspace2 ) ) {
            matrix_t<Number> timeConstraints = matrix_t<Number>::Zero( 2 * clockCount, segment.getDimension( subspace1 ) );
            vector_t<Number> timeConstants = vector_t<Number>::Zero( 2 * clockCount );
            for ( std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex ) {
                timeConstraints( 2 * clockIndex, segment.getDimension( subspace1 ) - clockCount + clockIndex ) = 1;
                timeConstraints( 2 * clockIndex + 1, segment.getDimension( subspace1 ) - clockCount + clockIndex ) = -1;
                timeConstants( 2 * clockIndex ) = vertex2.rawCoordinates()[ vertex2.dimension() - clockCount + clockIndex ];
                timeConstants( 2 * clockIndex + 1 ) = -1 * vertex2.rawCoordinates()[ vertex2.dimension() - clockCount + clockIndex ];
            }
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
std::vector<std::vector<Representation>> composeFlowpipes( const std::vector<ReachTreeNode<Representation>*>& nodes, const Decomposition& decomposition, FixedAnalysisParameters settings, std::size_t clockCount ) {
    using Number = typename Representation::NumberType;
    assert( nodes.size() == decomposition.subspaces.size() );
    std::vector<std::vector<Representation>> res;
    bool moreSegments = true;
    while ( moreSegments ) {
        moreSegments = false;
        std::vector<Representation> segment( decomposition.subspaces.size() );
        TimeInformation<Number> segmentTime( clockCount >= 1 ? clockCount : 1, Number( 0 ), carl::convert<tNumber, Number>( settings.localTimeHorizon * settings.jumpDepth ) );
        for ( std::size_t subspace = 0; subspace < decomposition.subspaces.size(); ++subspace ) {
            auto& flowpipe = nodes[ subspace ]->getFlowpipe();
            if ( !isClockedSubspace( decomposition.subspaceTypes[ subspace ] ) ) {
                if ( res.size() + 1 < flowpipe.size() ) {
                    // there are more segments
                    moreSegments = true;
                }
                assert( flowpipe.size() > res.size() );
                segment[ subspace ] = flowpipe[ res.size() ];
                tNumber segmentSize = ( nodes[ subspace ]->getTimings().upper() - nodes[ subspace ]->getTimings().lower() ) * settings.fixedTimeStep;
                // get global time interval
                segmentTime.setTimeInterval( 0, carl::Interval<Number>( 
                    carl::convert<tNumber, Number>( nodes[ subspace ]->getTimings().lower() ) * settings.fixedTimeStep + carl::convert<tNumber, Number>( res.size() * settings.fixedTimeStep ),
                    carl::convert<tNumber, Number>( nodes[ subspace ]->getTimings().lower() ) * settings.fixedTimeStep + carl::convert<tNumber, Number>( ( res.size() + 1 ) * settings.fixedTimeStep + segmentSize ) ) );
            } else {
                segment[ subspace ] = flowpipe[ 1 ];
            }
        }
        for ( std::size_t subspace = 0; subspace < decomposition.subspaces.size(); ++subspace ) {
            if ( isClockedSubspace( decomposition.subspaceTypes[ subspace ] ) ) {
                segment[ subspace] = detail::intersectSegmentWithClock( segment[ subspace ], segmentTime, segment[ subspace ].dimension() - 1 );
            }
        }
        res.push_back( segment );
    }
    return res;
}


namespace detail {

template <typename Representation>
TimeInformation<typename Representation::NumberType> getClockValues( const Representation& segment, std::size_t clockCount ) {
    using Number = typename Representation::NumberType;
    TimeInformation<Number> clockValues( clockCount );
    if ( segment.empty() ) {
        return clockValues;
    }

    for ( std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex ) {
        vector_t<Number> clockDirection = vector_t<Number>::Zero( segment.dimension() );
        clockDirection( segment.dimension() - clockCount + clockIndex ) = 1;
        Number clockUpper = segment.evaluate( clockDirection ).supportValue;
        Number clockLower = -1 * segment.evaluate( -1 * clockDirection ).supportValue;
        clockValues.setTimeInterval( clockIndex, carl::Interval<Number>( clockLower, clockUpper ) );
    }
    return clockValues;
}

template <typename Representation>
Representation intersectSegmentWithClock(
        const Representation& segment, TimeInformation<typename Representation::NumberType> clockValues, std::size_t clockCount ) {
    using Number = typename Representation::NumberType;
    if ( segment.empty() ) {
        return segment;
    }
    if ( clockValues.empty() ) {
        return Representation::Empty();
    }
    HPolytope<Number> segmentHpoly;
    convert( segment, segmentHpoly );
    for ( std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex ) {
        vector_t<Number> clockDirection = vector_t<Number>::Zero( segment.dimension() );
        clockDirection( segment.dimension() - clockCount + clockIndex ) = 1;
        Halfspace<Number> upperBound( clockDirection, clockValues.getTimeInterval( clockIndex ).upper() );
        Halfspace<Number> lowerBound( -1 * clockDirection, -1 * clockValues.getTimeInterval( clockIndex ).lower() );
        segmentHpoly.insert( upperBound );
        segmentHpoly.insert( lowerBound );
    }
    Representation constrainedSegment;
    convert( segmentHpoly, constrainedSegment );
    return constrainedSegment;
}

template <typename Representation>
Representation resetClocks( const Representation& segment, std::size_t clockCount, std::size_t jumpDepth ) {
    using Number = typename Representation::NumberType;
    if ( segment.empty() ) {
        return segment;
    }
    matrix_t<Number> resetMat = matrix_t<Number>::Identity( segment.dimension(), segment.dimension() );
    for ( std::size_t clockIndex = segment.dimension() - clockCount + jumpDepth; clockIndex < segment.dimension(); ++clockIndex ) {
        resetMat( clockIndex, clockIndex ) = 0;
    }
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