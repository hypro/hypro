
#include "types.h"

int main() {

	using Number = mpq_class;

	carl::Interval<Number> i;

	hypro::matrix_t<carl::Interval<Number>> intervalMatrix = hypro::matrix_t<carl::Interval<Number>>::Identity(2,2);

	std::cout << intervalMatrix << std::endl;

	hypro::matrix_t<carl::Interval<Number>> intervalMatrixExp = intervalMatrix.exp();

	std::cout << intervalMatrixExp << std::endl;

	return 0;
}
