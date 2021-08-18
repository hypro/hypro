/**
 * @file    BoxTest.cpp
 *
 * @covers  Box
 *
 * @author  Benedikt Seidl
 *
 * @since
 * @version 2014-05-27
 */

#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/Point.h>
#include <hypro/representations/GeometricObjectBase.h>

template <typename Number>
hypro::matrix_t<Number> createRotationMatrix( Number angle, std::size_t dimension, std::size_t first,
											  std::size_t second ) {
	hypro::matrix_t<Number> rotX = hypro::matrix_t<Number>::Identity( dimension, dimension );
	rotX( first, first ) = carl::cos( angle );
	rotX( first, second ) = -carl::sin( angle );
	rotX( second, first ) = carl::sin( angle );
	rotX( second, second ) = carl::cos( angle );
	return rotX;
}

template <typename Number>
class BoxTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		std::vector<carl::Interval<Number>> boundaries1;
		boundaries1.push_back( carl::Interval<Number>( 2, 6 ) );
		boundaries1.push_back( carl::Interval<Number>( 1, 3 ) );
		box1 = hypro::Box<Number>( boundaries1 );

		std::vector<carl::Interval<Number>> boundaries2;
		boundaries2.push_back( carl::Interval<Number>( -1, 6 ) );
		boundaries2.push_back( carl::Interval<Number>( 4, 7 ) );
		box2 = hypro::Box<Number>( boundaries2 );

		carl::Interval<Number> x = carl::Interval<Number>( -2, 2 );
		carl::Interval<Number> y = carl::Interval<Number>( 2, 4 );
		carl::Interval<Number> z = carl::Interval<Number>( -4, -2 );
		std::vector<carl::Interval<Number>> intervals1;
		intervals1.push_back( x );
		intervals1.push_back( y );
		intervals1.push_back( z );

		b1 = hypro::Box<Number>( intervals1 );

		carl::Interval<Number> a = carl::Interval<Number>( -1, 3 );
		carl::Interval<Number> b = carl::Interval<Number>( 2, 4 );
		carl::Interval<Number> c = carl::Interval<Number>( -3, 6 );
		std::vector<carl::Interval<Number>> intervals2;
		intervals2.push_back( a );
		intervals2.push_back( b );
		intervals2.push_back( c );

		b2 = hypro::Box<Number>( intervals2 );

		x = carl::Interval<Number>( 3, 5 );
		y = carl::Interval<Number>( 1, 3 );
		z = carl::Interval<Number>( 2, 5 );
		std::vector<carl::Interval<Number>> intervals3;
		intervals3.push_back( x );
		intervals3.push_back( y );
		intervals3.push_back( z );

		b3 = hypro::Box<Number>( intervals3 );

		a = carl::Interval<Number>( 1 );
		b = carl::Interval<Number>( 2, 4 );
		c = carl::Interval<Number>( -2, 3 );
		std::vector<carl::Interval<Number>> intervals4;
		intervals4.push_back( a );
		intervals4.push_back( b );
		intervals4.push_back( c );

		b4 = hypro::Box<Number>( intervals4 );
	}

	virtual void TearDown() {}

	hypro::Box<Number> box1;
	hypro::Box<Number> box2;
	hypro::Box<Number> box3;

	hypro::Box<Number> b1;
	hypro::Box<Number> b2;
	hypro::Box<Number> b3;
	hypro::Box<Number> b4;
};

TYPED_TEST( BoxTest, Constructor ) {
	hypro::Box<TypeParam> aBox = hypro::Box<TypeParam>();
	hypro::Box<TypeParam> bBox = aBox;
	hypro::Box<TypeParam> cBox = hypro::Box<TypeParam>( aBox );
	EXPECT_EQ( aBox, bBox );
	EXPECT_EQ( aBox, cBox );
	EXPECT_EQ( bBox, cBox );

	std::set<hypro::Point<TypeParam>> points;
	hypro::Point<TypeParam> p1 = hypro::Point<TypeParam>( { 1, 2 } );
	hypro::Point<TypeParam> p2 = hypro::Point<TypeParam>( { -3, 4 } );
	hypro::Point<TypeParam> p3 = hypro::Point<TypeParam>( { 0, 3 } );
	points.insert( p1 );
	points.insert( p2 );
	points.insert( p3 );

	hypro::Box<TypeParam> dBox( points );

	EXPECT_EQ( TypeParam( -3 ), dBox.min().at( 0 ) );
	EXPECT_EQ( TypeParam( 2 ), dBox.min().at( 1 ) );
	EXPECT_EQ( TypeParam( 1 ), dBox.max().at( 0 ) );
	EXPECT_EQ( TypeParam( 4 ), dBox.max().at( 1 ) );
	EXPECT_EQ( true, dBox.contains( hypro::Point<TypeParam>( { 0, 3 } ) ) );

	hypro::Box<TypeParam> b = hypro::Box<TypeParam>::Empty();
	EXPECT_TRUE( b.empty() );
}

TYPED_TEST( BoxTest, Access ) {
	std::vector<carl::Interval<TypeParam>> tmp = this->box1.intervals();
	EXPECT_EQ( 2, tmp[0].lower() );
	EXPECT_EQ( 6, tmp[0].upper() );
	EXPECT_EQ( 1, tmp[1].lower() );
	EXPECT_EQ( 3, tmp[1].upper() );

	EXPECT_EQ( (unsigned)2, this->box1.dimension() );
	EXPECT_EQ( (unsigned)2, this->box2.dimension() );
	EXPECT_EQ( (unsigned)0, this->box3.dimension() );

	EXPECT_EQ( hypro::Point<TypeParam>( { 6, 3 } ), this->box1.max() );
	EXPECT_EQ( hypro::Point<TypeParam>( { 2, 1 } ), this->box1.min() );

	EXPECT_EQ( this->box1, this->box1 );
	EXPECT_EQ( this->box2, this->box2 );
	EXPECT_EQ( this->box3, this->box3 );
	EXPECT_NE( this->box1, this->box2 );
	EXPECT_NE( this->box2, this->box3 );
	EXPECT_NE( this->box3, this->box1 );

	hypro::Box<TypeParam> emptyBox = hypro::Box<TypeParam>::Empty();
	hypro::Box<TypeParam> zeroDimBox;
	EXPECT_FALSE( this->box1.empty() );
	EXPECT_TRUE( emptyBox.empty() );
	EXPECT_TRUE( zeroDimBox.empty() );
}

TYPED_TEST( BoxTest, Insertion ) {
	std::vector<carl::Interval<TypeParam>> tmp;
	this->box1.insert( carl::Interval<TypeParam>( 3, 9 ) );
	EXPECT_EQ( true, this->box1.dimension() == 3 );

	EXPECT_EQ( 3, this->box1.interval( 2 ).lower() );
	EXPECT_EQ( 9, this->box1.interval( 2 ).upper() );

	this->box1.insert( carl::Interval<TypeParam>( 4, 5 ) );
	EXPECT_EQ( true, this->box1.dimension() == 4 );

	EXPECT_EQ( 4, this->box1.interval( 3 ).lower() );
	EXPECT_EQ( 5, this->box1.interval( 3 ).upper() );
}

TYPED_TEST( BoxTest, Vertices ) {
	std::vector<hypro::Point<TypeParam>> corners = this->b3.vertices();
	EXPECT_EQ( (unsigned)8, corners.size() );

	EXPECT_EQ( true,
			   std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 3, 1, 2 } ) ) != corners.end() );
	EXPECT_EQ( true,
			   std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 3, 1, 5 } ) ) != corners.end() );
	EXPECT_EQ( true,
			   std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 3, 3, 2 } ) ) != corners.end() );
	EXPECT_EQ( true,
			   std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 3, 3, 5 } ) ) != corners.end() );
	EXPECT_EQ( true,
			   std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 5, 1, 2 } ) ) != corners.end() );
	EXPECT_EQ( true,
			   std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 5, 1, 5 } ) ) != corners.end() );
	EXPECT_EQ( true,
			   std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 5, 3, 2 } ) ) != corners.end() );
	EXPECT_EQ( true,
			   std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 5, 3, 5 } ) ) != corners.end() );
}

TYPED_TEST( BoxTest, Union ) {
	hypro::Box<TypeParam> result = this->b3.unite( this->b2 );

	EXPECT_EQ( TypeParam( -1 ), result.min().at( 0 ) );
	EXPECT_EQ( TypeParam( 1 ), result.min().at( 1 ) );
	EXPECT_EQ( TypeParam( -3 ), result.min().at( 2 ) );
	EXPECT_EQ( TypeParam( 5 ), result.max().at( 0 ) );
	EXPECT_EQ( TypeParam( 4 ), result.max().at( 1 ) );
	EXPECT_EQ( TypeParam( 6 ), result.max().at( 2 ) );
}

TYPED_TEST( BoxTest, LinearTransformation ) {
	carl::Interval<TypeParam> x = carl::Interval<TypeParam>( -2, 2 );
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>( 2, 4 );
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>( -4, -2 );
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back( x );
	intervals1.push_back( y );
	intervals1.push_back( z );

	hypro::Box<TypeParam> b1( intervals1 );

	// rotation
	TypeParam angle = 90;

	hypro::matrix_t<TypeParam> rotX = createRotationMatrix( angle, 3, 1, 2 );
	hypro::matrix_t<TypeParam> rotY = createRotationMatrix( angle, 3, 0, 2 );
	hypro::matrix_t<TypeParam> rotZ = createRotationMatrix( angle, 3, 0, 1 );

	// result
	hypro::Box<TypeParam> resX = b1.linearTransformation( rotX );
	hypro::Box<TypeParam> resY = b1.linearTransformation( rotY );
	hypro::Box<TypeParam> resZ = b1.linearTransformation( rotZ );

	std::vector<hypro::Point<TypeParam>> cornersX = resX.vertices();

	std::vector<hypro::Point<TypeParam>> originalCorners = b1.vertices();
	std::vector<hypro::Point<TypeParam>> newCorners;
	for ( auto& point : originalCorners ) {
		newCorners.push_back( hypro::Point<TypeParam>( rotX * point.rawCoordinates() ) );
	}
	EXPECT_EQ( resX, hypro::Box<TypeParam>( newCorners ) );

	newCorners.clear();
	std::vector<hypro::Point<TypeParam>> cornersY = resY.vertices();
	for ( auto& point : originalCorners ) {
		newCorners.push_back( hypro::Point<TypeParam>( rotY * point.rawCoordinates() ) );
	}
	EXPECT_EQ( resY, hypro::Box<TypeParam>( newCorners ) );

	newCorners.clear();
	std::vector<hypro::Point<TypeParam>> cornersZ = resZ.vertices();
	for ( auto& point : originalCorners ) {
		newCorners.push_back( hypro::Point<TypeParam>( rotZ * point.rawCoordinates() ) );
	}
	EXPECT_EQ( resZ, hypro::Box<TypeParam>( newCorners ) );
}

TYPED_TEST( BoxTest, affineTransformation ) {
	// rotation
	TypeParam angle = 90;

	hypro::matrix_t<TypeParam> rotX = createRotationMatrix( angle, 3, 1, 2 );
	hypro::matrix_t<TypeParam> rotY = createRotationMatrix( angle, 3, 0, 2 );
	hypro::matrix_t<TypeParam> rotZ = createRotationMatrix( angle, 3, 0, 1 );

	hypro::vector_t<TypeParam> offset = hypro::vector_t<TypeParam>::Zero( 3 );

	// result
	hypro::Box<TypeParam> resX = this->b1.affineTransformation( rotX, offset );
	hypro::Box<TypeParam> resY = this->b1.affineTransformation( rotY, offset );
	hypro::Box<TypeParam> resZ = this->b1.affineTransformation( rotZ, offset );

	std::vector<hypro::Point<TypeParam>> cornersX = resX.vertices();

	std::vector<hypro::Point<TypeParam>> originalCorners = this->b1.vertices();
	std::vector<hypro::Point<TypeParam>> newCorners;
	for ( auto& point : originalCorners ) {
		newCorners.push_back( hypro::Point<TypeParam>( rotX * point.rawCoordinates() ) );
	}
	EXPECT_EQ( resX, hypro::Box<TypeParam>( newCorners ) );

	newCorners.clear();
	std::vector<hypro::Point<TypeParam>> cornersY = resY.vertices();
	for ( auto& point : originalCorners ) {
		newCorners.push_back( hypro::Point<TypeParam>( rotY * point.rawCoordinates() ) );
	}
	EXPECT_EQ( resY, hypro::Box<TypeParam>( newCorners ) );

	newCorners.clear();
	std::vector<hypro::Point<TypeParam>> cornersZ = resZ.vertices();
	for ( auto& point : originalCorners ) {
		newCorners.push_back( hypro::Point<TypeParam>( rotZ * point.rawCoordinates() ) );
	}
	EXPECT_EQ( resZ, hypro::Box<TypeParam>( newCorners ) );

	offset << TypeParam( 1 ), TypeParam( 1 ), TypeParam( 1 );

	// result with shifting
	resX = this->b1.affineTransformation( rotX, offset );
	resY = this->b1.affineTransformation( rotY, offset );
	resZ = this->b1.affineTransformation( rotZ, offset );

	cornersX = resX.vertices();

	originalCorners = this->b1.vertices();
	newCorners.clear();
	for ( auto& point : originalCorners ) {
		newCorners.push_back( hypro::Point<TypeParam>( rotX * point.rawCoordinates() + offset ) );
	}
	EXPECT_EQ( resX, hypro::Box<TypeParam>( newCorners ) );

	newCorners.clear();
	cornersY = resY.vertices();
	for ( auto& point : originalCorners ) {
		newCorners.push_back( hypro::Point<TypeParam>( rotY * point.rawCoordinates() + offset ) );
	}
	EXPECT_EQ( resY, hypro::Box<TypeParam>( newCorners ) );

	newCorners.clear();
	cornersZ = resZ.vertices();
	for ( auto& point : originalCorners ) {
		newCorners.push_back( hypro::Point<TypeParam>( rotZ * point.rawCoordinates() + offset ) );
	}
	EXPECT_EQ( resZ, hypro::Box<TypeParam>( newCorners ) );
}

TYPED_TEST( BoxTest, MinkowskiSum ) {
	hypro::Box<TypeParam> result;
	result = this->box1.minkowskiSum( this->box2 );
	EXPECT_EQ( 1, result.interval( 0 ).lower() );
	EXPECT_EQ( 12, result.interval( 0 ).upper() );
	EXPECT_EQ( 5, result.interval( 1 ).lower() );
	EXPECT_EQ( 10, result.interval( 1 ).upper() );

	hypro::Box<TypeParam> res = this->b1.minkowskiSum( this->b4 );
	std::vector<hypro::Point<TypeParam>> corners = res.vertices();

	EXPECT_TRUE( std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { -1, 4, -6 } ) ) !=
				 corners.end() );
	EXPECT_TRUE( std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { -1, 4, 1 } ) ) !=
				 corners.end() );
	EXPECT_TRUE( std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { -1, 8, -6 } ) ) !=
				 corners.end() );
	EXPECT_TRUE( std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { -1, 8, 1 } ) ) !=
				 corners.end() );
	EXPECT_TRUE( std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 3, 4, -6 } ) ) !=
				 corners.end() );
	EXPECT_TRUE( std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 3, 4, 1 } ) ) != corners.end() );
	EXPECT_TRUE( std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 3, 8, -6 } ) ) !=
				 corners.end() );
	EXPECT_TRUE( std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>( { 3, 8, 1 } ) ) != corners.end() );
}

TYPED_TEST( BoxTest, MinkowskiDecomposition ) {
	hypro::Box<TypeParam> result;
	result = this->box2.minkowskiDecomposition( this->box1 );
	EXPECT_EQ( -3, result.interval( 0 ).lower() );
	EXPECT_EQ( 0, result.interval( 0 ).upper() );
	EXPECT_EQ( 3, result.interval( 1 ).lower() );
	EXPECT_EQ( 4, result.interval( 1 ).upper() );

	result = this->box2.minkowskiDecomposition( this->box2 );
	EXPECT_EQ( 0, result.interval( 0 ).lower() );
	EXPECT_EQ( 0, result.interval( 0 ).upper() );
	EXPECT_EQ( 0, result.interval( 1 ).lower() );
	EXPECT_EQ( 0, result.interval( 1 ).upper() );
}

TYPED_TEST( BoxTest, makeSymmetric ) {
	hypro::Box<TypeParam> result;
	result = this->box1.makeSymmetric();
	EXPECT_EQ( -6, result.interval( 0 ).lower() );
	EXPECT_EQ( 6, result.interval( 0 ).upper() );
	EXPECT_EQ( -3, result.interval( 1 ).lower() );
	EXPECT_EQ( 3, result.interval( 1 ).upper() );

	result = this->box2.makeSymmetric();
	EXPECT_EQ( -6, result.interval( 0 ).lower() );
	EXPECT_EQ( 6, result.interval( 0 ).upper() );
	EXPECT_EQ( -7, result.interval( 1 ).lower() );
	EXPECT_EQ( 7, result.interval( 1 ).upper() );
}

TYPED_TEST( BoxTest, Intersection ) {
	hypro::Box<TypeParam> result;
	result = this->box1.intersect( this->box2 );

	EXPECT_TRUE( result.empty() );

	carl::Interval<TypeParam> x = carl::Interval<TypeParam>( -2, 2 );
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>( 2, 4 );
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>( -4, -2 );

	carl::Interval<TypeParam> a = carl::Interval<TypeParam>( 1 );
	carl::Interval<TypeParam> b = carl::Interval<TypeParam>( 2, 4 );
	carl::Interval<TypeParam> c = carl::Interval<TypeParam>( -2, 3 );

	hypro::Box<TypeParam> res = this->b1.intersect( this->b4 );
	carl::Interval<TypeParam> i = set_intersection( x, a );
	carl::Interval<TypeParam> j = set_intersection( y, b );
	carl::Interval<TypeParam> k = set_intersection( z, c );
	std::vector<carl::Interval<TypeParam>> intervals;
	intervals.push_back( i );
	intervals.push_back( j );
	intervals.push_back( k );

	EXPECT_EQ( hypro::Box<TypeParam>( intervals ), res );

	hypro::Box<TypeParam> empt1 = this->box1.intersect( hypro::Box<TypeParam>::Empty() );
	EXPECT_TRUE( empt1.empty() );

	auto empt2 = hypro::Box<TypeParam>::Empty();
	EXPECT_TRUE( empt2.empty() );

	auto empt3 = hypro::Box<TypeParam>::Empty().intersect( this->box1 );
	EXPECT_TRUE( empt3.empty() );

	auto empt4 = hypro::Box<TypeParam>::Empty().intersect( hypro::Box<TypeParam>::Empty() );
	EXPECT_TRUE( empt4.empty() );

	hypro::Box<TypeParam> reduced = this->box1.intersect( hypro::Box<TypeParam>( carl::Interval<TypeParam>( 3, 4 ) ) );
	std::vector<carl::Interval<TypeParam>> its;
	its.emplace_back( 3, 4 );
	its.emplace_back( 1, 3 );
	EXPECT_EQ( reduced, hypro::Box<TypeParam>( its ) );
}

TYPED_TEST( BoxTest, IntersectionHalfspace ) {
	hypro::Box<TypeParam> res1 = this->box1.intersectHalfspace( hypro::Halfspace<TypeParam>( { 1, 1 }, 4 ) );
	hypro::Box<TypeParam> res2 = this->box1.intersectHalfspace( hypro::Halfspace<TypeParam>( { 1, 1 }, 5 ) );
	hypro::Box<TypeParam> res3 = this->box1.intersectHalfspace( hypro::Halfspace<TypeParam>( { 1, 1 }, 6 ) );
	hypro::Box<TypeParam> res4 = this->box1.intersectHalfspace( hypro::Halfspace<TypeParam>( { 1, 1 }, 9 ) );
	hypro::Box<TypeParam> res5 = this->box1.intersectHalfspace( hypro::Halfspace<TypeParam>( { 1, 1 }, 10 ) );
	hypro::Box<TypeParam> res6 = this->box1.intersectHalfspace( hypro::Halfspace<TypeParam>( { 1, 0 }, 3 ) );
	hypro::Box<TypeParam> res7 = this->box1.intersectHalfspace( hypro::Halfspace<TypeParam>( { 1, 1 }, 3 ) );
	hypro::Box<TypeParam> res8 = this->box1.intersectHalfspace( hypro::Halfspace<TypeParam>( { 1, 0 }, 2 ) );

	std::vector<carl::Interval<TypeParam>> i1;
	std::vector<carl::Interval<TypeParam>> i2;
	std::vector<carl::Interval<TypeParam>> i3;
	std::vector<carl::Interval<TypeParam>> i4;
	std::vector<carl::Interval<TypeParam>> i5;
	std::vector<carl::Interval<TypeParam>> i6;
	std::vector<carl::Interval<TypeParam>> i7;
	std::vector<carl::Interval<TypeParam>> i8;

	i1.push_back( carl::Interval<TypeParam>( 2, 3 ) );
	i1.push_back( carl::Interval<TypeParam>( 1, 2 ) );
	EXPECT_EQ( res1, hypro::Box<TypeParam>( i1 ) );

	i2.push_back( carl::Interval<TypeParam>( 2, 4 ) );
	i2.push_back( carl::Interval<TypeParam>( 1, 3 ) );
	EXPECT_EQ( res2, hypro::Box<TypeParam>( i2 ) );

	i3.push_back( carl::Interval<TypeParam>( 2, 5 ) );
	i3.push_back( carl::Interval<TypeParam>( 1, 3 ) );
	EXPECT_EQ( res3, hypro::Box<TypeParam>( i3 ) );

	i4.push_back( carl::Interval<TypeParam>( 2, 6 ) );
	i4.push_back( carl::Interval<TypeParam>( 1, 3 ) );
	EXPECT_EQ( res4, hypro::Box<TypeParam>( i4 ) );

	i5.push_back( carl::Interval<TypeParam>( 2, 6 ) );
	i5.push_back( carl::Interval<TypeParam>( 1, 3 ) );
	EXPECT_EQ( res5, hypro::Box<TypeParam>( i5 ) );

	i6.push_back( carl::Interval<TypeParam>( 2, 3 ) );
	i6.push_back( carl::Interval<TypeParam>( 1, 3 ) );
	EXPECT_EQ( res6, hypro::Box<TypeParam>( i6 ) );

	i7.push_back( carl::Interval<TypeParam>( 2, 2 ) );
	i7.push_back( carl::Interval<TypeParam>( 1, 1 ) );
	EXPECT_EQ( res7, hypro::Box<TypeParam>( i7 ) );

	i8.push_back( carl::Interval<TypeParam>( 2, 2 ) );
	i8.push_back( carl::Interval<TypeParam>( 1, 3 ) );
	EXPECT_EQ( res8, hypro::Box<TypeParam>( i8 ) );
}

TYPED_TEST( BoxTest, Membership ) {
	hypro::Point<TypeParam> p( { 4, 2 } );
	EXPECT_TRUE( this->box1.contains( p ) );
}

TYPED_TEST( BoxTest, NumberReduction ) {
	carl::Interval<TypeParam> xInterval( carl::rationalize<TypeParam>( 0.01 ), carl::rationalize<TypeParam>( 0.02 ) );
	carl::Interval<TypeParam> yInterval( carl::rationalize<TypeParam>( -1.02 ), carl::rationalize<TypeParam>( -1.01 ) );

	hypro::Box<TypeParam> box;
	box.insert( xInterval );
	box.insert( yInterval );

	EXPECT_TRUE( box.reduceNumberRepresentation( 2 ).contains( box ) || box == box.reduceNumberRepresentation() );
}

TYPED_TEST( BoxTest, SatisfiesHalfspace ) {
	carl::Interval<TypeParam> xInterval( TypeParam( 1 ), TypeParam( 2 ) );
	hypro::Box<TypeParam> box;
	box.insert( xInterval );

	hypro::Halfspace<TypeParam> hsp1( { 1 }, 3 );
	hypro::Halfspace<TypeParam> hsp2( { 1 }, 0 );
	hypro::Halfspace<TypeParam> hsp3( { 1 }, 1 );

	EXPECT_EQ( box.satisfiesHalfspace( hsp1 ).first, hypro::CONTAINMENT::FULL );
	EXPECT_EQ( box.satisfiesHalfspace( hsp2 ).first, hypro::CONTAINMENT::NO );
	EXPECT_EQ( box.satisfiesHalfspace( hsp3 ).first, hypro::CONTAINMENT::PARTIAL );
	EXPECT_TRUE( box.satisfiesHalfspaces( hypro::matrix_t<TypeParam>(), hypro::vector_t<TypeParam>() ).first !=
				 hypro::CONTAINMENT::NO );
	hypro::matrix_t<TypeParam> mat = hypro::matrix_t<TypeParam>( 2, 1 );
	mat << 1, -1;
	hypro::vector_t<TypeParam> vec = hypro::vector_t<TypeParam>( 2 );
	vec << 2, -2;

	EXPECT_EQ( box.satisfiesHalfspaces( mat, vec ).first, hypro::CONTAINMENT::PARTIAL );
	EXPECT_EQ( box.satisfiesHalfspaces( mat, vec ).second,
			   hypro::Box<TypeParam>(
					 std::make_pair( hypro::Point<TypeParam>( { 2 } ), hypro::Point<TypeParam>( { 2 } ) ) ) );
	vec << 3, -4;
	EXPECT_EQ( box.satisfiesHalfspaces( mat, vec ).first, hypro::CONTAINMENT::NO );
	EXPECT_TRUE( box.satisfiesHalfspaces( mat, vec ).second.empty() );
	vec << 3, 1;
	EXPECT_EQ( box.satisfiesHalfspaces( mat, vec ).first, hypro::CONTAINMENT::FULL );
	EXPECT_EQ( box.satisfiesHalfspaces( mat, vec ).second, box );
}

TYPED_TEST( BoxTest, SatisfiesHalfspaceOpenBox ) {
	carl::Interval<TypeParam> xInterval( TypeParam( 1 ), TypeParam( 2 ) );
	carl::Interval<TypeParam> yInterval( TypeParam( 0 ), TypeParam( 1 ) );
	yInterval.setLowerBoundType( carl::BoundType::STRICT );

	hypro::Box<TypeParam> box;
	box.insert( xInterval );
	box.insert( yInterval );

	hypro::Halfspace<TypeParam> hsp1( { 1, 0 }, 3 );
	hypro::Halfspace<TypeParam> hsp2( { 1, 0 }, 0 );
	hypro::Halfspace<TypeParam> hsp3( { 1, 0 }, 1 );

	EXPECT_EQ( hypro::CONTAINMENT::FULL, box.satisfiesHalfspace( hsp1 ).first );
	EXPECT_EQ( hypro::CONTAINMENT::NO, box.satisfiesHalfspace( hsp2 ).first );
	EXPECT_EQ( hypro::CONTAINMENT::PARTIAL, box.satisfiesHalfspace( hsp3 ).first );

	EXPECT_TRUE( box.satisfiesHalfspaces( hypro::matrix_t<TypeParam>(), hypro::vector_t<TypeParam>() ).first !=
				 hypro::CONTAINMENT::NO );
	hypro::matrix_t<TypeParam> mat = hypro::matrix_t<TypeParam>( 2, 2 );
	mat << 1, 0, -1, 0;
	hypro::vector_t<TypeParam> vec = hypro::vector_t<TypeParam>( 2 );
	vec << 2, -2;

	EXPECT_EQ( hypro::CONTAINMENT::PARTIAL, box.satisfiesHalfspaces( mat, vec ).first );
	EXPECT_EQ( hypro::Box<TypeParam>( std::vector<carl::Interval<TypeParam>>{
					 carl::Interval( TypeParam( 2 ), TypeParam( 2 ) ), yInterval } ),
			   box.satisfiesHalfspaces( mat, vec ).second );
	vec << 3, -4;
	EXPECT_EQ( hypro::CONTAINMENT::NO, box.satisfiesHalfspaces( mat, vec ).first );
	EXPECT_TRUE( box.satisfiesHalfspaces( mat, vec ).second.empty() );
	vec << 3, 1;
	EXPECT_EQ( hypro::CONTAINMENT::FULL, box.satisfiesHalfspaces( mat, vec ).first );
	EXPECT_EQ( box, box.satisfiesHalfspaces( mat, vec ).second );

	// test that y == 0 is not contained in the box
	mat << 0, 1, 0, -1;
	vec << 0, 0;
	EXPECT_EQ( hypro::CONTAINMENT::NO, box.satisfiesHalfspaces( mat, vec ).first );
	vec << 1, -1;
	EXPECT_EQ( hypro::CONTAINMENT::PARTIAL, box.satisfiesHalfspaces( mat, vec ).first );
}

TYPED_TEST( BoxTest, Projection ) {
	carl::Interval<TypeParam> xInterval( TypeParam( 1 ), TypeParam( 2 ) );
	carl::Interval<TypeParam> yInterval( carl::rationalize<TypeParam>( -1.02 ), carl::rationalize<TypeParam>( -1.01 ) );
	hypro::Box<TypeParam> box;
	box.insert( xInterval );
	box.insert( yInterval );

	std::vector<std::size_t> dims;
	dims.push_back( 0 );

	EXPECT_EQ( box.projectOn( dims ), hypro::Box<TypeParam>( std::make_pair( hypro::Point<TypeParam>( { 1 } ),
																			 hypro::Point<TypeParam>( { 2 } ) ) ) );
	EXPECT_EQ( box.projectOn( std::vector<std::size_t>() ), hypro::Box<TypeParam>::Empty() );
}

TYPED_TEST( BoxTest, SettingsConversion ) {
	hypro::Point<TypeParam> p1( { 1, 1 } );
	hypro::Point<TypeParam> p2( { 2, 2 } );
	hypro::BoxT<TypeParam, hypro::Converter<TypeParam>, hypro::BoxLinearOptimizationOn> box1(
		  std::make_pair( p1, p2 ) );
	hypro::BoxT<TypeParam, hypro::Converter<TypeParam>, hypro::BoxLinearOptimizationOff> box2( box1 );
	EXPECT_EQ( box2.limits().first, p1 );
	EXPECT_EQ( box2.limits().second, p2 );
	EXPECT_EQ( box1, box2 );
}

TYPED_TEST( BoxTest, Evaluation ) {
	hypro::Point<TypeParam> p1( { -1, -1 } );
	hypro::Point<TypeParam> p2( { 1, 1 } );
	hypro::BoxT<TypeParam, hypro::Converter<TypeParam>, hypro::BoxLinearOptimizationOn> box1(
		  std::make_pair( p1, p2 ) );
	hypro::vector_t<TypeParam> dirVec = hypro::vector_t<TypeParam>::Zero( 2 );
	dirVec << 1, 0;
	hypro::EvaluationResult<TypeParam> res = box1.evaluate( dirVec, true );
	EXPECT_EQ( res.supportValue, 1 );
	EXPECT_EQ( res.errorCode, hypro::SOLUTION::FEAS );

	hypro::matrix_t<TypeParam> dirMat = hypro::matrix_t<TypeParam>::Zero( 3, 2 );
	dirMat << 1, 0, 0, -1, 1, 1;
	std::vector<hypro::EvaluationResult<TypeParam>> allRes = box1.multiEvaluate( dirMat, true );
	EXPECT_EQ( allRes.at( 0 ).supportValue, 1 );
	EXPECT_EQ( allRes.at( 0 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( allRes.at( 1 ).supportValue, 1 );
	EXPECT_EQ( allRes.at( 1 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( allRes.at( 2 ).supportValue, 2 );
	EXPECT_EQ( allRes.at( 2 ).errorCode, hypro::SOLUTION::FEAS );
}