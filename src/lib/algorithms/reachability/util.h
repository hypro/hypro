#pragma once

namespace hypro {
	namespace reachability {

		template<typename Representation>
		void printFlowpipe( const std::vector<Representation>& _flowpipe ) {
			for ( const auto& segment : _flowpipe ) {
				std::cout << segment << ", " << std::endl;
			}
		}

		template<typename Representation>
		void printFlowpipeReduced( const std::vector<Representation>& _flowpipe ) {
			std::cout << *_flowpipe.begin() << ", " << std::endl;
			std::cout << "(...)" << std::endl;
			std::cout << *_flowpipe.back() << std::endl;
		}

	} // namespace reachability

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
	matrix_t<Number> mat = hypro::matrix_t<Number>::Zero( 2 * _dim, _dim );
	vector_t<Number> vec( 2 * _dim, 1 );
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

} // namespace hypro
