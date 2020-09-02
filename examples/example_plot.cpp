/**
 * \example example_plot.cpp This file shows how to use the plotter.
 */

#include "representations/GeometricObjectBase.h"
#include "util/plotting/Plotter.h"

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
	plotter.plot2d();
	plotter.plotTex();
	plotter.plotEps();

	return 0;
}
