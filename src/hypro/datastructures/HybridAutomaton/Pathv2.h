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

    std::pair<Path<Number>, Path<Number>> split( std::size_t n ) {
        assert( n < elements.size() );
        auto pathPrefix = std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Number> const*>>(
            elements.begin(), elements.begin() + n - 1 );
        auto pathPostfix = std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Number> const*>>(
            elements.begin() + n, elements.end() );
        return std::make_pair(
            Path{ rootLocation, pathPrefix },
            Path{ elements.at( n - 1 ).second->getTarget(), pathPostfix } );
    }
};

}  // namespace hypro