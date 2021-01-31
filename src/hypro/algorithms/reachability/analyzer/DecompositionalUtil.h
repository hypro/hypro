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
std::vector<Point<typename State::NumberType>> composeSubspaces( const State& segment, std::size_t dim1, std::size_t dim2, Decomposition decomposition, std::size_t clockCount );

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
std::vector<std::vector<Representation>> composeFlowpipes( const std::vector<ReachTreeNode<Representation>*>& nodes, const Decomposition& decomposition, FixedAnalysisParameters settings, std::size_t clockCount );

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
TimeInformation<typename Representation::NumberType> getClockValues( const Representation& segment, std::size_t clockCount );

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
        const Representation& segment, TimeInformation<typename Representation::NumberType> clockValues, std::size_t clockCount );

/**
 * @brief       Reset clock to 0 in a segment.
 * @tparam      Representation      The state-set representation of the segment.
 * @param       segment             The segment for which to reset the clock.
 * @param       clockIndex          The index of the clock-variable in the segment.
 * @return      The segment with clock reset to 0.
 */
template <typename Representation>
Representation resetClocks( const Representation& segment, std::size_t clockCount );

/**
 * @brief       Get all (local and global) bad states as conditions in a location of an automaton.
 * @tparam      Number          The number type used by the automaton.
 * @param       ha              Pointer to the hybrid automaton.
 * @param       loc             Pointer to a location in the automaton.
 * @return      Vector of all local and global bad states in the location.
 */
template <typename Number>
std::vector<Condition<Number>> collectBadStates( const HybridAutomaton<Number>* ha, const Location<Number>* loc );
} // namespace detail
} // namespace hypro

#include "DecompositionalUtil.tpp"