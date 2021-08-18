#pragma once
#include "../IHandler.h"
#include "ltiFirstSegmentHandler.h"

namespace hypro {
template <typename State>
class rectangularFirstSegmentHandler : public IFirstSegmentHandler<State> {
	using Number = typename State::NumberType;
	State& mState;
	flowVariant<Number> mFlow;
	std::size_t mIndex;

  public:
	rectangularFirstSegmentHandler( State& state, std::size_t index )
		: mState( state )
		, mFlow()
		, mIndex( index ) {}

	void handle();
	const char* handlerName() { return "rectangularFirstSegmentHandler"; }

	const flowVariant<typename State::NumberType>& getTransformation() const { return mFlow; }
};
}  // namespace hypro

#include "rectangularFirstSegmentHandler.tpp"
