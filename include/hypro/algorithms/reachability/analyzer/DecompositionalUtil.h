#pragma once
#include <hypro/algorithms/reachability/types.h>
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h>
#include <hypro/datastructures/reachability/ReachTreev2.h>
#include <hypro/datastructures/reachability/TreeTraversal.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/types.h>

namespace hypro {
/**
 * @brief       Return whether the analysis subspace uses multiple segments for each time-elapse.
 * @param       dynamics    The dynamic type of the subspace.
 * @return      True if multiple segments are constructed during analysis and false otherwise.
 */
inline bool isSegmentedSubspace( const DynamicType dynamics );

namespace detail {

template <typename Representation>
HPolytope<typename Representation::NumberType> composeSubspaceConstraints(
	  const std::vector<Representation>& subspaceSets,
	  const Condition<typename Representation::NumberType>& dependencies,
	  const Decomposition& decomposition,
	  std::size_t clockCount );

template <typename Representation>
Representation composeSubspaces(
	  const std::vector<Representation>& subspaceSets,
	  const Condition<typename Representation::NumberType>& dependencies,
	  const Decomposition& decomposition,
	  std::size_t clockCount );

template <typename Representation>
Condition<typename Representation::NumberType> getDependencies( const Representation& composedSet, const Decomposition& decomposition );

template <typename Representation>
Representation projectOnDimensions( const Representation& composedSet, const std::vector<std::size_t>& dimensions );

template <typename Representation>
Representation addClocksAndInitial( const Representation& set, std::size_t clockCount );

template <typename Representation>
bool isDependency( const std::vector<Eigen::Index>& dimensions, const Decomposition& decomposition );

template <typename Representation>
std::vector<Representation> decompose( const Representation& composedSet, const Decomposition& decomposition, std::size_t clockCount );

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
}  // namespace detail

/**
 * @brief       Generator for composed segments after analysis.
 * @detail      Used for plotting. After analysis, generate composed segments by
 *              iterating over all subspace-reach-trees and the dependency simultaneously.
 */
template <typename Representation>
struct DecompositionalSegmentGen;

}  // namespace hypro

#include "DecompositionalUtil.tpp"