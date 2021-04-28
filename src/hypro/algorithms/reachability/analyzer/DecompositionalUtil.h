#pragma once
#include <hypro/types.h>
#include <hypro/algorithms/reachability/types.h>
#include <hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h>
#include <hypro/datastructures/reachability/ReachTreev2.h>

namespace hypro {
/**
 * @brief       Return whether the analysis subspace uses one segment for each time-elapse or uses time-steps to construct
 *              multiple segments.
 * @param       dynamics    The dynamic type of the subspace.
 * @return      True if the subspace needs a clock for analysis and false otherwise.
 */
inline bool isClockedSubspace( const DynamicType dynamics );

namespace detail {

template <typename Representation>
HPolytope<typename Representation::NumberType> composeSubspaceConstraints(
    const std::vector<Representation>& subspaceSets,
    const Condition<typename Representation::NumberType>& dependencies,
    std::size_t clockCount );

template <typename Representation>
Representation composeSubspaces(
    const std::vector<Representation>& subspaceSets,
    const Condition<typename Representation::NumberType>& dependencies,
    std::size_t clockCount );

template <typename Representation>
std::pair<Condition<typename Representation::NumberType>, std::vector<Representation>> decompose(
    const Representation& composedSet,
    std::size_t clockCount );


/**
 * @brief       Get the clock values covered by the given segment.
 * @tparam      Representation      The state-set representation of the segment.
 * @param       segment             The set to get the clock values for.
 * @param       clockIndexLocal     The index of the local clock-variable in the segment.
 * @param       clockIndexGlobal    The index of the global clock-variable in the segment.
 * @return      The time intervals of the global and local glock covered by the segment.
 */
template <typename Representation>
TimeInformation<typename Representation::NumberType> getClockValues(
    const Representation& segment,
    std::size_t clockCount );

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
        const Representation& segment,
        TimeInformation<typename Representation::NumberType> clockValues,
        std::size_t clockCount );

/**
 * @brief       Get all (local and global) bad states as conditions in a location of an automaton.
 * @tparam      Number          The number type used by the automaton.
 * @param       ha              Pointer to the hybrid automaton.
 * @param       loc             Pointer to a location in the automaton.
 * @return      Vector of all local and global bad states in the location.
 */
template <typename Number>
std::vector<Condition<Number>> collectBadStates( 
    const HybridAutomaton<Number>* ha,
    const Location<Number>* loc );
} // namespace detail
} // namespace hypro

#include "DecompositionalUtil.tpp"