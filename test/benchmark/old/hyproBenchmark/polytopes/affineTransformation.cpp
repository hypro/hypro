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

Results<std::size_t> affineTransformation( const Settings& settings ) {
	Results<std::size_t> ress;
	// benchmark against PPL
#ifdef HYPRO_USE_PPL
	using pplItv = Parma_Polyhedra_Library::Interval<
		  double, Parma_Polyhedra_Library::Interval_Info_Null<benchmark::box::Double_Interval_Policy>>;
	using pplbox = Parma_Polyhedra_Library::Box<pplItv>;
#endif

	// initialize random number generator
	std::mt19937 generator{ 123 };
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	// iterate over dimensions
	for ( std::size_t d = 1; d < settings.maxDimension; ++d ) {
		// create instances
		std::vector<hypro::matrix_t<::benchmark::Number>> matrices;
		std::vector<hypro::vector_t<::benchmark::Number>> vectors;
		Timer creationTimer;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			hypro::matrix_t<::benchmark::Number> matrix = hypro::matrix_t<::benchmark::Number>( d, d );
			hypro::vector_t<::benchmark::Number> vector = hypro::vector_t<::benchmark::Number>( d );
			for ( Eigen::Index row = 0; row < d; ++row ) {
				for ( Eigen::Index col = 0; col < d; ++col ) {
					matrix( row, col ) = dist( generator );
				}
				vector( row ) = dist( generator );
			}
			matrices.emplace_back( std::move( matrix ) );
			vectors.emplace_back( std::move( vector ) );
		}

		// create vpoly, raute-shaped
		hypro::VPolytope<::benchmark::Number> vpoly;
		for ( Eigen::Index i = 0; i < d; ++i ) {
			hypro::vector_t<::benchmark::Number> coords = hypro::vector_t<::benchmark::Number>::Zero( d );
			coords( i ) = 1;
			vpoly.insert( coords );
			coords( i ) = -1;
			vpoly.insert( coords );
		}

		// create hpoly via conversion
		hypro::HPolytope<::benchmark::Number> hpoly = hypro::Converter<::benchmark::Number>::toHPolytope( vpoly );

		auto creationTime = creationTimer.elapsed();
		std::cout << "Dimension " << d << ": Creation took " << creationTime.count() << " sec." << std::endl;
		ress.mCreationTime += creationTime;

		// run instances
		Timer runTimerHyPro;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			vpoly.affineTransformation( matrices[i], vectors[i] );
		}
		auto runningTime = runTimerHyPro.elapsed();
		ress.emplace_back( { "affineTransformationVPoly", runningTime / settings.iterations, static_cast<int>( d ) } );

		runTimerHyPro.reset();
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			hpoly.affineTransformation( matrices[i], vectors[i] );
		}
		runningTime = runTimerHyPro.elapsed();
		ress.emplace_back( { "affineTransformationHPoly", runningTime / settings.iterations, static_cast<int>( d ) } );

		std::cout << "Dimension " << d << ":  Running took " << runningTime.count() << " sec." << std::endl;

		ress.mRunningTime += runningTime;
	}
	return ress;
}

}  // namespace benchmark::polytope
