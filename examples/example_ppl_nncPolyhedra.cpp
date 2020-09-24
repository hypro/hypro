/**
 * Example which shows how to use PPL NNC polyhedra
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @file example_ppl_nncPolyhedra.cpp
 *
 * @since       2014-03-25
 * @version     2014-03-25
 */

#include <hypro/representations/GeometricObjectBase.h>
#include <iostream>

#ifdef HYPRO_USE_PPL

using namespace Parma_Polyhedra_Library;
using namespace hypro;

int main( int argc, char** argv ) {
	using Number = double;

	matrix_t<Number> A = matrix_t<Number>( 4, 2 );
	A << 1, 0, -1, 0, 0, 1, 0, -1;
	vector_t<Number> b = vector_t<Number>( 4 );
	b << 1, 1, 0, 0;

	Polytope<Number> aPoly( A, b );

	std::cout << aPoly << std::endl;
	std::cout << aPoly.rawPolyhedron().generators() << std::endl;

	std::cout << "Linear transformation." << std::endl;

	matrix_t<Number> trafo = matrix_t<Number>( 2, 2 );
	trafo << 2.5, 0, 0, 2.5;
	vector_t<Number> translation = vector_t<Number>( 2 );
	translation << 1, 2;

	aPoly = aPoly.affineTransformation( trafo, translation );

	std::cout << "Result: " << std::endl;
	std::cout << aPoly << std::endl;
	std::cout << aPoly.rawPolyhedron().generators() << std::endl;
}

#else

int main( int argc, char** argv ) {
	std::cout << "This example only works if the PPL-wrapper of hypro is enabled."
			  << std::endl;
	return 0;
}

#endif
