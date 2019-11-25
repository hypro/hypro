/**
 * Example file for polytope reduction.
 * @brief [brief description]
 * @details [long description]
 *
 */

 #include "util/plotting/Plotter.h"
 #include "datastructures/Halfspace.h"
 #include "representations/GeometricObject.h"

using namespace hypro;

int main()
{
	typedef mpq_class Number;

	HPolytope<Number> box;
	box.insert(Halfspace<Number>({1,0},1));
	box.insert(Halfspace<Number>({0,1},1));
	box.insert(Halfspace<Number>({-1,0},1));
	box.insert(Halfspace<Number>({0,-1},1));
	box.insert(Halfspace<Number>({1,0},2));
	box.insert(Halfspace<Number>({0,1},2));
	box.insert(Halfspace<Number>({-1,0},2));
	box.insert(Halfspace<Number>({0,-1},2));
	box.insert(Halfspace<Number>({1,1},2));

	matrix_t<Number> A = matrix_t<Number>(2,2);
	A << carl::rationalize<mpq_class>(cos(0.5)),2,1.5,1;
	vector_t<Number> b = vector_t<Number>(2);
	b << 5,0;

	box.removeRedundancy();

	std::cout << "End removeRedundantPlanes" << std::endl;

	HPolytope<Number> boxTrafoed = box.affineTransformation(A,b);
	boxTrafoed = boxTrafoed.affineTransformation(A,b);
	boxTrafoed = boxTrafoed.affineTransformation(A,b);
	std::cout << boxTrafoed << std::endl;

	HPolytope<Number> boxReduced = boxTrafoed;
	boxReduced.reduceNumberRepresentation();
	std::cout << boxReduced << std::endl;

	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	plotter.addObject(box.vertices());
	unsigned obj2 = plotter.addObject(boxTrafoed.vertices());
	unsigned obj3 = plotter.addObject(boxReduced.vertices());
	plotter.setObjectColor(obj2, plotting::colors[plotting::red]);
	plotter.setObjectColor(obj3, plotting::colors[plotting::green]);

	plotter.plot2d();

	return 0;
}
