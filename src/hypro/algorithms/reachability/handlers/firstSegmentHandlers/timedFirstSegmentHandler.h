#pragma once
#include "../IHandler.h"
#include "ltiFirstSegmentHandler.h"

namespace hypro
{
    template<class Representation, typename Number>
	class timedFirstSegmentHandler : public ltiFirstSegmentHandler<Representation,Number> {
	public:
		timedFirstSegmentHandler() = delete;
		timedFirstSegmentHandler(State_t<Number>* state, size_t index, tNumber timeStep) : ltiFirstSegmentHandler<Representation,Number>(state,index,timeStep){}
		
		void handle();
		const char* handlerName() {return "timedFirstSegmentHandler";}
	};
} // hypro

#include "timedFirstSegmentHandler.tpp"
