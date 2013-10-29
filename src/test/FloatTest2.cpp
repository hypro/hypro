#include "gtest/gtest.h"
#include "defines.h"
#include "../lib/numbers/FLOAT_T.h"

TEST(FloatTest, Constructor)
{ 
    double val = 4;
    
    hypro::FLOAT_T<mpfr_t> testFloat = hypro::FLOAT_T<mpfr_t>(val, hypro::N);
    std::cout << testFloat << std::endl;
}

TEST(FloatTest, BooleanOperators)
{
}

TEST(FloatTest, ArithmeticOperators)
{
    double v1 = 4;
    hypro::FLOAT_T<mpfr_t> f1 = hypro::FLOAT_T<mpfr_t>(v1, hypro::N);
    double v2 = 3;
    hypro::FLOAT_T<mpfr_t> f2 = hypro::FLOAT_T<mpfr_t>(v2, hypro::N);
    
    hypro::FLOAT_T<mpfr_t> result;
    
    result = f1.mul(f2,hypro::N);
    std::cout << f1 << std::endl;
}

TEST(FloatTest, SpecialOperators)
{
	
}

TEST(FloatTest, ConversionOperators)
{
}
