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

using namespace hypro;

class NeighbourhoodContainerTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        container = NeighbourhoodContainer<number_t>();
    }
	
    virtual void TearDown()
    {
    }

    NeighbourhoodContainer<number_t> container;
};

TEST_F(NeighbourhoodContainerTest, Constructor)
{
    NeighbourhoodContainer<number_t> nc1 = NeighbourhoodContainer<number_t>();
    SUCCEED();
}

TEST_F(NeighbourhoodContainerTest, InsertVertexAndNeighbours)
{
    Point<number_t> p;
    vVecIt<number_t> neighbourBegin;
    vVecIt<number_t> neighbourEnd;
    container.insertVertexAndNeighbours(p, neighbourBegin, neighbourEnd);
}

TEST_F(NeighbourhoodContainerTest, MoveVertices)
{
    Point<number_t> p;
    container.moveVertices(p);
}

TEST_F(NeighbourhoodContainerTest, Clear)
{
    container.clear();
}