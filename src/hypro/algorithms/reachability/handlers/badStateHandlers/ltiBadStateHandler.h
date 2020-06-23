#pragma once
#include "datastructures/HybridAutomaton/Condition.h"

namespace hypro {

template <typename Representation, typename Number>
std::pair<CONTAINMENT, Representation> ltiIntersectBadStates( const Representation& valuationSet, const HybridAutomaton<Number>& automaton );

template <typename Representation, typename Number>
std::pair<CONTAINMENT, Representation> ltiIntersectBadStates( const Representation& valuationSet, const Condition<Number>& localBadState, const std::vector<Condition<Number>>& globalBadStates );

}  // namespace hypro

#include "ltiBadStateHandler.tpp"
