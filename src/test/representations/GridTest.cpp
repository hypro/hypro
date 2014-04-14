/**
 * @file    GridTest.cpp
 * 
 * @covers  Grid
 * 
 * @author  Benedikt Seidl
 * 
 * @since   2014-04-14
 * @version 2014-04-14
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/Point.h"
#include "../../lib/representations/OrthogonalPolyhedron/Grid.h"

using namespace hypro;

class GridTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        grid = Grid<number_t>();
    }
	
    virtual void TearDown()
    {
    }

    Grid<number_t> grid;
};

TEST_F(GridTest, Constructor)
{
    Grid<number_t> grid1();
    Grid<number_t>::gridMap map;
    Grid<number_t> grid2(map);
}