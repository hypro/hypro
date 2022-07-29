#pragma once

#include "../../types.h"
#include "Transition.h"

namespace hypro {

template <class Number>
struct Path {
	Location<Number> const* rootLocation{};
	std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Number, Location<Number>> const*>> elements{};	 ///< Path in pairs of time and discrete steps. Intervals holds the information when the transition was taken.

	Path() = default;
	Path( size_t numElements )
		: elements( numElements ) {}

	Path<Number> head( std::size_t n ) const {
		assert( n <= elements.size() );
		Path<Number> res;
		if ( n == elements.size() ) {
			res.elements = elements;
			res.rootLocation = rootLocation;
		} else if ( n == 0 ) {
			res.elements = {};
			res.rootLocation = rootLocation;
		} else {
			res.elements = std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Number, Location<Number>> const*>>(
				  elements.begin(), elements.begin() + n );
			res.rootLocation = rootLocation;
		}
		return res;
	}

	Path<Number> tail( std::size_t n ) const {
		assert( n <= elements.size() );
		Path<Number> res;
		if ( n == elements.size() ) {
			res.elements = elements;
			res.rootLocation = rootLocation;
		} else if ( n == 0 ) {
			res.elements = {};
			res.rootLocation = elements.at( elements.size() - 1 ).second->getTarget();
		} else {
			res.elements = std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Number, Location<Number>> const*>>(
				  elements.end() - n, elements.end() );
			res.rootLocation = elements.at( elements.size() - ( n + 1 ) ).second->getTarget();
		}
		return res;
	}
};

template <typename Number>
std::ostream& operator<<( std::ostream& out, const Path<Number>& path ) {
	auto printNode = []( const auto ) {};
	out << path.rootLocation->getName();
	for ( const auto& pair : path.elements ) {
		out << ", " << pair.first << " -> " << pair.second->getTarget()->getName();
	}
	return out;
}

}  // namespace hypro