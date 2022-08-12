#include "../../hypro/datastructures/Point.h"
#include "../../hypro/representations/GeometricObjectBase.h"
#include "../defines.h"
#include "gtest/gtest.h"


using namespace hypro;
using namespace carl;

template <typename Number>
class VPolytopeTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		vector_t<Number> p1 = vector_t<Number>( 2 );
		p1( 0 ) = 1;
		p1( 1 ) = 2;
		vector_t<Number> p2 = vector_t<Number>( 2 );
		p2( 0 ) = 3;
		p2( 1 ) = 2;
		vector_t<Number> p3 = vector_t<Number>( 2 );
		p3( 0 ) = 3;
		p3( 1 ) = 4;
		vector_t<Number> p4 = vector_t<Number>( 2 );
		p4( 0 ) = 1;
		p4( 1 ) = 4;
		vector_t<Number> p5 = vector_t<Number>( 2 );
		p5( 0 ) = 2;
		p5( 1 ) = 1;
		vector_t<Number> p6 = vector_t<Number>( 2 );
		p6( 0 ) = 4;
		p6( 1 ) = 1;
		vector_t<Number> p7 = vector_t<Number>( 2 );
		p7( 0 ) = 4;
		p7( 1 ) = 3;
		vector_t<Number> p8 = vector_t<Number>( 2 );
		p8( 0 ) = 2;
		p8( 1 ) = 3;

		points1.push_back( Point<Number>( p1 ) );
		points1.push_back( Point<Number>( p2 ) );
		points1.push_back( Point<Number>( p3 ) );
		points1.push_back( Point<Number>( p4 ) );

		points2.push_back( Point<Number>( p5 ) );
		points2.push_back( Point<Number>( p6 ) );
		points2.push_back( Point<Number>( p7 ) );
		points2.push_back( Point<Number>( p8 ) );
	}

	virtual void TearDown() {}

	typename VPolytope<Number>::pointVector points1;
	typename VPolytope<Number>::pointVector points2;
};

TYPED_TEST( SetMinusTest, Constructor ) {
	HPolytope<TypeParam> HPolytope = HPolytope<TypeParam>( this->points1 );
	HPolytope<TypeParam> HPolytope2 = HPolytope<TypeParam>( this->points2 );

    BoxT<TypeParam> Box = BoxT<TypeParam>( this->points1 );
	BoxT<TypeParam> Box2 = BoxT<TypeParam>( this->points2 );

	SUCCEED();
}

TYPED_TEST( SetMinusTest, SetMinus ) {
    HPolytope<TypeParam> HPolytope = HPolytope<TypeParam>( this->points1 );
	HPolytope<TypeParam> HPolytope2 = HPolytope<TypeParam>( this->points2 );

    BoxT<TypeParam> Box = BoxT<TypeParam>( this->points1 );
	BoxT<TypeParam> Box2 = BoxT<TypeParam>( this->points2 );

    Hpolytope.setMinus2(HPolytope2);
    Box.setMinus2(Box2);
}