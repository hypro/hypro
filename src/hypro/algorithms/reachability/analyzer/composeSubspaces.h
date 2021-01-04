#pragma once
#include <hypro/types.h>
#include <hypro/algorithms/reachability/types.h>
#include <hypro/algorithms/reachability/analyzer/DecompositionalUtil.h>
#include <hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h>

namespace hypro {

/**
 * @brief       Construct vertices of two-dimensional projection of the segment on dim1 and dim2.
 * @details     The dimension indices are absolute, i.e. referring to the original, not decomposed automaton.
 *              If both dimensions are in a subspace with a clock, then the vertices will be synchronized
 *              using the clock values, otherwise the cartesian product of the subspace-sets will be constructed.
 * @tparam      State           A templated State class used to represent the segment.
 * @param       dim1            The dimension of the first variable to compose.
 * @param       dim2            The dimension of the second variable to compose.
 * @param       decomposition   Information on the decomposition used to compute the subspaces of the variables. 
 * @return      The vertices of the composed and projected set.
 */
template <typename State>
std::vector<Point<typename State::NumberType>> composeSubspaces( const State& segment, std::size_t dim1, std::size_t dim2, Decomposition decomposition ) {
    using Number = typename State::NumberType;

    auto [subspace1, index1] = getSubspaceIndexOfDimension( dim1, decomposition );
    auto [subspace2, index2] = getSubspaceIndexOfDimension( dim2, decomposition );
    std::vector<Point<Number>> joinedVertices;
    auto vertices1 = segment.vertices( subspace1 );
    auto vertices2 = segment.vertices( subspace2 );
    if ( isClockedSubspace( decomposition.subspaceTypes[ subspace1 ] ) && isClockedSubspace( decomposition.subspaceTypes[ subspace2 ] ) ) {
        for ( auto& vertex1 : vertices1 ) {
            for ( auto& vertex2 : vertices2 ) {
                if ( vertex1.rawCoordinates()[ vertex1.dimension() - 2 ] == vertex2.rawCoordinates()[ vertex2.dimension() - 2 ] &&
                    vertex1.rawCoordinates()[ vertex1.dimension() - 1 ] == vertex2.rawCoordinates()[ vertex2.dimension() - 1 ] ) {
                    joinedVertices.push_back( Point<Number>{ vertex1.rawCoordinates()[index1], vertex2.rawCoordinates()[index2] } );
                }
            }
        }
    } else {
        for ( auto& vertex1 : vertices1 ) {
            for ( auto& vertex2 : vertices2 ) {
                joinedVertices.push_back( Point<Number>{ vertex1.rawCoordinates()[index1], vertex2.rawCoordinates()[index2] } );
            }
        }
    }
    return joinedVertices;
}

/**
 * @brief       Join flowpipes of subspaces and return a single flowpipe with vectors representing the composed segments.
 * @details     If there is any subspace without clock (i.e. it has multiple segments for each flowpipe and uses a time-step)
 *              Then the flowpipes are synchronized using that time step (discretized time). Otherwise each flowpipe
 *              has one segment for each subspace that represents the entire time-elapse.
 * @tparam      Representation  The state-set representation of the segments in the flowpipes.
 * @param       nodes           Pointers to the nodes holding the flowpipes (one for each subspace).
 * @param       decomposition   Information on the decomposition. 
 * @param       timeStep        The analyzer specific time step used in analysis.
 * @param       fixedTimeStep   The fixed time step used in analysis.
 * @return      A single flowpipe with vectors as segments representing the subspace-sets.
 */
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
}