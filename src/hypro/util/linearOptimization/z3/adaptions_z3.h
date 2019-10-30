
#pragma once
#include <z3.h>
#include "z3Convenience.h"
#include "helper_methods.h"

namespace hypro {

	template<typename Number>
	EvaluationResult<Number> z3OptimizeLinear(bool maximize, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const EvaluationResult<Number>& preSolution = EvaluationResult<Number>());

	// double specialization
	template<>
	EvaluationResult<double> z3OptimizeLinear(bool maximize, const vector_t<double>& _direction, const matrix_t<double>& constraints, const vector_t<double>& constants, const EvaluationResult<double>& preSolution);

	template<typename Number>
	bool z3CheckConsistency(const matrix_t<Number>& constraints, const vector_t<Number>& constants);

	template<typename Number>
	bool z3CheckPoint(const matrix_t<Number>& constraints, const vector_t<Number>& constants, const Point<Number>& point);

	template<typename Number>
	std::vector<std::size_t> z3RedundantConstraints(const matrix_t<Number>& constraints, const vector_t<Number>& constants);

} // namespace hypro

#include "adaptions_z3.tpp"
