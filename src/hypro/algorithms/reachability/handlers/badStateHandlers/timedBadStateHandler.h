#pragma once
#include "../IHandler.h"
#include "ltiBadStateHandler.h"

namespace hypro
{
    template<class Representation,typename Number>
	class timedBadStateHandler : public ltiBadStateHandler<Representation,Number> {
	public:
		timedBadStateHandler() = delete;
		timedBadStateHandler(State_t<Number>* state, size_t index) : ltiBadStateHandler<Representation,Number>(state,index){}
		
		void handle();
		const char* handlerName() {return "timedBadStateHandler";}
	};
} // hypro

#include "timedBadStateHandler.tpp"