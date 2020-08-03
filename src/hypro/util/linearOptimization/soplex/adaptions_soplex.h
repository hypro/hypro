
#pragma once
#include <soplex.h>
#include <carl/core/Relation.h>

namespace hypro {

template <typename Number>
soplex::SoPlex initializeSolver( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations );

template <typename Number>
EvaluationResult<Number> soplexOptimizeLinear( const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, bool maximize );

template <typename Number>
bool soplexCheckConsistency( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations );

template <typename Number>
bool soplexCheckPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, const Point<Number>& point );

}  // namespace hypro

#include "adaptions_soplex.tpp"
