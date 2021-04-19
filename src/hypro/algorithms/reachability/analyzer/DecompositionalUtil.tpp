#include "DecompositionalUtil.h"

namespace hypro {

inline bool isClockedSubspace( const DynamicType dynamics ) {
    return ( dynamics != DynamicType::affine && dynamics != DynamicType::linear && dynamics != DynamicType::discrete );
}



namespace detail {

template <typename Representation>
Condition<typename Representation::NumberType> composeSubspaces( const std::vector<Representation>& subspaceSets, const Condition<typename Representation::NumberType>& dependencies, std::size_t clockCount ) {
    // todo: implement
    return dependencies;
}

template <typename Representation>
std::vector<Representation> decomposeInitial( const Representation& initial, std::size_t clockCount ) {
    // todo: implement
    return std::vector<Representation>();
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