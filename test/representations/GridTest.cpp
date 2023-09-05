/**
 * @file    GridTest.cpp
 *
 * @covers  Grid
 *
 * @author  Benedikt Seidl
 *
 * @since   2014-04-14
 * @version 2014-05-27
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/datastructures/Point.h>
#include <hypro/datastructures/Vertex.h>
#include <hypro/representations/OrthogonalPolyhedron/Grid.h>

using namespace hypro;
using namespace carl;

template <typename Number>
class GridTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		// vertices

		vertices.insert( Vertex<Number>( Point<Number>( { 2, 2 } ), true ) );
		vertices.insert( Vertex<Number>( Point<Number>( { 6, 2 } ), false ) );
		vertices.insert( Vertex<Number>( Point<Number>( { 6, 6 } ), false ) );
		vertices.insert( Vertex<Number>( Point<Number>( { 4, 6 } ), false ) );
		vertices.insert( Vertex<Number>( Point<Number>( { 4, 4 } ), true ) );
		vertices.insert( Vertex<Number>( Point<Number>( { 2, 4 } ), false ) );

		grid1.induceGrid( vertices );
	}

	virtual void TearDown() { grid1.clear(); }

	vSet<Number> vertices;
	hypro::Grid<Number> grid1;
};

TYPED_TEST( GridTest, Constructor ) {
	hypro::Grid<TypeParam> grid;
	EXPECT_TRUE( grid.empty() );
	hypro::Grid<TypeParam> copy( grid );
	EXPECT_TRUE( copy.empty() );
}

TYPED_TEST( GridTest, Properties ) {
	Point<TypeParam> p1( { 3, 3 } );

	EXPECT_FALSE( this->grid1.empty() );
	EXPECT_EQ( this->grid1.size(), std::size_t( 6 ) );
	EXPECT_TRUE( this->grid1.find( p1 ) != this->grid1.end() );

	this->grid1.clear();
	EXPECT_TRUE( this->grid1.empty() );
	EXPECT_EQ( this->grid1.size(), std::size_t( 0 ) );
	EXPECT_FALSE( this->grid1.find( p1 ) != this->grid1.end() );
}

TYPED_TEST( GridTest, Insert ) {
	Point<TypeParam> p;

	p = Point<TypeParam>( { 2, 7 } );
	this->grid1.insert( p, true );
	EXPECT_EQ( true, this->grid1.colorAt( p ) );

	p = Point<TypeParam>( { 0, 0 } );
	this->grid1.insert( p, false );
	EXPECT_EQ( false, this->grid1.colorAt( p ) );

	p = Point<TypeParam>( { 1, 2 } );
	this->grid1.insert( p, true );
	EXPECT_EQ( true, this->grid1.colorAt( p ) );

	p = Point<TypeParam>( { 10, 7 } );
	this->grid1.insert( p, false );
	EXPECT_EQ( false, this->grid1.colorAt( p ) );

	p = Point<TypeParam>( { 10, 10 } );
	this->grid1.insert( p, false );
	EXPECT_EQ( false, this->grid1.colorAt( p ) );
}

TYPED_TEST( GridTest, InsertInduced ) {
	Point<std::size_t> p;

	p = Point<std::size_t>( { 1, 2 } );
	this->grid1.insertInduced( p, true );
	EXPECT_EQ( true, this->grid1.colorAtInduced( p ) );

	p = Point<std::size_t>( { 0, 0 } );
	this->grid1.insertInduced( p, false );
	EXPECT_EQ( false, this->grid1.colorAtInduced( p ) );

	p = Point<std::size_t>( { 1, 0 } );
	this->grid1.insertInduced( p, true );
	EXPECT_EQ( true, this->grid1.colorAtInduced( p ) );

	p = Point<std::size_t>( { 3, 2 } );
	this->grid1.insertInduced( p, false );
	EXPECT_EQ( false, this->grid1.colorAtInduced( p ) );

	p = Point<std::size_t>( { 3, 3 } );
	this->grid1.insertInduced( p, false );
	EXPECT_EQ( false, this->grid1.colorAtInduced( p ) );
}

TYPED_TEST( GridTest, ColorAt ) {
	Point<TypeParam> p;

	p = Point<TypeParam>( { 1, 5 } );
	EXPECT_EQ( false, this->grid1.colorAt( p ) );

	p = Point<TypeParam>( { 4, 5 } );
	EXPECT_EQ( true, this->grid1.colorAt( p ) );

	p = Point<TypeParam>( { 6, 3 } );
	EXPECT_EQ( false, this->grid1.colorAt( p ) );

	p = Point<TypeParam>( { 10, 10 } );
	EXPECT_EQ( false, this->grid1.colorAt( p ) );
}

TYPED_TEST( GridTest, ColorAtInduced ) {
	Point<std::size_t> p;

	p = Point<std::size_t>( { 1, 1 } );
	EXPECT_EQ( true, this->grid1.colorAtInduced( p ) );

	p = Point<std::size_t>( { 2, 2 } );
	EXPECT_EQ( true, this->grid1.colorAtInduced( p ) );

	p = Point<std::size_t>( { 3, 3 } );
	EXPECT_EQ( false, this->grid1.colorAtInduced( p ) );

	p = Point<std::size_t>( { 5, 5 } );
	EXPECT_EQ( false, this->grid1.colorAtInduced( p ) );
}

TYPED_TEST( GridTest, CalculateInduced ) {
	Point<std::size_t>::coordinateMap i;
	typename Point<TypeParam>::coordinateMap c;

	Point<TypeParam> p1( { 3, 2 } );
	Point<std::size_t> ip1( { 1, 1 } );

	Point<TypeParam> p2( { 2, 5 } );
	Point<std::size_t> ip2( { 1, 2 } );

	Point<TypeParam> p3( { 5, 5 } );
	Point<std::size_t> ip3( { 2, 2 } );

	EXPECT_EQ( ip1, this->grid1.calculateInduced( p1 ).first );
	EXPECT_EQ( ip2, this->grid1.calculateInduced( p2 ).first );
	EXPECT_EQ( ip3, this->grid1.calculateInduced( p3 ).first );
}

TYPED_TEST( GridTest, CalculateOriginal ) {
	Point<std::size_t>::coordinateMap i;
	typename Point<TypeParam>::coordinateMap c;

	Point<std::size_t> ip1( { 1, 1 } );
	Point<TypeParam> op1( { 2, 2 } );

	Point<std::size_t> ip2( { 1, 2 } );
	Point<TypeParam> op2( { 2, 4 } );

	Point<std::size_t> ip3( { 2, 2 } );
	Point<TypeParam> op3( { 4, 4 } );

	EXPECT_EQ( op1, this->grid1.calculateOriginal( ip1 ) );
	EXPECT_EQ( op2, this->grid1.calculateOriginal( ip2 ) );
	EXPECT_EQ( op3, this->grid1.calculateOriginal( ip3 ) );
}

TYPED_TEST( GridTest, Translate ) {
	vSet<std::size_t> induced;

	induced.insert( Vertex<std::size_t>( Point<std::size_t>( { 1, 1 } ), true ) );
	induced.insert( Vertex<std::size_t>( Point<std::size_t>( { 2, 2 } ), true ) );
	induced.insert( Vertex<std::size_t>( Point<std::size_t>( { 3, 3 } ), false ) );
	induced.insert( Vertex<std::size_t>( Point<std::size_t>( { 1, 2 } ), false ) );
	induced.insert( Vertex<std::size_t>( Point<std::size_t>( { 3, 1 } ), false ) );
	induced.insert( Vertex<std::size_t>( Point<std::size_t>( { 2, 3 } ), false ) );

	EXPECT_EQ( induced, this->grid1.translateToInduced( this->vertices ) );
	EXPECT_EQ( this->vertices, this->grid1.translateToOriginal( induced ) );
}
