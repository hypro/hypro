#include "gtest/gtest.h"
#include "algorithms/reachability/Settings.h"
#include <iostream>

TEST(UtilityTest, ReachabilitySettings)
{
	hypro::reachability::ReachabilitySettings<double> settings;
	settings.timeBound = 3.0;

	hypro::reachability::ReachabilitySettings<double> copy(settings);
	hypro::reachability::ReachabilitySettings<double> copy2 = settings;

	EXPECT_EQ(settings, copy);
	EXPECT_EQ(settings, copy2);
	EXPECT_EQ(copy, copy2);
}
