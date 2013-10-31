#include "gtest/gtest.h"
#include "defines.h"
#include "../lib/numbers/FLOAT_T.h"
#include <mpfr.h>

TEST(doubleFloatTest, Constructor)
{ 
    // double constructor tests
    double dVal = 4;
    ASSERT_NO_THROW(hypro::FLOAT_T<double> hf1 = hypro::FLOAT_T<double>(dVal));
    dVal = 0;
    EXPECT_EQ(0, hypro::FLOAT_T<double>(dVal).getValue());
    
    // float constructor tests
    float fVal = 4;
    ASSERT_NO_THROW(hypro::FLOAT_T<double> hf1 = hypro::FLOAT_T<double>(fVal));
    fVal = 0;
    EXPECT_EQ(0, hypro::FLOAT_T<double>(fVal).getValue());
    
    // integer constructor tests
    int iVal = 4;
    ASSERT_NO_THROW(hypro::FLOAT_T<double> hf1 = hypro::FLOAT_T<double>(iVal));
    iVal = 0;
    EXPECT_EQ(0, hypro::FLOAT_T<double>(iVal).getValue());
    
    // mpfr constructor tests
    dVal = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899;
    hypro::FLOAT_T<double> hf1 = hypro::FLOAT_T<double>(dVal);
    
    // copy constructor test
    ASSERT_EQ(hf1, hypro::FLOAT_T<double>(hf1));
    SUCCEED();
}

TEST(doubleFloatTest, BooleanOperators)
{
}

TEST(doubleFloatTest, Addition)
{
    
}

TEST(doubleFloatTest, Subtraction)
{
    
}

TEST(doubleFloatTest, Multiplication)
{
    double v1 = 4;
    hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
    double v2 = 3;
    hypro::FLOAT_T<double> f2 = hypro::FLOAT_T<double>(v2);
    
    hypro::FLOAT_T<double> result;
    
    result = f1.mul(f2,hypro::N);
    std::cout << f1 << std::endl;
}

TEST(doubleFloatTest, Division)
{
    
}

TEST(doubleFloatTest, Roots)
{
	
}

TEST(doubleFloatTest, ConversionOperators)
{
}

TEST(doubleFloatTest, Precision)
{}
