#pragma once
#include "../IHandler.h"
#include "ltiInvariantHandler.h"

namespace hypro {
template <typename State>
class discreteInvariantHandler : public ltiInvariantHandler<State> {
  public:
	discreteInvariantHandler() = delete;
	discreteInvariantHandler( State* state, size_t index )
		: ltiInvariantHandler<State>( state, index ) {}

	void handle();
	const char* handlerName() { return "discreteInvariantHandler"; }
};
}  // namespace hypro

#include "discreteInvariantHandler.tpp"
