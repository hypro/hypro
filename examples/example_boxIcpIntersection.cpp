/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * \example example_boxIcpIntersection.cpp This example shows how a box is intersected with a
 * halfspace using a method based on Interval Constraint Propagation (ICP), i.e., exploiting
 * interval arithmetic.
 */

#include <hypro/datastructures/Halfspace.h>
#include <hypro/representations/GeometricObjectBase.h>

int main() {
	// use rational arithmetic.
	typedef mpq_class Number;

	std::vector<carl::Interval<Number>> intervals;
	intervals.emplace_back( 1, 2 );
	intervals.emplace_back( 1, 2 );

	hypro::vector_t<Number> n1 = hypro::vector_t<Number>::Zero( 2 );
	n1 << 1, 1;

	// fully included
	hypro::Halfspace<Number> hsp1{ n1, Number( 2 ) };

	std::cout << "Intersect with " << hsp1 << std::endl;
	hypro::icpIntersectHalfspace( intervals, hsp1 );
	std::cout << "Result:" << std::endl;
	for ( const auto& i : intervals ) {
		std::cout << i << std::endl;
	}

	return 0;
}
