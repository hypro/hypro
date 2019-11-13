#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
class rectangularInvariantHandler : public IInvariantHandler {
	using Number = typename State::NumberType;

  protected:
	CONTAINMENT mContainment = CONTAINMENT::NO;
	State* mState;
	size_t mIndex;
	bool mMarkedForDelete = false;

  public:
	rectangularInvariantHandler() = delete;
	rectangularInvariantHandler( State* state, size_t index )
		: mState( state )
		, mIndex( index ) {}

	void handle();
	const char* handlerName() { return "rectangularInvariantHandler"; }
	// return containment status
	virtual CONTAINMENT getContainment() override { return mContainment; }
	virtual bool getMarkedForDelete() override { return mMarkedForDelete; }
	virtual void setMarkedForDelete( bool toDelete ) override { mMarkedForDelete = toDelete; }
};
}  // namespace hypro

#include "rectangularInvariantHandler.tpp"
