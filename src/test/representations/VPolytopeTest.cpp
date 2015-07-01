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

	/*std::cout<< "Part 2 starting: "	<< std::endl;
	          std::vector<Point<TypeParam>> ps3;
	          Point<TypeParam> p01 = Point<TypeParam>({1,1,1});
	          Point<TypeParam> p02 = Point<TypeParam>({1,3,1});
	          Point<TypeParam> p03 = Point<TypeParam>({3,1,1});
	          Point<TypeParam> p04 = Point<TypeParam>({3,3,1});
	          Point<TypeParam> p05 = Point<TypeParam>({1,1,3});
	          Point<TypeParam> p06 = Point<TypeParam>({1,3,3});
	          Point<TypeParam> p07 = Point<TypeParam>({3,1,3});
	          Point<TypeParam> p08 = Point<TypeParam>({3,3,3});

	          ps3.push_back(p01);
	          ps3.push_back(p02);
	          ps3.push_back(p03);
	          ps3.push_back(p04);
	          ps3.push_back(p05);
	          ps3.push_back(p06);
	          ps3.push_back(p07);
	          ps3.push_back(p08);

	          VPolytope<TypeParam> pt3 = VPolytope<TypeParam>(ps3);

	          std::vector<Point<TypeParam>> ps4;
	          Point<TypeParam> p09 = Point<TypeParam>({3,5,1});
	          Point<TypeParam> p10 = Point<TypeParam>({5,3,1});
	          Point<TypeParam> p11 = Point<TypeParam>({5,5,1});
	          Point<TypeParam> p12 = Point<TypeParam>({3,5,3});
	          Point<TypeParam> p13 = Point<TypeParam>({5,3,3});
	          Point<TypeParam> p14 = Point<TypeParam>({5,5,3});

	          ps4.push_back(p04);
	          ps4.push_back(p08);
	          ps4.push_back(p09);
	          ps4.push_back(p10);
	          ps4.push_back(p11);
	          ps4.push_back(p12);
	          ps4.push_back(p13);
	          ps4.push_back(p14);

	          VPolytope<TypeParam> pt4 = VPolytope<TypeParam>(ps4);

	          VPolytope<TypeParam> res2 = pt3.unite(pt4);

	          for(auto& vertex : pt3.vertices()) {
	        	  EXPECT_TRUE(res2.contains(vertex));
	          }

	          for(auto& vertex : pt4.vertices()) {
	        	  EXPECT_TRUE(res2.contains(vertex));
	          }


	          VPolytope<TypeParam> res3 = res2.unite(VPolytope<TypeParam>());

	          for(auto& vertex : res3.vertices()) {
	        	  EXPECT_TRUE(res2.contains(vertex));
	          }

	          for(auto& vertex : res2.vertices()) {
	        	  EXPECT_TRUE(res3.contains(vertex));
	          } */
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

	/*std::cout<< "Part 2 starting: "	<< std::endl;

	      std::vector<Point<TypeParam>> ps3;
	      Point<TypeParam> p01 = Point<TypeParam>({1,1,1});
	      Point<TypeParam> p02 = Point<TypeParam>({1,3,1});
	      Point<TypeParam> p03 = Point<TypeParam>({3,1,1});
	      Point<TypeParam> p04 = Point<TypeParam>({3,3,1});
	      Point<TypeParam> p05 = Point<TypeParam>({1,1,3});
	      Point<TypeParam> p06 = Point<TypeParam>({1,3,3});
	      Point<TypeParam> p07 = Point<TypeParam>({3,1,3});
	      Point<TypeParam> p08 = Point<TypeParam>({3,3,3});

	      ps3.push_back(p01);
	      ps3.push_back(p02);
	      ps3.push_back(p03);
	      ps3.push_back(p04);
	      ps3.push_back(p05);
	      ps3.push_back(p06);
	      ps3.push_back(p07);
	      ps3.push_back(p08);

	      VPolytope<TypeParam> pt3 = VPolytope<TypeParam>(ps3);

	      std::vector<Point<TypeParam>> ps4;
	      Point<TypeParam> p09 = Point<TypeParam>({2,2,1});
	      Point<TypeParam> p10 = Point<TypeParam>({2,4,1});
	      Point<TypeParam> p11 = Point<TypeParam>({4,2,1});
	      Point<TypeParam> p12 = Point<TypeParam>({4,4,1});
	      Point<TypeParam> p13 = Point<TypeParam>({2,2,3});
	      Point<TypeParam> p14 = Point<TypeParam>({2,4,3});
	      Point<TypeParam> p15 = Point<TypeParam>({4,2,3});
	      Point<TypeParam> p16 = Point<TypeParam>({4,4,3});

	      ps4.push_back(p09);
	      ps4.push_back(p10);
	      ps4.push_back(p11);
	      ps4.push_back(p12);
	      ps4.push_back(p13);
	      ps4.push_back(p14);
	      ps4.push_back(p15);
	      ps4.push_back(p16);

	      VPolytope<TypeParam> pt4 = VPolytope<TypeParam>(ps4);

	      VPolytope<TypeParam> res2 = pt3.intersect(pt4);

	      for(auto& vertex : res2.vertices()) {
	    	  EXPECT_TRUE(pt3.contains(vertex));
	    	  EXPECT_TRUE(pt4.contains(vertex));
	      }

	      VPolytope<TypeParam> res3 = res2.intersect(VPolytope<TypeParam>());

	      EXPECT_TRUE(res3.size() == 0); */
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
