#include "representations/GeometricObjectBase.h"

using namespace hypro;

int main() {

  using maptype = Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, 1>>;

  double *values = new double[3];
  values[0] = 1.0;
  values[1] = 2.0;
  values[2] = 3.0;

  std::size_t dim = 3;

  maptype testMap = maptype(values, dim);

  for (std::size_t i = 0; i < dim; ++i) {
    std::cout << testMap(i) << std::endl;
  }

  vector_t<double> testVec{testMap};

  for (std::size_t i = 0; i < dim; ++i) {
    std::cout << testVec(i) << std::endl;
  }

  delete values;

  return 0;
}