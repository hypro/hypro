#pragma once
#include "../../../../datastructures/reachability/ReachTreev2.h"
#include "../../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../../flags.h"
#include "util.h"

namespace hypro {

template <typename State>
class rectangularJumpHandler {
	using Number = typename State::NumberType;
	using TransitionStateMap = typename std::map<Transition<Number>*, std::vector<State>>;

  public:
	TransitionStateMap applyJump( const TransitionStateMap& states, Transition<Number>* transition, const AnalysisParameters& strategy );

	void aggregate( TransitionStateMap& processedStates, const TransitionStateMap& toAggregate, const AnalysisParameters& strategy ) const;

	void applyReset( State& state, Transition<Number>* transitionPtr ) const;

	void applyReduction( State& state ) const;

	TransitionStateMap applyReverseJump( const TransitionStateMap& states, Transition<Number>* transition, const AnalysisParameters& strategy );

	void applyGuard( State& state, Transition<Number>* transitionPtr ) const;

	// typename ReachTreeNode<State>::NodeList_t createNodesFromStates( Transition<Number>* transition, const std::vector<State>& states, std::size_t targetLevel, carl::Interval<tNumber>& coveredTimeInterval, typename ReachTreeNode<State>::Node_t parent );
};

}  // namespace hypro

#include "rectangularJumpHandler.tpp"
