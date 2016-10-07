/**
 * This file shows how to use the plotter.
 * @file example_plot.cpp
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-03-01
 * @version	2015-03-01
 */

#include "../src/hypro/config.h"
#include "../src/hypro/util/Plotter.h"
#include "../src/hypro/representations/OrthogonalPolyhedron/OrthogonalPolyhedron.h"

using namespace hypro;
using namespace carl;

int main(int argc, char** argv) {

	VertexContainer<FLOAT_T<double>> container;
	container.insert(Point<FLOAT_T<double>>({3,0}), true);
	container.insert(Point<FLOAT_T<double>>({5,0}), false);
	container.insert(Point<FLOAT_T<double>>({5,2}), true);
	container.insert(Point<FLOAT_T<double>>({7,2}), true);
	container.insert(Point<FLOAT_T<double>>({7,0}), true);
	container.insert(Point<FLOAT_T<double>>({9,0}), false);
	container.insert(Point<FLOAT_T<double>>({9,2}), true);
	container.insert(Point<FLOAT_T<double>>({11,2}), false);
	container.insert(Point<FLOAT_T<double>>({11,4}), false);
	container.insert(Point<FLOAT_T<double>>({9,4}), false);
	container.insert(Point<FLOAT_T<double>>({9,7}), false);
	container.insert(Point<FLOAT_T<double>>({7,6}), true);
	container.insert(Point<FLOAT_T<double>>({7,4}), true);
	container.insert(Point<FLOAT_T<double>>({5,4}), false);
	container.insert(Point<FLOAT_T<double>>({5,6}), true);
	container.insert(Point<FLOAT_T<double>>({3,7}), false);

	// container.insert(Point<FLOAT_T<double>>({2,0}), true);
	// container.insert(Point<FLOAT_T<double>>({6,0}), false);
	// container.insert(Point<FLOAT_T<double>>({2,6}), false);
	// container.insert(Point<FLOAT_T<double>>({6,6}), false);

	VertexContainer<FLOAT_T<double>> container2;
	container2.insert(Point<FLOAT_T<double>>({4,2}), true);
	container2.insert(Point<FLOAT_T<double>>({4,8}), false);
	container2.insert(Point<FLOAT_T<double>>({8,2}), false);
	container2.insert(Point<FLOAT_T<double>>({8,8}), false);

	OrthogonalPolyhedron<FLOAT_T<double>> test(container);
	OrthogonalPolyhedron<FLOAT_T<double>> test2(container2);

	// std::cout << "Color Test:" << std::endl;
	// Point<FLOAT_T<double>> p1({6,4});
	// Point<FLOAT_T<double>> p2({2,4});
	// Point<FLOAT_T<double>> p3({4,6});
	// Point<FLOAT_T<double>> p4({4,2});
	// Point<FLOAT_T<double>> p5({5.9,4});
	// assert(test.contains(p1));
	// assert(test.contains(p2));
	// assert(test.contains(p3));
	// assert(test.contains(p4));
	// assert(test.contains(p5));
	// std::cout << "Color Test End." << std::endl;

	std::vector<Point<FLOAT_T<double>>> neighborhood = test.neighborhood(Point<FLOAT_T<double>>({20,40}));
	std::cout << "neighborhood: " << std::endl;
	for(const auto& point : neighborhood) {
		std::cout << point << std::endl;
	}

	std::vector<Point<FLOAT_T<double>>> islice = test.iSlice(0,2);
	std::cout << "0-3-slice: " << std::endl;
	for(const auto& point : islice) {
		std::cout << point << std::endl;
	}

	// plot
	std::cout << "Plotting." << std::endl;
	hypro::Plotter<FLOAT_T<double>>& plotter = hypro::Plotter<FLOAT_T<double>>::getInstance();
	plotter.setFilename("ortho");
	gnuplotSettings settings;
	settings.fill = true;
	plotter.updateSettings(settings);

	// OrthogonalPolyhedron<FLOAT_T<double>> united = test.unite(test2);
	// for(const auto& vertex : united.vertices()) {
	// 	std::cout << vertex << std::endl;
	// }

	OrthogonalPolyhedron<FLOAT_T<double>> intersection = test.intersect(test2);
	for(const auto& vertex : intersection.vertices()) {
		std::cout << vertex << std::endl;
	}

	//unsigned test2Id = plotter.addObject(test2.preparePlot(0,1), false);
	unsigned testId = plotter.addObject(test.preparePlot(0,1), false);
	unsigned intersectionObject = plotter.addObject(intersection.preparePlot(0,1), false);
	// unsigned unionObject = plotter.addObject(united.preparePlot(0,1), false);

	plotter.setObjectColor(intersectionObject, colors[orange]);
	//plotter.setObjectColor(unionObject, colors[orange]);

	plotter.plot2d();

	return 0;
}
