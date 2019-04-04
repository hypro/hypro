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

    	mat = matrix_t<TypeParam>::Zero(constraintSize,dim);
		mat(0,0) = TypeParam(1);
		mat(1,0) = TypeParam(-1);
		mat(2,1) = TypeParam(1);
		mat(3,1) = TypeParam(-1);

		middle = vector_t<TypeParam>::Ones(constraintSize);
		//the other vecs upleft
		//the other vecs upright
		//the other vecs downleft
		//the other vecs downright

		tpoly1 = TemplatePolyhedron<TypeParam>(mat,vec1);
    }
    virtual void TearDown(){}

    std::size_t dim = 2;
	std::size_t constraintSize = 4;

    matrix_t<TypeParam> mat;	//A square with unit directions in 2d
    vector_t<TypeParam> vec1;	//for middle
    vector_t<TypeParam> vec2;	//for upleft
    vector_t<TypeParam> vec3;	//for upright
    vector_t<TypeParam> vec4;	//for downleft
    vector_t<TypeParam> vec5;	//for downright

    TemplatePolyhedron<TypeParam> middle;	  	//Middle of square in origin
    TemplatePolyhedron<TypeParam> upleft;	  	//Middle of square in (-1,1)
    TemplatePolyhedron<TypeParam> upright;		//Middle of square in (1,1)	
    TemplatePolyhedron<TypeParam> downleft; 	//Middle of square in (-1,-1)
    TemplatePolyhedron<TypeParam> downright;	//Middle of square in (1,-1)
};

TYPED_TEST(TemplatePolyhedronTest, Constructor){

	//Empty constructor
	TemplatePolyhedron<TypeParam> empty;
	EXPECT_EQ(empty.matrix(), matrix_t<TypeParam>::Zero(0,0));
	EXPECT_EQ(empty.vector(), vector_t<TypeParam>::Zero(0));

	//Define control matrix
	matrix_t<TypeParam> controlMatrix = matrix_t<TypeParam>::Zero(constraintSize,dim);
	controlMatrix(0,0) = TypeParam(1);
	controlMatrix(1,0) = TypeParam(-1);
	controlMatrix(2,1) = TypeParam(1);
	controlMatrix(3,1) = TypeParam(-1);

	//Regular directions constructor - Unbounded template polyhedra: Should throw
	std::size_t noOfSides = 2;
	vector_t<TypeParam> offset = vector_t<TypeParam>::Ones(noOfSides);
	try {
		TemplatePolyhedron<TypeParam> regular(dim, noOfSides, offset);
		FAIL();
	} catch(std::invalid_argument& e){
		//If we get here thats right. Just continue then.
	}

	//Regular directions constructor - Bounded template polyhedra: Should work
	noOfSides = constraintSize;
	offset = vector_t<TypeParam>::Ones(noOfSides);
	TemplatePolyhedron<TypeParam> regular(dim, noOfSides, offset);
	EXPECT_EQ(regular.matrix(), controlMatrix);
	EXPECT_EQ(empty.matrix(), controlMatrix);
	EXPECT_EQ(regular.vector(), offset);

	//Matrix Vector constructor - with a different matrix and vector: matrix should still be controlMatrix
	//vector is not changed, since its size does not comply with the #rows of controlMatrix
	matrix_t<TypeParam> differentMatrix = matrix_t<TypeParam>::Zero(constraintSize-1,dim);
	differentMatrix(0,0) = TypeParam(1);
	differentMatrix(0,1) = TypeParam(1);
	differentMatrix(1,0) = TypeParam(-1);
	differentMatrix(2,1) = TypeParam(-1);
	vector_t<TypeParam> differentOffset = 2*vector_t<TypeParam>::Ones(constraintSize-1);
	TemplatePolyhedron<TypeParam> matVecTPoly(differentMatrix, differentOffset);
	EXPECT_EQ(matVecTPoly.matrix(), controlMatrix);
	EXPECT_EQ(regular.matrix(), controlMatrix);
	EXPECT_EQ(empty.matrix(), controlMatrix);	
	EXPECT_EQ(matVecTPoly.vector(), offset);

	//Vector constructor: Should work
	vector_t<TypeParam> functioningOffset = 3*vector_t<TypeParam>::Ones(constraintSize);
	TemplatePolyhedron<TypeParam> vecTPoly(functioningOffset);
	EXPECT_EQ(vecTPoly.matrix(), matVecTPoly.matrix());
	EXPECT_EQ(vecTPoly.vector(), functioningOffset);

	//Copy constructor
	TemplatePolyhedron<TypeParam> copy(vecTPoly);
	EXPECT_EQ(copy.matrix(), vecTPoly.matrix());
	EXPECT_EQ(copy.vector(), vecTPoly.vector());

	//Move constructor
	TemplatePolyhedron<TypeParam> move(std::move(vecTPoly));
	EXPECT_EQ(move.matrix(), vecTPoly.matrix());
	EXPECT_EQ(move.vector(), vecTPoly.vector());

	//Settings constructor
	TemplatePolyhedronT<TypeParam,Converter<TypeParam>,TemplatePolyhedronDifferent> setting(vecTPoly);
	EXPECT_EQ(setting.matrix(), vecTPoly.matrix());
	EXPECT_EQ(setting.vector(), vecTPoly.vector());	

}

TYPED_TEST(TemplatePolyhedronTest, Intersect){

}

TYPED_TEST(TemplatePolyhedronTest, Containment){

}

TYPED_TEST(TemplatePolyhedronTest, Union){

}

