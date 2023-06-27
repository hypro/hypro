//
// Created by kai on 13.06.23.
//

#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/util/linearFractionalProgramming/charnesCooperTransformation.h>
#include <hypro/types.h>

TEST(CharnesCooperTransormation, testSimpleCase) {
	using namespace hypro;

	vector_t<mpq_class> numerator = vector_t<mpq_class>(2 );
	numerator << 2,-1;
	vector_t<mpq_class> denominator = vector_t<mpq_class>(2);
	denominator << 3,-1;
	matrix_t<mpq_class> constraints = matrix_t<mpq_class>(6,2);

	constraints << -1,0,1,0,0,-1,0,1,-2,1,-3,1;
	vector_t<mpq_class> constraints_b = vector_t<mpq_class>(6);
	constraints_b <<-1,2,2,2,0,0;


	auto [found, res] = charnesCooperTransformation<mpq_class>(numerator,0,denominator,0,constraints,constraints_b);

	res.dot(- numerator)/ res.dot(denominator);
	ASSERT_TRUE(res.dot(- numerator)/ res.dot(denominator) ==  mpq_class(-4,5));
	SUCCEED();
}