#include "representations/GeometricObjectBase.h"
#include "util/Plotter.h"

#include <gmpxx.h>

int main() {
	using Number = double;
	// using Number = mpq_class;
	using namespace hypro;

	Plotter<Number>& plt = Plotter<Number>::getInstance();

	// assembly of the first poly
	std::vector<Halfspace<Number>> hspaces;
	vector_t<Number> normal1 = vector_t<Number>::Zero( 2 );
	normal1 << 1, -1;
	Halfspace<Number> hsp1( normal1, 0 );
	hspaces.emplace_back( hsp1 );

	vector_t<Number> normal2 = vector_t<Number>::Zero( 2 );
	normal2 << -2, 1;
	Halfspace<Number> hsp2( normal2, 0 );
	hspaces.emplace_back( hsp2 );

	vector_t<Number> normal3 = vector_t<Number>::Zero( 2 );
	normal3 << 0, 1;
	Halfspace<Number> hsp3( normal1, 5 );
	hspaces.emplace_back( hsp3 );

	HPolytope<Number> hpoly1( hspaces );

	// alternative construction
	matrix_t<Number> mat = matrix_t<Number>( 3, 2 );
	vector_t<Number> vec = vector_t<Number>( 3 );

	mat << 1, -1, -2, 1, 0, 1;
	vec << 0, 0, 5;

	HPolytope<Number> hpoly2( mat, vec );

	// plt.addObject(hpoly1.vertices());
	plt.addObject( hpoly2.vertices() );

	// halfspace intersection
	matrix_t<Number> hspMat = matrix_t<Number>( 2, 2 );
	vector_t<Number> hspVec = vector_t<Number>( 2 );
	hspMat << 0, 1, 0, -1;
	hspVec << 3, -3;

	std::pair<bool, HPolytope<Number>> intersectionPair =
		  hpoly1.satisfiesHalfspaces( hspMat, hspVec );

	std::cout << "Intersection not empty: " << intersectionPair.first
			  << std::endl;
	std::cout << "Result after intersection: " << intersectionPair.second
			  << std::endl;

	unsigned intersectionId = plt.addObject( intersectionPair.second.vertices() );
	plt.setObjectColor( intersectionId, plotting::colors[plotting::red] );

	// projection to s-axis
	std::vector<unsigned> projectionVector;
	projectionVector.push_back( 0 );

	HPolytope<Number> projected =
		  intersectionPair.second.projectOn( projectionVector );

	std::cout << "Projection result: " << projected << std::endl;

	plt.plot2d();

	return 0;
}