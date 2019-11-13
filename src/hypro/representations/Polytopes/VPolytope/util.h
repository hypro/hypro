#pragma once
#include "../../../datastructures/Halfspace.h"
#include "../../../datastructures/Point.h"

namespace hypro {

template <typename N>
std::size_t numberOfPointsInHalfspace( const std::vector<Point<N>>& points, const Halfspace<N>& hsp ) {
	std::size_t count = 0;
	for ( const auto& v : points ) {
		if ( hsp.contains( v ) ) {
			++count;
		}
	}
	return count;
}
}  // namespace hypro
