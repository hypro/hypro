
#pragma once
#include "helper_functions.h"

#include <soplex.h>
#include <carl/core/Relation.h>

namespace hypro {

template <typename Number> 
EvaluationResult<Number> soplexOptimizeLinearPostSolve( const vector_t<Number>& direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, bool maximize, const EvaluationResult<Number>& preSolution );

template <typename Number>
EvaluationResult<Number> soplexOptimizeLinear( const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, bool maximize );

template <typename Number>
bool soplexCheckConsistency( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations );

template <typename Number>
bool soplexCheckPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, const Point<Number>& point );

template <typename Number>
std::vector<std::size_t> soplexRedundantConstraints( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations );

template <typename Number>
EvaluationResult<Number> soplexGetInternalPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations );

}  // namespace hypro

#include "adaptions_soplex.tpp"
