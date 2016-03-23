#pragma once

#include <eigen3/Eigen/Dense>

namespace hypro {
template <typename Number>
using vector_t = Eigen::Matrix<Number, Eigen::Dynamic, 1>;

template <typename Number>
using matrix_t = Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>;

enum State{TRUE,FALSE,NSET};

// Solution types
enum SOLUTION { FEAS = 0, INFEAS, INFTY, UNKNOWN };
} // namespace hypro

#include "util/adaptions_eigen.h"