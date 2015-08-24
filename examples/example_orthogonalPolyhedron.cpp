/**
 * This file shows how to use the plotter.
 * @file example_plot.cpp
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since	2015-03-01
 * @version	2015-03-01
 */

#include "../src/lib/config.h"
#include "../src/lib/util/Plotter.h"
#include "../src/lib/representations/OrthogonalPolyhedron/OrthogonalPolyhedron.h"

using namespace hypro;
using namespace carl;

int main(int argc, char** argv) {

	VertexContainer<FLOAT_T<mpfr_t>> container;
	container.insert(Point<FLOAT_T<mpfr_t>>({2,4}), true);
	container.insert(Point<FLOAT_T<mpfr_t>>({1,4}), false);
	container.insert(Point<FLOAT_T<mpfr_t>>({2,5}), false);
	container.insert(Point<FLOAT_T<mpfr_t>>({1,3}), true);
	container.insert(Point<FLOAT_T<mpfr_t>>({4,5}), false);
	container.insert(Point<FLOAT_T<mpfr_t>>({4,2}), false);
	container.insert(Point<FLOAT_T<mpfr_t>>({2,2}), true);	
	container.insert(Point<FLOAT_T<mpfr_t>>({2,3}), true);
	

	OrthogonalPolyhedron<FLOAT_T<mpfr_t>> test(container);

	// plot
	hypro::Plotter<FLOAT_T<mpfr_t>>& plotter = hypro::Plotter<FLOAT_T<mpfr_t>>::getInstance();
	plotter.setFilename("ortho");
	gnuplotSettings settings;
	settings.fill = true;
	plotter.updateSettings(settings);

	plotter.addObject(test.preparePlot(0,1), false);
	plotter.plot2d();

	return 0;
}