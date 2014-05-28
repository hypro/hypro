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
#include "../../lib/representations/OrthogonalPolyhedron/OrthogonalPolyhedron.h"
#include "../../lib/representations/OrthogonalPolyhedron/NeighbourhoodContainer.h"

#include <map>
#include <carl/core/VariablePool.h>

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

TEST_F(OrthogonalPolyhedronTest, Properties)
{
    ASSERT_FALSE(p1.empty());
    ASSERT_TRUE(p2.empty());
    
    std::vector<carl::Variable> variables;
    variables.push_back(x);
    variables.push_back(y);
    ASSERT_EQ(2, p1.dimension());
    ASSERT_EQ(variables, p1.variables());
}