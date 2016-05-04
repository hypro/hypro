
#include "../lib/representations/GeometricObject.h"
#include "../lib/datastructures/Halfspace.h"
#include "../lib/util/Plotter.h"

int main(int argc, char const *argv[])
{
	typedef cln::cl_RA Number;
	hypro::matrix_t<Number> A = hypro::matrix_t<Number>::Zero(3,3);
	A(0,0) = 1;
	A(1,1) = carl::convert<double,Number>(carl::cos(45));
	A(1,2) = carl::convert<double,Number>(-carl::sin(45));
	A(2,1) = carl::convert<double,Number>(carl::sin(45));
	A(2,2) = carl::convert<double,Number>(carl::cos(45));

	hypro::vector_t<Number> b = hypro::vector_t<Number>::Zero(3);

	hypro::Box<Number> testbox(std::make_pair(hypro::Point<Number>({-2,2,-4}), hypro::Point<Number>({2,4,-2})));

	std::vector<hypro::Point<Number>> tvertices = testbox.vertices();
	for(const auto& vertex : tvertices)
		std::cout << vertex << std::endl;

	std::cout << testbox << std::endl;

	hypro::Box<Number> res = testbox.linearTransformation(A,b);

	std::cout << res << std::endl;

	std::vector<hypro::Point<Number>> vertices = res.vertices();
	for(const auto& vertex : vertices)
		std::cout << vertex << std::endl;

	std::cout << "Manual computation" << std::endl;

	std::vector<hypro::Point<Number>> originalVertices = testbox.vertices();
	for(auto& v : originalVertices){
		std::cout << v << " -> ";
		v = A*v.rawCoordinates();
		std::cout << v << std::endl;
	}

	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();

	hypro::Box<Number> testbox2(std::make_pair(hypro::Point<Number>({-2,-2}), hypro::Point<Number>({2,2})));
	hypro::matrix_t<Number> normal = hypro::matrix_t<Number>(1,2);
	hypro::vector_t<Number> offset = hypro::vector_t<Number>(1);
	normal << 1,1;
	offset << carl::rationalize<Number>(-0.5);
	hypro::vector_t<Number> hsNormal = hypro::vector_t<Number>(2);
	hsNormal << 1,1;
	hypro::Halfspace<Number> cutter = hypro::Halfspace<Number>(hsNormal, carl::rationalize<Number>(-0.5));
	plotter.addObject(cutter);
	unsigned original = plotter.addObject(testbox2.vertices());
	unsigned cutted = plotter.addObject(testbox2.satisfiesHalfspaces(normal, offset).second.vertices());

	plotter.setObjectColor(original, hypro::colors[hypro::green]);
	plotter.setObjectColor(cutted, hypro::colors[hypro::red]);

	plotter.plot2d();


	hypro::Box<Number> testResBox(originalVertices);
	std::cout << testResBox << std::endl;
}
