/**
 * Example file for linear transformation of a H-Polytope.
 * @brief [brief description]
 * @details [long description]
 *
 */

 #include "../src/hypro/util/Plotter.h"
 #include "../src/hypro/datastructures/Halfspace.h"
 #include "../src/hypro/representations/GeometricObject.h"

using namespace hypro;

int main()
{
	typedef mpq_class Number;

	HPolytope<Number> box;
	box.insert(Halfspace<Number>({Number(1),Number(0)},Number(1)));
	box.insert(Halfspace<Number>({Number(0),Number(1)},Number(1)));
	box.insert(Halfspace<Number>({Number(-1),Number(0)},Number(1)));
	box.insert(Halfspace<Number>({Number(0),Number(-1)},Number(1)));

	matrix_t<Number> A = matrix_t<Number>(2,2);
	A << 2,0,0,2;
	vector_t<Number> b = vector_t<Number>(2);
	b << 5,0;

	HPolytope<Number> boxTrafoed = box.affineTransformation(A,b);
	//HPolytope<Number> boxTrafoed = box.linearTransformation(A,vector_t<Number>::Zero(2));
	std::cout << boxTrafoed << std::endl;

	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	plotter.addObject(box.vertices());
	unsigned obj2 = plotter.addObject(boxTrafoed.vertices());
	plotter.setObjectColor(obj2, plotting::colors[plotting::red]);

	plotter.plot2d();

	return 0;
}
