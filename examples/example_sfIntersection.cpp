#include "../src/hypro/representations/GeometricObject.h"
#include "../src/hypro/util/Plotter.h"

using namespace hypro;
using Number = double;
using Matrix = matrix_t<Number>;
using Vector = vector_t<Number>;

Number sandwichValue(const SupportFunction<Number>& obj, Vector a, Number b, Vector direction, Number lambda) {
	return obj.evaluate(direction - lambda*a).supportValue + lambda*b;
}

Number lowerBound(const SupportFunction<Number>& obj, Vector a, Number b, Vector direction, Number lambdaI, Number lambdaJ, Number lambda) {
	return ((sandwichValue(obj,a,b,direction,lambdaJ) - sandwichValue(obj,a,b,direction,lambdaI)) / (lambdaJ - lambdaI)) * (lambda - lambdaI) + sandwichValue(obj,a,b,direction,lambdaI);
}

void determineLowerBound(const SupportFunction<Number>& obj, Vector a, Number b, Vector direction) {
	int i = 0;
	Number rLow = -std::numeric_limits::infinity();
	Number rUp = std::numeric_limits::infinity();
	std::vector<Number> lambdas;
	lambas.push_back(0);
	lambas.push_back(1);

	while(true) {
		if(sandwichValue(obj,a,b,direction,lambdas.back()) <= sandwichValue(obj,a,b,direction,*(lambdas.end()-2)))

		lambdas.push_back(2*lambdas.back());
	}
}

int main() {

	Plotter<Number>& plt = Plotter<Number>::getInstance();

	Matrix constraints = Matrix(3,2);
	Vector constants = Vector(3);

	constraints << 1,1,-1,1,0,-1;
	constants << 2,2,1;

	SupportFunction<Number> sf = SupportFunction<Number>(constraints,constants);

	Matrix hsNormal = Matrix(1,2);
	Vector hsOffset = Vector(1);

	hsNormal << 1,0.5;
	hsOffset << 1.5;

	sf.intersectHalfspaces(hsNormal,hsOffset);

	plt.addObject(sf.vertices());
	plt.addObject(Halfspace<Number>(Vector(hsNormal.row(0)),hsOffset(0)));

	plt.plot2d();

	return 0;
}
