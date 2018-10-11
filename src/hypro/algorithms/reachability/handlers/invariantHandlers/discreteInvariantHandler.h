#pragma once
#include "../IHandler.h"
#include "ltiInvariantHandler.h"

namespace hypro
{
    template<class Representation,typename Number>
	class discreteInvariantHandler : public ltiInvariantHandler<Representation,Number> {
	public:
		discreteInvariantHandler() = delete;
		discreteInvariantHandler(State_t<Number>* state, size_t index) : ltiInvariantHandler<Representation,Number>(state,index){}
		
		void handle();
		const char* handlerName() {return "discreteInvariantHandler";}

	};
} // hypro
