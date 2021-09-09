#pragma once
#include "../IHandler.h"
#include "ltiResetHandler.h"

namespace hypro {
template <typename State>
class timedResetHandler : public ltiResetHandler<State> {
	using Number = typename State::NumberType;

  public:
	timedResetHandler() = delete;
	timedResetHandler( State* state, size_t index, matrix_t<Number> trafo, vector_t<Number> translation )
		: ltiResetHandler<State>( state, index, trafo, translation ) {}

	void handle();
	const char* handlerName() { return "timedResetHandler"; }
};
}  // namespace hypro

#include "timedResetHandler.tpp"