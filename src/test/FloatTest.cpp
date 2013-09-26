#include "gtest/gtest.h"
#include "defines.h"

TEST(FloatTest, Constructor)
{ 
    hypro_float_t testFloat(5);
    ASSERT_EQ(testFloat, hypro_float_t(5));
}

TEST(FloatTest, BooleanOperators)
{
	ASSERT_TRUE(hypro_float_t(5) == hypro_float_t(5));
	ASSERT_FALSE(hypro_float_t(3) == hypro_float_t(7));
	
	ASSERT_TRUE(hypro_float_t(4) != hypro_float_t(6));
	ASSERT_FALSE(hypro_float_t(3) != hypro_float_t(3));
	
	ASSERT_TRUE(hypro_float_t(9) > hypro_float_t(5));
	ASSERT_FALSE(hypro_float_t(3) > hypro_float_t(7));
	
	ASSERT_TRUE(hypro_float_t(2) < hypro_float_t(6));
	ASSERT_FALSE(hypro_float_t(8) < hypro_float_t(1));
	
	ASSERT_TRUE(hypro_float_t(3) <= hypro_float_t(3));
	ASSERT_FALSE(hypro_float_t(4) <= hypro_float_t(2));
	
	ASSERT_TRUE(hypro_float_t(7) >= hypro_float_t(7));
	ASSERT_FALSE(hypro_float_t(5) >= hypro_float_t(9));
}

TEST(FloatTest, ArithmeticOperators)
{
	
}

TEST(FloatTest, SpecialOperators)
{
	
}

TEST(FloatTest, ConversionOperators)
{
	hypro_float_t testFloat(3);
	ASSERT_EQ(testFloat.toDouble(), 3);
	ASSERT_EQ(testFloat.toString(), "3");
	
	testFloat = hypro_float_t(1.824);
	ASSERT_EQ(testFloat.toDouble(), 1.824);
	ASSERT_EQ(testFloat.toString(), "1.824");
	
	testFloat = hypro_float_t("1.235");
	ASSERT_EQ(testFloat.toDouble(), 1.235);
	ASSERT_EQ(testFloat.toString(), "1.235");
}