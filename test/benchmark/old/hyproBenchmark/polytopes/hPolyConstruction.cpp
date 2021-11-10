/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "benchmarkPolytope.h"

namespace benchmark::polytope {

Results<std::size_t> hPolyConstruction( const Settings& settings ) {
	Results<std::size_t> ress;

	// initialize random number generator
	std::mt19937 generator{ 123 };
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	// iterate over dimensions
	for ( std::size_t d = 1; d <= settings.maxDimension; ++d ) {
		Timer dimensionTimer;
		std::size_t vertexCount = settings.iterations;
		// create instances
		std::vector<hypro::Point<::benchmark::Number>> samplePoints;
		for ( std::size_t pointCount = 0; pointCount < vertexCount; ++pointCount ) {
			hypro::vector_t<::benchmark::Number> coordinates = hypro::vector_t<::benchmark::Number>( d );
			for ( Eigen::Index row = 0; row < d; ++row ) {
				coordinates( row ) = dist( generator );
			}
			samplePoints.emplace_back( hypro::Point( coordinates ) );
		}
		Timer constructionTimer;
		hypro::HPolytope<::benchmark::Number> hpoly( samplePoints );
		auto runningTime = constructionTimer.elapsed();
		std::cout << "Construction of " << d << "-dimensional HPolytope took " << runningTime.count() << " sec\n";
		ress.mRunningTime += runningTime;
		ress.emplace_back( { "hPolyVertexConstruction", dimensionTimer.elapsed(), static_cast<int>( d ) } );
	}
	return ress;
}

}  // namespace benchmark::polytope