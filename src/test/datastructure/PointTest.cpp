/**
 *  Testfile for the point datastructure.
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Benedikt Seidl
 */

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
        Point<number_t>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates1.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        p1 = Point<number_t>(coordinates1);

        // p2
        Point<number_t>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(a, FLOAT_T<number_t>(7)) );
        coordinates2.insert( std::make_pair(b, FLOAT_T<number_t>(8)) );
        p2 = Point<number_t>(coordinates2);

        // p3
        Point<number_t>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(c, FLOAT_T<number_t>(9)) );
        coordinates3.insert( std::make_pair(d, FLOAT_T<number_t>(-13)) );
        p3 = Point<number_t>(coordinates3);
        
        // p4
        Point<number_t>::coordinateMap coordinates4;
        coordinates4.insert( std::make_pair(c, FLOAT_T<number_t>(5)) );
        coordinates4.insert( std::make_pair(d, FLOAT_T<number_t>(8)) );
        p4 = Point<number_t>(coordinates4);
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
    Point<number_t> p4;
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
    
    p1.incrementInFixedDim(y);
    EXPECT_EQ(p1[y], FLOAT_T<number_t>(6));
    p1.incrementInAllDim(FLOAT_T<number_t>(3));
    EXPECT_EQ(p1[x], FLOAT_T<number_t>(5));
    EXPECT_EQ(p1[y], FLOAT_T<number_t>(9));
    p1.decrementInFixedDim(y);
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
    EXPECT_EQ(p2[c], FLOAT_T<number_t>(9));
    EXPECT_EQ(p2[d], FLOAT_T<number_t>(-13));
}

/**
 * @covers <>
 */
TEST_F(PointTest, BinaryOperatorTest)
{
    EXPECT_TRUE(p4 < p3);
    EXPECT_TRUE(p3 > p4);
    EXPECT_FALSE(p4 > p3);
    EXPECT_FALSE(p3 < p4);
    EXPECT_FALSE(p4 < p4);
    EXPECT_FALSE(p4 > p4);
    EXPECT_EQ(p4, p4);
    EXPECT_NE(p3, p4);
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
    
    EXPECT_TRUE(p1.hasDimension(x));
    EXPECT_FALSE(p1.hasDimension(a));
    EXPECT_FALSE(p2.hasDimension(x));
    EXPECT_TRUE(p2.hasDimension(a));

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
    
    EXPECT_TRUE(p3.haveSameDimensions(p4));
    EXPECT_FALSE(p2.haveSameDimensions(p4));
    
    EXPECT_TRUE(p1.hasDimensions(p1.variables()));
    EXPECT_TRUE(p2.hasDimensions(p2.variables()));
    EXPECT_TRUE(p3.hasDimensions(p3.variables()));
    EXPECT_TRUE(p4.hasDimensions(p4.variables()));
    EXPECT_FALSE(p1.hasDimensions(p4.variables()));
    EXPECT_FALSE(p4.hasDimensions(p1.variables()));
    EXPECT_TRUE(p3.hasDimensions(p4.variables()));
    EXPECT_TRUE(p4.hasDimensions(p3.variables()));
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
    
    Point<number_t> empty = p1.newEmpty();
    EXPECT_EQ(p1.dimension(), empty.dimension());
    EXPECT_TRUE(p1.haveSameDimensions(empty));
    EXPECT_EQ(0, empty[x]);

    Point<number_t>::rawCoordinateMap map;
    map.insert(std::make_pair(a, 123));
    map.insert(std::make_pair(b, 456));
    Point<number_t> p1(map);
    EXPECT_EQ(p1[a], FLOAT_T<number_t>(123));
    EXPECT_EQ(p1[b], FLOAT_T<number_t>(456));
}

TEST_F(PointTest, PolarCoordinates)
{
    std::vector<carl::FLOAT_T<number_t> > pc = p1.polarCoordinates(p1.origin(), false);
    FLOAT_T<number_t> expectedRes;
    expectedRes = 29;
    expectedRes.sqrt_assign();
    EXPECT_EQ(pc.at(0), expectedRes);
    
    pc = p2.polarCoordinates(p2.origin(), false);
    expectedRes = 113;
    expectedRes.sqrt_assign();
    EXPECT_EQ(pc.at(0), expectedRes);
    
    pc = p3.polarCoordinates(p3.origin(), false);
    expectedRes = 250;
    expectedRes.sqrt_assign();
    EXPECT_EQ(pc.at(0), expectedRes);
    
    pc = p4.polarCoordinates(p3, false);
}

TEST_F(PointTest, Neighbours)
{
    std::vector<Point<number_t> > neighbours = p1.getAllNeighborsForAFixedDimension(y);
    std::cout << "neighbours: ";
    for (auto n : neighbours) {
        std::cout << n << ", ";
    }
    std::cout << std::endl;
    p1.decrementInFixedDim(x);
    EXPECT_EQ(p1, neighbours[0]);
    
    p2[c] = FLOAT_T<number_t>(3);
    neighbours = p2.getAllNeighborsForAFixedDimension(a);
    std::cout << "neighbours: ";
    for (auto n : neighbours) {
        std::cout << n << ", ";
    }
    std::cout << std::endl;
    p2.decrementInFixedDim(b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p2) != neighbours.end());
    p2.decrementInFixedDim(c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p2) != neighbours.end());
    p2.incrementInFixedDim(b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p2) != neighbours.end());
    
    p3[a] = FLOAT_T<number_t>(2);
    p3[b] = FLOAT_T<number_t>(7);
    neighbours = p3.getAllNeighborsForAFixedDimension(a);
    std::cout << "neighbours: ";
    for (auto n : neighbours) {
        std::cout << n << ", ";
    }
    std::cout << std::endl;
    p3.decrementInFixedDim(b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.decrementInFixedDim(c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.incrementInFixedDim(b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.decrementInFixedDim(d);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.incrementInFixedDim(c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.decrementInFixedDim(b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
    p3.decrementInFixedDim(c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), p3) != neighbours.end());
}