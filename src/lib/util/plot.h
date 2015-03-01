/* 
 * @file   plot.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-03-01
 * @version	2015-03-01
 */

#pragma once

#include <vector>
#include "../lib/datastructures/Point.h"

namespace hypro {
	
	struct gnuplotSettings {
		
	};
	
	/**
	 * Plots a 2D plot. Note that the function assumes the points passed to be ordered.
	 * @param _points A ordered vector of points (2D).
	 * @param _settings Settings passed to gnuplot.
	 * 
	 */
	template<typename Number>
	static void plot( const std::vector<Point<Number>>& _points, const std::string& _outfile ="out.plt" ,  gnuplotSettings _settings = gnuplotSettings()) {
		// open file
		std::ofstream out;
		out.open (_outfile);
		out << "set object 1 polygon from \\ \n";
		for(unsigned pointIndex = 0; pointIndex < _points.size()-1; ++pointIndex) {
			assert(_points[pointIndex].dimension() <= 2); // TODO: Project to 2d
			if(_points[pointIndex].dimension() == 0) {
				continue;
			}
			out << "\t " << double(_points[pointIndex].at(0));
			for(unsigned d = 1; d < _points[pointIndex].dimension(); ++d) {
				out << ", " << double(_points[pointIndex].at(d));
			}
			out << " to \\ \n";
		}
		assert(_points[_points.size()-1].dimension() <= 2); // TODO: Project to 2d	
		out << "\t " << double(_points[_points.size()-1].at(0));
		for(unsigned d = 1; d < _points[_points.size()-1].dimension(); ++d) {
			out << ", " << double(_points[_points.size()-1].at(d));
		}
		
		// close file after writing
		out.close();
	} 
	
}

