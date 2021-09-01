#pragma once
#include "../IHandler.h"
#include "ltiBadStateHandler.h"

namespace hypro {
template <typename State>
class discreteBadStateHandler : public ltiBadStateHandler<State> {
  public:
	discreteBadStateHandler() = delete;
	discreteBadStateHandler( State* state, size_t index )
		: ltiBadStateHandler<State>( state, index ) {}

	void handle();
	const char* handlerName() { return "discreteBadStateHandler"; }
};
}  // namespace hypro

#include "discreteBadStateHandler.tpp"
