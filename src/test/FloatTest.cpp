#include "gtest/gtest.h"
#include "defines.h"

TEST(FloatTest, Constructor)
{ 
    hypro_float_t testFloat(5);
    EXPECT_EQ(testFloat, hypro_float_t(5));
    EXPECT_EQ(true, true);
}

TEST(FloatTest, BooleanOperators)
{
	EXPECT_TRUE(hypro_float_t(5) == hypro_float_t(5));
	EXPECT_FALSE(hypro_float_t(3) == hypro_float_t(7));
	
	EXPECT_TRUE(hypro_float_t(4) != hypro_float_t(6));
	EXPECT_FALSE(hypro_float_t(3) != hypro_float_t(3));
	
	EXPECT_TRUE(hypro_float_t(9) > hypro_float_t(5));
	EXPECT_FALSE(hypro_float_t(3) > hypro_float_t(7));
	
	EXPECT_TRUE(hypro_float_t(2) < hypro_float_t(6));
	EXPECT_FALSE(hypro_float_t(8) < hypro_float_t(1));
	
	EXPECT_TRUE(hypro_float_t(3) <= hypro_float_t(3));
	EXPECT_FALSE(hypro_float_t(4) <= hypro_float_t(2));
	
	EXPECT_TRUE(hypro_float_t(7) >= hypro_float_t(7));
	EXPECT_FALSE(hypro_float_t(5) >= hypro_float_t(9));
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
	EXPECT_EQ(testFloat.toDouble(), 3.0);
	EXPECT_EQ(testFloat.toString(), "3.0");
}