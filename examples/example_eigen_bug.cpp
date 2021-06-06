#include "types.h"
#include "util/linearOptimization/EvaluationResult.h"

using namespace hypro;

int main() {
	vector_t<mpq_class> vec = vector_t<mpq_class>::Zero( 2 );
	vec << 0, 1;

	{
		EvaluationResult<mpq_class> res = EvaluationResult<mpq_class>( vec, SOLUTION::INFEAS );
	}

	std::cout << "After deletion." << std::endl;

	return 0;
}