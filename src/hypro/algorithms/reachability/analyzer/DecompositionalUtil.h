namespace hypro {
namespace detail {
// get the time interval covered by the segment
template <typename Representation>
carl::Interval<typename Representation::NumberType> getTimeInterval( const Representation& segment, int clockIndex ) {
    using Number = typename Representation::NumberType;
    if ( segment.empty() ) {
        return carl::Interval<Number>::emptyInterval();
    }
    vector_t<Number>clockDirection = vector_t<Number>::Zero( segment.dimension() );
    clockDirection( clockIndex ) = 1;
    Number timeUpper = segment.evaluate( clockDirection ).supportValue;
    Number timeLower = segment.evaluate( -1 * clockDirection ).supportValue;
    return carl::Interval<Number>( -1*timeLower, timeUpper );

}

template <typename Representation>
Representation intersectSegmentWithTimeInterval( const Representation& segment, carl::Interval<typename Representation::NumberType> timeInterval, int clockIndex ) {
    using Number = typename Representation::NumberType;
    if ( segment.empty() ) {
        return segment;
    }
    vector_t<Number> clockDirection = vector_t<Number>::Zero( segment.dimension() );
    clockDirection( clockIndex ) = 1;
    Halfspace<Number> timePlaneUpper( clockDirection, timeInterval.upper() );
    Halfspace<Number> timePlaneLower( -1 * clockDirection, -1 * timeInterval.lower() );
    HPolytope<Number> segmentAsHpol;
    Representation constrainedSegment;
    convert( segment, segmentAsHpol );
    segmentAsHpol.insert( timePlaneUpper );
    segmentAsHpol.insert( timePlaneLower );
    convert( segmentAsHpol, constrainedSegment );
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