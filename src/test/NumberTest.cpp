#include "gtest/gtest.h"
#include "mpfr.h"

using namespace hypro;

TEST(Numbers, FirstTest)
{ 
    EXPECT_EQ(true,true);
}

TEST(Numbers, Constructor)
{ 
    mpfr_wrapper_t mpfrFloat(1);
    EXPECT_EQ(true,true);
}