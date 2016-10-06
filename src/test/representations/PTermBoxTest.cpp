/**
 * A testfile for boxes, please extend!
 *
 * @file    PTermBoxTest.cpp
 * @covers  PTermBox
 *
 * @author  Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author 	YOUR STORY!
 *
 * @since	2015-10-20
 * @version 2015-10-20
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../hypro/datastructures/Point.h"
#include "../../hypro/representations/PTermBox/PTermBox.h"

template<typename Number>
class PTermBoxTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        std::vector<carl::Interval<Number> > boundaries1;
        boundaries1.push_back(carl::Interval<Number>(2,6));
        boundaries1.push_back(carl::Interval<Number>(1,3));
        box1 = hypro::PTermBox<Number>(boundaries1);

        std::vector<carl::Interval<Number> > boundaries2;
        boundaries2.push_back(carl::Interval<Number>(-1,6));
        boundaries2.push_back(carl::Interval<Number>(4,7));
        box2 = hypro::PTermBox<Number>(boundaries2);

        std::vector<hypro::Point<Number>> points1;
        points1.push_back(hypro::Point<Number>({1,1,1}));
        points1.push_back(hypro::Point<Number>({3,4,5}));
        box3 = hypro::PTermBox<Number>(points1);
    }

    virtual void TearDown()
    {
    }

    hypro::PTermBox<Number> box1;
    hypro::PTermBox<Number> box2;
    hypro::PTermBox<Number> box3;
};

TYPED_TEST(PTermBoxTest, Constructor)
{
    hypro::PTermBox<TypeParam> aBox = hypro::PTermBox<TypeParam>();
	hypro::PTermBox<TypeParam> bBox = aBox;
	hypro::PTermBox<TypeParam> cBox = hypro::PTermBox<TypeParam>(aBox);
	EXPECT_EQ(aBox, bBox);
	EXPECT_EQ(aBox, cBox);
	EXPECT_EQ(bBox, cBox);

	std::set<hypro::Point<TypeParam>> points;
	hypro::Point<TypeParam> p1 = hypro::Point<TypeParam>({1,2});
	hypro::Point<TypeParam> p2 = hypro::Point<TypeParam>({-3,4});
	hypro::Point<TypeParam> p3 = hypro::Point<TypeParam>({0,3});
	points.insert(p1);
	points.insert(p2);
	points.insert(p3);

	hypro::PTermBox<TypeParam> dBox(points);


	if(dBox.min().dimension() > 0) {
		EXPECT_EQ(TypeParam(-3), dBox.min().at(0));
		EXPECT_EQ(TypeParam(2), dBox.min().at(1));
		EXPECT_EQ(TypeParam(1), dBox.max().at(0));
		EXPECT_EQ(TypeParam(4), dBox.max().at(1));
	} else {
		FAIL();
	}



	EXPECT_EQ(true, dBox.contains(hypro::Point<TypeParam>({0,3})));
    SUCCEED();
}

TYPED_TEST(PTermBoxTest, Access)
{
    std::vector<carl::Interval<TypeParam>> tmp = this->box1.boundaries();
    if(tmp.size() > 0) {
    	EXPECT_EQ(2, tmp[0].lower());
	    EXPECT_EQ(6, tmp[0].upper());
	    EXPECT_EQ(1, tmp[1].lower());
	    EXPECT_EQ(3, tmp[1].upper());
    } else {
    	FAIL();
    }


    EXPECT_EQ((unsigned) 2, this->box1.dimension());
    EXPECT_EQ((unsigned) 2, this->box2.dimension());
    EXPECT_EQ((unsigned) 0, this->box3.dimension());

    EXPECT_EQ(this->box1, this->box1);
    EXPECT_EQ(this->box2, this->box2);
    EXPECT_EQ(this->box3, this->box3);
    EXPECT_NE(this->box1, this->box2);
    EXPECT_NE(this->box2, this->box3);
    EXPECT_NE(this->box3, this->box1);

    hypro::PTermBox<TypeParam> emptyBox = hypro::PTermBox<TypeParam>::Empty();
    hypro::PTermBox<TypeParam> universalBox;
    EXPECT_FALSE(this->box1.empty());
    EXPECT_TRUE(emptyBox.empty());
    EXPECT_FALSE(universalBox.empty());
}

TYPED_TEST(PTermBoxTest, Insertion)
{
    std::vector<carl::Interval<TypeParam>> tmp;
    this->box1.insert(carl::Interval<TypeParam>(3,9));

    if(this->box1.dimension() > 0) {
    	EXPECT_EQ(3, this->box1.boundaries().at(2).lower());
    	EXPECT_EQ(9, this->box1.boundaries().at(2).upper());
    } else {
    	FAIL();
    }

    this->box1.insert(carl::Interval<TypeParam>(4,5));

    if(this->box1.dimension() > 0) {
    	EXPECT_EQ(4, this->box1.boundaries().at(3).lower());
    	EXPECT_EQ(5, this->box1.boundaries().at(3).upper());
    } else {
    	FAIL();
    }
}

TYPED_TEST(PTermBoxTest, Vertices) {
	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(3,5);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(1,3);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(2,5);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);

	hypro::PTermBox<TypeParam> b1(intervals1);

	std::vector<hypro::Point<TypeParam>> b1Vertices = b1.vertices();
	EXPECT_EQ((unsigned) 8, b1Vertices.size());

	EXPECT_EQ(true, std::find(b1Vertices.begin(), b1Vertices.end(),hypro::Point<TypeParam>({3,1,2})) != b1Vertices.end());
	EXPECT_EQ(true, std::find(b1Vertices.begin(), b1Vertices.end(),hypro::Point<TypeParam>({3,1,5})) != b1Vertices.end());
	EXPECT_EQ(true, std::find(b1Vertices.begin(), b1Vertices.end(),hypro::Point<TypeParam>({3,3,2})) != b1Vertices.end());
	EXPECT_EQ(true, std::find(b1Vertices.begin(), b1Vertices.end(),hypro::Point<TypeParam>({3,3,5})) != b1Vertices.end());
	EXPECT_EQ(true, std::find(b1Vertices.begin(), b1Vertices.end(),hypro::Point<TypeParam>({5,1,2})) != b1Vertices.end());
	EXPECT_EQ(true, std::find(b1Vertices.begin(), b1Vertices.end(),hypro::Point<TypeParam>({5,1,5})) != b1Vertices.end());
	EXPECT_EQ(true, std::find(b1Vertices.begin(), b1Vertices.end(),hypro::Point<TypeParam>({5,3,2})) != b1Vertices.end());
	EXPECT_EQ(true, std::find(b1Vertices.begin(), b1Vertices.end(),hypro::Point<TypeParam>({5,3,5})) != b1Vertices.end());
}

TYPED_TEST(PTermBoxTest, Union)
{
	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(3,5);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(1,3);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(2,5);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);

	hypro::PTermBox<TypeParam> b1(intervals1);

	carl::Interval<TypeParam> a = carl::Interval<TypeParam>(-1,3);
	carl::Interval<TypeParam> b = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> c = carl::Interval<TypeParam>(-3,6);
	std::vector<carl::Interval<TypeParam>> intervals2;
	intervals2.push_back(a);
	intervals2.push_back(b);
	intervals2.push_back(c);

	hypro::PTermBox<TypeParam> b2(intervals2);

	hypro::PTermBox<TypeParam> result = b1.unite(b2);

	if(result.min().dimension() > 0) {
		EXPECT_EQ(TypeParam(-1), result.min().at(0));
		EXPECT_EQ(TypeParam(1), result.min().at(1));
		EXPECT_EQ(TypeParam(-3), result.min().at(2));
		EXPECT_EQ(TypeParam(5), result.max().at(0));
		EXPECT_EQ(TypeParam(4), result.max().at(1));
		EXPECT_EQ(TypeParam(6), result.max().at(2));
	} else {
		FAIL();
	}
}

TYPED_TEST(PTermBoxTest, LinearTransformation)
{
	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(-2,2);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(-4,-2);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);

	hypro::PTermBox<TypeParam> b1(intervals1);

	// rotation
	TypeParam angle = 45;
	hypro::matrix_t<TypeParam> rotX = hypro::matrix_t<TypeParam>::Zero(3,3);
	rotX(0,0) = 1;
	rotX(1,1) = carl::cos(angle);
	rotX(1,2) = -carl::sin(angle);
	rotX(2,1) = carl::sin(angle);
	rotX(2,2) = carl::cos(angle);


	hypro::matrix_t<TypeParam> rotY = hypro::matrix_t<TypeParam>::Zero(3,3);
	rotY(0,0) = carl::cos(angle);
	rotY(0,2) = carl::sin(angle);
	rotY(1,1) = 1;
	rotY(2,0) = -carl::sin(angle);
	rotY(2,2) = carl::cos(angle);

	hypro::matrix_t<TypeParam> rotZ = hypro::matrix_t<TypeParam>::Zero(3,3);
	rotZ(0,0) = carl::cos(angle);
	rotZ(0,1) = -carl::sin(angle);
	rotZ(1,0) = carl::sin(angle);
	rotZ(1,1) = carl::cos(angle);
	rotZ(2,2) = 1;


	// result
	hypro::PTermBox<TypeParam> resX = b1.linearTransformation(rotX, hypro::vector_t<TypeParam>::Zero(rotX.rows()));
	hypro::PTermBox<TypeParam> resY = b1.linearTransformation(rotY, hypro::vector_t<TypeParam>::Zero(rotY.rows()));
	hypro::PTermBox<TypeParam> resZ = b1.linearTransformation(rotZ, hypro::vector_t<TypeParam>::Zero(rotZ.rows()));


	std::vector<hypro::Point<TypeParam>> cornersX = resX.vertices();
	std::vector<hypro::Point<TypeParam>> originalCorners = b1.vertices();
	std::vector<hypro::Point<TypeParam>> newCorners;
	for(auto& p : originalCorners) {
		newCorners.push_back(hypro::Point<TypeParam>(rotX*p.rawCoordinates()));
	}
	EXPECT_EQ(resX, hypro::PTermBox<TypeParam>(newCorners));

	newCorners.clear();
	std::vector<hypro::Point<TypeParam>> cornersY = resY.vertices();
	for(auto& p : originalCorners) {
		newCorners.push_back(hypro::Point<TypeParam>(rotY*p.rawCoordinates()));
	}
	EXPECT_EQ(resY, hypro::PTermBox<TypeParam>(newCorners));

	newCorners.clear();
	std::vector<hypro::Point<TypeParam>> cornersZ = resZ.vertices();
	for(auto& p : originalCorners) {
		newCorners.push_back(hypro::Point<TypeParam>(rotZ*p.rawCoordinates()));
	}
	EXPECT_EQ(resZ, hypro::PTermBox<TypeParam>(newCorners));
}

TYPED_TEST(PTermBoxTest, MinkowskiSum)
{
    hypro::PTermBox<TypeParam> result;
    result = this->box1.minkowskiSum(this->box2);
    if(result.dimension() > 0) {
    	EXPECT_EQ(1 , result.boundaries().at(0).lower());
	    EXPECT_EQ(12 , result.boundaries().at(0).upper());
	    EXPECT_EQ(5 , result.boundaries().at(1).lower());
	    EXPECT_EQ(10 , result.boundaries().at(1).upper());
    } else {
    	FAIL();
    }

	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(-2,2);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(-4,-2);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);

	hypro::PTermBox<TypeParam> b1(intervals1);

	carl::Interval<TypeParam> a = carl::Interval<TypeParam>(1);
	carl::Interval<TypeParam> b = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> c = carl::Interval<TypeParam>(-2,3);
	std::vector<carl::Interval<TypeParam>> intervals2;
	intervals2.push_back(a);
	intervals2.push_back(b);
	intervals2.push_back(c);

	hypro::PTermBox<TypeParam> b2(intervals2);

	hypro::PTermBox<TypeParam> res = b1.minkowskiSum(b2);
	std::vector<hypro::Point<TypeParam>> corners = res.vertices();

	EXPECT_TRUE(std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>({-1,4,-6}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>({-1,4,1}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>({-1,8,-6}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>({-1,8,1}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>({3,4,-6}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>({3,4,1}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>({3,8,-6}) ) != corners.end());
	EXPECT_TRUE(std::find( corners.begin(), corners.end(), hypro::Point<TypeParam>({3,8,1}) ) != corners.end());

}

TYPED_TEST(PTermBoxTest, Intersection)
{
    hypro::PTermBox<TypeParam> result;
    result = this->box1.intersect(this->box2);
    EXPECT_TRUE(result.empty());

	carl::Interval<TypeParam> x = carl::Interval<TypeParam>(-2,2);
	carl::Interval<TypeParam> y = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> z = carl::Interval<TypeParam>(-4,-2);
	std::vector<carl::Interval<TypeParam>> intervals1;
	intervals1.push_back(x);
	intervals1.push_back(y);
	intervals1.push_back(z);

	hypro::PTermBox<TypeParam> b1(intervals1);

	carl::Interval<TypeParam> a = carl::Interval<TypeParam>(1);
	carl::Interval<TypeParam> b = carl::Interval<TypeParam>(2,4);
	carl::Interval<TypeParam> c = carl::Interval<TypeParam>(-2,3);
	std::vector<carl::Interval<TypeParam>> intervals2;
	intervals2.push_back(a);
	intervals2.push_back(b);
	intervals2.push_back(c);

	hypro::PTermBox<TypeParam> b2(intervals2);

	hypro::PTermBox<TypeParam> res = b1.intersect(b2);
	carl::Interval<TypeParam> i = x.intersect(a);
	carl::Interval<TypeParam> j = y.intersect(b);
	carl::Interval<TypeParam> k = z.intersect(c);
	std::vector<carl::Interval<TypeParam>> intervals;
	intervals.push_back(i);
	intervals.push_back(j);
	intervals.push_back(k);

	EXPECT_EQ(hypro::PTermBox<TypeParam>(intervals), res);

	hypro::PTermBox<TypeParam> empt1 = this->box1.intersect(hypro::PTermBox<TypeParam>::Empty());
	EXPECT_TRUE(empt1.empty());

	hypro::PTermBox<TypeParam> empt2 = this->box1.intersect(hypro::PTermBox<TypeParam>::Empty(this->box1.dimension()));
	EXPECT_TRUE(empt2.empty());

	hypro::PTermBox<TypeParam> reduced = this->box1.intersect(hypro::PTermBox<TypeParam>(carl::Interval<TypeParam>(3,4)));
	EXPECT_EQ(reduced, hypro::PTermBox<TypeParam>(carl::Interval<TypeParam>(3,4)));
}

TYPED_TEST(PTermBoxTest, Membership)
{
    hypro::Point<TypeParam> p({4,2});
    EXPECT_TRUE(this->box1.contains(p));
}
