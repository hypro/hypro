#include "gtest/gtest.h"
#include "../defines.h"
#include "util/adaptions_eigen/adaptions_eigen.h"

template<typename Number>
class EigenAdaptionsTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {}

    virtual void TearDown()
    {}
};

TYPED_TEST(EigenAdaptionsTest, reduceNumberRepresentation)
{
	// TODO: finish vector rounding.
}

TYPED_TEST(EigenAdaptionsTest, createCode)
{
	hypro::matrix_t<TypeParam> a = hypro::matrix_t<TypeParam>(2,2);
	a << 1,2,3,4;

	std::string out = hypro::createCode(a,0);
	std::cout << out << std::endl;
}
