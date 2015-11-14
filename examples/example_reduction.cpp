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

  // HPolytopes Examples

  // 2D
	HPolytope<Number> nico; //NikolausHaus
  nico.insert(Hyperplane<Number>({-1,1},1));
	nico.insert(Hyperplane<Number>({1,1},1));
  nico.insert(Hyperplane<Number>({1,0},1));
	nico.insert(Hyperplane<Number>({0,-1},1));
  nico.insert(Hyperplane<Number>({-1,0},1));

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

  // 3D
  HPolytope<Number> td_example;
  td_example.insert(Hyperplane<Number>({0, 0, -1},0)); // a      0
  td_example.insert(Hyperplane<Number>({1, 0, 0.1},3)); // b     1
  td_example.insert(Hyperplane<Number>({-1, -1, 0.1},3)); // c   2
  td_example.insert(Hyperplane<Number>({0, 1, 0.1},3)); // d     3
  td_example.insert(Hyperplane<Number>({0, 0, 1},2)); // e       4

  HPolytope<Number> td_example2;
  td_example2.insert(Hyperplane<Number>({0, 0, -1},0)); // a      0
  td_example2.insert(Hyperplane<Number>({1, 0, 0.1},3)); // b     1
  td_example2.insert(Hyperplane<Number>({-1, -1, 0.1},3)); // c   2
  td_example2.insert(Hyperplane<Number>({0, 1, 0.1},3)); // d     3
  td_example2.insert(Hyperplane<Number>({-0.1, 0, 1},2)); // e       4

  HPolytope<Number> cube;
  cube.insert(Hyperplane<Number>({ 0,  0, -1}, 1));
  cube.insert(Hyperplane<Number>({ 0,  0,  1}, 1));
  cube.insert(Hyperplane<Number>({-1,  0,  0}, 1));
  cube.insert(Hyperplane<Number>({ 1,  0,  0}, 1));
  cube.insert(Hyperplane<Number>({ 0, -1,  0}, 1));
  cube.insert(Hyperplane<Number>({ 0,  1,  0}, 1));

  HPolytope<Number> sword;
  sword.insert(Hyperplane<Number>({ 0,  0, -1}, 1));
  sword.insert(Hyperplane<Number>({ 0,  0,  1}, 1));
  sword.insert(Hyperplane<Number>({-1, -0.1,  0}, 1));
  sword.insert(Hyperplane<Number>({ 1, -0.1,  0}, 1));
  sword.insert(Hyperplane<Number>({-1,  0.1,  0}, 1));
  sword.insert(Hyperplane<Number>({ 1,  0.1,  0}, 1));

  HPolytope<Number> ship; // cut tetrader
  ship.insert(Hyperplane<Number>({ 0,  0,  1}, 0));
  ship.insert(Hyperplane<Number>({-1,  0, -1}, 1));
  ship.insert(Hyperplane<Number>({ 1,  0, -1}, 1));
  ship.insert(Hyperplane<Number>({ 0, -1,  1}, 1));
  ship.insert(Hyperplane<Number>({ 0,  1,  1}, 1));

  HPolytope<Number> house;
  house.insert(Hyperplane<Number>({ 0,  0, -1}, 1));
  house.insert(Hyperplane<Number>({-1,  0,  0}, 1));
  house.insert(Hyperplane<Number>({ 1,  0,  0}, 1));
  house.insert(Hyperplane<Number>({ 0, -1,  0}, 1));
  house.insert(Hyperplane<Number>({ 0,  1,  0}, 1));

  house.insert(Hyperplane<Number>({ 1,  1,  1}, 1)); //roof
  house.insert(Hyperplane<Number>({ 1, -1,  1}, 1));
  house.insert(Hyperplane<Number>({-1,  1,  1}, 1));
  house.insert(Hyperplane<Number>({-1, -1,  1}, 1));


  // init reduce_HPolytopes
  HPolytope<Number> reduce_from = nico;

  HPolytope<Number> reduction_drop_normal;
  HPolytope<Number> reduction_drop_smooth;
  HPolytope<Number> reduction_unite_normal;
  HPolytope<Number> reduction_unite_smooth;
  HPolytope<Number> reduction_unite_cut;
  HPolytope<Number> reduction_unite_norm;
  HPolytope<Number> reduction_directed;

  // calculate volume of HPolytope reduce_from
  double prevVolume = approximateVolume<Number, hypro::HPolytope<Number>>(reduce_from);
  std::cout << "previous Volume is " << prevVolume << std::endl << std::endl;

  // Reducing
  std::cout << "\nDROP\n------------------------------------" << std::endl;

  //unsigned facet =1; // reduce one specific facet
  //for(unsigned facet=0; facet < reduce_from.size(); facet++){ // reduce all facets
  //  std::cout << "facet[" << facet << "]" << std::endl;

  //  // reduce and display the increase of the volume
  //  reduction_drop_normal = reduce_from.reduce_nd(0, facet);
  //  std::cout << "volume of drop_normal (red): +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_drop_normal)-prevVolume)/prevVolume)*100 << "% \n" << std::endl;
  //  reduction_drop_smooth = reduce_from.reduce_nd(1, facet);
  //  std::cout << "volume of drop_smooth (green): +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_drop_smooth)-prevVolume)/prevVolume)*100 << "% \n" << std::endl;
  //}


  //// reduce unite - take care of correct neighbor-relation
  //std::cout << "\nUNITE\n------------------------------------" << std::endl;

  //for(unsigned facet1=0; facet1 < reduce_from.size()-1; facet1++){
  //  for(unsigned facet2=facet1+1; facet2 < reduce_from.size(); facet2++){
  //    std::cout << "facet[" << facet2 << "] and facet[" << facet1 << "]" << std::endl;

  //    reduction_unite_normal = reduce_from.reduce_nd(2, facet2, facet1);
  //    std::cout << "volume of unite_normal (orange): +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_normal)-prevVolume)/prevVolume)*100 << "% \n" << std::endl;
  //    reduction_unite_smooth = reduce_from.reduce_nd(3, facet2, facet1);
  //    std::cout << "volume of unite_smooth (violett): +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_smooth)-prevVolume)/prevVolume)*100 << "% \n" << std::endl;
  //    reduction_unite_cut = reduce_from.reduce_nd(4, facet2, facet1);
  //    std::cout << "volume of unite_cut (turquoise): +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_cut)-prevVolume)/prevVolume)*100 << "% \n" << std::endl;

  //  }
  //}

  std::cout << "\nDIRECTED\n------------------------------------" << std::endl;
  vector_t<double> directed = vector_t<double>(2);
		directed(0) = -1;
		directed(1) = -1;
		//directed(2) = 1;
  reduction_directed = reduce_from.reduce_directed(directed);
  std::cout << "volume of directed (unknown): +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_directed)-prevVolume)/prevVolume)*100 << "% \n" << std::endl;


  // End Reducing


  // Prepare plotting - Reducing to 2d
  unsigned i=0,j=1;
  std::vector<Point<Number>> reduce_from_vertices_2d,
                            reduction_drop_normal_vertices_2d,
                            reduction_drop_smooth_vertices_2d,
                            reduction_unite_normal_vertices_2d,
                            reduction_unite_smooth_vertices_2d,
                            reduction_unite_cut_vertices_2d,
                            reduction_unite_norm_vertices_2d,
                            reduction_directed_vertices_2d;

  //for(Point<Number> point: reduce_from.vertices()){
  //  //std::cout << "Point of reduce_from: " << point << std::endl;
  //  point.reduceToDimensions({i,j});
  //  reduce_from_vertices_2d.push_back(point);
  //}
  //for(Point<Number> point: reduction_drop_normal.vertices()){
  //  point.reduceToDimensions({i,j});
  //  reduction_drop_normal_vertices_2d.push_back(point);
  //}
  //for(Point<Number> point: reduction_drop_smooth.vertices()){
  //  point.reduceToDimensions({i,j});
  //  reduction_drop_smooth_vertices_2d.push_back(point);
  //}
  //for(Point<Number> point: reduction_unite_normal.vertices()){
  //  point.reduceToDimensions({i,j});
  //  reduction_unite_normal_vertices_2d.push_back(point);
  //}
  //for(Point<Number> point: reduction_unite_smooth.vertices()){
  //  point.reduceToDimensions({i,j});
  //  reduction_unite_smooth_vertices_2d.push_back(point);
  //}
  //for(Point<Number> point: reduction_unite_cut.vertices()){
  //  point.reduceToDimensions({i,j});
  //  reduction_unite_cut_vertices_2d.push_back(point);
  //}
  //for(Point<Number> point: reduction_unite_norm.vertices()){
  //  point.reduceToDimensions({i,j});
  //  reduction_unite_norm_vertices_2d.push_back(point);
  //}
  //for(Point<Number> point: reduction_directed.vertices()){
  //  point.reduceToDimensions({i,j});
  //  reduction_directed_vertices_2d.push_back(point);
  //}

  // Plotting
  //3D
	//unsigned rdn = plotter.addObject(reduction_drop_normal_vertices_2d);
  //unsigned rds = plotter.addObject(reduction_drop_smooth_vertices_2d);
  //unsigned run = plotter.addObject(reduction_unite_normal_vertices_2d);
  //unsigned rus = plotter.addObject(reduction_unite_smooth_vertices_2d);
  //unsigned ruc = plotter.addObject(reduction_unite_cut_vertices_2d);
  //unsigned runo = plotter.addObject(reduction_unite_norm_vertices_2d);
  //unsigned ruso = plotter.addObject(reduction_unite_smooth_old_vertices_2d);
  //unsigned rd = plotter.addObject(reduction_directed_vertices_2d);
	//plotter.addObject(reduce_from_vertices_2d);

  //2D
  plotter.addObject(reduce_from.vertices());
  unsigned rd = plotter.addObject(reduction_directed.vertices());

  plotter.setObjectColor(rd, colors[red]); // TODO color for directed
  //plotter.setObjectColor(rdn, colors[red]);
  //plotter.setObjectColor(rds, colors[green]);
  //plotter.setObjectColor(run, colors[orange]);
  //plotter.setObjectColor(rus, colors[violett]);
  //plotter.setObjectColor(ruc, colors[turquoise]);
  //plotter.setObjectColor(runo, colors[bordeaux]);

	plotter.plot2d();

	return 0;
}
