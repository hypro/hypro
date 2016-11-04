#include "../src/hypro/util/Plotter.h"
#include "../src/hypro/representations/GeometricObject.h"

using namespace hypro;

int main(int argc, char** argv) {
	matrix_t<double> matrix2 = matrix_t<double>(3,2);
	vector_t<double> distances2 = vector_t<double>(3);
	matrix2 << 1,1,
		-1,1,
		0,-1,
	distances2 << 1,1,0;

	SupportFunction<double> poly2 = SupportFunction<double>(matrix2, distances2);

	hypro::Box<double> res = Converter<double>::toBox(poly2);

	std::cout << res << std::endl;

	vector_t<double> p1 = vector_t<double>(2);
	p1(0) = 1;
	p1(1) = 2;
	vector_t<double> p2 = vector_t<double>(2);
	p2(0) = 3;
	p2(1) = 2;
	vector_t<double> p3 = vector_t<double>(2);
	p3(0) = 3;
	p3(1) = 4;
	vector_t<double> p4 = vector_t<double>(2);
	p4(0) = 1;
	p4(1) = 4;
	std::vector<hypro::Point<double>> points;
	points.emplace_back(p1);
	points.emplace_back(p2);
	points.emplace_back(p3);
	points.emplace_back(p4);

	VPolytope<double> poly1 = VPolytope<double>(points);
	res = Converter<double>::toBox(poly1);

	std::cout << res << std::endl;

	vector_t<double> center = vector_t<double>(2);
	center << 2.0, 2.0;

	matrix_t<double> generators = matrix_t<double>(2,2);
	generators << 0.0, 1.0, 1.0, -1.0;

	Zonotope<double> zono1 = Zonotope<double>(center, generators);

	res = Converter<double>::toBox(zono1);
}
