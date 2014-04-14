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
        VariablePool& pool = VariablePool::getInstance();
        Variable x = pool.getFreshVariable(carl::VT_INT);
        Variable y = pool.getFreshVariable(carl::VT_INT);
        
        Point<number_t>::vector_t coordinates1;
        coordinates1.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates1.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        pt1 = Point<number_t>(coordinates1);
        
        Point<number_t>::vector_t coordinates2;
        coordinates2.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates2.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        pt2 = Point<number_t>(coordinates2);
        
        Point<number_t>::vector_t coordinates3;
        coordinates3.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates3.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        Vertex<number_t> v1(coordinates1, false);
        
        Point<number_t>::vector_t coordinates4;
        coordinates4.insert( std::make_pair(x, FLOAT_T<number_t>(-3)) );
        coordinates4.insert( std::make_pair(y, FLOAT_T<number_t>(4)) );
        Vertex<number_t> v2(coordinates2, true);
        
        vVec<number_t> vertexList;
        vertexList.push_back(v1);
        vertexList.push_back(v2);
                
        p1 = OrthogonalPolyhedron<number_t>();
        p2 = OrthogonalPolyhedron<number_t>(vertexList, 2);
    }
	
    virtual void TearDown()
    {
    }

    OrthogonalPolyhedron<number_t> p1;
    OrthogonalPolyhedron<number_t> p2;
    
    Point<number_t> pt1;
    Point<number_t> pt2;
};

TEST_F(OrthogonalPolyhedronTest, Constructor)
{
    Vertex<number_t>* vertices;
    unsigned nrVertices = 2;
    unsigned dim = 3;
    vVec<number_t> vertexList;
    vVec<number_t> extremeVertexList;
    NeighbourhoodContainer<number_t> neighbourhoods;

    OrthogonalPolyhedron<number_t> op1 = OrthogonalPolyhedron<number_t>();
    OrthogonalPolyhedron<number_t> op2 = OrthogonalPolyhedron<number_t>(vertices, nrVertices, dim);
    OrthogonalPolyhedron<number_t> op3 = OrthogonalPolyhedron<number_t>(vertexList, dim);
    OrthogonalPolyhedron<number_t> op4 = OrthogonalPolyhedron<number_t>(vertexList, dim, extremeVertexList);
    OrthogonalPolyhedron<number_t> op5 = OrthogonalPolyhedron<number_t>(vertexList, dim, neighbourhoods);
    SUCCEED();
}

TEST_F(OrthogonalPolyhedronTest, IsEmpty)
{
    ASSERT_TRUE(p1.isEmpty());
    ASSERT_FALSE(p2.isEmpty());
}

TEST_F(OrthogonalPolyhedronTest, IsUniversal)
{
    p1.isUniversal();
    p2.isUniversal();
}

TEST_F(OrthogonalPolyhedronTest, dimension)
{
    ASSERT_EQ(2, p1.dimension());
    ASSERT_EQ(2, p2.dimension());
}

/*TEST_F(OrthogonalPolyhedronTest, IsMember)
{
    p1.isMember(pt1, true);
    p2.isMember(pt2, false);
}*/