#include "Hyperplane.h"

template<typename Number>
Hyperplane<Number>::Hyperplane() {
}

template<typename Number>
Hyperplane<Number>::Hyperplane(unsigned int dimension) {
    mDimension = dimension;
}

template<typename Number>
Hyperplane<Number>::Hyperplane(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& d_vector, Number e_scalar) {
    mDimension = d_vector.rows();
    d_ = d_vector;
    e_ = e_scalar;
}

template<typename Number>
Hyperplane<Number>::~Hyperplane() {}

template<typename Number>
unsigned int Hyperplane<Number>::dimension() const {
    return mDimension;
}
template<typename Number>
Eigen::Matrix<Number, Eigen::Dynamic, 1> Hyperplane<Number>::getDVector() const {
    return d_;
}

template<typename Number>
Number Hyperplane<Number>::getEValue() const {
    return e_;
}

template<typename Number>
void Hyperplane<Number>::setDVector(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& d_vector) {
	d_ = d_vector;
}

template<typename Number>
void Hyperplane<Number>::setEValue(const Number e_scalar){
	e_ = e_scalar;
}