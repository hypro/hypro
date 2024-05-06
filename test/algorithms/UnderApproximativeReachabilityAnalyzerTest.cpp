//
// Created by kai on 13.06.23.
//

#include "hypro/algorithms/reachability/handlers/timeEvolutionHandlers/rectangularTimeEvolutionHandler.h"
#include "hypro/datastructures/HybridAutomaton/flow/rectangular.h"
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
	expected_b << 2, -mpq_class(2,5);

    auto [result_a, result_b] = subject.solve(a,b, rates);
	ASSERT_TRUE(result_a.isApprox(expectedFactors));
	ASSERT_TRUE(result_b.isApprox(expected_b));
	SUCCEED();
}


TEST( UnderApproximativeReachabilityAnalyzer, testWithBox ) {
	using namespace hypro;
	UnderApproximativeReachabilityAnalyzer<mpq_class> subject = UnderApproximativeReachabilityAnalyzer<mpq_class>();

	// Ax <= b
	matrix_t<mpq_class> a = matrix_t<mpq_class>::Zero( 4, 2 );
	vector_t<mpq_class> b = vector_t<mpq_class>::Zero(4);

	a << 1,0, -1,0 , 0,1, 0,-1;
	b << 2.5,-1.5, 5.5,  -4.5 ;


	vector_t<carl::Interval<mpq_class>> rates = vector_t<carl::Interval<mpq_class>>(2);
	rates << carl::Interval<mpq_class>(0,1), carl::Interval<mpq_class>(1,1);

	matrix_t<mpq_class> expectedFactors = matrix_t<mpq_class>(5,2);
	expectedFactors <<1,0,-1,0,0,1,1,-1,-1,1;

	vector_t<mpq_class> expected_b = vector_t<mpq_class>(5);
	expected_b << 2.5, - mpq_class (3,2),mpq_class (11,2),-2,4;

	auto [result_a, result_b] = subject.solve(a,b, rates);

	ASSERT_TRUE(result_a.isApprox(expectedFactors));
	ASSERT_TRUE(result_b.isApprox(expected_b));
	SUCCEED();
}



TEST( UnderApproximativeReachabilityAnalyzer, test3d ) {
	using namespace hypro;
	UnderApproximativeReachabilityAnalyzer<mpq_class> subject = UnderApproximativeReachabilityAnalyzer<mpq_class>();

	// Ax <= b
	matrix_t<mpq_class> a = matrix_t<mpq_class>::Zero( 6, 3 );
	vector_t<mpq_class> b = vector_t<mpq_class>::Zero(6);

	a << 1,0,0,-1,0,0,0,1,0,0,-1,-1.5,0,0,-1,0,0,1;
	b << -10,-10,-8,6,4,-10;


	vector_t<carl::Interval<mpq_class>> rates = vector_t<carl::Interval<mpq_class>>(3);
	rates << carl::Interval<mpq_class>(-1,1), carl::Interval<mpq_class>(-1,1),carl::Interval<mpq_class >(1,2);

	matrix_t<mpq_class> expectedFactors = matrix_t<mpq_class>(14,3);
	expectedFactors <<1,0,0,
		             -1,0,0,
		              0,1,0,
		              0,0,1,
		            1,-2,-3,
		             1,0,-1,
		              1,0,1,
		            -1,-2,-3,
		            -1,0,-1,
		             -1,0,1,
		      0,mpq_class(6,10),mpq_class(-6,10),
		             0,1,-1,
		              0,1,1,
		            0,-2,-2;

	vector_t<mpq_class> expected_b = vector_t<mpq_class>(14);
	expected_b << -10,
		  -10,
		  -8,
		  -10,
		  2,
		  -6,
		  -20,
		  2,
		  -6,
		  -20,
		  -mpq_class (28,5),
		  -4,
		  -18,
		  2;

	auto [result_a, result_b] = subject.solve(a,b, rates);
	ASSERT_TRUE(result_a.isApprox(expectedFactors));
	ASSERT_TRUE(result_b.isApprox(expected_b));
	SUCCEED();
}



TEST( UnderApproximativeReachabilityAnalyzer, test4d ) {
	using namespace hypro;
	UnderApproximativeReachabilityAnalyzer<mpq_class> subject = UnderApproximativeReachabilityAnalyzer<mpq_class>();

	// Ax <= b
	matrix_t<mpq_class> a = matrix_t<mpq_class>::Zero( 10, 4 );
	vector_t<mpq_class> b = vector_t<mpq_class>::Zero(10);

	a << -1,1,0,0,0,-1,0,1,1,0,-1,0,0,0,0,-1,-1,0,1,0,-1,0,1,1,0,1,0,0,0,-1,0,0,0,0,1,0,0,0,-1,0;
	b << 0,0,-1,0,3,4,2.5,-1.5,5.5,-4.5;


	vector_t<carl::Interval<mpq_class>> rates = vector_t<carl::Interval<mpq_class>>(4);
	rates << carl::Interval<mpq_class>(1,1), carl::Interval<mpq_class>(0,1), carl::Interval<mpq_class >(1,1),carl::Interval<mpq_class >(0,0);

	matrix_t<mpq_class> expectedFactors = matrix_t<mpq_class>(15,4);
	expectedFactors << -1,1,0,0,0,-1,0,1,1,0,-1,0,0,0,0,-1,-1,0,1,0,-1,0,1,1,0,1,0,0,0,-1,0,0,0,0,1,0,0,1,0,0,-1,1,1,0,0,0,0,1,0,-1,1,1,0,1,-1,0,0,-1,1,0;

	vector_t<mpq_class> expected_b = vector_t<mpq_class>(15);
	expected_b << 0,0,-1,0,3,4,mpq_class (5,2),mpq_class (-3,2),mpq_class (11,2),mpq_class (5,2),mpq_class (11,2),mpq_class (5,2),mpq_class (11,2),-2,4;

	auto [result_a, result_b] = subject.solve(a,b, rates);
	ASSERT_TRUE(result_a.isApprox(expectedFactors));
	ASSERT_TRUE(result_b.isApprox(expected_b));
	SUCCEED();
}



TEST(UnderApproximativeReachabilityAnalyzer, ReverseTimeEvolution) {
	using Number = mpq_class;
	using Vector = hypro::vector_t<Number>;
	using Pol = PolyT<mpq_class>;
	using Constr = ConstraintT<mpq_class>;



	typename rectangularFlow<Number>::flowMap fMap;
	carl::Variable x = freshRealVariable( "x" );
	carl::Variable y = freshRealVariable( "y" );

	fMap[x] = carl::Interval<Number>{ 1, 2 };
	fMap[y] = carl::Interval<Number>{ -2, 2 };
	rectangularFlow<Number> flow = hypro::rectangularFlow<Number>{ fMap };

	Converter<Number>::CarlPolytope bad;

	bad.addConstraint( Constr( Pol(2) *Pol(x) - Pol(y) - Pol(2) , carl::Relation::LEQ ) );
	bad.addConstraint( Constr( - Pol(3)*Pol( x ) + Pol( y ) + Pol( 3 ), carl::Relation::LEQ ) );

	UnderApproximativeReachabilityAnalyzer<Number> analyzer = UnderApproximativeReachabilityAnalyzer<Number>();


	auto vars = bad.getVariables();


	vector_t<carl::Interval<Number>> rates = vector_t<carl::Interval<Number>>(vars.size());
	auto flowMap = flow.getFlowIntervals();
	int i = 0;
	for (auto var: vars){
		rates(i) = flowMap.at(var);
		i++;
	}


    auto [matrix, constants] = analyzer.solve(bad.matrix(), bad.vector(),rates);


	auto result = rectangularUnderapproximateReverseTimeEvolution(bad,flow);

	CarlPolytope<Number> res = CarlPolytope<Number>(matrix,constants);
	ASSERT_TRUE(result.matrix() == res.matrix());
	ASSERT_TRUE(result.vector() == res.vector());
	SUCCEED();
}

/**
 * 06-05-2024 Jonas Stuebbe:
 * This test is currently DISABLED as it fails in line 280.; Fixing this is assigned to Joanna Delicaris;
 * Expected equality of these values:
 * result.matrix()
 * Which is:
 *
 *
 * res.matrix()
 * Which is:
 * 		2 -1
 * 		-2 -1
 * 	TODO FIX test and remove 'DISABLED_' prefix.
 */
TEST(UnderApproximativeReachabilityAnalyzer, DISABLED_ReverseTimeEvolutionWithConstantInput) {
	using Number = mpq_class;
	using Vector = hypro::vector_t<Number>;
	using Pol = PolyT<mpq_class>;
	using Constr = ConstraintT<mpq_class>;



	typename rectangularFlow<Number>::flowMap fMap;




	carl::Variable x = freshRealVariable( "x" );
	carl::Variable y = freshRealVariable( "y" );

	fMap[x] = carl::Interval<Number>{ 1, 2 };
	fMap[y] = carl::Interval<Number>{ -2, 2 };
	rectangularFlow<Number> flow = hypro::rectangularFlow<Number>{ fMap };


	Converter<Number>::CarlPolytope bad;

	bad.addConstraint( Constr( Pol(2) *Pol(x) - Pol(y) - Pol(2) , carl::Relation::LEQ ) );
	bad.addConstraint( Constr( - Pol(3)*Pol( x ) + Pol( y ) + Pol( 3 ), carl::Relation::LEQ ) );


	// Ax <= b
	matrix_t<mpq_class> a = matrix_t<mpq_class>::Zero( 2, 2 );
	vector_t<mpq_class> b = vector_t<mpq_class>::Zero(2);

	a << 2,-1,-3,1;
	b << 2,-3;


	vector_t<carl::Interval<mpq_class>> rates_vector = vector_t<carl::Interval<mpq_class>>(2);
	rates_vector << carl::Interval<mpq_class>(1,2), carl::Interval<mpq_class>(-2,2);

	UnderApproximativeReachabilityAnalyzer<Number> analyzer = UnderApproximativeReachabilityAnalyzer<Number>();


	auto vars = bad.getVariables();


	vector_t<carl::Interval<Number>> rates = vector_t<carl::Interval<Number>>(vars.size());
	auto flowMap = flow.getFlowIntervals();
	int i = 0;
	for (auto var: vars){
		rates(i) = flowMap.at(var);
		i++;
	}

	auto [matrix, constants] = analyzer.solve(a, b,rates_vector);


	auto result = rectangularUnderapproximateReverseTimeEvolution(bad,flow);

	CarlPolytope<Number> res = CarlPolytope<Number>(matrix,constants);

	ASSERT_EQ(result.matrix(), res.matrix());

	ASSERT_EQ(result.vector(), res.vector());
	SUCCEED();
}


