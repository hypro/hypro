#pragma once
#include "../IHandler.h"
#include "ltiFirstSegmentHandler.h"

namespace hypro {
template <typename State>
class timedElapseFirstSegmentHandler : public ltiFirstSegmentHandler<State> {
	using Number = typename State::NumberType;

  public:
	timedElapseFirstSegmentHandler() = delete;
	timedElapseFirstSegmentHandler( State* state, size_t index, tNumber timeStep )
		: ltiFirstSegmentHandler<State>( state, index, timeStep ) {}

	void handle();
	const char* handlerName() { return "timedElapseFirstSegmentHandler"; }
};
}  // namespace hypro

#include "timedElapseFirstSegmentHandler.tpp"
