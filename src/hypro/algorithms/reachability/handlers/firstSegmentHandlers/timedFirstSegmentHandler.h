#pragma once
#include "../IHandler.h"
#include "ltiFirstSegmentHandler.h"

namespace hypro
{
    template<typename State>
	class timedFirstSegmentHandler : public ltiFirstSegmentHandler<State> {
		using Number = typename State::NumberType;
	public:
		timedFirstSegmentHandler() = delete;
		timedFirstSegmentHandler(State* state, size_t index, tNumber timeStep) : ltiFirstSegmentHandler<State>(state,index,timeStep){}

		void handle();
		const char* handlerName() {return "timedFirstSegmentHandler";}
	};
} // hypro

#include "timedFirstSegmentHandler.tpp"
