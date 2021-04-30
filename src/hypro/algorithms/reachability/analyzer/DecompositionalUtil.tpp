#include "DecompositionalUtil.h"

namespace hypro {

inline bool isClockedSubspace( const DynamicType dynamics ) {
    return ( dynamics != DynamicType::affine && dynamics != DynamicType::linear && dynamics != DynamicType::discrete );
}



namespace detail {

template <typename Representation>
HPolytope<typename Representation::NumberType> composeSubspaceConstraints( const std::vector<Representation>& subspaceSets, const Condition<typename Representation::NumberType>& dependencies, std::size_t clockCount ) {

    using Number = typename Representation::NumberType;
    // variable order in subspace sets: (x_i, x_i^init, c_i^1,...,c_i^clockCount)
    // variable order in dependencies: (x_1^init,...,x_n^init)
    // create composed polytope with dimension (dim(S_1) + .. + dim(S_n))
    // the variables are ordered by concatenating the variables in the subspaces
    std::size_t subspaceCount = subspaceSets.size();
    std::size_t compDim = subspaceCount * ( 2 + clockCount );

    // number of rows in full poytope
    std::size_t compRows = 0;
    compRows += std::accumulate( subspaceSets.begin(), subspaceSets.end(), 0, 
        []( std::size_t cur, const auto& sSet ) { return cur + sSet.matrix().rows(); } );
    compRows += dependencies.getMatrix().rows();
    // 2 inequalities for each equation c_1 = c_i in the subspaces i != 1 (per clock c)
    compRows += 2 * ( clockCount * ( subspaceCount - 1 ) );

    matrix_t<Number> compMat = matrix_t<Number>::Zero( compRows, compDim );
    vector_t<Number> compVec = vector_t<Number>::Zero( compRows );
    std::size_t accDim = 0;
    std::size_t accRows = 0;

    for ( std::size_t i = 0; i < subspaceCount; ++i ) {
        auto subspaceMatrix = subspaceSets[ i ].matrix();
        auto subspaceVector = subspaceSets[ i ].vector();
        compMat.block( accRows, accDim, subspaceMatrix.rows(), subspaceMatrix.cols() ) = subspaceMatrix;
        compVec.segment( accRows, subspaceVector.rows() ) = subspaceVector;
        accDim += subspaceSets[ i ].dimension();
        accRows += subspaceMatrix.rows();
    }

    if ( !dependencies.isTrue() ) {
        assert( dependencies.dimension() == subspaceCount );
        // add constraints of dependencies on x_i^init
        for ( std::size_t i = 0; i < subspaceCount; ++i ) {
            compMat.block( accRows, i * ( 2 + clockCount ) + 1, dependencies.getMatrix().rows(), 1  ) = dependencies.getMatrix().col( i );
            compVec.segment( accRows, dependencies.getVector().rows() ) = dependencies.getVector();
        }
        accRows += dependencies.getMatrix().rows();
    }

    // add constraints for clock equality
    for ( std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex ) {
        for ( std::size_t subspace = 1; subspace < subspaceCount; ++subspace ) {
            compMat( accRows, 2 + clockIndex ) = 1;
            compMat( accRows, subspace * ( 2 + clockCount ) + clockIndex + 2 ) = -1;
            compMat( accRows + 1, 2 + clockIndex ) = -1;
            compMat( accRows + 1, subspace * ( 2 + clockCount ) + clockIndex + 2 ) = 1;
            accRows += 2;
        }
    }

    return HPolytope<Number>( compMat, compVec );

}


template <typename Representation>
Representation composeSubspaces( const std::vector<Representation>& subspaceSets, const Condition<typename Representation::NumberType>& dependencies, std::size_t clockCount ) {
    using Number = typename Representation::NumberType;

    auto pol = composeSubspaceConstraints( subspaceSets, dependencies, clockCount );
    std::vector<std::size_t> toProject;
    for ( std::size_t i = 0; i < subspaceSets.size(); ++i ) {
        toProject.push_back( i * ( 2 + clockCount ) );
    }
    std::vector<std::size_t> projectOut;
    for ( std::size_t i = pol.dimension() - 1;; --i ) {
        if ( std::find( toProject.begin(), toProject.end(), i ) == toProject.end() ) {
            projectOut.push_back( i );
        }
        if ( i == 0 ) { break; }
    }
    pol = pol.projectOut( projectOut );
    Representation res;
    convert( pol, res );
    return res;
}

template <typename Representation>
std::pair<Condition<typename Representation::NumberType>, std::vector<Representation>> decompose( const Representation& composedSet, std::size_t clockCount ) {
    using Number = typename Representation::NumberType;

    // distribute rows among subspaces. If a row has multiple nonzero entries, it is a dependency between subspaces
    std::vector<Eigen::Index> depIndices;
    std::vector<std::vector<Eigen::Index>> subspaceIndices( composedSet.dimension() );
    for ( Eigen::Index row = 0; row < composedSet.matrix().rows(); ++row ) {
        Eigen::Index nonZeroSubspace;
        bool allZero = true;
        bool dependency = false;
        for ( std::size_t col = 0; col < composedSet.matrix().cols(); ++col ) {
            if ( composedSet.matrix()( row, col ) != 0 ) {
                if ( !allZero ) {
                    dependency = true;
                    break;
                } else {
                    nonZeroSubspace = col;
                    allZero = false;
                }
            }
        }
        if ( !dependency ) {
            subspaceIndices[ nonZeroSubspace ].push_back( row );
        } else {
            depIndices.push_back( row );
        }
    }

    std::vector<Representation> subspaceSets( composedSet.dimension() );
    // add initial variable and clocks
    for ( std::size_t subspace = 0; subspace < subspaceSets.size(); ++subspace ) {
        matrix_t<Number> subspaceMatrix = matrix_t<Number>::Zero( subspaceIndices[ subspace ].size() + 2 * ( clockCount + 1 ), clockCount + 2 );
        vector_t<Number> subspaceVector = vector_t<Number>::Zero( subspaceMatrix.rows() );
        std::size_t usedRows = 0;
        for ( auto row : subspaceIndices[ subspace ] ) {
            subspaceMatrix( usedRows, 0 ) = composedSet.matrix()( row, subspace );
            subspaceVector( usedRows ) = composedSet.vector()( row );
            usedRows++;
        }
        // initial constraint
        subspaceMatrix( usedRows, 0 ) = 1;
        subspaceMatrix( usedRows, 1 ) = -1;
        subspaceMatrix( usedRows + 1, 0 ) = -1;
        subspaceMatrix( usedRows + 1, 1 ) = 1;
        usedRows += 2;

        // clocks to zero
        for ( std::size_t clock = 0; clock < clockCount; ++clock ) {
            subspaceMatrix( usedRows, 2 + clock ) = 1;
            subspaceMatrix( usedRows + 1, 2 + clock ) = -1;
            usedRows += 2;
        }
        subspaceSets[ subspace ] = Representation{ subspaceMatrix, subspaceVector };
    }

    matrix_t<Number> depMatrix( depIndices.size(), composedSet.dimension() );
    vector_t<Number> depVector( depIndices.size() );
    for ( std::size_t row = 0; row < depIndices.size(); ++row ) {
        depMatrix.row( row ) = composedSet.matrix().row( depIndices[ row ] );
        depVector( row ) = composedSet.vector()( depIndices[ row ] );
    }
    Condition<Number> dependencies( depMatrix, depVector );
    return std::make_pair( dependencies, subspaceSets );
}

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