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

#include "../../../config.h"
#include "../../../datastructures/Point.h"
#include "../EvaluationResult.h"
#include "../glpk_context.h"

#include <glpk.h>

namespace hypro {

    inline void printProblem(glp_prob *glpkProblem);

    template<typename Number>
    vector_t<Number>
    refineSolution(glpk_context &context, const matrix_t<Number> &constraints, const vector_t<Number> &constants);

    /**
     * Use glpk to improve a given solution to an linear optimization problem
     * @tparam Number The used number type
     * @param context The glpk context holding the lp instance
     * @param _direction The optimization direction or cost function
     * @param constraints The matrix defining the coefficients of the constraints bounding the search space
     * @param constants The vector representing the constant parts in the constraints bounding the search space
     * @param useExact If true, use simplex method with internal rational arithmetic
     * @param preSolution The previous solution to be improved
     * @return An evaluation result containing the optimal value, the point that achieved this value and a status whether the solution was feasible
     */
    template<typename Number>
    EvaluationResult<Number> glpkOptimizeLinearPostSolve(glpk_context &context, const vector_t<Number> &_direction,
                                                         const matrix_t<Number> &constraints,
                                                         const vector_t<Number> &constants, bool useExact,
                                                         const EvaluationResult<Number> &preSolution);

    /**
     * Use glpk to perform linear optimization
     * @tparam Number The used number type
     * @param context The glpk context holding the lp instance
     * @param _direction The optimization direction or cost function
     * @param constraints The matrix defining the coefficients of the constraints bounding the search space
     * @param constants The vector representing the constant parts in the constraints bounding the search space
     * @param useExact If true, use simplex method with internal rational arithmetic
     * @return An evaluation result containing the optimal value, the point that achieved this value and a status whether the solution was feasible
     */
    template<typename Number>
    EvaluationResult<Number>
    glpkOptimizeLinear(glpk_context &context, const vector_t<Number> &_direction, const matrix_t<Number> &constraints,
                       const vector_t<Number> &constants, bool useExact);

    /**
     * Use glpk to check, whether a point is contained in the solutions space defined by the constraints
     * @tparam Number The used number type
     * @param context The glpk context holding the lp instance
     * @param constraints The matrix defining the coefficients of the constraints bounding the search space
     * @param constants The vector representing the constant parts in the constraints bounding the search space
     * @param point The point to be checked
     * @return True, if the given point is contained in the solution space defined by the constraints
     */
    template<typename Number>
    bool glpkCheckPoint(glpk_context &context, const matrix_t<Number> &constraints, const vector_t<Number> &,
                        const Point<Number> &point);

    /**
     * Use glpk to determine which of the passed constraints are redundant (not needed) to define the solution space
     * @tparam Number The used number type
     * @param context The glpk context holding the lp instance
     * @param constraints The matrix defining the coefficients of the constraints bounding the search space
     * @param constants The vector representing the constant parts in the constraints bounding the search space
     * @param relations The relation symbols between constraints (A) and constant part (b), e.g., Ax <= b for a system of linear inequalities
     * @return A vector of indices that reference redundant constraints
     */
    template<typename Number>
    std::vector<std::size_t>
    glpkRedundantConstraints(glpk_context &context, matrix_t<Number> constraints, vector_t<Number> constants,
                             std::vector<carl::Relation> &relations);

    /**
     * Use glpk to get a solution point that is contained in the solution space defined by the given constraints
     * @tparam Number The used number type
     * @param context The glpk context holding the lp instance (needs to be set up already)
     * @param dimension The dimensionality of the solution space
     * @param useExact If true, use simplex method with internal rational arithmetic
     * @return An evaluation result containing the internal point and a status whether the solution was feasible
     */
    template<typename Number>
    EvaluationResult<Number> glpkGetInternalPoint(glpk_context &context, std::size_t dimension, bool useExact);

// specializations
    template<>
    EvaluationResult<double>
    glpkOptimizeLinear(glpk_context &context, const vector_t<double> &_direction, const matrix_t<double> &constraints,
                       const vector_t<double> &constants, bool useExact);

    template<>
    bool glpkCheckPoint(glpk_context &context, const matrix_t<double> &constraints, const vector_t<double> &,
                        const Point<double> &point);

    template<>
    std::vector<std::size_t>
    glpkRedundantConstraints(glpk_context &context, matrix_t<double> constraints, vector_t<double> constants,
                             std::vector<carl::Relation> &relations);
}  // namespace hypro

#include "adaptions_glpk.tpp"
