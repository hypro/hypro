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

inline bool file_exists( const std::string& filename ) {
	struct stat buffer;
	return ( stat( filename.c_str(), &buffer ) == 0 );
}

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
