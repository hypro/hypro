#pragma once
#include "../IHandler.h"
#include "ltiTimeEvolutionHandler.h"
#include "../../../../datastructures/HybridAutomaton/State.h"

namespace hypro
{
    template<class Representation,typename Number>
	class timedElapseTimeEvolutionHandler : public ltiTimeEvolutionHandler<Representation,Number>{
	protected:
		bool mComputed;
		tNumber mTimeBound;
	public:
		timedElapseTimeEvolutionHandler() = delete;
		timedElapseTimeEvolutionHandler(State_t<Number>* state, size_t index, tNumber timeStep, tNumber timeBound, hypro::matrix_t<Number> trafo,hypro::vector_t<Number> translation) : ltiTimeEvolutionHandler<Representation,Number>(state, index, timeStep,trafo, translation){
			mComputed = false;
			mTimeBound = timeBound;
		}

		void handle();
		const char* handlerName() {return "timedElapseTimeEvolutionHandler";}
	};
} // hypro

#include "timedElapseTimeEvolutionHandler.tpp"