#pragma once
#include "../IHandler.h"
#include "ltiInvariantHandler.h"

namespace hypro
{
    template<class Representation,typename Number>
	class timedInvariantHandler : public ltiInvariantHandler<Representation,Number> {
	public:
		timedInvariantHandler() = delete;
		timedInvariantHandler(State_t<Number>* state, size_t index) : ltiInvariantHandler<Representation,Number>(state,index){}
		
		void handle();
		const char* handlerName() {return "timedInvariantHandler";}

	};
} // hypro

#include "timedInvariantHandler.tpp"
