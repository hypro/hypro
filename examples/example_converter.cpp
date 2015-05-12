
#include "../src/lib/representations/Converter.h"
#include "../src/lib/representations/SupportFunction/SupportFunction.h"

using namespace hypro;

int main(int argc, char** argv) {
	matrix_t<double> matrix = matrix_t<double>(4,2);
	vector_t<double> distances = vector_t<double>(4);
	matrix << 0,1,
		1,0,
		0,-1,
		-1,0;
	distances << 1,1,1,1;
	matrix_t<double> matrix2 = matrix_t<double>(3,2);
	vector_t<double> distances2 = vector_t<double>(3);
	matrix2 << 1,1,
		-1,1,
		0,-1,
	distances2 << 1,1,0;

	SupportFunction<double> poly1(SF_TYPE::POLY, matrix, distances);
	SupportFunction<double> poly2(SF_TYPE::POLY, matrix2, distances2);
	SupportFunction<double> ball(SF_TYPE::INFTY_BALL, .5);

	// SupportFunction<double> rounded = poly2.minkowskiSum(ball);
	SupportFunction<double> rounded = ball;

	Converter<hypro::Box<double>,SupportFunction<double> > converter;

	hypro::Box<double> res = converter.convert(poly2);

	std::cout << res << std::endl;

}