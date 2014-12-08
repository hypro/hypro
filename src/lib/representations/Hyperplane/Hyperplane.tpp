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
Hyperplane<Number>::Hyperplane(const hypro::vector_t<Number>& d_vector, hypro::scalar_t<Number> e_scalar) {
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
hypro::vector_t<Number> Hyperplane<Number>::vector() const {
    return d_;
}

template<typename Number>
hypro::scalar_t<Number> Hyperplane<Number>::scalar() const {
    return e_;
}

template<typename Number>
void Hyperplane<Number>::setVector(const hypro::vector_t<Number>& d_vector) {
    if(mDimension==0) {
        mDimension = d_vector.rows();
    }
    assert(mDimension==d_vector.rows());
    d_ = d_vector;
}

template<typename Number>
void Hyperplane<Number>::setScalar(const hypro::scalar_t<Number> e_scalar){
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