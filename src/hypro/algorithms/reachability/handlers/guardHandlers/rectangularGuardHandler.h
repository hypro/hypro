#pragma once
#include "../../../../datastructures/reachability/SettingsProvider.h"
#include "../IHandler.h"

namespace hypro {
template <typename State>
class rectangularGuardHandler {
	using Number = typename State::NumberType;

  protected:
	CONTAINMENT mContainment = CONTAINMENT::BOT;
	State mState;
	Transition<Number>* mTransition = nullptr;

  public:
	rectangularGuardHandler() = delete;
	rectangularGuardHandler( Transition<Number>* transition )
		: mState()
		, mTransition( transition ) {
	}

	CONTAINMENT operator()( const State& state );
	CONTAINMENT getGuardContainment() { return mContainment; }
	bool guardSatisfied() {
		assert( mContainment != CONTAINMENT::BOT );
		return mContainment != CONTAINMENT::NO;
	}
	const State& getState() { return mState; }
	void setState( const State& state ) { mState = state; }
	Transition<Number>* getTransitionPtr() { return mTransition; }
	void reinitialize();
};
}  // namespace hypro

#include "rectangularGuardHandler.tpp"
