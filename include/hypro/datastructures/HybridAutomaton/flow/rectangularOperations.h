/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../carlTypes.h"
#include "rectangular.h"

namespace hypro {

/**
 * @brief Creates a set of constraints which describe forward time evolution for the passed variable.
 * @details The primed variable serves as the initialization, the original variable will be the variable for which the result is described. The variable t is the used clock/time variable, the passed interval describes the flow. The method creates constraints in the assumption that t >= 0 holds.
 * @tparam N Number type (rational)
 * @tparam D Number type (float) used to describe the flow
 * @param original The original variable (the result is described in this var)
 * @param primed The initial valuation of the original variable
 * @param t The variable which reflects time
 * @param flow The interval describing the dynamics
 * @return std::vector<ConstraintT<N>> A set of constraints which describe all possible time successors
 */
    template<typename N, typename D>
    std::vector<ConstraintT<N>> createFlowConstraints(carl::Variable original, carl::Variable primed, carl::Variable t,
                                                      const carl::Interval<D> &flow) {
        std::vector<ConstraintT<N>> res;

        // catch equations
        if (lowerBoundType(flow) == carl::BoundType::WEAK && upperBoundType(flow) == carl::BoundType::WEAK &&
            flow.lower() == flow.upper()) {
            res.emplace_back(
                    PolyT<N>(primed) + PolyT<N>(carl::convert<D, N>(flow.lower())) * PolyT<N>(t) - PolyT<N>(original),
                    carl::Relation::EQ);
            return res;
        }

        // lower flow bound
        // x' + lb*t - x <= 0
        // x >= x' + lb*t
        if (lowerBoundType(flow) != carl::BoundType::INFTY) {
            res.emplace_back(
                    PolyT<N>(primed) + PolyT<N>(carl::convert<D, N>(flow.lower())) * PolyT<N>(t) - PolyT<N>(original),
                    carl::Relation::LEQ);
        }

        // upper flow bound
        // x' + ub*t - x >= 0
        // x <= x' + ub*t
        if (upperBoundType(flow) != carl::BoundType::INFTY) {
            res.emplace_back(
                    PolyT<N>(primed) + PolyT<N>(carl::convert<D, N>(flow.upper())) * PolyT<N>(t) - PolyT<N>(original),
                    carl::Relation::GEQ);
        }

        return res;
    }

/**
 * @brief Creates a set of constraints which describe backward time evolution for the passed variable.
 * @details The primed variable serves as the initialization, the original variable will be the variable for which the result is described. The variable t is the used clock/time variable, the passed interval describes the flow. The method creates constraints under the assumption that t <= 0 holds.
 * @tparam N Number type (rational)
 * @tparam D Number type (float) used to describe the flow
 * @param original The original variable (the result is described in this var)
 * @param primed The initial valuation of the original variable
 * @param t The variable which reflects time
 * @param flow The interval describing the dynamics
 * @return std::vector<ConstraintT<N>> A set of constraints which describe all possible time predeccessors
 */
    template<typename N, typename D>
    std::vector<ConstraintT<N>>
    createReverseFlowConstraints(carl::Variable original, carl::Variable primed, carl::Variable t,
                                 const carl::Interval<D> &flow) {
        std::vector<ConstraintT<N>> res;

        // catch equations
        if (lowerBoundType(flow) == carl::BoundType::WEAK && upperBoundType(flow) == carl::BoundType::WEAK &&
            flow.lower() == flow.upper()) {
            res.emplace_back(
                    -PolyT<N>(primed) + PolyT<N>(carl::convert<D, N>(flow.lower())) * PolyT<N>(t) + PolyT<N>(original),
                    carl::Relation::EQ);
            return res;
        }

        // lower flow bound
        // x' + lb*t -x >= 0
        // x <= x' + lb*t, t <= 0
        // upd 14.09.21
        // t >= 0 and x' >= x + lb*t
        // x + lb*t - x' <= 0
        if (lowerBoundType(flow) != carl::BoundType::INFTY) {
            res.emplace_back(
                    -PolyT<N>(primed) + PolyT<N>(carl::convert<D, N>(flow.lower())) * PolyT<N>(t) + PolyT<N>(original),
                    carl::Relation::LEQ);
        }

        // upper flow bound
        // x' + ub*t -x <= 0
        // x >= x' + ub*t, t <= 0
        // upd 14.09.21
        // t >= 0 and x' <= x + ub*t
        // x + ub*t - x' >= 0
        if (upperBoundType(flow) != carl::BoundType::INFTY) {
            res.emplace_back(
                    -PolyT<N>(primed) + PolyT<N>(carl::convert<D, N>(flow.upper())) * PolyT<N>(t) + PolyT<N>(original),
                    carl::Relation::GEQ);
        }

        return res;
    }

/**
 * @brief Creates a set of constraints which describe under-approximative backward time evolution for the passed variable.
 * @details The primed variable serves as the initialization, the original variable will be the variable for which the result is described. The variable t is the used clock/time variable, the passed interval describes the flow. The method creates constraints under the assumption that t <= 0 holds.
 * @tparam N Number type (rational)
 * @tparam D Number type (float) used to describe the flow
 * @param original The original variable (the result is described in this var)
 * @param primed The initial valuation of the original variable
 * @param t The variable which reflects time
 * @param flow The interval describing the dynamics
 * @return std::vector<ConstraintT<N>> A set of constraints which describe all possible time predeccessors
 */
    template<typename N, typename D>
    std::vector<ConstraintT<N>>
    createUnderapproximativeReverseFlowConstraints(carl::Variable original, carl::Variable primed, carl::Variable t,
                                                   const carl::Interval<D> &flow) {
        std::vector<ConstraintT<N>> res;

        // catch equations
        if (lowerBoundType(flow) == carl::BoundType::WEAK && upperBoundType(flow) == carl::BoundType::WEAK &&
            flow.lower() == flow.upper()) {
            res.emplace_back(
                    -PolyT<N>(primed) + PolyT<N>(carl::convert<D, N>(flow.lower())) * PolyT<N>(t) + PolyT<N>(original),
                    carl::Relation::EQ);
            return res;
        }

        // lower flow bound
        // x' + lb*t - x >= 0
        // x <= x' + lb*t
        if (lowerBoundType(flow) != carl::BoundType::INFTY) {
            res.emplace_back(
                    -PolyT<N>(primed) + PolyT<N>(carl::convert<D, N>(flow.lower())) * PolyT<N>(t) + PolyT<N>(original),
                    carl::Relation::GEQ);
        }

        // upper flow bound
        // x' + ub*t - x >= 0
        // x <= x' + ub*t
        if (upperBoundType(flow) != carl::BoundType::INFTY) {
            res.emplace_back(
                    -PolyT<N>(primed) + PolyT<N>(carl::convert<D, N>(flow.upper())) * PolyT<N>(t) + PolyT<N>(original),
                    carl::Relation::LEQ);
        }

        return res;
    }

}  // namespace hypro
