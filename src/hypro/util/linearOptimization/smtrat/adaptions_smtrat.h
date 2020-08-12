#pragma once
#include "../../VariablePool.h"
#include "SimplexSolver.h"
#include "convenience.h"
#include "helper_methods.h"

namespace hypro {

template <typename Number>
EvaluationResult<Number> smtratOptimizeLinearPostSolve( const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relationSymbols, bool maximize, const EvaluationResult<Number>& preSolution );

template <typename Number>
EvaluationResult<Number> smtratOptimizeLinear( const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relationSymbols, bool maximize );

template <typename Number>
bool smtratCheckConsistency( const matrix_t<Number>& constraints, const vector_t<Number>& constants );

template <typename Number>
bool smtratCheckPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relationSymbols, const Point<Number>& point );

template <typename Number>
std::vector<std::size_t> smtratRedundantConstraints( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relationSymbols );

template <typename Number>
EvaluationResult<Number> smtratGetInternalPoint( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relationSymbols );

}  // namespace hypro

#include "adaptions_smtrat.tpp"
