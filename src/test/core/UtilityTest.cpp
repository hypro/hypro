#include "gtest/gtest.h"
#include "types.h"
#include <iostream>

TEST(UtilityTest, OutstreamOperators)
{
	std::ostringstream out;
	hypro::SOLUTION sol = hypro::SOLUTION::INFEAS;
	out << sol;
	EXPECT_EQ("INFEAS", out.str());

	out.str(std::string());

	sol = hypro::SOLUTION::FEAS;
	out << sol;
	EXPECT_EQ("FEAS", out.str());

	out.str(std::string());

	sol = hypro::SOLUTION::INFTY;
	out << sol;
	EXPECT_EQ("INFTY", out.str());

	out.str(std::string());

	sol = hypro::SOLUTION::UNKNOWN;
	out << sol;
	EXPECT_EQ("UNKNOWN", out.str());
}
