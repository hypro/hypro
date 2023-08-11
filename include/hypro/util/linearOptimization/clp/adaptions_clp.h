/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 *
 */
#pragma once

#include <hypro/flags.h>

#ifdef HYPRO_USE_CLP

#include "../../../config.h"
#include "../../../datastructures/Point.h"
#include "../EvaluationResult.h"
#include "clp_context.h"

#include <ClpSimplex.hpp>

namespace hypro {

template <typename Number>
EvaluationResult<Number> clpOptimizeLinear( clp_context& context, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, bool );

/**
 * Use clp to improve a given solution to an linear optimization problem
 * @tparam Number The used number type
 * @param context The clp context holding the lp instance
 * @param _direction The optimization direction or cost function
 * @param constraints The matrix defining the coefficients of the constraints bounding the search space
 * @param constants The vector representing the constant parts in the constraints bounding the search space
 * @param useExact NOT USED
 * @param preSolution The previous solution to be improved
 * @return An evaluation result containing the optimal value, the point that achieved this value and a status whether the solution was feasible
 */
template <typename Number>
EvaluationResult<Number> clpOptimizeLinearPost( clp_context& context, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>&, bool, const EvaluationResult<Number>& preSolution );

/**
 * Use clp to check, whether a point is contained in the solutions space defined by the constraints
 * @tparam Number The used number type
 * @param context The glpk context holding the lp instance
 * @param constraints The matrix defining the coefficients of the constraints bounding the search space
 * @param constants The vector representing the constant parts in the constraints bounding the search space
 * @param point The point to be checked
 * @return True, if the given point is contained in the solution space defined by the constraints
 */
template <typename Number>
bool clpCheckPoint( clp_context& context, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const Point<Number>& _point );

/**
 * Use clp to determine which of the passed constraints are redundant (not needed) to define the solution space
 * @tparam Number The used number type
 * @param context The glpk context holding the lp instance
 * @param constraints The matrix defining the coefficients of the constraints bounding the search space
 * @param constants The vector representing the constant parts in the constraints bounding the search space
 * @return A vector of indices that reference redundant constraints
 */
template <typename Number>
std::vector<std::size_t> clpRedundantConstraints( clp_context& context, const matrix_t<Number>& constraints, const vector_t<Number>& constants );

/**
 * Use clp to get a solution point that is contained in the solution space defined by the given constraints
 * @tparam Number The used number type
 * @param context The glpk context holding the lp instance (needs to be set up already)
 * @return An evaluation result containing the internal point and a status whether the solution was feasible
 */
template <typename Number>
EvaluationResult<Number> clpGetInternalPoint( clp_context& context );

SOLUTION clpCheckConsistency( clp_context& context );

void clpPrintProblem( clp_context& context );

}  // namespace hypro

#include "adaptions_clp.tpp"

#endif
