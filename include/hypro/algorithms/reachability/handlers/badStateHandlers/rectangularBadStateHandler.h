#pragma once

namespace hypro {
template <typename State, typename Location>
std::pair<CONTAINMENT, State> rectangularIntersectBadStates( const State& stateSet, const Location* loc, const HybridAutomaton<typename State::NumberType>& automaton );

template <typename State, typename Location>
std::pair<CONTAINMENT, State> rectangularBadIntersectInitialStates( const State& stateSet, const Location* loc, const HybridAutomaton<typename State::NumberType>& automaton );

}  // namespace hypro

#include "rectangularBadStateHandler.tpp"
