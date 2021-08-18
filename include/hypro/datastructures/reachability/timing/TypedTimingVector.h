#pragma once

#include "FlowpipeTimingVector.h"
#include "types.h"

namespace hypro {

class TypedTimingVector {
	FlowpipeTimingVector mFullContaimentTiming{};
	FlowpipeTimingVector mPartialContaimentTiming{};

	void appendInterval( CONTAINMENT c, IntegralInterval duration ) {
		if ( c == CONTAINMENT::FULL ) {
			mFullContaimentTiming.appendInterval( duration );
		}
		appendIntervalPartialContainment.appendInterval( duration );
	}

	void aggregateIntervals()
};
}  // namespace hypro