#pragma once

#include "datastructures/HybridAutomaton/Transition.h"
#include "types.h"

namespace hypro {

template <class Number>
struct Path {
	Path() = default;
	Path(size_t numElements) : elements(numElements) {}
	std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Number> const* > > elements{};  ///< Path in pairs of time and discrete steps. Intervals holds the information when the transition was taken.
};

}