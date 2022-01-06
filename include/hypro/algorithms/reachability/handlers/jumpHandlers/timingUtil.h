#pragma once
#include "../../../../datastructures/reachability/timing/EventTimingContainer.h"
#include "../../../../datastructures/reachability/timing/EventTimingProvider.h"

namespace hypro {

template <typename Number, typename State>
inline bool updateTiming( typename EventTimingContainer<Number>::Node_t current, carl::Interval<tNumber> entryTimestamp, Transition<Number>* transition, StrategyNode<State> currentStratNode, bool insert ) {
	bool skip = false;
	for ( auto tChild : current->getChildren() ) {
		if ( tChild->getLocation() == transition->getTarget() && tChild->getEntryTransition() == transition && set_has_intersection( tChild->getEntryTimestamp(), entryTimestamp ) ) {
			// in case no aggregation happened, the timing node should cover all separate branches in one, i.e. we unify the entry time
			// stamps. Otherwise we can use regular refinement by intersection (2nd case).
			if ( ( currentStratNode.aggregation == AGG_SETTING::NO_AGG && currentStratNode.clustering == -1 ) ||
				 ( currentStratNode.aggregation == AGG_SETTING::MODEL && transition->getAggregation() == Aggregation::none ) ) {
				tChild->setEntryTimestamp( set_intersection( entryTimestamp, tChild->getEntryTimestamp() ) );
			} else {
				tChild->setEntryTimestamp( set_convexHull( entryTimestamp, tChild->getEntryTimestamp() ) );
			}
			skip = true;
			break;
		}
	}

	if ( !skip && insert ) {
		typename EventTimingContainer<Number>::Node_t newChild = EventTimingProvider<Number>::getInstance().addChildToNode( current, SettingsProvider<State>::getInstance().getReachabilitySettings().timeBound * SettingsProvider<State>::getInstance().getReachabilitySettings().jumpDepth );
		newChild->setLocation( transition->getTarget() );
		newChild->setEntryTransition( transition );
		newChild->setEntryTimestamp( entryTimestamp );
	}

	return skip;
}

}  // namespace hypro
