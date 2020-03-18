/** \example example_HPolytope.cpp
 * 	This is an example file showing how to create and modify a polytope in
 * H-representation.
 */

#include "representations/GeometricObjectBase.h"
#include "util/plotting/Plotter.h"

typedef double Number;

int main() {
  // we create the constraints and constants defining a 2D-unit box.
  hypro::matrix_t<Number> HPolyConstraints = hypro::matrix_t<Number>(4, 2);
  HPolyConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
  hypro::vector_t<Number> HPolyConstants = hypro::vector_t<Number>(4);
  HPolyConstants << 1, 1, 1, 1;

  // create the actual polytope and add its vertices to the global plotter
  // (singleton).
  hypro::HPolytope<Number> poly(HPolyConstraints, HPolyConstants);
  hypro::Plotter<Number>::getInstance().addObject(poly.vertices());

  // create rotation matrix for +45 degrees (corresponds to ~0.785398 radians).
  hypro::matrix_t<Number> rotation = hypro::matrix_t<Number>(2, 2);
  rotation << std::cos(0.785398), -std::sin(0.785398), std::sin(0.785398),
      std::cos(0.785398);

  // perform linear transformation (rotation) and plot the new object in green
  // (default = blue).
  poly = poly.linearTransformation(rotation);
  unsigned obj2 =
      hypro::Plotter<Number>::getInstance().addObject(poly.vertices());
  hypro::Plotter<Number>::getInstance().setObjectColor(
      obj2, hypro::plotting::colors[hypro::plotting::green]);

  // create a *.plt file (gnuplot).
  hypro::Plotter<Number>::getInstance().plot2d();

  return 0;
}
