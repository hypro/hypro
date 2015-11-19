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
  std::vector<vector_t<Number>> directions;
  unsigned dimension = 3; // set dimension for test object here

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

  HPolytope<Number> diamond;
  //diamond.insert(Hyperplane<Number>({-1,10},1));
  //diamond.insert(Hyperplane<Number>({-1,1.5},5));
  //diamond.insert(Hyperplane<Number>({-1,1.3},2));
  //diamond.insert(Hyperplane<Number>({-1,1.1},3));
  diamond.insert(Hyperplane<Number>({-1,1},5));
  //diamond.insert(Hyperplane<Number>({-1,0.1},1));
  diamond.insert(Hyperplane<Number>({0,1},4));
  //diamond.insert(Hyperplane<Number>({-1,0.1},1));
  diamond.insert(Hyperplane<Number>({1,1},5));
  //diamond.insert(Hyperplane<Number>({1,1.1},3));
  //diamond.insert(Hyperplane<Number>({1,1.3},2));
  //diamond.insert(Hyperplane<Number>({1,1.5},5));
  //diamond.insert(Hyperplane<Number>({1,10},1));


  diamond.insert(Hyperplane<Number>({-1,-1},1));
  diamond.insert(Hyperplane<Number>({1,-1},1));

  vector_t<double> directed2d_1 = vector_t<double>(2);
  directed2d_1(0) = 0.01; directed2d_1(1) = 1;

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
  cube.insert(Hyperplane<Number>({-1,  0,  -1}, 1));
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
  house.insert(Hyperplane<Number>({ 0,  0, -1}, 1)); //floor 0
  house.insert(Hyperplane<Number>({-1,  0,  0}, 1)); //left 1
  house.insert(Hyperplane<Number>({ 1,  0,  0}, 1)); //right 2
  house.insert(Hyperplane<Number>({ 0, -1,  0}, 1)); //back 3
  house.insert(Hyperplane<Number>({ 0,  1,  0}, 1)); //front 4

  house.insert(Hyperplane<Number>({ 1,  1,  1}, 1)); //roof front-right 5
  house.insert(Hyperplane<Number>({ 1, -1,  1}, 1)); //back-right 6
  house.insert(Hyperplane<Number>({-1,  1,  1}, 1)); //front-left 7
  house.insert(Hyperplane<Number>({-1, -1,  1}, 1)); //back-left 8

  vector_t<double> directed3d_1 = vector_t<double>(3);
  directed3d_1(0) = 1; directed3d_1(1) = 1; directed3d_1(2) = 1;
  vector_t<double> directed3d_2 = vector_t<double>(3);
  directed3d_2(0) = 1.1; directed3d_2(1) = -1; directed3d_2(2) = 1;
  vector_t<double> directed3d_3 = vector_t<double>(3);
  directed3d_3(0) = 0.1; directed3d_3(1) = -1; directed3d_3(2) = 1;

  // 4D

  HPolytope<Number> confuse_cube;
  confuse_cube.insert(Hyperplane<Number>({ 0,  0,  0, -1}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 0,  0,  0,  1.1}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 0,  0, -1.2,  0}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 0,  0,  1,  0}, 1));
  confuse_cube.insert(Hyperplane<Number>({-0.9,  0,  0,  0}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 1,  0,  0,  0}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 0, -1.2,  0,  0}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 0,  0.8,  0,  0}, 1));

  vector_t<double> directed4d_1 = vector_t<double>(4);
  directed4d_1(0) = 1; directed4d_1(1) = 1.1; directed4d_1(2) = 0.9; directed4d_1(3) = 1.5;

  // init reduce_HPolytopes
  HPolytope<Number> reduce_from = td_example;

  HPolytope<Number> reduction_drop_normal;
  HPolytope<Number> reduction_drop_smooth;
  HPolytope<Number> reduction_unite_normal;
  HPolytope<Number> reduction_unite_smooth;
  HPolytope<Number> reduction_unite_cut;
  HPolytope<Number> reduction_unite_norm;
  HPolytope<Number> reduction_directed_small;
  HPolytope<Number> reduction_directed_big;

  // calculate volume of HPolytope reduce_from
  double prevVolume = approximateVolume<Number, hypro::HPolytope<Number>>(reduce_from);
  std::cout << "previous Volume is " << prevVolume << std::endl << std::endl;

  // Reducing
  std::cout << "\nDROP\n------------------------------------\nwith drop_normal (red), drop_smooth (green)" << std::endl << std::endl;

  //unsigned facet =1; // reduce one specific facet
  for(unsigned facet=0; facet < reduce_from.size(); facet++){ // reduce all facets
    std::cout << "(facet" << facet << ")" <<  std::endl;

    // reduce and display the increase of the volume
    reduction_drop_normal = reduce_from.reduce_nd(0, facet);
    std::cout << "volume of drop_normal: +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_drop_normal)-prevVolume)/prevVolume)*100 << "%" << std::endl;
    reduction_drop_smooth = reduce_from.reduce_nd(1, facet);
    std::cout << "volume of drop_smooth: +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_drop_smooth)-prevVolume)/prevVolume)*100 << "%" << std::endl;

    std::cout << std::endl;
  }


  // reduce unite - take care of correct neighbor-relation
  std::cout << "\nUNITE\n------------------------------------\nwith unite_normal (orange), unite_smooth (violett), unite_cut (turquoise)" << std::endl << std::endl;
  //unsigned facet1 = 5, facet2 =7;

  for(unsigned facet1=0; facet1 < reduce_from.size()-1; facet1++){
    for(unsigned facet2=facet1+1; facet2 < reduce_from.size(); facet2++){
      std::cout << "(facet" << facet2 << ", facet" << facet1 << ")" << std::endl;

      reduction_unite_normal = reduce_from.reduce_nd(2, facet2, facet1);
      std::cout << "volume of unite_normal: +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_normal)-prevVolume)/prevVolume)*100 << "%" << std::endl;
      reduction_unite_smooth = reduce_from.reduce_nd(3, facet2, facet1);
      std::cout << "volume of unite_smooth: +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_smooth)-prevVolume)/prevVolume)*100 << "%" << std::endl;
      reduction_unite_cut = reduce_from.reduce_nd(4, facet2, facet1);
      std::cout << "volume of unite_cut:    +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_cut)-prevVolume)/prevVolume)*100 << "%" << std::endl;

      std::cout << std::endl;
    }
  }

  std::cout << "\nDIRECTED\n------------------------------------\nwith directed_small (maygreen), directed_big (lila)" << std::endl << std::endl;

  //2D
  if(dimension==2){
    directions.push_back(directed2d_1);
  }

  //3D
  else if(dimension==3){
    directions.push_back(directed3d_1);
    //directions.push_back(directed3d_2);
    //directions.push_back(directed3d_3);
  }

  //4D
  else if(dimension==4){
    directions.push_back(directed4d_1);
  }


  reduction_directed_small = reduce_from.reduce_directed(directions, 6);
  std::cout << "volume of directed_small: +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_directed_small)-prevVolume)/prevVolume)*100 << "%" << std::endl;
  reduction_directed_big = reduce_from.reduce_directed(directions, 7);
  std::cout << "volume of directed_big:   +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_directed_big)-prevVolume)/prevVolume)*100 << "%" << std::endl;

  std::cout << std::endl;
  // End Reducing

  // Plotting
  unsigned rdn, rds, run, rus, ruc, rdis, rdib;
  //3D
  if(dimension==3){
    // Prepare plotting - Reducing to 2d
    unsigned i=0,j=1;
    std::vector<Point<Number>> reduce_from_vertices_2d,
                              reduction_drop_normal_vertices_2d,
                              reduction_drop_smooth_vertices_2d,
                              reduction_unite_normal_vertices_2d,
                              reduction_unite_smooth_vertices_2d,
                              reduction_unite_cut_vertices_2d,
                              reduction_unite_norm_vertices_2d,
                              reduction_directed_small_vertices_2d,
                              reduction_directed_big_vertices_2d;

    for(Point<Number> point: reduce_from.vertices()){
      //std::cout << "Point of reduce_from: " << point << std::endl;
      point.reduceToDimensions({i,j});
      reduce_from_vertices_2d.push_back(point);
    }
    for(Point<Number> point: reduction_drop_normal.vertices()){
      point.reduceToDimensions({i,j});
      reduction_drop_normal_vertices_2d.push_back(point);
    }
    for(Point<Number> point: reduction_drop_smooth.vertices()){
      point.reduceToDimensions({i,j});
      reduction_drop_smooth_vertices_2d.push_back(point);
    }
    for(Point<Number> point: reduction_unite_normal.vertices()){
      point.reduceToDimensions({i,j});
      reduction_unite_normal_vertices_2d.push_back(point);
    }
    for(Point<Number> point: reduction_unite_smooth.vertices()){
      point.reduceToDimensions({i,j});
      reduction_unite_smooth_vertices_2d.push_back(point);
    }
    for(Point<Number> point: reduction_unite_cut.vertices()){
      point.reduceToDimensions({i,j});
      reduction_unite_cut_vertices_2d.push_back(point);
    }
    for(Point<Number> point: reduction_unite_norm.vertices()){
      point.reduceToDimensions({i,j});
      reduction_unite_norm_vertices_2d.push_back(point);
    }
    for(Point<Number> point: reduction_directed_small.vertices()){
      point.reduceToDimensions({i,j});
      reduction_directed_small_vertices_2d.push_back(point);
    }
    for(Point<Number> point: reduction_directed_big.vertices()){
      point.reduceToDimensions({i,j});
      reduction_directed_big_vertices_2d.push_back(point);
    }

  	rdn = plotter.addObject(reduction_drop_normal_vertices_2d);
    rds = plotter.addObject(reduction_drop_smooth_vertices_2d);
    run = plotter.addObject(reduction_unite_normal_vertices_2d);
    rus = plotter.addObject(reduction_unite_smooth_vertices_2d);
    ruc = plotter.addObject(reduction_unite_cut_vertices_2d);
    //runo = plotter.addObject(reduction_unite_norm_vertices_2d);
    rdis = plotter.addObject(reduction_directed_small_vertices_2d);
    rdib = plotter.addObject(reduction_directed_big_vertices_2d);

  	plotter.addObject(reduce_from_vertices_2d);
  }

  //2D
  if(dimension==2){
    plotter.addObject(reduce_from.vertices());
    rdn = plotter.addObject(reduction_drop_normal.vertices());
    rds = plotter.addObject(reduction_drop_smooth.vertices());
    run = plotter.addObject(reduction_unite_normal.vertices());
    rus = plotter.addObject(reduction_unite_smooth.vertices());
    ruc = plotter.addObject(reduction_unite_cut.vertices());
    rdis = plotter.addObject(reduction_directed_small.vertices());
    rdib = plotter.addObject(reduction_directed_big.vertices());
  }

  plotter.setObjectColor(rdn, colors[red]);
  plotter.setObjectColor(rds, colors[green]);
  plotter.setObjectColor(run, colors[orange]);
  plotter.setObjectColor(rus, colors[violett]);
  plotter.setObjectColor(ruc, colors[turquoise]);
  //plotter.setObjectColor(runo, colors[bordeaux]);
  plotter.setObjectColor(rdis, colors[maygreen]);
  plotter.setObjectColor(rdib, colors[lila]);

	plotter.plot2d();
  // End Plotting

	return 0;
}
