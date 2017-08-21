#include <algorithm>

namespace hypro {

	std::vector<std::size_t> HEXtoRGB(std::size_t color) {
		std::size_t r = ((color & (255 << 16)) >> 16); // bitwise and with 16^5 AND 16^4
		std::size_t g = ((color & (255 << 8)) >> 8);
		std::size_t b = color & 255;
		std::cout << "Convert " << color << " to [" << r << ", " << g << ", " << b << "]" << std::endl;
		return std::vector<std::size_t>({r,g,b});
	}

	std::size_t RGBtoHEX(std::vector<std::size_t> color) {
		assert(color.size() == 3);
		std::size_t res = 0;
		res += (color[0]/16 << 20);
		res += (color[0]%16 << 16);
		res += (color[1]/16 << 12);
		res += (color[1]%16 << 8);
		res += (color[2]/16 << 4);
		res += color[2]%16;
		std::cout << "Convert [" << color[0] << ", " << color[1] << ", " << color[2] << "] to " << res << std::endl;
		return res;
	}

	std::vector<double> RGBtoHSV(const std::vector<std::size_t>& color) {
		assert(color.size() == 3);
        std::size_t min = *std::min_element(color.begin(), color.end());
        std::size_t max = *std::max_element(color.begin(), color.end());

        double v = max/255;
        double s = 0;
        double h = 0;
        double delta = (max - min)/255;
        if( max != 0 )
            s = delta / max;        // s
        else {
            //// r = g = b = 0        // s = 0, v is undefined
            s = 0;
            h = -1;
            return std::vector<int>({h,s,0});
        }
        if( color[0] == max )
            h = ( color[1] - color[2] ) / delta;      // between yellow & magenta
        else if( color[1] == max )
            h = 2 + ( color[2] - color[0] ) / delta;  // between cyan & yellow
        else
            h = 4 + ( color[0] - color[1] ) / delta;  // between magenta & cyan
        h *= 60;                // degrees
        if( h < 0 )
            h += 360;
        if ( std::isnan(h) )
            h = 0;
        std::cout << "H: " << h << ", S: " << s << ", V: " << v << std::endl;
        return std::vector<int>({h,s,v});
    }

	std::vector<std::size_t> HSVtoRGB(const std::vector<int>& color) {
        std::size_t r = 0;
        std::size_t g = 0;
        std::size_t b = 0;
        int h= color[0];
        int s= color[1];
        int v= color[2];
        int i = 0;
        if(s == 0 ) {
            // achromatic (grey)
            r = g = b = v;
            return std::vector<std::size_t>({r,g,b});
        }
        h /= 60;            // sector 0 to 5
        i = std::floor( h );
        int f = h - i;          // factorial part of h
        int p = v * ( 1 - s );
        int q = v * ( 1 - s * f );
        int t = v * ( 1 - s * ( 1 - f ) );
        switch( i ) {
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
            default:        // case 5:
                r = v;
                g = p;
                b = q;
                break;
        }
        return std::vector<std::size_t>({r,g,b});
    }

    std::vector<std::size_t> adjustSaturation(const std::vector<std::size_t>& rgbColor, double factor) {
		std::vector<int> hsvColor = RGBtoHSV(rgbColor);
		hsvColor[1] *= factor;
		return HSVtoRGB(hsvColor);
	}

	std::vector<std::size_t> adjustSaturation(std::size_t rgbColor, double factor) {
		return adjustSaturation(HEXtoRGB(rgbColor),factor);
	}

} // namespace
