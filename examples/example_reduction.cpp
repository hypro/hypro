/**
 * Example file for polytope reduction.
 * @brief [brief description]
 * @details [long description]
 *
 */
#include <chrono>

#include "hypro/datastructures/Halfspace.h"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/representations/volumeApproximation.h"
#include "hypro/util/plotting/Plotter.h"

using namespace hypro;

int main() {
  typedef double Number;

  typedef std::chrono::high_resolution_clock clock;
  typedef std::chrono::microseconds timeunit;

  // HPolytopes Examples
  std::vector<vector_t<Number>> directions;

  // 2D
  HPolytope<Number> nico; // NikolausHaus
  nico.insert(Halfspace<Number>({-1, 1}, 1));
  nico.insert(Halfspace<Number>({1, 1}, 1));
  nico.insert(Halfspace<Number>({1, 0}, 1));
  nico.insert(Halfspace<Number>({0, -1}, 1));
  nico.insert(Halfspace<Number>({-1, 0}, 1));

  HPolytope<Number> square; // Square
  square.insert(Halfspace<Number>({-1, 0}, 1));
  square.insert(Halfspace<Number>({0, 1}, 1));
  square.insert(Halfspace<Number>({1, 0}, 1));
  square.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> rotated_square; // rotated Square
  rotated_square.insert(Halfspace<Number>({-1, 1}, 1));
  rotated_square.insert(Halfspace<Number>({1, 1}, 1));
  rotated_square.insert(Halfspace<Number>({1, -1}, 1));
  rotated_square.insert(Halfspace<Number>({-1, -1}, 1));

  HPolytope<Number> trapez; // trapez for Drop
  trapez.insert(Halfspace<Number>({-1, 0.5}, 0.53));
  trapez.insert(Halfspace<Number>({0, 1}, 1));
  trapez.insert(Halfspace<Number>({1, 0.5}, 0.53));
  trapez.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> trapez2; // trapez for Unite
  trapez2.insert(Halfspace<Number>({-1, 0.5}, 5));
  trapez2.insert(Halfspace<Number>({0, 1}, 1));
  trapez2.insert(Halfspace<Number>({1, 0.5}, 5));
  trapez2.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> trapez3; // trapez for Unite
  trapez3.insert(Halfspace<Number>({-1, 0.5}, 2));
  trapez3.insert(Halfspace<Number>({0, 1}, 1));
  trapez3.insert(Halfspace<Number>({1, 0.5}, 2));
  trapez3.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> trapez4; // trapez for Unite
  trapez4.insert(Halfspace<Number>({-1, 0.85}, 5));
  trapez4.insert(Halfspace<Number>({0, 1}, 1));
  trapez4.insert(Halfspace<Number>({1, 0.85}, 5));
  trapez4.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> equal;
  equal.insert(Halfspace<Number>({-1, 2}, 2));
  equal.insert(Halfspace<Number>({1, 3}, 2));
  equal.insert(Halfspace<Number>({2, 1}, 2));
  equal.insert(Halfspace<Number>({0, -1}, 0));

  HPolytope<Number> unite_compare;
  unite_compare.insert(Halfspace<Number>({-1, 0}, 5));
  unite_compare.insert(Halfspace<Number>({0.1, 1}, 1));
  unite_compare.insert(Halfspace<Number>({1, 1.1}, 5));
  unite_compare.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> unite;
  unite.insert(Halfspace<Number>({-1, 0}, 1));
  unite.insert(Halfspace<Number>({-1, 1}, 2));
  unite.insert(Halfspace<Number>({1, 1}, 2));
  unite.insert(Halfspace<Number>({1, 0}, 1));
  unite.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> uniteExtended;
  uniteExtended.insert(Halfspace<Number>({-1, 0}, 10));
  uniteExtended.insert(Halfspace<Number>({0, 1}, 1));
  uniteExtended.insert(Halfspace<Number>({1, 0}, 10));
  uniteExtended.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> multipleEqual;
  multipleEqual.insert(Halfspace<Number>({-0.1, 9}, 10));
  multipleEqual.insert(Halfspace<Number>({0, 1}, 1));
  multipleEqual.insert(Halfspace<Number>({0.1, 9}, 10));
  multipleEqual.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> directedEqual;
  directedEqual.insert(Halfspace<Number>({-1, 1}, 1));
  directedEqual.insert(Halfspace<Number>({1, 1}, 1));
  directedEqual.insert(Halfspace<Number>({-0.5, -1}, 1));
  directedEqual.insert(Halfspace<Number>({0.5, -1}, 1));

  HPolytope<Number> dropBest;
  dropBest.insert(Halfspace<Number>({-1, 0}, 1));
  dropBest.insert(Halfspace<Number>({0, 1}, 1));
  dropBest.insert(Halfspace<Number>({1, 1}, 1.9));
  dropBest.insert(Halfspace<Number>({1, 0}, 1));
  dropBest.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> dropSmoothBest;
  dropSmoothBest.insert(Halfspace<Number>({-1, 1}, 100));
  dropSmoothBest.insert(Halfspace<Number>({0, 1}, 1));
  dropSmoothBest.insert(Halfspace<Number>({1, 100}, 100));
  dropSmoothBest.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> uniteVerticesBest;
  uniteVerticesBest.insert(Halfspace<Number>({-1, -1}, 100));
  uniteVerticesBest.insert(Halfspace<Number>({0, 1}, 1));
  uniteVerticesBest.insert(Halfspace<Number>({1, 1}, 100));
  uniteVerticesBest.insert(Halfspace<Number>({0, -1}, 1));

  HPolytope<Number> twoD_template;
  std::vector<vector_t<Number>> directionsForTemplate =
      computeTemplate<Number>(5, 6);

  for (vector_t<Number> direction : directionsForTemplate) {
    twoD_template.insert(Halfspace<Number>(direction, 1));
  }

  HPolytope<Number> diamond;
  // diamond.insert(Halfspace<Number>({-1,10},1));
  // diamond.insert(Halfspace<Number>({-1,1.5},5));
  // diamond.insert(Halfspace<Number>({-1,1.3},2));
  // diamond.insert(Halfspace<Number>({-1,1.1},3));
  diamond.insert(Halfspace<Number>({-1, 1}, 5));
  // diamond.insert(Halfspace<Number>({-1,0.1},1));
  diamond.insert(Halfspace<Number>({0, 1}, 4));
  // diamond.insert(Halfspace<Number>({-1,0.1},1));
  diamond.insert(Halfspace<Number>({1, 1}, 5));
  // diamond.insert(Halfspace<Number>({1,1.1},3));
  // diamond.insert(Halfspace<Number>({1,1.3},2));
  // diamond.insert(Halfspace<Number>({1,1.5},5));
  // diamond.insert(Halfspace<Number>({1,10},1));
  diamond.insert(Halfspace<Number>({-1, -1}, 1));
  diamond.insert(Halfspace<Number>({1, -1}, 1));

  vector_t<Number> directed2d_1 = vector_t<Number>(2);
  directed2d_1(0) = 0;
  directed2d_1(1) = 1;

  // 3D
  HPolytope<Number> td_example;
  td_example.insert(Halfspace<Number>({0, 0, -1}, 0));    // a      0
  td_example.insert(Halfspace<Number>({1, 0, 0.1}, 3));   // b     1
  td_example.insert(Halfspace<Number>({-1, -1, 0.1}, 3)); // c   2
  td_example.insert(Halfspace<Number>({0, 1, 0.1}, 3));   // d     3
  td_example.insert(Halfspace<Number>({0, 0, 1}, 2));     // e       4

  HPolytope<Number> td_example2;
  td_example2.insert(Halfspace<Number>({0, 0, -1}, 0));    // a      0
  td_example2.insert(Halfspace<Number>({1, 0, 0.1}, 3));   // b     1
  td_example2.insert(Halfspace<Number>({-1, -1, 0.1}, 3)); // c   2
  td_example2.insert(Halfspace<Number>({0, 1, 0.1}, 3));   // d     3
  td_example2.insert(Halfspace<Number>({-0.1, 0, 1}, 2));  // e       4

  HPolytope<Number> cube;
  cube.insert(Halfspace<Number>({0, 0, -1}, 1));
  cube.insert(Halfspace<Number>({0, 0, 1}, 1));
  cube.insert(Halfspace<Number>({-1, 0, 0}, 1));
  cube.insert(Halfspace<Number>({1, 0, 0}, 1));
  cube.insert(Halfspace<Number>({0, -1, 0}, 1));
  cube.insert(Halfspace<Number>({0, 1, 0}, 1));

  HPolytope<Number> sword;
  sword.insert(Halfspace<Number>({0, 0, -1}, 1));
  sword.insert(Halfspace<Number>({0, 0, 1}, 1));
  sword.insert(Halfspace<Number>({-1, -0.1, 0}, 1));
  sword.insert(Halfspace<Number>({1, -0.1, 0}, 1));
  sword.insert(Halfspace<Number>({-1, 0.1, 0}, 1));
  sword.insert(Halfspace<Number>({1, 0.1, 0}, 1));

  HPolytope<Number> ship; // cut tetrader
  ship.insert(Halfspace<Number>({0, 0, 1}, 0));
  ship.insert(Halfspace<Number>({-1, 0, -1}, 1));
  ship.insert(Halfspace<Number>({1, 0, -1}, 1));
  ship.insert(Halfspace<Number>({0, -1, 1}, 1));
  ship.insert(Halfspace<Number>({0, 1, 1}, 1));

  HPolytope<Number> house;
  house.insert(Halfspace<Number>({0, 0, -1}, 1)); // floor 0
  house.insert(Halfspace<Number>({-1, 0, 0}, 1)); // left 1
  house.insert(Halfspace<Number>({1, 0, 0}, 1));  // right 2
  house.insert(Halfspace<Number>({0, -1, 0}, 1)); // back 3
  house.insert(Halfspace<Number>({0, 1, 0}, 1));  // front 4

  house.insert(Halfspace<Number>({1, 1, 1}, 1));   // roof front-right 5
  house.insert(Halfspace<Number>({1, -1, 1}, 1));  // back-right 6
  house.insert(Halfspace<Number>({-1, 1, 1}, 1));  // front-left 7
  house.insert(Halfspace<Number>({-1, -1, 1}, 1)); // back-left 8

  vector_t<Number> directed3d_1 = vector_t<Number>(3);
  directed3d_1(0) = 1;
  directed3d_1(1) = 1;
  directed3d_1(2) = 1;
  vector_t<Number> directed3d_2 = vector_t<Number>(3);
  directed3d_2(0) = 1.1;
  directed3d_2(1) = -1;
  directed3d_2(2) = 1;
  vector_t<Number> directed3d_3 = vector_t<Number>(3);
  directed3d_3(0) = 0.1;
  directed3d_3(1) = -1;
  directed3d_3(2) = 1;

  // 4D
  HPolytope<Number> confuse_cube;
  confuse_cube.insert(Halfspace<Number>({0, 0, 0, -1}, 1));
  confuse_cube.insert(Halfspace<Number>({0, 0, 0, 1}, 1));
  confuse_cube.insert(Halfspace<Number>({0, 0, -1, 0}, 1));
  confuse_cube.insert(Halfspace<Number>({0, 0, 1, 0}, 1));
  confuse_cube.insert(Halfspace<Number>({-1, 0, 0, 0}, 1));
  confuse_cube.insert(Halfspace<Number>({1, 0, 0, 0}, 1));
  confuse_cube.insert(Halfspace<Number>({0, -1, 0, 0}, 1));
  confuse_cube.insert(Halfspace<Number>({0, 1, 0, 0}, 1));

  vector_t<Number> directed4d_1 = vector_t<Number>(4);
  directed4d_1(0) = 1;
  directed4d_1(1) = 1.1;
  directed4d_1(2) = 0.9;
  directed4d_1(3) = 1.5;

  // 5D
  HPolytope<Number> confuse_cube5;
  confuse_cube5.insert(Halfspace<Number>({0, 0, 0, 0, -1}, 1));
  confuse_cube5.insert(Halfspace<Number>({0, 0, 0, 0, 1}, 1));
  confuse_cube5.insert(Halfspace<Number>({0, 0, 0, -1, 0}, 1));
  confuse_cube5.insert(Halfspace<Number>({0, 0, 0, 1, 0}, 1));
  confuse_cube5.insert(Halfspace<Number>({0, 0, -1, 0, 0}, 1));
  confuse_cube5.insert(Halfspace<Number>({0, 0, 1, 0, 0}, 1));
  confuse_cube5.insert(Halfspace<Number>({-1, 0, 0, 0, 0}, 1));
  confuse_cube5.insert(Halfspace<Number>({1, 0, 0, 0, 0}, 1));
  confuse_cube5.insert(Halfspace<Number>({0, -1, 0, 0, 0}, 1));
  confuse_cube5.insert(Halfspace<Number>({0, 1, 0, 0, 0}, 1));

  vector_t<Number> directed5d_1 = vector_t<Number>(5);
  directed5d_1(0) = 1;
  directed5d_1(1) = 1.1;
  directed5d_1(2) = 0.9;
  directed5d_1(3) = 1.5;
  directed5d_1(4) = 1;

  // init reduce_HPolytopes
  HPolytope<Number> reduce_from = twoD_template;

  unsigned dimension =
      reduce_from.dimension(); // set dimension for test object here
  bool volume = false;
  Number prevVolume = 0;

  HPolytope<Number> reduction_drop_normal, reduction_drop_smooth,
      reduction_unite_normal, reduction_unite_smooth, reduction_unite_cut,
      reduction_unite_norm, reduction_directed_small, reduction_directed_big,
      reduction_directed_template;

  clock::time_point start;
  double timeOfReachReduction;

  // Welcome
  std::cout << "Example_reduction\n-----------------" << std::endl;

  // calculate volume of HPolytope reduce_from
  if (volume) {
    prevVolume =
        approximateVolume<Number, hypro::HPolytope<Number>>(reduce_from);
    std::cout << "volume of reduce_from: " << prevVolume << std::endl
              << std::endl;
  }
  std::cout << "size of reduce_from: " << reduce_from.sizeOfHPolytopeT()
            << " with " << reduce_from.size() << " facets " << std::endl;

  reduce_from.reduce(1, 0, HPolytope<Number>::REDUCTION_STRATEGY::DROP);

  // Reducing
  std::cout << "\nDROP\n------------------------------------\nwith drop_normal "
               "(red), drop_smooth (red)"
            << std::endl
            << std::endl;

  unsigned facet = 0; // reduce one specific facet
  // for(unsigned facet=0; facet < reduce_from.size(); facet++){ // reduce all
  // facets
  std::cout << "(facet" << facet << ")" << std::endl;

  // reduce and display the increase of the volume
  std::cout << "drop_normal" << std::endl;
  start = clock::now();
  reduction_drop_normal =
      reduce_from.reduce(facet, 0, HPolytope<Number>::REDUCTION_STRATEGY::DROP);
  timeOfReachReduction =
      (double)std::chrono::duration_cast<timeunit>(clock::now() - start)
          .count() /
      1000;
  std::cout << "Total time for reduction(HYPRO): " << timeOfReachReduction
            << std::endl;
  if (volume)
    std::cout << "   +"
              << ((approximateVolume<Number, hypro::HPolytope<Number>>(
                       reduction_drop_normal) -
                   prevVolume) /
                  prevVolume) *
                     100
              << "%" << std::endl;
  std::cout << "size of reduction_drop_normal: "
            << reduction_drop_normal.sizeOfHPolytopeT() << std::endl;

  std::cout << "drop_smooth" << std::endl;
  start = clock::now();
  reduction_drop_smooth = reduce_from.reduce(
      facet, 0, HPolytope<Number>::REDUCTION_STRATEGY::DROP_SMOOTH);
  timeOfReachReduction =
      (double)std::chrono::duration_cast<timeunit>(clock::now() - start)
          .count() /
      1000;
  std::cout << "Total time for reduction(HYPRO): " << timeOfReachReduction
            << std::endl;
  if (volume)
    std::cout << "   +"
              << ((approximateVolume<Number, hypro::HPolytope<Number>>(
                       reduction_drop_smooth) -
                   prevVolume) /
                  prevVolume) *
                     100
              << "%" << std::endl;
  std::cout << "size of reduction_drop_smooth: "
            << reduction_drop_smooth.sizeOfHPolytopeT() << std::endl;

  std::cout << std::endl;
  //}

  // reduce unite - take care of correct neighbor-relation
  std::cout
      << "\nUNITE\n------------------------------------\nwith unite_normal "
         "(green), unite_smooth (maygreen), unite_cut (turquoise)"
      << std::endl
      << std::endl;
  // unsigned facet1 = 0, facet2 =3;

  for (unsigned facet1 = 0; facet1 < reduce_from.size() - 1; facet1++) {
    for (unsigned facet2 = facet1 + 1; facet2 < reduce_from.size(); facet2++) {
      // if(facet2==7 && facet1==6) break;

      std::cout << "(facet" << facet2 << ", facet" << facet1 << ")"
                << std::endl;

      std::cout << "unite_normal" << std::endl;
      start = clock::now();
      reduction_unite_normal = reduce_from.reduce(
          facet2, facet1, HPolytope<Number>::REDUCTION_STRATEGY::UNITE);
      timeOfReachReduction =
          (double)std::chrono::duration_cast<timeunit>(clock::now() - start)
              .count() /
          1000;
      std::cout << "Total time for reduction(HYPRO): " << timeOfReachReduction
                << std::endl;
      if (volume && reduction_unite_normal.size() < reduce_from.size())
        std::cout << "   +"
                  << ((approximateVolume<Number, hypro::HPolytope<Number>>(
                           reduction_unite_normal) -
                       prevVolume) /
                      prevVolume) *
                         100
                  << "%" << std::endl;
      std::cout << "size of reduction_unite_normal: "
                << reduction_unite_normal.sizeOfHPolytopeT() << std::endl;

      std::cout << "unite_smooth" << std::endl;
      start = clock::now();
      reduction_unite_smooth = reduce_from.reduce(
          facet2, facet1, HPolytope<Number>::REDUCTION_STRATEGY::UNITE_SMOOTH);
      timeOfReachReduction =
          (double)std::chrono::duration_cast<timeunit>(clock::now() - start)
              .count() /
          1000;
      std::cout << "Total time for reduction(HYPRO): " << timeOfReachReduction
                << std::endl;
      if (volume && reduction_unite_smooth.size() < reduce_from.size())
        std::cout << "   +"
                  << ((approximateVolume<Number, hypro::HPolytope<Number>>(
                           reduction_unite_smooth) -
                       prevVolume) /
                      prevVolume) *
                         100
                  << "%" << std::endl;
      std::cout << "size of reduction_unite_smooth: "
                << reduction_unite_smooth.sizeOfHPolytopeT() << std::endl;

      std::cout << "unite_cut" << std::endl;
      start = clock::now();
      reduction_unite_cut = reduce_from.reduce(
          facet2, facet1, HPolytope<Number>::REDUCTION_STRATEGY::UNITE_CUT);
      timeOfReachReduction =
          (double)std::chrono::duration_cast<timeunit>(clock::now() - start)
              .count() /
          1000;
      std::cout << "Total time for reduction(HYPRO): " << timeOfReachReduction
                << std::endl;
      if (volume && reduction_unite_cut.size() < reduce_from.size())
        std::cout << "   +"
                  << ((approximateVolume<Number, hypro::HPolytope<Number>>(
                           reduction_unite_cut) -
                       prevVolume) /
                      prevVolume) *
                         100
                  << "%" << std::endl;
      std::cout << "size of reduction_unite_cut: "
                << reduction_unite_cut.sizeOfHPolytopeT() << std::endl;

      std::cout << "unite_norm" << std::endl;
      start = clock::now();
      reduction_unite_norm = reduce_from.reduce(
          facet2, facet1, HPolytope<Number>::REDUCTION_STRATEGY::UNITE_NORM);
      timeOfReachReduction =
          (double)std::chrono::duration_cast<timeunit>(clock::now() - start)
              .count() /
          1000;
      std::cout << "Total time for reduction(HYPRO): " << timeOfReachReduction
                << std::endl;
      if (volume && reduction_unite_norm.size() < reduce_from.size())
        std::cout << "   +"
                  << ((approximateVolume<Number, hypro::HPolytope<Number>>(
                           reduction_unite_norm) -
                       prevVolume) /
                      prevVolume) *
                         100
                  << "%" << std::endl;
      std::cout << "size of reduction_unite_norm: "
                << reduction_unite_norm.sizeOfHPolytopeT() << std::endl;

      std::cout << std::endl;
    }
  }

  std::cout << "\nDIRECTED\n------------------------------------\nwith "
               "directed_small (violett), directed_big (lila), "
               "directed_template (bordeaux)"
            << std::endl
            << std::endl;

  // 2D
  if (dimension == 2) {
    directions.push_back(directed2d_1);
  }
  // 3D
  else if (dimension == 3) {
    directions.push_back(directed3d_1);
    // directions.push_back(directed3d_2);
    // directions.push_back(directed3d_3);
  }
  // 4D
  else if (dimension == 4) {
    directions.push_back(directed4d_1);
  }
  // 5D
  else if (dimension == 5) {
    directions.push_back(directed5d_1);
  }

  reduction_directed_small = reduce_from.reduce_directed(
      directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_SMALL);
  std::cout << "directed_small" << std::endl;
  if (volume)
    std::cout << "   +"
              << ((approximateVolume<Number, hypro::HPolytope<Number>>(
                       reduction_directed_small) -
                   prevVolume) /
                  prevVolume) *
                     100
              << "%" << std::endl;
  std::cout << "size of reduction_directed_small: "
            << reduction_directed_small.sizeOfHPolytopeT() << std::endl;

  reduction_directed_big = reduce_from.reduce_directed(
      directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_BIG);
  std::cout << "directed_big" << std::endl;
  if (volume)
    std::cout << "   +"
              << ((approximateVolume<Number, hypro::HPolytope<Number>>(
                       reduction_directed_big) -
                   prevVolume) /
                  prevVolume) *
                     100
              << "%" << std::endl;
  std::cout << "size of reduction_directed_big: "
            << reduction_directed_big.sizeOfHPolytopeT() << std::endl;

  reduction_directed_template = reduce_from.reduce_directed(
      computeTemplate<Number>(dimension, 5),
      HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);
  std::cout << "directed_template" << std::endl;
  if (volume)
    std::cout << "   +"
              << ((approximateVolume<Number, hypro::HPolytope<Number>>(
                       reduction_directed_template) -
                   prevVolume) /
                  prevVolume) *
                     100
              << "%" << std::endl;
  std::cout << "size of reduction_directed_template: "
            << reduction_directed_template.sizeOfHPolytopeT() << std::endl;

  std::cout << std::endl;

  std::cout << "reduction of heuristic" << std::endl;

  start = clock::now();
  HPolytope<Number> reduction = reduce_from.heuristic();
  timeOfReachReduction =
      (double)std::chrono::duration_cast<timeunit>(clock::now() - start)
          .count() /
      1000;
  std::cout << "Total time for reduction(HYPRO): " << timeOfReachReduction
            << std::endl
            << std::endl;

  if (volume)
    std::cout << "   +"
              << ((approximateVolume<Number, hypro::HPolytope<Number>>(
                       reduction) -
                   prevVolume) /
                  prevVolume) *
                     100
              << "%" << std::endl;
  std::cout << "size of reduction_drop_normal: " << reduction.sizeOfHPolytopeT()
            << std::endl;
  // End Reducing

  return 0;
}
