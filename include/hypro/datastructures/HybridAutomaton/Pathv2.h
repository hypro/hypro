/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../types.h"
#include "Transition.h"

namespace hypro {

template <class Number, class Location>
struct Path {
	Location const* rootLocation{};
	std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Location> const*>> elements{};	 ///< Path in pairs of time and discrete steps. Intervals holds the information when the transition was taken.

	Path() = default;
	Path( size_t numElements )
		: elements( numElements ) {}

	Path<Number, Location> head( std::size_t n ) const {
		assert( n <= elements.size() );
		Path<Number, Location> res;
		if ( n == elements.size() ) {
			res.elements = elements;
			res.rootLocation = rootLocation;
		} else if ( n == 0 ) {
			res.elements = {};
			res.rootLocation = rootLocation;
		} else {
			res.elements = std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Location> const*>>(
				  elements.begin(), elements.begin() + n );
			res.rootLocation = rootLocation;
		}
		return res;
	}

	Path<Number, Location> tail( std::size_t n ) const {
		assert( n <= elements.size() );
		Path<Number, Location> res;
		if ( n == elements.size() ) {
			res.elements = elements;
			res.rootLocation = rootLocation;
		} else if ( n == 0 ) {
			res.elements = {};
			res.rootLocation = elements.at( elements.size() - 1 ).second->getTarget();
		} else {
			res.elements = std::vector<std::pair<carl::Interval<SegmentInd>, Transition<Location> const*>>(
				  elements.end() - n, elements.end() );
			res.rootLocation = elements.at( elements.size() - ( n + 1 ) ).second->getTarget();
		}
		return res;
	}
};

template <typename Number, typename Location>
std::ostream& operator<<( std::ostream& out, const Path<Number, Location>& path ) {
	auto printNode = []( const auto ) {};
	out << path.rootLocation->getName();
	for ( const auto& pair : path.elements ) {
		out << ", " << pair.first << " -> " << pair.second->getTarget()->getName();
	}
	return out;
}

}  // namespace hypro