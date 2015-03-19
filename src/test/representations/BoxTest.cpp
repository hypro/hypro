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
        box1 = Box<Number>(boundaries1);
        
        std::map<const carl::Variable, carl::Interval<Number> > boundaries2;
        boundaries2.insert(std::make_pair(x, Interval<Number>(-1,6)));
        boundaries2.insert(std::make_pair(y, Interval<Number>(4,7)));
        box2 = Box<Number>(boundaries2);
    }
	
    virtual void TearDown()
    {
    }
	
    hypro::VariablePool& pool = hypro::VariablePool::getInstance();
    carl::Variable x;
    carl::Variable y;

    Box<Number> box1;
    Box<Number> box2;
    Box<Number> box3;
};

TYPED_TEST(BoxTest, Constructor)
{
    Box<TypeParam> aBox = Box<TypeParam>();
	Box<TypeParam> bBox = aBox;
	Box<TypeParam> cBox = Box<TypeParam>(aBox);
	EXPECT_EQ(aBox, bBox);
	EXPECT_EQ(aBox, cBox);
	EXPECT_EQ(bBox, cBox);
	
	std::set<Point<TypeParam>> points;
	Point<TypeParam> p1 = Point<TypeParam>({1,2});
	Point<TypeParam> p2 = Point<TypeParam>({-3,4});
	Point<TypeParam> p3 = Point<TypeParam>({0,3});
	points.insert(p1);
	points.insert(p2);
	points.insert(p3);

	Box<TypeParam> dBox(points);
	
	EXPECT_EQ(TypeParam(-3), dBox.min().at(0));
	EXPECT_EQ(TypeParam(2), dBox.min().at(1));
	EXPECT_EQ(TypeParam(1), dBox.max().at(0));
	EXPECT_EQ(TypeParam(4), dBox.max().at(1));
	EXPECT_EQ(true, dBox.contains(Point<TypeParam>({0,3})));
    SUCCEED();
}

TYPED_TEST(BoxTest, Access)
{
    std::vector<carl::Interval<TypeParam>> tmp = this->box1.boundaries();
    EXPECT_EQ(2, tmp[0].lower());
    EXPECT_EQ(6, tmp[0].upper());
    EXPECT_EQ(1, tmp[1].lower());
    EXPECT_EQ(3, tmp[1].upper());
    
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
    std::vector<carl::Interval<TypeParam>> tmp;
    Variable z = this->pool.newCarlVariable();
    this->box1.insert(std::make_pair(z, Interval<TypeParam>(3,9)));
    EXPECT_EQ(true, this->box1.hasDimension(z));
    
    EXPECT_EQ(3, this->box1.interval(z).lower());
    EXPECT_EQ(9, this->box1.interval(z).upper());
    
    Variable w = this->pool.newCarlVariable();
    this->box1.insert(std::make_pair(w, Interval<TypeParam>(4,5)));
    EXPECT_EQ(true, this->box1.hasDimension(w));
    
    EXPECT_EQ(4, this->box1.interval(w).lower());
    EXPECT_EQ(5, this->box1.interval(w).upper());
}

TYPED_TEST(BoxTest, Corners) {
	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(3,5);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(1,3);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(2,5);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);
	
	Box<TypeParam> b1(intervals1);
	
	std::set<Point<TypeParam>> corners = b1.corners();
	EXPECT_EQ((unsigned) 8, corners.size());
	
	EXPECT_EQ(true, corners.find(Point<TypeParam>({3,1,2})) != corners.end());
	EXPECT_EQ(true, corners.find(Point<TypeParam>({3,1,5})) != corners.end());
	EXPECT_EQ(true, corners.find(Point<TypeParam>({3,3,2})) != corners.end());
	EXPECT_EQ(true, corners.find(Point<TypeParam>({3,3,5})) != corners.end());
	EXPECT_EQ(true, corners.find(Point<TypeParam>({5,1,2})) != corners.end());
	EXPECT_EQ(true, corners.find(Point<TypeParam>({5,1,5})) != corners.end());
	EXPECT_EQ(true, corners.find(Point<TypeParam>({5,3,2})) != corners.end());
	EXPECT_EQ(true, corners.find(Point<TypeParam>({5,3,5})) != corners.end());
}

TYPED_TEST(BoxTest, Union)
{
	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(3,5);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(1,3);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(2,5);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);
	
	Box<TypeParam> b1(intervals1);
	
	carl::Interval<TypeParam> a = carl::Interval<TypeParam>(-1,3);
	carl::Interval<TypeParam> b = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> c = carl::Interval<TypeParam>(-3,6);
	std::vector<carl::Interval<TypeParam>> intervals2;
	intervals2.push_back(a);
	intervals2.push_back(b);
	intervals2.push_back(c);
	
	Box<TypeParam> b2(intervals2);
	
	Box<TypeParam> result = b1.unite(b2);
	
	EXPECT_EQ(TypeParam(-1), result.min().at(0));
	EXPECT_EQ(TypeParam(1), result.min().at(1));
	EXPECT_EQ(TypeParam(-3), result.min().at(2));
	EXPECT_EQ(TypeParam(5), result.max().at(0));
	EXPECT_EQ(TypeParam(4), result.max().at(1));
	EXPECT_EQ(TypeParam(6), result.max().at(2));
}

TYPED_TEST(BoxTest, LinearTransformation)
{
	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(-2,2);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(-4,-2);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);
	
	Box<TypeParam> b1(intervals1);
	
	// rotation
	TypeParam angle = 90;
	matrix_t<TypeParam> rotX = matrix_t<TypeParam>::Zero(3,3);
	rotX(0,0) = 1;
	rotX(1,1) = cos(angle);
	rotX(1,2) = -sin(angle);
	rotX(2,1) = sin(angle);
	rotX(2,2) = cos(angle);
	
	matrix_t<TypeParam> rotY = matrix_t<TypeParam>::Zero(3,3);
	rotY(0,0) = cos(angle);
	rotY(0,2) = sin(angle);
	rotY(1,1) = 1;
	rotY(2,0) = -sin(angle);
	rotY(2,2) = cos(angle);
	
	matrix_t<TypeParam> rotZ = matrix_t<TypeParam>::Zero(3,3);
	rotZ(0,0) = cos(angle);
	rotZ(0,1) = -sin(angle);
	rotZ(1,0) = sin(angle);
	rotZ(1,1) = cos(angle);
	rotZ(2,2) = 1;
	
	// result
	Box<TypeParam> resX = b1.linearTransformation(rotX);
	Box<TypeParam> resY = b1.linearTransformation(rotY);
	Box<TypeParam> resZ = b1.linearTransformation(rotZ);
	
	
	std::set<Point<TypeParam>> cornersX = resX.corners();
	std::set<Point<TypeParam>> originalCorners = b1.corners();
	std::set<Point<TypeParam>> newCorners;
	for(auto& point : originalCorners) {
		newCorners.insert(Point<TypeParam>(rotX*point.rawCoordinates()));
	}
	EXPECT_EQ(resX, Box<TypeParam>(newCorners));
	
	newCorners.clear();
	std::set<Point<TypeParam>> cornersY = resY.corners();
	for(auto& point : originalCorners) {
		newCorners.insert(Point<TypeParam>(rotY*point.rawCoordinates()));
	}
	EXPECT_EQ(resY, Box<TypeParam>(newCorners));
	
	newCorners.clear();
	std::set<Point<TypeParam>> cornersZ = resZ.corners();
	for(auto& point : originalCorners) {
		newCorners.insert(Point<TypeParam>(rotZ*point.rawCoordinates()));
	}
	EXPECT_EQ(resZ, Box<TypeParam>(newCorners));
	
}

TYPED_TEST(BoxTest, MinkowskiSum)
{
    Box<TypeParam> result;
    result = this->box1.minkowskiSum(this->box2);
    EXPECT_EQ(1 , result.interval(this->x).lower());
    EXPECT_EQ(12 , result.interval(this->x).upper());
    EXPECT_EQ(5 , result.interval(this->y).lower());
    EXPECT_EQ(10 , result.interval(this->y).upper());
	
	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(-2,2);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(-4,-2);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);
	
	Box<TypeParam> b1(intervals1);
	
	carl::Interval<TypeParam> a = carl::Interval<TypeParam>(1);
	carl::Interval<TypeParam> b = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> c = carl::Interval<TypeParam>(-2,3);
	std::vector<carl::Interval<TypeParam>> intervals2;
	intervals2.push_back(a);
	intervals2.push_back(b);
	intervals2.push_back(c);
	
	Box<TypeParam> b2(intervals2);
	
	Box<TypeParam> res = b1.minkowskiSum(b2);
	std::set<Point<TypeParam>> corners = res.corners();
	
	EXPECT_TRUE(corners.find( Point<TypeParam>({-1,4,-6}) ) != corners.end());
	EXPECT_TRUE(corners.find( Point<TypeParam>({-1,4,1}) ) != corners.end());
	EXPECT_TRUE(corners.find( Point<TypeParam>({-1,8,-6}) ) != corners.end());
	EXPECT_TRUE(corners.find( Point<TypeParam>({-1,8,1}) ) != corners.end());
	EXPECT_TRUE(corners.find( Point<TypeParam>({3,4,-6}) ) != corners.end());
	EXPECT_TRUE(corners.find( Point<TypeParam>({3,4,1}) ) != corners.end());
	EXPECT_TRUE(corners.find( Point<TypeParam>({3,8,-6}) ) != corners.end());
	EXPECT_TRUE(corners.find( Point<TypeParam>({3,8,1}) ) != corners.end());
	
}

TYPED_TEST(BoxTest, Intersection)
{
    Box<TypeParam> result;
    result = this->box1.intersect(this->box2);
    EXPECT_TRUE(result.isEmpty());
	
	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(-2,2);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(-4,-2);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);
	
	Box<TypeParam> b1(intervals1);
	
	carl::Interval<TypeParam> a = carl::Interval<TypeParam>(1);
	carl::Interval<TypeParam> b = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> c = carl::Interval<TypeParam>(-2,3);
	std::vector<carl::Interval<TypeParam>> intervals2;
	intervals2.push_back(a);
	intervals2.push_back(b);
	intervals2.push_back(c);
	
	Box<TypeParam> b2(intervals2);
	
	Box<TypeParam> res = b1.intersect(b2);
	carl::Interval<TypeParam> i = x.intersect(a);
	carl::Interval<TypeParam> j = y.intersect(b);
	carl::Interval<TypeParam> k = z.intersect(c);
	std::vector<carl::Interval<TypeParam>> intervals;
	intervals.push_back(i);
	intervals.push_back(j);
	intervals.push_back(k);
	
	EXPECT_EQ(Box<TypeParam>(intervals), res);
	
}

TYPED_TEST(BoxTest, Membership)
{
    Point<TypeParam> p;
    p.setCoordinate(this->x, 4);
    p.setCoordinate(this->y, 2);
    EXPECT_TRUE(this->box1.contains(p));
}
