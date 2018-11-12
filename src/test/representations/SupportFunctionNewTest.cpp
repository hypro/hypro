/**
 * Tests for new SupportFunction architecture
 *
 * @author Phillip Tse
 */ 

//#include "../../hypro/representations/SupportFunctionNew/SupportFunctionContentNew.h"
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
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity(2,2);
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf(&box);
	EXPECT_TRUE(sf.getRoot()->getType() == SFNEW_TYPE::LEAF);
	EXPECT_TRUE(sf.getRoot()->getOriginCount() == 0);
	EXPECT_TRUE(sf.getRoot()->getChildren().size() == 0);
	
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

	//Make the box 
	Point<TypeParam> p({TypeParam(0),TypeParam(0)});
	Point<TypeParam> q({TypeParam(1),TypeParam(1)});
	Box<TypeParam> box(std::make_pair(p,q));
	
	//The tree with only one leaf containing the box
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf(&box);
	EXPECT_TRUE(sf.getRoot()->getType() == SFNEW_TYPE::LEAF);
	EXPECT_TRUE(sf.getRoot()->getOriginCount() == 0);
	EXPECT_TRUE(sf.getRoot()->getChildren().size() == 0);

	//tMat = 2 * Identity_Matrix , tVec = (1 0 0)
	int dim = 2;
	matrix_t<TypeParam> tMat = matrix_t<TypeParam>::Identity(dim, dim);
	vector_t<TypeParam> tVec = vector_t<TypeParam>::Zero(dim);
	tVec(0) = 1;

	//Directions to evaluate, is the identity matrix
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity(dim,dim);

	//Save pointer to parameters for later, checking if it remains the same object 
	std::shared_ptr<const LinTrafoParameters<TypeParam>> trafo0Params = nullptr;

	//sf1
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf1 = sf.affineTransformation(tMat, tVec); 
	EXPECT_TRUE(sf1.getRoot() != nullptr);
	EXPECT_TRUE(sf1.getRoot()->getChildren().size() == 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf1.getRoot().get()))->getCurrentExponent(), 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf1.getRoot().get()))->getSuccessiveTransformations(), 0);
	std::cout << "Constructed trafo1" << std::endl;

	std::cout << "Ref count of trafo1 before deletion: " << sf1.getRoot().use_count() << std::endl;
	std::cout << "Ref count of leaf before deletion: " << sf1.getRoot()->getChildren().at(0).use_count() << std::endl;

	//Fill trafo0Params
	trafo0Params = (dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf1.getRoot().get()))->getParameters();
	std::cout << "saved trafo0Params with address " << trafo0Params << std::endl;

	//sf2
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf2 = sf1.affineTransformation(tMat, tVec); 
	EXPECT_TRUE(sf2.getRoot() != nullptr);
	EXPECT_TRUE(sf2.getRoot()->getChildren().size() == 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf2.getRoot().get()))->getCurrentExponent(), 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf2.getRoot().get()))->getSuccessiveTransformations(), 1);
	std::cout << "Constructed trafo2" << std::endl;

	//Check whether parameter object remained the same (whether both point to the same address)
	EXPECT_EQ(trafo0Params, (dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf2.getRoot().get())->getParameters()));

	//Evaluate
	std::cout << "START EVALUATION FOR 2 TRAFOS\n"; 
	std::vector<EvaluationResult<TypeParam>> res = sf2.multiEvaluate(directions,true);
	std::cout << "END EVALUATION\n";

	//Check if the supportvalues were right
	//Should be [1 + #trafos , 1] everywhere
	EXPECT_EQ(res.at(0).supportValue, TypeParam(3));
	EXPECT_EQ(res.at(1).supportValue, TypeParam(1));

/*
	int numOfTrafos = 9;
	for(int i = 0; i < numOfTrafos; i++){
		
		sf = sf.affineTransformation(tMat, tVec);
		
		EXPECT_TRUE(sf.getRoot() != nullptr);
		EXPECT_TRUE(sf.getRoot()->getChildren().size() == 1);
		EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf.getRoot().get()))->getCurrentExponent(), 1);
		EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf.getRoot().get()))->getSuccessiveTransformations(), 0);
		std::cout << "Constructed trafo" << i << std::endl;
		
		if(i == 0){
			//Save pointer to parameters for later, checking if it remains the same object 
			trafo0Params = (dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf.getRoot().get()))->getParameters();
			std::cout << "saved trafo0Params with address " << trafo0Params << std::endl;
		}
		
		if((i % 2 == 1) || (i == numOfTrafos)){

			//Check whether parameter object remained the same (whether both point to the same address)
			EXPECT_EQ(trafo0Params, (dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf.getRoot().get())->getParameters()));

			//Evaluate
			std::cout << "START EVALUATION FOR " << i << " TRAFOS\n"; 
			std::vector<EvaluationResult<TypeParam>> res = sf.multiEvaluate(directions,true);
			std::cout << "END EVALUATION\n";

			//Check if the supportvalues were right
			//Should be [1 + #trafos , 1] everywhere
			EXPECT_EQ(res.at(0).supportValue, TypeParam(1 + (i + 1)));
			EXPECT_EQ(res.at(1).supportValue, TypeParam(1));
		}
	}
*/
}


////// Functionality Tests
/*
TYPED_TEST(SupportFunctionNewTest, SupportFunctionNewEvaluate){
	
	//Construct leaf nodes
	Box<TypeParam> box1 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(-1)}), Point<TypeParam>({TypeParam(1), TypeParam(2)})));
	std::cout << "box1: " << box1 << std::endl;
	Leaf<TypeParam, Box<TypeParam>> l1(&box1);
	Box<TypeParam> box2 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(0)}), Point<TypeParam>({TypeParam(2), TypeParam(2)})));
	std::cout << "box2: " << box2 << std::endl;
	Leaf<TypeParam, Box<TypeParam>> l2(&box2);

	//Assemble them to a tree 
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf(&l1);
	EXPECT_TRUE(sf.getRoot()->getParent() == nullptr);
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf2(&l2);
	EXPECT_TRUE(sf2.getRoot()->getParent() == nullptr);

	//Build trafop
	matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Zero(2,2);
	trafoMat(0,0) = TypeParam(2);
	trafoMat(1,1) = TypeParam(2);
	vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero(2);
	TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> trafo(&sf, trafoMat, trafoVec);

	EXPECT_TRUE(sf.getRoot() == &trafo);
	EXPECT_TRUE(sf.getRoot()->getChildren().size() == 1);
	EXPECT_TRUE(sf.getRoot()->getChildren().at(0)->getParent() == &trafo);

	SumOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sum(&sf, &sf2);
	
	EXPECT_TRUE(sf.getRoot() == &sum);
	EXPECT_TRUE(sf.getRoot()->getType() == SFNEW_TYPE::SUMOP);
	EXPECT_TRUE(sf.getRoot()->getOriginCount() == sf.getRoot()->getChildren().size());
	EXPECT_TRUE(sf.getRoot()->getChildren().at(0)->getParent() == &sum);
	EXPECT_TRUE(sf.getRoot()->getChildren().at(1)->getParent() == &sum);
	std::cout << sf << std::endl;

	//Evaluate
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Zero(2,2);
	directions(0,0) = TypeParam(1);
	directions(1,1) = TypeParam(1);
	std::cout << "START EVALUATION\n"; 
	std::vector<EvaluationResult<TypeParam>> res = sf.multiEvaluate(directions,true);
	std::cout << "END EVALUATION\n";
	std::cout << "Result of Evaluation is:\n";
	for(auto& eRes : res){
		std::cout << eRes << std::endl;
	}
	
}
*/
/*
TYPED_TEST(SupportFunctionNewTest, AffineTransformation){

	//Make the box leaf
	Point<TypeParam> p({TypeParam(0),TypeParam(0)});
	Point<TypeParam> q({TypeParam(1),TypeParam(1)});
	Box<TypeParam> box(std::make_pair(p,q));
	Leaf<TypeParam, Box<TypeParam>> r(&box);
	EXPECT_TRUE(r.getType() == SFNEW_TYPE::LEAF);
	EXPECT_TRUE(r.getOriginCount() == 0);
	EXPECT_TRUE(r.getChildren().size() == 0);

	//The tree
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf(&r);

	//tMat = 2 * Identity_Matrix , tVec = (1 0 0)
	int dim = 2;
	matrix_t<TypeParam> tMat = matrix_t<TypeParam>::Zero(dim, dim);
	vector_t<TypeParam> tVec = vector_t<TypeParam>::Zero(dim);
	for(int i = 0; i < tMat.rows(); i++){
		tMat(i,i) = 1;
	}
	tVec(0) = 1;

	sf = sf.affineTransformation(tMat, tVec);	

}
*/