
#include "../src/hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../src/hypro/representations/GeometricObjectBase.h"

using namespace hypro;

int main() {
  using Number = double;

  LocationManager<Number> &lMan = LocationManager<Number>::getInstance();
  Location<Number> *l1 = lMan.create();

  State<Number, ConstraintSet<Number>> s1(l1);

  matrix_t<Number> matr = matrix_t<Number>::Identity(2, 2);
  vector_t<Number> vec = vector_t<Number>(2);
  vec << 1, 2;
  State<Number, ConstraintSet<Number>> s2(l1, ConstraintSet<Number>(matr, vec));
  State<Number, ConstraintSet<Number>, ConstraintSet<Number>> s3(
      l1, ConstraintSet<Number>(matr, vec), ConstraintSet<Number>(matr, vec));

  std::cout << "Equal: " << (s1.getLocation()->getId() == l1->getId())
            << std::endl;
  std::cout << "Equal: " << (s2.getLocation()->getId() == l1->getId())
            << std::endl;
  std::cout << "Equal: " << (s2.getSet().matrix() == matr) << std::endl;
  std::cout << "Equal: " << (s2.getSet().vector() == vec) << std::endl;
  std::cout << "Equal: " << (s2.getSet<0>().matrix() == matr) << std::endl;
  std::cout << "Equal: " << (s2.getSet<0>().vector() == vec) << std::endl;
  std::cout << "Equal: " << (s3.getSet<1>().matrix() == matr) << std::endl;
  std::cout << "Equal: " << (s3.getSet<1>().vector() == vec) << std::endl;

  matrix_t<Number> matr2 = matrix_t<Number>::Identity(2, 2);
  vector_t<Number> vec2 = vector_t<Number>(2);
  vec << 2, 3;

  ConstraintSet<Number> setUpd(matr2, vec2);

  s3.setSet<1>(setUpd);
  std::cout << "Equal: " << (s3.getSet<1>().matrix() == matr) << std::endl;
  std::cout << "Equal: " << (s3.getSet<1>().vector() == vec)
            << " (should be false) " << std::endl;
  std::cout << "Equal: " << (s3.getSet<1>().matrix() == matr2) << std::endl;
  std::cout << "Equal: " << (s3.getSet<1>().vector() == vec2) << std::endl;

  State<Number, ConstraintSet<Number>, ConstraintSet<Number>> s4(
      l1, ConstraintSet<Number>(matr, vec), ConstraintSet<Number>(matr, vec));

  State<Number, ConstraintSet<Number>, ConstraintSet<Number>> unionResult =
      s4.aggregate(s3);
}
