#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
class ltiInvariantHandler : public IInvariantHandler {
	using Number = typename State::NumberType;

  protected:
	CONTAINMENT mContainment = CONTAINMENT::NO;
	State* mState;
	size_t mIndex;
	bool mMarkedForDelete = false;

  public:
	ltiInvariantHandler() = delete;
	ltiInvariantHandler( State* state, size_t index ) {
		mState = state;
		mIndex = index;
	}

	void handle();
	const char* handlerName() { return "ltiInvariantHandler"; }
	// return containment status
	virtual CONTAINMENT getContainment() override { return mContainment; }
	virtual bool getMarkedForDelete() override { return mMarkedForDelete; }
	virtual void setMarkedForDelete( bool toDelete ) override { mMarkedForDelete = toDelete; }
    
    std::pair<CONTAINMENT, State> ltiIntersectInvariant( const State& stateSet );
};
}  // namespace hypro

#include "ltiInvariantHandler.tpp"
