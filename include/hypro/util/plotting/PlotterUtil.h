/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <vector>

namespace hypro {

std::vector<std::size_t> HEXtoRGB( std::size_t color );
std::size_t RGBtoHEX( std::vector<std::size_t> color );

std::vector<double> RGBtoHSV( const std::vector<std::size_t>& color );
std::vector<std::size_t> HSVtoRGB( const std::vector<double>& color );

std::vector<std::size_t> adjustSaturation( const std::vector<std::size_t>& rgbColor, double factor );
std::size_t adjustSaturation( std::size_t rgbColor, double factor );

template <typename N>
class Point;

template <typename N>
std::vector<Point<N>> reduceToDimensions( const std::vector<Point<N>>& vertices, const std::vector<std::size_t>& dims ) {
	auto res = vertices;
	for ( auto& p : res ) {
		p = p.reduceToDimensions( dims );
	}
	return res;
}

}  // namespace hypro
