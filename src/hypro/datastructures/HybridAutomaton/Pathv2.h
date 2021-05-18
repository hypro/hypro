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

    std::pair<Path<Number>, Path<Number>> split( std::size_t n ) const {
        assert( n < elements.size() );
        Path<Number> pathPrefix;
        Path<Number> pathSuffix;
        pathPrefix.elements = std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Number> const*>>(
            elements.begin(), elements.begin() + n - 1 );
        pathSuffix.elements = std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Number> const*>>(
            elements.begin() + n, elements.end() );
        pathPrefix.rootLocation = rootLocation;
        pathSuffix.rootLocation = elements.at( n - 1 ).second->getTarget();
        return std::make_pair( pathPrefix, pathSuffix );
    }
};

}  // namespace hypro