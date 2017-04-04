
#include "../src/hypro/representations/GeometricObject.h"

using namespace hypro;

int main(int argc, char** argv) {
	using Number = mpq_class;


	matrix_t<Number> matrix = matrix_t<Number>(4,3);
	vector_t<Number> distances = vector_t<Number>(4);
	matrix << 0,1,2,
		1,0,2,
		0,-1,-1,
		-1,0,-1;
	distances << 1,carl::rationalize<Number>(5),carl::rationalize<Number>(1),-4;


	vector_t<Number> shift = vector_t<Number>(3);
	shift << 1,1,1;
	matrix_t<Number> trafoMatrix = matrix_t<Number>(3,3);
	trafoMatrix << 1,0,0,0,1,0,0,0,1;

	matrix_t<Number> invariant = matrix_t<Number>(1,3);
	invariant << 1,0,0;
	vector_t<Number> invariantConst = vector_t<Number>(1);
	invariantConst << 100000;

	SupportFunction<Number> poly1(matrix, distances);
	SupportFunction<Number> ball(SF_TYPE::INFTY_BALL, carl::rationalize<Number>(.5), 2);
	SupportFunction<Number> rounded1 = poly1.minkowskiSum(ball);
	SupportFunction<Number> current = rounded1;

	// create large tree
	unsigned targetDepth = 1200;
	while (targetDepth > 0) {
		std::cout << current.depth() << ",";
		current = current.affineTransformation(trafoMatrix, shift);
		current = current.intersectHalfspaces(invariant,invariantConst);
		targetDepth -= 2;
	}

	std::cout << "Current depth: " << current.depth() << std::endl;

	//current.collectProjections();

}
