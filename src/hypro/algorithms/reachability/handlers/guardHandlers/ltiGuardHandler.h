#pragma once
#include "../../../../datastructures/reachability/SettingsProvider.h"
#include "../IHandler.h"

namespace hypro {
template <typename State>
class ltiGuardHandler {
	using Number = typename State::NumberType;

  protected:
	TransitionStatesMap mGuardSatisfyingStates;

  public:
	using TransitionStatesMap = std::map<Transition<Number>*, std::vector<State>>;

	bool operator()( const State& stateSet );

	const TransitionStatesMap& getGuardSatisfyingStateSets() const { return mGuardSatisfyingStates; }
};
}  // namespace hypro

#include "ltiGuardHandler.tpp"