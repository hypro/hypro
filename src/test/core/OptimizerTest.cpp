#include "gtest/gtest.h"
#include "util/linearOptimization/Optimizer.h"
#include <iostream>

using namespace hypro;

TEST(OptimizerTest, EvaluationResult) {
	EvaluationResult<double> evRes1;
	EXPECT_EQ(0, evRes1.supportValue);
	EXPECT_EQ(SOLUTION::INFEAS, evRes1.errorCode);
	EXPECT_EQ(vector_t<double>::Zero(0), evRes1.optimumValue);

	EvaluationResult<double> evRes2(SOLUTION::FEAS);
	EXPECT_EQ(0, evRes2.supportValue);
	EXPECT_EQ(SOLUTION::FEAS, evRes2.errorCode);
	EXPECT_EQ(vector_t<double>::Zero(0), evRes2.optimumValue);

	EvaluationResult<double> evRes3(3.0, SOLUTION::FEAS);
	EXPECT_EQ(3.0, evRes3.supportValue);
	EXPECT_EQ(SOLUTION::FEAS, evRes3.errorCode);
	EXPECT_EQ(vector_t<double>::Zero(0), evRes3.optimumValue);

	vector_t<double> sol = vector_t<double>::Zero(2);
	sol << 3,0;
	EvaluationResult<double> evRes4(sol, SOLUTION::FEAS);
	EXPECT_EQ(0, evRes4.supportValue);
	EXPECT_EQ(SOLUTION::FEAS, evRes4.errorCode);
	EXPECT_EQ(sol, evRes4.optimumValue);
}

TEST(OptimizerTest, Minimize){
	
	//Constraints as box around center with corners (2,2)(2,-2)(-2,2)(-2,-2)
	matrix_t<double> boxMat = matrix_t<double>::Zero(4,2);
	boxMat << 1,0,
		   -1,0,
		   0,1,
		   0,-1;
	vector_t<double> boxVec = vector_t<double>::Zero(4);
	boxVec << 2,2,2,2;
	Optimizer<double> op(boxMat,boxVec,false);
	auto res = op.evaluate(vector_t<double>::Ones(2), false);
	vector_t<double> controlVec = -2.0*vector_t<double>::Ones(2);
	EXPECT_EQ(-4.0, res.supportValue);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_EQ(controlVec, res.optimumValue);

	vector_t<double> objective = vector_t<double>::Zero(2);
	objective << -2, 1;
	controlVec = vector_t<double>::Zero(2);
	controlVec << 2, -2;
	res = op.evaluate(objective, false);
	EXPECT_EQ(-6.0, res.supportValue);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_EQ(controlVec, res.optimumValue);
}

TEST(OptimizerTest, Maximize){
	
	//Constraints as box around center with corners (2,2)(2,-2)(-2,2)(-2,-2)
	matrix_t<double> boxMat = matrix_t<double>::Zero(4,2);
	boxMat << 1,0,
		   -1,0,
		   0,1,
		   0,-1;
	vector_t<double> boxVec = vector_t<double>::Zero(4);
	boxVec << 2,2,2,2;
	Optimizer<double> op(boxMat,boxVec,true);
	auto res = op.evaluate(vector_t<double>::Ones(2), false);
	vector_t<double> controlVec = 2.0*vector_t<double>::Ones(2);
	EXPECT_EQ(4.0, res.supportValue);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_EQ(controlVec, res.optimumValue);

	vector_t<double> objective = vector_t<double>::Zero(2);
	objective << -2, 1;
	controlVec = vector_t<double>::Zero(2);
	controlVec << -2, 2;
	res = op.evaluate(objective, false);
	EXPECT_EQ(6.0, res.supportValue);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_EQ(controlVec, res.optimumValue);
}

TEST(OptimizerTest, setVector){

	// Maximize with first constraint vector
	matrix_t<double> boxMat = matrix_t<double>::Zero(4,2);
	boxMat << 1,0,
		   -1,0,
		   0,1,
		   0,-1;
	vector_t<double> boxVec = vector_t<double>::Zero(4);
	boxVec << 2,2,2,2;
	Optimizer<double> op(boxMat,boxVec,true);
	auto res = op.evaluate(vector_t<double>::Ones(2), false);
	vector_t<double> controlVec = 2.0*vector_t<double>::Ones(2);
	EXPECT_EQ(4.0, res.supportValue);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_EQ(controlVec, res.optimumValue);

	// Switch to second constraint vector and maximize again
	boxVec << 3, 3, 3, 3;
	op.setVector(boxVec);
	res = op.evaluate(vector_t<double>::Ones(2), false);
	controlVec = 3.0*vector_t<double>::Ones(2);
	EXPECT_EQ(6.0, res.supportValue);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_EQ(controlVec, res.optimumValue);
}

TEST(OptimizerTest, checkConsistency){

	//Constraints as box around center with corners (2,2)(2,-2)(-2,2)(-2,-2)
	matrix_t<double> boxMat = matrix_t<double>::Zero(4,2);
	boxMat << 1,0,
		   -1,0,
		   0,1,
		   0,-1;
	vector_t<double> boxVec = vector_t<double>::Zero(4);
	boxVec << 2,2,2,2;
	Optimizer<double> op(boxMat,boxVec);
	bool res = op.checkConsistency();
	EXPECT_EQ(true, res);

	// switching to unsatisfiable constraints
	boxVec << 2, -3, 2, 2;
	op.setVector(boxVec);
	res = op.checkConsistency();
	EXPECT_EQ(false, res);

	// single point
	boxVec << 0, 0, 0, 0;
	op.setVector(boxVec);
	res = op.checkConsistency();
	EXPECT_EQ(true, res);
}

TEST(OptimizerTest, checkPoint){

	//Constraints as box around center with corners (2,2)(2,-2)(-2,2)(-2,-2)
	matrix_t<double> boxMat = matrix_t<double>::Zero(4,2);
	boxMat << 1,0,
		   -1,0,
		   0,1,
		   0,-1;
	vector_t<double> boxVec = vector_t<double>::Zero(4);
	boxVec << 2,2,2,2;
	Optimizer<double> op(boxMat,boxVec);

	Point<double> pointSat(vector_t<double>::Zero(2));
	bool res = op.checkPoint(pointSat);
	EXPECT_EQ(true, res);

	Point<double> pointUnsat(3.0*vector_t<double>::Ones(2));
	res = op.checkPoint(pointUnsat);
	EXPECT_EQ(false, res);
}

TEST(OptimizerTest, getInternalPoint){
	matrix_t<double> boxMat = matrix_t<double>::Zero(4,2);
	boxMat << 1,0,
		   -1,0,
		   0,1,
		   0,-1;
	vector_t<double> boxVec = vector_t<double>::Zero(4);
	boxVec << 2,2,2,2;
	Optimizer<double> op(boxMat,boxVec);

	auto res = op.getInternalPoint();
	Point<double> point(res.optimumValue);
	bool consistent = op.checkPoint(point);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_EQ(true, consistent);

	// Switch constraint vector, such that 0 is not an inner point
	boxVec << 10, -2, -5, 10;
	op.setVector(boxVec);
	res = op.getInternalPoint();
	point = Point<double>(res.optimumValue);
	consistent = op.checkPoint(point);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_EQ(true, consistent);

	// Switch to unsatisfiable constraints
	boxVec << 10, -11, 2, 2;
	op.setVector(boxVec);
	res = op.getInternalPoint();
	EXPECT_EQ(SOLUTION::INFEAS, res.errorCode);
}

TEST(OptimizerTest, redundantConstraints){
	// two redundant constraints.
	// Assuming that the first redundant constraints are returned
	matrix_t<double> boxMat = matrix_t<double>::Zero(6,2);
	boxMat << 1,1,
			1,0,
			1,0,
			0,1,
			-1,0,
			0,-1;
	vector_t<double> boxVec = vector_t<double>::Zero(6);
	boxVec << 5, 3, 2, 2, 2, 2;
	Optimizer<double> op(boxMat, boxVec);
	auto res = op.redundantConstraints();
	std::vector<std::size_t> controlVec{ 0, 1 }; 
	EXPECT_EQ(controlVec, res);

	// No redundant constraints
	boxMat << 1,0,
		   -1,0,
		   0,1,
		   0,-1,
		   1, 1,
		   -1, -1;
	boxVec << 2, 2, 2, 2, 2, 2;
	op.setMatrix(boxMat);
	op.setVector(boxVec);
	res = op.redundantConstraints();
	controlVec = std::vector<std::size_t>();
	EXPECT_EQ(controlVec, res);
}
