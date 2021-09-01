#include "PlotterUtil.h"

namespace hypro {

std::vector<std::size_t> HEXtoRGB( std::size_t color ) {
	std::size_t r = ( ( color & ( 255 << 16 ) ) >> 16 );  // bitwise and with 16^5 AND 16^4
	std::size_t g = ( ( color & ( 255 << 8 ) ) >> 8 );
	std::size_t b = color & 255;
	// std::cout << "Convert " << color << " to [" << r << ", " << g << ", " << b << "]" << std::endl;
	return { r, g, b };
}

std::size_t RGBtoHEX( std::vector<std::size_t> color ) {
	assert( color.size() == 3 );
	std::size_t res = 0;
	res += ( color[0] / 16 << 20 );
	res += ( color[0] % 16 << 16 );
	res += ( color[1] / 16 << 12 );
	res += ( color[1] % 16 << 8 );
	res += ( color[2] / 16 << 4 );
	res += color[2] % 16;
	// std::cout << "Convert [" << color[0] << ", " << color[1] << ", " << color[2] << "] to " << res << std::endl;
	return res;
}

std::vector<double> RGBtoHSV( const std::vector<std::size_t>& color ) {
	assert( color.size() == 3 );
	// scale domain from [0,255] to [0,1]
	std::vector<double> scaled;
	for ( auto item : color ) {
		scaled.push_back( double( item ) / 255.0 );
	}

	auto min = std::min_element( scaled.begin(), scaled.end() );
	auto max = std::max_element( scaled.begin(), scaled.end() );

	double v = ( *max );
	double s = 0;
	double h = 0;
	double delta = ( *max - *min );
	if ( *max != 0 )
		s = delta / *max;  // s
	else {
		//// r = g = b = 0        // s = 0, v is undefined
		s = 0;
		h = -1;
		return std::vector<double>( { h, s, 0 } );
	}
	if ( 0 == max - scaled.begin() )				// the max element is at position 0
		h = ( scaled[1] - scaled[2] ) / delta;		// between yellow & magenta
	else if ( 1 == max - scaled.begin() )			// the max element is at position 1
		h = 2 + ( scaled[2] - scaled[0] ) / delta;	// between cyan & yellow
	else											// the max element is at position 2
		h = 4 + ( scaled[0] - scaled[1] ) / delta;	// between magenta & cyan

	h *= 60;  // degrees -> domain of h is [0,360]
	if ( h < 0 )
		h += 360;
	if ( std::isnan( h ) )
		h = 0;
	// std::cout << "H: " << h << ", S: " << s << ", V: " << v << std::endl;
	assert( 0 <= h && h <= 360 );
	assert( 0 <= s && s <= 1 );
	assert( 0 <= v && v <= 1 );
	return std::vector<double>( { h, s, v } );
}

std::vector<std::size_t> HSVtoRGB( const std::vector<double>& color ) {
	double r = 0;
	double g = 0;
	double b = 0;
	double h = color[0];
	double s = color[1];
	double v = color[2];
	assert( 0 <= h && h <= 360 );
	assert( 0 <= s && s <= 1 );
	assert( 0 <= v && v <= 1 );

	int i = 0;
	if ( s == 0 ) {
		// achromatic (grey)
		// r,g,b in [0,1] -> scale
		r = g = b = v;
		std::size_t resR = std::size_t( r * 255.0 );
		std::size_t resG = std::size_t( g * 255.0 );
		std::size_t resB = std::size_t( b * 255.0 );
		return std::vector<std::size_t>( { resR, resG, resB } );
	}
	h /= 60.0;	// sector 0 to 5
	i = int( std::floor( h ) );
	double f = h - i;  // factorial part of h
	double p = v * ( 1 - s );
	double q = v * ( 1 - s * f );
	double t = v * ( 1 - s * ( 1 - f ) );
	switch ( i ) {
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		default:  // case 5:
			r = v;
			g = p;
			b = q;
			break;
	}
	// r,g,b in [0,1] -> scale
	std::size_t resR = std::size_t( r * 255.0 );
	std::size_t resG = std::size_t( g * 255.0 );
	std::size_t resB = std::size_t( b * 255.0 );
	return std::vector<std::size_t>( { resR, resG, resB } );
}

std::vector<std::size_t> adjustSaturation( const std::vector<std::size_t>& rgbColor, double factor ) {
	std::vector<double> hsvColor = RGBtoHSV( rgbColor );
	hsvColor[1] *= factor;
	return HSVtoRGB( hsvColor );
}

std::size_t adjustSaturation( std::size_t rgbColor, double factor ) {
	return RGBtoHEX( adjustSaturation( HEXtoRGB( rgbColor ), factor ) );
}

}  // namespace hypro
