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
        // vertices

        vertices.insert(Vertex<Number>({1, 5}, false));
        vertices.insert(Vertex<Number>({4, 6}, true));
        vertices.insert(Vertex<Number>({6, 8}, true));

	grid1.induceGrid(vertices);
    }
	
    virtual void TearDown()
    {
    }

    vSet<Number> vertices;

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
    Point<TypeParam> p1({2, 5});
    
    EXPECT_FALSE(this->grid1.empty());
    EXPECT_EQ(this->grid1.size(),3);
    EXPECT_TRUE(this->grid1.find(p1) != this->grid1.end());
    
    this->grid1.clear();
    EXPECT_TRUE(this->grid1.empty());
    EXPECT_EQ(this->grid1.size(),0);
    EXPECT_FALSE(this->grid1.find(p1) != this->grid1.end());
}

TYPED_TEST(GridTest, Insert)
{
    Point<TypeParam> p;
    
    p = Point<TypeParam>({2, 7});
    this->grid1.insert(p, true);
    EXPECT_EQ(true, this->grid1.colorAt(p));
    
    p = Point<TypeParam>({0, 0});
    this->grid1.insert(p, false);
    EXPECT_EQ(false, this->grid1.colorAt(p));
    
    p = Point<TypeParam>({1, 2});
    this->grid1.insert(p, true);
    EXPECT_EQ(true, this->grid1.colorAt(p));
    
    p = Point<TypeParam>({10, 7});
    this->grid1.insert(p, false);
    EXPECT_EQ(false, this->grid1.colorAt(p));
    
    p = Point<TypeParam>({10, 10});
    this->grid1.insert(p, false);
    EXPECT_EQ(true, this->grid1.colorAt(p));
}

TYPED_TEST(GridTest, InsertInduced)
{
    Point<int> p;

    p = Point<TypeParam>({1, 2});
    this->grid1.insertInduced(p, true);
    EXPECT_EQ(true, this->grid1.colorAtInduced(p));
    
    p = Point<TypeParam>({0, 0});
    this->grid1.insertInduced(p, false);
    EXPECT_EQ(false, this->grid1.colorAtInduced(p));
    
    p = Point<TypeParam>({1, 0});
    this->grid1.insertInduced(p, true);
    EXPECT_EQ(true, this->grid1.colorAtInduced(p));
    
    p = Point<TypeParam>({3, 2});
    this->grid1.insertInduced(p, false);
    EXPECT_EQ(false, this->grid1.colorAtInduced(p));
    
    p = Point<TypeParam>({3, 3});
    this->grid1.insertInduced(p, false);
    EXPECT_EQ(true, this->grid1.colorAtInduced(p));
}

TYPED_TEST(GridTest, ColorAt)
{
    Point<TypeParam> p;

    p = Point<TypeParam>({1, 5});
    EXPECT_EQ(false, this->grid1.colorAt(p));

    p = Point<TypeParam>({4, 6});
    EXPECT_EQ(true, this->grid1.colorAt(p));

    p = Point<TypeParam>({6, 8});
    EXPECT_EQ(true, this->grid1.colorAt(p));

    p = Point<TypeParam>({0, 0});
    EXPECT_THROW(this->grid1.colorAt(p), std::out_of_range);
}

TYPED_TEST(GridTest, ColorAtInduced)
{
    Point<int> p;

    p = Point<TypeParam>({1, 1});
    EXPECT_EQ(false, this->grid1.colorAtInduced(p));

    p = Point<TypeParam>({2, 2});
    EXPECT_EQ(true, this->grid1.colorAtInduced(p));

    p = Point<TypeParam>({3, 3});
    EXPECT_EQ(true, this->grid1.colorAtInduced(p));

    p = Point<TypeParam>({0, 0});
    EXPECT_THROW(this->grid1.colorAtInduced(p), std::out_of_range);
}

TYPED_TEST(GridTest, CalculateInduced)
{
    Point<int>::coordinateMap i;
    typename Point<TypeParam>::coordinateMap c;
    
    Point<TypeParam> p1({1, 5});
    Point<int> ip1({1, 1});
    
    Point<TypeParam> p2({2, 6});
    Point<int> ip2({1, 2});
    
    Point<TypeParam> p3({5, 7});
    Point<int> ip3({2, 2});
    
    EXPECT_EQ(ip1, this->grid1.calculateInduced(p1).first);
    EXPECT_EQ(ip2, this->grid1.calculateInduced(p2).first);
    EXPECT_EQ(ip3, this->grid1.calculateInduced(p3).first);
}

TYPED_TEST(GridTest, CalculateOriginal)
{
    Point<int>::coordinateMap i;
    typename Point<TypeParam>::coordinateMap c;
    
    Point<int> ip1({1, 1});
    Point<TypeParam> op1({1, 5});
    
    Point<int> ip2({1, 2});
    Point<TypeParam> op2({1, 6});
    
    Point<int> ip3({2, 2});
    Point<TypeParam> op3({4, 6});
    
    EXPECT_EQ(op1, this->grid1.calculateOriginal(ip1));
    EXPECT_EQ(op2, this->grid1.calculateOriginal(ip2));
    EXPECT_EQ(op3, this->grid1.calculateOriginal(ip3));
}

TYPED_TEST(GridTest, Translate)
{
    vSet<unsigned> induced;

    induced.insert(Vertex<unsigned>({1, 1}, false));
    induced.insert(Vertex<unsigned>({2, 2}, true));
    induced.insert(Vertex<unsigned>({3, 3}, true));
    
    EXPECT_EQ(induced, this->grid1.translateToInduced(this->vertices));
    EXPECT_EQ(this->vertices, this->grid1.translateToOriginal(induced));
}