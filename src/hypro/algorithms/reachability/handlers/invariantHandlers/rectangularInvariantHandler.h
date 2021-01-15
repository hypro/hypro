#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename Representation>
std::pair<CONTAINMENT, Representation> rectangularIntersectInvariant( const Representation& stateSet, const Location<typename Representation::NumberType>* loc );
}  // namespace hypro

#include "rectangularInvariantHandler.tpp"
