/**
 * This file shows how to use the plotter.
 * @file example_plot.cpp
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-03-01
 * @version	2015-10-05
 */

#include "../src/lib/util/Plotter.h"
#include "../src/lib/representations/GeometricObject.h"

using namespace hypro;

int main(int argc, char** argv) {

	#ifdef USE_CLN_NUMBERS
	typedef cln::cl_RA Number;
	#else
	typedef double Number;
	#endif

	Plotter<Number>& plotter = Plotter<Number>::getInstance();

	HPolytope<Number> poly;
	poly.insert(Halfspace<Number>({1,1},1));
	poly.insert(Halfspace<Number>({-1,1},1));
	poly.insert(Halfspace<Number>({0,-1},1));

	std::vector<Point<Number>> vertices = poly.vertices();

	plotter.addObject(vertices);

	std::cout << "Added points." << std::endl;

	plotter.addObject(poly.constraints());
	plotter.addObject(Halfspace<Number>({1,0},1));

	std::cout << "Added planes." << std::endl;

	plotter.addPoint(Point<Number>({-1.5,3}));

	std::cout << "Added point." << std::endl;

	plotter.plot2d();
	plotter.plotTex();

	return 0;
}
