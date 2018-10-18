#include "gtest/gtest.h"
#include "datastructures/reachability/Settings.h"
#include <iostream>

TEST(UtilityTest, ReachabilitySettings)
{
	hypro::ReachabilitySettings settings;
	settings.timeBound = 3.0;

	hypro::ReachabilitySettings copy(settings);
	hypro::ReachabilitySettings copy2 = settings;

	EXPECT_EQ(settings, copy);
	EXPECT_EQ(settings, copy2);
	EXPECT_EQ(copy, copy2);
}
