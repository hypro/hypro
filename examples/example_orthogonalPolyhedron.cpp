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

	VertexContainer<FLOAT_T<mpfr_t>> container2;
	container2.insert(Point<FLOAT_T<mpfr_t>>({1,1}), true);
	container2.insert(Point<FLOAT_T<mpfr_t>>({1,2}), true);
	container2.insert(Point<FLOAT_T<mpfr_t>>({2,1}), true);
	container2.insert(Point<FLOAT_T<mpfr_t>>({2,2}), true);

	OrthogonalPolyhedron<FLOAT_T<mpfr_t>> test(container);
	OrthogonalPolyhedron<FLOAT_T<mpfr_t>> test2(container2);

	std::vector<Point<FLOAT_T<mpfr_t>>> neighborhood = test.neighborhood(Point<FLOAT_T<mpfr_t>>({2,4}));
	std::cout << "neighborhood: " << std::endl;
	for(const auto& point : neighborhood) {
		std::cout << point << std::endl;
	}

	std::vector<Point<FLOAT_T<mpfr_t>>> islice = test.iSlice(0,2);
	std::cout << "0-3-slice: " << std::endl;
	for(const auto& point : islice) {
		std::cout << point << std::endl;
	}

	// plot
	std::cout << "Plotting." << std::endl;
	hypro::Plotter<FLOAT_T<mpfr_t>>& plotter = hypro::Plotter<FLOAT_T<mpfr_t>>::getInstance();
	plotter.setFilename("ortho");
	gnuplotSettings settings;
	settings.fill = true;
	plotter.updateSettings(settings);

	//unsigned testId = plotter.addObject(test.preparePlot(0,1), false);
	unsigned test2Id = plotter.addObject(test2.preparePlot(0,1), false);

	OrthogonalPolyhedron<FLOAT_T<mpfr_t>> united = test.unite(test2);
	//for(const auto& vertex : united.vertices()) {
	//	std::cout << vertex << std::endl;
	//}

	//OrthogonalPolyhedron<FLOAT_T<mpfr_t>> intersection = test.intersect(test2);
	//for(const auto& vertex : united.vertices()) {
	//	std::cout << vertex << std::endl;
	//}

	unsigned unionObject = plotter.addObject(united.preparePlot(0,1), false);

	plotter.setObjectColor(unionObject, "#F6A800");

	plotter.plot2d();

	return 0;
}
