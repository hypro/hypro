/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 18.03.22.
 */

#ifndef HYPRO_GNUPLOTSETTINGS_H
#define HYPRO_GNUPLOTSETTINGS_H

#include "Colors.h"

#include <carl/interval/Interval.h>
#include <string>

namespace hypro::plotting {

/**
 * @brief      A struct holding a basic set of options for the gnuplot plotting.
 */
struct gnuplotSettings {
	std::string name = "";			   //< title
	std::string filename = "out";	   //< filename
	std::size_t color = colors[blue];  //< default blue
	bool fill = false;				   //< do not fill
	bool axes = true;				   //< plot axes
	bool grid = true;				   //< plot grid
	bool title = false;				   //< plot title
	bool key = false; 				   //> plot key/legend
	double pointSize = 0.2;			   //< pointsize
	double linewidth = 0.1;			   //< linewidth
	carl::Interval<double> xPlotInterval = carl::Interval<double>::emptyInterval();
	carl::Interval<double> yPlotInterval = carl::Interval<double>::emptyInterval();
	bool keepAspectRatio = true;				  //< keep aspect ratio for both axes
	std::vector<std::size_t> dimensions{ 0, 1 };  //< dimensions to plot
	bool cummulative = false;					  //< if enabled, plot each new segment in a new plot, only works for gnuplot, not for tex (TODO)
	bool plain = false;							  //< overrides most settings
	bool overwriteFiles = false;				  //< set to enable file overwriting
	std::size_t writeIntermediate = 0;			  //< set to a strictly positve number n to write (append) every n objects to a file, those objects are deleted from the plotter afterwards
	bool key = false; //< if true, a key/legend is added to the plot
};

}  // namespace hypro::plotting

#endif	// HYPRO_GNUPLOTSETTINGS_H
