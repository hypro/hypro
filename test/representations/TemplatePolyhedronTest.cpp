/**
 * TemplatePolyhedronTest.cpp
 *
 * A testing suite for TemplatePolyhedron.h
 *
 * @author Phillip Tse
 * @date 3.4.2019
 */

#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/representations/GeometricObjectBase.h>

using namespace hypro;

template <typename Number>
class TemplatePolyhedronTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		mat = matrix_t<Number>::Zero( 4, 2 );
		mat( 0, 0 ) = Number( 1 );
		mat( 1, 0 ) = Number( -1 );
		mat( 2, 1 ) = Number( 1 );
		mat( 3, 1 ) = Number( -1 );

		triangleMat = matrix_t<Number>::Zero( 3, 2 );
		triangleMat << -1, 2, 1, 2, 0, -1;
		triangleVec = vector_t<Number>::Zero( 3 );
		triangleVec << 0, 2, 0;

		middleVec = 2 * vector_t<Number>::Ones( 4 );
		upleftVec = vector_t<Number>::Zero( 4 );
		upleftVec << -1, 3, 3, -1;
		uprightVec = vector_t<Number>::Zero( 4 );
		uprightVec << 3, -1, 3, -1;
		downleftVec = vector_t<Number>::Zero( 4 );
		downleftVec << -1, 3, -1, 3;
		downrightVec = vector_t<Number>::Zero( 4 );
		downrightVec << 3, -1, -1, 3;

		middle = TemplatePolyhedron<Number>( mat, middleVec );
		upleft = TemplatePolyhedron<Number>( mat, upleftVec );
		upright = TemplatePolyhedron<Number>( mat, uprightVec );
		downleft = TemplatePolyhedron<Number>( mat, downleftVec );
		downright = TemplatePolyhedron<Number>( mat, downrightVec );
		infeas = TemplatePolyhedron<Number>( mat, -0.5 * middleVec );
		triangle = TemplatePolyhedron<Number>( triangleMat, triangleVec );
	}
	virtual void TearDown() {}

	matrix_t<Number> mat;			// A square with unit directions in 2d
	vector_t<Number> middleVec;		// for middle
	vector_t<Number> upleftVec;		// for upleft
	vector_t<Number> uprightVec;	// for upright
	vector_t<Number> downleftVec;	// for downleft
	vector_t<Number> downrightVec;	// for downright

	TemplatePolyhedron<Number> empty;	   // An empty tpoly
	TemplatePolyhedron<Number> middle;	   // Middle of square in origin with side length 4
	TemplatePolyhedron<Number> upleft;	   // Middle of square in (-2,2) with side length 2
	TemplatePolyhedron<Number> upright;	   // Middle of square in (2,2)	with side length 2
	TemplatePolyhedron<Number> downleft;   // Middle of square in (-2,-2) with side length 2
	TemplatePolyhedron<Number> downright;  // Middle of square in (2,-2) with side length 2
	TemplatePolyhedron<Number> infeas;	   // Middle of square in origin with side length 1 but with inverted directions

	matrix_t<Number> triangleMat;
	vector_t<Number> triangleVec;
	TemplatePolyhedron<Number> triangle;  // Triangle with points (0,0),(1,0.5)(2,0)
};

TYPED_TEST( TemplatePolyhedronTest, Constructor ) {
	// Empty constructor
	EXPECT_EQ( this->empty.rGetMatrixPtr(), nullptr );
	EXPECT_EQ( this->empty.vector(), vector_t<TypeParam>::Zero( 0 ) );
	EXPECT_EQ( this->empty.getOptimizer().matrix(), matrix_t<TypeParam>() );
	EXPECT_EQ( this->empty.getOptimizer().vector(), vector_t<TypeParam>() );

	// Define control matrix
	matrix_t<TypeParam> controlMatrix = matrix_t<TypeParam>::Zero( 4, 2 );
	controlMatrix( 0, 0 ) = TypeParam( 1 );
	controlMatrix( 1, 0 ) = TypeParam( -1 );
	controlMatrix( 2, 1 ) = TypeParam( 1 );
	controlMatrix( 3, 1 ) = TypeParam( -1 );

	// Regular directions constructor - Unbounded template polyhedra: Should work
	std::size_t noOfSides = 2;
	vector_t<TypeParam> offset = vector_t<TypeParam>::Ones( noOfSides );
	TemplatePolyhedron<TypeParam> regular( 2, noOfSides, offset );

	// Regular directions constructor - Bounded template polyhedra: Should work
	noOfSides = 4;
	offset = vector_t<TypeParam>::Ones( noOfSides );
	regular = TemplatePolyhedron<TypeParam>( 2, noOfSides, offset );
	EXPECT_EQ( regular.matrix(), controlMatrix );
	EXPECT_EQ( regular.vector(), offset );
	EXPECT_EQ( regular.getOptimizer().matrix(), controlMatrix );
	EXPECT_EQ( regular.getOptimizer().vector(), offset );

	// Matrix Vector constructor - with a different matrix and vector
	matrix_t<TypeParam> differentMatrix = matrix_t<TypeParam>::Zero( 3, 2 );
	differentMatrix( 0, 0 ) = TypeParam( 1 );
	differentMatrix( 0, 1 ) = TypeParam( 1 );
	differentMatrix( 1, 0 ) = TypeParam( -1 );
	differentMatrix( 2, 1 ) = TypeParam( -1 );
	vector_t<TypeParam> differentOffset = 2 * vector_t<TypeParam>::Ones( 3 );
	TemplatePolyhedron<TypeParam> matVecTPoly( differentMatrix, differentOffset );
	EXPECT_EQ( matVecTPoly.matrix(), differentMatrix );
	EXPECT_EQ( matVecTPoly.vector(), differentOffset );
	EXPECT_EQ( regular.matrix(), controlMatrix );
	EXPECT_EQ( matVecTPoly.getOptimizer().matrix(), differentMatrix );
	EXPECT_EQ( matVecTPoly.getOptimizer().vector(), differentOffset );

	// Vector of matrices and vectors constructor
	auto pair1 = std::make_pair( controlMatrix, offset );
	auto pair2 = std::make_pair( differentMatrix, differentOffset );
	TemplatePolyhedron<TypeParam> templ(
		  std::vector<std::pair<matrix_t<TypeParam>, vector_t<TypeParam>>>{ pair1, pair2 } );
	matrix_t<TypeParam> controlMatrix2( controlMatrix.rows() + differentMatrix.rows(), controlMatrix.cols() );
	controlMatrix2.block( 0, 0, controlMatrix.rows(), controlMatrix.cols() ) = controlMatrix;
	controlMatrix2.block( controlMatrix.rows(), 0, differentMatrix.rows(), differentMatrix.cols() ) = differentMatrix;
	vector_t<TypeParam> controlVector2( offset.rows() + differentOffset.rows(), offset.cols() );
	controlVector2.block( 0, 0, offset.rows(), 1 ) = offset;
	controlVector2.block( offset.rows(), 0, differentOffset.rows(), 1 ) = differentOffset;
	EXPECT_EQ( templ.matrix(), controlMatrix2 );
	EXPECT_EQ( templ.vector(), controlVector2 );
	EXPECT_EQ( templ.getOptimizer().matrix(), controlMatrix2 );
	EXPECT_EQ( templ.getOptimizer().vector(), controlVector2 );

	// Copy constructor
	TemplatePolyhedron<TypeParam> copy( matVecTPoly );
	EXPECT_EQ( copy.matrix(), matVecTPoly.matrix() );
	EXPECT_EQ( copy.vector(), matVecTPoly.vector() );
	EXPECT_EQ( copy.rGetMatrixPtr(), matVecTPoly.rGetMatrixPtr() );
	EXPECT_EQ( copy.getOptimizer().matrix(), matVecTPoly.matrix() );
	EXPECT_EQ( copy.getOptimizer().vector(), matVecTPoly.vector() );

	// Settings constructor
	TemplatePolyhedronT<TypeParam, Converter<TypeParam>, OctagonShape> setting( matVecTPoly );
	EXPECT_EQ( setting.matrix(), matVecTPoly.matrix() );
	EXPECT_EQ( setting.vector(), matVecTPoly.vector() );
	EXPECT_EQ( setting.rGetMatrixPtr(), matVecTPoly.rGetMatrixPtr() );
	EXPECT_EQ( setting.getOptimizer().matrix(), matVecTPoly.matrix() );
	EXPECT_EQ( setting.getOptimizer().vector(), matVecTPoly.vector() );

	// Move constructor
	TemplatePolyhedron<TypeParam> move( std::move( matVecTPoly ) );
	EXPECT_EQ( move.matrix(), differentMatrix );
	EXPECT_EQ( move.vector(), differentOffset );
	EXPECT_EQ( matVecTPoly.rGetMatrixPtr(), nullptr );
	EXPECT_EQ( move.rGetMatrixPtr(), copy.rGetMatrixPtr() );
	EXPECT_EQ( move.rGetMatrixPtr(), setting.rGetMatrixPtr() );
	EXPECT_EQ( move.getOptimizer().matrix(), differentMatrix );
	EXPECT_EQ( move.getOptimizer().vector(), differentOffset );
	// Somehow test whether GLP instance of matVecTPoly has been cleaned
}

TYPED_TEST( TemplatePolyhedronTest, Containment ) {
	// Point of a different dimension - should fail
	Point<TypeParam> p0 = Point<TypeParam>::Zero( 3 );
	EXPECT_THROW( this->middle.contains( p0 ), std::invalid_argument );

	// Point that lies within middle template poly
	Point<TypeParam> p1 = Point<TypeParam>::Zero( 2 );
	EXPECT_TRUE( this->middle.contains( p1 ) );

	// Point on the edge
	Point<TypeParam> p2( { TypeParam( 0 ), TypeParam( 2 ) } );
	EXPECT_TRUE( this->middle.contains( p2 ) );

	// Point outside
	Point<TypeParam> p3( { TypeParam( 1.1234 ), TypeParam( 4.1 ) } );
	EXPECT_FALSE( this->middle.contains( p3 ) );

	// Empty poly does not contain any points, not even the empty point
	EXPECT_FALSE( this->empty.contains( p1 ) );
	EXPECT_FALSE( this->empty.contains( p2 ) );
	EXPECT_FALSE( this->empty.contains( Point<TypeParam>() ) );

	// Template Poly in a different dimension - should fail
	matrix_t<TypeParam> diffDimMat = matrix_t<TypeParam>::Identity( 3, 3 );
	vector_t<TypeParam> diffDimVec = vector_t<TypeParam>::Ones( 3 );
	TemplatePolyhedron<TypeParam> t1( diffDimMat, diffDimVec );
	EXPECT_THROW( this->middle.contains( t1 ), std::invalid_argument );

	// Template poly that lies fully within middle
	vector_t<TypeParam> withinVec = 0.5 * vector_t<TypeParam>::Ones( 4 );
	TemplatePolyhedron<TypeParam> t2( this->mat, withinVec );
	EXPECT_TRUE( this->middle.contains( t2 ) );

	// Template poly that lies partially within middle - False since contains() is only true for full containment
	EXPECT_FALSE( this->middle.contains( this->upright ) );

	// Template poly that lies fully outside middle
	vector_t<TypeParam> outsideVec = 100 * vector_t<TypeParam>::Ones( 4 );
	TemplatePolyhedron<TypeParam> t3( this->mat, outsideVec );
	EXPECT_FALSE( this->middle.contains( t3 ) );

	// Template poly that is like t2 (fully within middle), but its directions are inversed - Unbounded poly test, check
	// later vector_t<TypeParam> inverseWithinVec = -1*withinVec; TemplatePolyhedron<TypeParam> t4(this->mat,
	// inverseWithinVec); EXPECT_FALSE(t4.contains(p1)); EXPECT_TRUE(t4.contains(p3));
	// EXPECT_FALSE(this->middle.contains(t4));
}

TYPED_TEST( TemplatePolyhedronTest, Emptiness ) {
	// Empty TPoly
	EXPECT_TRUE( this->empty.empty() );

	// Normal TPoly
	EXPECT_FALSE( this->middle.empty() );

	// Point TPoly
	TemplatePolyhedron<TypeParam> pointTPoly( this->mat, vector_t<TypeParam>::Zero( 4 ) );
	EXPECT_FALSE( pointTPoly.empty() );

	// Infeasible TPoly
	EXPECT_TRUE( this->infeas.empty() );
}

TYPED_TEST( TemplatePolyhedronTest, Vertices ) {
	// Empty TPoly
	EXPECT_EQ( this->empty.vertices(), std::vector<Point<TypeParam>>() );

	// Normal TPoly
	auto vert = this->middle.vertices();
	EXPECT_EQ( vert.size(), std::size_t( 4 ) );
	EXPECT_TRUE( std::find( vert.begin(), vert.end(), Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) !=
				 vert.end() );
	EXPECT_TRUE( std::find( vert.begin(), vert.end(), Point<TypeParam>( { TypeParam( 2 ), TypeParam( -2 ) } ) ) !=
				 vert.end() );
	EXPECT_TRUE( std::find( vert.begin(), vert.end(), Point<TypeParam>( { TypeParam( -2 ), TypeParam( 2 ) } ) ) !=
				 vert.end() );
	EXPECT_TRUE( std::find( vert.begin(), vert.end(), Point<TypeParam>( { TypeParam( -2 ), TypeParam( -2 ) } ) ) !=
				 vert.end() );

	// Point TPoly
	TemplatePolyhedron<TypeParam> pointTPoly( this->mat, vector_t<TypeParam>::Zero( 4 ) );
	EXPECT_EQ( pointTPoly.vertices().size(), std::size_t( 1 ) );
	EXPECT_EQ( pointTPoly.vertices().front(), Point<TypeParam>::Zero( 2 ) );

	// Infeas Poly - TODO
}

TYPED_TEST( TemplatePolyhedronTest, Supremum ) {
	// Empty TPoly
	EXPECT_EQ( this->empty.supremum(), TypeParam( 0 ) );

	// Normal TPoly
	EXPECT_EQ( this->middle.supremum(), TypeParam( 2 ) );
	EXPECT_EQ( this->upright.supremum(), TypeParam( 3 ) );

	// Infeas TPoly - TODO
	EXPECT_EQ( this->infeas.supremum(), TypeParam( 0 ) );
}

TYPED_TEST( TemplatePolyhedronTest, Evaluation ) {
	vector_t<TypeParam> up = vector_t<TypeParam>::Zero( 2 );
	up( 1 ) = TypeParam( 1 );

	// One direction evaluation - Empty TPoly
	EvaluationResult<TypeParam> res1 = this->empty.evaluate( up, true );
	EXPECT_EQ( res1.errorCode, SOLUTION::INFEAS );
	EXPECT_EQ( res1.supportValue, 0 );
	EXPECT_EQ( res1.optimumValue, vector_t<TypeParam>::Zero( 0 ) );

	// One direction evaluation - Normal TPoly
	EvaluationResult<TypeParam> res2 = this->middle.evaluate( up, true );
	EXPECT_EQ( res2.errorCode, SOLUTION::FEAS );
	EXPECT_EQ( res2.supportValue, 2 );
	// EXPECT_EQ(res2.optimumValue, 2*up);

	// One direction evaluation - Infeasible TPoly
	// TemplatePolyhedron<TypeParam> infeas(this->mat, -0.5*vector_t<TypeParam>::Ones(4));
	// EvaluationResult<TypeParam> res3 = infeas.evaluate(up, true);
	// EXPECT_EQ(res3.errorCode, SOLUTION::INFEAS);	//Test says INFTY?
	// EXPECT_EQ(res3.supportValue, 0);
	// EXPECT_EQ(res3.optimumValue, vector_t<TypeParam>::Zero(0));

	matrix_t<TypeParam> allcorners = matrix_t<TypeParam>::Zero( 4, 2 );
	allcorners << 1, 1, 1, -1, -1, 1, -1, -1;

	// Multiple direction evaluation - Empty TPoly
	std::vector<EvaluationResult<TypeParam>> res4 = this->empty.multiEvaluate( allcorners, true );
	EXPECT_EQ( res4.size(), std::size_t( 0 ) );

	// Multiple direction evaluation - Normal TPoly
	res4 = this->middle.multiEvaluate( allcorners, true );
	EXPECT_EQ( res4.size(), std::size_t( 4 ) );
	for ( const auto& elem : res4 ) {
		EXPECT_EQ( elem.errorCode, SOLUTION::FEAS );
		EXPECT_EQ( elem.supportValue, TypeParam( 4 ) );
	}

	// Multiple direction evaluation - Infeasible TPoly
	std::vector<EvaluationResult<TypeParam>> res5 = this->infeas.multiEvaluate( allcorners, true );
	EXPECT_EQ( res5.size(), std::size_t( 0 ) );
}

TYPED_TEST( TemplatePolyhedronTest, RemoveRedundancy ) {
	// Empty TPoly
	this->empty.removeRedundancy();

	// TPoly with no redundancy
	auto matRows = this->middle.matrix().rows();
	auto matCols = this->middle.matrix().cols();
	auto vecRows = this->middle.vector().rows();
	this->middle.removeRedundancy();
	EXPECT_EQ( matRows, this->middle.matrix().rows() );
	EXPECT_EQ( matCols, this->middle.matrix().cols() );
	EXPECT_EQ( vecRows, this->middle.vector().rows() );
	EXPECT_EQ( this->middle.getOptimizer().matrix(), this->mat );
	EXPECT_EQ( this->middle.getOptimizer().vector(), this->middleVec );

	// TPoly with 1 redundant constraint
	matrix_t<TypeParam> withOneRedundantMat = matrix_t<TypeParam>::Zero( 5, 2 );
	vector_t<TypeParam> withOneRedundantVec = vector_t<TypeParam>::Zero( 5 );
	for ( int i = 0; i < this->mat.rows(); i++ ) {
		for ( int j = 0; j < this->mat.cols(); j++ ) {
			withOneRedundantMat( i, j ) = this->mat( i, j );
		}
		withOneRedundantVec( i ) = this->middleVec( i );
	}
	withOneRedundantMat( 4, 0 ) = TypeParam( 4 );
	withOneRedundantVec( 4 ) = TypeParam( 4 );
	TemplatePolyhedron<TypeParam> withOneRedundant( withOneRedundantMat, withOneRedundantVec );
	withOneRedundant.removeRedundancy();
	EXPECT_EQ( withOneRedundant.matrix().rows(), 4 );
	EXPECT_EQ( withOneRedundant.vector().rows(), 4 );
	EXPECT_NE( withOneRedundant.matrix(), matrix_t<TypeParam>::Zero( 4, 2 ) );
	EXPECT_NE( withOneRedundant.vector(), vector_t<TypeParam>::Zero( 4 ) );
	matrix_t<TypeParam> controlMat = matrix_t<TypeParam>::Zero( 4, 2 );
	controlMat << -1, 0, 0, 1, 0, -1, 4, 0;
	vector_t<TypeParam> controlVec = vector_t<TypeParam>::Zero( 4 );
	controlVec << 2, 2, 2, 4;
	EXPECT_EQ( withOneRedundant.getOptimizer().matrix(), controlMat );
	EXPECT_EQ( withOneRedundant.getOptimizer().vector(), controlVec );

	// Multiple redundant constraints
}

TYPED_TEST( TemplatePolyhedronTest, AffineTransformation ) {
	// Define matrix and vector for linear and affine transformation which only scale by 3 and translate by 2 in each
	// coordinate
	matrix_t<TypeParam> transMat = 3 * matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> transVec = 2 * vector_t<TypeParam>::Ones( 2 );

	// Empty TPoly
	// EXPECT_TRUE(this->empty.linearTransformation(transMat).empty());
	// std::cout << "===== Empty =====" << std::endl;
	EXPECT_TRUE( this->empty.affineTransformation( transMat, transVec ).empty() );

	// Normal TPoly
	// std::cout << "===== Scaling =====" << std::endl;
	auto res = this->middle.linearTransformation( transMat );
	EXPECT_EQ( res.matrix(), this->mat );
	EXPECT_EQ( res.vector(), 3 * this->middleVec );
	EXPECT_EQ( res.rGetMatrixPtr(), this->middle.rGetMatrixPtr() );
	// std::cout << "===== Scaling + Translate =====" << std::endl;
	res = this->middle.affineTransformation( transMat, transVec );
	vector_t<TypeParam> controlVec( 4 );
	controlVec << 8, 4, 8, 4;
	EXPECT_EQ( res.matrix(), this->mat );
	EXPECT_EQ( res.vector(), controlVec );
	EXPECT_EQ( res.rGetMatrixPtr(), this->middle.rGetMatrixPtr() );

	// Make an irregular tpoly with points {(1,0),(0,2),(1,-2),(-3,2)}
	matrix_t<TypeParam> irregularMat( 4, 2 );
	irregularMat << 0, 1, 2, 1, 1, 0, -1, -1;
	vector_t<TypeParam> irregularVec( 4 );
	irregularVec << 2, 2, 1, 1;
	TemplatePolyhedron<TypeParam> irreg( irregularMat, irregularVec );

	// Scale irreg by 2 in each dimension
	// std::cout << "===== Scaling Irreg =====" << std::endl;
	matrix_t<TypeParam> scaleMat = matrix_t<TypeParam>::Identity( 2, 2 );
	scaleMat( 0, 0 ) = 2;
	controlVec << 2, 4, 2, 4;
	res = irreg.linearTransformation( scaleMat );
	EXPECT_EQ( res.matrix(), irregularMat );
	EXPECT_EQ( res.vector(), controlVec );
	res = irreg.affineTransformation( scaleMat, vector_t<TypeParam>::Zero( 2 ) );
	EXPECT_EQ( res.vector(), controlVec );

	// Rotate irreg by 90 degrees anticlockwise
	// std::cout << "===== Rotate Irreg =====" << std::endl;
	matrix_t<TypeParam> rotMat = matrix_t<TypeParam>::Zero( 2, 2 );
	rotMat( 0, 1 ) = -1;
	rotMat( 1, 0 ) = 1;
	controlVec << 1, 5, 2, 5;
	res = irreg.linearTransformation( rotMat );
	EXPECT_EQ( res.matrix(), irregularMat );
	EXPECT_EQ( res.vector(), controlVec );
	res = irreg.affineTransformation( rotMat, vector_t<TypeParam>::Zero( 2 ) );
	EXPECT_EQ( res.matrix(), irregularMat );
	EXPECT_EQ( res.vector(), controlVec );

	// Translate irreg by (3,2)
	// std::cout << "===== Translate Irreg =====" << std::endl;
	vector_t<TypeParam> translate = vector_t<TypeParam>::Zero( 2 );
	translate << 3, 2;
	controlVec << 4, 10, 4, -4;
	res = irreg.affineTransformation( matrix_t<TypeParam>::Identity( 2, 2 ), translate );
	EXPECT_EQ( res.matrix(), irregularMat );
	EXPECT_EQ( res.vector(), controlVec );

	// Combine Scaling and rotation
	// std::cout << "===== Scale and Rotate Irreg =====" << std::endl;
	res = irreg.linearTransformation( rotMat * scaleMat );
	EXPECT_EQ( res.matrix(), irregularMat );
	// EXPECT_EQ(res.vector(), controlVec);
	// std::cout << "irreg.vec after combining scaling and rotation is: \n" << res.vector() << std::endl;
}

TYPED_TEST( TemplatePolyhedronTest, MinkowskiSum ) {
#ifndef NDEBUG
	// Both matrices not defined
	auto resEmpty = this->empty.minkowskiSum( this->empty );
	EXPECT_EQ( resEmpty, this->empty );

	// Both matrices empty but defined - return second argument
	auto resInfeas = this->infeas.minkowskiSum( this->infeas );
	EXPECT_EQ( resInfeas, this->infeas );
	EXPECT_TRUE( resInfeas.empty() );

	// First argument empty - return second argument
	auto resFirstEmpty = this->infeas.minkowskiSum( this->upright );
	EXPECT_EQ( resFirstEmpty, this->upright );
	EXPECT_FALSE( resFirstEmpty.empty() );

	// Second argument empty - return first argument
	auto resSecondEmpty = this->upright.minkowskiSum( this->infeas );
	EXPECT_EQ( resSecondEmpty, this->upright );
	EXPECT_FALSE( resSecondEmpty.empty() );
#endif

	// When matrices are the same
	auto res1 = this->middle.minkowskiSum( this->upright );
	vector_t<TypeParam> controlVec = vector_t<TypeParam>::Zero( 4 );
	controlVec << 5, 1, 5, 1;
	auto res1Vertices = res1.vertices();
	EXPECT_EQ( res1.vector(), controlVec );
	EXPECT_EQ( res1Vertices.size(), std::size_t( 4 ) );
	EXPECT_TRUE( std::find( res1Vertices.begin(), res1Vertices.end(),
							Point<TypeParam>( { TypeParam( 5 ), TypeParam( 5 ) } ) ) != res1Vertices.end() );
	EXPECT_TRUE( std::find( res1Vertices.begin(), res1Vertices.end(),
							Point<TypeParam>( { TypeParam( 5 ), TypeParam( -1 ) } ) ) != res1Vertices.end() );
	EXPECT_TRUE( std::find( res1Vertices.begin(), res1Vertices.end(),
							Point<TypeParam>( { TypeParam( -1 ), TypeParam( 5 ) } ) ) != res1Vertices.end() );
	EXPECT_TRUE( std::find( res1Vertices.begin(), res1Vertices.end(),
							Point<TypeParam>( { TypeParam( -1 ), TypeParam( -1 ) } ) ) != res1Vertices.end() );
	EXPECT_EQ( res1.rGetMatrixPtr(), this->middle.rGetMatrixPtr() );

	// When matrices differ - Happens after projections
	auto res2 = this->upleft.minkowskiSum( this->triangle );
	EXPECT_FALSE( res2.empty() );
	EXPECT_EQ( res2.matrix().rows(), 4 );
	auto res2Vertices = res2.vertices();
	EXPECT_EQ( res1Vertices.size(), std::size_t( 4 ) );
}

TYPED_TEST( TemplatePolyhedronTest, Intersect ) {
	// Wish result poly after intersection between middle and upright
	vector_t<TypeParam> resVec = vector_t<TypeParam>::Zero( 4 );
	resVec << 2, -1, 2, -1;
	TemplatePolyhedron<TypeParam> resMiddleUpright( this->mat, resVec );

	// Intersect middle and upright - Should result in resMiddleUpright
	EXPECT_EQ( this->middle.intersect( this->upright ), resMiddleUpright );
	EXPECT_EQ( this->middle.intersect( this->upright ).rGetMatrixPtr(), this->middle.rGetMatrixPtr() );

	// Intersect upleft and upright - Should be empty
	EXPECT_TRUE( this->upright.intersect( this->upleft ).empty() );

	// Intersect middle and empty - Should result in middle
	EXPECT_EQ( this->middle.intersect( this->empty ), this->middle );

	// Intersect upleft and infeas - should result in upleft
	EXPECT_EQ( this->upleft.intersect( this->infeas ), this->upleft );

	// Intersect infeas and empty - should result in empty
	// EXPECT_EQ(this->infeas.intersect(this->empty), this->empty);
}

TYPED_TEST( TemplatePolyhedronTest, Union ) {
	// Wish result poly after unification between middle and upright
	vector_t<TypeParam> resVec = vector_t<TypeParam>::Zero( 4 );
	resVec << 3, 2, 3, 2;
	TemplatePolyhedron<TypeParam> resMiddleUpright( this->mat, resVec );

	// Unite middle and upright - Should result in resMiddleUpright
	EXPECT_EQ( this->middle.unite( this->upright ), resMiddleUpright );
	EXPECT_EQ( this->middle.unite( this->upright ).rGetMatrixPtr(), this->middle.rGetMatrixPtr() );

	// Unite upleft and upright - Union of two disconnected sets results in the smallest set containing both
	resVec << 3, 3, 3, -1;
	TemplatePolyhedron<TypeParam> resUprightUpLeft( this->mat, resVec );
	EXPECT_FALSE( this->upright.unite( this->upleft ).empty() );
	EXPECT_EQ( this->upright.unite( this->upleft ), resUprightUpLeft );

	// Unite middle and empty - Should be middle
	EXPECT_EQ( this->middle.unite( this->empty ), this->middle );

	// Unite upleft and infeas - should be upleft
	EXPECT_EQ( this->upleft.unite( this->infeas ), this->upleft );

	// Unite infeas and empty - should be empty
	// EXPECT_TRUE(this->infeas.unite(this->empty).empty());

	// Unite upright, middle and downleft - should work
	vector_t<TypeParam> resVec2 = vector_t<TypeParam>::Zero( 4 );
	resVec2 << 3, 3, 3, 3;
	TemplatePolyhedron<TypeParam> multiUnite( this->mat, resVec2 );
	std::vector<TemplatePolyhedron<TypeParam>> uniteWith;
	uniteWith.push_back( this->middle );
	uniteWith.push_back( this->downleft );
	auto tmp = this->upright.unite( uniteWith );
	EXPECT_EQ( tmp, multiUnite );
	EXPECT_EQ( tmp.rGetMatrixPtr(), this->upright.rGetMatrixPtr() );

	// Unite upright, middle and infeas - should result in resMiddleUpright
	uniteWith.pop_back();
	uniteWith.push_back( this->infeas );
	EXPECT_EQ( this->upright.unite( uniteWith ), resMiddleUpright );
}

TYPED_TEST( TemplatePolyhedronTest, IntersectHalfspaces ) {
	// Halfspace to test with; initially halfspace lies completely outside and contains middle fully
	Halfspace<TypeParam> hspace( { TypeParam( 1 ), TypeParam( 1 ) }, TypeParam( 5 ) );
	EXPECT_EQ( this->middle.intersectHalfspace( hspace ), this->middle );

	// Halfspace touches middle, only point (-2,-2) is contained
	// std::cout << "TemplatePolyhedronTest::IntersectHalfspaces, zweiter Test" << std::endl;
	hspace.setOffset( -4 );
	vector_t<TypeParam> controlVec = 2 * vector_t<TypeParam>::Ones( 4 );
	controlVec( 0 ) = TypeParam( -2 );
	controlVec( 2 ) = TypeParam( -2 );
	TemplatePolyhedron<TypeParam> controlTPoly( this->mat, controlVec );
	// std::cout << "TemplatePolyhedronTest::IntersectHalfspaces, controlTPoly: " << controlTPoly << std::endl;
	auto blub = this->middle.intersectHalfspace( hspace );
	// std::cout << "TemplatePolyhedronTest::IntersectHalfspaces, intersectHalfspaces result: " << blub << std::endl;
	EXPECT_EQ( this->middle.intersectHalfspace( hspace ), controlTPoly );

	// Halfspace through the origin - worst case approximation: overapproximates to the original box
	// std::cout << "TemplatePolyhedronTest::IntersectHalfspaces, dritter Test" << std::endl;
	hspace.setOffset( 0 );
	auto tmp = this->middle.intersectHalfspace( hspace );
	EXPECT_EQ( tmp, this->middle );
	EXPECT_EQ( tmp.rGetMatrixPtr(), this->middle.rGetMatrixPtr() );

	// Halfspace shrinking the original
	// std::cout << "TemplatePolyhedronTest::IntersectHalfspaces, vierter Test" << std::endl;
	hspace.setOffset( -1 );
	controlVec << 1, 2, 1, 2;
	TemplatePolyhedron<TypeParam> controlTPoly2( this->mat, controlVec );
	EXPECT_EQ( this->middle.intersectHalfspace( hspace ), controlTPoly2 );

	// Multiple halfspaces lying outside

	// Multiple halfspaces overapproximating back to the original

	// Multiple halfspaces shrinking the original
	matrix_t<TypeParam> hspaceNormals = matrix_t<TypeParam>::Zero( 3, 2 );
	hspaceNormals << 1, 0, 0, 1, 1, 1;
	vector_t<TypeParam> hspaceOffsets = vector_t<TypeParam>::Ones( 3 );
	controlVec << 1, 2, 1, 2;
	TemplatePolyhedron<TypeParam> controlTPoly3( this->mat, controlVec );
	auto res = this->middle.intersectHalfspaces( hspaceNormals, hspaceOffsets );
	EXPECT_EQ( res, controlTPoly3 );
	EXPECT_EQ( res.rGetMatrixPtr(), this->middle.rGetMatrixPtr() );
}

TYPED_TEST( TemplatePolyhedronTest, SatisfiesHalfspaces ) {
	// Empty tpoly
	Halfspace<TypeParam> hspace( { TypeParam( 1 ), TypeParam( 1 ) }, TypeParam( 5 ) );
	auto res = this->empty.satisfiesHalfspace( hspace );
	EXPECT_EQ( res.first, CONTAINMENT::NO );
	EXPECT_EQ( res.second, this->empty );

	// middle completely inside halfspace
	res = this->middle.satisfiesHalfspace( hspace );
	EXPECT_EQ( res.first, CONTAINMENT::FULL );
	EXPECT_EQ( res.second, this->middle );

	// middle completely outside halfspace
	hspace.setOffset( -5 );
	res = this->middle.satisfiesHalfspace( hspace );
	EXPECT_EQ( res.first, CONTAINMENT::NO );
	EXPECT_EQ( res.second, this->middle );

	// halfspace halfs middle
	hspace.setOffset( 0 );
	res = this->middle.satisfiesHalfspace( hspace );
	EXPECT_EQ( res.first, CONTAINMENT::PARTIAL );
	EXPECT_EQ( res.second, this->middle );
	EXPECT_EQ( res.second.rGetMatrixPtr(), this->middle.rGetMatrixPtr() );

	// middle completely inside halfspaces
	matrix_t<TypeParam> normals = matrix_t<TypeParam>::Zero( 3, 2 );
	normals << 1, 0, 1, 1, 0, 1;
	vector_t<TypeParam> offsets = vector_t<TypeParam>::Zero( 3 );
	offsets << 3, 4, 3;
	res = this->middle.satisfiesHalfspaces( normals, offsets );
	EXPECT_EQ( res.first, CONTAINMENT::FULL );
	EXPECT_EQ( res.second, this->middle );

	// middle completely outside halfspaces
	offsets << -3, -5, -3;
	res = this->middle.satisfiesHalfspaces( normals, offsets );
	EXPECT_EQ( res.first, CONTAINMENT::NO );
	EXPECT_EQ( res.second, this->middle );

	// middle partially inside halfspaces
	offsets << 1, 0, 1;
	vector_t<TypeParam> controlVec = vector_t<TypeParam>::Zero( 4 );
	controlVec << 1, 2, 1, 2;
	TemplatePolyhedron<TypeParam> control( this->mat, controlVec );
	res = this->middle.satisfiesHalfspaces( normals, offsets );
	EXPECT_EQ( res.first, CONTAINMENT::PARTIAL );
	EXPECT_EQ( res.second, control );
	EXPECT_EQ( res.second.rGetMatrixPtr(), this->middle.rGetMatrixPtr() );
}

TYPED_TEST( TemplatePolyhedronTest, Projection ) {
	matrix_t<TypeParam> cubeMat = matrix_t<TypeParam>::Zero( 6, 3 );
	cubeMat << 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1;
	vector_t<TypeParam> cubeVec = 2 * vector_t<TypeParam>::Ones( 6 );
	TemplatePolyhedron<TypeParam> cube( cubeMat, cubeVec );

	// Project to x-y-plane
	std::vector<std::size_t> projectDims( { 0, 1 } );
	auto xy = cube.projectOn( projectDims );
	matrix_t<TypeParam> controlMat = matrix_t<TypeParam>::Zero( 4, 2 );
	controlMat << 1, 0, -1, 0, 0, 1, 0, -1;
	vector_t<TypeParam> controlVec = 2 * vector_t<TypeParam>::Ones( 4 );
	EXPECT_NE( xy.matrix(), cubeMat );
	// EXPECT_EQ(xy.matrix(), controlMat); //is the same but matrix is scrambled
	// EXPECT_EQ(xy.vector(), controlVec); //Is the same but all values in vec and matrix are halved
	EXPECT_NE( xy, this->middle );

	// Project to x axis
	projectDims.pop_back();
	auto x = cube.projectOn( projectDims );
	matrix_t<TypeParam> controlMat2 = matrix_t<TypeParam>::Zero( 2, 1 );
	controlMat2 << 1, -1;
	vector_t<TypeParam> controlVec2 = 2 * vector_t<TypeParam>::Ones( 2 );
	// EXPECT_EQ(x.matrix(), controlMat2); //is the same but matrix is scrambled
	// EXPECT_EQ(x.vector(), controlVec2);

	// Project to no dimension
	projectDims.pop_back();
	auto none = cube.projectOn( projectDims );
	EXPECT_EQ( none, TemplatePolyhedron<TypeParam>::Empty() );

	// Project to all dimensions
	projectDims.push_back( 0 );
	projectDims.push_back( 1 );
	projectDims.push_back( 2 );
	auto full = cube.projectOn( projectDims );
	// EXPECT_EQ(full, cube); //is the same but matrix is scrambled
}

TYPED_TEST( TemplatePolyhedronTest, Overapproximation ) {
	// Overapproximate Empty - If empty return this
	EXPECT_EQ( this->empty, this->empty.overapproximate( this->mat ) );
	EXPECT_EQ( this->infeas, this->infeas.overapproximate( this->mat ) );

	// Overapproximate itself
	EXPECT_EQ( this->middle, this->middle.overapproximate( this->mat ) );

	// Overapproximate differently
	vector_t<TypeParam> controlVec( 4 );
	controlVec << 2, 0, 0.5, 0;
	EXPECT_EQ( TemplatePolyhedron<TypeParam>( this->mat, controlVec ), this->triangle.overapproximate( this->mat ) );
}

TYPED_TEST( TemplatePolyhedronTest, Boundedness ) {
	// Bounded - empty
	EXPECT_TRUE( this->empty.isBounded() );
	// Bounded - infeasible
	EXPECT_TRUE( this->infeas.isBounded() );
	// Bounded - normal
	EXPECT_TRUE( this->middle.isBounded() );

	// Unbounded
	matrix_t<TypeParam> m( 1, 2 );
	m << -1, 0;
	TemplatePolyhedron<TypeParam> unbounded( m, vector_t<TypeParam>::Zero( 1 ) );
	EXPECT_FALSE( unbounded.isBounded() );
	// Unbounded, but all normals are within one halfsphere
	matrix_t<TypeParam> fiveSidesOfOctagon( 5, 2 );
	fiveSidesOfOctagon << 0, 1, -1, 1, -1, 0, -1, -1, 0, -1;
	TemplatePolyhedron<TypeParam> incompleteOctagon( fiveSidesOfOctagon, vector_t<TypeParam>::Ones( 5 ) );
	EXPECT_FALSE( unbounded.isBounded() );
}

TYPED_TEST( TemplatePolyhedronTest, ReduceRepresentation ) {
	// TODO: Test case empty tpoly

	// Test case normal
	matrix_t<TypeParam> bigMat = matrix_t<TypeParam>::Zero( 7, 2 );
	bigMat << -1, 0, 1, 0, 0, -1, 0, 1,	 // Should be removed
		  0, 1,							 // Should be removed
		  0, 1,							 // Should not be removed since it has the smallest offset
		  1, 1;							 // Should not be removed, although redundant for definition of tpoly
	vector_t<TypeParam> bigVec = vector_t<TypeParam>::Zero( 7 );
	bigVec << 2, 2, 2, 2, 3, 1, 10;
	TemplatePolyhedron<TypeParam> bigPoly( bigMat, bigVec );
	bigPoly.reduceRepresentation();
	matrix_t<TypeParam> controlMat = matrix_t<TypeParam>::Zero( 5, 2 );
	controlMat << -1, 0, 1, 0, 0, -1, 0, 1, 1, 1;
	vector_t<TypeParam> controlVec = vector_t<TypeParam>::Zero( 5 );
	controlVec << 2, 2, 2, 1, 3;
	EXPECT_EQ( bigPoly.matrix(), controlMat );
	EXPECT_EQ( bigPoly.vector(), controlVec );
}