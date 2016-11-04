/**
 * This file shows how to use the plotter.
 * @file example_plot.cpp
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-03-01
 * @version	2015-03-01
 */

#include "config.h"
#include "util/Plotter.h"
#include "representations/GeometricObject.h"

using namespace hypro;
using namespace carl;

int main(int argc, char** argv) {

	VertexContainer<double> container;
	container.insert(Point<double>({3,0}), true);
	container.insert(Point<double>({5,0}), false);
	container.insert(Point<double>({5,2}), true);
	container.insert(Point<double>({7,2}), true);
	container.insert(Point<double>({7,0}), true);
	container.insert(Point<double>({9,0}), false);
	container.insert(Point<double>({9,2}), true);
	container.insert(Point<double>({11,2}), false);
	container.insert(Point<double>({11,4}), false);
	container.insert(Point<double>({9,4}), false);
	container.insert(Point<double>({9,7}), false);
	container.insert(Point<double>({7,6}), true);
	container.insert(Point<double>({7,4}), true);
	container.insert(Point<double>({5,4}), false);
	container.insert(Point<double>({5,6}), true);
	container.insert(Point<double>({3,7}), false);

	// container.insert(Point<double>({2,0}), true);
	// container.insert(Point<double>({6,0}), false);
	// container.insert(Point<double>({2,6}), false);
	// container.insert(Point<double>({6,6}), false);

	VertexContainer<double> container2;
	container2.insert(Point<double>({4,2}), true);
	container2.insert(Point<double>({4,8}), false);
	container2.insert(Point<double>({8,2}), false);
	container2.insert(Point<double>({8,8}), false);

	OrthogonalPolyhedron<double, Converter<double>> test(container);
	OrthogonalPolyhedron<double, Converter<double>> test2(container2);

	// std::cout << "Color Test:" << std::endl;
	// Point<double> p1({6,4});
	// Point<double> p2({2,4});
	// Point<double> p3({4,6});
	// Point<double> p4({4,2});
	// Point<double> p5({5.9,4});
	// assert(test.contains(p1));
	// assert(test.contains(p2));
	// assert(test.contains(p3));
	// assert(test.contains(p4));
	// assert(test.contains(p5));
	// std::cout << "Color Test End." << std::endl;

	std::vector<Point<double>> neighborhood = test.neighborhood(Point<double>({20,40}));
	std::cout << "neighborhood: " << std::endl;
	for(const auto& point : neighborhood) {
		std::cout << point << std::endl;
	}

	std::vector<Point<double>> islice = test.iSlice(0,2);
	std::cout << "0-3-slice: " << std::endl;
	for(const auto& point : islice) {
		std::cout << point << std::endl;
	}

	// plot
	std::cout << "Plotting." << std::endl;
	hypro::Plotter<double>& plotter = hypro::Plotter<double>::getInstance();
	plotter.setFilename("ortho");
	gnuplotSettings settings;
	settings.fill = true;
	plotter.updateSettings(settings);

	// OrthogonalPolyhedron<double> united = test.unite(test2);
	// for(const auto& vertex : united.vertices()) {
	// 	std::cout << vertex << std::endl;
	// }

	OrthogonalPolyhedron<double, Converter<double>> intersection = test.intersect(test2);
	for(const auto& vertex : intersection.vertices()) {
		std::cout << vertex << std::endl;
	}

	/* TODO: Fix plotter to allow direct object adding.
	//unsigned test2Id = plotter.addObject(test2.preparePlot(0,1), false);
	unsigned testId = plotter.addObject(test.preparePlot(0,1), false);
	unsigned intersectionObject = plotter.addObject(intersection.preparePlot(0,1), false);
	// unsigned unionObject = plotter.addObject(united.preparePlot(0,1), false);

	plotter.setObjectColor(intersectionObject, colors[orange]);
	//plotter.setObjectColor(unionObject, colors[orange]);

	plotter.plot2d();
	*/
	return 0;
}
