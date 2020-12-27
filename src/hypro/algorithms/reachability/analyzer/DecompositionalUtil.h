namespace hypro {
namespace detail {
/**
 * @brief       Get the clock values covered by the given segment.
 * @tparam      Representation      The state-set representation of the segment.
 * @param       segment             The set to get the clock values for.
 * @param       clockIndexLocal     The index of the local clock-variable in the segment.
 * @param       clockIndexGlobal    The index of the global clock-variable in the segment.
 * @return      The time intervals of the global and local glock covered by the segment.
 */
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

/**
 * @brief       Compute the intersection of the segment with the given time intervals.
 * @tparam      Representation      The state-set representation of the segment.
 * @param       segment             The segment to intersect with the clock.
 * @param       clock               The local and global time intervals.
 * @param       clockIndexLocal     The index of the local clock-variable in the segment.
 * @param       clockIndexGlobal    The index of the global clock-variable in the segment.
 * @return      The segment intersected with the clock intervals.
 */
template <typename Representation>
Representation intersectSegmentWithClock(
        const Representation& segment, TimeInformation<typename Representation::NumberType> clock, int clockIndexLocal, int clockIndexGlobal ) {
    using Number = typename Representation::NumberType;
    if ( segment.empty() ) {
        return segment;
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

/**
 * @brief       Compute intersection of two clock-values.
 * @tparam      Number          The number type used by the clocks.
 * @param       clock1          The values of the first clock.
 * @param       clock2          The values of the second clock.
 * @return      The intersection of local and global time intervals of clock1 and clock2
 */
template <typename Number>
TimeInformation<Number> intersectTimeInformation( const TimeInformation<Number>& clock1, const TimeInformation<Number>& clock2 ) {
    return TimeInformation<Number> {
        carl::set_intersection( clock1.localTime, clock2.localTime ),
        carl::set_intersection( clock1.globalTime, clock2.globalTime ) };
}

/**
 * @brief       Reset clock to 0 in a segment.
 * @tparam      Representation      The state-set representation of the segment.
 * @param       segment             The segment for which to reset the clock.
 * @param       clockIndex          The index of the clock-variable in the segment.
 * @return      The segment with clock reset to 0.
 */
template <typename Representation>
Representation resetClock( const Representation& segment, int clockIndex ) {
    using Number = typename Representation::NumberType;
    matrix_t<Number> resetMat = matrix_t<Number>::Identity( segment.dimension(), segment.dimension() );
    resetMat( clockIndex, clockIndex ) = 0;
    return segment.linearTransformation( resetMat );
}

/**
 * @brief       Get all (local and global) bad states as conditions in a location of an automaton.
 * @tparam      Number          The number type used by the automaton.
 * @param       ha              Pointer to the hybrid automaton.
 * @param       loc             Pointer to a location in the automaton.
 * @return      Vector of all local and global bad states in the location.
 */
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