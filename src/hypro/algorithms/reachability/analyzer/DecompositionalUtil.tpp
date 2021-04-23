#include "DecompositionalUtil.h"

namespace hypro {

inline bool isClockedSubspace( const DynamicType dynamics ) {
    return ( dynamics != DynamicType::affine && dynamics != DynamicType::linear && dynamics != DynamicType::discrete );
}



namespace detail {

template <typename Representation>
Representation composeSubspaces( const std::vector<Representation>& subspaceSets, const Condition<typename Representation::NumberType>& dependencies, std::size_t clockCount ) {
    using Number = typename Representation::NumberType;
    // variable order in subspace sets: (x_i, x_i^init, c_i^1,...,c_i^clockCount)
    // variable order in dependencies: (x_1^init,...,x_n^init)
    // initialize polytope with dimension (dim(S_1) + .. + dim(S_n))
    // the variables are ordered by concatenating the variables in the subspaces

    std::size_t fullDimension = 0;
    std::size_t numberRows = 0;
    // constraints on subspace sets
    for ( std::size_t i = 0; i < subspaceSets.size(); ++i ) {
        fullDimension += subspaceSets[ i ].dimension();
        numberRows += subspaceSets[ i ].matrix().rows();
    }
    // constraints in the dependencies
    numberRows += dependencies.getMatrix().rows();
    // constraints for clock equality
    numberRows += 2 * ( clockCount * ( subspaceSets.size() - 1 ) );
    matrix_t<Number> fullConstraints = matrix_t<Number>::Zero( numberRows, fullDimension );
    vector_t<Number> fullVector = vector_t<Number>::Zero( numberRows );
    matrix_t<Number> fullDependencies = matrix_t<Number>::Zero( dependencies.getMatrix().rows(), fullDimension );

    std::size_t accumulatedDimension = 0;
    std::size_t accumulatedRows = 0;
    // holds the indices of the variables x_i
    std::vector<std::size_t> toProject;
    for ( std::size_t i = 0; i < subspaceSets.size(); ++i ) {
        auto subspaceMatrix = subspaceSets[ i ].matrix();
        auto subspaceVector = subspaceSets[ i ].vector();
        fullConstraints.block( accumulatedRows, accumulatedDimension, subspaceMatrix.rows(), subspaceMatrix.cols() ) = subspaceMatrix;
        fullVector.segment( accumulatedRows, subspaceVector.rows() ) = subspaceVector;
        toProject.push_back( accumulatedDimension );
        fullDependencies.col( accumulatedDimension + 1 ) = dependencies.getMatrix().col( i );
        accumulatedDimension += subspaceSets[ i ].dimension();
        accumulatedRows += subspaceMatrix.rows();
    }

    // add constraints of dependencies
    fullConstraints.block( accumulatedRows, 0, fullDependencies.rows(), fullDependencies.cols() ) = fullDependencies;
    fullVector.segment( accumulatedRows, dependencies.getVector().rows() ) = dependencies.getVector();
    accumulatedRows += fullDependencies.rows();
    // add constraints for clock equality
    for ( std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex ) {
        for ( std::size_t subspace = 1; subspace < subspaceSets.size(); ++subspace ) {
            fullConstraints( accumulatedRows, 2 + clockIndex ) = 1;
            fullConstraints( accumulatedRows, subspace * ( 2 + clockCount ) + clockIndex + 2 ) = -1;
            fullConstraints( accumulatedRows + 1, 2 + clockIndex ) = -1;
            fullConstraints( accumulatedRows + 1, subspace * ( 2 + clockCount ) + clockIndex + 2 ) = 1;
            accumulatedRows += 2;
        }
    }

    std::vector<std::size_t> projectOut;
    for ( std::size_t i = fullDimension - 1;; --i ) {
        if ( std::find( toProject.begin(), toProject.end(), i ) == toProject.end() ) {
            projectOut.push_back( i );
        }
        if ( i == 0 ) { break; }
    }
    HPolytope<Number> hpol = HPolytope<Number>( fullConstraints, fullVector ).projectOut( projectOut );
    Representation res;
    convert( hpol, res );
    return res;
}

template <typename Representation>
std::pair<Condition<typename Representation::NumberType>, std::vector<Representation>> decompose( const Representation& composedSet, std::size_t clockCount ) {
    // todo: implement
    using Number = typename Representation::NumberType;
    return std::make_pair( Condition<Number>(), std::vector<Representation>() );
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