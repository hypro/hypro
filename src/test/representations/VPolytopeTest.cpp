#include "gtest/gtest.h"
#include "../defines.h"
#include "carl/numbers/FLOAT_T.h"
#include <carl/core/VariablePool.h>
#include "../../lib/datastructures/Point.h"
#include "../../lib/representations/Polytopes/VPolytope/VPolytope.h"

using namespace hypro;
using namespace carl;

template<typename Number>
class VPolytopeTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		vector_t<Number> p1 = vector_t<Number>(2);
		p1(0) = 1;
		p1(1) = 2;
		vector_t<Number> p2 = vector_t<Number>(2);
		p2(0) = 3;
		p2(1) = 2;
		vector_t<Number> p3 = vector_t<Number>(2);
		p3(0) = 3;
		p3(1) = 4;
		vector_t<Number> p4 = vector_t<Number>(2);
		p4(0) = 1;
		p4(1) = 4;
		vector_t<Number> p5 = vector_t<Number>(2);
		p5(0) = 2;
		p5(1) = 1;
		vector_t<Number> p6 = vector_t<Number>(2);
		p6(0) = 4;
		p6(1) = 1;
		vector_t<Number> p7 = vector_t<Number>(2);
		p7(0) = 4;
		p7(1) = 3;
		vector_t<Number> p8 = vector_t<Number>(2);
		p8(0) = 2;
		p8(1) = 3;

		points1.push_back(Point<Number>(p1));
		points1.push_back(Point<Number>(p2));
		points1.push_back(Point<Number>(p3));
		points1.push_back(Point<Number>(p4));
		
		points2.push_back(Point<Number>(p5));
		points2.push_back(Point<Number>(p6));
		points2.push_back(Point<Number>(p7));
		points2.push_back(Point<Number>(p8));
	}
	
	virtual void TearDown()
	{
	}

	typename VPolytope<Number>::pointVector points1;
	typename VPolytope<Number>::pointVector points2;
};

TYPED_TEST(VPolytopeTest, Constructor)
{
	VPolytope<TypeParam> aVPolytope = VPolytope<TypeParam>();
	VPolytope<TypeParam> anotherVPolytope = VPolytope<TypeParam>(this->points1);
	VPolytope<TypeParam> vpt2 = VPolytope<TypeParam>(this->points2);
	
	VPolytope<TypeParam> copyAssignment = VPolytope<TypeParam>(anotherVPolytope);
	
	SUCCEED();
}

TYPED_TEST(VPolytopeTest, Access)
{
	VPolytope<TypeParam> vpt1 = VPolytope<TypeParam>(this->points1);
	EXPECT_EQ((unsigned) 2, vpt1.dimension());
	EXPECT_EQ((unsigned) 4, vpt1.size());
	EXPECT_FALSE(vpt1.reduced());
	//polytope::Fan<TypeParam> tmpFan = vpt1.fan();
		
	typename VPolytope<TypeParam>::pointVector vertices =  vpt1.vertices();
	for(auto& vertex : vertices) {
		EXPECT_TRUE(vpt1.hasVertex(vertex));
	}
}

TYPED_TEST(VPolytopeTest, Insertion)
{
	VPolytope<TypeParam> vpt1 = VPolytope<TypeParam>(this->points1);
	Point<TypeParam> p1({1,1});
	vpt1.insert(p1);
	Point<TypeParam> p2({1,2});
	vpt1.insert(p2);
	Point<TypeParam> p3({1,3});
	vpt1.insert(p3);
	Point<TypeParam> p4({1,4});
	vpt1.insert(p4);
	Point<TypeParam> p5({1,5});
	vpt1.insert(p5);

	EXPECT_FALSE(vpt1.reduced());
}

TYPED_TEST(VPolytopeTest, Union)
{
	VPolytope<TypeParam> vpt1 = VPolytope<TypeParam>(this->points1);
	VPolytope<TypeParam> vpt2 = VPolytope<TypeParam>(this->points2);
	VPolytope<TypeParam> res = vpt1.unite(vpt2);

	for(auto& vertex : vpt1.vertices()) {
		//EXPECT_TRUE(res.hasVertex(vertex));
		EXPECT_TRUE(res.contains(vertex));
	}
	for(auto& vertex : vpt2.vertices()) {
		//EXPECT_TRUE(res.hasVertex(vertex));
		EXPECT_TRUE(res.contains(vertex));
	}
}

TYPED_TEST(VPolytopeTest, LinearTransformation)
{
	VPolytope<TypeParam> vpt1 = VPolytope<TypeParam>(this->points1);
	matrix_t<TypeParam> A(2,2);
	A(0,0) = 1;
	A(0,1) = 2;
	A(1,0) = 3;
	A(1,1) = 4;

	VPolytope<TypeParam> res = vpt1.linearTransformation(A);

	for(auto& vertex : vpt1.vertices()) {
		EXPECT_TRUE(res.hasVertex(Point<TypeParam>(vector_t<TypeParam>(A*vertex.rawCoordinates()))));
	}
}

TYPED_TEST(VPolytopeTest, MinkowskiSum)
{
	VPolytope<TypeParam> vpt1 = VPolytope<TypeParam>(this->points1);
	VPolytope<TypeParam> vpt2 = VPolytope<TypeParam>(this->points2);

	VPolytope<TypeParam> res = vpt1.minkowskiSum(vpt2);

	//std::cout << "Result: " << std::endl << res << std::endl;

	for(auto& lhs : vpt1.vertices()) {
		for(auto& rhs : vpt2.vertices()) {
			EXPECT_TRUE(res.hasVertex(lhs+rhs));
		}
	}
}

TYPED_TEST(VPolytopeTest, Intersection)
{	
	VPolytope<TypeParam> vpt1 = VPolytope<TypeParam>(this->points1);
	VPolytope<TypeParam> vpt2 = VPolytope<TypeParam>(this->points2);
	VPolytope<TypeParam> result = vpt1.intersect(vpt2);

	for(auto& vertex : result.vertices()) {
		EXPECT_TRUE(vpt1.contains(vertex));
		EXPECT_TRUE(vpt2.contains(vertex));
	}
}

TYPED_TEST(VPolytopeTest, Membership)
{
	VPolytope<TypeParam> vpt1 = VPolytope<TypeParam>(this->points1);
	
	Point<TypeParam> p1({0, 0});
	EXPECT_FALSE(vpt1.contains(p1));

	Point<TypeParam> p2({2.5, 3});
	EXPECT_TRUE(vpt1.contains(p2));

	Point<TypeParam> p3({3, 3});
	EXPECT_TRUE(vpt1.contains(p3));

	Point<TypeParam> p4({2, 2});
	EXPECT_TRUE(vpt1.contains(p4));
}
