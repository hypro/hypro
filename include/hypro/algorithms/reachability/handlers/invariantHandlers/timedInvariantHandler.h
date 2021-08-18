#pragma once
#include "../IHandler.h"
#include "ltiInvariantHandler.h"

namespace hypro {
template <typename State>
class timedInvariantHandler : public ltiInvariantHandler<State> {
	using Number = typename State::NumberType;

  public:
	timedInvariantHandler() = delete;
	timedInvariantHandler( State* state, size_t index )
		: ltiInvariantHandler<State>( state, index ) {}

	void handle();
	const char* handlerName() { return "timedInvariantHandler"; }
};
}  // namespace hypro

#include "timedInvariantHandler.tpp"
