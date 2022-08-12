#include <hypro/representations/GeometricObjectBase.h>
#include <random>
#include <valgrind/callgrind.h>

using namespace hypro;

int main() {
	std::mt19937 generator;
	std::uniform_int_distribution<int> dist =
		  std::uniform_int_distribution<int>( 0, 10 );

	std::size_t dimension = 100;
	matrix_t<double> constraints =
		  matrix_t<double>::Zero( 2 * dimension, dimension );
	vector_t<double> constants = vector_t<double>::Ones( 2 * dimension );
	for ( std::size_t i = 0; i < dimension; ++i ) {
		constraints( 2 * i, i ) = 1;
		constraints( 2 * i + 1, i ) = -1;
	}

	// SupportFunctionT<double,Converter<double>,NoTrafoReduction> sf =
	// SupportFunctionT<double,Converter<double>,NoTrafoReduction>(constraints,
	// constants);
	SupportFunction<double> sf = SupportFunction<double>( constraints, constants );

	matrix_t<double> matrix = matrix_t<double>( dimension, dimension );
	vector_t<double> vector = vector_t<double>( dimension );
	vector_t<double> direction = vector_t<double>( dimension );
	for ( std::size_t row = 0; row < dimension; ++row ) {
		for ( std::size_t col = 0; col < dimension; ++col ) {
			matrix( row, col ) = dist( generator );
		}
		vector( row ) = dist( generator );
		direction( row ) = dist( generator );
	}

	CALLGRIND_START_INSTRUMENTATION;
	for ( std::size_t i = 0; i < 3142; ++i ) {
		sf = sf.affineTransformation( matrix, vector );
		// std::cout << i+1 << ": Depth: " << sf.depth() << std::endl;
	}
	auto tmp = sf.evaluate( direction );
	CALLGRIND_STOP_INSTRUMENTATION;

	return 0;
}
