#pragma once
#include "../../../../representations/GeometricObjectBase.h"

namespace hypro {

/**
 * @brief Compute time elapse (unbounded) starting from an initial set.
 * @details Converts to VPolytope representation and combines the rays as in "Verification of Real-Time Systems
using Linear Relation Analysis" (Halbwachs et al.).
 * @tparam StateSet
 * @param initialSet
 * @param flow
 * @return StateSet
 */
template <typename StateSet>
StateSet linearApplyTimeEvolution( const StateSet& initialSet, const StateSet& flow );

/**
 * @brief Compute time elapse (bounded) starting from an initial set.
 * @details Converts to VPolytope representation and combines & bounds the rays.
 * @tparam StateSet
 * @param initialSet
 * @param flow
 * @param timeBound
 * @return StateSet
 */
template <typename StateSet>
StateSet linearApplyBoundedTimeEvolution( const StateSet& initialSet, const StateSet& flow, tNumber timeBound );

}  // namespace hypro

#include "linearTimeEvolutionHandler.tpp"