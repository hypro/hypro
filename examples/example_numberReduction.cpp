/**
 * Example file for polytope reduction.
 * @brief [brief description]
 * @details [long description]
 *
 */

 #include "../src/lib/util/Plotter.h"
 #include "../src/lib/datastructures/Hyperplane.h"
 #include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"

using namespace hypro;

int main(int argc, char const *argv[])
{
	typedef carl::FLOAT_T<mpq_class> Number;

	HPolytope<Number> box;
	box.insert(Hyperplane<Number>({1,0},1));
	box.insert(Hyperplane<Number>({0,1},1));
	box.insert(Hyperplane<Number>({-1,0},1));
	box.insert(Hyperplane<Number>({0,-1},1));
	box.insert(Hyperplane<Number>({1,0},2));
	box.insert(Hyperplane<Number>({0,1},2));
	box.insert(Hyperplane<Number>({-1,0},2));
	box.insert(Hyperplane<Number>({0,-1},2));
	box.insert(Hyperplane<Number>({1,1},2));

	matrix_t<Number> A = matrix_t<Number>(2,2);
	A << carl::rationalize<mpq_class>(cos(0.5)),2,1.5,1;
	vector_t<Number> b = vector_t<Number>(2);
	b << 5,0;

	box.removeRedundantPlanes();

	std::cout << "End removeRedundantPlanes" << std::endl;

	HPolytope<Number> boxTrafoed = box.linearTransformation(A,b);
	boxTrafoed = boxTrafoed.linearTransformation(A,b);
	boxTrafoed = boxTrafoed.linearTransformation(A,b);
	std::cout << boxTrafoed << std::endl;

	HPolytope<Number> boxReduced = boxTrafoed;
	boxReduced.reduceNumberRepresentation();
	std::cout << boxReduced << std::endl;

	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	unsigned obj1 = plotter.addObject(box.vertices());
	unsigned obj2 = plotter.addObject(boxTrafoed.vertices());
	unsigned obj3 = plotter.addObject(boxReduced.vertices());
	plotter.setObjectColor(obj2, colors[red]);
	plotter.setObjectColor(obj3, colors[green]);

	plotter.plot2d();

	return 0;
}
