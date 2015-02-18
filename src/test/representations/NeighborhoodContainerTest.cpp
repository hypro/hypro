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
		pool.clear();
		a = pool.newCarlVariable();
		b = pool.newCarlVariable();
		c = pool.newCarlVariable();
		d = pool.newCarlVariable();
        // p1
        typename Point<int>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(a, 2) );
        coordinates1.insert( std::make_pair(b, 5) );
        p1 = Point<int>(coordinates1);

        // p2
        typename Point<int>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(a, 7) );
        coordinates2.insert( std::make_pair(b, 8) );
        coordinates2.insert( std::make_pair(c, 3) );
        p2 = Point<int>(coordinates2);

        // p3
        typename Point<int>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(a, 2) );
        coordinates3.insert( std::make_pair(b, 7) );
        coordinates3.insert( std::make_pair(c, 9) );
        coordinates3.insert( std::make_pair(d, -13) );
        p3 = Point<int>(coordinates3);
    }
	
    virtual void TearDown()
    {
    }

    hypro::VariablePool& pool = hypro::VariablePool::getInstance();
    Variable a;
    Variable b;
    Variable c;
    Variable d;

    Point<int> p1;
    Point<int> p2;
    Point<int> p3;
};

TEST_F(NeighborhoodContainerTest, Constructor)
{
    NeighborhoodContainer nc1;
    NeighborhoodContainer copy(nc1);
    SUCCEED();
}

TEST_F(NeighborhoodContainerTest, Clear)
{
    NeighborhoodContainer container;
    container.clear();
    EXPECT_TRUE(container.empty());
}

TEST_F(NeighborhoodContainerTest, Neighbours)
{
    NeighborhoodContainer container;

    std::vector<Point<int> > neighbours = container.getNeighborhoodForDimension(this->p1, this->b);
    this->p1.decrementInFixedDim(this->a);
    EXPECT_EQ(this->p1, neighbours[0]);
    container.clear();

    neighbours = container.getNeighborhoodForDimension(this->p2, this->a);
    this->p2.decrementInFixedDim(this->b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p2) != neighbours.end());
    this->p2.decrementInFixedDim(this->c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p2) != neighbours.end());
    this->p2.incrementInFixedDim(this->b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p2) != neighbours.end());
    container.clear();
    
    neighbours = container.getNeighborhoodForDimension(this->p3, this->a);
    this->p3.decrementInFixedDim(this->b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.decrementInFixedDim(this->c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.incrementInFixedDim(this->b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.decrementInFixedDim(this->d);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.incrementInFixedDim(this->c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.decrementInFixedDim(this->b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.decrementInFixedDim(this->c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
}