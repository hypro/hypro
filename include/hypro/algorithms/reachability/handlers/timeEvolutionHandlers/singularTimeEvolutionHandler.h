/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
    template<typename StateSet>
    StateSet singularApplyTimeEvolution(const StateSet &initialSet,
                                        const std::vector<Point<typename StateSet::NumberType>> &flowVertices);

/**
 * @brief Compute time elapse (bounded) starting from an initial set.
 * @details Converts to VPolytope representation and combines & bounds the rays.
 * @tparam StateSet The used representation.
 * @param initialSet The initial set of states before time elapsed.
 * @param flowVertices List of vertices that describe the flow of the system.
 * @param timeBound The time bound to use for the computation of the reachable set.
 * @return StateSet The reachable states starting from initial set by letting time elapse (bounded).
 */
    template<typename StateSet>
    StateSet singularApplyBoundedTimeEvolution(const StateSet &initialSet,
                                               const std::vector<Point<typename StateSet::NumberType>> &flowVertices,
                                               tNumber timeBound);

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
    template<typename StateSet>
    StateSet singularApplyTimeStep(const StateSet &initialSet,
                                   const std::vector<Point<typename StateSet::NumberType>> &flowVertices,
                                   tNumber timeStart, tNumber timeBound);


}  // namespace hypro

#include "singularTimeEvolutionHandler.tpp"
