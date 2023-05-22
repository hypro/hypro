#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
#include "hypro/util/plotting/Plotter.h"

#include <iostream>
#include <stdlib.h>
// use floating point arithmetic.
typedef double Number;

// does Matrix multiplication with Erika's method
void columnMultiplication( std::vector<hypro::matrix_t<Number>> matrices, std::vector<hypro::matrix_t<Number>> mappingMatrices, int matrixDimension ) {
	for ( int i = 0; i < matrices.size(); i++ ) {
		for ( int j = 0; j < matrixDimension; j++ ) {
			for ( int k = 0; k < matrixDimension; k++ ) {
				matrices[i]( j, k ) = ( mappingMatrices[i].row( j ) * matrices[i].col( k ) ).value();
			}
		}
	}
}

// normal Matrix multiplication
void matrixMultiplication( std::vector<hypro::matrix_t<Number>> matrices, std::vector<hypro::matrix_t<Number>> mappingMatrices ) {
	for ( int i = 0; i < matrices.size(); i++ ) {
		matrices[i] = mappingMatrices[i] * matrices[i];
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

int main() {
	int matrixDimension = 2;
	std::vector<hypro::matrix_t<Number>> matrices;
	std::vector<hypro::matrix_t<Number>> mappingMatrices;

	std::vector<double> measurements = {};
	srand( time( 0 ) );
	for ( int k = 0; k < 10000; k++ ) {
		hypro::matrix_t<Number> matrix = hypro::matrix_t<Number>( matrixDimension, matrixDimension );
		for ( int i = 0; i <matrixDimension ; ++i ) {
			for ( int j = 0; j < matrixDimension; ++j ) {
				matrix( i, j ) = rand() % 1000;
			}
		}
		matrices.push_back( matrix );

		hypro::matrix_t<Number> mappingMatrix = hypro::matrix_t<Number>::Identity( matrixDimension, matrixDimension );
		for ( int i = 0; i < matrixDimension; i++ ) {
				mappingMatrix( i, i ) = rand() % 1000;
		}
		mappingMatrices.push_back( mappingMatrix );
	}


	auto t1 = std::chrono::high_resolution_clock::now();
	columnMultiplication( matrices, mappingMatrices,matrixDimension);
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms_double1 = t2 - t1;
	std::cout << "time of Erika's method: " << ms_double1.count() << std::endl;


	auto t3 = std::chrono::high_resolution_clock::now();
	matrixMultiplication( matrices, mappingMatrices );
	auto t4 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms_double2 = t4 - t3;
	std::cout << "time of matrix multiplication : " << ms_double2.count() << std::endl;

}