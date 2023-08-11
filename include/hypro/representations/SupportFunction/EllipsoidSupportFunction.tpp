/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * This file contains the basic implementation of support functions of polyhedra
 * (template polyhedra) and their
 * evaluation.
 * @file EllipsoidSupportFunction.tpp
 *
 * @author Phillip Florian
 *
 * @since	2016-05-04
 * @version	2016-05-04
 */

#include "EllipsoidSupportFunction.h"

namespace hypro {

    template<typename Number>
    EllipsoidSupportFunction<Number>::EllipsoidSupportFunction(matrix_t<Number> _matrix)
            : mDimension(_matrix.rows()), mShapeMatrix(_matrix) {
        mType = SF_TYPE::ELLIPSOID;
        assert(_matrix.transpose() == _matrix);  // symmetric
        // Todo: _matrix is positive definite?
    }

    template<typename Number>
    EllipsoidSupportFunction<Number>::EllipsoidSupportFunction(const EllipsoidSupportFunction<Number> &_orig)
            : mDimension(_orig.dimension()), mShapeMatrix(_orig.shapeMatrix()), mType(_orig.type()) {
    }

    template<typename Number>
    EllipsoidSupportFunction<Number>::~EllipsoidSupportFunction() {
    }

    template<typename Number>
    unsigned EllipsoidSupportFunction<Number>::dimension() const {
        return mDimension;
    }

    template<typename Number>
    std::vector<EvaluationResult<Number>>
    EllipsoidSupportFunction<Number>::multiEvaluate(const matrix_t<Number> &_A) const {
        assert(_A.cols() == mDimension);
        std::vector<EvaluationResult<Number>> res;
        //	std::cout << "ELLIPSOID SF, evaluate in directions " << convert<Number,double>(_A) << std::endl;
        for (unsigned index = 0; index < _A.rows(); ++index) {
            res.push_back(evaluate(_A.row(index)));
            // assert(res.back().errorCode != SOLUTION::FEAS || this->contains(res.back().optimumValue));
            // assert(this->contains(res.back().optimumValue));
        }
        assert(res.size() == std::size_t(_A.rows()));
        return res;
    }

    template<typename Number>
    bool EllipsoidSupportFunction<Number>::contains(const Point<Number> &_point) const {
        return this->contains(_point.rawCoordinates());
    }

    template<typename Number>
    bool EllipsoidSupportFunction<Number>::contains(const vector_t<Number> &_point) const {
        if (carl::sqrt_safe(_point.dot(this->mShapeMatrix * _point)).second <= 1) {
            return true;
        }
        return false;
    }

    template<typename Number>
    bool EllipsoidSupportFunction<Number>::empty() const {
        for (unsigned i = 0; i < mShapeMatrix.rows(); i++) {
            for (unsigned j = 0; j < mShapeMatrix.cols(); j++) {
                if (mShapeMatrix(i, j) != 0)
                    return false;
            }
        }
        return true;
    }

}  // namespace hypro
