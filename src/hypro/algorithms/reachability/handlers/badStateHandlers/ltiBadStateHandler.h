#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
class ltiBadStateHandler : public IBadStateHandler {
	using Number = typename State::NumberType;

  protected:
	bool mIntersects = false;
	State* mState;
	bool mNoBadStates = false;
	size_t mIndex;
	bool mMarkedForDelete = false;

  public:
	ltiBadStateHandler() = delete;
	ltiBadStateHandler( State* state, size_t index ) {
		mState = state;
		mIndex = index;
	}

	void handle();
	const char* handlerName() { return "ltiBadStateHandler"; }
	// return intersection status
	virtual bool intersectsBadState() override { return mIntersects; }

	virtual bool getMarkedForDelete() override { return mMarkedForDelete; }
	virtual void setMarkedForDelete( bool toDelete ) override { mMarkedForDelete = toDelete; }
};
}  // namespace hypro

#include "ltiBadStateHandler.tpp"
