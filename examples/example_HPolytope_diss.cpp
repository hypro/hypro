#include "representations/GeometricObjectBase.h"
#include "util/plotting/Plotter.h"
#include <vector>

typedef double Number;

int main() {
  hypro::Point<mpq_class> p1 = hypro::Point<mpq_class>({1, 1, 1});
  hypro::Point<mpq_class> p2 = hypro::Point<mpq_class>({2, 2, 2});

  std::vector<hypro::Point<mpq_class>> points;
  points.push_back(p1);
  points.push_back(p2);

  hypro::HPolytope<mpq_class> poly{points};

  // hypro::Plotter<mpq_class>::getInstance().addObject(poly.vertices());

  // create a *.plt file (gnuplot).
  // hypro::Plotter<mpq_class>::getInstance().plot2d();

  return 0;
}