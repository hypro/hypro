
#pragma once
#include <z3.h>
#include "z3Convenience.h"

namespace hypro {

	template<typename Number>
	EvaluationResult<Number> z3OptimizeLinear(const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const EvaluationResult<Number>& preSolution = EvaluationResult<Number>());

	template<typename Number>
	bool z3CheckConsistency(const matrix_t<Number>& constraints, const vector_t<Number>& constants);

	template<typename Number>
	bool z3CheckPoint(const matrix_t<Number>& constraints, const vector_t<Number>& constants, const Point<Number>& point);

	template<typename Number>
	std::vector<std::size_t> z3RedundantConstraints(const matrix_t<Number>& constraints, const vector_t<Number>& constants);

} // namespace hypro

#include "adaptions_z3.tpp"
