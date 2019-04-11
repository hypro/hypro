/** 
 * TemplatePolyhedronTest.cpp
 *
 * A testing suite for TemplatePolyhedron.h
 *
 * @author Phillip Tse
 * @date 3.4.2019
 */

#include "../defines.h"
#include "../../hypro/representations/GeometricObject.h"
#include "gtest/gtest.h"

using namespace hypro;

template<typename Number>
class TemplatePolyhedronTest : public ::testing::Test
{
protected:

    virtual void SetUp(){

    	mat = matrix_t<Number>::Zero(4,2);
		mat(0,0) = Number(1);
		mat(1,0) = Number(-1);
		mat(2,1) = Number(1);
		mat(3,1) = Number(-1);

		middleVec = 2*vector_t<Number>::Ones(4);
		upleftVec = vector_t<Number>::Zero(4);
		upleftVec << -1, 3, -1, 3;
		uprightVec = vector_t<Number>::Zero(4);
		uprightVec << 3, -1, 3, -1;
		downleftVec = vector_t<Number>::Zero(4);
		downleftVec << -1, 3, 3, -1;
		downrightVec = vector_t<Number>::Zero(4);
		downrightVec << 3, -1, -1, 3;

		middle = TemplatePolyhedron<Number>(mat,middleVec);
		upleft = TemplatePolyhedron<Number>(mat,upleftVec);
		upright = TemplatePolyhedron<Number>(mat,uprightVec);
		downleft = TemplatePolyhedron<Number>(mat,downleftVec);
		downright = TemplatePolyhedron<Number>(mat,downrightVec);
    }
    virtual void TearDown(){}

    matrix_t<Number> mat;			//A square with unit directions in 2d
    vector_t<Number> middleVec;		//for middle
    vector_t<Number> upleftVec;		//for upleft
    vector_t<Number> uprightVec;	//for upright
    vector_t<Number> downleftVec; 	//for downleft
    vector_t<Number> downrightVec;	//for downright

    TemplatePolyhedron<Number> middle;	  	//Middle of square in origin
    TemplatePolyhedron<Number> upleft;	  	//Middle of square in (-1,1)
    TemplatePolyhedron<Number> upright;		//Middle of square in (1,1)	
    TemplatePolyhedron<Number> downleft; 	//Middle of square in (-1,-1)
    TemplatePolyhedron<Number> downright;	//Middle of square in (1,-1)
};

TYPED_TEST(TemplatePolyhedronTest, Constructor){

	//Empty constructor
	TemplatePolyhedron<TypeParam> empty;
	EXPECT_EQ(empty.rGetMatrixPtr(), nullptr);
	EXPECT_EQ(empty.vector(), vector_t<TypeParam>::Zero(0));

	//Define control matrix
	matrix_t<TypeParam> controlMatrix = matrix_t<TypeParam>::Zero(4,2);
	controlMatrix(0,0) = TypeParam(1);
	controlMatrix(1,0) = TypeParam(-1);
	controlMatrix(2,1) = TypeParam(1);
	controlMatrix(3,1) = TypeParam(-1);

	//Regular directions constructor - Unbounded template polyhedra: Should throw
	std::size_t noOfSides = 2;
	vector_t<TypeParam> offset = vector_t<TypeParam>::Ones(noOfSides);
	try {
		TemplatePolyhedron<TypeParam> regular(2, noOfSides, offset);
		FAIL();
	} catch(std::invalid_argument& e){
		//If we get here thats right. Just continue then.
	}

	//Regular directions constructor - Bounded template polyhedra: Should work
	noOfSides = 4;
	offset = vector_t<TypeParam>::Ones(noOfSides);
	TemplatePolyhedron<TypeParam> regular(2, noOfSides, offset);
	EXPECT_EQ(regular.matrix(), controlMatrix);
	EXPECT_EQ(regular.vector(), offset);

	//Matrix Vector constructor - with a different matrix and vector
	matrix_t<TypeParam> differentMatrix = matrix_t<TypeParam>::Zero(3,2);
	differentMatrix(0,0) = TypeParam(1);
	differentMatrix(0,1) = TypeParam(1);
	differentMatrix(1,0) = TypeParam(-1);
	differentMatrix(2,1) = TypeParam(-1);
	vector_t<TypeParam> differentOffset = 2*vector_t<TypeParam>::Ones(3);
	TemplatePolyhedron<TypeParam> matVecTPoly(differentMatrix, differentOffset);
	EXPECT_EQ(matVecTPoly.matrix(), differentMatrix);
	EXPECT_EQ(matVecTPoly.vector(), differentOffset);
	EXPECT_EQ(regular.matrix(), controlMatrix);	

	//Copy constructor
	TemplatePolyhedron<TypeParam> copy(matVecTPoly);
	EXPECT_EQ(copy.matrix(), matVecTPoly.matrix());
	EXPECT_EQ(copy.vector(), matVecTPoly.vector());
	EXPECT_EQ(copy.rGetMatrixPtr(), matVecTPoly.rGetMatrixPtr());

	//Settings constructor
	TemplatePolyhedronT<TypeParam,Converter<TypeParam>,TemplatePolyhedronDifferent> setting(matVecTPoly);
	EXPECT_EQ(setting.matrix(), matVecTPoly.matrix());
	EXPECT_EQ(setting.vector(), matVecTPoly.vector());
	EXPECT_EQ(setting.rGetMatrixPtr(), matVecTPoly.rGetMatrixPtr());

	//Move constructor
	TemplatePolyhedron<TypeParam> move(std::move(matVecTPoly));
	EXPECT_EQ(move.matrix(), differentMatrix);
	EXPECT_EQ(move.vector(), differentOffset);
	EXPECT_EQ(matVecTPoly.rGetMatrixPtr(), nullptr);
	EXPECT_EQ(move.rGetMatrixPtr(), copy.rGetMatrixPtr());
	EXPECT_EQ(move.rGetMatrixPtr(), setting.rGetMatrixPtr());
}


TYPED_TEST(TemplatePolyhedronTest, Containment){

	//Point of a different dimension - should fail
	try {
		Point<TypeParam> p0 = Point<TypeParam>::Zero(3);
		this->middle.contains(p0);
		FAIL();
	}catch(std::invalid_argument& e){
		//Is right if it fails, in that case continue
	}
	
	//Point that lies within middle template poly
	Point<TypeParam> p1 = Point<TypeParam>::Zero(2);
	EXPECT_TRUE(this->middle.contains(p1));

	//Point on the edge
	Point<TypeParam> p2({TypeParam(0), TypeParam(2)});
	EXPECT_TRUE(this->middle.contains(p2));	

	//Point outside
	Point<TypeParam> p3({TypeParam(1.7234), TypeParam(2.1)});
	EXPECT_TRUE(!(this->middle.contains(p3)));	

	//Template Poly in a different dimension - should fail
	matrix_t<TypeParam> diffDimMat = matrix_t<TypeParam>::Identity(3,3);
	vector_t<TypeParam> diffDimVec = vector_t<TypeParam>::Ones(3);
	try {
		TemplatePolyhedron<TypeParam> t1(diffDimMat, diffDimVec);
		this->middle.contains(t1);
		FAIL();
	} catch(std::invalid_argument& e){
		//Is right if it fails, in that case continue	
	}

	//Template poly that lies fully within middle 
	vector_t<TypeParam> withinVec = vector_t<TypeParam>::Zero(2);
	TemplatePolyhedron<TypeParam> t2(this->mat, withinVec);
	EXPECT_TRUE(this->middle.contains(t2)); 

	//Template poly that lies partially within middle
	EXPECT_TRUE(this->middle.contains(this->upright)); //???

	//Template poly that lies fully outside middle
 	vector_t<TypeParam> outsideVec = 100*vector_t<TypeParam>::Ones(2);
 	TemplatePolyhedron<TypeParam> t3(this->mat, outsideVec);
 	EXPECT_TRUE(!(this->middle.contains(t3)));
}

TYPED_TEST(TemplatePolyhedronTest, Intersect){

	//Wish result poly after intersection between middle and upright
	vector_t<TypeParam> resVec = vector_t<TypeParam>::Zero(4);
	resVec << 2,-1,2,-1;
	TemplatePolyhedron<TypeParam> resMiddleUpright(this->mat, resVec);

	//Intersect middle and upleft - Should result in resMiddleUpright
	EXPECT_EQ(this->middle.intersect(this->upright), resMiddleUpright);

	//Intersect upleft and upright - Should be empty
	//EXPECT_EQ(this->upright.intersect(this->upleft), TemplatePolyhedron<TypeParam>());

}

TYPED_TEST(TemplatePolyhedronTest, Union){

}

