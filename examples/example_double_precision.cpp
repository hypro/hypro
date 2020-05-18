//
// Created by Jannik Hüls on 01.08.18.
//

#include "representations/GeometricObjectBase.h"
#include "util/Plotter.h"
#include <gmpxx.h>

int main() {
  using Number = double;
  // using Number = mpq_class;
  using namespace hypro;

  vector_t<Number> v = vector_t<Number>::Zero(3);
  v << 0, 0, 0;
  Point<Number> p4(v);
  v << 3, 1, 0;
  Point<Number> p1(v);
  v << 5, 5, 0;
  Point<Number> p2(v);
  v << 5, 5, 5;
  Point<Number> p3(v);

  HPolytope<Number> boxPolytope({p1, p2, p3, p4});
}
