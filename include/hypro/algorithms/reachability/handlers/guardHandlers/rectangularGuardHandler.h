#pragma once

namespace hypro {

template <typename Representation>
class rectangularGuardHandler {
	using Number = typename Representation::NumberType;
	using TransitionContainmentMap = std::map<const Transition<Number>*, CONTAINMENT>;

  public:
	using TransitionStatesMap = std::map<Transition<Number>*, std::vector<Representation> >;

	void operator()( const Representation& stateSet, const Location<Number>* loc );

	const TransitionStatesMap& getGuardSatisfyingStateSets() const { return mGuardSatisfyingStates; }
	const TransitionContainmentMap& getGuardContainment() const { return mGuardContainment; }

  protected:
	TransitionStatesMap mGuardSatisfyingStates;
	TransitionContainmentMap mGuardContainment;
};

}  // namespace hypro

#include "rectangularGuardHandler.tpp"
