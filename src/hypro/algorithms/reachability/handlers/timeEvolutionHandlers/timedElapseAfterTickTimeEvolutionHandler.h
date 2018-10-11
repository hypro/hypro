#pragma once
#include "../IHandler.h"
#include "ltiTimeEvolutionHandler.h"
#include "../../../../datastructures/HybridAutomaton/State.h"

namespace hypro
{
    /**
	* used when a timedFirstSegmentHandler was used. It does a tick on first segment and is used if the automaton
	* is not full timed
	*/
	template<class Representation,typename Number>
	class timedElapseAfterTickTimeEvolutionHandler : public ltiTimeEvolutionHandler<Representation,Number>{
	protected:
		bool mComputed;
		tNumber mTimeBound;
	public:
		timedElapseAfterTickTimeEvolutionHandler() = delete;
		timedElapseAfterTickTimeEvolutionHandler(State_t<Number>* state, size_t index, tNumber timeStep, tNumber timeBound, hypro::matrix_t<Number> trafo,hypro::vector_t<Number> translation) : ltiTimeEvolutionHandler<Representation,Number>(state, index, timeStep,trafo, translation){
			mComputed = false;
			mTimeBound = timeBound;
		}

		void handle();
		const char* handlerName() {return "timedElapseContinuousEvolutionHandler";}
	};
} // hypro
