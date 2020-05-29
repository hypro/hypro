#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
class rectangularBadStateHandler {
	using Number = typename State::NumberType;

  protected:
	size_t mIndex = 0;
	CONTAINMENT mContainment = CONTAINMENT::BOT;

  public:
	CONTAINMENT operator()( State& currentStateSet );
	// return intersection status
	bool intersectsBadState() { return mContainment != CONTAINMENT::NO; }
};
}  // namespace hypro

#include "rectangularBadStateHandler.tpp"
