/**
 * Example file for polytope heuristic reduction.
 *
 */
 #include <chrono>

 #include "../src/lib/util/Plotter.h"
 #include "../src/lib/datastructures/Hyperplane.h"
 #include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"
 #include "../src/lib/representations/volumeApproximation.h"

using namespace hypro;

int main(int argc, char const *argv[])
{
	typedef double Number;

  typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::microseconds timeunit;

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
  trapez.insert(Hyperplane<Number>({-1,0.5},0.53));
	trapez.insert(Hyperplane<Number>({0,1},1));
  trapez.insert(Hyperplane<Number>({1,0.5},0.53));
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

  HPolytope<Number> trapez4; //trapez for Unite
  trapez4.insert(Hyperplane<Number>({-1,0.85},5));
	trapez4.insert(Hyperplane<Number>({0,1},1));
  trapez4.insert(Hyperplane<Number>({1,0.85},5));
	trapez4.insert(Hyperplane<Number>({0,-1},1));

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
  std::vector<vector_t<Number>> directionsForTemplate = computeTemplate<Number>(2,16);

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
  HPolytope<Number> reduce_from = nico;


  unsigned dimension = reduce_from.dimension(); // set dimension for test object here
  bool volume=true;
  Number prevVolume=0;

  // Welcome
  std::cout << "example_heuristic\n-----------------" << std::endl;

  // calculate volume of HPolytope reduce_from
  if(volume){
    prevVolume = approximateVolume<Number, hypro::HPolytope<Number>>(reduce_from);
    std::cout << "volume of reduce_from: " << prevVolume << std::endl << std::endl;
  }
  std::cout << "size of reduce_from: " << reduce_from.sizeOfHPolytope() << std::endl;


  // Reducing
  std::cout << "reduction of heuristic"<< std::endl;

  clock::time_point start = clock::now();
  HPolytope<Number> reduction = reduce_from.heuristic();
  double timeOfReachReduction = (double) std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
  std::cout << "Total time for reduction(HYPRO): " << timeOfReachReduction << std::endl << std::endl;

  if(volume) std::cout << "   +" << ((approximateVolume<Number, hypro::HPolytope<Number>>(reduction)-prevVolume)/prevVolume)*100 << "%" << std::endl;
  std::cout << "size of reduction_drop_normal: " << reduction.sizeOfHPolytope() << std::endl;
  // End Reducing

	return 0;
}
