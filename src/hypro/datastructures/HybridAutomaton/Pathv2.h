#pragma once

#include "../../types.h"
#include "Transition.h"

namespace hypro {

template <class Number>
struct Path {
	Location<Number> const* rootLocation{};
	std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Number> const*> > elements{};	///< Path in pairs of time and discrete steps. Intervals holds the information when the transition was taken.

	Path() = default;
	Path( size_t numElements )
		: elements( numElements ) {}
};

}  // namespace hypro