#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>


namespace hypro {

	std::vector<std::size_t> HEXtoRGB(std::size_t color);
	std::size_t RGBtoHEX(std::vector<std::size_t> color);

	std::vector<double> RGBtoHSV(const std::vector<std::size_t>& color);
	std::vector<std::size_t> HSVtoRGB(const std::vector<double>& color);

    std::vector<std::size_t> adjustSaturation(const std::vector<std::size_t>& rgbColor, double factor);
	std::size_t adjustSaturation(std::size_t rgbColor, double factor);

} // namespace
