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
#include <carl/core/VariablePool.h>
#include "../../lib/datastructures/Point.h"
#include "../../lib/representations/conversion/Converter.h"

using namespace hypro;
using namespace carl;

template<typename Number>
class BoxTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        std::vector<carl::Interval<Number> > boundaries1;
        boundaries1.push_back(carl::Interval<Number>(2,6));
        boundaries1.push_back(carl::Interval<Number>(1,3));
        box1 = hypro::Box<Number>(boundaries1);

        std::vector<carl::Interval<Number> > boundaries2;
        boundaries2.push_back(carl::Interval<Number>(-1,6));
        boundaries2.push_back(carl::Interval<Number>(4,7));
        box2 = hypro::Box<Number>(boundaries2);
    }

    virtual void TearDown()
    {
    }

    hypro::Box<Number> box1;
    hypro::Box<Number> box2;
    hypro::Box<Number> box3;
};

TYPED_TEST(BoxTest, Constructor)
{
    hypro::Box<TypeParam> aBox = hypro::Box<TypeParam>();
	hypro::Box<TypeParam> bBox = aBox;
	hypro::Box<TypeParam> cBox = hypro::Box<TypeParam>(aBox);
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

	hypro::Box<TypeParam> dBox(points);

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

    EXPECT_EQ(Point<TypeParam>({6,3}), this->box1.max());
    EXPECT_EQ(Point<TypeParam>({2,1}), this->box1.min());

    EXPECT_EQ(this->box1, this->box1);
    EXPECT_EQ(this->box2, this->box2);
    EXPECT_EQ(this->box3, this->box3);
    EXPECT_NE(this->box1, this->box2);
    EXPECT_NE(this->box2, this->box3);
    EXPECT_NE(this->box3, this->box1);

    hypro::Box<TypeParam> emptyBox = hypro::Box<TypeParam>::Empty();
    hypro::Box<TypeParam> universalBox;
    EXPECT_FALSE(this->box1.empty());
    EXPECT_TRUE(emptyBox.empty());
    EXPECT_FALSE(universalBox.empty());
}

TYPED_TEST(BoxTest, Insertion)
{
    std::vector<carl::Interval<TypeParam>> tmp;
    this->box1.insert(carl::Interval<TypeParam>(3,9));
    EXPECT_EQ(true, this->box1.dimension() == 3);

    EXPECT_EQ(3, this->box1.interval(2).lower());
    EXPECT_EQ(9, this->box1.interval(2).upper());

    this->box1.insert(carl::Interval<TypeParam>(4,5));
    EXPECT_EQ(true, this->box1.dimension() == 4);

    EXPECT_EQ(4, this->box1.interval(3).lower());
    EXPECT_EQ(5, this->box1.interval(3).upper());
}

TYPED_TEST(BoxTest, Vertices) {
	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(3,5);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(1,3);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(2,5);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);

	hypro::Box<TypeParam> b1(intervals1);

	std::vector<Point<TypeParam>> corners = b1.vertices();
	EXPECT_EQ((unsigned) 8, corners.size());

	EXPECT_EQ(true, std::find(corners.begin(), corners.end(),Point<TypeParam>({3,1,2})) != corners.end());
	EXPECT_EQ(true, std::find(corners.begin(), corners.end(),Point<TypeParam>({3,1,5})) != corners.end());
	EXPECT_EQ(true, std::find(corners.begin(), corners.end(),Point<TypeParam>({3,3,2})) != corners.end());
	EXPECT_EQ(true, std::find(corners.begin(), corners.end(),Point<TypeParam>({3,3,5})) != corners.end());
	EXPECT_EQ(true, std::find(corners.begin(), corners.end(),Point<TypeParam>({5,1,2})) != corners.end());
	EXPECT_EQ(true, std::find(corners.begin(), corners.end(),Point<TypeParam>({5,1,5})) != corners.end());
	EXPECT_EQ(true, std::find(corners.begin(), corners.end(),Point<TypeParam>({5,3,2})) != corners.end());
	EXPECT_EQ(true, std::find(corners.begin(), corners.end(),Point<TypeParam>({5,3,5})) != corners.end());
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

	hypro::Box<TypeParam> b1(intervals1);

	carl::Interval<TypeParam> a = carl::Interval<TypeParam>(-1,3);
	carl::Interval<TypeParam> b = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> c = carl::Interval<TypeParam>(-3,6);
	std::vector<carl::Interval<TypeParam>> intervals2;
	intervals2.push_back(a);
	intervals2.push_back(b);
	intervals2.push_back(c);

	hypro::Box<TypeParam> b2(intervals2);

	//std::cout << "Union of " << b1 << " and " << b2 << std::endl;

	hypro::Box<TypeParam> result = b1.unite(b2);

	//std::cout << "Result: " << result << std::endl;

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

	hypro::Box<TypeParam> b1(intervals1);

	// rotation
	TypeParam angle = 90;

	matrix_t<TypeParam> rotX = matrix_t<TypeParam>::Zero(3,3);
	rotX(0,0) = 1;
	rotX(1,1) = carl::cos(angle);
	rotX(1,2) = -carl::sin(angle);
	rotX(2,1) = carl::sin(angle);
	rotX(2,2) = carl::cos(angle);


	matrix_t<TypeParam> rotY = matrix_t<TypeParam>::Zero(3,3);
	rotY(0,0) = carl::cos(angle);
	rotY(0,2) = carl::sin(angle);
	rotY(1,1) = 1;
	rotY(2,0) = -carl::sin(angle);
	rotY(2,2) = carl::cos(angle);

	matrix_t<TypeParam> rotZ = matrix_t<TypeParam>::Zero(3,3);
	rotZ(0,0) = carl::cos(angle);
	rotZ(0,1) = -carl::sin(angle);
	rotZ(1,0) = carl::sin(angle);
	rotZ(1,1) = carl::cos(angle);
	rotZ(2,2) = 1;


	// result
	hypro::Box<TypeParam> resX = b1.linearTransformation(rotX, vector_t<TypeParam>::Zero(rotX.rows()));
	hypro::Box<TypeParam> resY = b1.linearTransformation(rotY, vector_t<TypeParam>::Zero(rotY.rows()));
	hypro::Box<TypeParam> resZ = b1.linearTransformation(rotZ, vector_t<TypeParam>::Zero(rotZ.rows()));


	std::vector<Point<TypeParam>> cornersX = resX.vertices();

	for(const auto& vertex : cornersX) {
		std::cout << vertex << ", ";
	}
	std::cout << std::endl;

	std::vector<Point<TypeParam>> originalCorners = b1.vertices();
	std::vector<Point<TypeParam>> newCorners;
	for(auto& point : originalCorners) {
		newCorners.push_back(Point<TypeParam>(rotX*point.rawCoordinates()));
	}
	EXPECT_EQ(resX, hypro::Box<TypeParam>(newCorners));


	newCorners.clear();
	std::vector<Point<TypeParam>> cornersY = resY.vertices();
	for(auto& point : originalCorners) {
		newCorners.push_back(Point<TypeParam>(rotY*point.rawCoordinates()));
	}
	EXPECT_EQ(resY, hypro::Box<TypeParam>(newCorners));

	newCorners.clear();
	std::vector<Point<TypeParam>> cornersZ = resZ.vertices();
	for(auto& point : originalCorners) {
		newCorners.push_back(Point<TypeParam>(rotZ*point.rawCoordinates()));
	}
	EXPECT_EQ(resZ, hypro::Box<TypeParam>(newCorners));
}

TYPED_TEST(BoxTest, MinkowskiSum)
{
    hypro::Box<TypeParam> result;
    result = this->box1.minkowskiSum(this->box2);
    EXPECT_EQ(1 , result.interval(0).lower());
    EXPECT_EQ(12 , result.interval(0).upper());
    EXPECT_EQ(5 , result.interval(1).lower());
    EXPECT_EQ(10 , result.interval(1).upper());

	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(-2,2);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(-4,-2);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);

	hypro::Box<TypeParam> b1(intervals1);

	carl::Interval<TypeParam> a = carl::Interval<TypeParam>(1);
	carl::Interval<TypeParam> b = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> c = carl::Interval<TypeParam>(-2,3);
	std::vector<carl::Interval<TypeParam>> intervals2;
	intervals2.push_back(a);
	intervals2.push_back(b);
	intervals2.push_back(c);

	hypro::Box<TypeParam> b2(intervals2);

	hypro::Box<TypeParam> res = b1.minkowskiSum(b2);
	std::vector<Point<TypeParam>> corners = res.vertices();

	EXPECT_TRUE(std::find( corners.begin(), corners.end(), Point<TypeParam>({-1,4,-6}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), Point<TypeParam>({-1,4,1}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), Point<TypeParam>({-1,8,-6}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), Point<TypeParam>({-1,8,1}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), Point<TypeParam>({3,4,-6}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), Point<TypeParam>({3,4,1}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), Point<TypeParam>({3,8,-6}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), Point<TypeParam>({3,8,1}) ) != corners.end());

}

TYPED_TEST(BoxTest, MinkowskiDecomposition)
{
	hypro::Box<TypeParam> result;
	result = this->box2.minkowskiDecomposition(this->box1);
	EXPECT_EQ(-3 , result.interval(0).lower());
	EXPECT_EQ(0 , result.interval(0).upper());
	EXPECT_EQ(3 , result.interval(1).lower());
	EXPECT_EQ(4 , result.interval(1).upper());

	result = this->box2.minkowskiDecomposition(this->box2);
	EXPECT_EQ(0 , result.interval(0).lower());
	EXPECT_EQ(0 , result.interval(0).upper());
	EXPECT_EQ(0 , result.interval(1).lower());
	EXPECT_EQ(0 , result.interval(1).upper());

}

TYPED_TEST(BoxTest, Intersection)
{
    hypro::Box<TypeParam> result;
    result = this->box1.intersect(this->box2);

    EXPECT_TRUE(result.empty());

	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(-2,2);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(-4,-2);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);

	hypro::Box<TypeParam> b1(intervals1);

	carl::Interval<TypeParam> a = carl::Interval<TypeParam>(1);
	carl::Interval<TypeParam> b = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> c = carl::Interval<TypeParam>(-2,3);
	std::vector<carl::Interval<TypeParam>> intervals2;
	intervals2.push_back(a);
	intervals2.push_back(b);
	intervals2.push_back(c);

	hypro::Box<TypeParam> b2(intervals2);

	hypro::Box<TypeParam> res = b1.intersect(b2);
	carl::Interval<TypeParam> i = x.intersect(a);
	carl::Interval<TypeParam> j = y.intersect(b);
	carl::Interval<TypeParam> k = z.intersect(c);
	std::vector<carl::Interval<TypeParam>> intervals;
	intervals.push_back(i);
	intervals.push_back(j);
	intervals.push_back(k);

	EXPECT_EQ(hypro::Box<TypeParam>(intervals), res);

	hypro::Box<TypeParam> empt1 = this->box1.intersect(hypro::Box<TypeParam>::Empty());
	EXPECT_TRUE(empt1.empty());

	hypro::Box<TypeParam> empt2 = this->box1.intersect(hypro::Box<TypeParam>::Empty(this->box1.dimension()));
	EXPECT_TRUE(empt2.empty());

	hypro::Box<TypeParam> reduced = this->box1.intersect(hypro::Box<TypeParam>(carl::Interval<TypeParam>(3,4)));
	EXPECT_EQ(reduced, hypro::Box<TypeParam>(carl::Interval<TypeParam>(3,4)));
}

TYPED_TEST(BoxTest, IntersectionHalfspace)
{
	hypro::Box<TypeParam> res1 = this->box1.intersectHalfspace(hypro::Halfspace<TypeParam>({1,1},4));
	hypro::Box<TypeParam> res2 = this->box1.intersectHalfspace(hypro::Halfspace<TypeParam>({1,1},5));
	hypro::Box<TypeParam> res3 = this->box1.intersectHalfspace(hypro::Halfspace<TypeParam>({1,1},6));
	hypro::Box<TypeParam> res4 = this->box1.intersectHalfspace(hypro::Halfspace<TypeParam>({1,1},9));
	hypro::Box<TypeParam> res5 = this->box1.intersectHalfspace(hypro::Halfspace<TypeParam>({1,1},10));

	std::vector<carl::Interval<TypeParam>> i1;
	std::vector<carl::Interval<TypeParam>> i2;
	std::vector<carl::Interval<TypeParam>> i3;
	std::vector<carl::Interval<TypeParam>> i4;
	std::vector<carl::Interval<TypeParam>> i5;

	i1.push_back(carl::Interval<TypeParam>(2,3));
	i1.push_back(carl::Interval<TypeParam>(1,2));
	EXPECT_EQ(res1, hypro::Box<TypeParam>(i1));

	i2.push_back(carl::Interval<TypeParam>(2,4));
	i2.push_back(carl::Interval<TypeParam>(1,3));
	EXPECT_EQ(res2, hypro::Box<TypeParam>(i2));

	i3.push_back(carl::Interval<TypeParam>(2,5));
	i3.push_back(carl::Interval<TypeParam>(1,3));
	EXPECT_EQ(res3, hypro::Box<TypeParam>(i3));

	i4.push_back(carl::Interval<TypeParam>(2,6));
	i4.push_back(carl::Interval<TypeParam>(1,3));
	EXPECT_EQ(res4, hypro::Box<TypeParam>(i4));

	i5.push_back(carl::Interval<TypeParam>(2,6));
	i5.push_back(carl::Interval<TypeParam>(1,3));
	EXPECT_EQ(res5, hypro::Box<TypeParam>(i5));
}

TYPED_TEST(BoxTest, Membership)
{
    Point<TypeParam> p({4,2});
    EXPECT_TRUE(this->box1.contains(p));
}
