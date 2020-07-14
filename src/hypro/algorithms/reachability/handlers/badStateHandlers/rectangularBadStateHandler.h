#pragma once

namespace hypro {
template <typename State>
std::pair<CONTAINMENT, State> rectangularIntersectBadStates( const State& stateSet, const HybridAutomaton<typename State::NumberType>& automaton );

}  // namespace hypro

#include "rectangularBadStateHandler.tpp"
