#include "../src/hypro/representations/GeometricObjectBase.h"

int main() {

  using namespace hypro;
  using Number = mpq_class;

  matrix_t<Number> a = matrix_t<Number>(4, 2);
  a << 1, 0, 0, 1, -1, 0, 0, -1;
  vector_t<Number> b = vector_t<Number>(4);
  b << 1, 1, 1, 1;

  HPolytope<Number> hpoly(a, b);

  vector_t<Number> direction = vector_t<Number>(2);
  direction << 1, 1;

  hpoly.evaluate(direction);
}
