/**
 * \example example_plot.cpp This file shows how to use the plotter.
 */

#include "datastructures/Point.h"
#include "representations/GeometricObjectBase.h"
#include "util/plotting/Plotter.h"

#include <random>

using namespace hypro;

int main() {
	typedef double Number;

	// get reference to singleton plotter
	Plotter<Number>& plotter = Plotter<Number>::getInstance();

	double lower_bound = 0;
	double upper_bound = 0.2;
	std::uniform_real_distribution<double> unif( lower_bound, upper_bound );
	std::default_random_engine re;
	// double a_random_double = unif(re);

	// define starting point(s)
	int samples = 2;
	std::vector<hypro::Point<Number>> points;
	points.push_back( hypro::Point<Number>{ 0, 0.1, 1, 0.1, 1 } );
	points.push_back( hypro::Point<Number>{ 0, 0, 1, 0.1, 1 } );
	points.push_back( hypro::Point<Number>{ 0, 0.2, 1, 0.1, 1 } );

	while ( samples > 0 ) {
		points.push_back( hypro::Point<Number>{ 0, unif( re ), 1, 0.1, 1 } );
		--samples;
	}

	hypro::matrix_t<Number> A = hypro::matrix_t<Number>( 5, 5 );
	A << 1, 0, 0.001, 0, 0, 0, 1, 0, 0.001, 0.000000375, 0, 0, 1, 0, 0, 0, -0.001,
		  0, 1, 0.00075, 0, 0, 0, 0, 1;

	for ( int i = 0; i < 8000; ++i ) {
		for ( auto& p : points ) {
			auto t = p.linearTransformation( A );
			plotter.addObject( { p.projectOn( { 0, 1 } ), t.projectOn( { 0, 1 } ) } );
			p = std::move( t );
		}
	}

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
