#pragma once
#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../../../../datastructures/reachability/NodeManager.h"
#include "../../../../datastructures/reachability/ReachTreeNodev2.h"
#include "../../../../datastructures/reachability/Task.h"
#include "../../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../../flags.h"
#include "../HandlerFactory.h"
#include "../IHandler.h"
#include "timingUtil.h"
#include "util.h"

namespace hypro {

template <typename State>
class ltiJumpHandler {
	using Number = typename State::NumberType;
	using TransitionStateMap = typename std::map<Transition<Number>*, std::vector<State>>;

  public:
	TransitionStateMap applyJump( const TransitionStateMap& states, Transition<Number>* transition, const AnalysisParameters& strategy );

	void aggregate( TransitionStateMap& processedStates, const TransitionStateMap& toAggregate, const AnalysisParameters& strategy ) const;

	void applyReset( State& state, Transition<Number>* transitionPtr ) const;

	// typename ReachTreeNode<State>::NodeList_t createNodesFromStates( Transition<Number>* transition, const std::vector<State>& states, std::size_t targetLevel, carl::Interval<tNumber>& coveredTimeInterval, typename ReachTreeNode<State>::Node_t parent );
};

}  // namespace hypro

#include "ltiJumpHandler.tpp"
