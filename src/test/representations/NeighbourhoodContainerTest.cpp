/**
 * @file    NeighbourhoodContainerTest.cpp
 * 
 * @covers  NeighbourhoodContainer
 * 
 * @author  Benedikt Seidl
 * 
 * @since   2014-03-17
 * @version 2014-03-17
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/Point.h"
#include "../../lib/datastructures/Vertex.h"
#include "../../lib/representations/OrthogonalPolyhedron/NeighbourhoodContainer.h"
#include <carl/core/VariablePool.h>

using namespace hypro;
using namespace carl;

class NeighbourhoodContainerTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        container = NeighbourhoodContainer<number>();
    }
	
    virtual void TearDown()
    {
    }

    carl::VariablePool& pool = carl::VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");

    NeighbourhoodContainer<number> container;
};

TEST_F(NeighbourhoodContainerTest, Constructor)
{
    NeighbourhoodContainer<number> nc1;
    NeighbourhoodContainer<number> copy(nc1);
    SUCCEED();
}

TEST_F(NeighbourhoodContainerTest, InsertVertexAndNeighbours)
{
    Point<number>::coordinateMap coordinates;
    vSet<number> neighbourhood;
    
    
    coordinates[x] = 3; coordinates[y] = 5;
    neighbourhood.insert(Vertex<number>(coordinates, true));
    
    coordinates[x] = 0; coordinates[y] = 0;
    Point<number> p1(coordinates);
    
    EXPECT_FALSE(container.hasNeighbourhood(p1));
    container.insertVertexAndNeighbours(p1, neighbourhood.begin(), neighbourhood.end());
    
    EXPECT_TRUE(container.hasNeighbourhood(p1));
    EXPECT_EQ(neighbourhood, container.getNeighbourhood(p1));
    
    
    coordinates[x] = 5; coordinates[y] = 4;
    neighbourhood.insert(Vertex<number>(coordinates, true));
    
    coordinates[x] = 2; coordinates[y] = 1;
    Point<number> p2(coordinates);
    
    EXPECT_FALSE(container.hasNeighbourhood(p2));
    container.insertVertexAndNeighbours(p2, neighbourhood);
    
    EXPECT_TRUE(container.hasNeighbourhood(p2));
    EXPECT_EQ(neighbourhood, container.getNeighbourhood(p2));
    
    
    EXPECT_FALSE(container.empty());
}

TEST_F(NeighbourhoodContainerTest, MoveVertices)
{
    Point<number>::coordinateMap coordinates;
    coordinates[x] = 3; coordinates[y] = 4;
    Point<number> p(coordinates);
    
    container.moveVertices(p);
}

TEST_F(NeighbourhoodContainerTest, Clear)
{
    container.clear();
    EXPECT_TRUE(container.empty());
}