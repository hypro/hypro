/**
 * Test for hyperplanes.
 * @file PolytopeTest.cpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since       2015-02-12
 * @version     2015-02-12
 */

#include "gtest/gtest.h"
#include "../defines.h"

#include "../../lib/datastructures/Hyperplane.h"
#include "../../lib/representations/Polytopes/HPolytope/HPolytope.h"

using namespace hypro;
using namespace carl;

template<typename Number>
class HyperplaneTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

};

TYPED_TEST(HyperplaneTest, Constructor)
{
	//Hyperplane<TypeParam> empty = Hyperplane<TypeParam>();
	Point<TypeParam> vec = Point<TypeParam>({2,4});
	Hyperplane<TypeParam> normals = Hyperplane<TypeParam>(vec, TypeParam(3));
	Hyperplane<TypeParam> initializer = Hyperplane<TypeParam>({TypeParam(2), TypeParam(4)}, TypeParam(3));
	EXPECT_EQ(normals, initializer);

	vector_t<TypeParam> normal = vector_t<TypeParam>(2);
	normal(0) = TypeParam(2);
	normal(1) = TypeParam(4);
	Hyperplane<TypeParam>(normal, TypeParam(3));
	//Hyperplane(const vector_t<Number>& _vec, const std::vector<vector_t<Number>>& _vectorSet);

	//std::cout << __func__ << ": vec " << vec << ", normal: " << normal << std::endl;


	Hyperplane<TypeParam> copy = Hyperplane<TypeParam>(normals);
	//EXPECT_EQ(copy, normals);
	SUCCEED();
}

TYPED_TEST(HyperplaneTest, Access)
{

}

TYPED_TEST(HyperplaneTest, Evaluation)
{
	vector_t<TypeParam> vec(2);
	vec(0) = 2;
	vec(1) = 4;
	Hyperplane<TypeParam> hp1 = Hyperplane<TypeParam>(vec, TypeParam(3));

	vector_t<TypeParam> test(2);
	test(0) = 5;
	test(1) = 1;

	EXPECT_EQ(TypeParam(vec.dot(test)), hp1.evaluate(test) );
}

TYPED_TEST(HyperplaneTest, SignedDistance)
{
	vector_t<TypeParam> vec(2);
	vec(0) = 2;
	vec(1) = 4;
	Hyperplane<TypeParam> hp1 = Hyperplane<TypeParam>(vec, TypeParam(3));

	vector_t<TypeParam> test(2);
	test(0) = 5;
	test(1) = 1;

	EXPECT_EQ(TypeParam(vec.dot(test)) - hp1.offset(), hp1.signedDistance(test) );
}

TYPED_TEST(HyperplaneTest, Intersection)
{
	vector_t<TypeParam> normal1(4);
	normal1(0) = 1;
	normal1(1) = 1;
	normal1(2) = 1;
	normal1(3) = 1;
	Hyperplane<TypeParam> hp1 = Hyperplane<TypeParam>(normal1, TypeParam(3));

	vector_t<TypeParam> normal2(4);
	normal2(0) = 2;
	normal2(1) = 1;
	normal2(2) = 3;
	normal2(3) = 4;
	Hyperplane<TypeParam> hp2 = Hyperplane<TypeParam>(normal2, TypeParam(4));

	//HPolytope<TypeParam> res = hp1.intersection(hp2);
	//std::cout << res << std::endl;

	//std::cout << "Intersection Vector calculation result: " << std::endl;
	vector_t<TypeParam> v = hp1.intersectionVector(hp2);
	//std::cout << "Intersection Vector: " << v << std::endl;
}

TYPED_TEST(HyperplaneTest, saveIntersection)
{
	/*
	vector_t<TypeParam> normal1(2);
	normal1(0) = 1;
	normal1(1) = 1;
	Hyperplane<TypeParam> hp1 = Hyperplane<TypeParam>(normal1, TypeParam(1));

	vector_t<TypeParam> normal2(2);
	normal2(0) = -1 + 1000000000*std::numeric_limits<TypeParam>::epsilon();
	normal2(1) = -1 + 1000000000*std::numeric_limits<TypeParam>::epsilon();
	Hyperplane<TypeParam> hp2 = Hyperplane<TypeParam>(normal2, TypeParam(-1+0.0001));

	std::vector<hypro::Hyperplane<TypeParam>> hpv;
	hpv.push_back(hp1);
	hpv.push_back(hp2);

	hypro::vector_t<TypeParam> res = Hyperplane<TypeParam>::saveIntersect(hpv, 1);

	EXPECT_TRUE(hp1.normal().dot(res) >= hp1.offset());
	EXPECT_TRUE(hp2.normal().dot(res) >= hp2.offset());
	*/
}