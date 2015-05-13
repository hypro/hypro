
#include "../src/lib/representations/Converter.h"

using namespace hypro;

int main(int argc, char** argv) {
	matrix_t<double> matrix2 = matrix_t<double>(3,2);
	vector_t<double> distances2 = vector_t<double>(3);
	matrix2 << 1,1,
		-1,1,
		0,-1,
	distances2 << 1,1,0;

	SupportFunction<double> poly2(SF_TYPE::POLY, matrix2, distances2);
	
	hypro::Box<double> res = convert(poly2);

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
	VPolytope<double>::vertexSet points;
	points.insert(p1);
	points.insert(p2);
	points.insert(p3);
	points.insert(p4);

	VPolytope<double> poly1 = VPolytope<double>(points);
	res = convert(poly1);

	std::cout << res << std::endl;

	vector_t<double> center = vector_t<double>(2);
	center << 2.0, 2.0;

	matrix_t<double> generators = matrix_t<double>(2,2);
	generators << 0.0, 1.0, 1.0, -1.0;

	Zonotope<double> zono1 = Zonotope<double>(center, generators);

	res = convert(zono1);

	std::cout << res << std::endl;

	std::vector<vector_t<double>> coordinates;
	coordinates.push_back(p1);
	coordinates.push_back(p2);
	coordinates.push_back(p3);
	coordinates.push_back(p4);

	hypro::Polytope<double> poly3(coordinates);

	res = convert(poly3);

	std::cout << res << std::endl;	
}