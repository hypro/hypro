#pragma once

namespace hypro {
template <typename State>
std::vector<std::pair<CONTAINMENT, State>> stochasticRectangularIntersectBadStates( const State& stateSet, const HybridAutomaton<typename State::NumberType>& automaton );

template <typename State>
std::vector<std::pair<CONTAINMENT, State>> stochasticRectangularBadIntersectInitialStates( const State& stateSet, const HybridAutomaton<typename State::NumberType>& automaton );

}  // namespace hypro

#include "stochasticRectangularBadStateHandler.tpp"
