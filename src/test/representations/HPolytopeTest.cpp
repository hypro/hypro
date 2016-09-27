#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/representations/GeometricObject.h"

using namespace hypro;


template<typename Number>
class HPolytopeTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		// A rectangle
		Halfspace<Number> hp1({Number(1),Number(0)},Number(2));
		Halfspace<Number> hp2({Number(0),Number(1)},Number(2));
		Halfspace<Number> hp3({Number(-1),Number(0)},Number(2));
		Halfspace<Number> hp4({Number(0),-Number(1)},Number(2));

		// A triangle
		Halfspace<Number> hp5({Number(1),Number(1)},Number(1));
		Halfspace<Number> hp6({Number(-1),Number(1)},Number(1));
		Halfspace<Number> hp7({Number(0),Number(-1)},Number(1));

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

	typename HPolytopeT<Number,Converter<Number>>::HalfspaceVector planes1;
	typename HPolytopeT<Number,Converter<Number>>::HalfspaceVector planes2;
};

TYPED_TEST(HPolytopeTest, Constructor)
{
	HPolytope<TypeParam> aHPolytope = HPolytope<TypeParam>();
	HPolytope<TypeParam> anotherHPolytope = HPolytope<TypeParam>(this->planes1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->planes2);
	HPolytope<TypeParam> empt = HPolytope<TypeParam>::Empty();
	EXPECT_TRUE(empt.empty());

	HPolytope<TypeParam> copyAssignment = HPolytope<TypeParam>(anotherHPolytope);

	//VPolytope<TypeParam> alien;
	//alien.insert(Point<TypeParam>({5,3,2}));
	//alien.insert(Point<TypeParam>({7,5,-1}));
//
	//HPolytope<TypeParam> alienPolytope(alien);

	SUCCEED();
}

TYPED_TEST(HPolytopeTest, Access)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	EXPECT_EQ((unsigned) 2, hpt1.dimension());
	EXPECT_EQ((unsigned) 4, hpt1.size());
	//EXPECT_FALSE(hpt1.reduced());
	//polytope::Fan<TypeParam> tmpFan = hpt1.fan();

	typename HPolytope<TypeParam>::HalfspaceVector planes =  hpt1.constraints();
	for(auto& constraint : planes) {
		EXPECT_TRUE(hpt1.hasConstraint(constraint));
	}
}

TYPED_TEST(HPolytopeTest, Swap)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->planes2);

	typename HPolytope<TypeParam>::HalfspaceVector planes =  hpt1.constraints();

	swap(hpt1,hpt2);

	for(auto& constraint : planes) {
		EXPECT_TRUE(hpt2.hasConstraint(constraint));
	}
}

////////////TODO: change this test to work with a 3D HPolytope<TypeParam>
TYPED_TEST(HPolytopeTest, Corners)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	HPolytope<TypeParam> hpt2 = HPolytope<TypeParam>(this->planes2);

	typename std::vector<Point<TypeParam>> corners = hpt1.vertices();
	for(const auto& corner : corners) {
		EXPECT_TRUE(hpt1.isExtremePoint(corner));
	}

	corners = hpt2.vertices();

	for(const auto& corner : corners) {
		EXPECT_TRUE(hpt2.isExtremePoint(corner));
	}

	// test extremepoints
	vector_t<TypeParam> p1(2);
	p1(0) = 2;
	p1(1) = 0;
	EXPECT_FALSE(hpt1.isExtremePoint(p1));

	// test overapproximation
	HPolytope<TypeParam> reproduction(corners);

	EXPECT_TRUE(hpt2.contains(reproduction));
}


TYPED_TEST(HPolytopeTest, Insertion)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	Halfspace<TypeParam> p1({TypeParam(1),TypeParam(1)}, TypeParam(4));
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

	std::vector<Halfspace<TypeParam>> ps3;
	Halfspace<TypeParam> p01 = Halfspace<TypeParam>({TypeParam(0),TypeParam(-1),TypeParam(0)},TypeParam(1));
	Halfspace<TypeParam> p02 = Halfspace<TypeParam>({TypeParam(0),TypeParam(1),TypeParam(0)},TypeParam(-3));
	Halfspace<TypeParam> p03 = Halfspace<TypeParam>({TypeParam(-1),TypeParam(0),TypeParam(0)},TypeParam(1));
	Halfspace<TypeParam> p04 = Halfspace<TypeParam>({TypeParam(1),TypeParam(0),TypeParam(0)},TypeParam(-3));
	Halfspace<TypeParam> p05 = Halfspace<TypeParam>({TypeParam(0),TypeParam(0),TypeParam(-1)},TypeParam(1));
	Halfspace<TypeParam> p06 = Halfspace<TypeParam>({TypeParam(0),TypeParam(0),TypeParam(1)},TypeParam(-3));

	ps3.push_back(p01);
	ps3.push_back(p02);
	ps3.push_back(p03);
	ps3.push_back(p04);
	ps3.push_back(p05);
	ps3.push_back(p06);

	HPolytope<TypeParam> pt3 = HPolytope<TypeParam>(ps3);

	std::vector<Halfspace<TypeParam>> ps4;
	Halfspace<TypeParam> p07 = Halfspace<TypeParam>({TypeParam(0),TypeParam(-1),TypeParam(0)},TypeParam(3));
	Halfspace<TypeParam> p08 = Halfspace<TypeParam>({TypeParam(0),TypeParam(1),TypeParam(0)},TypeParam(-5));
	Halfspace<TypeParam> p09 = Halfspace<TypeParam>({TypeParam(-1),TypeParam(0),TypeParam(0)},TypeParam(3));
	Halfspace<TypeParam> p10 = Halfspace<TypeParam>({TypeParam(1),TypeParam(0),TypeParam(0)},TypeParam(-5));


	ps4.push_back(p05);
	ps4.push_back(p06);
	ps4.push_back(p07);
	ps4.push_back(p08);
	ps4.push_back(p09);
	ps4.push_back(p10);


	HPolytope<TypeParam> pt4 = HPolytope<TypeParam>(ps4);

	HPolytope<TypeParam> res2 = pt3.unite(pt4);
	for(auto& vertex : pt3.vertices()) {
	  EXPECT_TRUE(res2.contains(vertex));
	}
	for(auto& vertex : pt4.vertices()) {
	  EXPECT_TRUE(res2.contains(vertex));
	}

	HPolytope<TypeParam> res3 = res2.unite(HPolytope<TypeParam>());
	for(auto& vertex : res3.vertices()) {
	  EXPECT_TRUE(res2.contains(vertex));
	}
	for(auto& vertex : res2.vertices()) {
	  EXPECT_TRUE(res3.contains(vertex));
	}  //still needs HPolytope<TypeParam> to VPolytope conversion for higher dimensions !!!!
}

TYPED_TEST(HPolytopeTest, Evaluate)
{
	matrix_t<TypeParam> A(4,2);
	A(0,0) = 1;			//     1    1
	A(0,1) = 1;			//     1    0
	A(1,0) = 1;	        //     0    1
	A(1,1) = 0;         //     0   -1
	A(2,0) = 0;
	A(2,1) = 1;
	A(3,0) = 0;
	A(3,1) = -1;
	vector_t<TypeParam> b(4);
	b(0) = 0;
	b(1) = 1;
	b(2) = 0;
	b(3) = 1;


	HPolytope<TypeParam> poly = HPolytope<TypeParam>(A,b);
	vector_t<TypeParam> dir(2);
	dir(0) = 1;
	dir(1) = 0;
	EvaluationResult<TypeParam> res = poly.evaluate(dir);
	ASSERT_EQ(SOLUTION::FEAS, res.errorCode);
	ASSERT_EQ(TypeParam(1), res.supportValue);
}

TYPED_TEST(HPolytopeTest, LinearTransformation)
{
	HPolytope<TypeParam> hpt1 = HPolytope<TypeParam>(this->planes1);
	matrix_t<TypeParam> A(2,2);
	A(0,0) = 1;
	A(0,1) = 2;
	A(1,0) = 3;
	A(1,1) = 4;

	HPolytope<TypeParam> res = hpt1.linearTransformation(A, vector_t<TypeParam>::Zero(A.rows()));
	VPolytope<TypeParam> test(hpt1.vertices());
	test = test.linearTransformation(A,vector_t<TypeParam>::Zero(A.rows()));

	std::cout << "Res vertices: " << std::endl;
	for(const auto& vertex : res.vertices()) {
		std::cout << vertex << std::endl;
	}

	std::cout << "Test vertices: " << std::endl;
	for(const auto& vertex : test.vertices()) {
		std::cout << vertex << std::endl;
	}

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

	for(auto& lhs : hpt1.vertices()) {
		for(auto& rhs : hpt2.vertices()) {
			EXPECT_TRUE(res.contains(lhs+rhs)); // Todo: Make this more restrictive
		}
	}

	for(auto& lhs : hpt1.vertices()) {
		for(auto& rhs : hpt2.vertices()) {
			EXPECT_TRUE(res.contains(TypeParam(carl::rationalize<TypeParam>(0.99))*lhs+rhs));
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

	std::vector<Halfspace<TypeParam>> ps3;
	Halfspace<TypeParam> p01 = Halfspace<TypeParam>({TypeParam(0),TypeParam(-1),TypeParam(0)},TypeParam(1));
	Halfspace<TypeParam> p02 = Halfspace<TypeParam>({TypeParam(0),TypeParam(1),TypeParam(0)},TypeParam(3));
	Halfspace<TypeParam> p03 = Halfspace<TypeParam>({TypeParam(-1),TypeParam(0),TypeParam(0)},TypeParam(1));
	Halfspace<TypeParam> p04 = Halfspace<TypeParam>({TypeParam(1),TypeParam(0),TypeParam(0)},TypeParam(3));
	Halfspace<TypeParam> p05 = Halfspace<TypeParam>({TypeParam(0),TypeParam(0),TypeParam(-1)},TypeParam(1));
	Halfspace<TypeParam> p06 = Halfspace<TypeParam>({TypeParam(0),TypeParam(0),TypeParam(1)},TypeParam(3));

	ps3.push_back(p01);
	ps3.push_back(p02);
	ps3.push_back(p03);
	ps3.push_back(p04);
	ps3.push_back(p05);
	ps3.push_back(p06);

	HPolytope<TypeParam> pt3 = HPolytope<TypeParam>(ps3);

	std::vector<Halfspace<TypeParam>> ps4;
	Halfspace<TypeParam> p07 = Halfspace<TypeParam>({TypeParam(0),TypeParam(-1),TypeParam(0)},TypeParam(3));
	Halfspace<TypeParam> p08 = Halfspace<TypeParam>({TypeParam(0),TypeParam(1),TypeParam(0)},TypeParam(5));
	Halfspace<TypeParam> p09 = Halfspace<TypeParam>({TypeParam(-1),TypeParam(0),TypeParam(0)},TypeParam(3));
	Halfspace<TypeParam> p10 = Halfspace<TypeParam>({TypeParam(1),TypeParam(0),TypeParam(0)},TypeParam(5));


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

	Point<TypeParam> p1({TypeParam(0), TypeParam(0)});
	EXPECT_TRUE(hpt1.contains(p1));

	Point<TypeParam> p2({carl::rationalize<TypeParam>(1.5), carl::rationalize<TypeParam>(1.5)});
	EXPECT_TRUE(hpt1.contains(p2));

	Point<TypeParam> p3({TypeParam(-2),TypeParam(0)});
	EXPECT_TRUE(hpt1.contains(p3));

	Point<TypeParam> p4({TypeParam(2), TypeParam(2)});
	EXPECT_TRUE(hpt1.contains(p4));

	Point<TypeParam> p5({carl::rationalize<TypeParam>(2.1), TypeParam(0)});
	EXPECT_FALSE(hpt1.contains(p5));
}
