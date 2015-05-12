
#include "../src/lib/representations/SupportFunction/SupportFunction.h"
#include "../src/lib/util/plot.h"

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

	SupportFunction<double> rounded = poly2.minkowskiSum(ball);
	//SupportFunction<double> rounded = ball;

	// create array holding equaly distributed directions
	int resolution = 360;
	matrix_t<double> evaldirections = matrix_t<double>(resolution, 2);
	for(int pos = 0; pos < resolution; ++pos) {
		double angle = pos*(360/resolution);
		evaldirections(pos,0) = cos(angle*3.141592654/180);
		evaldirections(pos,1) = sin(angle*3.141592654/180);
		std::cout << "angle: " << angle <<  " -> " << evaldirections(pos,0) << ", " << evaldirections(pos,1) << std::endl;

	}

	std::cout << "evaldirections " << evaldirections << std::endl << std::endl;
	vector_t<double> result = rounded.multiEvaluate(evaldirections);
	std::cout << result << std::endl;

	// plotting 
	std::vector<Point<double>> points;
	for(int i = 0; i < resolution; ++i) {
		std::cout << "Calculate intersection between " << i << " and " << ((i-1+resolution)%resolution) << std::endl;
		matrix_t<double> matr = matrix_t<double>(2,2);
		matr.row(0) = evaldirections.row(i);
		matr.row(1) = evaldirections.row(((i-1+resolution)%resolution));
		vector_t<double> vec = vector_t<double>(2);
		vec(0) = result(i);
		vec(1) = result(((i-1+resolution)%resolution));
		Point<double> res = Point<double>(matr.colPivHouseholderQr().solve(vec));
		std::cout << "solve " << matr << " = " << vec << std::endl << " => " << res << std::endl << std::endl;
		points.push_back(res);
	}

	plot(points);
}