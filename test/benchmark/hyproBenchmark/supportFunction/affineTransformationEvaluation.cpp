#include "benchmark_sf.h"

namespace benchmark {
namespace sf {

void affineTrafoCreator( std::map<std::size_t, std::vector<hypro::matrix_t<::benchmark::Number>>>& matricesMap,
						 std::map<std::size_t, std::vector<hypro::vector_t<::benchmark::Number>>>& vectorsMap,
						 std::map<std::size_t, std::vector<hypro::vector_t<::benchmark::Number>>>& directionsMap,
						 const Settings& settings ) {
	// initialize random number generator
	std::mt19937 generator;
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	for ( std::size_t d = 1; d < settings.maxDimension; ++d ) {
		// create instances
		std::vector<hypro::matrix_t<::benchmark::Number>> matrices;
		std::vector<hypro::vector_t<::benchmark::Number>> vectors;
		std::vector<hypro::vector_t<::benchmark::Number>> directions;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			hypro::matrix_t<::benchmark::Number> matrix = hypro::matrix_t<::benchmark::Number>( d, d );
			hypro::vector_t<::benchmark::Number> vector = hypro::vector_t<::benchmark::Number>( d );
			hypro::vector_t<::benchmark::Number> direction = hypro::vector_t<::benchmark::Number>( d );
			for ( std::size_t row = 0; row < d; ++row ) {
				for ( std::size_t col = 0; col < d; ++col ) {
					matrix( row, col ) = dist( generator );
				}
				vector( row ) = dist( generator );
				direction( row ) = dist( generator );
			}
			matrices.emplace_back( std::move( matrix ) );
			vectors.emplace_back( std::move( vector ) );
			directions.emplace_back( std::move( direction ) );
		}
		matricesMap[d] = matrices;
		vectorsMap[d] = vectors;
		directionsMap[d] = directions;
	}
}

Results<std::size_t> affineTransformationEvaluation( const Settings& settings ) {
	Results<std::size_t> ress;

	std::map<std::size_t, std::vector<hypro::matrix_t<::benchmark::Number>>> matricesMap;
	std::map<std::size_t, std::vector<hypro::vector_t<::benchmark::Number>>> vectorsMap;
	std::map<std::size_t, std::vector<hypro::vector_t<::benchmark::Number>>> directionsMap;

	affineTrafoCreator( matricesMap, vectorsMap, directionsMap, settings );

	std::queue<std::future<Results<std::size_t>>> workingQueue;

	// iterate over dimensions
	for ( std::size_t d = 1; d <= settings.maxDimension; d += settings.stepSize ) {
		// create base support function being the unit box
		hypro::matrix_t<::benchmark::Number> constraints = hypro::matrix_t<::benchmark::Number>::Zero( 2 * d, d );
		hypro::vector_t<::benchmark::Number> constants = hypro::vector_t<::benchmark::Number>::Ones( 2 * d );
		for ( std::size_t i = 0; i < d; ++i ) {
			constraints( 2 * i, i ) = 1;
			constraints( 2 * i + 1, i ) = -1;
		}
		hypro::SupportFunction<::benchmark::Number> sFunct( constraints, constants );
		hypro::SupportFunctionT<::benchmark::Number, hypro::Converter<::benchmark::Number>, hypro::NoTrafoReduction>
			  sFunctNoReduction( constraints, constants );

		// run instances asynchronous

		auto& mVector = matricesMap[d];
		auto& vVector = vectorsMap[d];
		auto& dVector = directionsMap[d];

		while ( workingQueue.size() > std::thread::hardware_concurrency() ) {
			auto res = workingQueue.front().get();

			// process
			ress.insert( ress.end(), res.begin(), res.end() );
			std::cout << "Finished dimension " << res.begin()->mDimension << std::endl;

			workingQueue.pop();
		}

		std::cout << "Launch tasks for dimension " << d << std::endl;

		workingQueue.emplace( std::async( std::launch::async, affineTrafoHelper<hypro::SupportFunctionSetting>, mVector,
										  vVector, dVector, d, "affineTransformationEval", settings, sFunct ) );
		workingQueue.emplace( std::async( std::launch::async, affineTrafoHelper<hypro::NoTrafoReduction>, mVector,
										  vVector, dVector, d, "affineTransformationEvalNoReduction", settings,
										  sFunctNoReduction ) );
	}

	while ( !workingQueue.empty() ) {
		auto res = workingQueue.front().get();

		// process
		ress.insert( ress.end(), res.begin(), res.end() );
		std::cout << "Finished dimension " << res.begin()->mDimension << std::endl;

		workingQueue.pop();
	}

	return ress;
}

}  // namespace sf
}  // namespace benchmark
