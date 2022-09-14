/**
 * @file    OrthogonalPolyhedronTest.cpp
 *
 * @covers  OrthogonalPolyhedron
 *
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-03-17
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/datastructures/Point.h>
#include <hypro/datastructures/Vertex.h>
#include <hypro/datastructures/VertexContainer.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/representations/OrthogonalPolyhedron/NeighborhoodContainer.h>
#include <hypro/types.h>
#include <hypro/util/VariablePool.h>
#include <map>

using namespace hypro;
using namespace carl;

template <typename Number>
class OrthogonalPolyhedronTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		container1.insert( Point<Number>( { 3, 3 } ), true );
		container1.insert( Point<Number>( { 3, 6 } ), false );
		container1.insert( Point<Number>( { 5, 3 } ), false );
		container1.insert( Point<Number>( { 5, 5 } ), true );
		container1.insert( Point<Number>( { 7, 5 } ), false );
		container1.insert( Point<Number>( { 7, 6 } ), false );

		p1 = OrthogonalPolyhedron<Number>( container1 );

		container2.insert( Point<Number>( { 1, 2 } ), true );
		container2.insert( Point<Number>( { 1, 4 } ), false );
		container2.insert( Point<Number>( { 2, 4 } ), true );
		container2.insert( Point<Number>( { 2, 5 } ), false );
		container2.insert( Point<Number>( { 4, 5 } ), false );
		container2.insert( Point<Number>( { 4, 2 } ), false );

		p2 = OrthogonalPolyhedron<Number>( container2 );
	}

	virtual void TearDown() {}

	hypro::VariablePool& pool = hypro::VariablePool::getInstance();
	carl::Variable x = pool.carlVarByIndex( 0 );
	carl::Variable y = pool.carlVarByIndex( 1 );

	VertexContainer<Number> container1;
	VertexContainer<Number> container2;

	OrthogonalPolyhedron<Number> p1;
	OrthogonalPolyhedron<Number> p2;
};

TYPED_TEST( OrthogonalPolyhedronTest, Constructor ) {
	// empty constructor
	OrthogonalPolyhedron<TypeParam> p1;

	// constructor from vertex
	Vertex<TypeParam> v1( Point<TypeParam>( { 1, 2 } ), false );
	OrthogonalPolyhedron<TypeParam> p2( v1 );

	// constructor from vertexContainer
	OrthogonalPolyhedron<TypeParam> p3( this->container1 );

	// constructor from set of vertices
	OrthogonalPolyhedron<TypeParam> p4( this->container1.vertices() );

	// copy constructor
	OrthogonalPolyhedron<TypeParam> copy( p4 );
	SUCCEED();
}

TYPED_TEST( OrthogonalPolyhedronTest, Properties ) {
	EXPECT_FALSE( this->p1.empty() );
	OrthogonalPolyhedron<TypeParam> empty;
	EXPECT_TRUE( empty.empty() );

	EXPECT_EQ( (unsigned)2, this->p1.dimension() );

	std::vector<carl::Variable> variables;
	variables.push_back( this->x );
	variables.push_back( this->y );
	EXPECT_EQ( variables, this->p1.variables() );
}

TYPED_TEST( OrthogonalPolyhedronTest, BoundaryBox ) {
	hypro::Box<TypeParam> boundaryBox;
	boundaryBox.insert( carl::Interval<TypeParam>( 3, 7 ) );
	boundaryBox.insert( carl::Interval<TypeParam>( 3, 6 ) );

	EXPECT_EQ( boundaryBox, this->p1.boundaryBox() );
}

/*

TYPED_TEST(OrthogonalPolyhedronTest, LinearTransformation)
{
	matrix_t<TypeParam> A = createMatrix(std::vector<std::vector<TypeParam> >({
			std::vector<TypeParam>({5, -2}),
			std::vector<TypeParam>({9, 3})
	}));

	vector_t<TypeParam> v = createVector(std::vector<TypeParam>({7, 2}));


	VertexContainer<TypeParam> container1;
	typename Point<TypeParam>::coordinateMap coordinates;

	coordinates[this->x] = 38; coordinates[this->y] = 16;
	container1.insert(Point<TypeParam>(coordinates), true);

	coordinates[this->x] = 65; coordinates[this->y] = 31;
	container1.insert(Point<TypeParam>(coordinates), false);

	coordinates[this->x] = 44; coordinates[this->y] = 12;
	container1.insert(Point<TypeParam>(coordinates), false);

	coordinates[this->x] = 62; coordinates[this->y] = 22;
	container1.insert(Point<TypeParam>(coordinates), true);

	coordinates[this->x] = 68; coordinates[this->y] = 18;
	container1.insert(Point<TypeParam>(coordinates), false);

	coordinates[this->x] = 77; coordinates[this->y] = 23;
	container1.insert(Point<TypeParam>(coordinates), false);

	VertexContainer<TypeParam> container2;

	coordinates[this->x] = 32; coordinates[this->y] = 20;
	container2.insert(Point<TypeParam>(coordinates), true);

	coordinates[this->x] = 41; coordinates[this->y] = 25;
	container2.insert(Point<TypeParam>(coordinates), false);

	coordinates[this->x] = 44; coordinates[this->y] = 23;
	container2.insert(Point<TypeParam>(coordinates), true);

	coordinates[this->x] = 53; coordinates[this->y] = 28;
	container2.insert(Point<TypeParam>(coordinates), false);

	coordinates[this->x] = 59; coordinates[this->y] = 24;
	container2.insert(Point<TypeParam>(coordinates), false);

	coordinates[this->x] = 32; coordinates[this->y] = 9;
	container2.insert(Point<TypeParam>(coordinates), false);

	coordinates[this->x] = 26; coordinates[this->y] = 13;
	container2.insert(Point<TypeParam>(coordinates), true);

	coordinates[this->x] = 35; coordinates[this->y] = 18;
	container2.insert(Point<TypeParam>(coordinates), true);


	OrthogonalPolyhedron<TypeParam> expected1(container1);
	OrthogonalPolyhedron<TypeParam> expected2(container2);

	OrthogonalPolyhedron<TypeParam> result1, result2;

	EXPECT_TRUE(this->p1.linearTransformation(result1, A, v));
	EXPECT_TRUE(this->p2.linearTransformation(result2, A, v));

	EXPECT_EQ(expected1, result1);
	EXPECT_EQ(expected2, result2);
}

*/

TYPED_TEST( OrthogonalPolyhedronTest, Intersect ) {
	OrthogonalPolyhedron<TypeParam> result;

	VertexContainer<TypeParam> container;

	container.insert( Point<TypeParam>( { 3, 3 } ), true );
	container.insert( Point<TypeParam>( { 4, 3 } ), false );
	container.insert( Point<TypeParam>( { 3, 5 } ), false );
	container.insert( Point<TypeParam>( { 4, 5 } ), false );
	OrthogonalPolyhedron<TypeParam> p3( container );

	OrthogonalPolyhedron<TypeParam> expected( container );

	result = this->p2.intersect( this->p1 );

	EXPECT_EQ( expected, result );
}

TYPED_TEST( OrthogonalPolyhedronTest, Hull ) {
	VertexContainer<TypeParam> container;

	container.insert( Point<TypeParam>( { 3, 3 } ), true );
	container.insert( Point<TypeParam>( { 3, 6 } ), false );
	container.insert( Point<TypeParam>( { 7, 3 } ), false );
	container.insert( Point<TypeParam>( { 7, 6 } ), false );

	OrthogonalPolyhedron<TypeParam> hull( container );
	OrthogonalPolyhedron<TypeParam> result;

	result = this->p1.hull();
	EXPECT_EQ( hull, result );
}

/*
TYPED_TEST(OrthogonalPolyhedronTest, Contains)
{
	typename Point<TypeParam>::coordinateMap coordinates;

	coordinates[this->x] = 4; coordinates[this->y] = 5;
	Point<TypeParam> pt1(coordinates); // true

	coordinates[this->x] = 4; coordinates[this->y] = 6;
	Point<TypeParam> pt2(coordinates); // false

	coordinates[this->x] = 5; coordinates[this->y] = 5;
	Point<TypeParam> pt3(coordinates); // true

	coordinates[this->x] = 1; coordinates[this->y] = 5;
	Point<TypeParam> pt4(coordinates); // false

	coordinates[this->x] = 6; coordinates[this->y] = 4;
	Point<TypeParam> pt5(coordinates); // false

	coordinates[this->x] = 5; coordinates[this->y] = TypeParam(6.5);
	Point<TypeParam> pt6(coordinates); // false

	coordinates[this->x] = 4; coordinates[this->y] = 3;
	Point<TypeParam> pt7(coordinates); // true

	coordinates[this->x] = 3; coordinates[this->y] = 5;
	Point<TypeParam> pt8(coordinates); // true

	coordinates[this->x] = 5; coordinates[this->y] = 4;
	Point<TypeParam> pt9(coordinates); // false

	coordinates[this->x] = 6; coordinates[this->y] = 5;
	Point<TypeParam> pt10(coordinates); // true

	coordinates[this->x] = 7; coordinates[this->y] = 6;
	Point<TypeParam> pt11(coordinates); // false

	coordinates[this->x] = 0; coordinates[this->y] = 0;
	Point<TypeParam> pt12(coordinates); // false

	coordinates[this->x] = 1; coordinates[this->y] = 1;
	Point<TypeParam> pt13(coordinates); // false

	coordinates[this->x] = 100; coordinates[this->y] = 100;
	Point<TypeParam> pt14(coordinates); // false

	EXPECT_TRUE(this->p1.contains(pt1));
	EXPECT_FALSE(this->p1.contains(pt2));
	EXPECT_TRUE(this->p1.contains(pt3));
	EXPECT_FALSE(this->p1.contains(pt4));
	EXPECT_FALSE(this->p1.contains(pt5));
	EXPECT_FALSE(this->p1.contains(pt6));
	EXPECT_TRUE(this->p1.contains(pt7));
	EXPECT_TRUE(this->p1.contains(pt8));
	EXPECT_FALSE(this->p1.contains(pt9));
	EXPECT_TRUE(this->p1.contains(pt10));
	EXPECT_FALSE(this->p1.contains(pt11));
	EXPECT_FALSE(this->p1.contains(pt12));
	EXPECT_FALSE(this->p1.contains(pt13));
	EXPECT_FALSE(this->p1.contains(pt14));

	// also check all vertices
	for (auto vertexIt : this->container1.vertices()) {
		EXPECT_EQ(vertexIt.color(), this->p1.contains(vertexIt.point()));
	}
}
*/

TYPED_TEST( OrthogonalPolyhedronTest, Unite ) {
	OrthogonalPolyhedron<TypeParam> result;

	VertexContainer<TypeParam> container;

	container.insert( Point<TypeParam>( { 1, 3 } ), true );
	container.insert( Point<TypeParam>( { 1, 4 } ), false );
	container.insert( Point<TypeParam>( { 2, 2 } ), true );
	container.insert( Point<TypeParam>( { 2, 3 } ), true );
	container.insert( Point<TypeParam>( { 2, 4 } ), true );
	container.insert( Point<TypeParam>( { 2, 5 } ), false );
	container.insert( Point<TypeParam>( { 3, 5 } ), true );
	container.insert( Point<TypeParam>( { 3, 6 } ), false );
	container.insert( Point<TypeParam>( { 4, 2 } ), false );
	container.insert( Point<TypeParam>( { 4, 3 } ), true );
	container.insert( Point<TypeParam>( { 5, 3 } ), false );
	container.insert( Point<TypeParam>( { 5, 5 } ), true );
	container.insert( Point<TypeParam>( { 7, 5 } ), false );
	container.insert( Point<TypeParam>( { 7, 6 } ), false );

	OrthogonalPolyhedron<TypeParam> expected( container );

	result = this->p1.unite( this->p2 );

	EXPECT_EQ( expected, result );
}

TYPED_TEST( OrthogonalPolyhedronTest, SettingsConversion ) {
	hypro::OrthogonalPolyhedronT<TypeParam, hypro::Converter<TypeParam>, hypro::BoxLinearOptimizationOff> newOP(
		  this->p1 );
	EXPECT_EQ( newOP, this->p1 );
}