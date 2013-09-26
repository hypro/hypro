#include "gtest/gtest.h"
#include "defines.h"
#include "datastructures/point.h"

using namespace hypro;

class PointTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		// p1
		std::vector<hypro_float_t> coordinates1(2);
		coordinates1.push_back(hypro_float_t(2));
		coordinates1.push_back(hypro_float_t(5));
		p1 = Point<hypro_float_t>(coordinates1);
		
		// p2
		std::vector<hypro_float_t> coordinates2(2);
		coordinates2.push_back(hypro_float_t(7));
		coordinates2.push_back(hypro_float_t(8));
		p2 = Point<hypro_float_t>(coordinates2);
		
		// p3
		std::vector<hypro_float_t> coordinates3(2);
		coordinates3.push_back(hypro_float_t(-9));
		coordinates3.push_back(hypro_float_t(13));
		p3 = Point<hypro_float_t>(coordinates3);
	}
	
	virtual void TearDown()
	{
	}

	Point<hypro_float_t> p1;
	Point<hypro_float_t> p2;
	Point<hypro_float_t> p3;
};

TEST_F(PointTest, FirstTest)
{ 
	ASSERT_EQ(p1[0], hypro_float_t(2));
    ASSERT_EQ(p1[1], hypro_float_t(5));
    ASSERT_EQ(p1.getCoordinate(0), hypro_float_t(2));
    ASSERT_EQ(p1.getCoordinate(1), hypro_float_t(5));
    ASSERT_EQ(p1.getDimension(), (unsigned) 2);
    
    p1.IncrementInFixedDim(1);
    ASSERT_EQ(p1[1], hypro_float_t(6));
    p1.IncrementInAllDim(hypro_float_t(3));
    ASSERT_EQ(p1[0], hypro_float_t(5));
    ASSERT_EQ(p1[1], hypro_float_t(9));
    p1.DecrementInFixedDim(1);
    ASSERT_EQ(p1[1], hypro_float_t(8));
    
    p1[0] = hypro_float_t(3);
    p1[1] = hypro_float_t(-1);
    ASSERT_EQ(p1[0], hypro_float_t(3));
    ASSERT_EQ(p1[1], hypro_float_t(-1));
    p1.setCoordinate(0, 4);
    p1.setCoordinate(1, 7);
    ASSERT_EQ(p1[0], hypro_float_t(4));
    ASSERT_EQ(p1[1], hypro_float_t(7));
}

TEST_F(PointTest, OperationTest)
{	
	ASSERT_FALSE(p1.move(p2));
	ASSERT_EQ(p1[0], hypro_float_t(9));
	ASSERT_EQ(p1[1], hypro_float_t(13));
	
	ASSERT_TRUE(p2.move(p3));
	ASSERT_EQ(p2[0], hypro_float_t(-2));
	ASSERT_EQ(p2[1], hypro_float_t(21));
}

TEST_F(PointTest, BooleanTest)
{
	ASSERT_TRUE(p1.isInBoundary(p2));
	ASSERT_FALSE(p2.isInBoundary(p1));
	
	p1[0] = hypro_float_t(3);
	p2[0] = hypro_float_t(3);
	ASSERT_TRUE(p1.CompareReducedDimension(p2, 1));
	ASSERT_FALSE(p1.CompareReducedDimension(p3, 1));
	ASSERT_TRUE(p1.haveEqualCoordinate(p2));
	ASSERT_FALSE(p1.haveEqualCoordinate(p3));
	
	ASSERT_LT(p1, p2);
	ASSERT_GT(p2, p3);
	
	p1[1] = hypro_float_t(6);
	p2[1] = hypro_float_t(6);
	ASSERT_EQ(p1, p2);
	ASSERT_NE(p1, p3);
}

TEST(Point, Constructor)
{ 
    Point<hypro_float_t> p = Point<hypro_float_t>();
    ASSERT_EQ(p.getDimension(), (unsigned) 2);
    
    p = Point<hypro_float_t>(5);
    ASSERT_EQ(p.getDimension(), (unsigned) 5);
    
    hypro_float_t initialValue(4);
    p = Point<hypro_float_t>(7, initialValue);
    ASSERT_EQ(p.getDimension(), (unsigned) 7);
    ASSERT_EQ(p[0], hypro_float_t(7));
    ASSERT_EQ(p[6], hypro_float_t(7));
    
    Point<hypro_float_t> pCopy = Point<hypro_float_t>(p);
    ASSERT_EQ(p, pCopy);
}