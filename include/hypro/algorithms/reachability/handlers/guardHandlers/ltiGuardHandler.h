#pragma once

namespace hypro {
template <typename State>
class ltiGuardHandler {
	using Number = typename State::NumberType;

  public:
	using TransitionStatesMap = std::map<Transition<Number>*, std::vector<State>>;

	bool operator()( const State& stateSet );

	const TransitionStatesMap& getGuardSatisfyingStateSets() const { return mGuardSatisfyingStates; }

  protected:
	TransitionStatesMap mGuardSatisfyingStates;
};
}  // namespace hypro

#include "ltiGuardHandler.tpp"