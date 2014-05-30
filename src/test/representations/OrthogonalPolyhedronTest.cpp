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

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/Point.h"
#include "../../lib/datastructures/Vertex.h"
#include "../../lib/datastructures/VertexContainer.h"
#include "../../lib/representations/Box/Box.h"
#include "../../lib/representations/OrthogonalPolyhedron/OrthogonalPolyhedron.h"
#include "../../lib/representations/OrthogonalPolyhedron/NeighbourhoodContainer.h"

#include <map>
#include <carl/core/VariablePool.h>
#include <carl/core/Variable.h>
#include <carl/interval/Interval.h>

using namespace hypro;
using namespace carl;

class OrthogonalPolyhedronTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        VertexContainer<number_t> container;
        Point<number_t>::rawCoordinateMap coordinates;
        
        coordinates[x] = 3; coordinates[y] = 3;
        container.insert(Point<number_t>(coordinates), true);
        
        coordinates[x] = 3; coordinates[y] = 6;
        container.insert(Point<number_t>(coordinates), false);
        
        coordinates[x] = 5; coordinates[y] = 3;
        container.insert(Point<number_t>(coordinates), false);
        
        coordinates[x] = 5; coordinates[y] = 5;
        container.insert(Point<number_t>(coordinates), true);
        
        coordinates[x] = 7; coordinates[y] = 5;
        container.insert(Point<number_t>(coordinates), false);
        
        coordinates[x] = 7; coordinates[y] = 6;
        container.insert(Point<number_t>(coordinates), false);
        
        p1 = OrthogonalPolyhedron<number_t>(container);
    }
	
    virtual void TearDown()
    {
    }

    VariablePool& pool = VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");

    OrthogonalPolyhedron<number_t> p1;
    OrthogonalPolyhedron<number_t> p2;
};

TEST_F(OrthogonalPolyhedronTest, Constructor)
{
    OrthogonalPolyhedron<number_t> p;
    OrthogonalPolyhedron<number_t> copy(p);
    SUCCEED();
}

TEST_F(OrthogonalPolyhedronTest, Hull)
{
    VertexContainer<number_t> container;
    Point<number_t>::rawCoordinateMap coordinates;

    coordinates[x] = 3; coordinates[y] = 3;
    container.insert(Point<number_t>(coordinates), true);

    coordinates[x] = 3; coordinates[y] = 6;
    container.insert(Point<number_t>(coordinates), false);

    coordinates[x] = 7; coordinates[y] = 3;
    container.insert(Point<number_t>(coordinates), false);

    coordinates[x] = 7; coordinates[y] = 6;
    container.insert(Point<number_t>(coordinates), false);

    OrthogonalPolyhedron<number_t> hull(container);
    OrthogonalPolyhedron<number_t> result;
    
    EXPECT_TRUE(p1.hull(result));
    EXPECT_EQ(hull, result);
}

TEST_F(OrthogonalPolyhedronTest, Contains)
{
    Point<number_t>::rawCoordinateMap coordinates;
    
    coordinates[x] = 4; coordinates[x] = 5;
    Point<number_t> pt1(coordinates);
    
    coordinates[x] = 4; coordinates[x] = 6;
    Point<number_t> pt2(coordinates);
    
    coordinates[x] = 5; coordinates[x] = 5;
    Point<number_t> pt3(coordinates);
    
    coordinates[x] = 1; coordinates[x] = 5;
    Point<number_t> pt4(coordinates);
    
    coordinates[x] = 6; coordinates[x] = 4;
    Point<number_t> pt5(coordinates);
    
    coordinates[x] = 5; coordinates[x] = 6.5;
    Point<number_t> pt6(coordinates);
    
    EXPECT_TRUE(p1.contains(pt1));
    EXPECT_TRUE(p1.contains(pt2));
    EXPECT_TRUE(p1.contains(pt3));
    EXPECT_FALSE(p1.contains(pt4));
    EXPECT_FALSE(p1.contains(pt5));
    EXPECT_FALSE(p1.contains(pt6));
}

TEST_F(OrthogonalPolyhedronTest, Properties)
{
    EXPECT_FALSE(p1.empty());
    EXPECT_TRUE(p2.empty());
    
    std::vector<carl::Variable> variables;
    variables.push_back(x);
    variables.push_back(y);
    EXPECT_EQ(2, p1.dimension());
    EXPECT_EQ(variables, p1.variables());
}

TEST_F(OrthogonalPolyhedronTest, BoundaryBox)
{
    Box<number_t> boundaryBox;
    boundaryBox.insert(x, carl::Interval<number_t>(3, 7));
    boundaryBox.insert(y, carl::Interval<number_t>(3, 6));
    
    EXPECT_EQ(boundaryBox, p1.boundaryBox());
}