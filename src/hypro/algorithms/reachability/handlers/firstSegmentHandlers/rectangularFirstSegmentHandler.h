#pragma once
#include "../IHandler.h"
#include "ltiFirstSegmentHandler.h"

namespace hypro
{
    template<typename State>
	class rectangularFirstSegmentHandler {
		using Number = typename State::NumberType;
	public:
		rectangularFirstSegmentHandler() = default;

		void handle();
		const char* handlerName() {return "rectangularFirstSegmentHandler";}
	};
} // hypro

#include "rectangularFirstSegmentHandler.tpp"
