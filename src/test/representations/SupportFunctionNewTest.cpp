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
	Point<TypeParam> p({TypeParam(0),TypeParam(0)});
	Point<TypeParam> q({TypeParam(1),TypeParam(1)});
	Box<TypeParam> box(std::make_pair(p,q));
	Leaf<TypeParam, Box<TypeParam>> r(&box);
	EXPECT_TRUE(r.getType() == SFNEW_TYPE::LEAF);
	EXPECT_TRUE(r.getOriginCount() == 0);
	EXPECT_TRUE(r.getChildren().size() == 0);

	//The tree
	SupportFunctionContentNew<TypeParam> sfc(&r);

	//tMat = 2 * Identity_Matrix , tVec = (1 0 0)
	int dim = 2;
	matrix_t<TypeParam> tMat = matrix_t<TypeParam>::Zero(dim, dim);
	vector_t<TypeParam> tVec = vector_t<TypeParam>::Zero(dim);
	for(int i = 0; i < tMat.rows(); i++){
		tMat(i,i) = 1;
	}
	tVec(0) = 1;

	//Construct trafo1
	TrafoOp<TypeParam> trafo1(&sfc, tMat, tVec);
	EXPECT_EQ(trafo1.getCurrentExponent(), 1);
	EXPECT_EQ(trafo1.getSuccessiveTransformations(), 0);

	//Save pointer to parameters for later, checking if it remains the same object 
	std::shared_ptr<const LinTrafoParameters<TypeParam>> trafo1Params = trafo1.getParameters();

	//Construct trafo2
	TrafoOp<TypeParam> trafo2(&sfc, tMat, tVec);	
	EXPECT_EQ(trafo2.getCurrentExponent(), 1);
	EXPECT_EQ(trafo2.getSuccessiveTransformations(), 1);

	//Evaluate
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity(dim,dim);
	std::cout << "START EVALUATION FOR 2 TRAFOS\n"; 
	std::vector<EvaluationResult<TypeParam>> res = sfc.evaluate(directions);
	std::cout << "END EVALUATION\n";
	
	//Check if the supportvalues were right
	//Should be [1 + #trafos , 1] everywhere
	EXPECT_EQ(res.at(0).supportValue, TypeParam(3));
	EXPECT_EQ(res.at(1).supportValue, TypeParam(1));

	TrafoOp<TypeParam> trafo3(&sfc, tMat, tVec);
	EXPECT_EQ(trafo3.getCurrentExponent(), 1);
	EXPECT_EQ(trafo3.getSuccessiveTransformations(), 2);

	TrafoOp<TypeParam> trafo4(&sfc, tMat, tVec);
	EXPECT_EQ(trafo4.getCurrentExponent(), 4);
	EXPECT_EQ(trafo4.getSuccessiveTransformations(), 0);

	//Check whether parameter object remained the same (whether both point to the same address)
	EXPECT_EQ(trafo1Params, trafo4.getParameters());

	//Evaluate
	std::cout << "START EVALUATION FOR 4 TRAFOS\n"; 
	res = sfc.evaluate(directions);
	std::cout << "END EVALUATION\n";

	EXPECT_EQ(res.at(0).supportValue, TypeParam(5));
	EXPECT_EQ(res.at(1).supportValue, TypeParam(1));

	TrafoOp<TypeParam> trafo5(&sfc, tMat, tVec);
	EXPECT_EQ(trafo5.getCurrentExponent(), 1);
	EXPECT_EQ(trafo5.getSuccessiveTransformations(), 0);

	TrafoOp<TypeParam> trafo6(&sfc, tMat, tVec);
	EXPECT_EQ(trafo6.getCurrentExponent(), 1);
	EXPECT_EQ(trafo6.getSuccessiveTransformations(), 1);

	//Evaluate
	std::cout << "START EVALUATION FOR 6 TRAFOS\n"; 
	res = sfc.evaluate(directions);
	std::cout << "END EVALUATION\n";

	EXPECT_EQ(res.at(0).supportValue, TypeParam(7));
	EXPECT_EQ(res.at(1).supportValue, TypeParam(1));

	TrafoOp<TypeParam> trafo7(&sfc, tMat, tVec);
	EXPECT_EQ(trafo7.getCurrentExponent(), 1);
	EXPECT_EQ(trafo7.getSuccessiveTransformations(), 2);

	TrafoOp<TypeParam> trafo8(&sfc, tMat, tVec);
	EXPECT_EQ(trafo8.getCurrentExponent(), 4);
	EXPECT_EQ(trafo8.getSuccessiveTransformations(), 1);

	EXPECT_EQ(trafo1Params, trafo8.getParameters());

	//Evaluate
	std::cout << "START EVALUATION FOR 8 TRAFOS\n"; 
	res = sfc.evaluate(directions);
	std::cout << "END EVALUATION\n";

	EXPECT_EQ(res.at(0).supportValue, TypeParam(9));
	EXPECT_EQ(res.at(1).supportValue, TypeParam(1));

	TrafoOp<TypeParam> trafo9(&sfc, tMat, tVec);
	EXPECT_EQ(trafo9.getCurrentExponent(), 1);
	EXPECT_EQ(trafo9.getSuccessiveTransformations(), 0);

	//Evaluate
	std::cout << "START EVALUATION FOR 9 TRAFOS\n"; 
	res = sfc.evaluate(directions);
	std::cout << "END EVALUATION\n";

}

////// Functionality Tests

TYPED_TEST(SupportFunctionNewTest, SupportFunctionNewEvaluate){
	
	//Construct leaf nodes
	Box<TypeParam> box1 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(-1)}), Point<TypeParam>({TypeParam(1), TypeParam(2)})));
	std::cout << "box1: " << box1 << std::endl;
	Leaf<TypeParam, Box<TypeParam>> l1(&box1);
	Box<TypeParam> box2 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(0)}), Point<TypeParam>({TypeParam(2), TypeParam(2)})));
	std::cout << "box2: " << box2 << std::endl;
	Leaf<TypeParam, Box<TypeParam>> l2(&box2);

	//Assemble them to a tree 
	SupportFunctionContentNew<TypeParam> sfc(&l1);
	EXPECT_TRUE(sfc.getRoot()->getParent() == nullptr);
	SupportFunctionContentNew<TypeParam> sfc2(&l2);

	//Build trafoOp
	matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Zero(2,2);
	trafoMat(0,0) = TypeParam(2);
	trafoMat(1,1) = TypeParam(2);
	vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero(2);
	TrafoOp<TypeParam> trafo(&sfc, trafoMat, trafoVec);

	EXPECT_TRUE(sfc.getRoot() == &trafo);
	EXPECT_TRUE(sfc.getRoot()->getChildren().size() == 1);
	EXPECT_TRUE(sfc.getRoot()->getChildren().at(0)->getParent() == &trafo);

	SumOp<TypeParam> sum(&sfc, &sfc2);
	
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