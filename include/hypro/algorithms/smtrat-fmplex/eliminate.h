#pragma once

#include <vector>

#include <carl-formula/formula/Formula.h>
#include <carl-arith/poly/umvpoly/MultivariatePolynomial.h>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/StdVector>

#include "fmplex.h"

namespace smtrat::fmplex {

template<typename Number>
using Formula  = carl::Formula<carl::MultivariatePolynomial<Number>>;
template<typename Number>
using EigenMat = Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>;
template<typename Number>
using EigenVec = Eigen::Matrix<Number, Eigen::Dynamic, 1>;

template<typename Number>
Formula<Number> eliminate_variables(const Formula<Number>& f, const std::vector<carl::Variable>& vars);

template<typename Number>
std::pair<EigenMat<Number>, EigenVec<Number>> eliminate_cols(const EigenMat<Number>& constraints,
                                             const EigenVec<Number>& constants,
                                             const std::vector<std::size_t>& cols);
template<typename Number>
void write_matrix_to_ine(const EigenMat<Number>& constraints, const EigenVec<Number>& constants,
                         const std::vector<std::size_t>& cols, const std::string& filename);

}

#include "eliminate.tpp"