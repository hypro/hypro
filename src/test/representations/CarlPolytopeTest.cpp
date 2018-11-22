
#include "../defines.h"
#include "../../hypro/representations/GeometricObject.h"
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

TYPED_TEST(CarlPolytopeTest, Intersection)
{
    carl::Interval<TypeParam> i1{1,2};
    carl::Interval<TypeParam> i2{2,3};
    std::vector<carl::Interval<TypeParam>> intervals;
    intervals.emplace_back(i1);
    intervals.emplace_back(i2);

    hypro::CarlPolytope<TypeParam> p1{intervals};

    carl::Interval<TypeParam> i3{1,1};
    carl::Interval<TypeParam> i4{2,5};
    intervals.clear();
    intervals.emplace_back(i3);
    intervals.emplace_back(i4);

    hypro::CarlPolytope<TypeParam> p2{intervals};

    hypro::CarlPolytope<TypeParam> result = p1.intersect(p2);
    hypro::CarlPolytope<TypeParam> result2 = p2.intersect(p1);

    EXPECT_EQ(result.getFormula(), result2.getFormula());
}

TYPED_TEST(CarlPolytopeTest, GetHalfspaces)
{
    carl::Interval<TypeParam> i1 = carl::Interval<TypeParam>{1,2};
    carl::Interval<TypeParam> i2 = carl::Interval<TypeParam>{1,2};
    std::vector<carl::Interval<TypeParam>> intervals;
    intervals.push_back(i1);
    intervals.push_back(i2);

    hypro::CarlPolytope<TypeParam> c1{intervals};

    auto hspVector = c1.getHalfspaces();

    EXPECT_EQ(std::size_t(4),hspVector.size());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({1,0},2)) != hspVector.end());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({-1,0},-1)) != hspVector.end());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({0,1},2)) != hspVector.end());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({0,-1},-1)) != hspVector.end());
}

TYPED_TEST(CarlPolytopeTest, AddConstraint)
{
    carl::Interval<TypeParam> i1 = carl::Interval<TypeParam>{1,2};
    carl::Interval<TypeParam> i2 = carl::Interval<TypeParam>{1,2};
    std::vector<carl::Interval<TypeParam>> intervals;
    intervals.push_back(i1);
    intervals.push_back(i2);

    hypro::CarlPolytope<TypeParam> c1{intervals};

    auto hspVector = c1.getHalfspaces();

    EXPECT_EQ(std::size_t(4),hspVector.size());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({1,0},2)) != hspVector.end());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({-1,0},-1)) != hspVector.end());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({0,1},2)) != hspVector.end());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({0,-1},-1)) != hspVector.end());
    EXPECT_EQ(std::size_t(2),c1.dimension());

    // add constraints which introduce a new variable - the dimension should be increased.
    carl::Variable t = carl::freshRealVariable("t");
    c1.addConstraint(hypro::ConstraintT<TypeParam>(hypro::PolyT<TypeParam>(t), carl::Relation::GEQ));
    EXPECT_EQ(std::size_t(3),c1.dimension());

    hspVector = c1.getHalfspaces();

    EXPECT_EQ(std::size_t(5),hspVector.size());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({1,0,0},2)) != hspVector.end());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({-1,0,0},-1)) != hspVector.end());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({0,1,0},2)) != hspVector.end());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({0,-1,0},-1)) != hspVector.end());
    EXPECT_TRUE(std::find(hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>({0,0,-1},0)) != hspVector.end());
}
