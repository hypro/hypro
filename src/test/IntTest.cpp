#include "gtest/gtest.h"
#include "defines.h"

TEST(IntTest, Constructor)
{ 
    hypro_int_t testInt(5);
    ASSERT_EQ(testInt, hypro_int_t(5));
}

TEST(IntTest, BooleanOperators)
{
	ASSERT_TRUE(hypro_int_t(5) == hypro_int_t(5));
	ASSERT_FALSE(hypro_int_t(3) == hypro_int_t(7));
	
	ASSERT_TRUE(hypro_int_t(4) != hypro_int_t(6));
	ASSERT_FALSE(hypro_int_t(3) != hypro_int_t(3));
	
	ASSERT_TRUE(hypro_int_t(9) > hypro_int_t(5));
	ASSERT_FALSE(hypro_int_t(3) > hypro_int_t(7));
	
	ASSERT_TRUE(hypro_int_t(2) < hypro_int_t(6));
	ASSERT_FALSE(hypro_int_t(8) < hypro_int_t(1));
	
	ASSERT_TRUE(hypro_int_t(3) <= hypro_int_t(3));
	ASSERT_FALSE(hypro_int_t(4) <= hypro_int_t(2));
	
	ASSERT_TRUE(hypro_int_t(7) >= hypro_int_t(7));
	ASSERT_FALSE(hypro_int_t(5) >= hypro_int_t(9));
}

TEST(IntTest, ArithmeticOperators)
{
	
}

TEST(IntTest, SpecialOperators)
{
	
}

TEST(IntTest, ConversionOperators)
{
	hypro_int_t testInt(3);
	ASSERT_EQ(testInt.toInt(), 3);
	ASSERT_EQ(testInt.toString(), "3");
	
	testInt = hypro_int_t("7");
	ASSERT_EQ(testInt.toInt(), 7);
	ASSERT_EQ(testInt.toString(), "7");
}