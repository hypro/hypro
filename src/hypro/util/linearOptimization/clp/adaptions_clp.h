/**
 *
 */
#pragma once
#include "../../../config.h"
#include "../../../datastructures/Point.h"
#include "../EvaluationResult.h"

#include <ClpSimplex.hpp>

namespace hypro {

template <typename Number>
EvaluationResult<Number> clpOptimizeLinear();

template <typename Number>
bool clpCheckPoint();

template <typename Number>
std::vector<std::size_t> clpRedundantConstraints();

template <typename Number>
EvaluationResult<Number> clpGetInternalPoint();

}  // namespace hypro

#include "adaptions_clp.tpp"
