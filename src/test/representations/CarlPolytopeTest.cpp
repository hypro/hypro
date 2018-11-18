
#include "../defines.h"
#include "../../hypro/representations/Polytopes/carlPolytope/carlPolytope.h"
#include "gtest/gtest.h"


template<typename Number>
class CarlPolytopeTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {
    }

};

TYPED_TEST(CarlPolytopeTest, Constructor)
{
	hypro::CarlPolytope<TypeParam> p1{};

    carl::Interval<TypeParam> i1{1,2};
    carl::Interval<TypeParam> i2{2,3};
    std::vector<carl::Interval<TypeParam>> intervals;
    intervals.emplace_back(i1);
    intervals.emplace_back(i2);

    hypro::CarlPolytope<TypeParam> p2{intervals};

    hypro::matrix_t<TypeParam> constraints = hypro::matrix_t<TypeParam>(4,2);
    hypro::vector_t<TypeParam> constants = hypro::vector_t<TypeParam>(4);
    constraints << 1,0,
                    -1,0,
                    0,1,
                    0,-1;
    constants << 1,2,2,2;

    hypro::CarlPolytope<TypeParam> p3{constraints,constants};

}
