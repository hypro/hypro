/**
 *  Testfile for the point datastructure.
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Benedikt Seidl
 */

#include "../../hypro/datastructures/Point.h"
#include "../defines.h"
#include "gtest/gtest.h"
#include <carl/interval/Interval.h>


using namespace hypro;

template <typename Number>
class PointTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		pool.clear();
		x = pool.carlVarByIndex( 0 );
		y = pool.carlVarByIndex( 1 );
		a = pool.carlVarByIndex( 2 );
		b = pool.carlVarByIndex( 3 );
		// p1
		p1 = Point<Number>( { 2, 5 } );

		// p2
		p2 = Point<Number>( { 7, 8 } );

		// p3
		p3 = Point<Number>( { 9, -13 } );

		// p4
		p4 = Point<Number>( { 5, 8 } );
	}

	virtual void TearDown() {}

	hypro::VariablePool& pool = hypro::VariablePool::getInstance();
	carl::Variable x;
	carl::Variable y;
	carl::Variable a;
	carl::Variable b;

	Point<Number> p1;
	Point<Number> p2;
	Point<Number> p3;
	Point<Number> p4;
};

TYPED_TEST( PointTest, Constructor ) {
	Point<TypeParam> p;
	EXPECT_EQ( p.dimension(), (unsigned)0 );

	p = Point<TypeParam>( 5 );
	EXPECT_EQ( p.dimension(), (unsigned)1 );

	p = Point<TypeParam>( { 5, 0, 5, 2, 2, 2, 2, 2 } );

	EXPECT_EQ( p.dimension(), (unsigned)8 );
	EXPECT_EQ( p[2], TypeParam( 5 ) );
	EXPECT_EQ( p[1], TypeParam( 0 ) );
	EXPECT_EQ( p[0], TypeParam( 5 ) );

	Point<TypeParam> pCopy( p );
	EXPECT_TRUE( p == pCopy );

	Point<TypeParam> empty = this->p1.newEmpty();
	EXPECT_EQ( this->p1.dimension(), empty.dimension() );
	EXPECT_TRUE( this->p1.haveSameDimensions( empty ) );
	EXPECT_EQ( 0, empty[1] );

	Point<TypeParam> tmp( { 123, 456 } );
	EXPECT_EQ( tmp[0], TypeParam( 123 ) );
	EXPECT_EQ( tmp[1], TypeParam( 456 ) );

	swap( p, tmp );
	EXPECT_EQ( p[0], TypeParam( 123 ) );
	EXPECT_EQ( p[1], TypeParam( 456 ) );
}

TYPED_TEST( PointTest, PolarCoordinates ) {
	std::vector<TypeParam> pc = this->p1.polarCoordinates( this->p1.origin(), false );
	std::pair<TypeParam, TypeParam> expectedRes;

	expectedRes = carl::sqrt_safe( TypeParam( 29 ) );

	// special case: Use double comparison
	EXPECT_TRUE( carl::Interval<TypeParam>( expectedRes.first, expectedRes.second ).contains( pc.at( 0 ) ) );

	pc = this->p2.polarCoordinates( this->p2.origin(), false );
	expectedRes = carl::sqrt_safe( TypeParam( 113 ) );

	EXPECT_TRUE( carl::Interval<TypeParam>( expectedRes.first, expectedRes.second ).contains( pc.at( 0 ) ) );

	pc = this->p3.polarCoordinates( this->p3.origin(), false );
	expectedRes = carl::sqrt_safe( TypeParam( 250 ) );

	EXPECT_TRUE( carl::Interval<TypeParam>( expectedRes.first, expectedRes.second ).contains( pc.at( 0 ) ) );

	pc = this->p4.polarCoordinates( this->p4.origin(), false );
	expectedRes = carl::sqrt_safe( TypeParam( 89 ) );

	EXPECT_TRUE( carl::Interval<TypeParam>( expectedRes.first, expectedRes.second ).contains( pc.at( 0 ) ) );
}

/**
 * @covers Point::coordinate
 * @covers Point::dimension
 * @covers Point::IncrementInFixedDim
 * @covers Point::IncrementInAllDim
 * @covers Point::DecrementInFixedDim
 * @covers Point::setCoordinate
 */
TYPED_TEST( PointTest, CoordinateDimensionTest ) {
	EXPECT_EQ( this->p1[0], TypeParam( 2 ) );
	EXPECT_EQ( this->p1[1], TypeParam( 5 ) );
	EXPECT_EQ( this->p1.coordinate( 0 ), TypeParam( 2 ) );
	EXPECT_EQ( this->p1.coordinate( 1 ), TypeParam( 5 ) );
	EXPECT_EQ( this->p1.dimension(), (unsigned)2 );

	this->p1.incrementInFixedDim( 1 );
	EXPECT_EQ( this->p1[1], TypeParam( 6 ) );
	this->p1.incrementInAllDim( TypeParam( 3 ) );
	EXPECT_EQ( this->p1[0], TypeParam( 5 ) );
	EXPECT_EQ( this->p1[1], TypeParam( 9 ) );
	this->p1.decrementInFixedDim( 1 );
	EXPECT_EQ( this->p1[1], TypeParam( 8 ) );

	this->p1[this->x] = TypeParam( 3 );
	this->p1[this->y] = TypeParam( -1 );
	EXPECT_EQ( this->p1[this->x], TypeParam( 3 ) );
	EXPECT_EQ( this->p1[this->y], TypeParam( -1 ) );
	this->p1.setCoordinate( this->x, 4 );
	this->p1.setCoordinate( this->y, 7 );
	EXPECT_EQ( this->p1[this->x], TypeParam( 4 ) );
	EXPECT_EQ( this->p1[this->y], TypeParam( 7 ) );

	this->p1.setCoordinate( 4, 14 );
	EXPECT_EQ( this->p1[this->x], TypeParam( 4 ) );
	EXPECT_EQ( this->p1[this->y], TypeParam( 7 ) );
	EXPECT_EQ( this->p1[4], TypeParam( 14 ) );

	this->p1.setCoordinate( VariablePool::getInstance().carlVarByIndex( 5 ), 3 );
	EXPECT_EQ( this->p1[this->x], TypeParam( 4 ) );
	EXPECT_EQ( this->p1[this->y], TypeParam( 7 ) );
	EXPECT_EQ( this->p1[4], TypeParam( 14 ) );
	EXPECT_EQ( this->p1[5], TypeParam( 3 ) );
}

/**
 * @covers Point::move
 */
TYPED_TEST( PointTest, OperationTest ) {
	Point<TypeParam> res;
	res = this->p1.extAdd( this->p1 );
	EXPECT_EQ( res[0], TypeParam( 4 ) );
	EXPECT_EQ( res[1], TypeParam( 10 ) );

	res = this->p2.extAdd( this->p3 );
	EXPECT_EQ( res[0], TypeParam( 16 ) );
	EXPECT_EQ( res[1], TypeParam( -5 ) );
}

TYPED_TEST( PointTest, DimensionTest ) {
	this->p1.setCoordinate( this->a, 14 );
	EXPECT_EQ( this->p1.dimension(), std::size_t( 3 ) );

	std::vector<std::size_t> dims;
	dims.push_back( 0 );
	dims.push_back( 2 );
	this->p1 = this->p1.reduceToDimensions( dims );
	EXPECT_EQ( std::size_t( 2 ), this->p1.dimension() );
}

/**
 * @covers <>
 */
TYPED_TEST( PointTest, BinaryOperatorTest ) {
	EXPECT_FALSE( this->p4 > this->p3 );
	EXPECT_FALSE( this->p3 < this->p4 );
	EXPECT_TRUE( this->p4 < this->p3 );
	EXPECT_TRUE( this->p3 > this->p4 );
	EXPECT_FALSE( this->p4 < this->p4 );
	EXPECT_FALSE( this->p4 > this->p4 );
	EXPECT_TRUE( this->p4 == this->p4 );
	EXPECT_FALSE( this->p3 == this->p4 );
}

/**
 * @covers Point::isInBoundary
 * @covers Point::compareReducedDimension
 * @covers Point::haveEqualCoordinate
 */
TYPED_TEST( PointTest, BooleanTest ) {
	EXPECT_TRUE( this->p1.isInBoundary( this->p2 ) );
	EXPECT_FALSE( this->p2.isInBoundary( this->p1 ) );
	EXPECT_FALSE( this->p1.isInBoundary( this->p1 ) );

	this->p1[1] = TypeParam( 3 );

	EXPECT_TRUE( this->p1.hasDimension( this->x ) );
	EXPECT_FALSE( this->p1.hasDimension( this->a ) );
	EXPECT_TRUE( this->p2.hasDimension( this->x ) );
	EXPECT_FALSE( this->p2.hasDimension( this->a ) );

	this->p2[0] = TypeParam( 2 );
	this->p2[1] = TypeParam( 5 );

	EXPECT_TRUE( this->p1.haveEqualCoordinate( this->p1 ) );
	EXPECT_FALSE( this->p1.haveEqualCoordinate( this->p3 ) );
	//    this->p2.removeDimension(this->a);
	//    this->p2.removeDimension(this->b);
	//    EXPECT_LT(this->p1, this->p2);

	this->p2[1] = TypeParam( 3 );
	//    this->p2.removeDimension(this->a);

	EXPECT_EQ( this->p1, this->p2 );
	EXPECT_NE( this->p1, this->p3 );

	EXPECT_TRUE( this->p3.haveSameDimensions( this->p4 ) );
	EXPECT_TRUE( this->p2.haveSameDimensions( this->p4 ) );

	//    EXPECT_TRUE(this->p1.hasDimensions(this->p1.variables()));
	//    EXPECT_TRUE(this->p2.hasDimensions(this->p2.variables()));
	//    EXPECT_TRUE(this->p3.hasDimensions(this->p3.variables()));
	//    EXPECT_TRUE(this->p4.hasDimensions(this->p4.variables()));
	//    EXPECT_FALSE(this->p1.hasDimensions(this->p4.variables()));
	//    EXPECT_FALSE(this->p4.hasDimensions(this->p1.variables()));
	//    EXPECT_TRUE(this->p3.hasDimensions(this->p4.variables()));
	//    EXPECT_TRUE(this->p4.hasDimensions(this->p3.variables()));
}

TYPED_TEST( PointTest, AffineTransformation ) {
	typename hypro::matrix_t<TypeParam> A = createMatrix( std::vector<std::vector<TypeParam>>(
		  { std::vector<TypeParam>( { 4, 5 } ), std::vector<TypeParam>( { -2, 3 } ) } ) );

	typename hypro::vector_t<TypeParam> v = createVector( std::vector<TypeParam>( { 6, 1 } ) );

	EXPECT_EQ( Point<TypeParam>( { 39, 12 } ), this->p1.affineTransformation( A, v ) );
	EXPECT_EQ( Point<TypeParam>( { 74, 11 } ), this->p2.affineTransformation( A, v ) );
	EXPECT_EQ( Point<TypeParam>( { -23, -56 } ), this->p3.affineTransformation( A, v ) );
	EXPECT_EQ( Point<TypeParam>( { 66, 15 } ), this->p4.affineTransformation( A, v ) );
}

TYPED_TEST( PointTest, Projection ) {
	Point<TypeParam> p1( { 1, 2, 3, 4, 5, 6, 7 } );
	std::vector<std::size_t> dims;
	Point<TypeParam> empt = p1.projectOn( dims );
	EXPECT_EQ( empt.dimension(), unsigned( 0 ) );

	dims.push_back( 0 );
	dims.push_back( 1 );
	dims.push_back( 4 );
	dims.push_back( 5 );

	p1 = p1.projectOn( dims );
	EXPECT_EQ( p1, Point<TypeParam>( { 1, 2, 5, 6 } ) );
}

/*
TYPED_TEST(PointTest, Neighbors) {
	Point<TypeParam> a = Point<TypeParam>({1,1});
	Point<TypeParam> b = Point<TypeParam>({1,1});
	Point<TypeParam> c = Point<TypeParam>({1,1});
	Point<TypeParam> d = Point<TypeParam>({1,1});

	a.addNeighbor(b);
	EXPECT_TRUE(a.isNeighbor(b));
	EXPECT_TRUE(b.isNeighbor(a));
	EXPECT_FALSE(a.isNeighbor(c));
	EXPECT_TRUE(std::find(a.neighbors().begin(), a.neighbors().end(), b) != a.neighbors().end());
	EXPECT_TRUE(std::find(a.neighbors().begin(), a.neighbors().end(), c) == a.neighbors().end());
	a.removeNeighbor(b);
	EXPECT_TRUE(a.neighbors().empty());
	EXPECT_FALSE(a.isNeighbor(b));
}
*/

TYPED_TEST( PointTest, RemoveDuplicates ) {
	std::vector<Point<TypeParam>> points;
	points.emplace_back( Point<TypeParam>( { 1, 2 } ) );
	points.emplace_back( Point<TypeParam>( { 1, 2 } ) );
	points.emplace_back( Point<TypeParam>( { 1, 1 } ) );
	points.emplace_back( Point<TypeParam>( { 0, 2 } ) );
	points.emplace_back( Point<TypeParam>( { 3, 2 } ) );
	points.emplace_back( Point<TypeParam>( { 0, 2 } ) );

	points = Point<TypeParam>::removeDuplicatePoints( points );
	for ( const auto& p : points ) {
		std::cout << p << std::endl;
	}
	EXPECT_TRUE( std::count( points.begin(), points.end(), Point<TypeParam>( { 1, 2 } ) ) == 1 );
	EXPECT_TRUE( std::count( points.begin(), points.end(), Point<TypeParam>( { 1, 1 } ) ) == 1 );
	EXPECT_TRUE( std::count( points.begin(), points.end(), Point<TypeParam>( { 0, 2 } ) ) == 1 );
	EXPECT_TRUE( std::count( points.begin(), points.end(), Point<TypeParam>( { 3, 2 } ) ) == 1 );
}

TYPED_TEST( PointTest, Addition ) {
	Point<TypeParam> p1( { 1, 2 } );
	Point<TypeParam> p2( { 1, 2 } );
	EXPECT_EQ( p1 + p2, Point<TypeParam>( { 2, 4 } ) );
	Point<TypeParam> p3( { -1, -2 } );
	EXPECT_EQ( p1 + p3, Point<TypeParam>( { 0, 0 } ) );
}

template <typename N>
struct cmpTest {
	bool operator()( const hypro::Point<N>& lhs, const hypro::Point<N>& rhs ) const { return lhs < rhs; }
};

TYPED_TEST( PointTest, SortedVector ) {
	std::vector<hypro::Point<TypeParam>> points = {
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  hypro::Point<TypeParam>{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};
	auto pointsSortedOnce = points;
	TRACE( "hypro.core", "Start sorting." );
	std::sort( pointsSortedOnce.begin(), pointsSortedOnce.end(), cmpTest<TypeParam>() );
	TRACE( "hypro.core", "Done sorting." );
	std::cout << "original:" << std::endl;
	for ( const auto& p : points ) {
		std::cout << p << std::endl;
	}
	std::cout << "sorted:" << std::endl;
	for ( const auto& p : pointsSortedOnce ) {
		std::cout << p << std::endl;
	}

	EXPECT_EQ( points, pointsSortedOnce );	// gtest assertion
	auto pointsSortedTwice = pointsSortedOnce;
	std::sort( pointsSortedTwice.begin(), pointsSortedTwice.end() );
	EXPECT_EQ( pointsSortedOnce, pointsSortedTwice );
	;  // gtest assertion

	std::cout << "original equals sorted once: " << ( points == pointsSortedOnce ) << std::endl
			  << "sorted once equals sorted twice: " << ( pointsSortedOnce == pointsSortedTwice ) << std::endl;
}
