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
		infeas = TemplatePolyhedron<Number>(mat,-0.5*middleVec);
    }
    virtual void TearDown(){}

    matrix_t<Number> mat;			//A square with unit directions in 2d
    vector_t<Number> middleVec;		//for middle
    vector_t<Number> upleftVec;		//for upleft
    vector_t<Number> uprightVec;	//for upright
    vector_t<Number> downleftVec; 	//for downleft
    vector_t<Number> downrightVec;	//for downright

    TemplatePolyhedron<Number> empty;		//An empty tpoly
    TemplatePolyhedron<Number> middle;	  	//Middle of square in origin with side length 4
    TemplatePolyhedron<Number> upleft;	  	//Middle of square in (-2,2) with side length 2
    TemplatePolyhedron<Number> upright;		//Middle of square in (2,2)	with side length 2
    TemplatePolyhedron<Number> downleft; 	//Middle of square in (-2,-2) with side length 2
    TemplatePolyhedron<Number> downright;	//Middle of square in (2,-2) with side length 2
    TemplatePolyhedron<Number> infeas;		//Middle of square in origin with side length 1 but with inverted directions
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

	//Infeasible TPoly
	EXPECT_TRUE(this->infeas.empty());
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

	//Infeas Poly - TODO
}

TYPED_TEST(TemplatePolyhedronTest, Supremum){

	//Empty TPoly
	EXPECT_EQ(this->empty.supremum(), TypeParam(0));
	
	//Normal TPoly
	EXPECT_EQ(this->middle.supremum(), TypeParam(2));
	EXPECT_EQ(this->upright.supremum(), TypeParam(3));

	//Infeas TPoly - TODO
	EXPECT_EQ(this->infeas.supremum(), TypeParam(0));
}

TYPED_TEST(TemplatePolyhedronTest, Evaluation){

	vector_t<TypeParam> up = vector_t<TypeParam>::Zero(2);
	up(1) = TypeParam(1);

	//One direction evaluation - Empty TPoly
	EvaluationResult<TypeParam> res1 = this->empty.evaluate(up, true);
	EXPECT_EQ(res1.errorCode, SOLUTION::INFTY);
	EXPECT_EQ(res1.supportValue, 0);
	EXPECT_EQ(res1.optimumValue, vector_t<TypeParam>::Zero(0));

	//One direction evaluation - Normal TPoly
	EvaluationResult<TypeParam> res2 = this->middle.evaluate(up, true);
	EXPECT_EQ(res2.errorCode, SOLUTION::FEAS);
	EXPECT_EQ(res2.supportValue, 2);
	EXPECT_EQ(res2.optimumValue, 2*up);	

	//One direction evaluation - Infeasible TPoly
	//TemplatePolyhedron<TypeParam> infeas(this->mat, -0.5*vector_t<TypeParam>::Ones(4));
	//EvaluationResult<TypeParam> res3 = infeas.evaluate(up, true);
	//EXPECT_EQ(res3.errorCode, SOLUTION::INFEAS);	//Test says INFTY?
	//EXPECT_EQ(res3.supportValue, 0);
	//EXPECT_EQ(res3.optimumValue, vector_t<TypeParam>::Zero(0));	

	matrix_t<TypeParam> allcorners = matrix_t<TypeParam>::Zero(4,2);
	allcorners <<	1, 1,
					1, -1,
					-1, 1,
					-1, -1;

	//Multiple direction evaluation - Empty TPoly
	std::vector<EvaluationResult<TypeParam>> res4 = this->empty.multiEvaluate(allcorners, true);
	EXPECT_EQ(res4.size(), std::size_t(0));

	//Multiple direction evaluation - Normal TPoly
	res4 = this->middle.multiEvaluate(allcorners, true);
	EXPECT_EQ(res4.size(), std::size_t(4));	
	for(const auto& elem : res4){
		EXPECT_EQ(elem.errorCode, SOLUTION::FEAS);
		EXPECT_EQ(elem.supportValue, TypeParam(4));
	}

	//Multiple direction evaluation - Infeasible TPoly
	std::vector<EvaluationResult<TypeParam>> res5 = this->infeas.multiEvaluate(allcorners, true);
	EXPECT_EQ(res5.size(), std::size_t(0));
}

TYPED_TEST(TemplatePolyhedronTest, RemoveRedundancy){

	//Empty TPoly
	this->empty.removeRedundancy();

	//TPoly with no redundancy
	auto matRows = this->middle.matrix().rows();
	auto matCols = this->middle.matrix().cols();
	auto vecRows = this->middle.vector().rows();
	this->middle.removeRedundancy();
	EXPECT_EQ(matRows, this->middle.matrix().rows());
	EXPECT_EQ(matCols, this->middle.matrix().cols());
	EXPECT_EQ(vecRows, this->middle.vector().rows());

	//TPoly with 1 redundant constraint
	matrix_t<TypeParam> withOneRedundantMat = matrix_t<TypeParam>::Zero(5,2);
	vector_t<TypeParam> withOneRedundantVec = vector_t<TypeParam>::Zero(5);
	for(int i=0; i < this->mat.rows(); i++){
		for(int j = 0; j < this->mat.cols(); j++){
			withOneRedundantMat(i,j) = this->mat(i,j);
		}
		withOneRedundantVec(i) = this->middleVec(i);
	}
	withOneRedundantMat(4,0) = TypeParam(4);
	withOneRedundantVec(4) = TypeParam(4);
	TemplatePolyhedron<TypeParam> withOneRedundant(withOneRedundantMat, withOneRedundantVec);
	withOneRedundant.removeRedundancy();
	EXPECT_EQ(withOneRedundant.matrix().rows(), 4);
	EXPECT_EQ(withOneRedundant.vector().rows(), 4);

	//Multiple redundant constraints
}
/*
TYPED_TEST(TemplatePolyhedronTest, AffineTransformation){

	//Define matrix and vector for linear and affine transformation
	matrix_t<TypeParam> transMat = 3*matrix_t<TypeParam>::Identity(2,2);
	vector_t<TypeParam> transVec = 2*vector_t<TypeParam>::Ones(2);

	//Empty TPoly
	EXPECT_EQ(this->empty, this->empty.linearTransformation(transMat));
	EXPECT_EQ(this->empty, this->empty.affineTransformation(transMat, transVec));
	
	//Normal TPoly 
	auto res1 = this->middle.linearTransformation(transMat);
	EXPECT_EQ(res1.matrix(), this->mat);
	EXPECT_EQ(res1.vector(), 3*this->middleVec);
	auto res2 = this->middle.affineTransformation(transMat,transVec);
	vector_t<TypeParam> controlVec;
	controlVec << 7, 5, 7, 5;
	EXPECT_EQ(res2.matrix(), this->mat);
	EXPECT_EQ(res2.vector(), controlVec);
}
*/

TYPED_TEST(TemplatePolyhedronTest, MinkowskiSum){

	auto res1 = this->middle.minkowskiSum(this->upright);
	vector_t<TypeParam> controlVec = vector_t<TypeParam>::Zero(4);
	controlVec << 5,1,5,1;
	auto res1Vertices = res1.vertices();
	EXPECT_EQ(res1.vector(), controlVec);
	EXPECT_EQ(res1Vertices.size(), 4);
	EXPECT_TRUE(std::find(res1Vertices.begin(), res1Vertices.end(), Point<TypeParam>({TypeParam(5),TypeParam(5)})) != res1Vertices.end());
	EXPECT_TRUE(std::find(res1Vertices.begin(), res1Vertices.end(), Point<TypeParam>({TypeParam(5),TypeParam(-1)})) != res1Vertices.end());
	EXPECT_TRUE(std::find(res1Vertices.begin(), res1Vertices.end(), Point<TypeParam>({TypeParam(-1),TypeParam(5)})) != res1Vertices.end());
	EXPECT_TRUE(std::find(res1Vertices.begin(), res1Vertices.end(), Point<TypeParam>({TypeParam(-1),TypeParam(-1)})) != res1Vertices.end());
}

TYPED_TEST(TemplatePolyhedronTest, Intersect){

	//Wish result poly after intersection between middle and upright
	vector_t<TypeParam> resVec = vector_t<TypeParam>::Zero(4);
	resVec << 2,-1,2,-1;
	TemplatePolyhedron<TypeParam> resMiddleUpright(this->mat, resVec);

	//Intersect middle and upright - Should result in resMiddleUpright
	EXPECT_EQ(this->middle.intersect(this->upright), resMiddleUpright);

	//Intersect upleft and upright - Should be empty
	EXPECT_TRUE(this->upright.intersect(this->upleft).empty());

	//Intersect middle and empty - Should result in middle
	EXPECT_EQ(this->middle.intersect(this->empty), this->middle);

	//Intersect upleft and infeas - should result in upleft
	EXPECT_EQ(this->upleft.intersect(this->infeas), this->upleft);

	//Intersect infeas and empty - should result in empty
	EXPECT_EQ(this->infeas.intersect(this->empty), this->empty);
}

TYPED_TEST(TemplatePolyhedronTest, Union){

	//Wish result poly after unification between middle and upright
	vector_t<TypeParam> resVec = vector_t<TypeParam>::Zero(4);
	resVec << 3,2,3,2;
	TemplatePolyhedron<TypeParam> resMiddleUpright(this->mat, resVec);	

	//Unite middle and upright - Should result in resMiddleUpright
	EXPECT_EQ(this->middle.unite(this->upright), resMiddleUpright);

	//Unite upleft and upright - Should be empty
	EXPECT_TRUE(this->upright.unite(this->upleft).empty());

	//Unite middle and empty - Should be middle
	EXPECT_EQ(this->middle.unite(this->empty), this->middle);

	//Unite upleft and infeas - should be upleft
	EXPECT_EQ(this->upleft.unite(this->infeas), this->upleft);

	//Unite infeas and empty - should be empty
	EXPECT_TRUE(this->infeas.unite(this->empty).empty());

	//Unite upright, middle and downleft - should work
	vector_t<TypeParam> resVec2 = vector_t<TypeParam>::Zero(4);
	resVec2 << 3,3,3,3;
	TemplatePolyhedron<TypeParam> multiUnite(this->mat, resVec2);
	std::vector<TemplatePolyhedron<TypeParam>> uniteWith;
	uniteWith.push_back(this->middle);
	uniteWith.push_back(this->downleft);
	EXPECT_EQ(this->upright.unite(uniteWith), multiUnite);

	//Unite upright, middle and infeas - should result in resMiddleUpright
	uniteWith.pop_back();
	uniteWith.push_back(this->infeas);
	EXPECT_EQ(this->upright.unite(uniteWith), resMiddleUpright);

}
