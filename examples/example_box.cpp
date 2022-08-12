
/**
 * \example example_box.cpp This example shows how to use a box representation.
 * It covers creation of a box, an affine transformation of the created box as
 * well as the intersection with a half space and an included test for emptiness
 * of the resulting set.
 */

#include "datastructures/Halfspace.h"
#include "representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"

int main() {
  // use rational arithmetic.
  typedef mpq_class Number;

  // get plotter reference.
  hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();

  // create some transformation matrix.
  hypro::matrix_t<Number> A = hypro::matrix_t<Number>::Zero(3, 3);
  A(0, 0) = 1;
  A(1, 1) = carl::convert<double, Number>(carl::cos(45));
  A(1, 2) = carl::convert<double, Number>(-carl::sin(45));
  A(2, 1) = carl::convert<double, Number>(carl::sin(45));
  A(2, 2) = carl::convert<double, Number>(carl::cos(45));

  // create some translation vector.
  hypro::vector_t<Number> b = hypro::vector_t<Number>::Zero(3);

  // create a box out of two given limit points.
  hypro::Box<Number> testbox(std::make_pair(hypro::Point<Number>({-2, 2, -4}),
                                            hypro::Point<Number>({2, 4, -2})));

  // compute all vertices of the box and output them.
  std::vector<hypro::Point<Number>> tvertices = testbox.vertices();
  for (const auto &vertex : tvertices)
    std::cout << vertex << std::endl;

  std::cout << testbox << std::endl;

  // transform the initial box with the created matrix and vector (affine
  // transformation).
  hypro::Box<Number> res = testbox.affineTransformation(A, b);

  std::cout << res << std::endl;

  std::vector<hypro::Point<Number>> vertices = res.vertices();
  for (const auto &vertex : vertices)
    std::cout << vertex << std::endl;

  // create a second box which is two dimensional.
  hypro::Box<Number> testbox2(std::make_pair(hypro::Point<Number>({-2, -2}),
                                             hypro::Point<Number>({2, 2})));

  std::vector<hypro::Point<Number>> tvertices2 = testbox2.vertices();
  for (const auto &vertex : tvertices2)
    std::cout << vertex << std::endl;

  // create a halfspace (cutter) from a normal vector and an offset.
  hypro::matrix_t<Number> normal = hypro::matrix_t<Number>(1, 2);
  hypro::vector_t<Number> offset = hypro::vector_t<Number>(1);
  normal << 1, 1;
  offset << carl::rationalize<Number>(-0.5);
  std::cout << "normal: " << normal << std::endl << "offset: " << offset << std::endl;
  hypro::vector_t<Number> hsNormal = hypro::vector_t<Number>(2);
  hsNormal << 1, 1;
  hypro::Halfspace<Number> cutter =
      hypro::Halfspace<Number>(hsNormal, carl::rationalize<Number>(-0.5));

  // we can also plot halfspaces
  plotter.addObject(cutter);
  unsigned original = plotter.addObject(testbox2.vertices());

  // add the intersection of the second box and the created halfspace to the
  // plotter instance. Note: satisfiesHalfspaces returns a pair <bool,
  // Representation>.
  unsigned cutted = plotter.addObject(
      testbox2.satisfiesHalfspaces(normal, offset).second.vertices());

  // set colors and plot (gnuplot).
  plotter.setObjectColor(original,
                         hypro::plotting::colors[hypro::plotting::green]);
  plotter.setObjectColor(cutted, hypro::plotting::colors[hypro::plotting::red]);
  plotter.plot2d();

  return 0;
}
