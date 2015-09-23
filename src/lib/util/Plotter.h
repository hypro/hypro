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
#include <stack>
#include "../lib/datastructures/Point.h"

namespace hypro {

enum {
	petrol = 0,
	turquoise,
	green,
	maygreen,
	orange,
	red,
	bordeaux,
	violett,
	lila,
};
const char* colors[] = {"#006165", "#0098A1", "#57AB27", "#BDCD00", "#F6A800",
						"#CC071E", "#A11035", "#612158", "#7A6FAC"};

struct gnuplotSettings {
	std::string color = colors[petrol];  // default petrol
	bool fill = false;					 // do not fill
};

template <typename Number>
class Plotter : public carl::Singleton<Plotter<Number>> {
	friend carl::Singleton<Plotter<Number>>;

  private:
	std::string mFilename = "out";
	mutable std::ofstream mOutfile;
	std::multimap<unsigned, std::vector<Point<Number>>> mObjects;
	std::map<unsigned, std::string> mObjectColors;
	gnuplotSettings mSettings;
	unsigned mId;

  protected:
	Plotter() : mId( 1 ) {}

  public:
	~Plotter();

	void setFilename( const std::string& _filename = "out" );
	void updateSettings( gnuplotSettings _settings );

	// plotting functions

	/**
	 * @brief Writes the actual plot to the output file.
	 * @details
	 */
	void plot2d() const;

	unsigned addObject( const std::vector<Point<Number>>& _points, bool sorted = false );
	unsigned addObject( const std::vector<std::vector<Point<Number>>>& _points, bool sorted = false );

	void setObjectColor( unsigned _id, const std::string _color );

  private:
	// auxiliary functions
	void init( const std::string& _filename );
	std::vector<Point<Number>> grahamScan( const std::vector<Point<Number>>& _points );
	bool isLeftTurn( const Point<Number>& a, const Point<Number>& b, const Point<Number>& c );
};
}

#include "Plotter.tpp"
