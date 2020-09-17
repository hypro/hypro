/*
 * File:   ZonotopeTest.cpp
 * Author: jongan
 *
 * Created on Sep 1, 2014, 11:56:26 AM
 */

#include "../defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/Halfspace.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <iostream>
#include <stdlib.h>

/*
 * Google TYPED_TEST for Zonotope Implementation
 */

using namespace hypro;

template <typename Number>
class ZonotopeTest : public ::testing::Test {
  protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};

TYPED_TEST( ZonotopeTest, PlainConstructor ) {
	Zonotope<TypeParam> z1;
	EXPECT_TRUE( z1.empty() );
	EXPECT_EQ( z1.order(), TypeParam( 0 ) );
	EXPECT_EQ( z1.dimension(), (unsigned)0 );
	EXPECT_EQ( z1.center().rows(), 0 );
	EXPECT_EQ( z1.center().cols(), 1 );
	EXPECT_EQ( z1.generators().rows(), 0 );
	EXPECT_EQ( z1.generators().cols(), 0 );

	Zonotope<TypeParam> emp = Zonotope<TypeParam>::Empty();
	EXPECT_TRUE( emp.empty() );
}

TYPED_TEST( ZonotopeTest, DimConstructor ) {
	unsigned int dim = 4;
	Zonotope<TypeParam> z1( dim );
	EXPECT_EQ( z1.dimension(), (unsigned)4 );
}

TYPED_TEST( ZonotopeTest, FullConstructor ) {
	Eigen::Matrix<TypeParam, 2, 3> gen;
	Eigen::Matrix<TypeParam, 2, 1> center;

	gen << 2, 3, 6, 4, 1, 5;
	center << 1, 2;

	Zonotope<TypeParam> z2( center, gen );
	EXPECT_EQ( z2.dimension(), (unsigned)2 );
	EXPECT_EQ( z2.center(), center );
	EXPECT_EQ( z2.generators(), gen );
}

TYPED_TEST( ZonotopeTest, CopyConstructor ) {
	Eigen::Matrix<TypeParam, 3, 2> gen;
	Eigen::Matrix<TypeParam, 3, 1> center;
	center << 1, 5, 2;
	gen << 1, 2, 2, 8, 9, 1;
	Zonotope<TypeParam> z1( center, gen );
	Zonotope<TypeParam> z_copy( z1 );

	EXPECT_EQ( z_copy.dimension(), z1.dimension() );
	EXPECT_EQ( z_copy.center(), z1.center() );
	EXPECT_EQ( z_copy.generators(), z1.generators() );
}

TYPED_TEST( ZonotopeTest, ComputeZonotopeBoundary ) {
	Zonotope<TypeParam> z1( 2 );
	Eigen::Matrix<TypeParam, 2, 1> center = { carl::rationalize<TypeParam>( 1.1941 ),
											  carl::rationalize<TypeParam>( 0.1068 ) };
	Eigen::Matrix<TypeParam, 2, 6> generators;
	generators << carl::rationalize<TypeParam>( 0.3993 ), carl::rationalize<TypeParam>( 0.0160 ),
		  carl::rationalize<TypeParam>( 0.0020 ), carl::rationalize<TypeParam>( 0.0035 ), 0,
		  carl::rationalize<TypeParam>( -0.0017 ), carl::rationalize<TypeParam>( 0.0898 ),
		  carl::rationalize<TypeParam>( 0.0196 ), carl::rationalize<TypeParam>( -0.0015 ),
		  carl::rationalize<TypeParam>( 0.0008 ), carl::rationalize<TypeParam>( 0.0035 ),
		  carl::rationalize<TypeParam>( -0.0045 );

	z1.setCenter( center );
	z1.setGenerators( generators );

	std::vector<hypro::vector_t<TypeParam> > results = z1.computeZonotopeBoundary();
}

/*
TYPED_TEST(ZonotopeTest, Corners) {
	Eigen::Matrix<TypeParam, 2,3> gen;
	Eigen::Matrix<TypeParam, 2,1> center;

	gen << 2,3,6,
		   4,1,5;
	center << 1,
			  2;

	hypro::Zonotope<TypeParam> z2(center, gen);
	z2.corners();
}
*/

TYPED_TEST( ZonotopeTest, ZonogoneHPIntersect ) {
	Eigen::Matrix<TypeParam, 2, 1> dVec = { 0, 1 }, center = { carl::rationalize<TypeParam>( 1.1941 ),
															   carl::rationalize<TypeParam>( 0.1068 ) };
	Eigen::Matrix<TypeParam, 2, 6> generators;
	generators << carl::rationalize<TypeParam>( 0.3993 ), carl::rationalize<TypeParam>( 0.0160 ),
		  carl::rationalize<TypeParam>( 0.0020 ), carl::rationalize<TypeParam>( 0.0035 ), 0,
		  carl::rationalize<TypeParam>( -0.0017 ), carl::rationalize<TypeParam>( 0.0898 ),
		  carl::rationalize<TypeParam>( 0.0196 ), carl::rationalize<TypeParam>( -0.0015 ),
		  carl::rationalize<TypeParam>( 0.0008 ), carl::rationalize<TypeParam>( 0.0035 ),
		  carl::rationalize<TypeParam>( -0.0045 );

	hypro::Halfspace<TypeParam> hp( dVec, 0 );
	hypro::Zonotope<TypeParam> z( center, generators ), res;
	hypro::matrix_t<TypeParam> dummy;
	res = intersectZonotopeHalfspace( z, hp, dummy );
}

TYPED_TEST( ZonotopeTest, MinkowskiSum ) {
	hypro::Zonotope<TypeParam> z1( 2 ), z2( 2 ), z3( 2 );

	Eigen::Matrix<TypeParam, 2, 1> cen1, cen2, cen_res, gen_sum;
	Eigen::Matrix<TypeParam, 2, 2> gen1, gen2;

	cen1 << 1, 2;
	cen2 << 4, 7;

	gen1 << 3, 4, 6, 1;
	gen2 << 2, 1, 7, 8;

	z1.setCenter( cen1 );
	z1.setGenerators( gen1 );
	z2.setCenter( cen2 );
	z2.setGenerators( gen2 );

	z1 = z1.minkowskiSum( z2 );

	cen_res << 5, 9;

	gen_sum << 10, 22;

	EXPECT_EQ( z1.center(), cen_res );
	EXPECT_EQ( z1.size(), (unsigned)4 );
	EXPECT_EQ( z1.generators().rowwise().sum(), gen_sum );

	z1 = z2.minkowskiSum( z3 );
	EXPECT_EQ( z1.size(), (unsigned)2 );
	EXPECT_EQ( z1.generators(), gen2 );

	// z1.minkowskiSum(*this, z2);
	// EXPECT_NE(z1.center(), cen1);
}

// TYPED_TEST(ZonotopeTest, Intersection1) {
//    Eigen::Matrix<TypeParam, 3,3> gen, exp_gen, delta_gen;
//    Eigen::Matrix<TypeParam, 3,1> cen, d_vector, exp_center, delta_center;
//    gen << 2,0,0,
//            0,1,0,
//            0,0,3;
//
//    exp_gen << 1.6926, -0.2049, -0.6916,
//                -0.1025, 0.9317, -0.2305,
//                -1.0374, -0.6916, 0.660;
//
//    delta_gen << 0.001, 0.001, 0.001,
//                 0.001, 0.001, 0.001,
//                 0.001, 0.001, 0.001;
//
//
//    cen << 1,
//            1,
//            1;
//
//    exp_center << 1.1793,
//                  1.0598,
//                  1.6051;
//
//    d_vector << 6,
//                8,
//                9;
//
//    delta_center << 0.001,
//                    0.001,
//                    0.001;
//
//    Zonotope<TypeParam> z1(3), res(3);
//    z1.setCenter(cen);
//    z1.setGenerators(gen);
//
//    Halfspace<TypeParam> hp(3);
//    hp.setVector(d_vector);
//    hp.setScalar(30);
//
//    z1.intersect(res, hp, NDPROJECTION);
//
//    EXPECT_LT((res.center()-exp_center).array().abs().matrix().sum(), delta_center.sum());
//    EXPECT_LT((res.generators()-exp_gen).array().abs().matrix().rowwise().sum().sum(),
//    delta_gen.array().abs().matrix().rowwise().sum().sum());
//}

#ifdef HYPRO_USE_PPL
TYPED_TEST( ZonotopeTest, IntersectionHalfspace ) {
	Parma_Polyhedra_Library::Variable x( 0 ), y( 1 );
	Parma_Polyhedra_Library::Constraint hspace( y <= x - 1 );
	Eigen::Matrix<TypeParam, 2, 1> z_center( 3, -10 );
	Eigen::Matrix<TypeParam, 2, 2> z_gen;
	z_gen << 0, 1, 1, 0;
	hypro::Zonotope<TypeParam> z1( z_center, z_gen ), result( 2 );

	// Case 1: Zonotope is wholly inside the halfspace
	result = z1.intersect( hspace );
	bool foundIntersect = !result.empty();
	// Expect: result zonotope is the original zonotope, nothing is changed
	// Intersection trivially present
	EXPECT_TRUE( foundIntersect );
	EXPECT_EQ( result.center(), z_center );
	EXPECT_EQ( result.generators(), z_gen );

	// Case 2: Zonotope is wholly outside of the halfspace
	z_center << -3, 3;
	z_gen << 0, 1, 1, 0;
	z1.setCenter( z_center );
	z1.setGenerators( z_gen );
	result = z1.intersect( hspace );
	foundIntersect = !result.empty();
	// Expect: No intersect was found
	EXPECT_FALSE( foundIntersect );

	// Case 3: Zonotope intersects partially with halfspace
	z_center << 0, 0;
	z_gen << 0, 2, 2, 0;

	z1.setCenter( z_center );
	z1.setGenerators( z_gen );

	result = z1.intersect( hspace );
	foundIntersect = !result.empty();
	// Expect: Intersect to be found, resulting zonotope is a different zonotope
	// TODO: verify that the resulting zonotope is correct
	EXPECT_TRUE( foundIntersect );
	EXPECT_TRUE( result.center() != z_center );
	//    EXPECT_TRUE(result.generators()!=z_gen);
}

TYPED_TEST( ZonotopeTest, IntersectionPolytope ) {
	Eigen::Matrix<TypeParam, 2, 1> z_center;
	Eigen::Matrix<TypeParam, 2, 2> z_gen;
	z_center << 0, -1;
	z_gen << 0, 1, 1, 0;
	hypro::Zonotope<TypeParam> z1( z_center, z_gen ), result_zonotope( 2 );

	Parma_Polyhedra_Library::C_Polyhedron poly1( 2, Parma_Polyhedra_Library::UNIVERSE );
	Parma_Polyhedra_Library::Variable x( 0 ), y( 1 );
	Parma_Polyhedra_Library::Constraint_System cs;
	cs.insert( y <= 3 );
	cs.insert( y >= 1 );
	cs.insert( y >= x - 2 );
	cs.insert( y <= 2 * x - 1 );
	poly1.add_constraints( cs );

	// std::cout << "Polytope: " << poly1 << std::endl;
	result_zonotope = z1.intersect( poly1 );
	bool res = result_zonotope.empty();

	EXPECT_EQ( res, false );
}
#endif

TYPED_TEST( ZonotopeTest, RemoveEmptyGen ) {
	Eigen::Matrix<TypeParam, 3, 1> center;
	center << 2, 3, 6;

	Eigen::Matrix<TypeParam, 3, 4> gen;
	Eigen::Matrix<TypeParam, 3, 3> gen2;

	gen << 2, 3, 0, 2, 3, 6, 0, 3, 1, 5, 0, 7;

	gen2 << 2, 3, 2, 3, 6, 3, 1, 5, 7;

	hypro::Zonotope<TypeParam> z1;
	z1.setCenter( center );
	z1.setGenerators( gen );
	z1.removeEmptyGenerators();

	EXPECT_EQ( z1.generators(), gen2 );
}

TYPED_TEST( ZonotopeTest, AddGenerators ) {
	hypro::Zonotope<TypeParam> z( 2 );
	Eigen::Matrix<TypeParam, 2, 3> generators, generators2;
	Eigen::Matrix<TypeParam, 2, 6> concat_gens;
	generators << 1, 2, 5, 3, 1, 6;

	generators2 << 2, 1, 6, 2, 6, 8;

	z.addGenerators( generators );
	EXPECT_EQ( z.generators(), generators );

	z.addGenerators( generators2 );
	concat_gens << generators, generators2;
	EXPECT_EQ( z.generators(), concat_gens );
}

TYPED_TEST( ZonotopeTest, RemoveGenerators ) {
	matrix_t<TypeParam> generators( 2, 3 );
	generators << 1, 2, 5, 3, 1, 6;

	matrix_t<TypeParam> expectedResult( 2, 2 );
	expectedResult << 1, 5, 3, 6;

	hypro::removeGenerator( 1, generators );
	EXPECT_EQ( expectedResult, generators );
}

TYPED_TEST( ZonotopeTest, Intersection2 ) {
	hypro::Zonotope<TypeParam> z1( 3 );
	Eigen::Matrix<TypeParam, 3, 1> z_center, d, exp_center, delta;
	Eigen::Matrix<TypeParam, 3, 7> generators;
	z_center << carl::rationalize<TypeParam>( -0.0407 ), carl::rationalize<TypeParam>( -6.3274 ), 1;
	d << 1, 0, 0;

	exp_center << 0, carl::rationalize<TypeParam>( -6.254369393209305 ),
		  carl::rationalize<TypeParam>( 0.994400337321514 );

	delta << carl::rationalize<TypeParam>( 0.01 ), carl::rationalize<TypeParam>( 0.01 ),
		  carl::rationalize<TypeParam>( 0.01 );

	generators << carl::rationalize<TypeParam>( 0.01 ), carl::rationalize<TypeParam>( 0.00645 ),
		  carl::rationalize<TypeParam>( 0.03163725 ), carl::rationalize<TypeParam>( -5e-05 ),
		  carl::rationalize<TypeParam>( 0.0111647739218983 ), carl::rationalize<TypeParam>( 0.00714545531001491 ),
		  carl::rationalize<TypeParam>( -0.0224310133091988 ), 0, carl::rationalize<TypeParam>( 0.0100000000000000 ),
		  carl::rationalize<TypeParam>( 0.0490500000000000 ), 0, 0, carl::rationalize<TypeParam>( 0.0111647739218983 ),
		  carl::rationalize<TypeParam>( -0.0700969165912463 ), 0, 0, 0, 0, 0, 0,
		  carl::rationalize<TypeParam>( 0.0111647739218983 );

	z1.setCenter( z_center );
	z1.setGenerators( generators );

	hypro::Halfspace<TypeParam> h1 = hypro::Halfspace<TypeParam>();
	h1.setNormal( d );
	h1.setOffset( 0 );

	hypro::Zonotope<TypeParam> result = z1.intersect( h1, ZUtility::ALAMO );

	EXPECT_LT( ( result.center() - exp_center ).array().abs().matrix().sum(), delta.sum() );
}

TYPED_TEST( ZonotopeTest, ConvexHull ) {
	hypro::Zonotope<TypeParam> z1( 2 ), z2( 2 ), result;
	Eigen::Matrix<TypeParam, 2, 1> c1, c2, expected_center;
	Eigen::Matrix<TypeParam, 2, 2> g1;
	Eigen::Matrix<TypeParam, 2, 3> g2;
	Eigen::Matrix<TypeParam, 2, 3> expected_generators;

	c1 << 2, 1;
	c2 << 1, 1;

	g1 << 1, 1, 0, 1;

	g2 << 1, 1, carl::rationalize<TypeParam>( -0.5 ), 0, 1, carl::rationalize<TypeParam>( 0.2 );

	expected_center << carl::rationalize<TypeParam>( 1.5 ), 1;
	expected_generators << carl::rationalize<TypeParam>( 0.5 ), 1, carl::rationalize<TypeParam>( -0.5 ), 0, 1,
		  carl::rationalize<TypeParam>( 0.2 );

	z1.setCenter( c1 );
	z1.setGenerators( g1 );
	z2.setCenter( c2 );
	z2.setGenerators( g2 );

	result = z1.unite( z2 );

	EXPECT_EQ( result.center(), expected_center );
	EXPECT_EQ( result.generators(), expected_generators );
}

TYPED_TEST( ZonotopeTest, IntervalHull ) {
	Eigen::Matrix<TypeParam, 2, 1> center = { 2, 1 };
	Eigen::Matrix<TypeParam, 2, 3> generators;
	Eigen::Matrix<TypeParam, 2, 2> expected_generators;
	generators << 1, 4, 3, 6, 2, 1;
	expected_generators << 8, 0, 0, 9;
	hypro::Zonotope<TypeParam> result, zIH( center, generators );

	result = zIH.intervalHull();

	EXPECT_EQ( result.generators(), expected_generators );
	EXPECT_EQ( result.center(), center );
}

TYPED_TEST( ZonotopeTest, SatisfiesHalfspaces ) {
	// 4 contraints making up the unit box centered around 1,1, so with corner points (0,0),(2,0),(2,2),(0,2)
	// The zonotope has two generators (0.5,0.5) and (1,0). Thus, it will only be partially contained within the box.
	// The two extreme points of the zonotope (2.5, 1.5) and (-0.5, 0.5) should stick out of the box.
	matrix_t<TypeParam> boxMat = matrix_t<TypeParam>::Zero( 4, 2 );
	boxMat( 0, 0 ) = TypeParam( 1 );
	boxMat( 1, 1 ) = TypeParam( 1 );
	boxMat( 2, 0 ) = TypeParam( -1 );
	boxMat( 3, 1 ) = TypeParam( -1 );
	vector_t<TypeParam> boxVec = vector_t<TypeParam>::Zero( 4 );
	boxVec( 0 ) = TypeParam( 2 );
	boxVec( 1 ) = TypeParam( 2 );
	boxVec( 2 ) = TypeParam( 0 );
	boxVec( 3 ) = TypeParam( 0 );
	matrix_t<TypeParam> generators = matrix_t<TypeParam>::Zero( 2, 2 );
	generators( 0, 0 ) = TypeParam( 0.5 );
	generators( 1, 0 ) = TypeParam( 0.5 );
	generators( 0, 1 ) = TypeParam( 1 );
	generators( 1, 1 ) = TypeParam( 0 );
	vector_t<TypeParam> center = vector_t<TypeParam>::Zero( 2 );
	center( 0 ) = TypeParam( 1 );
	center( 1 ) = TypeParam( 1 );
	hypro::Zonotope<TypeParam> zono( center, generators );

	// Tests
	auto result = zono.satisfiesHalfspaces( boxMat, boxVec );
	EXPECT_EQ( result.first, hypro::CONTAINMENT::PARTIAL );

	Halfspace<TypeParam> rightSideOfBox( boxMat.row( 0 ), boxVec( 0 ) );
	Halfspace<TypeParam> leftSideOfBox( boxMat.row( 2 ), boxVec( 2 ) );
	Point<TypeParam> rightExtremePoint( { TypeParam( 2.5 ), TypeParam( 1.5 ) } );
	Point<TypeParam> leftExtremePoint( { TypeParam( -0.5 ), TypeParam( 0.5 ) } );
	EXPECT_TRUE( !rightSideOfBox.contains( rightExtremePoint ) );
	EXPECT_TRUE( !leftSideOfBox.contains( leftExtremePoint ) );
	EXPECT_TRUE( zono.contains( rightExtremePoint ) );
	EXPECT_TRUE( zono.contains( leftExtremePoint ) );

	Halfspace<TypeParam> upperSideOfBox( boxMat.row( 1 ), boxVec( 1 ) );
	Halfspace<TypeParam> lowerSideOfBox( boxMat.row( 3 ), boxVec( 3 ) );
	auto satisfiesUpperSide = zono.satisfiesHalfspace( upperSideOfBox );
	EXPECT_EQ( satisfiesUpperSide.first, hypro::CONTAINMENT::FULL );
	auto satisfiesLowerSide = zono.satisfiesHalfspace( lowerSideOfBox );
	EXPECT_EQ( satisfiesLowerSide.first, hypro::CONTAINMENT::FULL );
}
