#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
#include "hypro/util/plotting/Plotter.h"

#include <iostream>
#include <stdlib.h>
// use floating point arithmetic.
typedef double Number;

// does Matrix multiplication with Erika's method
void columnMultiplication( std::vector<hypro::matrix_t<Number>> matrices, std::vector<hypro::matrix_t<Number>> mappingMatrices ) {
	for ( int i = 0; i < matrices.size(); i++ ) {
		for ( int j = 0; j < 2; j++ ) {
			for ( int k = 0; k < 2; k++ ) {
				matrices[i]( j, k ) = ( mappingMatrices[i].row( j ) * matrices[i].col( k ) ).value();
			}
		}
		std::cout << "matrix after cal 1:  " << matrices[i] << std::endl;
	}
}

// normal Matrix multiplication
void matrixMultiplication( std::vector<hypro::matrix_t<Number>> matrices, std::vector<hypro::matrix_t<Number>> mappingMatrices ) {
	for ( int i = 0; i < matrices.size(); i++ ) {
		matrices[i] = mappingMatrices[i] * matrices[i];
		std::cout << "matrix after cal 2:  " << matrices[i] << std::endl;
	}
}

// does Matrix multiplication with Erika's method
/*void columnMultiplication( std::vector<hypro::matrix_t<Number>> matrices, float alpha ) {
	for ( auto& matrix : matrices ) {
		for ( int i = 0; i < 2; ++i ) {
			hypro::matrix_t<Number> mappingColumn = hypro::matrix_t<Number>::Zero( 1, 2 );
			mappingColumn( i ) = alpha;

			for ( int j = 0; j < 2; j++ ) {
				matrix( i, j ) = ( mappingColumn * matrix.col( j ) ).value();
			}
		}
	}
} */

// normal Matrix multiplication
/*void matrixMultiplication( std::vector<hypro::matrix_t<Number>> matrices, float alpha ) {
	for ( auto& matrix : matrices ) {
		for ( int i = 0; i < 2; ++i ) {
			hypro::matrix_t<Number> mappingMatrix = hypro::matrix_t<Number>::Identity( 2, 2 );
			mappingMatrix( i, i ) = alpha;

			matrix = mappingMatrix * matrix;
		}
	}
} */

// in advance generate 10000 matrices and 10000 mapping matrices / vectors
std::vector<hypro::matrix_t<Number>> matrices;
std::vector<hypro::matrix_t<Number>> mappingMatrices;

int main() {
	std::vector<double> measurements = {};
	srand( time( 0 ) );
	for ( int k = 0; k < 2; k++ ) {
		hypro::matrix_t<Number> matrix = hypro::matrix_t<Number>( 2, 2 );
		for ( int i = 0; i < 2; ++i ) {
			for ( int j = 0; j < 2; ++j ) {
				matrix( i, j ) = rand() % 10;
			}
		}
		matrices.push_back( matrix );

		std::cout << "matrix:  " << matrix << std::endl;

		hypro::matrix_t<Number> mappingMatrix = hypro::matrix_t<Number>::Identity( 2, 2 );
		for ( int i = 0; i < 2; ++i ) {
				mappingMatrix( i, i ) = rand() % 10;
		}
		mappingMatrices.push_back( mappingMatrix );
		std::cout << "mappingmatrix:  " << mappingMatrix << std::endl;
	}



	auto t1 = std::chrono::high_resolution_clock::now();

	columnMultiplication( matrices, mappingMatrices );

	auto t2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> ms_double1 = t2 - t1;

	std::cout << "time of multiplication only columns: " << ms_double1.count() << std::endl;

	auto t3 = std::chrono::high_resolution_clock::now();

	matrixMultiplication( matrices, mappingMatrices );

	auto t4 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> ms_double2 = t4 - t3;

	std::cout << "time of matrix multiplication : " << ms_double2.count() << std::endl;
	/*	std::cout << "Total time: " << ms_double << std::endl;
		measurements.push_back( ms_double.count() );

		auto const count = static_cast<float>( measurements.size() );
		auto mean = std::reduce( measurements.begin(), measurements.end() ) / count;

		std::cout << mean << std::endl; */
}