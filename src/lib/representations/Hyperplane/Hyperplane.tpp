#include "Hyperplane.h"


/**
 * Constructors of Zonotope class
 */

template<typename Number>
Hyperplane<Number>::Hyperplane() : mDimension(0) {
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
Hyperplane<Number>::Hyperplane(const Hyperplane<Number>& other) {
    d_ = other.d_;
    e_ = other.e_;
    mDimension = other.mDimension;
}

template<typename Number>
Hyperplane<Number>::~Hyperplane() {}

/**
 * Public member functions of Zonotope class
 */

template<typename Number>
unsigned int Hyperplane<Number>::dimension() const {
    return mDimension;
}
template<typename Number>
Eigen::Matrix<Number, Eigen::Dynamic, 1> Hyperplane<Number>::vector() const {
    return d_;
}

template<typename Number>
Number Hyperplane<Number>::scalar() const {
    return e_;
}

template<typename Number>
void Hyperplane<Number>::setVector(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& d_vector) {
    if(mDimension==0) {
        mDimension = d_vector.rows();
    }
    assert(mDimension==d_vector.rows());
    d_ = d_vector;
}

template<typename Number>
void Hyperplane<Number>::setScalar(const Number e_scalar){
	e_ = e_scalar;
}

template<typename Number>
bool Hyperplane<Number>::changeDimension(unsigned int newDimension) {
    assert(newDimension!=0);
    unsigned int oldDim = mDimension;
    mDimension = newDimension;
    if (newDimension == oldDim) {
        return false;
    }
    else {
        d_.conservativeResize(newDimension,1);
        for (unsigned i=oldDim; i<newDimension; i++) {
            d_(i) = 0;
        }
    }
    return true;
}