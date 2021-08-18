#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
class StochasticRectangularResetHandler : public IResetHandler {
	using Number = typename State::NumberType;
	using TransitionStatesMap = typename std::map<StochasticTransition<Number>*, std::vector<State>>;
	using TransitionContainmentMap = std::map<const StochasticTransition<Number>*, CONTAINMENT>;

  protected:
	State* mState;  // A state containing the first segment for each subspace
	std::vector<carl::Interval<Number>> mIntervalResets;
	TransitionStatesMap mResetSatisfyingStates;
	TransitionContainmentMap mResetContainment;

	size_t mIndex;

  public:

	void handle();
	const char* handlerName() { return "rectangularResetHandler"; }
	void rectangularIntersectReset( const State& stateSet, const HybridAutomaton<Number>& automaton );
	const TransitionStatesMap& getResetSatisfyingStateSets() const { return mResetSatisfyingStates; }
	const TransitionContainmentMap& getResetContainment() const { return mResetContainment; }
};
}  // namespace hypro

#include "StochasticRectangularResetHandler.tpp"
