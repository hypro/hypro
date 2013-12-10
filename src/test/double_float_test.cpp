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

/*
 * Test the following operations
 * 7 > 2
 * 2 < 7
 * 7 != 2
 * 7 >= 7
 * 7 <= 7
 * 7 == 7
 */
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

/*
 * Test the following operations
 * 7 + 2 = 9
 * 7 + -3 = 4
 * 7 + 0 = 7
 * 7 + -0 = 7
 */
TEST(doubleFloatTest, Addition)
{
    double v1 = 7;
    double v2 = 2;
    double v3 = 7;
    double v4 = -3;
    double v5 = 7;
    double v6 = 0;
    double v7 = 7;
    double v8 = -0;
    double vResult1 = 9;
    double vResult2 = 4;
    double vResult3 = 7;
    double vResult4 = 7;
    
    hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
    hypro::FLOAT_T<double> f2 = hypro::FLOAT_T<double>(v2);
    hypro::FLOAT_T<double> f3 = hypro::FLOAT_T<double>(v3);
    hypro::FLOAT_T<double> f4 = hypro::FLOAT_T<double>(v4);
    hypro::FLOAT_T<double> f5 = hypro::FLOAT_T<double>(v5);
    hypro::FLOAT_T<double> f6 = hypro::FLOAT_T<double>(v6);
    hypro::FLOAT_T<double> f7 = hypro::FLOAT_T<double>(v7);
    hypro::FLOAT_T<double> f8 = hypro::FLOAT_T<double>(v8);
    hypro::FLOAT_T<double> result1 = hypro::FLOAT_T<double>(vResult1);
    hypro::FLOAT_T<double> result2 = hypro::FLOAT_T<double>(vResult2);
    hypro::FLOAT_T<double> result3 = hypro::FLOAT_T<double>(vResult3);
    hypro::FLOAT_T<double> result4 = hypro::FLOAT_T<double>(vResult4);
    
    
    f1.add_assign(f2, hypro::HYPRO_RNDN);
    ASSERT_EQ(result1, f1);
    
    f3.add_assign(f4, hypro::HYPRO_RNDN);
    ASSERT_EQ(result2, f3);
    
    f5.add_assign(f6, hypro::HYPRO_RNDN);
    ASSERT_EQ(result3, f5);
    
    f7.add_assign(f8, hypro::HYPRO_RNDN);
    ASSERT_EQ(result4, f7);
}

/*
 * Test the following operations
 * 9 - 5 = 4
 * 9 - -4 = 13
 * 9 - 0 = 9
 * 9 - -0 = 9
 */
TEST(doubleFloatTest, Subtraction)
{
    double v1 = 9;
    double v2 = 5;
    double v3 = 9;
    double v4 = -4;
    double v5 = 9;
    double v6 = 0;
    double v7 = 9;
    double v8 = -0;
    double vResult1 = 4;
    double vResult2 = 13;
    double vResult3 = 9;
    double vResult4 = 9;
    
    hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
    hypro::FLOAT_T<double> f2 = hypro::FLOAT_T<double>(v2);
    hypro::FLOAT_T<double> f3 = hypro::FLOAT_T<double>(v3);
    hypro::FLOAT_T<double> f4 = hypro::FLOAT_T<double>(v4);
    hypro::FLOAT_T<double> f5 = hypro::FLOAT_T<double>(v5);
    hypro::FLOAT_T<double> f6 = hypro::FLOAT_T<double>(v6);
    hypro::FLOAT_T<double> f7 = hypro::FLOAT_T<double>(v7);
    hypro::FLOAT_T<double> f8 = hypro::FLOAT_T<double>(v8);
    hypro::FLOAT_T<double> result1 = hypro::FLOAT_T<double>(vResult1);
    hypro::FLOAT_T<double> result2 = hypro::FLOAT_T<double>(vResult2);
    hypro::FLOAT_T<double> result3 = hypro::FLOAT_T<double>(vResult3);
    hypro::FLOAT_T<double> result4 = hypro::FLOAT_T<double>(vResult4);
    
    f1.sub_assign(f2, hypro::HYPRO_RNDN);
    ASSERT_EQ(result1, f1);
    
    f3.sub_assign(f4, hypro::HYPRO_RNDN);
    ASSERT_EQ(result2, f3);
    
    f5.sub_assign(f6, hypro::HYPRO_RNDN);
    ASSERT_EQ(result3, f5);
    
    f7.sub_assign(f8, hypro::HYPRO_RNDN);
    ASSERT_EQ(result4, f7);
}

/*
 * Test the following operations
 * 4 * 3 = 12
 * 4 * -5 = -20
 * 4 * 0 = 0
 * 4 * -0 = 0
 */
TEST(doubleFloatTest, Multiplication)
{
    double v1 = 4;
    double v2 = 3;
    double v3 = 4;
    double v4 = -5;
    double v5 = 4;
    double v6 = 0;
    double v7 = 4;
    double v8 = -0;
    double vResult1 = 12;
    double vResult2 = -20;
    double vResult3 = 0;
    double vResult4 = 0;
    
    hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
    hypro::FLOAT_T<double> f2 = hypro::FLOAT_T<double>(v2);
    hypro::FLOAT_T<double> f3 = hypro::FLOAT_T<double>(v3);
    hypro::FLOAT_T<double> f4 = hypro::FLOAT_T<double>(v4);
    hypro::FLOAT_T<double> f5 = hypro::FLOAT_T<double>(v5);
    hypro::FLOAT_T<double> f6 = hypro::FLOAT_T<double>(v6);
    hypro::FLOAT_T<double> f7 = hypro::FLOAT_T<double>(v7);
    hypro::FLOAT_T<double> f8 = hypro::FLOAT_T<double>(v8);
    hypro::FLOAT_T<double> result1 = hypro::FLOAT_T<double>(vResult1);
    hypro::FLOAT_T<double> result2 = hypro::FLOAT_T<double>(vResult2);
    hypro::FLOAT_T<double> result3 = hypro::FLOAT_T<double>(vResult3);
    hypro::FLOAT_T<double> result4 = hypro::FLOAT_T<double>(vResult4);
    
    f1.mul_assign(f2, hypro::HYPRO_RNDN);
    ASSERT_EQ(result1, f1);
    
    f3.mul_assign(f4, hypro::HYPRO_RNDN);
    ASSERT_EQ(result2, f3);
    
    f5.mul_assign(f6, hypro::HYPRO_RNDN);
    ASSERT_EQ(result3, f5);
    
    f7.mul_assign(f8, hypro::HYPRO_RNDN);
    ASSERT_EQ(result4, f7);
}

/*
 * Test the following operations
 * 8 / 4 = 2
 * 8 / -2 = -4
 * -8 / -4 = 2
 * 8 / 0 throws
 */
TEST(doubleFloatTest, Division)
{
    double v1 = 8;
    double v2 = 4;
    double v3 = 8;
    double v4 = -2;
    double v5 = -8;
    double v6 = -4;
    double v7 = 8;
    double v8 = 0;
    double vResult1 = 2;
    double vResult2 = -4;
    double vResult3 = 2;
    
    hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
    hypro::FLOAT_T<double> f2 = hypro::FLOAT_T<double>(v2);
    hypro::FLOAT_T<double> f3 = hypro::FLOAT_T<double>(v3);
    hypro::FLOAT_T<double> f4 = hypro::FLOAT_T<double>(v4);
    hypro::FLOAT_T<double> f5 = hypro::FLOAT_T<double>(v5);
    hypro::FLOAT_T<double> f6 = hypro::FLOAT_T<double>(v6);
    hypro::FLOAT_T<double> f7 = hypro::FLOAT_T<double>(v7);
    hypro::FLOAT_T<double> f8 = hypro::FLOAT_T<double>(v8);
    hypro::FLOAT_T<double> result1 = hypro::FLOAT_T<double>(vResult1);
    hypro::FLOAT_T<double> result2 = hypro::FLOAT_T<double>(vResult2);
    hypro::FLOAT_T<double> result3 = hypro::FLOAT_T<double>(vResult3);
    
    f1.div_assign(f2, hypro::HYPRO_RNDN);
    ASSERT_EQ(result1, f1);
    
    f3.div_assign(f4 hypro::HYPRO_RNDN);
    ASSERT_EQ(result1, f3);
    
    f5.div_assign(f6, hypro::HYPRO_RNDN);
    ASSERT_EQ(result1, f5);
    
    // @todo specifiy exception
    ASSERT_ANY_THROW(f7.div_assign(f8, hypro::HYPRO_RNDN));
}

/*
 * Test the following operations
 * sqrt 16 = 4
 * cbrt 27 = 3
 * root 256 8 = 2
 * sqrt -7 throws
 */
TEST(doubleFloatTest, Roots)
{
    double v1 = 16;
    double v2 = 27;
    double v3 = 256;
    double v4 = -7;
    double vResult1 = 4;
    double vResult2 = 3;
    double vResult3 = 2;
    
    unsigned long int i1 = 8;
    hypro::FLOAT_T<double> f1 = hypro::FLOAT_T<double>(v1);
    hypro::FLOAT_T<double> f2 = hypro::FLOAT_T<double>(v2);
    hypro::FLOAT_T<double> f3 = hypro::FLOAT_T<double>(v3);
    hypro::FLOAT_T<double> f4 = hypro::FLOAT_T<double>(v4);
    hypro::FLOAT_T<double> result1 = hypro::FLOAT_T<double>(vResult1);
    hypro::FLOAT_T<double> result2 = hypro::FLOAT_T<double>(vResult2);
    hypro::FLOAT_T<double> result3 = hypro::FLOAT_T<double>(vResult3);

    f1.sqrt_assign(hypro::HYPRO_RNDN);
    ASSERT_EQ(result1, f1);

    f2.cbrt_assign(hypro::HYPRO_RNDN);
    ASSERT_EQ(result2, f1);

    f3.root_assign(i1, hypro::HYPRO_RNDN);
    ASSERT_EQ(result3, i1);
    
    // @todo specifiy exception
    ASSERT_ANY_THROW(f4.sqrt_assign(hypro::HYPRO_RNDN));
}

TEST(doubleFloatTest, ConversionOperators)
{
}

TEST(doubleFloatTest, Precision)
{
}
