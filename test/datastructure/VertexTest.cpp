#include "test/defines.h"
#include "gtest/gtest.h"
#include <carl/core/VariablePool.h>
#include <hypro/datastructures/Vertex.h>

using namespace hypro;
using namespace carl;

template <typename Number>
class VertexTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		pool.clear();
		x = pool.newCarlVariable();
		y = pool.newCarlVariable();

		p1 = Point<Number>( { Number( 2 ), Number( 5 ) } );
		p2 = Point<Number>( { Number( 7 ), Number( 8 ) } );
		p3 = Point<Number>( { Number( -9 ), Number( -13 ) } );
	}

	virtual void TearDown() {}

	hypro::VariablePool& pool = hypro::VariablePool::getInstance();
	carl::Variable x;
	carl::Variable y;

	Point<Number> p1;
	Point<Number> p2;
	Point<Number> p3;
};

TYPED_TEST( VertexTest, ColorTest ) {
	Vertex<TypeParam> v;
	v.setColor( true );
	ASSERT_TRUE( v.color() );
	v.invertColor();
	ASSERT_FALSE( v.color() );
}

TYPED_TEST( VertexTest, Constructor ) {
	Vertex<TypeParam> vertex1;
	ASSERT_FALSE( vertex1.color() );

	Vertex<TypeParam> vertex2( this->p1, true );
	ASSERT_EQ( vertex2.dimension(), (unsigned)2 );
	ASSERT_TRUE( vertex2.color() );

	Vertex<TypeParam> vertex3( Point<TypeParam>{ 1, 2, 3 }, true );
	vertex1.setPoint( Point<TypeParam>( { 1, 2, 3 } ) );
	vertex1.setColor( true );
	ASSERT_EQ( vertex1, vertex3 );
}

TYPED_TEST( VertexTest, Equality ) {
	Vertex<TypeParam> v1( this->p1, true );
	Vertex<TypeParam> v2( this->p1, false );
	Vertex<TypeParam> v3( this->p1, true );

	EXPECT_TRUE( v1 != v2 );
	EXPECT_TRUE( v1 == v3 );
}

TYPED_TEST( VertexTest, Order ) {
	Vertex<TypeParam> v1( this->p1, false );
	Vertex<TypeParam> v2( this->p1, true );
	Vertex<TypeParam> v3( this->p2, true );
	Vertex<TypeParam> v4( this->p3, false );

	EXPECT_TRUE( v1 < v2 );
	EXPECT_TRUE( v2 < v3 );
	EXPECT_TRUE( v3 > v4 );

	EXPECT_TRUE( v4 < v3 );
	EXPECT_TRUE( v3 > v2 );
	EXPECT_TRUE( v2 > v1 );
}
