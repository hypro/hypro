

// global typedefs
namespace hypro {
template <typename Number>
using vector_t = Eigen::Matrix<Number, Eigen::Dynamic, 1>;

template <typename Number>
using matrix_t = Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>;

template <typename Number>
using vectorSet = std::set<vector_t<Number>>;

enum State{TRUE,FALSE,NSET};

// Solution types
enum SOLUTION { FEAS = 0, INFEAS, INFTY, UNKNOWN };
}
