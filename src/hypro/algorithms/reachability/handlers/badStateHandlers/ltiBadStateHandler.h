#pragma once
#include "datastructures/HybridAutomaton/Condition.h"

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

    std::pair<CONTAINMENT, State> ltiIntersectBadStates( const State& stateSet, const HybridAutomaton<typename State::NumberType>& automaton );
    std::pair<CONTAINMENT, State> ltiIntersectBadStates( const State& stateSet, const Condition<typename State::NumberType>& localBadState, const std::vector<Condition<typename State::NumberType>>& globalBadStates );

};

// template <typename State>
// std::pair<CONTAINMENT, State> ltiIntersectBadStates( const State& stateSet, const HybridAutomaton<typename State::NumberType>& automaton );

// template <typename State>
// std::pair<CONTAINMENT, State> ltiIntersectBadStates( const State& stateSet, const Condition<typename State::Number>& localBadState, const std::vector<Condition<typename State::Number>>& globalBadStates );

}  // namespace hypro

#include "ltiBadStateHandler.tpp"
