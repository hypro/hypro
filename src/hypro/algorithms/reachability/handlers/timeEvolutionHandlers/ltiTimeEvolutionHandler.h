#pragma once
#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../IHandler.h"

namespace hypro {
template <typename State, typename Number>
State ltiApplyTimeEvolution( const State& currentSegment, const matrix_t<Number>& transformation, const vector_t<Number>& translation, tNumber timeStepSize );

}  // namespace hypro

#include "ltiTimeEvolutionHandler.tpp"
