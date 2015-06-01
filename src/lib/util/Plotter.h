/* 
 * @file   Plotter.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-03-01
 * @version	2015-05-16
 */

#pragma once

#include <carl/util/Singleton.h>
#include <vector>
#include <string>
#include "../lib/datastructures/Point.h"

namespace hypro {
	
	struct gnuplotSettings {
		std::string color = "#18571C"; // default green
	};
	
	template<typename Number>
	class Plotter : public carl::Singleton<Plotter<Number>>
    {
        friend carl::Singleton<Plotter<Number>>;
	private:
		std::string mFilename;
		mutable std::ofstream mOutfile;
		std::vector<std::vector<Point<Number>>> mObjects;
		gnuplotSettings mSettings;

	protected:
		Plotter()
        {}
	public:
		~Plotter();

		void setFilename(const std::string& _filename);
		void updateSettings(gnuplotSettings _settings);

		// plotting functions
		
		/**
		 * @brief Writes the actual plot to the output file.
		 * @details 
		 */
		void plot2d() const;

		void addObject(std::vector<Point<Number>> _points);

	private:
		// auxiliary functions
		void init(const std::string& _filename);
		void grahamScan(std::vector<Point<Number>>& _points);
		bool isLeftTurn(const Point<Number>& a, const Point<Number>& b, const Point<Number>& c);
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
		
		// set object
		vector_t<Number> min = _points[0].rawCoordinates();
		vector_t<Number> max = _points[0].rawCoordinates();
		
		out << "set object 1 polygon from \\\n";
		for(unsigned pointIndex = 0; pointIndex < _points.size(); ++pointIndex) {
			assert(_points[pointIndex].dimension() <= 2); // TODO: Project to 2d
			if(_points[pointIndex].dimension() == 0) {
				continue;
			}
			out << "  " << double(_points[pointIndex].at(0));
			
			// update min and max
			min(0) = min(0) < _points[pointIndex].at(0) ? min(0) : _points[pointIndex].at(0);
			max(0) = max(0) > _points[pointIndex].at(0) ? max(0) : _points[pointIndex].at(0);
			
			for(unsigned d = 1; d < _points[pointIndex].dimension(); ++d) {
				out << ", " << double(_points[pointIndex].at(d));
				// update min and max
				min(d) = min(d) < _points[pointIndex].at(d) ? min(d) : _points[pointIndex].at(d);
				max(d) = max(d) > _points[pointIndex].at(d) ? max(d) : _points[pointIndex].at(d);
			}
			out << " to \\\n";
		}
		assert(_points[_points.size()-1].dimension() <= 2); // TODO: Project to 2d	
		out << "  " << double(_points[0].at(0));
		for(unsigned d = 1; d < _points[0].dimension(); ++d) {
			out << ", " << double(_points[0].at(d));
		}
		out << " fs empty border lc rgb '" << _settings.color << "'\n";
		out << "set term post eps\n";
		out << "set output \"" << _outfile << ".eps\"\n";
		out << "plot ";

		for(unsigned d = 0; d < min.rows(); ++d) {
			out << "[" << min(d)*1.1 << ":" << max(d)*1.1 << "] ";
		}
		out << "NaN notitle";
		
		// close file after writing
		out.close();
	} 
	
}

#include "Plotter.tpp"
