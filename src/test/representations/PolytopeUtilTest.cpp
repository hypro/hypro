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

#include "../../lib/util/VariablePool.h"
#include "../../lib/representations/Polytopes/util.h"

using namespace hypro;
using namespace hypro::polytope;

template<typename Number>
class PolytopeUtilTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
		pool.clear();
		x = pool.newCarlVariable();
		y = pool.newCarlVariable();
        // p1
        typename Point<Number>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(x, Number(4.34)) );
        coordinates1.insert( std::make_pair(y, Number(4)) );
        p1 = Point<Number>(coordinates1);

        // p2
        typename Point<Number>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(x, Number(5)) );
        coordinates2.insert( std::make_pair(y, Number(7)) );
        p2 = Point<Number>(coordinates2);

        // p3
        typename Point<Number>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(x, Number(7)) );
        coordinates3.insert( std::make_pair(y, Number(7)) );
        p3 = Point<Number>(coordinates3);

        // p4
        typename Point<Number>::coordinateMap coordinates4;
        coordinates4.insert( std::make_pair(x, Number(8)) );
        coordinates4.insert( std::make_pair(y, Number(4)) );
        p4 = Point<Number>(coordinates4);

        // p5
        typename Point<Number>::coordinateMap coordinates5;
        coordinates5.insert( std::make_pair(x, Number(3)) );
        coordinates5.insert( std::make_pair(y, Number(3)) );
        p5 = Point<Number>(coordinates5);

        // p6
        typename Point<Number>::coordinateMap coordinates6;
        coordinates6.insert( std::make_pair(x, Number(4)) );
        coordinates6.insert( std::make_pair(y, Number(5)) );
        p6 = Point<Number>(coordinates6);

        // p7
        typename Point<Number>::coordinateMap coordinates7;
        coordinates7.insert( std::make_pair(x, Number(5)) );
        coordinates7.insert( std::make_pair(y, Number(3)) );
        p7 = Point<Number>(coordinates7);
    }

    virtual void TearDown()
    {
        hypro::VariablePool::getInstance().clear();
    }

    hypro::VariablePool& pool = hypro::VariablePool::getInstance();
    carl::Variable x;
    carl::Variable y;

    Point<Number> p1;
    Point<Number> p2;
    Point<Number> p3;
    Point<Number> p4;
    Point<Number> p5;
    Point<Number> p6;
    Point<Number> p7;
};

/**
 * @covers polytope::constructor
 * @covers polytope::pointToGenerator
 */
TYPED_TEST(PolytopeUtilTest, HyperplaneConstructor)
{
    Hyperplane<TypeParam> constructor1;

    vector_t<TypeParam> norm = vector_t<TypeParam>(2);
    norm(0) = 1;
    norm(1) = 3;

    Hyperplane<TypeParam> constructor2(norm, 4.3);

    Hyperplane<TypeParam> constructor3({1,3}, 4.3);

    Hyperplane<TypeParam> constructor4(constructor1);
    SUCCEED();
}

TYPED_TEST(PolytopeUtilTest, HyperplaneAccess)
{
    vector_t<TypeParam> norm = vector_t<TypeParam>(2);
    norm(0) = 1;
    norm(1) = 3;
    Hyperplane<TypeParam> access1(norm, 4.3);

    EXPECT_EQ(norm, access1.normal());
    EXPECT_EQ(4.3, access1.offset());
    EXPECT_EQ((unsigned) 2, access1.dimension());
}

TYPED_TEST(PolytopeUtilTest, HyperplaneIntersection)
{
    Point<TypeParam> norm({1,3});
    Hyperplane<TypeParam> intersection1(norm, 4.3);

    vector_t<TypeParam> vec = vector_t<TypeParam>(2);
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
	Cone<TypeParam> cone1;

	vector_t<TypeParam> normal1 = vector_t<TypeParam>(3);
	normal1 << TypeParam(1), TypeParam(0), TypeParam(0);
	std::shared_ptr<Hyperplane<TypeParam>> hp1 = std::shared_ptr<Hyperplane<TypeParam>>(new Hyperplane<TypeParam>(normal1,TypeParam(0)));

	vector_t<TypeParam> normal2 = vector_t<TypeParam>(3);
	normal2 << TypeParam(1), TypeParam(0), TypeParam(0);
	std::shared_ptr<Hyperplane<TypeParam>> hp2 = std::shared_ptr<Hyperplane<TypeParam>>(new Hyperplane<TypeParam>(normal2,TypeParam(0)));

	vector_t<TypeParam> normal3 = vector_t<TypeParam>(3);
	normal3 << TypeParam(1), TypeParam(0), TypeParam(0);
	std::shared_ptr<Hyperplane<TypeParam>> hp3 = std::shared_ptr<Hyperplane<TypeParam>>(new Hyperplane<TypeParam>(normal3,TypeParam(0)));

	typename Cone<TypeParam>::planeVector planes;
	planes.push_back(hp1);
	planes.push_back(hp2);
	planes.push_back(hp3);

	Cone<TypeParam> cone2(planes);

    SUCCEED();
}

TYPED_TEST(PolytopeUtilTest, ConeAccess)
{
	vector_t<TypeParam> normal1 = vector_t<TypeParam>(3);
	normal1 << TypeParam(1), TypeParam(0), TypeParam(0);
	std::shared_ptr<Hyperplane<TypeParam>> hp1 = std::shared_ptr<Hyperplane<TypeParam>>(new Hyperplane<TypeParam>(normal1,TypeParam(0)));

	vector_t<TypeParam> normal2 = vector_t<TypeParam>(3);
	normal2 << TypeParam(0), TypeParam(1), TypeParam(0);
	std::shared_ptr<Hyperplane<TypeParam>> hp2 = std::shared_ptr<Hyperplane<TypeParam>>(new Hyperplane<TypeParam>(normal2,TypeParam(0)));

	vector_t<TypeParam> normal3 = vector_t<TypeParam>(3);
	normal3 << TypeParam(0), TypeParam(0), TypeParam(1);
	std::shared_ptr<Hyperplane<TypeParam>> hp3 = std::shared_ptr<Hyperplane<TypeParam>>(new Hyperplane<TypeParam>(normal3,TypeParam(0)));

	typename Cone<TypeParam>::planeVector planes;
	planes.push_back(hp1);
	planes.push_back(hp2);
	planes.push_back(hp3);

	Cone<TypeParam> cone(planes);

	//std::cout << cone << std::endl;

	//vector_t<TypeParam> v1 = vector_t<TypeParam>(3);
	//v1 << TypeParam(1), TypeParam(1), TypeParam(1);
	vector_t<TypeParam> v2 = vector_t<TypeParam>(3);
	v2 << TypeParam(1), TypeParam(1), TypeParam(-1);
	//vector_t<TypeParam> v3 = vector_t<TypeParam>(3);
	//v3 << TypeParam(0), TypeParam(0), TypeParam(-1);

	//cone.add(v1);

	//std::cout << "Add v2." << std::endl;

	cone.add(v2);
	//cone.add(v3);

	//std::cout << "Result: " << cone << std::endl;

    SUCCEED();
}

TYPED_TEST(PolytopeUtilTest, dPermutation) {
	std::vector<std::vector<unsigned>> dperm = dPermutation(4,2);

	for(auto perm : dperm) {
		//std::cout << "permutation (";
		for(auto item : perm) {
			//std::cout << item << ", ";
		}
		//std::cout << ")" << std::endl;
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
