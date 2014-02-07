#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/Point.h"
#include <carl/core/VariablePool.h>
#include "carl/numbers/FLOAT_T.h"

using namespace hypro;
using namespace carl;

class PointTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        // p1
        Point<number_t>::vector_t coordinates1;
		//VariablePool& pool = VariablePool::getInstance();
		//Variable x = pool.getFreshVariable("x");
		//Variable y = pool.getFreshVariable("y");
        coordinates1.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates1.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        p1 = Point<number_t>(coordinates1);

        // p2
        Point<number_t>::vector_t coordinates2;
        coordinates2.insert( std::make_pair(a, FLOAT_T<number_t>(7)) );
        coordinates2.insert( std::make_pair(b, FLOAT_T<number_t>(8)) );
        p2 = Point<number_t>(coordinates2);

        // p3
        Point<number_t>::vector_t coordinates3;
        coordinates3.insert( std::make_pair(c, FLOAT_T<number_t>(-9)) );
		coordinates3.insert( std::make_pair(d, FLOAT_T<number_t>(13)) );
        p3 = Point<number_t>(coordinates3);
    }

    virtual void TearDown()
    {
    }
	
	VariablePool& pool = VariablePool::getInstance();
	Variable x = pool.getFreshVariable("x");
	Variable y = pool.getFreshVariable("y");
	Variable a = pool.getFreshVariable("a");
	Variable b = pool.getFreshVariable("b");
	Variable c = pool.getFreshVariable("c");
	Variable d = pool.getFreshVariable("d");
	
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
	EXPECT_EQ(p1[x], FLOAT_T<number_t>(2));
    EXPECT_EQ(p1[y], FLOAT_T<number_t>(5));
    EXPECT_EQ(p1.coordinate(x), FLOAT_T<number_t>(2));
    EXPECT_EQ(p1.coordinate(y), FLOAT_T<number_t>(5));
    EXPECT_EQ(p1.dimension(), (unsigned) 2);
    
    p1.IncrementInFixedDim(y);
    EXPECT_EQ(p1[y], FLOAT_T<number_t>(6));
    p1.IncrementInAllDim(FLOAT_T<number_t>(3));
    EXPECT_EQ(p1[x], FLOAT_T<number_t>(5));
    EXPECT_EQ(p1[y], FLOAT_T<number_t>(9));
    p1.DecrementInFixedDim(y);
    EXPECT_EQ(p1[y], FLOAT_T<number_t>(8));
    
    p1[x] = FLOAT_T<number_t>(3);
    p1[y] = FLOAT_T<number_t>(-1);
    EXPECT_EQ(p1[x], FLOAT_T<number_t>(3));
    EXPECT_EQ(p1[y], FLOAT_T<number_t>(-1));
    p1.setCoordinate(x, 4);
    p1.setCoordinate(y, 7);
    EXPECT_EQ(p1[x], FLOAT_T<number_t>(4));
    EXPECT_EQ(p1[y], FLOAT_T<number_t>(7));
}

/**
 * @covers Point::move
 */
TEST_F(PointTest, OperationTest)
{
    EXPECT_FALSE(p1.move(p1));
    EXPECT_EQ(p1[x], FLOAT_T<number_t>(4));
    EXPECT_EQ(p1[y], FLOAT_T<number_t>(10));

    EXPECT_TRUE(p2.move(p3));
    EXPECT_EQ(p2[a], FLOAT_T<number_t>(7));
    EXPECT_EQ(p2[b], FLOAT_T<number_t>(8));
	EXPECT_EQ(p2[c], FLOAT_T<number_t>(-9));
    EXPECT_EQ(p2[d], FLOAT_T<number_t>(13));
}

/**
 * @covers Point::isInBoundary
 * @covers Point::compareReducedDimension
 * @covers Point::haveEqualCoordinate
 */
TEST_F(PointTest, BooleanTest)
{
    EXPECT_TRUE(p1.isInBoundary(p2));
    EXPECT_TRUE(p2.isInBoundary(p1));
	EXPECT_TRUE(p1.isInBoundary(p1));
	
    p1[x] = FLOAT_T<number_t>(3);
    p2[x] = FLOAT_T<number_t>(4);
	p2[y] = FLOAT_T<number_t>(5);
	
    EXPECT_TRUE(p1.haveEqualCoordinate(p1));
    EXPECT_FALSE(p1.haveEqualCoordinate(p3));
	p2.removeDimension(a);
	p2.removeDimension(b);
    EXPECT_LT(p1, p2);
	
    p2[x] = FLOAT_T<number_t>(3);
	p2.removeDimension(a);
	
    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);
}

TEST_F(PointTest, Constructor)
{ 
    Point<number_t> p;
    EXPECT_EQ(p.dimension(), 0);
    
    p = Point<number_t>(y, 5);
    EXPECT_EQ(p.dimension(), 1);
    
	p[pool.getFreshVariable()] = 2;
	p[pool.getFreshVariable()] = 2;
	p[pool.getFreshVariable()] = 2;
	p[pool.getFreshVariable()] = 2;
	p[pool.getFreshVariable()] = 2;
	p[pool.getFreshVariable()] = 2;
	
    EXPECT_EQ(p.dimension(), (unsigned) 7);
    EXPECT_EQ(p[y], FLOAT_T<number_t>(5));
    
    Point<number_t> pCopy = Point<number_t>(p);
    EXPECT_EQ(p, pCopy);
    
    //ASSERT_NE(Point<number_t>(3), Point<number_t>(7));
}