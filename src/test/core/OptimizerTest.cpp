#include "gtest/gtest.h"
#include "util/linearOptimization/Optimizer.h"
#include <iostream>

#define EXPECT_NEAR_VECTORS(expected, actual, thresh) \
        ASSERT_EQ(expected.size(), actual.size()) << "Array sizes differ.";\
        for (int idx = 0; idx < expected.size(); ++idx) \
        { \
            EXPECT_NEAR(expected[idx], actual[idx], thresh) << "At index: " << idx;\
        }
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
	EXPECT_NEAR(-4.0, res.supportValue, 1.0e-8);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_NEAR_VECTORS(controlVec, res.optimumValue, 1.0e-8)

	vector_t<double> objective = vector_t<double>::Zero(2);
	objective << -2, 1;
	controlVec = vector_t<double>::Zero(2);
	controlVec << 2, -2;
	res = op.evaluate(objective, false);
	EXPECT_NEAR(-6.0, res.supportValue, 1.0e-8);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_NEAR_VECTORS(controlVec, res.optimumValue, 1.0e-8);
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
	EXPECT_NEAR(4.0, res.supportValue, 1.0e-8);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_NEAR_VECTORS(controlVec, res.optimumValue, 1.0e-8);

	vector_t<double> objective = vector_t<double>::Zero(2);
	objective << -2, 1;
	controlVec = vector_t<double>::Zero(2);
	controlVec << -2, 2;
	res = op.evaluate(objective, false);
	EXPECT_NEAR(6.0, res.supportValue, 1.0e-8);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_NEAR_VECTORS(controlVec, res.optimumValue, 1.0e-8);
}

TEST(OptimizerTest, optimizeUnbounded){
	matrix_t<double> mat = matrix_t<double>::Zero(2,2);
	mat << 1,0,
		0,1;
	vector_t<double> vec = vector_t<double>::Ones(2);
	Optimizer<double> op(mat, vec, false);
	auto res = op.evaluate(vector_t<double>::Ones(2), false);
	EXPECT_EQ(SOLUTION::INFTY, res.errorCode);
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
	EXPECT_NEAR(4.0, res.supportValue, 1.0e-8);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_NEAR_VECTORS(controlVec, res.optimumValue, 1.0e-8);

	// Switch to second constraint vector and maximize again
	boxVec << 3, 3, 3, 3;
	op.setVector(boxVec);
	res = op.evaluate(vector_t<double>::Ones(2), false);
	controlVec = 3.0*vector_t<double>::Ones(2);
	EXPECT_NEAR(6.0, res.supportValue, 1.0e-8);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_NEAR_VECTORS(controlVec, res.optimumValue, 1.0e-8);
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
	EXPECT_TRUE(res);

	// switching to unsatisfiable constraints
	boxVec << 2, -3, 2, 2;
	op.setVector(boxVec);
	res = op.checkConsistency();
	EXPECT_FALSE(res);

	// single point
	boxVec << 0, 0, 0, 0;
	op.setVector(boxVec);
	res = op.checkConsistency();
	EXPECT_TRUE(res);
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
	EXPECT_TRUE(res);

	Point<double> pointUnsat(3.0*vector_t<double>::Ones(2));
	res = op.checkPoint(pointUnsat);
	EXPECT_FALSE(res);
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
	EXPECT_TRUE(consistent);

	// Switch constraint vector, such that 0 is not an inner point
	boxVec << 10, -2, -5, 10;
	op.setVector(boxVec);
	res = op.getInternalPoint();
	point = Point<double>(res.optimumValue);
	consistent = op.checkPoint(point);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_TRUE(consistent);

	// Switch to unsatisfiable constraints
	boxVec << 10, -11, 2, 2;
	op.setVector(boxVec);
	res = op.getInternalPoint();
	EXPECT_EQ(SOLUTION::INFEAS, res.errorCode);
}

TEST(OptimizerTest, redundantConstraints){
	// two redundant constraints.
	// Assuming that the last constraints are checked first
	matrix_t<double> boxMat = matrix_t<double>::Zero(6,2);
	boxMat << 1,0,
			0,1,
			-1,0,
			0,-1,
			1,0,
			1,1;
	vector_t<double> boxVec = vector_t<double>::Zero(6);
	boxVec << 2, 2, 2, 2, 3, 5;
	Optimizer<double> op(boxMat, boxVec);
	auto res = op.redundantConstraints();
	std::vector<std::size_t> controlVec{ 4, 5 }; 
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

	boxMat = matrix_t<double>::Zero(5,2);
	boxMat << 1,0,
			-1,0,
			0,1,
			0,-1,
			1,1;
	boxVec = vector_t<double>::Zero(5);
	boxVec << 2,2,2,2,0;
	op.setMatrix(boxMat);
	op.setVector(boxVec);
	res = op.redundantConstraints();
	controlVec = std::vector<std::size_t> {0, 2};
	EXPECT_EQ(controlVec, res);
}

TEST(OptimizerTest, maximize_mixedConstraints){
	matrix_t<double> boxMat = matrix_t<double>::Zero(4,2);
	boxMat << 1,0,
			0,1,
			1,0,
			0,1;
	vector_t<double> boxVec = vector_t<double>::Zero(4);
	boxVec << 2, 2, -2, -2;
	std::vector<carl::Relation> relations = {carl::Relation::LEQ,
											carl::Relation::LEQ,
											carl::Relation::GEQ,
											carl::Relation::GEQ};
	Optimizer<double> op(boxMat, boxVec);	
	op.setRelations(relations);
	auto res = op.evaluate(vector_t<double>::Ones(2), false);
	vector_t<double> controlVec = 2.0*vector_t<double>::Ones(2);
	EXPECT_NEAR(4.0, res.supportValue, 1.0e-8);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_NEAR_VECTORS(controlVec, res.optimumValue, 1.0e-8);

	relations = {carl::Relation::LEQ,
				carl::Relation::LEQ,
				carl::Relation::EQ,
				carl::Relation::EQ};
	op.setRelations(relations);
	res = op.evaluate(vector_t<double>::Ones(2), false);
	controlVec = -2.0*vector_t<double>::Ones(2);
	EXPECT_NEAR(-4.0, res.supportValue, 1.0e-8);
	EXPECT_EQ(SOLUTION::FEAS, res.errorCode);
	EXPECT_NEAR_VECTORS(controlVec, res.optimumValue, 1.0e-8);

}

TEST(OptimizerTest, redundantConstraints_mixedConstraints){
	/* constraints:
		(0) x == 2 <-> x == 2
		(1) y <= 2 <-> -y >= -2
		(2) x <= 2 <-> x <= 2
		(3) y >= -2 <-> -y <= 2
		(4) x <= 3 <-> -x >= -3
		(5) x+y <= 5 <-> x+y <= 5

		line segment x == 2 and -2 <= y <= 2
		constraints 5,4 and 2 are redundant
	*/
	matrix_t<double> lineMat = matrix_t<double>::Zero(6,2);
	lineMat << 1,0,
			0,-1,
			1,0,
			0,-1,
			-1,0,
			1,1;
	vector_t<double> lineVec = vector_t<double>::Zero(6);
	lineVec << 2, -2, 2, 2, -3, 5;
	std::vector<carl::Relation> relations = {carl::Relation::EQ,
											carl::Relation::GEQ,
											carl::Relation::LEQ,
											carl::Relation::LEQ,
											carl::Relation::GEQ,
											carl::Relation::LEQ};
	Optimizer<double> op(lineMat, lineVec);
	op.setRelations(relations);
	auto res = op.redundantConstraints();
	std::vector<std::size_t> controlVec{ 2, 4, 5 };

	EXPECT_EQ(controlVec, res);
}