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

	HPolytope<Number> nico; //NikolausHaus
  nico.insert(Hyperplane<Number>({-1,1},1));
	nico.insert(Hyperplane<Number>({1,1},1));
  nico.insert(Hyperplane<Number>({1,0.1},1));
	nico.insert(Hyperplane<Number>({0,-1},1));
  nico.insert(Hyperplane<Number>({-1,0.5},1));

  HPolytope<Number> square; //Square
  square.insert(Hyperplane<Number>({-1,0},1));
	square.insert(Hyperplane<Number>({0,1},1));
  square.insert(Hyperplane<Number>({1,0},1));
	square.insert(Hyperplane<Number>({0,-1},1));

  HPolytope<Number> rotated_square; //rotated Square
  rotated_square.insert(Hyperplane<Number>({-1,1},1));
	rotated_square.insert(Hyperplane<Number>({1,1},1));
  rotated_square.insert(Hyperplane<Number>({1,-1},1));
	rotated_square.insert(Hyperplane<Number>({-1,-1},1));

  HPolytope<Number> trapez; //trapez for Drop
  trapez.insert(Hyperplane<Number>({-1,0.5},0.6));
	trapez.insert(Hyperplane<Number>({0,1},1));
  trapez.insert(Hyperplane<Number>({1,0.5},0.6));
	trapez.insert(Hyperplane<Number>({0,-1},1));

  HPolytope<Number> trapez2; //trapez for Unite
  trapez2.insert(Hyperplane<Number>({-1,0.5},5));
	trapez2.insert(Hyperplane<Number>({0,1},1));
  trapez2.insert(Hyperplane<Number>({1,0.5},5));
	trapez2.insert(Hyperplane<Number>({0,-1},1));

  HPolytope<Number> trapez3; //trapez for Unite
  trapez3.insert(Hyperplane<Number>({-1,0.5},2));
	trapez3.insert(Hyperplane<Number>({0,1},1));
  trapez3.insert(Hyperplane<Number>({1,0.5},2));
	trapez3.insert(Hyperplane<Number>({0,-1},1));

  HPolytope<Number> equal;
  equal.insert(Hyperplane<Number>({-1,2},2));
  equal.insert(Hyperplane<Number>({1,3},2));
  equal.insert(Hyperplane<Number>({2,1},2));
  equal.insert(Hyperplane<Number>({0,-1},0));

  HPolytope<Number> reduce_from = equal;

	HPolytope<Number> reduction = reduce_from.reduce(0,1);
  HPolytope<Number> reduction2 = reduce_from.reduce(4,0);

	unsigned r1 = plotter.addObject(reduction.vertices());
  unsigned r2 = plotter.addObject(reduction2.vertices());
	plotter.addObject(reduce_from.vertices());

	plotter.setObjectColor(r1, colors[red]);
  plotter.setObjectColor(r2, colors[green]);

	plotter.plot2d();

	return 0;
}
