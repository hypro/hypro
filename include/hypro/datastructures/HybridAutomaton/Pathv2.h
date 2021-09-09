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

template <typename Number>
std::ostream& operator<<( std::ostream& out, const Path<Number>& path ) {
	out << path.rootLocation->getName();
	for ( const auto& pair : path.elements ) {
		out << ", " << pair.first << " -> " << pair.second->getTarget()->getName();
	}
	return out;
}

}  // namespace hypro