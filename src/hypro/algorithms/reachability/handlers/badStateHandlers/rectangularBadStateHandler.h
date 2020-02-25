#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
class rectangularBadStateHandler : public IBadStateHandler {
	using Number = typename State::NumberType;

  protected:
	State& mState;
	size_t mIndex;
	CONTAINMENT mContainment = CONTAINMENT::NO;
	bool mNoBadStates = false;
	bool mMarkedForDelete = false;

  public:
	rectangularBadStateHandler() = delete;
	rectangularBadStateHandler( State& state, size_t index )
		: mState( state )
		, mIndex( index ) {}

	void handle();
	const char* handlerName() { return "rectangularBadStateHandler"; }
	// return intersection status
	virtual bool intersectsBadState() override { return mContainment != CONTAINMENT::NO; }

	virtual bool getMarkedForDelete() override { return mMarkedForDelete; }
	virtual void setMarkedForDelete( bool toDelete ) override { mMarkedForDelete = toDelete; }
};
}  // namespace hypro

#include "rectangularBadStateHandler.tpp"
