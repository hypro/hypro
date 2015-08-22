/* 
 * @file   Plotter.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-03-01
 * @version	2015-05-16
 */

#pragma once

#include "../config.h"
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

		void addObject(const std::vector<Point<Number>>& _points, bool sorted=false);
		void addObject(const std::vector<std::vector<Point<Number>>>& _points, bool sorted=false);

	private:
		// auxiliary functions
		void init(const std::string& _filename);
		std::vector<Point<Number>> grahamScan(const std::vector<Point<Number>>& _points);
		bool isLeftTurn(const Point<Number>& a, const Point<Number>& b, const Point<Number>& c);
	};
}

#include "Plotter.tpp"
