#include "gtest/gtest.h"
#include "types.h"
#include "util/Plotter.h"

using namespace hypro;

TEST(PlotterTest, ColorConversion)
{
	EXPECT_EQ(plotting::colors[plotting::blue], RGBtoHEX(HEXtoRGB(plotting::colors[plotting::blue])));
	std::cout << plotting::colors[plotting::blue] << " saturated by -50%: " << RGBtoHEX(adjustSaturation(plotting::colors[plotting::blue], 0.5)) << std::endl;
}
