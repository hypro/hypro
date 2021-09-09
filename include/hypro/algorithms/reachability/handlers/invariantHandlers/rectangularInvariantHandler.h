#pragma once
#include "../../FlowpipeConstructionConvenience.h"
#include "../IHandler.h"

namespace hypro {
template <typename Representation>
std::pair<CONTAINMENT, Representation> rectangularIntersectInvariant( const Representation& stateSet, const Location<typename Representation::NumberType>* loc );
}  // namespace hypro

#include "rectangularInvariantHandler.tpp"
