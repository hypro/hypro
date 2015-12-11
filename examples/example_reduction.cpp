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

  HPolytope<Number> twoD_template;
  std::vector<vector_t<Number>> directionsForTemplate = computeTemplate<Number>(2,7);


  for(vector_t<Number> direction: directionsForTemplate){
    twoD_template.insert(Hyperplane<Number>(direction, 1));
  }

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

  vector_t<Number> directed2d_1 = vector_t<Number>(2);
  directed2d_1(0) = 1; directed2d_1(1) = 1;

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

  vector_t<Number> directed3d_1 = vector_t<Number>(3);
  directed3d_1(0) = 1; directed3d_1(1) = 1; directed3d_1(2) = 1;
  vector_t<Number> directed3d_2 = vector_t<Number>(3);
  directed3d_2(0) = 1.1; directed3d_2(1) = -1; directed3d_2(2) = 1;
  vector_t<Number> directed3d_3 = vector_t<Number>(3);
  directed3d_3(0) = 0.1; directed3d_3(1) = -1; directed3d_3(2) = 1;

  // 4D

  HPolytope<Number> confuse_cube;
  confuse_cube.insert(Hyperplane<Number>({ 0,  0,  0, -1}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 0,  0,  0,  1}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 0,  0, -1,  0}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 0,  0,  1,  0}, 1));
  confuse_cube.insert(Hyperplane<Number>({-1,  0,  0,  0}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 1,  0,  0,  0}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 0, -1,  0,  0}, 1));
  confuse_cube.insert(Hyperplane<Number>({ 0,  1,  0,  0}, 1));

  vector_t<Number> directed4d_1 = vector_t<Number>(4);
  directed4d_1(0) = 1; directed4d_1(1) = 1.1; directed4d_1(2) = 0.9; directed4d_1(3) = 1.5;

  // 5D

  HPolytope<Number> confuse_cube5;
  confuse_cube5.insert(Hyperplane<Number>({ 0,  0,  0,  0, -1}, 1));
  confuse_cube5.insert(Hyperplane<Number>({ 0,  0,  0,  0,  1}, 2));
  confuse_cube5.insert(Hyperplane<Number>({ 0,  0,  0, -1,  0}, 1));
  confuse_cube5.insert(Hyperplane<Number>({ 0,  0,  0,  1,  0}, 2));
  confuse_cube5.insert(Hyperplane<Number>({ 0,  0, -1,  0,  0}, 1));
  confuse_cube5.insert(Hyperplane<Number>({ 0,  0,  1,  0,  0}, 2));
  confuse_cube5.insert(Hyperplane<Number>({-1,  0,  0,  0,  0}, 1));
  confuse_cube5.insert(Hyperplane<Number>({ 1,  0,  0,  0,  0}, 2));
  confuse_cube5.insert(Hyperplane<Number>({ 0, -1,  0,  0,  0}, 1));
  confuse_cube5.insert(Hyperplane<Number>({ 0,  1,  0,  0,  0}, 2));

  vector_t<Number> directed5d_1 = vector_t<Number>(5);
  directed5d_1(0) = 1; directed5d_1(1) = 1.1; directed5d_1(2) = 0.9; directed5d_1(3) = 1.5; directed5d_1(4) = 1;

  // init reduce_HPolytopes
  HPolytope<Number> reduce_from = twoD_template;


  unsigned dimension = nico.dimension(); // set dimension for test object here
  bool volume=true;
  Number prevVolume=0;

  HPolytope<Number> reduction_drop_normal,
                    reduction_drop_smooth,
                    reduction_unite_normal,
                    reduction_unite_smooth,
                    reduction_unite_cut,
                    reduction_unite_norm,
                    reduction_directed_small,
                    reduction_directed_big,
                    reduction_directed_template;

  // Welcome
  std::cout << "Example_reduction\n-----------------" << std::endl;

  // calculate volume of HPolytope reduce_from
if(volume){
  prevVolume = approximateVolume<Number, hypro::HPolytope<Number>>(reduce_from);
  std::cout << "volume of reduce_from: " << prevVolume << std::endl << std::endl;
 }
 std::cout << "size of reduce_from: " << reduce_from.sizeOfHPolytope() << std::endl;


  // Reducing
  std::cout << "\nDROP\n------------------------------------\nwith drop_normal (red), drop_smooth (red)" << std::endl << std::endl;

  //unsigned facet =1; // reduce one specific facet
  for(unsigned facet=0; facet < reduce_from.size(); facet++){ // reduce all facets
    std::cout << "(facet" << facet << ")" <<  std::endl;

    // reduce and display the increase of the volume
    std::cout << "drop_normal"<< std::endl;
    reduction_drop_normal = reduce_from.reduce(facet, 0, HPolytope<Number>::REDUCTION_STRATEGY::DROP);
    if(volume) std::cout << "   +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_drop_normal)-prevVolume)/prevVolume)*100 << "%" << std::endl;
    std::cout << "size of reduction_drop_normal: " << reduction_drop_normal.sizeOfHPolytope() << std::endl;

    std::cout << "drop_smooth"<< std::endl;
    reduction_drop_smooth = reduce_from.reduce(facet, 0, HPolytope<Number>::REDUCTION_STRATEGY::DROP_SMOOTH);
    if(volume) std::cout << "   +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_drop_smooth)-prevVolume)/prevVolume)*100 << "%" << std::endl;
    std::cout << "size of reduction_drop_smooth: " << reduction_drop_smooth.sizeOfHPolytope() << std::endl;

    std::cout << std::endl;
  }


  // reduce unite - take care of correct neighbor-relation
  std::cout << "\nUNITE\n------------------------------------\nwith unite_normal (green), unite_smooth (maygreen), unite_cut (turquoise)" << std::endl << std::endl;
  //unsigned facet1 = 2, facet2 =8;

  for(unsigned facet1=0; facet1 < reduce_from.size()-1; facet1++){
    for(unsigned facet2=facet1+1; facet2 < reduce_from.size(); facet2++){
      //if(facet2==7 && facet1==6) break;

      std::cout << "(facet" << facet2 << ", facet" << facet1 << ")" << std::endl;

      std::cout << "unite_normal"<< std::endl;
      reduction_unite_normal = reduce_from.reduce(facet2, facet1,  HPolytope<Number>::REDUCTION_STRATEGY::UNITE);
      if(volume) std::cout << "   +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_normal)-prevVolume)/prevVolume)*100 << "%" << std::endl;
      std::cout << "size of reduction_unite_normal: " << reduction_unite_normal.sizeOfHPolytope() << std::endl;

      std::cout << "unite_smooth"<< std::endl;
      reduction_unite_smooth = reduce_from.reduce(facet2, facet1,  HPolytope<Number>::REDUCTION_STRATEGY::UNITE_SMOOTH);
      if(volume) std::cout << "   +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_smooth)-prevVolume)/prevVolume)*100 << "%" << std::endl;
      std::cout << "size of reduction_unite_smooth: " << reduction_unite_smooth.sizeOfHPolytope() << std::endl;

      std::cout << "unite_cut"<< std::endl;
      reduction_unite_cut = reduce_from.reduce(facet2, facet1,  HPolytope<Number>::REDUCTION_STRATEGY::UNITE_CUT);
      if(volume) std::cout << "   +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_unite_cut)-prevVolume)/prevVolume)*100 << "%" << std::endl;
      std::cout << "size of reduction_unite_cut: " << reduction_unite_cut.sizeOfHPolytope() << std::endl;

      std::cout << std::endl;
    }
  }

  std::cout << "\nDIRECTED\n------------------------------------\nwith directed_small (violett), directed_big (lila), directed_template (bordeaux)" << std::endl << std::endl;

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
  //5D
  else if(dimension==5){
    directions.push_back(directed5d_1);
  }


  reduction_directed_small = reduce_from.reduce_directed(directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_SMALL);
  std::cout << "directed_small"<< std::endl;
  if(volume) std::cout << "   +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_directed_small)-prevVolume)/prevVolume)*100 << "%" << std::endl;
  std::cout << "size of reduction_directed_small: " << reduction_directed_small.sizeOfHPolytope() << std::endl;

  reduction_directed_big = reduce_from.reduce_directed(directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_BIG);
  std::cout << "directed_big"<< std::endl;
  if(volume) std::cout << "   +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_directed_big)-prevVolume)/prevVolume)*100 << "%" << std::endl;
  std::cout << "size of reduction_directed_big: " << reduction_directed_big.sizeOfHPolytope() << std::endl;

  reduction_directed_template = reduce_from.reduce_directed(computeTemplate<Number>(dimension, 3), HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);
  std::cout << "directed_template"<< std::endl;
  if(volume) std::cout << "   +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction_directed_template)-prevVolume)/prevVolume)*100 << "%" << std::endl;
  std::cout << "size of reduction_directed_template: " << reduction_directed_template.sizeOfHPolytope() << std::endl;

  std::cout << std::endl;
  // End Reducing

  
  // Plotting
  unsigned rdn, rds, run, rus, ruc, rdis, rdib, rdit;
  //3D ... nD
  if(dimension>2){
    // Prepare plotting - Reducing to 2d
    unsigned i=1,j=2;
    std::vector<Point<Number>> reduce_from_vertices_2d,
                              reduction_drop_normal_vertices_2d,
                              reduction_drop_smooth_vertices_2d,
                              reduction_unite_normal_vertices_2d,
                              reduction_unite_smooth_vertices_2d,
                              reduction_unite_cut_vertices_2d,
                              reduction_unite_norm_vertices_2d,
                              reduction_directed_small_vertices_2d,
                              reduction_directed_big_vertices_2d,
                              reduction_directed_template_vertices_2d;

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
    for(Point<Number> point: reduction_directed_template.vertices()){
      point.reduceToDimensions({i,j});
      reduction_directed_template_vertices_2d.push_back(point);
    }
    plotter.addObject(reduce_from_vertices_2d);

  	rdn = plotter.addObject(reduction_drop_normal_vertices_2d);
    rds = plotter.addObject(reduction_drop_smooth_vertices_2d);
    run = plotter.addObject(reduction_unite_normal_vertices_2d);
    rus = plotter.addObject(reduction_unite_smooth_vertices_2d);
    ruc = plotter.addObject(reduction_unite_cut_vertices_2d);
    //runo = plotter.addObject(reduction_unite_norm_vertices_2d);
    rdis = plotter.addObject(reduction_directed_small_vertices_2d);
    rdib = plotter.addObject(reduction_directed_big_vertices_2d);
    rdit = plotter.addObject(reduction_directed_template_vertices_2d);
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
    rdit = plotter.addObject(reduction_directed_template.vertices());
  }

  plotter.setObjectColor(rdn, colors[red]);
  plotter.setObjectColor(rds, colors[red]);
  plotter.setObjectColor(run, colors[green]);
  plotter.setObjectColor(rus, colors[maygreen]);
  plotter.setObjectColor(ruc, colors[turquoise]);
  //plotter.setObjectColor(runo, colors[bordeaux]);
  plotter.setObjectColor(rdis, colors[violett]);
  plotter.setObjectColor(rdib, colors[lila]);
  plotter.setObjectColor(rdit, colors[bordeaux]);


	plotter.plot2d();
  // End Plotting


	return 0;
}
