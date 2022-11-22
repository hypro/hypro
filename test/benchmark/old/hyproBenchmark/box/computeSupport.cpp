/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "benchmarkBox.h"

namespace benchmark {
namespace box {

Results<std::size_t> computeSupport( const Settings& settings ) {
	Results<std::size_t> ress;
	hypro::Box<::benchmark::Number> box;
	box.insert( carl::Interval<::benchmark::Number>( -1, 1 ) );

	// initialize random number generator
	std::mt19937 generator;
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	// iterate over dimensions
	for ( std::size_t d = 1; d < settings.maxDimension; ++d ) {
		// create instances
		std::vector<hypro::vector_t<::benchmark::Number>> normals;
		Timer creationTimer;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			hypro::vector_t<::benchmark::Number> normal = hypro::vector_t<::benchmark::Number>( d );
			for ( std::size_t id = 0; id < d; ++id ) {
				normal( id ) = dist( generator );
			}
			normals.emplace_back( normal );
		}
		auto creationTime = creationTimer.elapsed();
		ress.mCreationTime += creationTime;

		// run instances
		Timer runTimerHyPro;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			box.evaluate( normals[i] );
		}
		auto runningTime = runTimerHyPro.elapsed();
		ress.emplace_back( { "computeSupport", runningTime / settings.iterations, static_cast<int>( d ) } );
		std::cout << "Dimension " << d << ":  Running took " << runningTime.count() << " sec." << std::endl;

		// run instances
		Timer runTimerHyProConversion;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			hypro::Converter<::benchmark::Number>::toHPolytope( box ).evaluate( normals[i] );
		}
		auto runningTimeNaive = runTimerHyProConversion.elapsed();
		ress.emplace_back( { "computeSupportNaive", runningTimeNaive / settings.iterations, static_cast<int>( d ) } );

		ress.mRunningTime += runningTime;

		// prepare next run
		box.insert( carl::Interval<::benchmark::Number>( -1, 1 ) );
	}
	return ress;
}

}  // namespace box
}  // namespace benchmark
