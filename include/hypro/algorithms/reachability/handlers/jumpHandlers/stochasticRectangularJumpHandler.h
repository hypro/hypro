#pragma once
#include "../../../../datastructures/reachability/ReachTreev2.h"
#include "../../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../../flags.h"
#include "ltiJumpHandler.h"
#include "util.h"

namespace hypro {

template <typename State>
class stochasticRectangularJumpHandler {
	using Number = typename State::NumberType;
	using TransitionStateMap = typename std::map<StochasticTransition<Number>*, std::vector<State>>;
	using StatePair = std::vector<std::pair<State, State>>;

  public:
	TransitionStateMap applyJump( const TransitionStateMap& states, StochasticTransition<Number>* transition, const AnalysisParameters& strategy );

	void aggregate( TransitionStateMap& processedStates, const TransitionStateMap& toAggregate, const AnalysisParameters& strategy ) const {
		ltiJumpHandler<State>::aggregate( processedStates, toAggregate, strategy );
	}

	void applyReset( State& state, StochasticTransition<Number>* transitionPtr ) const;

	State applyReverseJump( State& state, StochasticTransition<Number>* transition, const AnalysisParameters& strategy );

	void applyGuard( State& state, StochasticTransition<Number>* transitionPtr ) const;

	const StatePair& getPrdecessor() const { return mPredecessor; }

	// typename ReachTreeNode<State>::NodeList_t createNodesFromStates( Transition<Number>* transition, const std::vector<State>& states, std::size_t targetLevel, carl::Interval<tNumber>& coveredTimeInterval, typename ReachTreeNode<State>::Node_t parent );

  protected:
	StatePair mPredecessor;
};

}  // namespace hypro

#include "stochasticRectangularJumpHandler.tpp"
