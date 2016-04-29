
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
	// the last variable is always a placeholder for a constant translation factor
	// no bloating in that dimension
	// unsigned int correctedDim = _dim;

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
	// mat(2*_dim-2,_dim-1) = 1;
	// mat(2*_dim-1,_dim-1) = 1;
	// mat(2*_dim-1,_dim-1) = -1; -> this does not work, as the dimension of the result is too low.
	// vec(2*_dim-2) = 0;
	// vec(2*_dim-1) = 0;

	// std::cout << "Hausdorff matrix: " << mat << ", Hausdorff vector " << vec << std::endl;

	Representation poly = Representation( mat, vec );
	return poly;
}

/*
template<typename Number>
SupportFunctionContent<Number> computePolytope(unsigned int _dim, Number _radius) {
	return SupportFunctionContent<Number>(SF_TYPE::INFTY_BALL, _radius );
}
*/
}
