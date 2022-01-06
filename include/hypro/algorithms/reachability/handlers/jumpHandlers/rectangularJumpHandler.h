#pragma once
#include "hypro/datastructures/reachability/ReachTreev2.h"
#include "hypro/datastructures/reachability/workQueue/WorkQueue.h"
#include "hypro/flags.h"
#include "util.h"

namespace hypro {

template <typename State>
class rectangularJumpHandler {
	using Number = typename State::NumberType;
	using TransitionStateMap = typename std::map<Transition<Number>*, std::vector<State>>;

  public:
	TransitionStateMap applyJump( const TransitionStateMap& states, Transition<Number>* transition, const AnalysisParameters& strategy, bool reverse = false );

	void applyReset( State& state, Transition<Number>* transitionPtr ) const;

	TransitionStateMap applyReverseJump( const TransitionStateMap& states, Transition<Number>* transition, const AnalysisParameters& strategy );

	void applyGuard( State& state, Transition<Number>* transitionPtr ) const;

	// typename ReachTreeNode<State>::NodeList_t createNodesFromStates( Transition<Number>* transition, const std::vector<State>& states, std::size_t targetLevel, carl::Interval<tNumber>& coveredTimeInterval, typename ReachTreeNode<State>::Node_t parent );
  private:
	auto filter( const TransitionStateMap& states, Transition<Number>* transition ) const -> TransitionStateMap;
};

}  // namespace hypro

#include "rectangularJumpHandler.tpp"
