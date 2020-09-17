#include "gtest/gtest.h"
#include <hypro/util/linearOptimization/Optimizer.h>
#include <iostream>

using namespace hypro;

TEST( OptimizerTest, EvaluationResult ) {
	EvaluationResult<double> evRes1;
	EXPECT_EQ( 0, evRes1.supportValue );
	EXPECT_EQ( SOLUTION::INFEAS, evRes1.errorCode );
	EXPECT_EQ( vector_t<double>::Zero( 0 ), evRes1.optimumValue );

	EvaluationResult<double> evRes2( SOLUTION::FEAS );
	EXPECT_EQ( 0, evRes2.supportValue );
	EXPECT_EQ( SOLUTION::FEAS, evRes2.errorCode );
	EXPECT_EQ( vector_t<double>::Zero( 0 ), evRes2.optimumValue );

	EvaluationResult<double> evRes3( 3.0, SOLUTION::FEAS );
	EXPECT_EQ( 3.0, evRes3.supportValue );
	EXPECT_EQ( SOLUTION::FEAS, evRes3.errorCode );
	EXPECT_EQ( vector_t<double>::Zero( 0 ), evRes3.optimumValue );

	vector_t<double> sol = vector_t<double>::Zero( 2 );
	sol << 3, 0;
	EvaluationResult<double> evRes4( sol, SOLUTION::FEAS );
	EXPECT_EQ( 0, evRes4.supportValue );
	EXPECT_EQ( SOLUTION::FEAS, evRes4.errorCode );
	EXPECT_EQ( sol, evRes4.optimumValue );
}

TEST( OptimizerTest, Minimize ) {
	// Constraints as box around center with corners (2,2)(2,-2)(-2,2)(-2,-2)
	matrix_t<double> boxMat = matrix_t<double>::Zero( 4, 2 );
	boxMat << 1, 0, -1, 0, 0, 1, 0, -1;
	vector_t<double> boxVec = vector_t<double>::Zero( 4 );
	boxVec << 2, 2, 2, 2;
	Optimizer<double> op( boxMat, boxVec, false );
	auto res = op.evaluate( vector_t<double>::Ones( 2 ), false );
	auto controlVec = -2.0 * vector_t<double>::Ones( 2 );
	EXPECT_EQ( -4.0, res.supportValue );
	EXPECT_EQ( SOLUTION::FEAS, res.errorCode );
	EXPECT_EQ( controlVec, res.optimumValue );
}