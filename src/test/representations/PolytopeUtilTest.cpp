/**
 * Test for the utility functions for polytopes.
 * @file PolytopeUtilTest.cpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since       2014-08-22
 * @version     2014-08-22
 */

#include "gtest/gtest.h"
#include "../defines.h"

#include "../../lib/representations/Polytopes/util.h"

template<typename Number>
class PolytopeUtilTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        p1 = hypro::Point<Number>({4.34,4});
        p2 = hypro::Point<Number>({5,7});
        p3 = hypro::Point<Number>({7,7});
        p4 = hypro::Point<Number>({8,4});
        p5 = hypro::Point<Number>({3,3});
        p6 = hypro::Point<Number>({4,5});
        p7 = hypro::Point<Number>({5,3});
    }

    virtual void TearDown()
    {
    }

    hypro::Point<Number> p1;
    hypro::Point<Number> p2;
    hypro::Point<Number> p3;
    hypro::Point<Number> p4;
    hypro::Point<Number> p5;
    hypro::Point<Number> p6;
    hypro::Point<Number> p7;
};

/**
 * @covers polytope::constructor
 * @covers polytope::pointToGenerator
 */
TYPED_TEST(PolytopeUtilTest, HyperplaneConstructor)
{
    hypro::Hyperplane<TypeParam> constructor1;

    hypro::vector_t<TypeParam> norm = hypro::vector_t<TypeParam>(2);
    norm(0) = 1;
    norm(1) = 3;

    hypro::Hyperplane<TypeParam> constructor2(norm, 4.3);

    hypro::Hyperplane<TypeParam> constructor3({1,3}, 4.3);

    hypro::Hyperplane<TypeParam> constructor4(constructor1);
    SUCCEED();
}

TYPED_TEST(PolytopeUtilTest, HyperplaneAccess)
{
    hypro::vector_t<TypeParam> norm = hypro::vector_t<TypeParam>(2);
    norm(0) = 1;
    norm(1) = 3;
    hypro::Hyperplane<TypeParam> access1(norm, 4.3);

    EXPECT_EQ(norm, access1.normal());
    EXPECT_EQ(4.3, access1.offset());
    EXPECT_EQ((unsigned) 2, access1.dimension());
}

TYPED_TEST(PolytopeUtilTest, HyperplaneIntersection)
{
    hypro::Point<TypeParam> norm({1,3});
    hypro::Hyperplane<TypeParam> intersection1(norm, 4.3);

    hypro::vector_t<TypeParam> vec = hypro::vector_t<TypeParam>(2);
    vec(0) = 2;
    vec(1) = 2;

    TypeParam result = 0.0;
    intersection1.intersection(result, vec);

    //std::cout << "Result: " << result << std::endl;

    EXPECT_EQ(1.075, vec(0)*result);
    EXPECT_EQ(1.075, vec(1)*result);
}

TYPED_TEST(PolytopeUtilTest, ConeConstructor)
{
	namespace ptope = hypro::polytope;

	ptope::Cone<TypeParam> cone1;

	hypro::vector_t<TypeParam> normal1 = hypro::vector_t<TypeParam>(3);
	normal1 << TypeParam(1), TypeParam(0), TypeParam(0);
	std::shared_ptr<hypro::Hyperplane<TypeParam>> hp1 = std::shared_ptr<hypro::Hyperplane<TypeParam>>(new hypro::Hyperplane<TypeParam>(normal1,TypeParam(0)));

	hypro::vector_t<TypeParam> normal2 = hypro::vector_t<TypeParam>(3);
	normal2 << TypeParam(1), TypeParam(0), TypeParam(0);
	std::shared_ptr<hypro::Hyperplane<TypeParam>> hp2 = std::shared_ptr<hypro::Hyperplane<TypeParam>>(new hypro::Hyperplane<TypeParam>(normal2,TypeParam(0)));

	hypro::vector_t<TypeParam> normal3 = hypro::vector_t<TypeParam>(3);
	normal3 << TypeParam(1), TypeParam(0), TypeParam(0);
	std::shared_ptr<hypro::Hyperplane<TypeParam>> hp3 = std::shared_ptr<hypro::Hyperplane<TypeParam>>(new hypro::Hyperplane<TypeParam>(normal3,TypeParam(0)));

	typename ptope::Cone<TypeParam>::planeVector planes;
	planes.push_back(hp1);
	planes.push_back(hp2);
	planes.push_back(hp3);

	ptope::Cone<TypeParam> cone2(planes);

    SUCCEED();
}

TYPED_TEST(PolytopeUtilTest, ConeAccess)
{
	namespace ptope = hypro::polytope;

	hypro::vector_t<TypeParam> normal1 = hypro::vector_t<TypeParam>(3);
	normal1 << TypeParam(1), TypeParam(0), TypeParam(0);
	std::shared_ptr<hypro::Hyperplane<TypeParam>> hp1 = std::shared_ptr<hypro::Hyperplane<TypeParam>>(new hypro::Hyperplane<TypeParam>(normal1,TypeParam(0)));

	hypro::vector_t<TypeParam> normal2 = hypro::vector_t<TypeParam>(3);
	normal2 << TypeParam(0), TypeParam(1), TypeParam(0);
	std::shared_ptr<hypro::Hyperplane<TypeParam>> hp2 = std::shared_ptr<hypro::Hyperplane<TypeParam>>(new hypro::Hyperplane<TypeParam>(normal2,TypeParam(0)));

	hypro::vector_t<TypeParam> normal3 = hypro::vector_t<TypeParam>(3);
	normal3 << TypeParam(0), TypeParam(0), TypeParam(1);
	std::shared_ptr<hypro::Hyperplane<TypeParam>> hp3 = std::shared_ptr<hypro::Hyperplane<TypeParam>>(new hypro::Hyperplane<TypeParam>(normal3,TypeParam(0)));

	typename ptope::Cone<TypeParam>::planeVector planes;
	planes.push_back(hp1);
	planes.push_back(hp2);
	planes.push_back(hp3);

	ptope::Cone<TypeParam> cone(planes);

	//std::cout << cone << std::endl;

	//hypro::vector_t<TypeParam> v1 = hypro::vector_t<TypeParam>(3);
	//v1 << TypeParam(1), TypeParam(1), TypeParam(1);
	hypro::vector_t<TypeParam> v2 = hypro::vector_t<TypeParam>(3);
	v2 << TypeParam(1), TypeParam(1), TypeParam(-1);
	//hypro::vector_t<TypeParam> v3 = hypro::vector_t<TypeParam>(3);
	//v3 << TypeParam(0), TypeParam(0), TypeParam(-1);

	//cone.add(v1);

	//std::cout << "Add v2." << std::endl;

	cone.add(v2);
	//cone.add(v3);

	//std::cout << "Result: " << cone << std::endl;

    SUCCEED();
}

TYPED_TEST(PolytopeUtilTest, dPermutation) {
	// TODO: introduce test.
	namespace ptope = hypro::polytope;

	ptope::dPermutator dpermutator = ptope::dPermutator(5,3);
	std::vector<unsigned> perm(3,0);

	while(!dpermutator.end()) {
		perm = dpermutator();
		std::cout << perm << std::endl;
	}
}

/*
TYPED_TEST(PolytopeUtilTest, ConeContains)
{

}

TYPED_TEST(PolytopeUtilTest, FanConstructor)
{
    SUCCEED();
}

TYPED_TEST(PolytopeUtilTest, FanAccess)
{

}

TYPED_TEST(PolytopeUtilTest, FanContainingCone)
{

}
*/
