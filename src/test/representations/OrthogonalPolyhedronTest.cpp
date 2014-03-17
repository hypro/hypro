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
    OrthogonalPolyhedron<number_t> op1 = OrthogonalPolyhedron<number_t>();
    OrthogonalPolyhedron<number_t> op2 = OrthogonalPolyhedron<number_t>();
    SUCCEED();
}