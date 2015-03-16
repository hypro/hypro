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
	Hyperplane<TypeParam> empty = Hyperplane<TypeParam>();
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
