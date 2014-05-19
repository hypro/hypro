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
#include <carl/core/VariablePool.h>

using namespace hypro;
using namespace carl;

class GridTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        Grid<number_t>::gridMap map1;
        Grid<number_t>::gridMap map2;
        
        // grid1
        Point<number_t>::vector_t coordinates1;
        coordinates1.insert( std::make_pair(x, FLOAT_T<number_t>(1)) );
        coordinates1.insert( std::make_pair(y, FLOAT_T<number_t>(1)) );
        p1 = Point<number_t>(coordinates1);
        map1.insert(std::pair<Point<number_t>, bool>(p1, true));
        
        Point<number_t>::vector_t coordinates2;
        coordinates2.insert( std::make_pair(x, FLOAT_T<number_t>(1)) );
        coordinates2.insert( std::make_pair(y, FLOAT_T<number_t>(2)) );
        p2 = Point<number_t>(coordinates2);
        map1.insert(std::pair<Point<number_t>, bool>(p2, false));
        
        // grid2
        Point<number_t>::vector_t coordinates3;
        coordinates3.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates3.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        p3 = Point<number_t>(coordinates3);
        map2.insert(std::pair<Point<number_t>, bool>(p3, true));
        
        Point<number_t>::vector_t coordinates4;
        coordinates4.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates4.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        p4 = Point<number_t>(coordinates4);
        map2.insert(std::pair<Point<number_t>, bool>(p4, true));
        
        grid1 = Grid<number_t>(map1);
        grid2 = Grid<number_t>(map2);
    }
	
    virtual void TearDown()
    {
    }
	
    VariablePool& pool = VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");
    
    Point<number_t> p1, p2, p3, p4;

    Grid<number_t> grid1;
    Grid<number_t> grid2;
};

TEST_F(GridTest, Constructor)
{
    Grid<number_t> grid1();
    Grid<number_t>::gridMap map;
    map.insert(std::pair<Point<number_t>, bool>(p1, true));
    map.insert(std::pair<Point<number_t>, bool>(p2, false));
    Grid<number_t> grid2(map);
}

TEST_F(GridTest, ColourAt)
{
    EXPECT_TRUE(grid1.colourAt(p1));
    EXPECT_FALSE(grid1.colourAt(p2));
    p1[x] = FLOAT_T<number_t>(1.5);
    EXPECT_TRUE(grid1.colourAt(p1));
    p1[x] = FLOAT_T<number_t>(2);
    EXPECT_FALSE(grid1.colourAt(p1));
}

TEST_F(GridTest, Contains)
{
    EXPECT_TRUE(grid1.contains(p1));
    EXPECT_FALSE(grid1.contains(p2));
    p1[x] = FLOAT_T<number_t>(1.5);
    EXPECT_TRUE(grid1.contains(p1));
    p1[x] = FLOAT_T<number_t>(2);
    EXPECT_FALSE(grid1.contains(p1));
}

TEST_F(GridTest, CalculateInduced)
{
    //EXPECT_EQ(p1, grid1.calculateInduced(p1));
    Point<number_t> p = Point<number_t>(p1);
    p[x] = FLOAT_T<number_t>(1.5);
    //EXPECT_EQ(p1, grid1.calculateInduced(p));
}