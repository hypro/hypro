/*
 * @file   Plotter.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-03-01
 * @version	2015-05-16
 */

#pragma once

#include "../config.h"
#include "datastructures/Point.h"
#include "datastructures/Halfspace.h"
#include <carl/util/Singleton.h>
#include <vector>
#include <string>
#include <stack>

namespace hypro {

namespace plotting {

	/**
	 * Enum required for referencing colors in the color array.
	 */
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
		blue
	};
	/**
	 * Color array holding a set of colors.
	 */
	const std::size_t colors[] = {0x006165, 0x0098A1, 0x57AB27, 0xBDCD00, 0xF6A800,
							0xCC071E, 0xA11035, 0x612158, 0x7A6FAC, 0x00549F};

	/**
	 * @brief      A struct holding a basic set of options for the gnuplot plotting.
	 */
	struct gnuplotSettings {
		std::string name = "";				// filename
		std::size_t color = colors[blue];  // default petrol
		bool fill = false;					 // do not fill
		bool axes = true;					 // plot axes
		bool grid = true;					 // plot grid
		double pointSize = 1.0;				 // pointsize
		double linewidth = 0.2;				 // linewidth
		bool keepAspectRatio = false; 		 // keep aspect ratio for both axes
		std::pair<unsigned, unsigned> dimensions = std::make_pair(0,1); // dimensions to plot
		bool cummulative = false;			 // if enabled, plot each new segment in a new plot, only works for gnuplot, not for tex (TODO)
	};

} // namespace plotting


/**
 * @brief      Class implementing a plotter. The plotter is implemented using carl::Singleton.
 * @tparam     Number  The used number type.
 */
template <typename Number>
class Plotter : public carl::Singleton<Plotter<Number>> {
	friend carl::Singleton<Plotter<Number>>;

  private:
	std::string mFilename = "out";
	mutable std::ofstream mOutfile;
	mutable std::multimap<unsigned, std::vector<Point<Number>>> mObjects;
	mutable std::multimap<unsigned, std::vector<Halfspace<Number>>> mPlanes;
	mutable std::multimap<unsigned, Point<Number>> mPoints;
	mutable std::multimap<unsigned, vector_t<Number>> mVectors;
	mutable std::pair<int, int> mLastDimensions;
	mutable std::pair<vector_t<Number>, vector_t<Number>> mLimits;
	std::map<unsigned, std::size_t> mObjectColors;
	plotting::gnuplotSettings mSettings;
	unsigned mId;

  protected:
	Plotter() : mLastDimensions(std::make_pair(-1,-1)), mId( 1 ) {}

  public:
	~Plotter();

	/**
	 * @brief      Sets the filename.
	 * @param[in]  _filename  The filename (default = "out").
	 */
	void setFilename( const std::string& _filename = "out" );

	/**
	 * @brief      Overrides the current plotting settings with the passed ones.
	 * @param[in]  _settings  The new settings.
	 */
	void updateSettings( const plotting::gnuplotSettings& _settings );

	/**
	 * @brief      Returns the current plotting settings struct.
	 * @return     The current settings.
	 */
	const plotting::gnuplotSettings& settings() const;

	/**
	 * @brief      Provides a reference to the current plotting settings such that they can be changed in place.
	 * @return     A reference to the current plotting settings.
	 */
	plotting::gnuplotSettings& rSettings();

	/**
	 * @brief      Creates a gnuplot file of the currently passed objects.
	 */
	void plot2d() const;

	/**
	 * @brief      Creates a LaTeX file of the currently passed objects.
	 */
	void plotTex() const;

	/**
	 * @brief      Creates a .gen file of the currently passed objects, which can be used in gnuplot as well.
	 */
	void plotGen() const;

	/**
	 * @brief      Adds an object represented as a vector of points. Duplicates and points inside will be removed by the plotter,
	 * which runs a 2d-convex hull algorithm (Graham's scan) one the vertices.
	 * @param[in]  _points  The points.
	 * @return     A unique id, which allows to reference the object to change its colors.
	 */
	unsigned addObject( const std::vector<Point<Number>>& _points );

	/**
	 * @brief      Adds several objects represented as a vector of vectors of points. Duplicates and points inside will be removed by the plotter,
	 * which runs a 2d-convex hull algorithm (Graham's scan) one the vertices.
	 * @param[in]  _points  The points.
	 * @return     The id of the last added object, which allows to reference the object to change its colors. All other ids can be derived using
	 * the size of the passed vector (ids are assigned ascending).
	 */
	unsigned addObject( const std::vector<std::vector<Point<Number>>>& _points );

	/**
	 * @brief      Adds a set of halfspaces to the plotter.
	 * @details    Note that the plotting of planes requires that at least one proper object (a set of points) is added as well, because the
	 * plotter needs to determine the plotting dimensions.
	 * @param[in]  _planes  The planes.
	 * @return     An id referencing the last plane.
	 */
	unsigned addObject( const std::vector<Halfspace<Number>>& _planes );

	/**
	 * @brief      Adds a halfspace to the plotter.
	 * @details    Note that the plotting of planes requires that at least one proper object (a set of points) is added as well, because the
	 * plotter needs to determine the plotting dimensions.
	 * @param[in]  _plane  The plane.
	 * @return     An id referencing the plane.
	 */
	unsigned addObject( const Halfspace<Number>& _plane );

	/**
	 * @brief      Adds a point to the plotter.
	 * @details    The point, in contrast to an object will be plotted as a cross.
	 * @param[in]  _point  The point.
	 * @return     An id referencing the point.
	 */
	unsigned addPoint( const Point<Number>& _point );

	/**
	 * @brief      Adds points to the plotter.
	 * @details    The points will be plotted as crosses.
	 * @param[in]  _points  The points.
	 * @return     An id referencing the last passed point.
	 */
	unsigned addPoints( const std::vector<Point<Number>>& _points );

	/**
	 * @brief      Adds a vector to the plotter.
	 * @details    A vector will be plotted as an arrow starting from the origin.
	 * @param[in]  _vector  The vector.
	 */
	void addVector( const vector_t<Number>& _vector );

	/**
	 * @brief      Sets the object color.
	 * @param[in]  _id     The identifier referencing the object.
	 * @param[in]  _color  The color.
	 */
	void setObjectColor( unsigned _id, const std::size_t _color );

  private:
	// auxiliary functions
	void init( const std::string& _filename );
	static std::vector<Point<Number>> grahamScan( const std::vector<Point<Number>>& _points );
	static bool isLeftTurn( const Point<Number>& a, const Point<Number>& b, const Point<Number>& c );
	void prepareObjects() const;
};
}

#include "Plotter.tpp"
