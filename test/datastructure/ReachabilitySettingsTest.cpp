/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/datastructures/reachability/Settings.h>

TEST( ReachabilitySettingsTest, Constructor ) {
	// old settings
	hypro::ReachabilitySettings settings_old{};
	// new settings
	hypro::Settings settings_new{};
	SUCCEED();
}

TEST( ReachabilitySettingsTest, Conversion ) {
	// old settings
	hypro::ReachabilitySettings settings_old_default{};
	// new settings
	hypro::Settings settings_new_default = hypro::convert( settings_old_default );

	// old settings
	hypro::ReachabilitySettings settings_old{ 1, 2, 0.001, "outfilename", 13, { { 0, 1 }, { 1, 2 } }, true, 3, true, true, true };
	// new settings
	hypro::Settings settings_new = hypro::convert( settings_old );
	ASSERT_EQ( settings_new.strategy().size(), 1 );
	EXPECT_EQ( settings_new.strategy().front().clustering, 3 );
	EXPECT_EQ( settings_new.strategy().front().timeStepFactor, 1 );
	EXPECT_EQ( settings_new.strategy().front().timeStep, 0.001 );
	EXPECT_EQ( settings_new.strategy().front().uniformBloating, true );
	auto plot_dimensions = std::vector<std::vector<std::size_t>>{ std::vector<std::size_t>{ 0, 1 }, std::vector<std::size_t>{ 1, 2 } };
	EXPECT_EQ( settings_new.plotting().plotDimensions, plot_dimensions );
	SUCCEED();
}
