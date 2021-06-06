#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>
#include <iostream>
#include <vector>

using namespace hypro;

int main() {
	using Point = Point<double>;
	using Matrix = matrix_t<double>;
	using Vector = vector_t<double>;

	std::vector<Point> points;
	points.emplace_back( Point{ 1, 2 } );
	points.emplace_back( Point{ 3, 1 } );
	points.emplace_back( Point{ 4, 3 } );
	points.emplace_back( Point{ 1.5, 4 } );

	auto& plt = Plotter<double>::getInstance();
	plt.setFilename( "polytope" );

	auto hpoly = HPolytope<double>( points );

	for ( const auto& hspace : hpoly.constraints() ) {
		std::cout << hspace << std::endl;
	}

	auto obj = plt.addObject( points );
	plt.plotTex();

	return 0;
}
