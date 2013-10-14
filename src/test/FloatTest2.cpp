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
	
}

TEST(FloatTest, SpecialOperators)
{
	
}

TEST(FloatTest, ConversionOperators)
{
}
