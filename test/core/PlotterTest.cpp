#include "gtest/gtest.h"
#include <hypro/types.h>
#include <hypro/util/plotting/Plotter.h>

using namespace hypro;

TEST( PlotterTest, ColorConversion ) {
	EXPECT_EQ( plotting::colors[plotting::blue], RGBtoHEX( HEXtoRGB( plotting::colors[plotting::blue] ) ) );
	EXPECT_EQ( std::vector<std::size_t>( { 10, 20, 30 } ),
			   HSVtoRGB( RGBtoHSV( std::vector<std::size_t>( { 10, 20, 30 } ) ) ) );
	// EXPECT_EQ(plotting::colors[plotting::blue],
	// RGBtoHEX(HSVtoRGB(RGBtoHSV(HEXtoRGB(plotting::colors[plotting::blue])))));
}
