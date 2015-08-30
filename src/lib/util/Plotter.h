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
		bool fill = false; // do not fill
	};

	template<typename Number>
	class Plotter : public carl::Singleton<Plotter<Number>>
	{
		friend carl::Singleton<Plotter<Number>>;
	private:
		std::string mFilename;
		mutable std::ofstream mOutfile;
		std::multimap<unsigned,std::vector<Point<Number>>> mObjects;
		std::map<unsigned,std::string> mObjectColors;
		gnuplotSettings mSettings;
		unsigned mId;

	protected:
		Plotter() :
			mId(1)
		{}
	public:
		~Plotter();

		void setFilename(const std::string& _filename="out");
		void updateSettings(gnuplotSettings _settings);

		// plotting functions

		/**
		 * @brief Writes the actual plot to the output file.
		 * @details
		 */
		void plot2d() const;

		unsigned addObject(const std::vector<Point<Number>>& _points, bool sorted=false);
		unsigned addObject(const std::vector<std::vector<Point<Number>>>& _points, bool sorted=false);

		void setObjectColor(unsigned _id, const std::string _color);

	private:
		// auxiliary functions
		void init(const std::string& _filename);
		std::vector<Point<Number>> grahamScan(const std::vector<Point<Number>>& _points);
		bool isLeftTurn(const Point<Number>& a, const Point<Number>& b, const Point<Number>& c);
	};
}

#include "Plotter.tpp"
