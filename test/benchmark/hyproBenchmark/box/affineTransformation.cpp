#include "benchmarkBox.h"

namespace benchmark::box {

Results<std::size_t> affineTransformation( const Settings& settings ) {
	Results<std::size_t> ress;
	hypro::Box<::benchmark::Number> box;
	// benchmark against PPL
#ifdef HYPRO_USE_PPL
	using pplItv = Parma_Polyhedra_Library::Interval<
		  double, Parma_Polyhedra_Library::Interval_Info_Null<benchmark::box::Double_Interval_Policy>>;
	using pplbox = Parma_Polyhedra_Library::Box<pplItv>;
#endif
	box.insert( carl::Interval<::benchmark::Number>( -1, 1 ) );

	// initialize random number generator
	std::mt19937 generator{ 123 };
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	bool timeout = false;
	bool timeoutNaive = false;
	bool timeoutPpl = false;

	// iterate over dimensions
	for ( std::size_t d = 1; d < settings.maxDimension; ++d ) {
		// create instances
		std::vector<hypro::matrix_t<::benchmark::Number>> matrices;
		std::vector<hypro::vector_t<::benchmark::Number>> vectors;

		if ( !timeout ) {
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
			auto creationTime = creationTimer.elapsed();
			// std::cout << "Dimension " << d << ": Creation took " << creationTime.count() << " sec." << std::endl;
			ress.mCreationTime += creationTime;

			// run instances
			Timer runTimerHyPro;
			for ( std::size_t i = 0; i < settings.iterations; ++i ) {
				box.affineTransformation( matrices[i], vectors[i] );
			}
			auto runningTime = runTimerHyPro.elapsed();
			ress.emplace_back( { "affineTransformation", runningTime / settings.iterations, static_cast<int>( d ) } );
			std::cout << "Dimension " << d << ":  Running took " << runningTime.count() << " sec." << std::endl;
			if ( runningTime.count() > double( settings.timeoutSec ) ) {
				timeout = true;
			}
			ress.mRunningTime += runningTime;
		}

		if ( !timeoutNaive ) {
			Timer runTimerHyProNaive;
			for ( std::size_t i = 0; i < settings.iterations; ++i ) {
				std::vector<hypro::Point<::benchmark::Number>> vertices = box.vertices();
				hypro::Point<::benchmark::Number> manualMin =
					  hypro::Point<::benchmark::Number>( matrices[i] * ( vertices.begin()->rawCoordinates() ) );
				hypro::Point<::benchmark::Number> manualMax =
					  hypro::Point<::benchmark::Number>( matrices[i] * ( vertices.begin()->rawCoordinates() ) );
				for ( const auto& v : vertices ) {
					hypro::Point<::benchmark::Number> t =
						  hypro::Point<::benchmark::Number>( matrices[i] * v.rawCoordinates() );
					for ( std::size_t d = 0; d < box.dimension(); ++d ) {
						if ( manualMin.at( d ) > t.at( d ) ) {
							manualMin[d] = t[d];
						}
						if ( manualMax.at( d ) < t.at( d ) ) {
							manualMax[d] = t[d];
						}
					}
				}
				manualMin += vectors[i];
				manualMax += vectors[i];
			}
			auto runningTimeNaive = runTimerHyProNaive.elapsed();
			ress.emplace_back(
				  { "affineTransformationNaive", runningTimeNaive / settings.iterations, static_cast<int>( d ) } );
			std::cout << "Dimension " << d << ":  Running took " << runningTimeNaive.count() << " sec." << std::endl;

			if ( runningTimeNaive.count() > double( settings.timeoutSec ) ) {
				timeoutNaive = true;
			}
		}

		// prepare next run
		box.insert( carl::Interval<::benchmark::Number>( -1, 1 ) );
	}
	return ress;
}

}  // namespace box
}  // namespace benchmark
