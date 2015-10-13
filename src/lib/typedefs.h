

// global typedefs
namespace hypro {
template <typename Number>
using vector_t = Eigen::Matrix<Number, Eigen::Dynamic, 1>;

template <typename Number>
using matrix_t = Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>;

template <typename Number>
class Polytope;

//template <typename Number>
//using valuation_t = Polytope<Number>;

template <typename Number>
using vectorSet = std::set<vector_t<Number>>;

typedef mpq_class Rational;
typedef carl::MultivariatePolynomial<Rational> Poly;
}