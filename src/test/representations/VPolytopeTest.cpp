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

        points1.insert(p1);
        points1.insert(p2);
        points1.insert(p3);
        points1.insert(p4);
		
        points2.insert(p5);
        points2.insert(p6);
        points2.insert(p7);
        points2.insert(p8);
    }
	
    virtual void TearDown()
    {
    }

    typename VPolytope<Number>::vertexSet points1;
    typename VPolytope<Number>::vertexSet points2;
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
}

TYPED_TEST(VPolytopeTest, Insertion)
{
}

TYPED_TEST(VPolytopeTest, Union)
{
}

TYPED_TEST(VPolytopeTest, LinearTransformation)
{

}

TYPED_TEST(VPolytopeTest, MinkowskiSum)
{
    //VPolytope<number_t> result;
}

TYPED_TEST(VPolytopeTest, Intersection)
{	
    VPolytope<TypeParam> vpt1 = VPolytope<TypeParam>(this->points1);
    VPolytope<TypeParam> vpt2 = VPolytope<TypeParam>(this->points2);
	
	std::cout << "vpt1: " << std::endl << vpt1 << std::endl << "vpt2: " << std::endl << vpt2 << std::endl;
	
	VPolytope<TypeParam> result = vpt1.intersect(vpt2);
	
	std::cout << "result: " << std::endl << result << std::endl;
}

TYPED_TEST(VPolytopeTest, Membership)
{
    //Point<number_t> p;
    //p.setCoordinate(x, 4);
    //p.setCoordinate(y, 2);
}