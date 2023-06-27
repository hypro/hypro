//
// Created by kai on 13.06.23.
//

#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/algorithms/reachability/analyzer/UnderApproximativeReachabilityAnalyzer.h>
#include <hypro/types.h>

TEST(UnderApproximativeReachabilityAnalyzer, testRateBox) {
	using namespace hypro;
	UnderApproximativeReachabilityAnalyzer<mpq_class> subject = UnderApproximativeReachabilityAnalyzer<mpq_class>();
	vector_t<carl::Interval<mpq_class>> rates = vector_t<carl::Interval<mpq_class>>(2);
	rates << (carl::Interval<mpq_class>(1,2)), carl::Interval<mpq_class >(-2,2);

	auto [result_factors, result_b] = subject.generate_rate_box(rates);
	matrix_t<mpq_class> expected_factors = matrix_t<mpq_class>(4,2);
	expected_factors << -1,0,1,0,0,-1,0,1;
	vector_t<mpq_class> expected_b = vector_t<mpq_class>(4);
	expected_b << -1,2,2,2;
	ASSERT_EQ(expected_factors, result_factors);
	ASSERT_EQ(expected_b, result_b);
	SUCCEED();
}



TEST( UnderApproximativeReachabilityAnalyzer, testSimple ) {
	using namespace hypro;
	UnderApproximativeReachabilityAnalyzer<mpq_class> subject = UnderApproximativeReachabilityAnalyzer<mpq_class>();

	// Ax <= b
	matrix_t<mpq_class> a = matrix_t<mpq_class>::Zero( 2, 2 );
	vector_t<mpq_class> b = vector_t<mpq_class>::Zero(2);

	a << 2,-1,-3,1;
	b << 2,-3;


	vector_t<carl::Interval<mpq_class>> rates = vector_t<carl::Interval<mpq_class>>(2);
	rates << carl::Interval<mpq_class>(1,2), carl::Interval<mpq_class>(-2,2);

	matrix_t<mpq_class> expectedFactors = matrix_t<mpq_class>(2,2);
	expectedFactors << 2 , -1 , mpq_class(-2,5), mpq_class(-1,5);

	vector_t<mpq_class> expected_b = vector_t<mpq_class>(2);
	expected_b << -2, mpq_class(2,5);

    auto [result_a, result_b] = subject.solve(a,b, rates);
	ASSERT_TRUE(result_a.isApprox(expectedFactors));
	ASSERT_TRUE(result_b.isApprox(expected_b));
	SUCCEED();
}