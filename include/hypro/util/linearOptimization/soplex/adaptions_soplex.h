
/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../types.h"
#include "helper_functions.h"
#include "soplex_hypro.h"

namespace hypro {
    /**
     * Use SoPlex to improve a given solution to an linear optimization problem
     * @tparam Number The used number type
     * @param maximize If true, maximize, otherwise minimize
     * @param _direction The optimization direction or cost function
     * @param constraints The matrix defining the coefficients of the constraints bounding the search space
     * @param constants The vector representing the constant parts in the constraints bounding the search space
     * @param relations The relation symbols between constraints (A) and constant part (b), e.g., Ax <= b for a system of linear inequalities
     * @param preSolution The previous solution to be improved
     * @return An evaluation result containing the optimal value, the point that achieved this value and a status whether the solution was feasible
     */
    template<typename Number>
    EvaluationResult <Number>
    soplexOptimizeLinearPostSolve(const vector_t<Number> &direction, const matrix_t<Number> &constraints,
                                  const vector_t<Number> &constants, const std::vector<carl::Relation> &relations,
                                  bool maximize, const EvaluationResult <Number> &preSolution);

    /**
     * Use SoPlex to perform linear optimization
     * @tparam Number The used number type
     * @param maximize If true, maximize, otherwise minimize
     * @param _direction The optimization direction or cost function
     * @param constraints The matrix defining the coefficients of the constraints bounding the search space
     * @param constants The vector representing the constant parts in the constraints bounding the search space
     * @param relations The relation symbols between constraints (A) and constant part (b), e.g., Ax <= b for a system of linear inequalities
     * @return An evaluation result containing the optimal value, the point that achieved this value and a status whether the solution was feasible
     */
    template<typename Number>
    EvaluationResult <Number>
    soplexOptimizeLinear(const vector_t<Number> &_direction, const matrix_t<Number> &constraints,
                         const vector_t<Number> &constants, const std::vector<carl::Relation> &relations,
                         bool maximize);

    /**
     * Use SoPlex to check, whether the solution space defined by the given constraints contains a solution (is non-empty)
     * @tparam Number The used number type
     * @param constraints The matrix defining the coefficients of the constraints bounding the search space
     * @param constants The vector representing the constant parts in the constraints bounding the search space
     * @param relations The relation symbols between constraints (A) and constant part (b), e.g., Ax <= b for a system of linear inequalities
     * @return True, if the solution space is non-empty, false otherwise
     */
    template<typename Number>
    bool soplexCheckConsistency(const matrix_t<Number> &constraints, const vector_t<Number> &constants,
                                const std::vector<carl::Relation> &relations);

    /**
     * Use SoPlex to check, whether a point is contained in the solutions space defined by the constraints
     * @tparam Number The used number type
     * @param constraints The matrix defining the coefficients of the constraints bounding the search space
     * @param constants The vector representing the constant parts in the constraints bounding the search space
     * @param relations The relation symbols between constraints (A) and constant part (b), e.g., Ax <= b for a system of linear inequalities
     * @param point The point to be checked
     * @return True, if the given point is contained in the solution space defined by the constraints
     */
    template<typename Number>
    bool soplexCheckPoint(const matrix_t<Number> &constraints, const vector_t<Number> &constants,
                          const std::vector<carl::Relation> &relations, const Point <Number> &point);

    /**
     * Use SoPlex to determine which of the passed constraints are redundant (not needed) to define the solution space
     * @tparam Number The used number type
     * @param constraints The matrix defining the coefficients of the constraints bounding the search space
     * @param constants The vector representing the constant parts in the constraints bounding the search space
     * @param relations The relation symbols between constraints (A) and constant part (b), e.g., Ax <= b for a system of linear inequalities
     * @return A vector of indices that reference redundant constraints
     */
    template<typename Number>
    std::vector<std::size_t>
    soplexRedundantConstraints(const matrix_t<Number> &constraints, const vector_t<Number> &constants,
                               const std::vector<carl::Relation> &relations);

    /**
     * Use SoPlex to get a solution point that is contained in the solution space defined by the given constraints
     * @tparam Number The used number type
     * @param constraints The matrix defining the coefficients of the constraints bounding the search space
     * @param constants The vector representing the constant parts in the constraints bounding the search space
     * @param relations The relation symbols between constraints (A) and constant part (b), e.g., Ax <= b for a system of linear inequalities
     * @return An evaluation result containing the internal point and a status whether the solution was feasible
     */
    template<typename Number>
    EvaluationResult <Number>
    soplexGetInternalPoint(const matrix_t<Number> &constraints, const vector_t<Number> &constants,
                           const std::vector<carl::Relation> &relations);

}  // namespace hypro

#include "adaptions_soplex.tpp"
