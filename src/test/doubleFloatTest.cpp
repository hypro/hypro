#include "gtest/gtest.h"
#include "defines.h"

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
    //ASSERT_EQ(hf1, hypro::FLOAT_T<double>(hf1));
}

TEST(doubleFloatTest, BooleanOperators)
{
	double v1 = 7;
    hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
    double v2 = 2;
    hypro::FLOAT_T<double> f2 = hypro::FLOAT_T<double>(v2);
    double v3 = 7;
    hypro::FLOAT_T<double> f3 = hypro::FLOAT_T<double>(v3);
    
    ASSERT_GT(f1, f2);
    ASSERT_LT(f2, f1);
    ASSERT_NE(f1, f2);
    ASSERT_GE(f1, f3);
    ASSERT_LE(f1, f3);
    ASSERT_EQ(f1, f3);
}

TEST(doubleFloatTest, Addition)
{
	double v1 = 7;
    hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
    double v2 = 2;
    hypro::FLOAT_T<double> f2 = hypro::FLOAT_T<double>(v2);
    
    double vResult = 9;
    hypro::FLOAT_T<double> result = hypro::FLOAT_T<double>(vResult);
    
    f1.add_assign(f2, hypro::HYPRO_RNDN);
    ASSERT_EQ(result, f1);
}

TEST(doubleFloatTest, Subtraction)
{
	double v1 = 9;
    hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
    double v2 = 5;
    hypro::FLOAT_T<double> f2 = hypro::FLOAT_T<double>(v2);
    
    double vResult = 4;
    hypro::FLOAT_T<double> result = hypro::FLOAT_T<double>(vResult);
    
    f1.sub_assign(f2, hypro::HYPRO_RNDN);
    ASSERT_EQ(result, f1);
}

TEST(doubleFloatTest, Multiplication)
{
    double v1 = 4;
    hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
    double v2 = 3;
    hypro::FLOAT_T<double> f2 = hypro::FLOAT_T<double>(v2);
    
    double vResult = 12;
    hypro::FLOAT_T<double> result = hypro::FLOAT_T<double>(vResult);
    
    f1.mul_assign(f2, hypro::HYPRO_RNDN);
    ASSERT_EQ(result, f1);
}

TEST(doubleFloatTest, Division)
{
    double v1 = 8;
    hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
    double v2 = 4;
    hypro::FLOAT_T<double> f2 = hypro::FLOAT_T<double>(v2);
    
    double vResult = 2;
    hypro::FLOAT_T<double> result = hypro::FLOAT_T<double>(vResult);
    
    f1.div_assign(f2, hypro::HYPRO_RNDN);
    ASSERT_EQ(result, f1);
    
    v2 = 0;
    f2 = hypro::FLOAT_T<double>(v2);
    
    ASSERT_THROW(f1.div_assign(f2, hypro::HYPRO_RNDN));
}

TEST(doubleFloatTest, Roots)
{
	double v1 = 16;
	hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
	
	double vResult = 4;
	hypro::FLOAT_T<double> result = hypro::FLOAT_T<double>(vResult);
	
	f1.sqrt_assign();
	ASSERT_EQ(result, f1);
	
	v1 = 27;
	f1 = hypro::FLOAT_T<double>(v1);
	
	vResult = 3;
	result = hypro::FLOAT_T<double>(vResult);
	
	f1.cbrt_assign();
	ASSERT_EQ(result, f1);
}

TEST(doubleFloatTest, ConversionOperators)
{
}

TEST(doubleFloatTest, Precision)
{
}
