/**
 * Tests for new SupportFunction architecture
 *
 * @author Phillip Tse
 */ 

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

	//sf3
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf3 = sf2.affineTransformation(tMat, tVec); 
	EXPECT_TRUE(sf3.getRoot() != nullptr);
	EXPECT_TRUE(sf3.getRoot()->getChildren().size() == 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf3.getRoot().get()))->getCurrentExponent(), 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf3.getRoot().get()))->getSuccessiveTransformations(), 2);
	std::cout << "Constructed trafo3" << std::endl;

	//sf4
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf4 = sf3.affineTransformation(tMat, tVec); 
	EXPECT_TRUE(sf4.getRoot() != nullptr);
	EXPECT_TRUE(sf4.getRoot()->getChildren().size() == 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf4.getRoot().get()))->getCurrentExponent(), 4);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf4.getRoot().get()))->getSuccessiveTransformations(), 0);
	std::cout << "Constructed trafo4" << std::endl;

	//Check whether parameter object remained the same (whether both point to the same address)
	EXPECT_EQ(trafo0Params, (dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf4.getRoot().get())->getParameters()));

	//Evaluate
	std::cout << "START EVALUATION FOR 4 TRAFOS\n"; 
	res = sf4.multiEvaluate(directions,true);
	std::cout << "END EVALUATION\n";

	//Check if the supportvalues were right
	//Should be [1 + #trafos , 1] everywhere
	EXPECT_EQ(res.at(0).supportValue, TypeParam(5));
	EXPECT_EQ(res.at(1).supportValue, TypeParam(1));

	//sf5
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf5 = sf4.affineTransformation(tMat, tVec); 
	EXPECT_TRUE(sf5.getRoot() != nullptr);
	EXPECT_TRUE(sf5.getRoot()->getChildren().size() == 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf5.getRoot().get()))->getCurrentExponent(), 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf5.getRoot().get()))->getSuccessiveTransformations(), 0);
	std::cout << "Constructed trafo5" << std::endl;

	//sf6
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf6 = sf5.affineTransformation(tMat, tVec); 
	EXPECT_TRUE(sf6.getRoot() != nullptr);
	EXPECT_TRUE(sf6.getRoot()->getChildren().size() == 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf6.getRoot().get()))->getCurrentExponent(), 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf6.getRoot().get()))->getSuccessiveTransformations(), 1);
	std::cout << "Constructed trafo6" << std::endl;

	//sf7
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf7 = sf6.affineTransformation(tMat, tVec); 
	EXPECT_TRUE(sf7.getRoot() != nullptr);
	EXPECT_TRUE(sf7.getRoot()->getChildren().size() == 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf7.getRoot().get()))->getCurrentExponent(), 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf7.getRoot().get()))->getSuccessiveTransformations(), 2);
	std::cout << "Constructed trafo7" << std::endl;

	//sf8
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf8 = sf7.affineTransformation(tMat, tVec); 
	EXPECT_TRUE(sf8.getRoot() != nullptr);
	EXPECT_TRUE(sf8.getRoot()->getChildren().size() == 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf8.getRoot().get()))->getCurrentExponent(), 4);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf8.getRoot().get()))->getSuccessiveTransformations(), 1);
	std::cout << "Constructed trafo8" << std::endl;

	//Check whether parameter object remained the same (whether both point to the same address)
	EXPECT_EQ(trafo0Params, (dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf8.getRoot().get())->getParameters()));

	//Evaluate
	std::cout << "START EVALUATION FOR 8 TRAFOS\n"; 
	res = sf8.multiEvaluate(directions,true);
	std::cout << "END EVALUATION\n";

	//Check if the supportvalues were right
	//Should be [1 + #trafos , 1] everywhere
	EXPECT_EQ(res.at(0).supportValue, TypeParam(9));
	EXPECT_EQ(res.at(1).supportValue, TypeParam(1));

	//sf9
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf9 = sf8.affineTransformation(tMat, tVec); 
	EXPECT_TRUE(sf9.getRoot() != nullptr);
	EXPECT_TRUE(sf9.getRoot()->getChildren().size() == 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf9.getRoot().get()))->getCurrentExponent(), 1);
	EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf9.getRoot().get()))->getSuccessiveTransformations(), 0);
	std::cout << "Constructed trafo9" << std::endl;

	//Check whether parameter object remained the same (whether both point to the same address)
	EXPECT_EQ(trafo0Params, (dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf9.getRoot().get())->getParameters()));

	//Evaluate
	std::cout << "START EVALUATION FOR 9 TRAFOS\n"; 
	res = sf9.multiEvaluate(directions,true);
	std::cout << "END EVALUATION\n";

	//Check if the supportvalues were right
	//Should be [1 + #trafos , 1] everywhere
	EXPECT_EQ(res.at(0).supportValue, TypeParam(10));
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

TYPED_TEST(SupportFunctionNewTest, SupportFunctionNewEvaluate){
	
	//Construct leaf nodes
	Box<TypeParam> box1 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(-1)}), Point<TypeParam>({TypeParam(1), TypeParam(2)})));
	std::cout << "box1: " << box1 << std::endl;
	Box<TypeParam> box2 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(0)}), Point<TypeParam>({TypeParam(2), TypeParam(2)})));
	std::cout << "box2: " << box2 << std::endl;

	//Assemble them to a tree 
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf(&box1);
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf2(&box2);
	
	//Build trafop
	matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Zero(2,2);
	trafoMat(0,0) = TypeParam(2);
	trafoMat(1,1) = TypeParam(2);
	vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero(2);

	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sfWithTrafo = sf.affineTransformation(trafoMat, trafoVec);
	
	EXPECT_TRUE(sfWithTrafo.getRoot()->getType() == SFNEW_TYPE::TRAFO);
	EXPECT_TRUE(sfWithTrafo.getRoot()->getChildren().size() == 1);
	
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sum = sfWithTrafo.minkowskiSum(sf2);
	
	EXPECT_TRUE(sum.getRoot()->getType() == SFNEW_TYPE::SUMOP);
	EXPECT_TRUE(sum.getRoot()->getOriginCount() == sum.getRoot()->getChildren().size());
	std::cout << sum << std::endl;

	//Evaluate
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Zero(2,2);
	directions(0,0) = TypeParam(1);
	directions(1,1) = TypeParam(1);
	std::cout << "START EVALUATION\n"; 
	std::vector<EvaluationResult<TypeParam>> res = sum.multiEvaluate(directions,true);
	std::cout << "END EVALUATION\n";
	std::cout << "Result of Evaluation is:\n";
	for(auto& eRes : res){
		std::cout << eRes << std::endl;
	}
	
}

TYPED_TEST(SupportFunctionNewTest, Deletion){

	//Non-owning pointers needed to check whether the sf's they are pointing to are actually deleted or not
	std::weak_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>> sf1Copy;
	std::weak_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>> sf2Copy;
	std::weak_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>> sfTrafoCopy;
	std::weak_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>> sfSumCopy;

	{
		//Construct leaf nodes
		Box<TypeParam> box1 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(-1)}), Point<TypeParam>({TypeParam(1), TypeParam(2)})));
		Box<TypeParam> box2 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(0)}), Point<TypeParam>({TypeParam(2), TypeParam(2)})));
		std::shared_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>> sf1 = std::make_shared<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>>(&box1);
		std::shared_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>> sf2 = std::make_shared<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>>(&box2);
		sf1Copy = sf1;
		sf2Copy = sf2;
		{
			//Build trafop
			std::cout << "Building trafoOp" << std::endl;
			matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Zero(2,2);
			trafoMat(0,0) = TypeParam(2);
			trafoMat(1,1) = TypeParam(2);
			vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero(2);

			SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sfTrafo = sf1->affineTransformation(trafoMat, trafoVec);
			//std::shared_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>> sfTrafoPtr = std::shared_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>>(&sfTrafo);
			std::shared_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>> sfTrafoPtr = std::make_shared<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>>(&sfTrafo);
			sfTrafoCopy = sfTrafoPtr;

			EXPECT_TRUE(sfTrafo.getRoot()->getType() == SFNEW_TYPE::TRAFO);
			EXPECT_TRUE(sfTrafo.getRoot()->getChildren().size() == 1);		

			{
				//Build SumOp
				std::cout << "Building sumOp" << std::endl;
				SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sum = sfTrafo.minkowskiSum(*sf2);
				//std::shared_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>> sumPtr = std::shared_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>>(&sum);
				std::shared_ptr<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>> sumPtr = std::make_shared<SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>>(&sum);
				std::cout << "copying shared_ptr" << std::endl;
				sfSumCopy = sumPtr;
				EXPECT_TRUE(sum.getRoot()->getType() == SFNEW_TYPE::SUMOP);
				EXPECT_TRUE(sum.getRoot()->getOriginCount() == sum.getRoot()->getChildren().size());
				std::cout << sum << std::endl;
			}
			//Since SumOp's scope ended, it will be deleted -> sfSumCopy's use_count == 0;
			EXPECT_TRUE(sfSumCopy.expired());
			EXPECT_TRUE(!sfTrafoCopy.expired());
			EXPECT_TRUE(!sf1Copy.expired());
			EXPECT_TRUE(!sf2Copy.expired());
			std::cout << "SumOp expired" << std::endl;
		}	
		EXPECT_TRUE(sfTrafoCopy.expired());
		EXPECT_TRUE(!sf1Copy.expired());
		EXPECT_TRUE(!sf2Copy.expired());	
		std::cout << "TrafoOp expired" << std::endl;
	}
	EXPECT_TRUE(sf1Copy.expired());
	std::cout << "sf1 expired" << std::endl;
	EXPECT_TRUE(sf2Copy.expired());
	std::cout << "sf2 expired" << std::endl;
}

/*
 * Test deletion mechanics. Test cases:
 * 1. Delete supportfunction to leaf (tree stays the same, only sf to leaf vanishes)
 * 2. Delete supportfunction to intermediate node (tree stays the same, only sf to intermediate node vanishes)
 * 3. Delete supportfunction to root (root and its pointer to its children get deleted)
 * 
 * NEEDS COPY ASSIGNMENT
 */
/*
TYPED_TEST(SupportFunctionNewTest, Deletion){

	//Construct leaf nodes
	Box<TypeParam> box1 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(-1)}), Point<TypeParam>({TypeParam(1), TypeParam(2)})));
	Box<TypeParam> box2 (std::make_pair(Point<TypeParam>({TypeParam(0),TypeParam(0)}), Point<TypeParam>({TypeParam(2), TypeParam(2)})));
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf1 = new SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>(&box1);
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sf2 = new SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>(&box2);
	
	//These pointer are needed to check later whether sf2 was deleted
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>* sf1ptr = &sf1;
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>* sf2ptr = &sf2;

	//This pointer is needed to delete sf2
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>* deleteSf2 = &sf2;

	//Build trafop
	matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Identity(2,2);
	vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero(2);

	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sfWithTrafo = new SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>(sf1.affineTransformation(trafoMat, trafoVec));
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>* sfWithTrafoPtr = &sfWithTrafo;
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>* deleteSfWithTrafo = &sfWithTrafo;

	EXPECT_TRUE(sfWithTrafo.getRoot()->getType() == SFNEW_TYPE::TRAFO);
	EXPECT_TRUE(sfWithTrafo.getRoot()->getChildren().size() == 1);
	
	//Build SumOp
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault> sum = new SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>(sfWithTrafo.minkowskiSum(sf2));
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>* sumPtr = &sum;
	SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>* deleteSum = &sum;
	
	EXPECT_TRUE(sum.getRoot()->getType() == SFNEW_TYPE::SUMOP);
	EXPECT_TRUE(sum.getRoot()->getOriginCount() == sum.getRoot()->getChildren().size());	

	std::cout << sum << std::endl;

	//Evaluate
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Zero(2,2);
	directions(0,0) = TypeParam(1);
	directions(1,1) = TypeParam(1);
	//std::cout << "START EVALUATION\n"; 
	std::vector<EvaluationResult<TypeParam>> res = sum.multiEvaluate(directions,true);
	//std::cout << "END EVALUATION\n";
	//std::cout << "Result of Evaluation is:\n";
	//for(auto& eRes : res){
	//	std::cout << eRes << std::endl;
	//}

	//Now delete a leaf
	delete deleteSf2;
	EXPECT_TRUE(sum.getRoot()->getChildren().at(1) != nullptr);
	std::vector<EvaluationResult<TypeParam>> res2 = sum.multiEvaluate(directions,true);
	EXPECT_TRUE(res2.size() == res.size());
	for(int i=0; i < res2.size(); i++){
		EXPECT_TRUE(res2.at(i) == res.at(i));
	}
	EXPECT_TRUE(sf1ptr != nullptr);
	EXPECT_TRUE(sf2ptr != nullptr);
	EXPECT_TRUE(sfWithTrafoPtr != nullptr);
	EXPECT_TRUE(sumPtr != nullptr);

	//Now delete a intermediate node
	delete deleteSfWithTrafo;
	EXPECT_TRUE(sum.getRoot()->getChildren().at(0) != nullptr);
	res2 = sum.multiEvaluate(directions,true);
	EXPECT_TRUE(res2.size() == res.size());
	for(int i=0; i < res2.size(); i++){
		EXPECT_TRUE(res2.at(i) == res.at(i));
	}	
	EXPECT_TRUE(sf1ptr != nullptr);
	EXPECT_TRUE(sf2ptr != nullptr);
	EXPECT_TRUE(sfWithTrafoPtr != nullptr);
	EXPECT_TRUE(sumPtr != nullptr);

	//Now delete root
	delete deleteSum;
	EXPECT_TRUE(sf1ptr != nullptr);
	EXPECT_TRUE(sf2ptr == nullptr);
	EXPECT_TRUE(sfWithTrafoPtr == nullptr);
	EXPECT_TRUE(sumPtr == nullptr);

	//Cleanup
	delete sf1ptr;
	delete sf2ptr;
	delete sfWithTrafoPtr;
	delete sumPtr;
}
*/
