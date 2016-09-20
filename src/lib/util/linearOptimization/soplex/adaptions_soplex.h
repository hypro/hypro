
#pragma once
#include <soplex.h>

namespace hypro {

	template<typename Number>
	EvaluationResult<Number> soplexOptimizeLinear(const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const EvaluationResult<Number>& preSolution = EvaluationResult<Number>());

	template<typename Number>
	bool soplexCheckConsistency(const matrix_t<Number>& constraints, const vector_t<Number>& constants);

	template<typename Number>
	bool soplexCheckPoint(const matrix_t<Number>& constraints, const vector_t<Number>& constants, const Point<Number>& point);

} // namespace hypro

#include "adaptions_soplex.tpp"
