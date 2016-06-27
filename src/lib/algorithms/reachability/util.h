
#pragma once

#include "../../representations/Box/Box.h"
#include "../../representations/SupportFunction/SupportFunctionContent.h"
#include "carl/core/VariablePool.h"

namespace hypro {

/*
 * Functionality for the reachability computation
 */

template <typename Number>
Number hausdorffError( const Number& delta, const matrix_t<Number>& matrix, const Number& _supremum ) {
	Number result;
	// calculate matrix infinity norm
	Number norm = inftyNorm(matrix);

	// Number tmp = delta * t;
	Number tmp = delta * norm;

	double tmpExp = std::exp(carl::toDouble(tmp));
	result = carl::rationalize<Number>(tmpExp);

	//tmp.exp( result );
	result = result - 1 - tmp;
	result *= _supremum;
	return result;
}

/**
 * based on the Hausdorff distance, constructs the box (also a polytope) that is used for bloating the initial
 * approximation
 */
template <typename Number, typename Representation>
Representation computePolytope( unsigned int _dim, Number _radius ) {
	hypro::matrix_t<Number> mat = hypro::matrix_t<Number>::Zero( 2 * _dim, _dim );
	hypro::vector_t<Number> vec( 2 * _dim, 1 );
	int i = 0;
	for ( unsigned z = 0; z < _dim; ++z ) {
		vec( i ) = _radius;
		vec( i + 1 ) = _radius;

		mat( i, z ) = 1;
		mat( i + 1, z ) = -1;

		i = i + 2;
	}
	Representation poly = Representation( mat, vec );
	return poly;
}

	/*
	template<typename Number, typename Representation>
	Representation computeFirstSegmentCLG(const matrix_t<Number>& A, const Representation& initialSet, const Number& delta){
		// matrix precomputations
		unsigned dimension = initialSet.dimension()+1;
		assert(A.rows() == dimension && A.cols()==dimension );
		matrix_t<Number> errormatrix = matrix_t<Number>::Zero(3*dimension, 3*dimension);
		std::cout << "Dimension: " << dimension << std::endl;
		std::cout << "A " << std::endl << A << "ABS(a)" << std::endl << abs(A) << std::endl;

		errormatrix.block(0,0,dimension,dimension) = abs(A);
		errormatrix.block(0, dimension, dimension, dimension) = matrix_t<Number>::Identity(dimension, dimension);
		errormatrix.block(dimension, 2*dimension, dimension, dimension) = matrix_t<Number>::Identity(dimension, dimension);

		std::cout << "Errormatrix before exponential: " << std::endl << errormatrix << std::endl;
		matrix_t<double> doubleErrorMatrix = 0.5*convert<Number,double>(errormatrix);
		doubleErrorMatrix = doubleErrorMatrix.exp();
		std::cout << "Errormatrix exponential: " << std::endl << doubleErrorMatrix << std::endl;

		matrix_t<Number> exponential = convert<double,Number>(matrix_t<double>(doubleErrorMatrix.block(0,0,dimension,dimension)));
		matrix_t<Number> firstErrorFactor = convert<double,Number>(matrix_t<double>(doubleErrorMatrix.block(0,dimension,dimension,dimension)));
		matrix_t<Number> secondErrorFactor = convert<double,Number>(matrix_t<double>(doubleErrorMatrix.block(0,2*dimension,dimension,dimension)));

		std::cout << "exponential " << exponential << std::endl;

		matrix_t<Number> tmp = matrix_t<Number>(A*(matrix_t<Number>::Identity(dimension,dimension) - exponential));
		std::cout << "linear trafo matrix: " << tmp << std::endl;

		std::cout << "initial set: " << initialSet << std::endl;
		Representation transformed = initialSet.linearTransformation(tmp, vector_t<Number>::Zero(dimension));

		std::cout << "transformed initial set: " << transformed << std::endl;

		std::cout << "Set without box around: " << initialSet.linearTransformation(A*(matrix_t<Number>::Identity(dimension,dimension) - exponential), vector_t<Number>::Zero(dimension)) << std::endl;

		Box<Number> errorapprox = Converter<Number>::toBox(initialSet.linearTransformation(A*(matrix_t<Number>::Identity(dimension,dimension) - exponential), vector_t<Number>::Zero(dimension)));
		errorapprox.makeSymmetric();

		std::cout << "Errorapprox box " << errorapprox << std::endl;

		errorapprox = errorapprox.linearTransformation(firstErrorFactor, vector_t<Number>::Zero(dimension));

		/*
		Box<Number> error;
		Box<Number> x0Error;



		Box<Number> scaledError = (Number(1)/Number(4)) * error;
		Representation bloatedFirstSet = (firstSet.minkowskiSum(scaledExternalInput)).minkowskiSum(externalInputError);
		return (initialSet.unite(bloatedFirstSet)).minkowskiSum(scaledError);

	}
	*/
}
