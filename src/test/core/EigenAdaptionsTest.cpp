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
