/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
 * @brief       Indicates whether the analysed subspace uses multiple segments for each time-elapse.
 * @param       dynamics    The dynamic type of the subspace.
 * @return      True if multiple segments are constructed during analysis and false otherwise.
 */
inline bool isSegmentedSubspace( const DynamicType dynamics );

/**
 * @brief       Used to eliminate discrete variables from decomposition for synchronization without discrete subspaces.
 * @param       index   The variable index in the original decomposition.
 * @param       decomposition   The original decomposition.
 * @return      Index of variable in new decomposition (without discrete subspaces).
 */
inline std::size_t getVarIndexWithoutDiscrete( std::size_t index, const Decomposition& decomposition );

namespace detail {

/**
 * @brief       Build fully-dimensional synchronized set by equalizing clocks and considering dependencies.
 * @detail      The constructed set has all clock variables, i.e., no variables are eliminated.
 * @param       subspaceSets    The unsynchronized sets.
 * @param       dependencies    Initial dependencies from last synchronization.
 * @param       decomposition   Information about subspace decomposition.
 * @param       clockCount      The number of clocks used for synchronization.
 * @return      Synchronized set as HPolytope with additional variables.
 */
template <typename Representation>
HPolytope<typename Representation::NumberType> composeSubspaceConstraints(
	  const std::vector<Representation>& subspaceSets,
	  const Condition<typename Representation::NumberType>& dependencies,
	  const Decomposition& decomposition,
	  std::size_t clockCount );

/**
 * @brief       Synchronize subspaces by equalizing clocks and considering dependencies.
 * @detail      The constructed set only has the original variables, i.e., no clock or dependency variables.
 * @param       subspaceSets    The unsynchronized sets.
 * @param       dependencies    Initial dependencies from last synchronization.
 * @param       decomposition   Information about subspace decomposition.
 * @param       clockCount      The number of clocks used for synchronization.
 * @return      Synchronized set without additional variables.
 */
template <typename Representation>
Representation composeSubspaces(
	  const std::vector<Representation>& subspaceSets,
	  const Condition<typename Representation::NumberType>& dependencies,
	  const Decomposition& decomposition,
	  std::size_t clockCount );

/**
 * @brief       Get dependencies between subspaces from fully dimensional composed set.
 * @param       composetSet     The fully dimensional set without additional variables.
 * @param       decomposition   Information about subspace decomposition.
 * @return      Dependencies between subspaces, encoded as condition.
 */
template <typename Representation>
Condition<typename Representation::NumberType> getDependencies( const Representation& composedSet, const Decomposition& decomposition );

/**
 * @brief       Wrapper function for FM elimiation. Project set on given dimensions by projecting out all other variables.
 * @param       composetSet     The set from which to eliminate variables.
 * @param       dimensions      The dimensions on which to project.
 * @return      New set with given dimensions.
 */
template <typename Representation>
Representation projectOnDimensions( const Representation& composedSet, const std::vector<std::size_t>& dimensions );

/**
 * @brief       Adds additional variables to a set.
 * @param       set         The original set without additional variables.
 * @param       clockCOunt  The number of clocks to add.
 * @return      New set with additional clocks at zero and dependency variables, initialized to their original variable counterpart.
 */
template <typename Representation>
Representation addClocksAndInitial( const Representation& set, std::size_t clockCount );

/**
 * @brief       Helper function to determine whether a row of a matrix encodes a dependency between subspaces.
 * @param       dimensions      Vector of non-zero columns in a matrix.
 * @param       decomposition   Information about subspace decomposition.
 * @return      true if the dimensions belong to at least two subspaces, otherwise false.
 */
template <typename Representation>
bool isDependency( const std::vector<Eigen::Index>& dimensions, const Decomposition& decomposition );

/**
 * @brief       Project composed set on the subspaces and add additional variables.
 * @param       composedSet     The original, fully dimensional set.
 * @param       decomposition   Information about subspace decomposition.
 * @param       clockCount      Number of clocks to add to each subspace.
 * @return      Vector of sets, one for each subspace with additional clock and dependency variables.
 */
template <typename Representation>
std::vector<Representation> decompose( const Representation& composedSet, const Decomposition& decomposition, std::size_t clockCount );

/**
 * @brief       Get the clock values covered by the given segment.
 * @tparam      Representation      The state-set representation of the segment.
 * @param       segment             The set to get the clock values for.
 * @param       clockCount          The number of clocks used for synchronization.
 * @return      The time intervals covered by the segment.
 */
template <typename Representation>
TimeInformation<typename Representation::NumberType> getClockValues(
	  const Representation& segment,
	  std::size_t clockCount );

/**
 * @brief       Compute the intersection of the segment with the given time intervals.
 * @tparam      Representation      The state-set representation of the segment.
 * @param       segment             The segment to intersect with the clock intervals.
 * @param       clockValues         The time intervals.
 * @param       clockCount          The number of clocks used for synchronization.
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
template <typename Representation, typename Location>
struct DecompositionalSegmentGen;

}  // namespace hypro

#include "DecompositionalUtil.tpp"