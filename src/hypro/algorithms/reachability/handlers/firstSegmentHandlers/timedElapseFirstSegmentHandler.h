#pragma once
#include "../IHandler.h"
#include "ltiFirstSegmentHandler.h"

namespace hypro
{
    template<class Representation, typename Number>
	class timedElapseFirstSegmentHandler : public ltiFirstSegmentHandler<Representation,Number> {
	public:
		timedElapseFirstSegmentHandler() = delete;
		timedElapseFirstSegmentHandler(State_t<Number>* state, size_t index, tNumber timeStep) : ltiFirstSegmentHandler<Representation,Number>(state,index,timeStep){}
		
		void handle();
		const char* handlerName() {return "timedElapseFirstSegmentHandler";}
	};
} // hypro
