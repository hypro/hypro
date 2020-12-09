#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
std::pair<CONTAINMENT, State> rectangularIntersectInvariant( const State& stateSet, const Location<typename State::NumberType>* loc );
}  // namespace hypro

#include "rectangularInvariantHandler.tpp"
