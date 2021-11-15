#pragma once
#include "hypro/datastructures/reachability/ReachTreev2.h"
#include "hypro/datastructures/reachability/workQueue/WorkQueue.h"
#include "hypro/flags.h"
#include "util.h"

namespace hypro {

template <typename Representation>
class singularJumpHandler {
	using Number = typename Representation::NumberType;
	using TransitionStateMap = typename std::map<Transition<Number>*, std::vector<Representation>>;

  public:
	TransitionStateMap applyJump( const TransitionStateMap& states, std::size_t subspace = 0 );

	void applyReset( Representation& state, Transition<Number>* transitionPtr, std::size_t subspace = 0 ) const;

	void applyReduction( Representation& state ) const;

	TransitionStateMap applyReverseJump( const TransitionStateMap& states, Transition<Number>* transition );

	void applyGuard( Representation& state, Transition<Number>* transitionPtr ) const;

	// typename ReachTreeNode<Representation>::NodeList_t createNodesFromStates( Transition<Number>* transition, const std::vector<Representation>& states, std::size_t targetLevel, carl::Interval<tNumber>& coveredTimeInterval, typename ReachTreeNode<Representation>::Node_t parent );
};

}  // namespace hypro

#include "singularJumpHandler.tpp"
