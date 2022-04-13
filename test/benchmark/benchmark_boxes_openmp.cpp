/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 13.04.22.
 */

#include <benchmark/benchmark.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <random>

namespace hypro::benchmark {

static void boxAffineTransformation( ::benchmark::State& st ) {
	using Number = double;
	// initialize random number generator
	std::mt19937 generator{ 123 };
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	Eigen::Index d{ st.range( 0 ) };
	hypro::Box<Number> box{ std::vector<carl::Interval<Number>>{ d, carl::Interval<Number>{ -1, 1 } } };
	for ( auto _ : st ) {
		hypro::matrix_t<Number> matrix = hypro::matrix_t<Number>( d, d );
		hypro::vector_t<Number> vector = hypro::vector_t<Number>( d );
		for ( Eigen::Index row = 0; row < d; ++row ) {
			for ( Eigen::Index col = 0; col < d; ++col ) {
				matrix( row, col ) = dist( generator );
			}
			vector( row ) = dist( generator );
		}

		box.affineTransformation( matrix, vector );
	}
}

BENCHMARK( boxAffineTransformation )->DenseRange( 1, 100, 2 );
// BENCHMARK_MAIN();

}  // namespace hypro::benchmark