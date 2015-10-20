/**
 * Example file for polytope reduction.
 * @brief [brief description]
 * @details [long description]
 *
 */

 #include "../src/lib/util/Plotter.h"
 #include "../src/lib/datastructures/Hyperplane.h"
 #include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"
 #include "../src/lib/representations/volumeApproximation.h"

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

  HPolytope<Number> unite_compare;
  unite_compare.insert(Hyperplane<Number>({-1,0},5));
  unite_compare.insert(Hyperplane<Number>({0.1,1},1));
  unite_compare.insert(Hyperplane<Number>({1,1.1},5));
  unite_compare.insert(Hyperplane<Number>({0,-1},1));

  HPolytope<Number> reduce_from = nico;

  unsigned facet=0;
  HPolytope<Number> reduction = reduce_from.reduce(0,facet);
  HPolytope<Number> reduction2 = reduce_from.reduce(1,facet);
	HPolytope<Number> reduction3 = reduce_from.reduce(2,facet);
  HPolytope<Number> reduction4 = reduce_from.reduce(3,facet);
  HPolytope<Number> reduction5 = reduce_from.reduce(4,facet);
  HPolytope<Number> reduction6 = reduce_from.reduce(5,facet);

  std::cout << "volume of reduction (drop_normal) red: " << approximateVolume<Number, hypro::HPolytope<Number>>(reduction) << std::endl;
  std::cout << "volume of reduction2 (drop_smooth) green: " << approximateVolume<Number, hypro::HPolytope<Number>>(reduction2) << std::endl;
  std::cout << "volume of reduction3 (unite_normal) orange: " << approximateVolume<Number, hypro::HPolytope<Number>>(reduction3) << std::endl;
  std::cout << "volume of reduction4 (unite_smooth) violett: " << approximateVolume<Number, hypro::HPolytope<Number>>(reduction4) << std::endl;
  std::cout << "volume of reduction5 (unite_cut) orange: " << approximateVolume<Number, hypro::HPolytope<Number>>(reduction5) << std::endl;
  std::cout << "volume of reduction6 (unite_norm) violett: " << approximateVolume<Number, hypro::HPolytope<Number>>(reduction6) << std::endl;

	unsigned r1 = plotter.addObject(reduction.vertices());
  unsigned r2 = plotter.addObject(reduction2.vertices());
  unsigned r3 = plotter.addObject(reduction3.vertices());
  unsigned r4 = plotter.addObject(reduction4.vertices());
  unsigned r5 = plotter.addObject(reduction5.vertices());
  unsigned r6 = plotter.addObject(reduction6.vertices());
	plotter.addObject(reduce_from.vertices());

	plotter.setObjectColor(r1, colors[red]);
  plotter.setObjectColor(r2, colors[green]);
  plotter.setObjectColor(r3, colors[orange]);
  plotter.setObjectColor(r4, colors[violett]);
  plotter.setObjectColor(r5, colors[turquoise]);
  plotter.setObjectColor(r6, colors[bordeaux]);



	plotter.plot2d();


	return 0;
}
