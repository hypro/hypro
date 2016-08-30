#include "../src/lib/util/linearOptimization/Optimizer.h"

int main() {

	using namespace hypro;
	using Number = mpq_class;

	matrix_t<Number> a = matrix_t<Number>(6,2);
	a << 1,0,0,1,-1,0,0,-1,1,0,1,0;
	vector_t<Number> b = vector_t<Number>(6);
	b << 1,1,1,1,2,1;

	Optimizer<Number> opt;
	opt.setMatrix(a);
	opt.setVector(b);

	std::vector<std::size_t> redundant = opt.redundantConstraints();
	for(const auto& index : redundant) {
		std::cout << "Redundant constraint no. " << index << std::endl;
	}
}
