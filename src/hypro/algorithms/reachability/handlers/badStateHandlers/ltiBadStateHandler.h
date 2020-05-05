#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
std::pair<CONTAINMENT, State> ltiIntersectBadStates( const State& stateSet );

}  // namespace hypro

#include "ltiBadStateHandler.tpp"
