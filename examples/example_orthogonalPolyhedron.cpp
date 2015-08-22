/**
 * This file shows how to use the plotter.
 * @file example_plot.cpp
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since	2015-03-01
 * @version	2015-03-01
 */

#include "../src/lib/util/Plotter.h"
#include "../src/lib/representations/OrthogonalPolyhedron/OrthogonalPolyhedron.h"

using namespace hypro;

int main(int argc, char** argv) {
	VertexContainer<int> container;
	container.insert(Point<int>({2,4}), true);
	container.insert(Point<int>({1,4}), false);
	container.insert(Point<int>({2,5}), false);
	container.insert(Point<int>({1,3}), true);
	container.insert(Point<int>({4,5}), false);
	container.insert(Point<int>({4,2}), false);
	container.insert(Point<int>({2,2}), true);	
	container.insert(Point<int>({2,3}), true);

	OrthogonalPolyhedron<int> test(container);

	// plot
	hypro::Plotter<int>& plotter = hypro::Plotter<int>::getInstance();

	plotter.addObject(test.preparePlot(0,1));

	plotter.plot2d();

	return 0;
}