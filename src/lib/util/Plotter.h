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
#include "../datastructures/Point.h"
#include "../datastructures/Hyperplane.h"

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
const std::size_t colors[] = {0x006165, 0x0098A1, 0x57AB27, 0xBDCD00, 0xF6A800,
						0xCC071E, 0xA11035, 0x612158, 0x7A6FAC};

struct gnuplotSettings {
	std::size_t color = colors[petrol];  // default petrol
	bool fill = false;					 // do not fill
	bool axes = true;					 // plot axes
	double pointSize = 1.0;				 // pointsize
};

template <typename Number>
class Plotter : public carl::Singleton<Plotter<Number>> {
	friend carl::Singleton<Plotter<Number>>;

  private:
	std::string mFilename = "out";
	mutable std::ofstream mOutfile;
	std::multimap<unsigned, std::vector<Point<Number>>> mObjects;
	std::multimap<unsigned, std::vector<Hyperplane<Number>>> mPlanes;
	std::multimap<unsigned, Point<Number>> mPoints;
	std::multimap<unsigned, vector_t<Number>> mVectors;
	std::map<unsigned, std::size_t> mObjectColors;
	gnuplotSettings mSettings;
	unsigned mId;

  protected:
	Plotter() : mId( 1 ) {}

  public:
	~Plotter();

	void setFilename( const std::string& _filename = "out" );
	void updateSettings( const gnuplotSettings& _settings );
	const gnuplotSettings& settings() const;
	gnuplotSettings& rSettings();

	// plotting functions

	/**
	 * @brief Writes the actual plot to the output file.
	 * @details
	 */
	void plot2d() const;

	void plotTex() const;

	unsigned addObject( const std::vector<Point<Number>>& _points, bool sorted = false );
	unsigned addObject( const std::vector<std::vector<Point<Number>>>& _points, bool sorted = false );
	unsigned addObject( const std::vector<Hyperplane<Number>>& _planes );
	unsigned addObject( const Hyperplane<Number>& _plane );
	void addPoint( const Point<Number>& _point );
	void addPoints( const std::vector<Point<Number>>& _points );
	void addVector( const vector_t<Number>& _vector );

	void setObjectColor( unsigned _id, const std::size_t _color );

  private:
	// auxiliary functions
	void init( const std::string& _filename );
	std::vector<Point<Number>> grahamScan( const std::vector<Point<Number>>& _points );
	bool isLeftTurn( const Point<Number>& a, const Point<Number>& b, const Point<Number>& c );
};
}

#include "Plotter.tpp"
