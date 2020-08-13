#pragma once

namespace hypro {
template <typename State>
class rectangularGuardHandler {
	using Number = typename State::NumberType;
	using TransitionContainmentMap = std::map<const Transition<Number>*, CONTAINMENT>;

  public:
	using TransitionStatesMap = std::map<Transition<Number>*, std::vector<State>>;

	void operator()( const State& stateSet );

	const TransitionStatesMap& getGuardSatisfyingStateSets() const { return mGuardSatisfyingStates; }
	const TransitionContainmentMap& getGuardContainment() const { return mGuardContainment; }

  protected:
	TransitionStatesMap mGuardSatisfyingStates;
	TransitionContainmentMap mGuardContainment;
};
}  // namespace hypro

#include "rectangularGuardHandler.tpp"
