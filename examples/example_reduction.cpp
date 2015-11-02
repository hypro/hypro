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

  HPolytope<Number> tdexample;
  tdexample.insert(Hyperplane<Number>({0, 0, -1},0)); // a      0
  tdexample.insert(Hyperplane<Number>({1, 0, 0.1},3)); // b     1
  tdexample.insert(Hyperplane<Number>({-1, -1, 0.1},3)); // c   2
  tdexample.insert(Hyperplane<Number>({0, 1, 0.1},3)); // d     3
  tdexample.insert(Hyperplane<Number>({0, 0, 1},2)); // e       4

  HPolytope<Number> reduce_from = unite_compare;
  HPolytope<Number> reduction_drop_normal;
  HPolytope<Number> reduction_drop_smooth;
  HPolytope<Number> reduction_unite_normal;
  HPolytope<Number> reduction_unite_smooth;
  HPolytope<Number> reduction_unite_cut;
  HPolytope<Number> reduction_unite_norm;

  double prevVolume = approximateVolume<Number, hypro::HPolytope<Number>>(tdexample);
  std::cout << "previous Volume is " << prevVolume << std::endl << std::endl;

  reduction_drop_normal = tdexample.reduce_nd();
  std::cout << "volume of drop_normal: +" << approximateVolume<Number, hypro::HPolytope<Number>>(reduction_drop_normal)-prevVolume << std::endl;

  // Reducing
  //for(unsigned facet=0; facet < 4; facet++){
  //  reduction_drop_normal = reduce_from.reduce(0,facet);
  //  std::cout << "facet[" << facet << "] volume of drop_normal red: +" << approximateVolume<Number, hypro::HPolytope<Number>>(reduction_drop_normal)-prevVolume << std::endl;
  //  reduction_drop_smooth = reduce_from.reduce(1,facet);
  //  std::cout << "facet[" << facet << "] volume of drop_smooth green: +" << approximateVolume<Number, hypro::HPolytope<Number>>(reduction_drop_smooth)-prevVolume << std::endl;
  //	reduction_unite_normal = reduce_from.reduce(2,facet);
  //  std::cout << "facet[" << facet << "] volume of unite_normal orange: +" << approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_normal)-prevVolume << std::endl;
  //  reduction_unite_smooth = reduce_from.reduce(3,facet);
  //  std::cout << "facet[" << facet << "] volume of unite_smooth violett: +" << approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_smooth)-prevVolume << std::endl;
  //  reduction_unite_cut = reduce_from.reduce(4,facet);
  //  std::cout << "facet[" << facet << "] volume of unite_cut turquoise: +" << approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_cut)-prevVolume << std::endl;
  //  reduction_unite_norm = reduce_from.reduce(5,facet);
  //  std::cout << "facet[" << facet << "] volume of unite_norm bordeaux: +" << approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_norm)-prevVolume << std::endl << std::endl;
  //}

  // Plotting
	//unsigned rdn = plotter.addObject(reduction_drop_normal.vertices());
  //unsigned rds = plotter.addObject(reduction_drop_smooth.vertices());
  //unsigned run = plotter.addObject(reduction_unite_normal.vertices());
  //unsigned rus = plotter.addObject(reduction_unite_smooth.vertices());
  //unsigned ruc = plotter.addObject(reduction_unite_cut.vertices());
  //unsigned runo = plotter.addObject(reduction_unite_norm.vertices());
	//plotter.addObject(reduce_from.vertices());

  //plotter.setObjectColor(rdn, colors[red]);
  //plotter.setObjectColor(rds, colors[green]);
  //plotter.setObjectColor(run, colors[orange]);
  //plotter.setObjectColor(rus, colors[violett]);
  //plotter.setObjectColor(ruc, colors[turquoise]);
  //plotter.setObjectColor(runo, colors[bordeaux]);



	//plotter.plot2d();


	return 0;
}
