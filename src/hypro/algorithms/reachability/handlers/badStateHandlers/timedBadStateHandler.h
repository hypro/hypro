#pragma once
#include "../IHandler.h"
#include "ltiBadStateHandler.h"

namespace hypro {
template <typename State>
class timedBadStateHandler : public ltiBadStateHandler<State> {
	using Number = typename State::NumberType;

  public:
	timedBadStateHandler() = delete;
	timedBadStateHandler( State* state, size_t index )
		: ltiBadStateHandler<State>( state, index ) {}

	void handle();
	const char* handlerName() { return "timedBadStateHandler"; }
};
}  // namespace hypro

#include "timedBadStateHandler.tpp"