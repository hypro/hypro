#pragma once
#include "../../../../datastructures/HybridAutomaton/Condition.h"

namespace hypro {

template <typename Representation, typename Number>
std::pair<CONTAINMENT, Representation> ltiIntersectBadStates( const Representation& valuationSet, Location<Number> const* location, const HybridAutomaton<Number>& automaton, std::size_t I = 0 );

}  // namespace hypro

#include "ltiBadStateHandler.tpp"
