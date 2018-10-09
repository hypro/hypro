/**
 * Tests for new SupportFunction architecture
 *
 * @author Phillip Tse
 */ 

#include "../../hypro/representations/SupportFunctionNew/SupportFunctionContentNew.h"
#include "../../hypro/representations/GeometricObject.h"
//#include "../../hypro/representations/Polytopes/VPolytope/VPolytope.h"
//#include "../../hypro/representations/Box/Box.h"
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
	matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Zero(2,2);
	trafoMat(0,0) = TypeParam(2);
	trafoMat(1,1) = TypeParam(2);
	vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero(2);
	TrafoOp<TypeParam> trafo(trafoMat, trafoVec);
	SumOp<TypeParam> sum;

	//Assemble them to a tree 
	SupportFunctionContentNew<TypeParam> sfc(&l1);
	SupportFunctionContentNew<TypeParam> sfc2(&l2);
	sfc.addUnaryOp(&trafo);
	EXPECT_TRUE(sfc.getRoot() == &trafo);
	EXPECT_TRUE(sfc.getRoot()->getChildren().size() == 1);
	sfc.addBinaryOp(&sum, &sfc2);
	EXPECT_TRUE(sfc.getRoot() == &sum);
	EXPECT_TRUE(sfc.getRoot()->getType() == SFNEW_TYPE::SUMOP);
	EXPECT_TRUE(sfc.getRoot()->getOriginCount() == sfc.getRoot()->getChildren().size());

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