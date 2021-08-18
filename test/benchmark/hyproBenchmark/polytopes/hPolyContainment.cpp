#include "benchmarkPolytope.h"
#include <valgrind/callgrind.h>

namespace benchmark {
namespace polytope {

Results<std::size_t> hPolyContainment( const Settings& settings ) {
	Results<std::size_t> ress;

	// initialize random number generator
	std::mt19937 generator;
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	// iterate over dimensions
	for ( std::size_t d = 1; d < settings.maxDimension; ++d ) {
		CALLGRIND_STOP_INSTRUMENTATION;
		// create instances
		std::vector<hypro::vector_t<::benchmark::Number>> samples;
		Timer creationTimer;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			hypro::vector_t<::benchmark::Number> sample = hypro::vector_t<::benchmark::Number>( d );
			for ( std::size_t row = 0; row < d; ++row ) {
				sample( row ) = dist( generator );
			}
			samples.emplace_back( std::move( sample ) );
		}

		// create vpoly, randomized from 10 points
		hypro::VPolytope<::benchmark::Number> vpoly;
		for ( std::size_t vertexIndex = 0; vertexIndex < 3 * d; ++vertexIndex ) {
			hypro::vector_t<::benchmark::Number> vertex = hypro::vector_t<::benchmark::Number>::Zero( d );
			for ( std::size_t i = 0; i < d; ++i ) {
				vertex( i ) = dist( generator );
			}
			vpoly.insert( vertex );
		}

		// create hpoly via conversion and cached via settings-conversion construction
		hypro::HPolytope<::benchmark::Number> hpoly = hypro::Converter<::benchmark::Number>::toHPolytope( vpoly );
		hypro::HPolytopeT<::benchmark::Number, hypro::Converter<::benchmark::Number>,
						  hypro::HPolytopeBoundingBoxCaching>
			  hpolyCache{ hpoly };

		auto creationTime = creationTimer.elapsed();
		std::cout << "Dimension " << d << ": Creation took " << creationTime.count() << " sec." << std::endl;
		ress.mCreationTime += creationTime;

		CALLGRIND_START_INSTRUMENTATION;

		// run instances
		Timer runTimerHyPro;
		bool containment;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			hpoly.contains( samples[i] );
		}
		auto runningTime = runTimerHyPro.elapsed();
		ress.emplace_back( { "hPolyContainmentRegular", runningTime, static_cast<int>( d ) } );

		runTimerHyPro.reset();
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			hpolyCache.contains( samples[i] );
		}
		runningTime = runTimerHyPro.elapsed();
		ress.emplace_back( { "hPolyContainmentCache", runningTime, static_cast<int>( d ) } );

		std::cout << "Dimension " << d << ":  Running took " << runningTime.count() << " sec." << std::endl;

		ress.mRunningTime += runningTime;
	}
	return ress;
}

}  // namespace polytope
}  // namespace benchmark
