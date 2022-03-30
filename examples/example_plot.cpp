/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * \example example_plot.cpp This file shows how to use the plotter.
 */

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/datastructures/Halfspace.h>
#include <hypro/util/plotting/Plotter.h>
#include <hypro/paths.h>

using namespace hypro;

int main() {
	typedef double Number;

	// get reference to singleton plotter
	Plotter<Number>& plotter = Plotter<Number>::getInstance();

	// create a polytope in h-representation to be plotted
	HPolytope<Number> poly;
	poly.insert( Halfspace<Number>( { 1, 1 }, 1 ) );
	poly.insert( Halfspace<Number>( { -1, 1 }, 1 ) );
	poly.insert( Halfspace<Number>( { 0, -1 }, 1 ) );

	// collect the vertices
	std::vector<Point<Number>> vertices = poly.vertices();

	// pass to plotter.
	plotter.addObject( vertices );

	// we can also add half-spaces to be plotted (within a bounding box)
	plotter.addObject( poly.constraints() );
	plotter.addObject( Halfspace<Number>( { 1, 0 }, 1 ) );

	// single points will be marked as a cross in the plot
	plotter.addPoint( Point<Number>( { carl::rationalize<Number>( -1.5 ), 3 } ) );

	// create a three-dimensional box
	std::vector<carl::Interval<Number>> intervals;
	intervals.emplace_back( carl::Interval<Number>( 1, 2 ) );
	intervals.emplace_back( carl::Interval<Number>( 0, 1 ) );
	intervals.emplace_back( carl::Interval<Number>( -1, 0 ) );
	Box<Number> box{ intervals };

	// as we only plot in two dimensions, project on the dimension which will be
	// plotted
	auto projectedBox = box.projectOn( { 0, 1 } );

	// push vertices of projected box to Plotter, store id of object
	std::size_t id = plotter.addObject( projectedBox.vertices() );

	// we can adjust the color of an object, default is blue.
	plotter.setObjectColor( id, plotting::colors[plotting::green] );

	// we may adjust the output file name (default out.XYZ), the file type is
	// determined by the used plot function (see below) the filename also
	// determines the title of the plot
	plotter.setFilename( "plotTest" );

	// write plot files - gnuplot files with different output terminals are
	// supported: pdf (plot2d), tex (plotTex), and eps (plotEps). plain gnuplot
	// files (*.gen) may also be created via plotGen().
	plotter.plot2d( PLOTTYPE::pdf );
	plotter.plot2d( PLOTTYPE::tex );
	plotter.plot2d( PLOTTYPE::eps );

	// clear the plotter, i.e., remove all stored objects to create a fresh canvas
	plotter.clear();

	// second example: plot reachability results
	using Box = hypro::Box<Number>;
	// parse automaton
	auto [automaton, rsettings] = parseFlowstarFile<Number>( getCSModelsPath() + "bouncing_ball.model" );
	auto settings = convert( rsettings );

	// adjust settings locally to speed up computation
	settings.rFixedParameters().jumpDepth = 1;
	settings.rStrategy().front().aggregation = AGG_SETTING::AGG;

	// setup reachability analysis method
	auto roots = makeRoots<Box>( automaton );
	auto reacher = reachability::Reach<Box>( automaton, settings.fixedParameters(), settings.strategy().front(), roots );
	auto result = reacher.computeForwardReachability();
	std::cout << "Reachability result: " << result << std::endl;

	// add sets to plotter
	for ( const auto& root : roots ) {
		for ( const auto& set : getSegments( root ) ) {
			plotter.addObject( set.projectOn( { 0, 1 } ).vertices() );
		}
	}

	// write to file, this time, attempt to direcly invoke gnuplot (the second, Boolean parameter for the plot2d-function)
	plotter.setFilename( "Bball_out" );
	plotter.plot2d( PLOTTYPE::tex, true );
	plotter.plot2d( PLOTTYPE::png, true );
	plotter.plot2d( PLOTTYPE::eps, true );

	return 0;
}
