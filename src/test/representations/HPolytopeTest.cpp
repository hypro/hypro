#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/representations/Polytopes/HPolytope/HPolytope.h"

using namespace hypro;
using namespace carl;

template<typename Number>
class HPolytopeTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		// A rectangle
		Hyperplane<Number> hp1({1,0},2);
		Hyperplane<Number> hp2({0,1},2);
		Hyperplane<Number> hp3({-1,0},2);
		Hyperplane<Number> hp4({0,-1},2);

		// A triangle
		Hyperplane<Number> hp5({1,1},1);
		Hyperplane<Number> hp6({-1,1},1);
		Hyperplane<Number> hp7({0,-1},1);

		planes1.push_back(hp1);
		planes1.push_back(hp2);
		planes1.push_back(hp3);
		planes1.push_back(hp4);

		planes2.push_back(hp5);
		planes2.push_back(hp6);
		planes2.push_back(hp7);
	}
	
	virtual void TearDown()
	{
	}

	typename HPolytope<Number>::HyperplaneVector planes1;
	typename HPolytope<Number>::HyperplaneVector planes2;
};

TYPED_TEST(HPolytopeTest, Constructor)
{
	HPolytope<TypeParam> aHPolytope = HPolytope<TypeParam>();
	HPolytope<TypeParam> anotherHPolytope = HPolytope<TypeParam>(this->planes1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->planes2);
	
	HPolytope<TypeParam> copyAssignment = HPolytope<TypeParam>(anotherHPolytope);
	
	SUCCEED();
}

TYPED_TEST(HPolytopeTest, Access)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	EXPECT_EQ((unsigned) 2, hpt1.dimension());
	EXPECT_EQ((unsigned) 4, hpt1.size());
	//EXPECT_FALSE(hpt1.reduced());
	//polytope::Fan<TypeParam> tmpFan = hpt1.fan();
		
	typename HPolytope<TypeParam>::HyperplaneVector planes =  hpt1.constraints();
	for(auto& constraint : planes) {
		EXPECT_TRUE(hpt1.hasConstraint(constraint));
	}
}

TYPED_TEST(HPolytopeTest, Corners)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->planes2);

	typename VPolytope<TypeParam>::pointVector corners = hpt1.vertices();
	for(auto& corner : corners) {
		EXPECT_TRUE(hpt1.isExtremePoint(corner, TypeParam(0.0001)));
	}

	corners = hpt2.vertices();
	for(auto& corner : corners) {
		EXPECT_TRUE(hpt2.isExtremePoint(corner, TypeParam(0.0001)));
	}

	// test extremepoints
	hypro::vector_t<TypeParam> p1(2);
	p1(0) = 2;
	p1(1) = 0;
	EXPECT_FALSE(hpt1.isExtremePoint(p1, TypeParam(0.0001)));
}


TYPED_TEST(HPolytopeTest, Insertion)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	Hyperplane<TypeParam> p1({1,1}, 4);
	hpt1.insert(p1);

	EXPECT_TRUE(hpt1.hasConstraint(p1));
}

/*
TYPED_TEST(HPolytopeTest, Union)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->points1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->points2);
	HPolytope<TypeParam> res = hpt1.unite(hpt2);

	for(auto& vertex : hpt1.vertices()) {
		EXPECT_TRUE(res.hasVertex(vertex));
		EXPECT_TRUE(res.contains(vertex));
	}
	for(auto& vertex : hpt2.vertices()) {
		EXPECT_TRUE(res.hasVertex(vertex));
		EXPECT_TRUE(res.contains(vertex));
	}
}
*/
TYPED_TEST(HPolytopeTest, LinearTransformation)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	matrix_t<TypeParam> A(2,2);
	A(0,0) = 1;
	A(0,1) = 2;
	A(1,0) = 3;
	A(1,1) = 4;

	HPolytope<TypeParam> res = hpt1.linearTransformation(A);

	for(auto& plane : hpt1.constraints()) {
		EXPECT_TRUE(res.hasConstraint(plane.linearTransformation(A)));
	}
}


TYPED_TEST(HPolytopeTest, MinkowskiSum)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->planes2);

	HPolytope<TypeParam> res = hpt1.minkowskiSum(hpt2);

	std::cout << "Result: " << std::endl << res << std::endl;

	std::cout << "Result vertices: " << std::endl;
	for(auto& vertex : res.vertices()) {
		std::cout << vertex.rawCoordinates().transpose() << std::endl;
	}

	for(auto& lhs : hpt1.vertices()) {
		for(auto& rhs : hpt2.vertices()) {
			std::cout << "Test: " << vector_t<TypeParam>(lhs+rhs).transpose() << std::endl;
			EXPECT_TRUE(res.contains(lhs+rhs)); // Todo: Make this more restrictive
		}
	}

	vector_t<TypeParam> p1(2);
	p1(0) = 3;
	p1(1) = 2;
	EXPECT_TRUE(res.contains(p1));
	p1(0) = 3;
	p1(1) = 3;
	EXPECT_FALSE(res.contains(p1));
}


TYPED_TEST(HPolytopeTest, Intersection)
{	
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->planes2);
	HPolytope<TypeParam> result = hpt1.intersect(hpt2);

	for(auto& plane : result.constraints()) {
		EXPECT_TRUE(hpt1.hasConstraint(plane) || hpt2.hasConstraint(plane));
	}
}


TYPED_TEST(HPolytopeTest, Membership)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	
	Point<TypeParam> p1({0, 0});
	EXPECT_TRUE(hpt1.contains(p1));

	Point<TypeParam> p2({1.5, 1.5});
	EXPECT_TRUE(hpt1.contains(p2));

	Point<TypeParam> p3({-2,0});
	EXPECT_TRUE(hpt1.contains(p3));

	Point<TypeParam> p4({2, 2});
	EXPECT_TRUE(hpt1.contains(p4));

	Point<TypeParam> p5({2.1, 0});
	EXPECT_FALSE(hpt1.contains(p5));
}
