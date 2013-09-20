#include "gtest/gtest.h"
#include "mpfr.h"
#include "numbers/mpfr_wrapper_t.h"
#include "numbers/HYPRO_FLOAT_T.h"

using namespace hypro;

TEST(Numbers, FirstTest)
{ 
    mpfr_wrapper_t mpfrFloat(1);
    HYPRO_FLOAT_T<mpfr_wrapper_t> kram(mpfrFloat);
    std::cout << "Ping" << std::endl;
    EXPECT_EQ(true,true);
}

TEST(Numbers, Constructor)
{ 
    mpfr_wrapper_t mpfrFloat(1);
    EXPECT_EQ(true,true);
}