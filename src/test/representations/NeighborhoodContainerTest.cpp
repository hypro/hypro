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

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/Point.h"
#include "../../lib/datastructures/Vertex.h"
#include "../../lib/representations/OrthogonalPolyhedron/NeighborhoodContainer.h"
#include <carl/core/VariablePool.h>

using namespace hypro;
using namespace carl;

class NeighborhoodContainerTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        // p1
        Point<number_t>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(a, FLOAT_T<number_t>(2)) );
        coordinates1.insert( std::make_pair(b, FLOAT_T<number_t>(5)) );
        p1 = Point<number_t>(coordinates1);

        // p2
        Point<number_t>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(a, FLOAT_T<number_t>(7)) );
        coordinates2.insert( std::make_pair(b, FLOAT_T<number_t>(8)) );
        coordinates2.insert( std::make_pair(c, FLOAT_T<number_t>(3)) );
        p2 = Point<number_t>(coordinates2);

        // p3
        Point<number_t>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(a, FLOAT_T<number_t>(2)) );
        coordinates3.insert( std::make_pair(b, FLOAT_T<number_t>(7)) );
        coordinates3.insert( std::make_pair(c, FLOAT_T<number_t>(9)) );
        coordinates3.insert( std::make_pair(d, FLOAT_T<number_t>(-13)) );
        p3 = Point<number_t>(coordinates3);
    }
	
    virtual void TearDown()
    {
    }

    carl::VariablePool& pool = carl::VariablePool::getInstance();
    Variable a = pool.getFreshVariable("a");
    Variable b = pool.getFreshVariable("b");
    Variable c = pool.getFreshVariable("c");
    Variable d = pool.getFreshVariable("d");

    Point<number_t> p1;
    Point<number_t> p2;
    Point<number_t> p3;
};

TEST_F(NeighborhoodContainerTest, Constructor)
{
    NeighborhoodContainer<number_t> nc1;
    NeighborhoodContainer<number_t> copy(nc1);
    SUCCEED();
}

TEST_F(NeighborhoodContainerTest, Clear)
{
    NeighborhoodContainer<number_t> container;
    container.clear();
    EXPECT_TRUE(container.empty());
}

TEST_F(NeighborhoodContainerTest, Neighbours)
{
    NeighborhoodContainer<number_t> container;

    std::vector<Point<number_t> > neighbours = container.getNeighborhoodForDimension(p1, b);
    p1.decrementInFixedDim(a);
    EXPECT_EQ(p1, neighbours[0]);
    container.clear();

    neighbours = container.getNeighborhoodForDimension(p2, a);
    p2.decrementInFixedDim(b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p2) != neighbours.end());
    p2.decrementInFixedDim(c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p2) != neighbours.end());
    p2.incrementInFixedDim(b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p2) != neighbours.end());
    container.clear();
    
    neighbours = container.getNeighborhoodForDimension(p3, a);
    p3.decrementInFixedDim(b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.decrementInFixedDim(c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.incrementInFixedDim(b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.decrementInFixedDim(d);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.incrementInFixedDim(c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.decrementInFixedDim(b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.decrementInFixedDim(c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
}