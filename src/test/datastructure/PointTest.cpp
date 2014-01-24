#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/Point.h"
//#include "carl/numbers/FLOAT_T.h"

using namespace hypro;
using namespace carl;

class PointTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        // p1
        Point<number_t>::vector_t coordinates1;
        coordinates1.push_back(FLOAT_T<number_t>(2));
        coordinates1.push_back(FLOAT_T<number_t>(5));
        p1 = Point<number_t>(coordinates1);

        // p2
        Point<number_t>::vector_t coordinates2;
        coordinates2.push_back(FLOAT_T<number_t>(7));
        coordinates2.push_back(FLOAT_T<number_t>(8));
        p2 = Point<number_t>(coordinates2);

        // p3
        Point<number_t>::vector_t coordinates3;
        coordinates3.push_back(FLOAT_T<number_t>(-9));
        coordinates3.push_back(FLOAT_T<number_t>(13));
        p3 = Point<number_t>(coordinates3);
    }

    virtual void TearDown()
    {
    }

    Point<number_t> p1;
    Point<number_t> p2;
    Point<number_t> p3;
};

/**
 * @covers Point::coordinate
 * @covers Point::dimension
 * @covers Point::IncrementInFixedDim
 * @covers Point::IncrementInAllDim
 * @covers Point::DecrementInFixedDim
 * @covers Point::setCoordinate
 */
TEST_F(PointTest, CoordinateDimensionTest)
{ 
    ASSERT_EQ(p1[0], FLOAT_T<number_t>(2));
    ASSERT_EQ(p1[1], FLOAT_T<number_t>(5));
    ASSERT_EQ(p1.coordinate(0), FLOAT_T<number_t>(2));
    ASSERT_EQ(p1.coordinate(1), FLOAT_T<number_t>(5));
    ASSERT_EQ(p1.dimension(), (unsigned) 2);
    
    p1.IncrementInFixedDim(1);
    ASSERT_EQ(p1[1], FLOAT_T<number_t>(6));
    p1.IncrementInAllDim(FLOAT_T<number_t>(3));
    ASSERT_EQ(p1[0], FLOAT_T<number_t>(5));
    ASSERT_EQ(p1[1], FLOAT_T<number_t>(9));
    p1.DecrementInFixedDim(1);
    ASSERT_EQ(p1[1], FLOAT_T<number_t>(8));
    
    p1[0] = FLOAT_T<number_t>(3);
    p1[1] = FLOAT_T<number_t>(-1);
    ASSERT_EQ(p1[0], FLOAT_T<number_t>(3));
    ASSERT_EQ(p1[1], FLOAT_T<number_t>(-1));
    p1.setCoordinate(0, 4);
    p1.setCoordinate(1, 7);
    ASSERT_EQ(p1[0], FLOAT_T<number_t>(4));
    ASSERT_EQ(p1[1], FLOAT_T<number_t>(7));
}

/**
 * @covers Point::move
 */
TEST_F(PointTest, OperationTest)
{	
    std::cout << p1 << "\n" << p2 << std::endl;
    ASSERT_FALSE(p1.move(p2));
    ASSERT_EQ(p1[0], FLOAT_T<number_t>(9));
    ASSERT_EQ(p1[1], FLOAT_T<number_t>(13));

    ASSERT_TRUE(p2.move(p3));
    ASSERT_EQ(p2[0], FLOAT_T<number_t>(-2));
    ASSERT_EQ(p2[1], FLOAT_T<number_t>(21));
}

/**
 * @covers Point::isInBoundary
 * @covers Point::compareReducedDimension
 * @covers Point::haveEqualCoordinate
 */
TEST_F(PointTest, BooleanTest)
{
    ASSERT_TRUE(p1.isInBoundary(p2));
    ASSERT_FALSE(p2.isInBoundary(p1));

    p1[0] = FLOAT_T<number_t>(3);
    p2[0] = FLOAT_T<number_t>(3);
    ASSERT_TRUE(p1.compareReducedDimension(p2, 1));
    ASSERT_FALSE(p1.compareReducedDimension(p3, 1));
    ASSERT_TRUE(p1.haveEqualCoordinate(p2));
    ASSERT_FALSE(p1.haveEqualCoordinate(p3));

    ASSERT_LT(p1, p2);
    ASSERT_GT(p2, p3);

    p1[1] = FLOAT_T<number_t>(6);
    p2[1] = FLOAT_T<number_t>(6);
    ASSERT_EQ(p1, p2);
    ASSERT_NE(p1, p3);
}

TEST_F(PointTest, Constructor)
{ 
    Point<number_t> p;
    ASSERT_EQ(p.dimension(), 1);
    
    p = Point<number_t>(1, 5);
    ASSERT_EQ(p.dimension(), 5);
    
    FLOAT_T<number_t> initialValue(4);
    p = Point<number_t>(initialValue, 7);
    ASSERT_EQ(p.dimension(), (unsigned) 7);
    ASSERT_EQ(p[0], FLOAT_T<number_t>(4));
    ASSERT_EQ(p[6], FLOAT_T<number_t>(4));
    
    Point<number_t> pCopy = Point<number_t>(p);
    ASSERT_EQ(p, pCopy);
    
    ASSERT_NE(Point<number_t>(3), Point<number_t>(7));
}