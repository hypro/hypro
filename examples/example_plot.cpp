/**
 * \example example_plot.cpp This file shows how to use the plotter.
 */

#include "util/plotting/Plotter.h"
#include "representations/GeometricObject.h"

using namespace hypro;

int main() {

	typedef double Number;

	Plotter<Number>& plotter = Plotter<Number>::getInstance();

	HPolytope<Number> poly;
	poly.insert(Halfspace<Number>({1,1},1));
	poly.insert(Halfspace<Number>({-1,1},1));
	poly.insert(Halfspace<Number>({0,-1},1));

	std::vector<Point<Number>> vertices = poly.vertices();

	plotter.addObject(vertices);

	plotter.addObject(poly.constraints());
	plotter.addObject(Halfspace<Number>({1,0},1));

	plotter.addPoint(Point<Number>({carl::rationalize<Number>(-1.5),3}));

	plotter.plot2d();
	plotter.plotTex();
	plotter.plotEps();

	return 0;
}
