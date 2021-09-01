#pragma once
#include "../../../../representations/GeometricObjectBase.h"

namespace hypro {

/**
 * @brief Compute time elapse (unbounded) starting from an initial set.
 * @details Converts to VPolytope representation and combines the rays as in "Verification of Real-Time Systems
using Linear Relation Analysis" (Halbwachs et al.).
 * @tparam StateSet The used representation.
 * @param initialSet The initial set of states before time elapsed.
 * @param flowVertices List of vertices that describe the flow of the system.
 * @return StateSet The reachable states starting from initial set by letting time elapse (unbounded).
 */
template <typename StateSet>
StateSet singularApplyTimeEvolution( const StateSet& initialSet, const std::vector<Point<typename StateSet::NumberType>>& flowVertices );

/**
 * @brief Compute time elapse (bounded) starting from an initial set.
 * @details Converts to VPolytope representation and combines & bounds the rays.
 * @tparam StateSet The used representation.
 * @param initialSet The initial set of states before time elapsed.
 * @param flowVertices List of vertices that describe the flow of the system.
 * @param timeBound The time bound to use for the computation of the reachable set.
 * @return StateSet The reachable states starting from initial set by letting time elapse (bounded).
 */
template <typename StateSet>
StateSet singularApplyBoundedTimeEvolution( const StateSet& initialSet, const std::vector<Point<typename StateSet::NumberType>>& flowVertices, tNumber timeBound );

/**
 * @brief Compute state set reachable from initial set at time points between timeStart and timeBound
 * @details Converts to VPolytope representation and combines & bounds the rays.
 * @tparam StateSet The used representation.
 * @param initialSet The initial set of states before time elapsed.
 * @param flowVertices List of vertices that describe the flow of the system.
 * @param timeStart The initial time offset
 * @param timeBound The time bound to use for the computation of the reachable set.
 * @return StateSet The reachable states starting from initial set offset by timeStart by letting time elapse (bounded).
 */
template <typename StateSet>
StateSet singularApplyTimeStep( const StateSet& initialSet, const std::vector<Point<typename StateSet::NumberType>>& flowVertices, tNumber timeStart, tNumber timeBound );


}  // namespace hypro

#include "singularTimeEvolutionHandler.tpp"