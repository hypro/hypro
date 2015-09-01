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

	VertexContainer<FLOAT_T<double>> container;
	container.insert(Point<FLOAT_T<double>>({3,3}), true);
	container.insert(Point<FLOAT_T<double>>({5,3}), false);
	container.insert(Point<FLOAT_T<double>>({5,5}), true);
	container.insert(Point<FLOAT_T<double>>({7,5}), false);
	container.insert(Point<FLOAT_T<double>>({7,6}), false);
	container.insert(Point<FLOAT_T<double>>({3,6}), false);

	VertexContainer<FLOAT_T<double>> container2;
	container2.insert(Point<FLOAT_T<double>>({1,1}), true);
	container2.insert(Point<FLOAT_T<double>>({1,2}), true);
	container2.insert(Point<FLOAT_T<double>>({2,1}), true);
	container2.insert(Point<FLOAT_T<double>>({2,2}), true);

	OrthogonalPolyhedron<FLOAT_T<double>> test(container);
	//OrthogonalPolyhedron<FLOAT_T<double>> test2(container2);

	std::vector<Point<FLOAT_T<double>>> neighborhood = test.neighborhood(Point<FLOAT_T<double>>({2,4}));
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

	unsigned testId = plotter.addObject(test.preparePlot(0,1), false);
	//unsigned test2Id = plotter.addObject(test2.preparePlot(0,1), false);

	//OrthogonalPolyhedron<FLOAT_T<double>> united = test.unite(test2);
	//for(const auto& vertex : united.vertices()) {
	//	std::cout << vertex << std::endl;
	//}

	//OrthogonalPolyhedron<FLOAT_T<double>> intersection = test.intersect(test2);
	//for(const auto& vertex : united.vertices()) {
	//	std::cout << vertex << std::endl;
	//}

	//unsigned unionObject = plotter.addObject(united.preparePlot(0,1), false);

	//plotter.setObjectColor(unionObject, "#F6A800");

	plotter.plot2d();

	return 0;
}
