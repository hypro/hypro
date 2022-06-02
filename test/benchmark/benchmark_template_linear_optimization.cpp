/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 13.04.22.
 */

#include <benchmark/benchmark.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <random>

namespace hypro::benchmark {

static void templateEvaluationClassic( ::benchmark::State& st ) {
	using Number = mpq_class;
	// initialize random number generator
	std::mt19937 generator{ 123 };
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	// Eigen::Index d{ st.range( 0 ) };
	// std::size_t numberDirections{ st.range( 1 ) };
	Eigen::Index d{ st.range( 0 ) };
	std::size_t numberDirections{ 8 };

	auto directions = hypro::computeTemplate<Number>( d, numberDirections );
	auto directionMatrix = hypro::createMatrix( directions );
	// create random polytope
	hypro::vector_t<Number> distances = hypro::vector_t<Number>( directions.size() );
	for ( Eigen::Index i = 0; i < distances.rows(); ++i ) {
		distances( i ) = dist( generator );
	}
	// create polytope
	auto poly = hypro::HPolytope<Number>( directionMatrix, distances );
	poly.removeRedundancy();
	for ( auto _ : st ) {
		st.PauseTiming();
		hypro::vector_t<Number> vector = hypro::vector_t<Number>( d );
		for ( Eigen::Index row = 0; row < d; ++row ) {
			vector( row ) = dist( generator );
		}
		st.ResumeTiming();
		hypro::EvaluationResult<Number> res;
		::benchmark::DoNotOptimize( res = poly.evaluate( vector ) );
	}
}

static void templateEvaluationNew( ::benchmark::State& st ) {
	using Number = mpq_class;
	// initialize random number generator
	std::mt19937 generator{ 123 };
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	// function sorting the template according to the L2-norm with the direction
	auto orderDirections = []( const auto& directions, const auto& direction ) {
		auto dim = directions.cols();
		std::map<Number, std::vector<Eigen::Index>> best;
		for ( Eigen::Index row = 0; row < directions.rows(); ++row ) {
			auto n = hypro::vector_t<Number>( directions.row( row ) ).dot( direction );
			if ( best.find( n ) == best.end() ) {
				best.insert( std::make_pair( n, std::vector<Eigen::Index>{ row } ) );
			} else {
				best[n].push_back( row );
			}
		}
		return best;
	};

	// Eigen::Index d{ st.range( 0 ) };
	// std::size_t numberDirections{ st.range( 1 ) };
	Eigen::Index d{ st.range( 0 ) };
	std::size_t numberDirections{ 8 };

	auto directions = hypro::computeTemplate<Number>( d, numberDirections );
	auto directionMatrix = hypro::createMatrix( directions );
	// create random polytope
	hypro::vector_t<Number> distances = hypro::vector_t<Number>( directions.size() );
	for ( Eigen::Index i = 0; i < distances.rows(); ++i ) {
		distances( i ) = dist( generator );
	}
	// create polytope
	auto poly = hypro::HPolytope<Number>( directionMatrix, distances );
	poly.removeRedundancy();
	for ( auto _ : st ) {
		st.PauseTiming();
		hypro::vector_t<Number> vector = hypro::vector_t<Number>( d );
		for ( Eigen::Index row = 0; row < d; ++row ) {
			vector( row ) = dist( generator );
		}
		st.ResumeTiming();
		auto sorted = orderDirections( directionMatrix, vector );

		// compute solution with the new approach, less aggressive for now
		auto constraints = hypro::matrix_t<Number>( d, d );
		auto constants = hypro::vector_t<Number>( d );
		std::size_t count = 0;
		std::size_t pos = 0;
		std::size_t i = 0;
		while ( count < d ) {
			constraints.row( count ) = directionMatrix.row( std::next( sorted.rbegin(), i )->second.at( pos ) );
			constants( count ) = distances( std::next( sorted.rbegin(), i )->second.at( pos ) );
			++count;
			++pos;
			if ( pos == std::next( sorted.rbegin(), i )->second.size() ) {
				pos = 0;
				++i;
			}
		}
		// For now use Optimizer - the benefit should be the reduced effort for the linear optimization
		auto x = constraints.colPivHouseholderQr().solve( constants );
		// auto opt = hypro::Optimizer( constraints, constants );
		Number res;
		::benchmark::DoNotOptimize( res = vector.dot( x.rhs() ) );
	}
}

static void templateEvaluationNewParallel( ::benchmark::State& st ) {
	using Number = mpq_class;
	// initialize random number generator
	std::mt19937 generator{ 123 };
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	// function sorting the template according to the L2-norm with the direction
	auto orderDirections = []( const auto& directions, const auto& direction ) {
		auto dim = directions.cols();
		std::map<Number, std::vector<Eigen::Index>> best;
#pragma openmp parallel for
		for ( Eigen::Index row = 0; row < directions.rows(); ++row ) {
			auto n = hypro::vector_t<Number>( directions.row( row ) ).dot( direction );
			if ( best.find( n ) == best.end() ) {
#pragma openmp critical
				best.insert( std::make_pair( n, std::vector<Eigen::Index>{ row } ) );
			} else {
#pragma openmp critical
				best[n].push_back( row );
			}
		}
		return best;
	};

	// Eigen::Index d{ st.range( 0 ) };
	// std::size_t numberDirections{ st.range( 1 ) };
	Eigen::Index d{ st.range( 0 ) };
	std::size_t numberDirections{ 8 };

	auto directions = hypro::computeTemplate<Number>( d, numberDirections );
	auto directionMatrix = hypro::createMatrix( directions );
	// create random polytope
	hypro::vector_t<Number> distances = hypro::vector_t<Number>( directions.size() );
	for ( Eigen::Index i = 0; i < distances.rows(); ++i ) {
		distances( i ) = dist( generator );
	}
	// create polytope
	auto poly = hypro::HPolytope<Number>( directionMatrix, distances );
	poly.removeRedundancy();
	for ( auto _ : st ) {
		st.PauseTiming();
		hypro::vector_t<Number> vector = hypro::vector_t<Number>( d );
		for ( Eigen::Index row = 0; row < d; ++row ) {
			vector( row ) = dist( generator );
		}
		st.ResumeTiming();
		auto sorted = orderDirections( directionMatrix, vector );

		// compute solution with the new approach, less aggressive for now
		auto constraints = hypro::matrix_t<Number>( d, d );
		auto constants = hypro::vector_t<Number>( d );
		std::size_t count = 0;
		std::size_t pos = 0;
		std::size_t i = 0;
		while ( count < d ) {
			constraints.row( count ) = directionMatrix.row( std::next( sorted.rbegin(), i )->second.at( pos ) );
			constants( count ) = distances( std::next( sorted.rbegin(), i )->second.at( pos ) );
			++count;
			++pos;
			if ( pos == std::next( sorted.rbegin(), i )->second.size() ) {
				pos = 0;
				++i;
			}
		}
		// For now use Optimizer - the benefit should be the reduced effort for the linear optimization
		auto x = constraints.colPivHouseholderQr().solve( constants );
		// auto opt = hypro::Optimizer( constraints, constants );
		Number res;
		::benchmark::DoNotOptimize( res = vector.dot( x.rhs() ) );
	}
}

// BENCHMARK( boxAffineTransformation )->DenseRange( 1, 100, 5 );
BENCHMARK( templateEvaluationClassic )->DenseRange( 1, 20, 5 );
BENCHMARK( templateEvaluationNew )->DenseRange( 1, 20, 3 );
BENCHMARK( templateEvaluationNewParallel )->DenseRange( 1, 20, 3 );
// BENCHMARK_MAIN();

}  // namespace hypro::benchmark