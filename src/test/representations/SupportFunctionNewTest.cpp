/**
 * Tests for new SupportFunction architecture
 *
 * @author Phillip Tse
 */ 

#include "../../hypro/representations/SupportFunctionNew/SupportFunctionContentNew.h"
#include "../../hypro/representations/GeometricObject.h"
#include "gtest/gtest.h"
#include "../defines.h"

using namespace hypro;

template<typename Number>
class SupportFunctionNewTest : public ::testing::Test {
protected:
	virtual void SetUp() {

	}
	virtual void TearDown() {

	}	
};

////// Data Structure Tests


TYPED_TEST(SupportFunctionNewTest, LeafTest){

	Box<TypeParam> box;
	Leaf<TypeParam, Box<TypeParam>> r(&box);
	EXPECT_TRUE(r.getType() == SFNEW_TYPE::LEAF);
	EXPECT_TRUE(r.getOriginCount() == 0);
	EXPECT_TRUE(r.getChildren().size() == 0);

/*	WAIT UNTIL VPOLY::MULTIEVALUATE IMPLEMENTED
	VPolytope<TypeParam> vpoly;
	Leaf<TypeParam, VPolytope<TypeParam>> child(&vpoly);
	r.addToChildren(&child);
	EXPECT_TRUE(r.getChildren().size() == 1);
	EXPECT_TRUE(child.getChildren().size() == 0);
*/
}

//Have a box as a leaf. Put a chain of trafoOps above the leaf. 
//Check currentExponent, successiveTransformations and parameter values
TYPED_TEST(SupportFunctionNewTest, TrafoOp){

	//Make the box leaf
	Box<TypeParam> box;
	Leaf<TypeParam, Box<TypeParam>> r(&box);
	EXPECT_TRUE(r.getType() == SFNEW_TYPE::LEAF);
	EXPECT_TRUE(r.getOriginCount() == 0);
	EXPECT_TRUE(r.getChildren().size() == 0);

	//The tree
	SupportFunctionContentNew<TypeParam> sfc(&r);

	//tMat = 2 * Identity_Matrix , tVec = (1 0 0)
	int dim = 3;
	matrix_t<TypeParam> tMat = matrix_t<TypeParam>::Zero(dim, dim);
	vector_t<TypeParam> tVec = vector_t<TypeParam>::Zero(dim);
	for(int i = 0; i < tMat.rows(); i++){
		tMat(i,i) = 2;
	}
	tVec(0) = 1;

	//Construct trafo1
	std::cout << "make trafo1" << std::endl;
	TrafoOp<TypeParam> trafo1(&sfc, tMat, tVec);
	EXPECT_EQ(trafo1.getCurrentExponent(), 1);
	EXPECT_EQ(trafo1.getSuccessiveTransformations(), 0);

	//Construct trafo2
	std::cout << "make trafo2" << std::endl;
	TrafoOp<TypeParam> trafo2(&sfc, tMat, tVec);	
	EXPECT_EQ(trafo2.getCurrentExponent(), 1);
	EXPECT_EQ(trafo2.getSuccessiveTransformations(), 1);	

	std::cout << "make trafo3" << std::endl;
	TrafoOp<TypeParam> trafo3(&sfc, tMat, tVec);
	EXPECT_EQ(trafo3.getCurrentExponent(), 1);
	EXPECT_EQ(trafo3.getSuccessiveTransformations(), 2);

	std::cout << "make trafo4" << std::endl;
	TrafoOp<TypeParam> trafo4(&sfc, tMat, tVec);
	EXPECT_EQ(trafo4.getCurrentExponent(), 4);
	EXPECT_EQ(trafo4.getSuccessiveTransformations(), 0);	

	std::cout << "make trafo5" << std::endl;
	TrafoOp<TypeParam> trafo5(&sfc, tMat, tVec);
	EXPECT_EQ(trafo5.getCurrentExponent(), 1);
	EXPECT_EQ(trafo5.getSuccessiveTransformations(), 0);

	std::cout << "make trafo6" << std::endl;
	TrafoOp<TypeParam> trafo6(&sfc, tMat, tVec);
	EXPECT_EQ(trafo6.getCurrentExponent(), 1);
	EXPECT_EQ(trafo6.getSuccessiveTransformations(), 1);

	std::cout << "make trafo7" << std::endl;
	TrafoOp<TypeParam> trafo7(&sfc, tMat, tVec);
	EXPECT_EQ(trafo7.getCurrentExponent(), 1);
	EXPECT_EQ(trafo7.getSuccessiveTransformations(), 2);

	std::cout << "make trafo8" << std::endl;
	TrafoOp<TypeParam> trafo8(&sfc, tMat, tVec);
	EXPECT_EQ(trafo8.getCurrentExponent(), 4);
	EXPECT_EQ(trafo8.getSuccessiveTransformations(), 0);

	std::cout << "make trafo9" << std::endl;
	TrafoOp<TypeParam> trafo9(&sfc, tMat, tVec);
	EXPECT_EQ(trafo9.getCurrentExponent(), 1);
	EXPECT_EQ(trafo9.getSuccessiveTransformations(), 0);
}

/*
TYPED_TEST(SupportFunctionNewTest, ParameterStruct){

	RootGrowNode<TypeParam> r;
	Parameters<int, float, RootGrowNode<TypeParam>> p(1, 2.0f, r);
	//EXPECT_TRUE(Parameters<int,float,RootGrowNode<TypeParam>>::size() == std::size_t(3));

	Parameters<double, matrix_t<TypeParam>> p2(std::make_tuple(-2.0, matrix_t<TypeParam>::Zero(4,4)));
	//EXPECT_TRUE(Parameters<double, matrix_t<TypeParam>>::size() == std::size_t(2));
}
*/

TYPED_TEST(SupportFunctionNewTest, RootGrowTree){

	SUCCEED();

}

////// Data Structure Integration Tests (Virtual functions etc)

////// Functionality Tests

TYPED_TEST(SupportFunctionNewTest, SupportFunctionNewEvaluate){
	
	//Construct needed nodes
	Box<TypeParam> box1 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(-1)}), Point<TypeParam>({TypeParam(1), TypeParam(2)})));
	std::cout << "box1: " << box1 << std::endl;
	Leaf<TypeParam, Box<TypeParam>> l1(&box1);
	Box<TypeParam> box2 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(0)}), Point<TypeParam>({TypeParam(2), TypeParam(2)})));
	std::cout << "box2: " << box2 << std::endl;
	Leaf<TypeParam, Box<TypeParam>> l2(&box2);
/*
	matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Zero(2,2);
	trafoMat(0,0) = TypeParam(2);
	trafoMat(1,1) = TypeParam(2);
	vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero(2);
	TrafoOp<TypeParam> trafo(trafoMat, trafoVec);
*/
	SumOp<TypeParam> sum;

	//Assemble them to a tree 
	SupportFunctionContentNew<TypeParam> sfc(&l1);
	EXPECT_TRUE(sfc.getRoot()->getParent() == nullptr);
	SupportFunctionContentNew<TypeParam> sfc2(&l2);
/*
	sfc.addUnaryOp(&trafo);
	EXPECT_TRUE(sfc.getRoot() == &trafo);
	EXPECT_TRUE(sfc.getRoot()->getChildren().size() == 1);
	EXPECT_TRUE(sfc.getRoot()->getChildren().at(0)->getParent() == &trafo);
*/
	sfc.addBinaryOp(&sum, &sfc2);
	EXPECT_TRUE(sfc.getRoot() == &sum);
	EXPECT_TRUE(sfc.getRoot()->getType() == SFNEW_TYPE::SUMOP);
	EXPECT_TRUE(sfc.getRoot()->getOriginCount() == sfc.getRoot()->getChildren().size());
	EXPECT_TRUE(sfc.getRoot()->getChildren().at(0)->getParent() == &sum);
	EXPECT_TRUE(sfc.getRoot()->getChildren().at(1)->getParent() == &sum);
	std::cout << sfc << std::endl;

	//Evaluate
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Zero(2,2);
	directions(0,0) = TypeParam(1);
	directions(1,1) = TypeParam(1);
	std::cout << "START EVALUATION\n"; 
	std::vector<EvaluationResult<TypeParam>> res = sfc.evaluate(directions);
	std::cout << "END EVALUATION\n";
	std::cout << "Result of Evaluation is:\n";
	for(auto& eRes : res){
		std::cout << eRes << std::endl;
	}
	
}