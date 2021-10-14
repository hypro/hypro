/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/*
 * Created by stefan on 13.10.21.
 */

#pragma once

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/adaptions_carl/adaptions_interval.h>
#include <hypro/util/sequenceGeneration/SequenceGenerator.h>

namespace hypro {

template <typename SetType>
struct BoxContainment {
	using Number = typename SetType::NumberType;

	BoxContainment( std::size_t splits, const Box<Number>& container )
		: mSplits( splits )
		, mContainer( container ) {}

	HyperOctreeOp operator()( const SetType& obj ) const {
		auto intersectionResult = mContainer.intersect( hypro::Converter<Number>::toBox( obj ) );
		// if the set is not at all contained, this is the wrong container
		if ( intersectionResult.empty() ) {
			return HyperOctreeOp::SKIP;
		}
		// if this is only partially contained, add to parent
		if ( intersectionResult != obj ) {
			return HyperOctreeOp::ADD;
		}
		// if the object fully fits into the current container, descend
		assert( intersectionResult == obj );
		return HyperOctreeOp::DESCEND;
	}

	std::vector<BoxContainment> split() const {
		auto intervals = mContainer.intervals();
		auto dim = intervals.size();
		// split all intervals into mSplits many parts
		std::vector<decltype( intervals )> splitIntervals{ dim, decltype( intervals ){} };
		for ( std::size_t i = 0; i < dim; ++i ) {
			splitIntervals[i] = split_homogeneously_weak_bounds( intervals[i], mSplits );
		}

		// create all boxes by creating all combinations of intervals
		Combinator boxCombinator{ mSplits, dim };
		std::vector<BoxContainment> newPredicates;
		while ( !boxCombinator.end() ) {
			auto intervalIndices = boxCombinator();

			// assemble new box
			std::vector<carl::Interval<Number>> newIntervals;
			for ( std::size_t pos = 0; pos < dim; ++pos ) {
				newIntervals.push_back( splitIntervals[pos][intervalIndices[pos]] );
			}
			newPredicates.emplace_back( BoxContainment( mSplits, Box<Number>{ newIntervals } ) );
		}
		return newPredicates;
	}

	std::size_t mSplits = 2;
	Box<Number> mContainer;
};

}  // namespace hypro