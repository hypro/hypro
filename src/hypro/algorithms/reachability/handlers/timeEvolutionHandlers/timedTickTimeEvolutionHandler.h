#pragma once
#include "../IHandler.h"
#include "ltiTimeEvolutionHandler.h"
#include "../../../../datastructures/HybridAutomaton/State.h"

namespace hypro
{
    template<typename State>
	class timedTickTimeEvolutionHandler : public ltiTimeEvolutionHandler<State>{
		using Number = typename State::NumberType;
	public:
		timedTickTimeEvolutionHandler() = delete;
		timedTickTimeEvolutionHandler(State* state, size_t index, tNumber timeStep, matrix_t<Number> trafo,vector_t<Number> translation) : ltiTimeEvolutionHandler<State>(state, index, timeStep,trafo, translation){}

		void handle();
		const char* handlerName() {return "timedTickTimeEvolutionHandler";}
	};
} // hypro

#include "timedTickTimeEvolutionHandler.tpp"