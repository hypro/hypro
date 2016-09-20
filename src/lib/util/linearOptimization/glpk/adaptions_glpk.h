/**
 *
 */
#pragma once
#include "../EvaluationResult.h"
#include "../../../datastructures/Point.h"
#include "../../../config.h"
#include <glpk.h>

namespace hypro {
	inline void printProblem(glp_prob* glpkProblem);

	template<typename Number>
	EvaluationResult<Number> glpkOptimizeLinear(glp_prob* glpkProblem, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants);

	template<typename Number>
	bool glpkCheckPoint(glp_prob* glpkProblem, const matrix_t<Number>& constraints, const vector_t<Number>& , const Point<Number>& point);

	template<typename Number>
	std::vector<std::size_t> glpkRedundantConstraints(glp_prob* glpkProblem, matrix_t<Number> constraints, vector_t<Number> constants);
} // namespace hypro

#include "adaptions_glpk.tpp"
