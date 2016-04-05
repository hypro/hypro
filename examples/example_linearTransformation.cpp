/**
 * Example file for linear transformation of a H-Polytope.
 * @brief [brief description]
 * @details [long description]
 *
 */

 #include "../src/lib/util/Plotter.h"
 #include "../src/lib/datastructures/Halfspace.h"
 #include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"

using namespace hypro;

int main(int argc, char const *argv[])
{
	typedef carl::FLOAT_T<mpq_class> Number;

	HPolytope<Number> box;
	box.insert(Halfspace<Number>({1,0},1));
	box.insert(Halfspace<Number>({0,1},1));
	box.insert(Halfspace<Number>({-1,0},1));
	box.insert(Halfspace<Number>({0,-1},1));

	matrix_t<Number> A = matrix_t<Number>(2,2);
	A << 2,0,0,2;
	vector_t<Number> b = vector_t<Number>(2);
	b << 5,0;

	HPolytope<Number> boxTrafoed = box.linearTransformation(A,b);
	//HPolytope<Number> boxTrafoed = box.linearTransformation(A,vector_t<Number>::Zero(2));
	std::cout << boxTrafoed << std::endl;

	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	unsigned obj1 = plotter.addObject(box.vertices());
	unsigned obj2 = plotter.addObject(boxTrafoed.vertices());
	plotter.setObjectColor(obj2, colors[red]);

	plotter.plot2d();

	return 0;
}
