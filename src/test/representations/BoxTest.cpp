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

template<typename Number>
class BoxTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
		pool.clear();
		x = pool.newCarlVariable();
		y = pool.newCarlVariable();
        std::map<const carl::Variable, carl::Interval<Number> > boundaries1;
        boundaries1.insert(std::make_pair(x, Interval<Number>(2,6)));
        boundaries1.insert(std::make_pair(y, Interval<Number>(1,3)));
        box1.insert(boundaries1);
        
        std::map<const carl::Variable, carl::Interval<Number> > boundaries2;
        boundaries2.insert(std::make_pair(x, Interval<Number>(-1,6)));
        boundaries2.insert(std::make_pair(y, Interval<Number>(4,7)));
        box2.insert(boundaries2);
    }
	
    virtual void TearDown()
    {
    }
	
    hypro::VariablePool& pool = hypro::VariablePool::getInstance();
    Variable x;
    Variable y;

    Box<Number> box1;
    Box<Number> box2;
    Box<Number> box3;
};

TYPED_TEST(BoxTest, Constructor)
{
    Box<TypeParam> aBox = Box<TypeParam>();
    SUCCEED();
}

TYPED_TEST(BoxTest, Access)
{
    typename Box<TypeParam>::intervalMap tmp = this->box1.boundaries();
    EXPECT_EQ(2, tmp[this->x].lower());
    EXPECT_EQ(6, tmp[this->x].upper());
    EXPECT_EQ(1, tmp[this->y].lower());
    EXPECT_EQ(3, tmp[this->y].upper());
    
    EXPECT_EQ((unsigned) 2, this->box1.dimension());
    EXPECT_EQ((unsigned) 2, this->box2.dimension());
    EXPECT_EQ((unsigned) 0, this->box3.dimension());
    
    EXPECT_TRUE(this->box1.haveSameDimensions(this->box2));
    EXPECT_FALSE(this->box1.haveSameDimensions(this->box3));
    
    typename Point<TypeParam>::coordinateMap coMax1;
    coMax1.insert(std::make_pair(this->x, 6));
    coMax1.insert(std::make_pair(this->y, 3));
    EXPECT_EQ(Point<TypeParam>(coMax1), this->box1.max());
    typename Point<TypeParam>::coordinateMap coMin1;
    coMin1.insert(std::make_pair(this->x, 2));
    coMin1.insert(std::make_pair(this->y, 1));
    EXPECT_EQ(Point<TypeParam>(coMin1), this->box1.min());
    
    EXPECT_EQ(this->box1, this->box1);
    EXPECT_EQ(this->box2, this->box2);
    EXPECT_EQ(this->box3, this->box3);
    EXPECT_NE(this->box1, this->box2);
    EXPECT_NE(this->box2, this->box3);
    EXPECT_NE(this->box3, this->box1);
    
    Box<TypeParam> emptyBox;
    EXPECT_FALSE(this->box1.isEmpty());
    EXPECT_TRUE(emptyBox.isEmpty());
}

TYPED_TEST(BoxTest, Insertion)
{
    typename Box<TypeParam>::intervalMap tmp;
    Variable z = this->pool.newCarlVariable();
    tmp.insert(std::make_pair(z, Interval<TypeParam>(3,9)));
    this->box1.insert(tmp);
    EXPECT_EQ(true, this->box1.hasDimension(z));
    
    EXPECT_EQ(3, this->box1.interval(z).lower());
    EXPECT_EQ(9, this->box1.interval(z).upper());
    
    Variable w = this->pool.newCarlVariable();
    this->box1.insert(std::make_pair(w, Interval<TypeParam>(4,5)));
    EXPECT_EQ(true, this->box1.hasDimension(w));
    
    EXPECT_EQ(4, this->box1.interval(w).lower());
    EXPECT_EQ(5, this->box1.interval(w).upper());
}

TYPED_TEST(BoxTest, Union)
{
    cln::cl_RA tmp;
}

TYPED_TEST(BoxTest, LinearTransformation)
{

}

TYPED_TEST(BoxTest, MinkowskiSum)
{
    Box<TypeParam> result;
    this->box1.minkowskiSum(result, this->box2);
    EXPECT_EQ(1 , result.interval(this->x).lower());
    EXPECT_EQ(12 , result.interval(this->x).upper());
    EXPECT_EQ(5 , result.interval(this->y).lower());
    EXPECT_EQ(10 , result.interval(this->y).upper());
}

TYPED_TEST(BoxTest, Intersection)
{
    Box<TypeParam> result;
    this->box1.intersect(result, this->box2);
    EXPECT_TRUE(result.isEmpty());
}

TYPED_TEST(BoxTest, ConvexHull)
{
    // stupid for Boxes, only required for orthogonal polyhedra
    Box<TypeParam> result;
    EXPECT_TRUE(this->box1.hull(result));
    EXPECT_EQ(this->box1, result);
}

TYPED_TEST(BoxTest, Membership)
{
    Point<TypeParam> p;
    p.setCoordinate(this->x, 4);
    p.setCoordinate(this->y, 2);
    EXPECT_TRUE(this->box1.contains(p));
}
