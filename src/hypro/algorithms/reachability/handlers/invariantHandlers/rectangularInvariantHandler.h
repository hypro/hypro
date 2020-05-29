#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
class rectangularInvariantHandler {
	using Number = typename State::NumberType;

  public:
	rectangularInvariantHandler() = default;

	CONTAINMENT operator()( State& stateSet );
};
}  // namespace hypro

#include "rectangularInvariantHandler.tpp"
