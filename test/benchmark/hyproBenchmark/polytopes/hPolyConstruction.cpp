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