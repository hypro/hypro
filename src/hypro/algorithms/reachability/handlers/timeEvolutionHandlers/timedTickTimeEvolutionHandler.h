#pragma once
#include "../IHandler.h"
#include "ltiTimeEvolutionHandler.h"
#include "../../../../datastructures/HybridAutomaton/State.h"

namespace hypro
{
    template<class Representation,typename Number>
	class timedTickTimeEvolutionHandler : public ltiTimeEvolutionHandler<Representation,Number>{
	public:
		timedTickTimeEvolutionHandler() = delete;
		timedTickTimeEvolutionHandler(State_t<Number>* state, size_t index, tNumber timeStep, matrix_t<Number> trafo,vector_t<Number> translation) : ltiTimeEvolutionHandler<Representation,Number>(state, index, timeStep,trafo, translation){}

		void handle();
		const char* handlerName() {return "timedTickTimeEvolutionHandler";}
	};
} // hypro

#include "timedTickTimeEvolutionHandler.tpp"