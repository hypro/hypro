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

template<typename Number>
class GridTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {

        typename Grid<Number>::gridMap map1;
        typename Grid<Number>::gridMap map2;
        
        std::vector<carl::Variable> variables;
        variables.push_back(x);
        variables.push_back(y);

        grid1.reserveInducedGrid(variables);
        grid2.reserveInducedGrid(variables);
        
        // grid1
        typename Point<Number>::coordinateMap coordinates;
        coordinates[x] = Number(1);
        coordinates[y] = Number(1);
        p1 = Point<Number>(coordinates);
        grid1.insert(p1, true);
        
        coordinates[x] = Number(1);
        coordinates[y] = Number(2);
        p2 = Point<Number>(coordinates);
        grid1.insert(p2, false);
        
        // grid2
        coordinates[x] = Number(2);
        coordinates[y] = Number(5);
        p3 = Point<Number>(coordinates);
        grid1.insert(p3, true);
        
        coordinates[x] = Number(2);
        coordinates[y] = Number(5);
        p4 = Point<Number>(coordinates);
        grid1.insert(p4, true);
        
        // vertices
        coordinates[x] = 1; coordinates[y] = 5;
        vertices.insert(Vertex<Number>(coordinates, false));

        coordinates[x] = 4; coordinates[y] = 6;
        vertices.insert(Vertex<Number>(coordinates, true));

        coordinates[x] = 6; coordinates[y] = 8;
        vertices.insert(Vertex<Number>(coordinates, true));
    }
	
    virtual void TearDown()
    {
    }

    carl::VariablePool& pool = carl::VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");
    
    Point<Number> p1, p2, p3, p4;
    
    vSet<Number> vertices;

    Grid<Number> grid1;
    Grid<Number> grid2;
};

TYPED_TEST(GridTest, Constructor)
{
    Grid<TypeParam> grid;
    EXPECT_TRUE(grid.empty());
    Grid<TypeParam> copy(grid);
    EXPECT_TRUE(copy.empty());
}

TYPED_TEST(GridTest, Access)
{
    EXPECT_TRUE(this->grid1.find(this->p1) != this->grid1.end());
    ++this->p1[this->x];
    EXPECT_TRUE(this->grid1.find(this->p1) == this->grid1.end());
}

TYPED_TEST(GridTest, Insert)
{
    Point<TypeParam> p = Point<TypeParam>(this->p4);
    p[this->x] += TypeParam(0.5);
    
    this->grid1.insert(this->p4, true);
    EXPECT_TRUE(this->grid1.colourAt(this->p4));
    EXPECT_TRUE(this->grid1.colourAt(p));
    
    p[this->x] += TypeParam(5);
    this->p4[this->x] += TypeParam(5);
    
    this->grid1.insert(p, false);
    EXPECT_FALSE(this->grid1.colourAt(this->p4));
    EXPECT_FALSE(this->grid1.colourAt(p));
}

TYPED_TEST(GridTest, ColourAt)
{
    EXPECT_TRUE(this->grid1.colourAt(this->p1));
    EXPECT_FALSE(this->grid1.colourAt(this->p2));
    this->p1[this->x] = TypeParam(1.5);
    EXPECT_TRUE(this->grid1.colourAt(this->p1));
    this->p1[this->x] = TypeParam(2);
    EXPECT_FALSE(this->grid1.colourAt(this->p1));
}

TYPED_TEST(GridTest, InsertVerticesInMap)
{
    vSet<TypeParam> vertices;
    typename Point<TypeParam>::coordinateMap coordinates;
    Vertex<TypeParam> v1, v2, v3;
    
    coordinates[this->x] = 1; coordinates[this->y] = 5;
    v1 = Vertex<TypeParam>(coordinates, false);
    coordinates[this->x] = 4; coordinates[this->y] = 7;
    v2 = Vertex<TypeParam>(coordinates, true);
    coordinates[this->x] = 6; coordinates[this->y] = 8;
    v3 = Vertex<TypeParam>(coordinates, true);
    
    this->vertices.insert(v1);
    this->vertices.insert(v2);
    this->vertices.insert(v3);
    
    this->grid1.insertVerticesInMap(this->vertices);
    
    EXPECT_FALSE(this->grid1.colourAt(v1.point()));
    EXPECT_TRUE(this->grid1.colourAt(v2.point()));
    EXPECT_TRUE(this->grid1.colourAt(v3.point()));
}

TYPED_TEST(GridTest, InduceGrid)
{
    EXPECT_FALSE(this->grid1.induced());
    
    this->grid1.induceGrid(this->vertices);
    
    EXPECT_TRUE(this->grid1.induced());
    
    this->p4[this->x] = 10; this->p4[this->y] = 9;
    
    Point<TypeParam> _p1 = Point<TypeParam>(this->p1); // (1;1)
    Point<TypeParam> _p2 = Point<TypeParam>(this->p2); // (1;2)
    Point<TypeParam> _p3 = Point<TypeParam>(this->p3); // (2;5)
    Point<TypeParam> _p4 = Point<TypeParam>(this->p4); // (10;9)
    
    _p1[this->x] = 1; _p1[this->y] = 0;
    _p2[this->x] = 1; _p2[this->y] = 0;
    _p3[this->x] = 1; _p3[this->y] = 5;
    _p4[this->x] = 6; _p4[this->y] = 8;
    
    EXPECT_EQ(_p1, this->grid1.nextPointOnGrid(this->p1));
    EXPECT_EQ(_p2, this->grid1.nextPointOnGrid(this->p2));
    EXPECT_EQ(_p3, this->grid1.nextPointOnGrid(this->p3));
    EXPECT_EQ(_p4, this->grid1.nextPointOnGrid(this->p4));
}

TYPED_TEST(GridTest, NextPointOnGrid)
{
    // check for original grid
    EXPECT_EQ(this->p1, this->grid1.nextPointOnGrid(this->p1));
    Point<TypeParam> p = Point<TypeParam>(this->p1);
    p[this->x] += TypeParam(0.5);
    EXPECT_EQ(this->p1, this->grid1.nextPointOnGrid(p));
    
    
    // check for induced grid
    this->grid1.induceGrid(this->vertices);
    
    typename Point<TypeParam>::coordinateMap c;
    
    c[this->x] = 1; c[this->y] = 5;
    Point<TypeParam> p1(c);
    c[this->x] = 1; c[this->y] = 5;
    Point<TypeParam> np1(c);
    
    c[this->x] = 2; c[this->y] = 6;
    Point<TypeParam> p2(c);
    c[this->x] = 1; c[this->y] = 6;
    Point<TypeParam> np2(c);
    
    c[this->x] = 5; c[this->y] = 7;
    Point<TypeParam> p3(c);
    c[this->x] = 4; c[this->y] = 6;
    Point<TypeParam> np3(c);
    
    EXPECT_EQ(np1, this->grid1.nextPointOnGrid(p1));
    EXPECT_EQ(np2, this->grid1.nextPointOnGrid(p2));
    EXPECT_EQ(np3, this->grid1.nextPointOnGrid(p3));
}

TYPED_TEST(GridTest, CalculateInduced)
{
    this->grid1.induceGrid(this->vertices);
    
    typename Point<TypeParam>::coordinateMap c;
    
    c[this->x] = 1; c[this->y] = 5;
    Point<TypeParam> p1(c);
    c[this->x] = 1; c[this->y] = 1;
    Point<TypeParam> ip1(c);
    
    c[this->x] = 2; c[this->y] = 6;
    Point<TypeParam> p2(c);
    c[this->x] = 1; c[this->y] = 2;
    Point<TypeParam> ip2(c);
    
    c[this->x] = 5; c[this->y] = 7;
    Point<TypeParam> p3(c);
    c[this->x] = 2; c[this->y] = 2;
    Point<TypeParam> ip3(c);
    
    EXPECT_EQ(ip1, this->grid1.calculateInduced(p1));
    EXPECT_EQ(ip2, this->grid1.calculateInduced(p2));
    EXPECT_EQ(ip3, this->grid1.calculateInduced(p3));
}

TYPED_TEST(GridTest, CalculateOriginal)
{
    this->grid1.induceGrid(this->vertices);
    
    typename Point<TypeParam>::coordinateMap c;
    
    c[this->x] = 1; c[this->y] = 1;
    Point<TypeParam> ip1(c);
    c[this->x] = 1; c[this->y] = 5;
    Point<TypeParam> op1(c);
    
    c[this->x] = 1; c[this->y] = 2;
    Point<TypeParam> ip2(c);
    c[this->x] = 1; c[this->y] = 6;
    Point<TypeParam> op2(c);
    
    c[this->x] = 2; c[this->y] = 2;
    Point<TypeParam> ip3(c);
    c[this->x] = 4; c[this->y] = 6;
    Point<TypeParam> op3(c);
    
    EXPECT_EQ(op1, this->grid1.calculateOriginal(ip1));
    EXPECT_EQ(op2, this->grid1.calculateOriginal(ip2));
    EXPECT_EQ(op3, this->grid1.calculateOriginal(ip3));
}

TYPED_TEST(GridTest, Translate)
{
    this->grid1.induceGrid(this->vertices);
    vSet<TypeParam> induced;
    typename Point<TypeParam>::coordinateMap coordinates;

    coordinates[this->x] = 1; coordinates[this->y] = 1;
    induced.insert(Vertex<TypeParam>(coordinates, false));

    coordinates[this->x] = 2; coordinates[this->y] = 2;
    induced.insert(Vertex<TypeParam>(coordinates, true));

    coordinates[this->x] = 3; coordinates[this->y] = 3;
    induced.insert(Vertex<TypeParam>(coordinates, true));
    
    EXPECT_EQ(induced, this->grid1.translateToInduced(this->vertices));
    EXPECT_EQ(this->vertices, this->grid1.translateToOriginal(induced));
}
