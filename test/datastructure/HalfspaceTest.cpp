/**
 * Test for Halfspaces.
 * @file PolytopeTest.cpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since       2015-02-12
 * @version     2015-02-12
 */

#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/Halfspace.h>

using namespace hypro;
using namespace carl;

template <typename Number>
class HalfspaceTest : public ::testing::Test {
  protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};

TYPED_TEST( HalfspaceTest, Constructor ) {
	// Halfspace<TypeParam> empty = Halfspace<TypeParam>();
	Point<TypeParam> vec = Point<TypeParam>( { 2, 4 } );
	Halfspace<TypeParam> normals = Halfspace<TypeParam>( vec, TypeParam( 3 ) );
	Halfspace<TypeParam> initializer = Halfspace<TypeParam>( { TypeParam( 2 ), TypeParam( 4 ) }, TypeParam( 3 ) );
	EXPECT_EQ( normals, initializer );

	vector_t<TypeParam> normal = vector_t<TypeParam>( 2 );
	normal( 0 ) = TypeParam( 2 );
	normal( 1 ) = TypeParam( 4 );
	Halfspace<TypeParam>( normal, TypeParam( 3 ) );

	Halfspace<TypeParam> copy = Halfspace<TypeParam>( normals );
	EXPECT_EQ( copy, normals );

	SUCCEED();
}

TYPED_TEST( HalfspaceTest, Access ) {
	Halfspace<TypeParam> tmp( { 1, 2 }, 3 );
}

TYPED_TEST( HalfspaceTest, Evaluation ) {
	vector_t<TypeParam> vec( 2 );
	vec( 0 ) = 2;
	vec( 1 ) = 4;
	Halfspace<TypeParam> hp1 = Halfspace<TypeParam>( vec, TypeParam( 3 ) );

	vector_t<TypeParam> test( 2 );
	test( 0 ) = 5;
	test( 1 ) = 1;

	EXPECT_EQ( TypeParam( vec.dot( test ) ), hp1.evaluate( test ) );
}

TYPED_TEST( HalfspaceTest, SignedDistance ) {
	vector_t<TypeParam> vec( 2 );
	vec( 0 ) = 2;
	vec( 1 ) = 4;
	Halfspace<TypeParam> hp1 = Halfspace<TypeParam>( vec, TypeParam( 3 ) );

	vector_t<TypeParam> test( 2 );
	test( 0 ) = 5;
	test( 1 ) = 1;

	EXPECT_EQ( TypeParam( vec.dot( test ) ) - hp1.offset(), hp1.signedDistance( test ) );
}

TYPED_TEST( HalfspaceTest, Intersection ) {
	vector_t<TypeParam> normal1( 4 );
	normal1( 0 ) = 1;
	normal1( 1 ) = 1;
	normal1( 2 ) = 1;
	normal1( 3 ) = 1;
	Halfspace<TypeParam> hp1 = Halfspace<TypeParam>( normal1, TypeParam( 3 ) );

	vector_t<TypeParam> normal2( 4 );
	normal2( 0 ) = 2;
	normal2( 1 ) = 1;
	normal2( 2 ) = 3;
	normal2( 3 ) = 4;
	Halfspace<TypeParam> hp2 = Halfspace<TypeParam>( normal2, TypeParam( 4 ) );

	vector_t<TypeParam> v = hp1.intersectionVector( hp2 );
}

TYPED_TEST( HalfspaceTest, saveIntersection ) {
	/*
	vector_t<TypeParam> normal1(2);
	normal1(0) = 1;
	normal1(1) = 1;
	Halfspace<TypeParam> hp1 = Halfspace<TypeParam>(normal1, TypeParam(1));

	vector_t<TypeParam> normal2(2);
	normal2(0) = -1 + 1000000000*std::numeric_limits<TypeParam>::epsilon();
	normal2(1) = -1 + 1000000000*std::numeric_limits<TypeParam>::epsilon();
	Halfspace<TypeParam> hp2 = Halfspace<TypeParam>(normal2, TypeParam(-1+0.0001));

	std::vector<hypro::Halfspace<TypeParam>> hpv;
	hpv.push_back(hp1);
	hpv.push_back(hp2);

	hypro::vector_t<TypeParam> res = Halfspace<TypeParam>::saveIntersect(hpv, 1);

	EXPECT_TRUE(hp1.normal().dot(res) >= hp1.offset());
	EXPECT_TRUE(hp2.normal().dot(res) >= hp2.offset());
	*/
}
