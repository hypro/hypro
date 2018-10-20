#pragma once
#include "../IHandler.h"
#include "ltiResetHandler.h"

namespace hypro
{
    template<class Representation,typename Number>
	class timedResetHandler : public ltiResetHandler<Representation,Number>{
	public:
		timedResetHandler() = delete;
		timedResetHandler(State_t<Number>* state, size_t index, matrix_t<Number> trafo,vector_t<Number> translation) : ltiResetHandler<Representation,Number>(state, index,trafo, translation){}

		void handle();
		const char* handlerName() {return "timedResetHandler";}
	};
} // hypro

#include "timedResetHandler.tpp"