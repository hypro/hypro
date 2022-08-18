/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * @file   Plotter.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-03-01
 * @version	2015-05-16
 */

#pragma once

#include "../../config.h"
#include "../../datastructures/Halfspace.h"
#include "../../datastructures/Point.h"
#include "../fileHandling.h"
#include "../logging/Logger.h"
#include "../type_handling/plottype_enums.h"
#include "Colors.h"
#include "GnuplotSettings.h"
#include "PlotterUtil.h"

#include <carl/interval/Interval.h>
#include <carl/util/Singleton.h>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

namespace hypro {
namespace plotting {

template <typename Number>
struct PlotObject {
	std::vector<Point<Number>> vertices;					 //< vertices of the object
	bool isPrepared = false;								 //< true, if the vertices are already in order and reduced (Graham's scan)
	bool isPlotted = false;									 //< true, if the object has already been written to a file
	std::optional<std::size_t> color = std::nullopt;		 //< set to custom color id
	std::optional<gnuplotSettings> settings = std::nullopt;	 //< optional custom settings
	std::string objectTitle = "";							 //< set to custom object title
};

}  // namespace plotting

/**
 * @brief      Class implementing a plotter. The plotter is implemented using carl::Singleton.
 * @tparam     Number  The used number type.
 */
template <typename Number>
class Plotter : public carl::Singleton<Plotter<Number>> {
	friend carl::Singleton<Plotter<Number>>;

  private:
	mutable std::ofstream mOutfile;
	mutable std::map<unsigned, plotting::PlotObject<Number>> mObjects;
	mutable std::map<unsigned, plotting::PlotObject<Number>> mLines;
	mutable std::multimap<unsigned, std::vector<Halfspace<Number>>> mPlanes;
	mutable std::vector<plotting::PlotObject<Number>> mPoints;
	mutable std::multimap<unsigned, std::pair<vector_t<Number>, vector_t<Number>>> mVectors;
	mutable std::pair<vector_t<Number>, vector_t<Number>> mLimits;
	std::map<unsigned, std::size_t> mObjectColors;
	plotting::gnuplotSettings mSettings = plotting::gnuplotSettings{};
	unsigned mId;

  protected:
	Plotter()
		: mId( 1 ) {}

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
	 * @brief Creates a gnuplot file of the currently passed objects.
	 * @details    The resulting *.plt file can be compiled to a pdf invoking gnuplot.
	 * @param outformat Specifies the type of output file generated.
	 */
	void plot2d( PLOTTYPE outformat = PLOTTYPE::pdf, bool runGnuplot = false ) const;

	/**
	 * @brief      Creates a LaTeX file of the currently passed objects.
	 * @details    We use the gnuplot latex terminal type in standalone mode. Note that for Linux systems at least Texlive 2015 has to be
	 * installed to be able to compile the resulting *.tex file.
	 */
	[[deprecated( "Use plot2d(PLOTTYPE::tex) instead." )]] void plotTex() const;  // marked for deprecation: 6.6.20

	/**
	 * @brief      Creates a .eps file of the currently passed objects, which can be used in gnuplot as well.
	 */
	[[deprecated( "Use plot2d(PLOTTYPE::eps) instead." )]] void plotEps() const;  // marked for deprecation: 6.6.20

	/**
	 * @brief      Creates a .eps file of the currently passed objects, which can be used in gnuplot as well.
	 */
	[[deprecated( "Use plot2d(PLOTTYPE::png) instead." )]] void plotPng() const;  // marked for deprecation: 6.6.20

	[[deprecated( "Use plot2d(PLOTTYPE::gen) instead." )]] void plotGen() const;  // marked for deprecation: 6.6.20

	/**
	 * @brief      Adds an object represented as a vector of points. Duplicates and points inside will be removed by the plotter,
	 * which runs a 2d-convex hull algorithm (Graham's scan) one the vertices.
	 * @param[in]  _points  The points.
	 * @param[in]  _objectTitle  Title of the object for the key.
	 * @param[in]  _color  Optionally color the object.
	 * @return     A unique id, which allows to reference the object to change its colors.
	 */
	unsigned addObject( const std::vector<Point<Number>>& _points, std::string _objectTitle, std::optional<std::size_t> _color = std::nullopt, std::optional<plotting::gnuplotSettings> settings = std::nullopt );

	/**
	 * @brief      Adds an object represented as a vector of points. Duplicates and points inside will be removed by the plotter,
	 * which runs a 2d-convex hull algorithm (Graham's scan) one the vertices.
	 * @param[in]  _points  The points.
	 * @return     A unique id, which allows to reference the object to change its colors.
	 */
	unsigned addObject( const std::vector<Point<Number>>& _points, std::optional<std::size_t> color = std::nullopt, std::optional<plotting::gnuplotSettings> settings = std::nullopt );

	/**
	 * Similar to addObject, but does not apply Graham's scan on the passed points to not change the order of points.
	 * @param _points An ordered sequence of points
	 * @param color Optional coloring information
	 * @param settings Optional individual gnuplot settings
	 * @return A unique id, whcih allows to reference the object later to change it
	 */
	unsigned addOrderedObject( const std::vector<Point<Number>>& _points, std::optional<std::size_t> color = std::nullopt, std::optional<plotting::gnuplotSettings> settings = std::nullopt );

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
	 * @brief Removes an object from the plotter, no-op if the id is not used.
	 * @param id The id of the object to be removed
	 */
	void removeObject( unsigned id );

	/**
	 * Plots a line built from segments connecting nodes.
	 * @param points A sequence of nodes which define the line segments of the polyline
	 * @param color Optional color for the polyline
	 */
	void addPolyline( const std::vector<Point<Number>>& points, std::optional<std::size_t> color = std::nullopt );

	/**
	 * @brief      Adds a point to the plotter.
	 * @details    The point, in contrast to an object will be plotted as a cross.
	 * @param[in]  _point  The point.
	 * @param[in]  _color Optionally color the point.
	 */
	unsigned addPoint( const Point<Number>& _point, std::optional<std::size_t> _color = std::nullopt, std::optional<plotting::gnuplotSettings> settings = std::nullopt );

	/**
	 * @brief      Adds points to the plotter.
	 * @details    The points will be plotted as crosses.
	 * @param[in]  _points  The points.
	 */
	void addPoints( const std::vector<Point<Number>>& _points );

	/**
	 * @brief      Adds a vector to the plotter.
	 * @details    A vector will be plotted as an arrow starting from the origin.
	 * @param[in]  _vector  The vector.
	 */
	void addVector( const vector_t<Number>& _vector, std::optional<vector_t<Number>> origin = std::nullopt );

	/**
	 * @brief      Sets the object color.
	 * @param[in]  _id     The identifier referencing the object.
	 * @param[in]  _color  The color.
	 */
	[[deprecated( "Unsafe if intermediate plotting enabled. Set color directly when adding instead." )]] void setObjectColor( unsigned _id, const std::size_t _color );	 // marked for deprecation 12.06.2021

	void clear();

	/**
	 * @brief Implementation of Graham's scan.
	 *
	 * @param _points A vector of 2-dimensional points.
	 * @return std::vector<Point<Number>> An ordered vector of 2-dimensional points (counterclockwise).
	 */
	static std::vector<Point<Number>> grahamScan( const std::vector<Point<Number>>& _points );

  private:
	// auxiliary functions
	void updateLimits( const std::vector<Point<Number>>& points );
	void init( const std::string& _filename );
	void writeGnuplot() const;
	void writeGen() const;
	static bool isLeftTurn( const Point<Number>& a, const Point<Number>& b, const Point<Number>& c );
	void prepareObjects() const;
};
}  // namespace hypro

#include "Plotter.tpp"
