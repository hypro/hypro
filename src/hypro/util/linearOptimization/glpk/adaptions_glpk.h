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
inline void printProblem( glp_prob* glpkProblem );

template <typename Number>
vector_t<Number> refineSolution( glpk_context& context, const matrix_t<Number>& constraints, const vector_t<Number>& constants );

template <typename Number>
EvaluationResult<Number> glpkOptimizeLinearPostSolve( glpk_context& context, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, bool useExact, const EvaluationResult<Number>& preSolution );

template <typename Number>
EvaluationResult<Number> glpkOptimizeLinear( glpk_context& context, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, bool useExact );

template <typename Number>
bool glpkCheckPoint( glpk_context& context, const matrix_t<Number>& constraints, const vector_t<Number>&, const Point<Number>& point );

template <typename Number>
std::vector<std::size_t> glpkRedundantConstraints( glpk_context& context, matrix_t<Number> constraints, vector_t<Number> constants, std::vector<carl::Relation>& relations );

template <typename Number>
EvaluationResult<Number> glpkGetInternalPoint( glpk_context& context, std::size_t dimension, bool useExact );

// specializations
template <>
EvaluationResult<double> glpkOptimizeLinear( glpk_context& context, const vector_t<double>& _direction, const matrix_t<double>& constraints, const vector_t<double>& constants, bool useExact );

template <>
bool glpkCheckPoint( glpk_context& context, const matrix_t<double>& constraints, const vector_t<double>&, const Point<double>& point );

template <>
std::vector<std::size_t> glpkRedundantConstraints( glpk_context& context, matrix_t<double> constraints, vector_t<double> constants, std::vector<carl::Relation>& relations );
}  // namespace hypro

#include "adaptions_glpk.tpp"
