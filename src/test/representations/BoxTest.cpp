/**
 * @file    BoxTest.cpp
 * 
 * @covers  Box
 * 
 * @author  Benedikt Seidl
 * 
 * @since
 * @version 2014-05-27
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include <carl/numbers/FLOAT_T.h>
#include <carl/core/VariablePool.h>
#include "../../lib/datastructures/Point.h"
#include "../../lib/representations/Box/Box.h"

using namespace hypro;
using namespace carl;

class BoxTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        std::map<const carl::Variable, carl::Interval<number> > boundaries1;
        boundaries1.insert(std::make_pair(x, Interval<number>(2,6)));
        boundaries1.insert(std::make_pair(y, Interval<number>(1,3)));
        box1.insert(boundaries1);
        
        std::map<const carl::Variable, carl::Interval<number> > boundaries2;
        boundaries2.insert(std::make_pair(x, Interval<number>(-1,6)));
        boundaries2.insert(std::make_pair(y, Interval<number>(4,7)));
        box2.insert(boundaries2);
    }
	
    virtual void TearDown()
    {
    }
	
    carl::VariablePool& pool = carl::VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");

    Box<number> box1;
    Box<number> box2;
    Box<number> box3;
};

TEST_F(BoxTest, Constructor)
{
    Box<number> aBox = Box<number>();
    SUCCEED();
}

TEST_F(BoxTest, Access)
{
    Box<number>::intervalMap tmp = box1.boundaries();
    EXPECT_EQ(2, tmp[x].lower());
    EXPECT_EQ(6, tmp[x].upper());
    EXPECT_EQ(1, tmp[y].lower());
    EXPECT_EQ(3, tmp[y].upper());
    
    EXPECT_EQ((unsigned) 2, box1.dimension());
    EXPECT_EQ((unsigned) 2, box2.dimension());
    EXPECT_EQ((unsigned) 0, box3.dimension());
    
    EXPECT_TRUE(box1.haveSameDimensions(box2));
    EXPECT_FALSE(box1.haveSameDimensions(box3));
    
    Point<number>::coordinateMap coMax1;
    coMax1.insert(std::make_pair(x, 6));
    coMax1.insert(std::make_pair(y, 3));
    EXPECT_EQ(Point<number>(coMax1), box1.max());
    Point<number>::coordinateMap coMin1;
    coMin1.insert(std::make_pair(x, 2));
    coMin1.insert(std::make_pair(y, 1));
    EXPECT_EQ(Point<number>(coMin1), box1.min());
    
    EXPECT_EQ(box1, box1);
    EXPECT_EQ(box2, box2);
    EXPECT_EQ(box3, box3);
    EXPECT_NE(box1, box2);
    EXPECT_NE(box2, box3);
    EXPECT_NE(box3, box1);
    
    Box<number> emptyBox;
    EXPECT_FALSE(box1.isEmpty());
    EXPECT_TRUE(emptyBox.isEmpty());
}

TEST_F(BoxTest, Insertion)
{
    Box<number>::intervalMap tmp;
    Variable z = pool.getFreshVariable("z");
    tmp.insert(std::make_pair(z, Interval<number>(3,9)));
    box1.insert(tmp);
    EXPECT_EQ(true, box1.hasDimension(z));
    
    EXPECT_EQ(3, box1.interval(z).lower());
    EXPECT_EQ(9, box1.interval(z).upper());
    
    Variable w = pool.getFreshVariable("w");
    box1.insert(std::make_pair(w, Interval<number>(4,5)));
    EXPECT_EQ(true, box1.hasDimension(w));
    
    EXPECT_EQ(4, box1.interval(w).lower());
    EXPECT_EQ(5, box1.interval(w).upper());
}

TEST_F(BoxTest, Union)
{
    cln::cl_RA tmp;
}

TEST_F(BoxTest, LinearTransformation)
{

}

TEST_F(BoxTest, MinkowskiSum)
{
    Box<number> result;
    box1.minkowskiSum(result, box2);
    EXPECT_EQ(1 , result.interval(x).lower());
    EXPECT_EQ(12 , result.interval(x).upper());
    EXPECT_EQ(5 , result.interval(y).lower());
    EXPECT_EQ(10 , result.interval(y).upper());
}

TEST_F(BoxTest, Intersection)
{
    Box<number> result;
    box1.intersect(result, box2);
    EXPECT_TRUE(result.isEmpty());
}

TEST_F(BoxTest, ConvexHull)
{
    // stupid for Boxes, only required for orthogonal polyhedra
    Box<number> result;
    EXPECT_TRUE(box1.hull(result));
    EXPECT_EQ(box1, result);
}

TEST_F(BoxTest, Membership)
{
    Point<number> p;
    p.setCoordinate(x, 4);
    p.setCoordinate(y, 2);
    EXPECT_TRUE(box1.contains(p));
}
