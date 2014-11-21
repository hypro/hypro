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
        
        std::vector<carl::Variable> variables;
        variables.push_back(x);
        variables.push_back(y);

        grid1.reserveInducedGrid(variables);
        grid2.reserveInducedGrid(variables);
        
        // grid1
        Point<number_t>::coordinateMap coordinates;
        coordinates[x] = FLOAT_T<number_t>(1);
        coordinates[y] = FLOAT_T<number_t>(1);
        p1 = Point<number_t>(coordinates);
        grid1.insert(p1, true);
        
        coordinates[x] = FLOAT_T<number_t>(1);
        coordinates[y] = FLOAT_T<number_t>(2);
        p2 = Point<number_t>(coordinates);
        grid1.insert(p2, false);
        
        // grid2
        coordinates[x] = FLOAT_T<number_t>(2);
        coordinates[y] = FLOAT_T<number_t>(5);
        p3 = Point<number_t>(coordinates);
        grid1.insert(p3, true);
        
        coordinates[x] = FLOAT_T<number_t>(2);
        coordinates[y] = FLOAT_T<number_t>(5);
        p4 = Point<number_t>(coordinates);
        grid1.insert(p4, true);
        
        // vertices
        coordinates[x] = 1; coordinates[y] = 5;
        vertices.insert(Vertex<number_t>(coordinates, false));

        coordinates[x] = 4; coordinates[y] = 6;
        vertices.insert(Vertex<number_t>(coordinates, true));

        coordinates[x] = 6; coordinates[y] = 8;
        vertices.insert(Vertex<number_t>(coordinates, true));
    }
	
    virtual void TearDown()
    {
    }

    carl::VariablePool& pool = carl::VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");
    
    Point<number_t> p1, p2, p3, p4;
    
    vSet<number_t> vertices;

    Grid<number_t> grid1;
    Grid<number_t> grid2;
};

TEST_F(GridTest, Constructor)
{
    Grid<number_t> grid;
    EXPECT_TRUE(grid.empty());
    Grid<number_t> copy(grid);
    EXPECT_TRUE(copy.empty());
}

TEST_F(GridTest, Access)
{
    EXPECT_TRUE(grid1.find(p1) != grid1.end());
    ++p1[x];
    EXPECT_TRUE(grid1.find(p1) == grid1.end());
}

TEST_F(GridTest, Insert)
{
    Point<number_t> p = Point<number_t>(p4);
    p[x] += FLOAT_T<number_t>(0.5);
    
    grid1.insert(p4, true);
    EXPECT_TRUE(grid1.colourAt(p4));
    EXPECT_TRUE(grid1.colourAt(p));
    
    p[x] += FLOAT_T<number_t>(5);
    p4[x] += FLOAT_T<number_t>(5);
    
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

TEST_F(GridTest, InsertVerticesInMap)
{
    vSet<number_t> vertices;
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
    
    EXPECT_EQ(_p1, grid1.nextPointOnGrid(p1));
    EXPECT_EQ(_p2, grid1.nextPointOnGrid(p2));
    EXPECT_EQ(_p3, grid1.nextPointOnGrid(p3));
    EXPECT_EQ(_p4, grid1.nextPointOnGrid(p4));
}

TEST_F(GridTest, NextPointOnGrid)
{
    // check for original grid
    EXPECT_EQ(p1, grid1.nextPointOnGrid(p1));
    Point<number_t> p = Point<number_t>(p1);
    p[x] += FLOAT_T<number_t>(0.5);
    EXPECT_EQ(p1, grid1.nextPointOnGrid(p));
    
    
    // check for induced grid
    grid1.induceGrid(vertices);
    
    Point<number_t>::rawCoordinateMap c;
    
    c[x] = 1; c[y] = 5;
    Point<number_t> p1(c);
    c[x] = 1; c[y] = 5;
    Point<number_t> np1(c);
    
    c[x] = 2; c[y] = 6;
    Point<number_t> p2(c);
    c[x] = 1; c[y] = 6;
    Point<number_t> np2(c);
    
    c[x] = 5; c[y] = 7;
    Point<number_t> p3(c);
    c[x] = 4; c[y] = 6;
    Point<number_t> np3(c);
    
    EXPECT_EQ(np1, grid1.nextPointOnGrid(p1));
    EXPECT_EQ(np2, grid1.nextPointOnGrid(p2));
    EXPECT_EQ(np3, grid1.nextPointOnGrid(p3));
}

TEST_F(GridTest, CalculateInduced)
{
    grid1.induceGrid(vertices);
    
    Point<number_t>::rawCoordinateMap c;
    
    c[x] = 1; c[y] = 5;
    Point<number_t> p1(c);
    c[x] = 1; c[y] = 1;
    Point<number_t> ip1(c);
    
    c[x] = 2; c[y] = 6;
    Point<number_t> p2(c);
    c[x] = 1; c[y] = 2;
    Point<number_t> ip2(c);
    
    c[x] = 5; c[y] = 7;
    Point<number_t> p3(c);
    c[x] = 2; c[y] = 2;
    Point<number_t> ip3(c);
    
    EXPECT_EQ(ip1, grid1.calculateInduced(p1));
    EXPECT_EQ(ip2, grid1.calculateInduced(p2));
    EXPECT_EQ(ip3, grid1.calculateInduced(p3));
}

TEST_F(GridTest, CalculateOriginal)
{
    grid1.induceGrid(vertices);
    
    Point<number_t>::rawCoordinateMap c;
    
    c[x] = 1; c[y] = 1;
    Point<number_t> ip1(c);
    c[x] = 1; c[y] = 5;
    Point<number_t> op1(c);
    
    c[x] = 1; c[y] = 2;
    Point<number_t> ip2(c);
    c[x] = 1; c[y] = 6;
    Point<number_t> op2(c);
    
    c[x] = 2; c[y] = 2;
    Point<number_t> ip3(c);
    c[x] = 4; c[y] = 6;
    Point<number_t> op3(c);
    
    EXPECT_EQ(op1, grid1.calculateOriginal(ip1));
    EXPECT_EQ(op2, grid1.calculateOriginal(ip2));
    EXPECT_EQ(op3, grid1.calculateOriginal(ip3));
}

TEST_F(GridTest, Translate)
{
    grid1.induceGrid(vertices);
    vSet<number_t> induced;
    Point<number_t>::coordinateMap coordinates;

    coordinates[x] = 1; coordinates[y] = 1;
    induced.insert(Vertex<number_t>(coordinates, false));

    coordinates[x] = 2; coordinates[y] = 2;
    induced.insert(Vertex<number_t>(coordinates, true));

    coordinates[x] = 3; coordinates[y] = 3;
    induced.insert(Vertex<number_t>(coordinates, true));
    
    EXPECT_EQ(induced, grid1.translateToInduced(vertices));
    EXPECT_EQ(vertices, grid1.translateToOriginal(induced));
}
