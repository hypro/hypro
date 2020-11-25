#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
std::pair<CONTAINMENT, State> rectangularIntersectInvariant( const State& stateSet, const Location<Number>* loc );
}  // namespace hypro

#include "rectangularInvariantHandler.tpp"
