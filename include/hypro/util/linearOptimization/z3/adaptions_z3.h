
#pragma once
#include "../../../flags.h"
#ifdef HYPRO_USE_Z3
#include "helper_methods.h"
#include "z3Convenience.h"

#include <z3.h>

namespace hypro {
template <typename Number>
EvaluationResult<Number> z3OptimizeLinearPostSolve( bool maximize, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, const EvaluationResult<Number>& preSolution );

template <typename Number>
EvaluationResult<Number> z3OptimizeLinear( bool maximize, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations );

// double specialization
template <>
EvaluationResult<double> z3OptimizeLinear( bool maximize, const vector_t<double>& _direction, const matrix_t<double>& constraints, const vector_t<double>& constants, const std::vector<carl::Relation>& relations );

template <typename Number>
bool z3CheckConsistency( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations );

template <typename Number>
bool z3CheckPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, const Point<Number>& point );

template <typename Number>
std::vector<std::size_t> z3RedundantConstraints( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations );

}  // namespace hypro

#include "adaptions_z3.tpp"
#endif	// HYPRO_USE_Z3
