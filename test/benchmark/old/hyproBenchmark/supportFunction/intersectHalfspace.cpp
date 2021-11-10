/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "benchmark_sf.h"

namespace benchmark::sf {

Results<std::size_t> intersectHalfspace( const Settings& settings ) {
	Results<std::size_t> ress;

	// initialize random number generator
	std::mt19937 generator;
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	// iterate over dimensions
	for ( Eigen::Index d = 1; d < settings.maxDimension; ++d ) {
		// create base support function being the unit box
		hypro::matrix_t<::benchmark::Number> constraints = hypro::matrix_t<::benchmark::Number>::Zero( 2 * d, d );
		hypro::vector_t<::benchmark::Number> constants = hypro::vector_t<::benchmark::Number>::Ones( 2 * d );
		for ( Eigen::Index i = 0; i < d; ++i ) {
			constraints( 2 * i, i ) = 1;
			constraints( 2 * i + 1, i ) = -1;
		}
		hypro::SupportFunction<::benchmark::Number> sFunct( constraints, constants );
		// create instances
		std::vector<hypro::matrix_t<::benchmark::Number>> matrices;
		std::vector<hypro::vector_t<::benchmark::Number>> vectors;
		std::vector<hypro::vector_t<::benchmark::Number>> directions;
		Timer creationTimer;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			hypro::matrix_t<::benchmark::Number> matrix = hypro::matrix_t<::benchmark::Number>( d, d );
			hypro::vector_t<::benchmark::Number> vector = hypro::vector_t<::benchmark::Number>( d );
			hypro::vector_t<::benchmark::Number> direction = hypro::vector_t<::benchmark::Number>( d );
			for ( Eigen::Index row = 0; row < d; ++row ) {
				for ( Eigen::Index col = 0; col < d; ++col ) {
					matrix( row, col ) = dist( generator );
				}
				vector( row ) = dist( generator );
				direction( row ) = dist( generator );
			}
			matrices.emplace_back( std::move( matrix ) );
			vectors.emplace_back( std::move( vector ) );
			directions.emplace_back( std::move( direction ) );
		}
		auto creationTime = creationTimer.elapsed();
		std::cout << "Dimension " << d << ": Creation took " << creationTime.count() << " sec." << std::endl;
		ress.mCreationTime += creationTime;

		// run instances
		Timer runTimerHyPro;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			for ( std::size_t multiplications = 0; multiplications < 1024; ++multiplications ) {
				sFunct = sFunct.affineTransformation( matrices[i], vectors[i] );
			}
			sFunct.evaluate( directions[i] );
		}
		auto runningTime = runTimerHyPro.elapsed();
		ress.emplace_back( { "affineTransformation", runningTime, static_cast<int>( d ) } );
		std::cout << "Dimension " << d << ":  Running took " << runningTime.count() << " sec." << std::endl;

		ress.mRunningTime += runningTime;
	}
	return ress;
}

}  // namespace benchmark::sf
