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

Results<std::size_t> unite( const Settings& settings ) {
	Results<std::size_t> ress;
	// benchmark against PPL
#ifdef HYPRO_USE_PPL
	using pplItv = Parma_Polyhedra_Library::Interval<
		  double, Parma_Polyhedra_Library::Interval_Info_Null<benchmark::box::Double_Interval_Policy>>;
	using pplbox = Parma_Polyhedra_Library::Box<pplItv>;
#endif

	// initialize random number generator
	std::mt19937 generator;
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	// iterate over dimensions
	for ( std::size_t d = 1; d < settings.maxDimension; ++d ) {
		// create instances
		std::vector<hypro::Box<::benchmark::Number>> lhsBoxes;
		std::vector<hypro::Box<::benchmark::Number>> rhsBoxes;
		Timer creationTimer;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			hypro::Box<::benchmark::Number> lhsBox;
			hypro::Box<::benchmark::Number> rhsBox;
			for ( std::size_t id = 0; id < d; ++id ) {
				lhsBox.insert( carl::Interval<::benchmark::Number>( -dist( generator ), dist( generator ) ) );
				rhsBox.insert( carl::Interval<::benchmark::Number>( -dist( generator ), dist( generator ) ) );
				assert( !lhsBox.empty() );
				assert( !rhsBox.empty() );
			}
			lhsBoxes.emplace_back( std::move( lhsBox ) );
			rhsBoxes.emplace_back( std::move( rhsBox ) );
		}
		auto creationTime = creationTimer.elapsed();
		std::cout << "Dimension " << d << ": Creation took " << creationTime.count() << " sec." << std::endl;
		ress.mCreationTime += creationTime;

		// run instances
		Timer runTimerHyPro;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			auto tmp = lhsBoxes[i].unite( rhsBoxes[i] );
		}
		auto runningTime = runTimerHyPro.elapsed();
		ress.emplace_back( { "union", runningTime / settings.iterations, static_cast<int>( d ) } );
		std::cout << "Dimension " << d << ":  Running took " << runningTime.count() << " sec." << std::endl;

		ress.mRunningTime += runningTime;
	}
	return ress;
}

}  // namespace box
}  // namespace benchmark
