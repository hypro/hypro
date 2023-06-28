/**
 * @file    NeighborhoodContainerTest.cpp
 *
 * @covers  NeighborhoodContainer
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
#include <hypro/representations/OrthogonalPolyhedron/NeighborhoodContainer.h>

using namespace hypro;
using namespace carl;

class NeighborhoodContainerTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		pool.clear();
		a = pool.carlVarByIndex( 0 );
		b = pool.carlVarByIndex( 1 );
		c = pool.carlVarByIndex( 2 );
		d = pool.carlVarByIndex( 3 );
		// p1
		p1 = Point<int>( { 2, 5 } );

		// p2
		p2 = Point<int>( { 7, 8, 3 } );

		// p3
		p3 = Point<int>( { 2, 7, 9, -13 } );
	}

	virtual void TearDown() {}

	hypro::VariablePool& pool = hypro::VariablePool::getInstance();
	carl::Variable a;
	carl::Variable b;
	carl::Variable c;
	carl::Variable d;

	hypro::Point<int> p1;
	hypro::Point<int> p2;
	hypro::Point<int> p3;
};

TEST_F( NeighborhoodContainerTest, Constructor ) {
	NeighborhoodContainer nc1;
	NeighborhoodContainer copy( nc1 );
	SUCCEED();
}

TEST_F( NeighborhoodContainerTest, Clear ) {
	NeighborhoodContainer container;
	container.clear();
	EXPECT_TRUE( container.empty() );
}

TEST_F( NeighborhoodContainerTest, Neighbours ) {
	NeighborhoodContainer container;

	std::vector<Point<int> > neighbours = container.getNeighborhoodForDimension( this->p1, this->b );
	this->p1.decrementInFixedDim( this->a );
	EXPECT_EQ( this->p1, neighbours[0] );
	container.clear();

	neighbours = container.getNeighborhoodForDimension( this->p2, this->a );
	this->p2.decrementInFixedDim( this->b );
	EXPECT_TRUE( std::find( neighbours.begin(), neighbours.end(), this->p2 ) != neighbours.end() );
	this->p2.decrementInFixedDim( this->c );
	EXPECT_TRUE( std::find( neighbours.begin(), neighbours.end(), this->p2 ) != neighbours.end() );
	this->p2.incrementInFixedDim( this->b );
	EXPECT_TRUE( std::find( neighbours.begin(), neighbours.end(), this->p2 ) != neighbours.end() );
	container.clear();

	neighbours = container.getNeighborhoodForDimension( this->p3, this->a );
	this->p3.decrementInFixedDim( this->b );
	EXPECT_TRUE( std::find( neighbours.begin(), neighbours.end(), this->p3 ) != neighbours.end() );
	this->p3.decrementInFixedDim( this->c );
	EXPECT_TRUE( std::find( neighbours.begin(), neighbours.end(), this->p3 ) != neighbours.end() );
	this->p3.incrementInFixedDim( this->b );
	EXPECT_TRUE( std::find( neighbours.begin(), neighbours.end(), this->p3 ) != neighbours.end() );
	this->p3.decrementInFixedDim( this->d );
	EXPECT_TRUE( std::find( neighbours.begin(), neighbours.end(), this->p3 ) != neighbours.end() );
	this->p3.incrementInFixedDim( this->c );
	EXPECT_TRUE( std::find( neighbours.begin(), neighbours.end(), this->p3 ) != neighbours.end() );
	this->p3.decrementInFixedDim( this->b );
	EXPECT_TRUE( std::find( neighbours.begin(), neighbours.end(), this->p3 ) != neighbours.end() );
	this->p3.decrementInFixedDim( this->c );
	EXPECT_TRUE( std::find( neighbours.begin(), neighbours.end(), this->p3 ) != neighbours.end() );
}
