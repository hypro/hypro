/**
 *
 */
#pragma once
#include "../../../flags.h"
#ifdef HYPRO_USE_CLP

#include "../../../config.h"
#include "../../../datastructures/Point.h"
#include "../EvaluationResult.h"
#include "clp_context.h"

#include <ClpSimplex.hpp>

namespace hypro {

template <typename Number>
EvaluationResult<Number> clpOptimizeLinear( clp_context& context, const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, bool );

template <typename Number>
bool clpCheckPoint( clp_context& context, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const Point<Number>& _point );

template <typename Number>
std::vector<std::size_t> clpRedundantConstraints( clp_context& context, const matrix_t<Number>& constraints, const vector_t<Number>& constants );

template <typename Number>
EvaluationResult<Number> clpGetInternalPoint( clp_context& context );

SOLUTION clpCheckConsistency( clp_context& context );

}  // namespace hypro

#include "adaptions_clp.tpp"

#endif
