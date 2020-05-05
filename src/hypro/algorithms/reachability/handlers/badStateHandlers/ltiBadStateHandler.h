#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
std::pair<CONTAINMENT, State> ltiIntersectBadStates( const State& stateSet, size_t index );

}  // namespace hypro

#include "ltiBadStateHandler.tpp"
