/**
 * @file    GridTest.cpp
 * 
 * @covers  Grid
 * 
 * @author  Benedikt Seidl
 * 
 * @since   2014-04-14
 * @version 2014-05-27
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/Point.h"
#include "../../lib/datastructures/Vertex.h"
#include "../../lib/datastructures/VertexContainer.h"
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
        Point<number_t>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(x, FLOAT_T<number_t>(1)) );
        coordinates1.insert( std::make_pair(y, FLOAT_T<number_t>(1)) );
        p1 = Point<number_t>(coordinates1);
        map1.insert(std::make_pair(p1, true));
        
        Point<number_t>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(x, FLOAT_T<number_t>(1)) );
        coordinates2.insert( std::make_pair(y, FLOAT_T<number_t>(2)) );
        p2 = Point<number_t>(coordinates2);
        map1.insert(std::make_pair(p2, false));
        
        // grid2
        Point<number_t>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates3.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        p3 = Point<number_t>(coordinates3);
        map2.insert(std::make_pair(p3, true));
        
        Point<number_t>::coordinateMap coordinates4;
        coordinates4.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates4.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        p4 = Point<number_t>(coordinates4);
        map2.insert(std::make_pair(p4, true));
        
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
    Grid<number_t> grid1;
    Grid<number_t>::gridMap map;
    map.insert(std::make_pair(p1, true));
    map.insert(std::make_pair(p2, false));
    Grid<number_t> grid2(map);
}

TEST_F(GridTest, Insert)
{
    Point<number_t> p = Point<number_t>(p4);
    p[x] += FLOAT_T<number_t>(0.5);
    
    grid1.insert(p4, true);
    EXPECT_TRUE(grid1.colourAt(p4));
    EXPECT_TRUE(grid1.colourAt(p));
    
    grid1.insert(p, false);
    EXPECT_FALSE(grid1.colourAt(p4));
    EXPECT_FALSE(grid1.colourAt(p));
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

TEST_F(GridTest, CalculateInduced)
{
    EXPECT_EQ(p1, grid1.calculateInduced(p1));
    Point<number_t> p = Point<number_t>(p1);
    p[x] += FLOAT_T<number_t>(0.5);
    EXPECT_EQ(p1, grid1.calculateInduced(p));
}

TEST_F(GridTest, InsertVerticesInMap)
{
    VertexContainer<number_t> vertices;
    Vertex<number_t>::rawCoordinateMap coordinates;
    Vertex<number_t> v1, v2, v3;
    
    coordinates[x] = 1; coordinates[y] = 5;
    v1 = Vertex<number_t>(coordinates, false);
    coordinates[x] = 4; coordinates[y] = 7;
    v2 = Vertex<number_t>(coordinates, true);
    coordinates[x] = 6; coordinates[y] = 8;
    v3 = Vertex<number_t>(coordinates, true);
    
    vertices.insert(v1);
    vertices.insert(v2);
    vertices.insert(v3);
    
    grid1.insertVerticesInMap(vertices);
    
    EXPECT_FALSE(grid1.colourAt(v1));
    EXPECT_TRUE(grid1.colourAt(v2));
    EXPECT_TRUE(grid1.colourAt(v3));
}

TEST_F(GridTest, InduceGrid)
{
    vSet<number_t> vertices;
    Vertex<number_t>::rawCoordinateMap coordinates;
    
    coordinates[x] = 1; coordinates[y] = 5;
    vertices.insert(Vertex<number_t>(coordinates, false));
    
    coordinates[x] = 4; coordinates[y] = 7;
    vertices.insert(Vertex<number_t>(coordinates, true));
    
    coordinates[x] = 6; coordinates[y] = 8;
    vertices.insert(Vertex<number_t>(coordinates, true));
    
    EXPECT_FALSE(grid1.induced());
    
    grid1.induceGrid(vertices);
    
    EXPECT_TRUE(grid1.induced());
    
    p4[x] = 10; p4[y] = 9;
    
    Point<number_t> _p1 = Point<number_t>(p1); // (1;1)
    Point<number_t> _p2 = Point<number_t>(p2); // (1;2)
    Point<number_t> _p3 = Point<number_t>(p3); // (2;5)
    Point<number_t> _p4 = Point<number_t>(p4); // (10;9)
    
    _p1[x] = 1; _p1[y] = 0;
    _p2[x] = 1; _p2[y] = 0;
    _p3[x] = 1; _p3[y] = 5;
    _p4[x] = 6; _p4[y] = 8;
    
    EXPECT_EQ(_p1, grid1.calculateInduced(p1));
    EXPECT_EQ(_p2, grid1.calculateInduced(p2));
    EXPECT_EQ(_p3, grid1.calculateInduced(p3));
    EXPECT_EQ(_p4, grid1.calculateInduced(p4));
}