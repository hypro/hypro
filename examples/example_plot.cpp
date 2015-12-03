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
#include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"

using namespace hypro;

int main(int argc, char** argv) {

	Plotter<double>& plotter = Plotter<double>::getInstance();

	HPolytope<double> poly;
	poly.insert(Hyperplane<double>({1,1},1));
	poly.insert(Hyperplane<double>({-1,1},1));
	poly.insert(Hyperplane<double>({0,-1},1));

	std::vector<Point<double>> vertices = poly.vertices();

	plotter.addObject(vertices);

	std::cout << "Added points." << std::endl;

	plotter.addObject(poly.constraints());

	std::cout << "Added planes." << std::endl;

	plotter.addPoint(Point<double>({-1.5,3}));

	std::cout << "Added point." << std::endl;

	plotter.plot2d();

	return 0;
}
