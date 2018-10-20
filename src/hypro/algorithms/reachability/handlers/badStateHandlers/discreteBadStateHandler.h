#pragma once
#include "../IHandler.h"
#include "ltiBadStateHandler.h"

namespace hypro
{
    template<class Representation,typename Number>
	class discreteBadStateHandler : public ltiBadStateHandler<Representation,Number> {
	public:
		discreteBadStateHandler() = delete;
		discreteBadStateHandler(State_t<Number>* state, size_t index) : ltiBadStateHandler<Representation,Number>(state,index){}
		
		void handle();
		const char* handlerName() {return "discreteBadStateHandler";}

	};
} // hypro

#include "discreteBadStateHandler.tpp"
