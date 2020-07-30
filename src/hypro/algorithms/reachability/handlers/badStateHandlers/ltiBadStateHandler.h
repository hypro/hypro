#pragma once
#include "datastructures/HybridAutomaton/Condition.h"

namespace hypro {

template <typename State>
std::pair<CONTAINMENT, State> ltiIntersectBadStates( const State& stateSet, const HybridAutomaton<typename State::NumberType>& automaton );

template <typename State>
std::pair<CONTAINMENT, State> ltiIntersectBadStates( const State& stateSet, const Condition<typename State::Number>& localBadState, const std::vector<Condition<typename State::Number>>& globalBadStates );

}  // namespace hypro

#include "ltiBadStateHandler.tpp"
