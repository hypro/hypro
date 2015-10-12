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
	typedef double Number;

	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	gnuplotSettings settings;
	//settings.fill = true;
	plotter.updateSettings(settings);

	/* Do stuff here */

	HPolytope<Number> poly; //NikolausHaus
  poly.insert(Hyperplane<Number>({-1,1},1));
	poly.insert(Hyperplane<Number>({1,1},1));
  poly.insert(Hyperplane<Number>({1,0.1},1));
	poly.insert(Hyperplane<Number>({0,-1},1));
  poly.insert(Hyperplane<Number>({-1,0},1));


	HPolytope<Number> poly2 = poly.reduce();
	//poly2.insert(Hyperplane<Number>({1,1},1));
	//poly2.insert(Hyperplane<Number>({-1,1},1));
	//poly2.insert(Hyperplane<Number>({0,-1},1));

	unsigned p2 = plotter.addObject(poly2.vertices());
	unsigned p1 = plotter.addObject(poly.vertices());

	plotter.setObjectColor(p2, colors[red]);

	plotter.plot2d();

	return 0;
}
