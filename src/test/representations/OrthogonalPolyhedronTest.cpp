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
#include "../../lib/representations/OrthogonalPolyhedron/OrthogonalPolyhedron.h"
#include "../../lib/representations/OrthogonalPolyhedron/NeighbourhoodContainer.h"

using namespace hypro;

class OrthogonalPolyhedronTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        
    }
	
    virtual void TearDown()
    {
    }

    OrthogonalPolyhedron<number_t> polyhedron;
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