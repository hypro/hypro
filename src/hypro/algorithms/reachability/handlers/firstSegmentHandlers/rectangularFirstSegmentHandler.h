#pragma once
#include "../IHandler.h"
#include "ltiFirstSegmentHandler.h"

namespace hypro
{
    template<typename State>
	class rectangularFirstSegmentHandler {
		using Number = typename State::NumberType;

		rectangularFlow<Number> mFlow;
	public:
		rectangularFirstSegmentHandler(const rectangularFlow<Number>& flow ) : mFlow(flow) {}

		void handle();
		const char* handlerName() {return "rectangularFirstSegmentHandler";}

		const flowVariant<typename State::NumberType> getTransformation() const { return mFlow; }
	};
} // hypro

#include "rectangularFirstSegmentHandler.tpp"
