#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
std::pair<CONTAINMENT, State> rectangularIntersectInvariant( const State& stateSet );
}  // namespace hypro

#include "rectangularInvariantHandler.tpp"
