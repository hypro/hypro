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
		pool.clear();
		x = pool.newCarlVariable();
		y = pool.newCarlVariable();
        typename Point<Number>::coordinateMap coordinates;

        // vertices

        coordinates[x] = 1; coordinates[y] = 5;
        vertices.insert(Vertex<Number>(coordinates, false));

        coordinates[x] = 4; coordinates[y] = 6;
        vertices.insert(Vertex<Number>(coordinates, true));

        coordinates[x] = 6; coordinates[y] = 8;
        vertices.insert(Vertex<Number>(coordinates, true));

	grid1.induceGrid(vertices);
    }
	
    virtual void TearDown()
    {
    }

    vSet<Number> vertices;

    hypro::VariablePool& pool = hypro::VariablePool::getInstance();
    Variable x;
    Variable y;

    Grid<Number> grid1;
};

TYPED_TEST(GridTest, Constructor)
{
    Grid<TypeParam> grid;
    EXPECT_TRUE(grid.empty());
    Grid<TypeParam> copy(grid);
    EXPECT_TRUE(copy.empty());
}

TYPED_TEST(GridTest, Properties)
{
    Point<TypeParam> p1;
//    p1[this->x] = 2;
//    p1[this->y] = 5;
    p1[this->x] = 4;
    p1[this->y] = 6;
    
    EXPECT_FALSE(this->grid1.empty());
    EXPECT_EQ(3, this->grid1.size());
    EXPECT_TRUE(this->grid1.find(p1) != this->grid1.end());
    
    this->grid1.clear();
    EXPECT_TRUE(this->grid1.empty());
    EXPECT_EQ(0, this->grid1.size());
    EXPECT_FALSE(this->grid1.find(p1) != this->grid1.end());
}

TYPED_TEST(GridTest, Insert)
{
    Point<TypeParam> p;
    
    p[this->x] = 2; p[this->y] = 7;
    this->grid1.insert(p, true);
    EXPECT_EQ(true, this->grid1.colorAt(p));
    
    p[this->x] = 0; p[this->y] = 0;
    this->grid1.insert(p, false);
    EXPECT_EQ(false, this->grid1.colorAt(p));
    
    p[this->x] = 1; p[this->y] = 2;
    this->grid1.insert(p, true);
    EXPECT_EQ(true, this->grid1.colorAt(p));
    
    p[this->x] = 10; p[this->y] = 7;
    this->grid1.insert(p, false);
    EXPECT_EQ(false, this->grid1.colorAt(p));
    
    p[this->x] = 10; p[this->y] = 10;
    this->grid1.insert(p, false);
    EXPECT_EQ(true, this->grid1.colorAt(p));
}

TYPED_TEST(GridTest, InsertInduced)
{
    Point<int> p;

    p[this->x] = 1; p[this->y] = 2;
    this->grid1.insertInduced(p, true);
    EXPECT_EQ(true, this->grid1.colorAtInduced(p));
    
    p[this->x] = 0; p[this->y] = 0;
    this->grid1.insertInduced(p, false);
    EXPECT_EQ(false, this->grid1.colorAtInduced(p));
    
    p[this->x] = 1; p[this->y] = 0;
    this->grid1.insertInduced(p, true);
    EXPECT_EQ(true, this->grid1.colorAtInduced(p));
    
    p[this->x] = 3; p[this->y] = 2;
    this->grid1.insertInduced(p, false);
    EXPECT_EQ(false, this->grid1.colorAtInduced(p));
    
    p[this->x] = 3; p[this->y] = 3;
    this->grid1.insertInduced(p, false);
    EXPECT_EQ(true, this->grid1.colorAtInduced(p));
}

TYPED_TEST(GridTest, ColorAt)
{
    Point<TypeParam> p;

    p[this->x] = 1; p[this->y] = 5;
    EXPECT_EQ(false, this->grid1.colorAt(p));

    p[this->x] = 4; p[this->y] = 6;
    EXPECT_EQ(true, this->grid1.colorAt(p));

    p[this->x] = 6; p[this->y] = 8;
    EXPECT_EQ(true, this->grid1.colorAt(p));

    p[this->x] = 0; p[this->y] = 0;
    EXPECT_THROW(this->grid1.colorAt(p), std::out_of_range);
}

TYPED_TEST(GridTest, ColorAtInduced)
{
    Point<int> p;

    p[this->x] = 1; p[this->y] = 1;
    EXPECT_EQ(false, this->grid1.colorAtInduced(p));

    p[this->x] = 2; p[this->y] = 2;
    EXPECT_EQ(true, this->grid1.colorAtInduced(p));

    p[this->x] = 3; p[this->y] = 3;
    EXPECT_EQ(true, this->grid1.colorAtInduced(p));

    p[this->x] = 0; p[this->y] = 0;
    EXPECT_THROW(this->grid1.colorAtInduced(p), std::out_of_range);
}

TYPED_TEST(GridTest, CalculateInduced)
{
    Point<int>::coordinateMap i;
    typename Point<TypeParam>::coordinateMap c;
    
    c[this->x] = 1; c[this->y] = 5;
    Point<TypeParam> p1(c);
    i[this->x] = 1; i[this->y] = 1;
    Point<int> ip1(i);
    
    c[this->x] = 2; c[this->y] = 6;
    Point<TypeParam> p2(c);
    i[this->x] = 1; i[this->y] = 2;
    Point<int> ip2(i);
    
    c[this->x] = 5; c[this->y] = 7;
    Point<TypeParam> p3(c);
    i[this->x] = 2; i[this->y] = 2;
    Point<int> ip3(i);
    
    EXPECT_EQ(ip1, this->grid1.calculateInduced(p1));
    EXPECT_EQ(ip2, this->grid1.calculateInduced(p2));
    EXPECT_EQ(ip3, this->grid1.calculateInduced(p3));
}

TYPED_TEST(GridTest, CalculateOriginal)
{
    Point<int>::coordinateMap i;
    typename Point<TypeParam>::coordinateMap c;
    
    i[this->x] = 1; i[this->y] = 1;
    Point<int> ip1(i);
    c[this->x] = 1; c[this->y] = 5;
    Point<TypeParam> op1(c);
    
    i[this->x] = 1; i[this->y] = 2;
    Point<int> ip2(i);
    c[this->x] = 1; c[this->y] = 6;
    Point<TypeParam> op2(c);
    
    i[this->x] = 2; i[this->y] = 2;
    Point<int> ip3(i);
    c[this->x] = 4; c[this->y] = 6;
    Point<TypeParam> op3(c);
    
    EXPECT_EQ(op1, this->grid1.calculateOriginal(ip1));
    EXPECT_EQ(op2, this->grid1.calculateOriginal(ip2));
    EXPECT_EQ(op3, this->grid1.calculateOriginal(ip3));
}

TYPED_TEST(GridTest, Translate)
{
    vSet<int> induced;
    typename Point<int>::coordinateMap coordinates;

    coordinates[this->x] = 1; coordinates[this->y] = 1;
    induced.insert(Vertex<int>(coordinates, false));

    coordinates[this->x] = 2; coordinates[this->y] = 2;
    induced.insert(Vertex<int>(coordinates, true));

    coordinates[this->x] = 3; coordinates[this->y] = 3;
    induced.insert(Vertex<int>(coordinates, true));
    
    EXPECT_EQ(induced, this->grid1.translateToInduced(this->vertices));
    EXPECT_EQ(this->vertices, this->grid1.translateToOriginal(induced));
}