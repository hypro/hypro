#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
std::pair<CONTAINMENT, State> ltiIntersectInvariant( const State& stateSet );
}  // namespace hypro

#include "ltiInvariantHandler.tpp"
