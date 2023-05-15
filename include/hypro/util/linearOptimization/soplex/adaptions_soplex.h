
/*
 * Copyright (c) 2023.
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

    template<typename Number>
    EvaluationResult <Number>
    soplexOptimizeLinearPostSolve(const vector_t<Number> &direction, const matrix_t<Number> &constraints,
                                  const vector_t<Number> &constants, const std::vector<carl::Relation> &relations,
                                  bool maximize, const EvaluationResult <Number> &preSolution);

    template<typename Number>
    EvaluationResult <Number>
    soplexOptimizeLinear(const vector_t<Number> &_direction, const matrix_t<Number> &constraints,
                         const vector_t<Number> &constants, const std::vector<carl::Relation> &relations,
                         bool maximize);

    template<typename Number>
    bool soplexCheckConsistency(const matrix_t<Number> &constraints, const vector_t<Number> &constants,
                                const std::vector<carl::Relation> &relations);

    template<typename Number>
    bool soplexCheckPoint(const matrix_t<Number> &constraints, const vector_t<Number> &constants,
                          const std::vector<carl::Relation> &relations, const Point <Number> &point);

    template<typename Number>
    std::vector<std::size_t>
    soplexRedundantConstraints(const matrix_t<Number> &constraints, const vector_t<Number> &constants,
                               const std::vector<carl::Relation> &relations);

    template<typename Number>
    EvaluationResult <Number>
    soplexGetInternalPoint(const matrix_t<Number> &constraints, const vector_t<Number> &constants,
                           const std::vector<carl::Relation> &relations);

}  // namespace hypro

#include "adaptions_soplex.tpp"
