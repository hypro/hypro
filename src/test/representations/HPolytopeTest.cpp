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
	HPolytope<TypeParam> empt = HPolytope<TypeParam>::Empty();
	EXPECT_TRUE(empt.empty());

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

TYPED_TEST(HPolytopeTest, Swap)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->planes2);

	typename HPolytope<TypeParam>::HyperplaneVector planes =  hpt1.constraints();

	swap(hpt1,hpt2);

	for(auto& constraint : planes) {
		EXPECT_TRUE(hpt2.hasConstraint(constraint));
	}
}

TYPED_TEST(HPolytopeTest, Corners)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->planes2);

	typename std::vector<Point<TypeParam>> corners = hpt1.vertices();
	for(auto& corner : corners) {
		EXPECT_TRUE(hpt1.isExtremePoint(corner));
	}

	corners = hpt2.vertices();
	std::cout << "HPT2: " << hpt2 << std::endl;

	for(auto& corner : corners) {
		EXPECT_TRUE(hpt2.isExtremePoint(corner));
	}

	// test extremepoints
	hypro::vector_t<TypeParam> p1(2);
	p1(0) = 2;
	p1(1) = 0;
	EXPECT_FALSE(hpt1.isExtremePoint(p1));
}


TYPED_TEST(HPolytopeTest, Insertion)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	Hyperplane<TypeParam> p1({1,1}, 4);
	hpt1.insert(p1);

	EXPECT_TRUE(hpt1.hasConstraint(p1));
}


TYPED_TEST(HPolytopeTest, Union)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->planes2);
	HPolytope<TypeParam> res = hpt1.unite(hpt2);

	for(auto& vertex : hpt1.vertices()) {
		//EXPECT_TRUE(res.hasVertex(vertex));
		EXPECT_TRUE(res.contains(vertex));
	}
	for(auto& vertex : hpt2.vertices()) {
		//EXPECT_TRUE(res.hasVertex(vertex));
		EXPECT_TRUE(res.contains(vertex));
	}

	/* std::cout<< "Part 2 starting: "	<< std::endl;
			  std::vector<Hyperplane<TypeParam>> ps3;
			  Hyperplane<TypeParam> p01 = Hyperplane<TypeParam>({0,-1,0},1);
			  Hyperplane<TypeParam> p02 = Hyperplane<TypeParam>({0,1,0},-3);
			  Hyperplane<TypeParam> p03 = Hyperplane<TypeParam>({-1,0,0},1);
			  Hyperplane<TypeParam> p04 = Hyperplane<TypeParam>({1,0,0},-3);
			  Hyperplane<TypeParam> p05 = Hyperplane<TypeParam>({0,0,-1},1);
			  Hyperplane<TypeParam> p06 = Hyperplane<TypeParam>({0,0,1},-3);

			  ps3.push_back(p01);
			  ps3.push_back(p02);
			  ps3.push_back(p03);
			  ps3.push_back(p04);
			  ps3.push_back(p05);
			  ps3.push_back(p06);

			  HPolytope<TypeParam> pt3 = HPolytope<TypeParam>(ps3);

			  std::vector<Hyperplane<TypeParam>> ps4;
			  Hyperplane<TypeParam> p07 = Hyperplane<TypeParam>({0,-1,0},3);
			  Hyperplane<TypeParam> p08 = Hyperplane<TypeParam>({0,1,0},-5);
			  Hyperplane<TypeParam> p09 = Hyperplane<TypeParam>({-1,0,0},3);
			  Hyperplane<TypeParam> p10 = Hyperplane<TypeParam>({1,0,0},-5);


			  ps4.push_back(p05);
			  ps4.push_back(p06);
			  ps4.push_back(p07);
			  ps4.push_back(p08);
			  ps4.push_back(p09);
			  ps4.push_back(p10);


			  HPolytope<TypeParam> pt4 = HPolytope<TypeParam>(ps4);

			  std::cout<<__func__ << " : " <<__LINE__ <<std::endl;

			  HPolytope<TypeParam> res2 = pt3.unite(pt4);
			  std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
			  for(auto& vertex : pt3.vertices()) {
				  EXPECT_TRUE(res2.contains(vertex));
			  }
			  std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
			  for(auto& vertex : pt4.vertices()) {
				  EXPECT_TRUE(res2.contains(vertex));
			  }

			  std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
			  HPolytope<TypeParam> res3 = res2.unite(HPolytope<TypeParam>());
			  std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
			  for(auto& vertex : res3.vertices()) {
				  EXPECT_TRUE(res2.contains(vertex));
			  }
			  std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
			  for(auto& vertex : res2.vertices()) {
				  EXPECT_TRUE(res3.contains(vertex));
			  } */ //still needs HPolytope to VPolytope conversion for higher dimensions !!!!
}

TYPED_TEST(HPolytopeTest, LinearTransformation)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	matrix_t<TypeParam> A(2,2);
	A(0,0) = 1;
	A(0,1) = 2;
	A(1,0) = 3;
	A(1,1) = 4;

	std::cout << "linearTransformation begin." << std::endl;
	HPolytope<TypeParam> res = hpt1.linearTransformation(A, vector_t<TypeParam>::Zero(A.rows()));
	std::cout << "linearTransformation end." << std::endl;
	std::cout << "Linear Transformation result: " << res << std::endl;

	std::cout << "Compute vertices for VPoly construction." << std::endl;
	VPolytope<TypeParam> test(hpt1.vertices());
	std::cout << "Test: " << test << std::endl;

	std::cout << "Test linearTransformation begin." << std::endl;
	test = test.linearTransformation(A,vector_t<TypeParam>::Zero(A.rows()));
	std::cout << "Test linearTransformation end." << std::endl;

	for(const auto& vertex : test.vertices()) {
		EXPECT_TRUE(res.contains(vertex));
	}
	for(const auto& vertex : res.vertices()) {
		EXPECT_TRUE(test.contains(vertex));
	}
}


TYPED_TEST(HPolytopeTest, MinkowskiSum)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->planes2);

	HPolytope<TypeParam> res = hpt1.minkowskiSum(hpt2);

	//std::cout << "Result: " << std::endl << res << std::endl;

	//std::cout << "Result vertices: " << std::endl;
	for(auto& vertex : res.vertices()) {
		std::cout << vertex.rawCoordinates().transpose() << std::endl;
	}

	//std::cout << "######" << std::endl;

	for(auto& lhs : hpt1.vertices()) {
		for(auto& rhs : hpt2.vertices()) {
	//		std::cout << "Test: " << vector_t<TypeParam>(lhs+rhs).transpose() << std::endl;
			EXPECT_TRUE(res.contains(lhs+rhs)); // Todo: Make this more restrictive
		}
	}

	//std::cout << "######" << std::endl;

	for(auto& lhs : hpt1.vertices()) {
		for(auto& rhs : hpt2.vertices()) {
	//		std::cout << "Test: " << vector_t<TypeParam>(TypeParam(0.99)*lhs+rhs).transpose() << std::endl;
			EXPECT_TRUE(res.contains(TypeParam(0.99)*lhs+rhs));
		}
	}

	//std::cout << "######" << std::endl;

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

	std::cout << "A: " << hpt1 << std::endl;
	std::cout << "B: " << hpt2 << std::endl;
	std::cout << "Res: " << result << std::endl;


	for(auto& plane : result.constraints()) {
		EXPECT_TRUE(hpt1.hasConstraint(plane) || hpt2.hasConstraint(plane));
	}

	std::cout<< "Part 2 starting: "	<< std::endl;
	std::vector<Hyperplane<TypeParam>> ps3;
	Hyperplane<TypeParam> p01 = Hyperplane<TypeParam>({0,-1,0},1);
	Hyperplane<TypeParam> p02 = Hyperplane<TypeParam>({0,1,0},3);
	Hyperplane<TypeParam> p03 = Hyperplane<TypeParam>({-1,0,0},1);
	Hyperplane<TypeParam> p04 = Hyperplane<TypeParam>({1,0,0},3);
	Hyperplane<TypeParam> p05 = Hyperplane<TypeParam>({0,0,-1},1);
	Hyperplane<TypeParam> p06 = Hyperplane<TypeParam>({0,0,1},3);

	ps3.push_back(p01);
	ps3.push_back(p02);
	ps3.push_back(p03);
	ps3.push_back(p04);
	ps3.push_back(p05);
	ps3.push_back(p06);

	HPolytope<TypeParam> pt3 = HPolytope<TypeParam>(ps3);

	std::vector<Hyperplane<TypeParam>> ps4;
	Hyperplane<TypeParam> p07 = Hyperplane<TypeParam>({0,-1,0},3);
	Hyperplane<TypeParam> p08 = Hyperplane<TypeParam>({0,1,0},5);
	Hyperplane<TypeParam> p09 = Hyperplane<TypeParam>({-1,0,0},3);
	Hyperplane<TypeParam> p10 = Hyperplane<TypeParam>({1,0,0},5);


	ps4.push_back(p05);
	ps4.push_back(p06);
	ps4.push_back(p07);
	ps4.push_back(p08);
	ps4.push_back(p09);
	ps4.push_back(p10);


	HPolytope<TypeParam> pt4 = HPolytope<TypeParam>(ps4);

	HPolytope<TypeParam> res2 = pt3.intersect(pt4);

	for(auto& vertex : res2.vertices()) {
	  EXPECT_TRUE(pt3.contains(vertex));
	  EXPECT_TRUE(pt4.contains(vertex));
	}

	HPolytope<TypeParam> res3 = res2.intersect(HPolytope<TypeParam>::Empty());

	EXPECT_TRUE(res3.empty());
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
