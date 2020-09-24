#include <carl/numbers/numbers.h>
#include <hypro/algorithms/quickhull/Quickhull.h>
#include <hypro/representations/GeometricObjectBase.h>

using namespace hypro;

using number_t = mpq_class;

int main() {
	std::vector<Point<number_t>> points;

	points.push_back( Point<number_t>{ 6, 0, 1 } );
	points.push_back( Point<number_t>{ 1, 12, 18 } );
	points.push_back( Point<number_t>{ 1, 0, 15 } );
	points.push_back( Point<number_t>{ 3, 14, 3 } );
	points.push_back( Point<number_t>{ 17, 4, 16 } );

	HPolytope<number_t> hpoly{ points };

	VPolytope<number_t> vpoly{ hpoly.matrix(), hpoly.vector() };

	TRACE( "quickhull", vpoly );
}