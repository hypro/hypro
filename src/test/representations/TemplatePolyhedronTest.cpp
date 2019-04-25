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

    TemplatePolyhedron<Number> empty;		//An empty tpoly
    TemplatePolyhedron<Number> middle;	  	//Middle of square in origin with side length 2
    TemplatePolyhedron<Number> upleft;	  	//Middle of square in (-1,1) with side length 2
    TemplatePolyhedron<Number> upright;		//Middle of square in (1,1)	with side length 2
    TemplatePolyhedron<Number> downleft; 	//Middle of square in (-1,-1) with side length 2
    TemplatePolyhedron<Number> downright;	//Middle of square in (1,-1) with side length 2
};

TYPED_TEST(TemplatePolyhedronTest, Constructor){

	//Empty constructor
	EXPECT_EQ(this->empty.rGetMatrixPtr(), nullptr);
	EXPECT_EQ(this->empty.vector(), vector_t<TypeParam>::Zero(0));
	EXPECT_EQ(this->empty.getOptimizer().matrix(), matrix_t<TypeParam>());
	EXPECT_EQ(this->empty.getOptimizer().vector(), vector_t<TypeParam>());

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
	EXPECT_EQ(regular.getOptimizer().matrix(), controlMatrix);
	EXPECT_EQ(regular.getOptimizer().vector(), offset);

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
	EXPECT_EQ(matVecTPoly.getOptimizer().matrix(), differentMatrix);
	EXPECT_EQ(matVecTPoly.getOptimizer().vector(), differentOffset);

	//Copy constructor
	TemplatePolyhedron<TypeParam> copy(matVecTPoly);
	EXPECT_EQ(copy.matrix(), matVecTPoly.matrix());
	EXPECT_EQ(copy.vector(), matVecTPoly.vector());
	EXPECT_EQ(copy.rGetMatrixPtr(), matVecTPoly.rGetMatrixPtr());
	EXPECT_EQ(copy.getOptimizer().matrix(), matVecTPoly.matrix());
	EXPECT_EQ(copy.getOptimizer().vector(), matVecTPoly.vector());

	//Settings constructor
	TemplatePolyhedronT<TypeParam,Converter<TypeParam>,TemplatePolyhedronDifferent> setting(matVecTPoly);
	EXPECT_EQ(setting.matrix(), matVecTPoly.matrix());
	EXPECT_EQ(setting.vector(), matVecTPoly.vector());
	EXPECT_EQ(setting.rGetMatrixPtr(), matVecTPoly.rGetMatrixPtr());
	EXPECT_EQ(setting.getOptimizer().matrix(), matVecTPoly.matrix());
	EXPECT_EQ(setting.getOptimizer().vector(), matVecTPoly.vector());

	//Move constructor
	TemplatePolyhedron<TypeParam> move(std::move(matVecTPoly));
	EXPECT_EQ(move.matrix(), differentMatrix);
	EXPECT_EQ(move.vector(), differentOffset);
	EXPECT_EQ(matVecTPoly.rGetMatrixPtr(), nullptr);
	EXPECT_EQ(move.rGetMatrixPtr(), copy.rGetMatrixPtr());
	EXPECT_EQ(move.rGetMatrixPtr(), setting.rGetMatrixPtr());
	EXPECT_EQ(move.getOptimizer().matrix(), differentMatrix);
	EXPECT_EQ(move.getOptimizer().vector(), differentOffset);
	//Somehow test whether GLP instance of matVecTPoly has been cleaned
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
	Point<TypeParam> p3({TypeParam(1.1234), TypeParam(4.1)});
	EXPECT_FALSE(this->middle.contains(p3));	

	//Empty poly does not contain any points, not even the empty point
	EXPECT_FALSE(this->empty.contains(p1));
	EXPECT_FALSE(this->empty.contains(p2));
	EXPECT_FALSE(this->empty.contains(Point<TypeParam>()));

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
	vector_t<TypeParam> withinVec = 0.5*vector_t<TypeParam>::Ones(4);
	TemplatePolyhedron<TypeParam> t2(this->mat, withinVec);
	EXPECT_TRUE(this->middle.contains(t2)); 

	//Template poly that lies partially within middle - False since contains() is only true for full containment
	EXPECT_FALSE(this->middle.contains(this->upright)); 

	//Template poly that lies fully outside middle
	vector_t<TypeParam> outsideVec = 100*vector_t<TypeParam>::Ones(4);
 	TemplatePolyhedron<TypeParam> t3(this->mat, outsideVec);
 	EXPECT_FALSE(this->middle.contains(t3));

 	//Template poly that is like t2 (fully within middle), but its directions are inversed - Unbounded poly test, check later
 	//vector_t<TypeParam> inverseWithinVec = -1*withinVec;
	//TemplatePolyhedron<TypeParam> t4(this->mat, inverseWithinVec);
	//EXPECT_FALSE(t4.contains(p1));
	//EXPECT_TRUE(t4.contains(p3));
	//EXPECT_FALSE(this->middle.contains(t4)); 	
}

TYPED_TEST(TemplatePolyhedronTest, Emptiness){
	
	//Empty TPoly
	EXPECT_TRUE(this->empty.empty());

	//Normal TPoly
	EXPECT_FALSE(this->middle.empty());

	//Point TPoly
	TemplatePolyhedron<TypeParam> pointTPoly(this->mat, vector_t<TypeParam>::Zero(4));
	EXPECT_FALSE(pointTPoly.empty());

	//Unbounded TPoly
	//TemplatePolyhedron<TypeParam> unbound(this->mat, -0.5*vector_t<TypeParam>::Ones(4));
	//EXPECT_FALSE(unbound.empty());
}

TYPED_TEST(TemplatePolyhedronTest, Vertices){

	//Empty TPoly
	EXPECT_EQ(this->empty.vertices(), std::vector<Point<TypeParam>>());

	//Normal TPoly
	auto vert = this->middle.vertices();
	EXPECT_EQ(vert.size(), std::size_t(4));
	EXPECT_TRUE(std::find(vert.begin(), vert.end(), Point<TypeParam>({TypeParam(2), TypeParam(2)})) != vert.end());
	EXPECT_TRUE(std::find(vert.begin(), vert.end(), Point<TypeParam>({TypeParam(2), TypeParam(-2)})) != vert.end());
	EXPECT_TRUE(std::find(vert.begin(), vert.end(), Point<TypeParam>({TypeParam(-2), TypeParam(2)})) != vert.end());
	EXPECT_TRUE(std::find(vert.begin(), vert.end(), Point<TypeParam>({TypeParam(-2), TypeParam(-2)})) != vert.end());

	//Point TPoly
	TemplatePolyhedron<TypeParam> pointTPoly(this->mat, vector_t<TypeParam>::Zero(4));
	EXPECT_EQ(pointTPoly.vertices().size(), std::size_t(1));
	EXPECT_EQ(pointTPoly.vertices().front(), Point<TypeParam>::Zero(2));

	//Unbound Poly - TODO
}

TYPED_TEST(TemplatePolyhedronTest, Supremum){

	//Empty TPoly
	std::cout << "1" << std::endl;
	EXPECT_EQ(this->empty.supremum(), TypeParam(0));
	
	//Normal TPoly
	std::cout << "2" << std::endl;
	EXPECT_EQ(this->middle.supremum(), TypeParam(2));
	std::cout << "3" << std::endl;
	EXPECT_EQ(this->upright.supremum(), TypeParam(3));
	std::cout << "4" << std::endl;

	//Unbound TPoly - TODO 
}

/*
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

*/