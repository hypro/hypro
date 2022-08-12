/*
 * This example file shows the usage of the Polytope class.
 *
 * @file   example_polytope.h
 * @author Tayfun Oezen <tayfun.oezen@rwth-aachen.de>
 *
 * @since       2014-11-23
 * @version     2014-11-23
 */

#include "hypro/config.h"
#include "hypro/datastructures/Point.h"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"

int main() {

  typedef mpq_class number_t;

  hypro::Plotter<number_t> &plotter = hypro::Plotter<number_t>::getInstance();

  // hypro::Polytope<number_t> polytope1 = hypro::Polytope<number_t>();
  // hypro::Polytope<number_t> polytope2 = hypro::Polytope<number_t>(polytope1);

  hypro::matrix_t<number_t> matrix = hypro::matrix_t<number_t>(6, 2);
  matrix << -1, number_t(490576) / number_t(99100001), 0, -1, 0, 1, 1, 0, 1,
      number_t(-10000) / number_t(1000001), 1,
      number_t(-480461) / number_t(97100000);
  hypro::vector_t<number_t> constants = hypro::vector_t<number_t>(6);
  constants << number_t(-123874939928) / number_t(12387500125),
      number_t(98100001) / number_t(1000000000), number_t(1) / number_t(1000),
      number_t(51) / number_t(5),
      number_t(10200500738519539) / number_t(1000001000000000),
      number_t(51) / number_t(5);
  std::cout << matrix << std::endl << constants << std::endl;

  hypro::matrix_t<number_t> matrix2 = hypro::matrix_t<number_t>(4, 2);
  matrix2 << 1000000000, 0, -1000000000, 0, 0, 1000000000, 0, -1000000000;
  hypro::vector_t<number_t> constants2 = hypro::vector_t<number_t>(4);
  constants2 << 50725487, 50725487, 50725487, 50725487;
  std::cout << matrix2 << std::endl << constants2 << std::endl;

  hypro::HPolytope<number_t> hpoly(matrix, constants);
  hypro::HPolytope<number_t> hpoly2(matrix2, constants2);
  hypro::HPolytope<number_t> addition = hpoly.minkowskiSum(hpoly2);

  unsigned a = plotter.addObject(hpoly.vertices());
  unsigned b = plotter.addObject(hpoly2.vertices());
  unsigned c = plotter.addObject(addition.vertices());
  plotter.setObjectColor(a, hypro::plotting::colors[hypro::plotting::green]);
  plotter.setObjectColor(b, hypro::plotting::colors[hypro::plotting::red]);
  plotter.setObjectColor(c, hypro::plotting::colors[hypro::plotting::orange]);

  plotter.plot2d();

  /*
  if(polytope1.empty() && polytope2.empty())
  {
          hypro::Point<number_t> p1;
          hypro::Point<number_t> p2;
          hypro::Point<number_t> p3;
          hypro::Point<number_t> p4;

          p1 = hypro::Point<number_t>({1,1});
          p2 = hypro::Point<number_t>({1,3});
          p3 = hypro::Point<number_t>({3,1});
          p4 = hypro::Point<number_t>({3,3});

          std::vector<hypro::Point<number_t>> pv;
          pv.push_back(p1);
          pv.push_back(p2);
          pv.push_back(p3);
          pv.push_back(p4);
          polytope1 = hypro::Polytope<number_t>(pv);

          if(polytope1.contains(p1))
          {

                  p1 = hypro::Point<number_t>({1.5,1.5});
                  p2 = hypro::Point<number_t>({2.5,1.5});
                  p3 = hypro::Point<number_t>({1.5,2.5});
                  p4 = hypro::Point<number_t>({2.5,2.5});

                  polytope2.addPoint(p1);
                  polytope2.addPoint(p2);
                  polytope2.addPoint(p3);
                  polytope2.addPoint(p4);

                  hypro::Polytope<number_t> polytope3 =
  hypro::Polytope<number_t>();

                  polytope1 = polytope2.minkowskiSum(polytope3);

                  polytope1.updatePoints();
                  polytope2.updatePoints();
                  polytope3.updatePoints();

                  polytope3 = polytope1.intersect(polytope2);

                  polytope1.updatePoints();
                  polytope2.updatePoints();
                  polytope3.updatePoints();

                  hypro::Polytope<number_t> polytope4 =
  hypro::Polytope<number_t>();

                  polytope1 = polytope3.unite(polytope4);

                  polytope1.updatePoints();
                  polytope2.updatePoints();
                  polytope3.updatePoints();
                  polytope4.updatePoints();
          }
  }*/
  return 0;
}
