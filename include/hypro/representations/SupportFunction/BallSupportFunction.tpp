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
 *(template polyhedra) and their
 *evaluation.
 * @file BallSupportFunction.tpp
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-04-17
 * @version	2015-04-17
 */

#include "BallSupportFunction.h"

namespace hypro {

    template<typename Number>
    BallSupportFunction<Number>::BallSupportFunction(Number _radius, SF_TYPE _type)
            : mDimension(0), mRadius(_radius), mType(_type) {
        assert(_type == SF_TYPE::INFTY_BALL || _type == SF_TYPE::TWO_BALL);
    }

    template<typename Number>
    BallSupportFunction<Number>::BallSupportFunction(const BallSupportFunction<Number> &_orig)
            : mDimension(0), mRadius(_orig.radius()), mType(_orig.type()) {
    }

    template<typename Number>
    BallSupportFunction<Number>::~BallSupportFunction() {
    }

    template<typename Number>
    unsigned BallSupportFunction<Number>::dimension() const {
        return mDimension;
    }

    template<typename Number>
    Number BallSupportFunction<Number>::radius() const {
        return mRadius;
    }

    template<typename Number>
    SF_TYPE BallSupportFunction<Number>::type() const {
        return mType;
    }

    template<typename Number>
    Point<Number> BallSupportFunction<Number>::supremumPoint() const {
        Point<Number> res(vector_t<Number>::Zero(this->dimension()));
        res[0] = mRadius;
        return res;
    }

    template<typename Number>
    EvaluationResult<Number> BallSupportFunction<Number>::evaluate(const vector_t<Number> &l) const {
        EvaluationResult<Number> result;
        // the ball is empty.
        if (mRadius < 0) {
            return result;
        }
        // there is no cost function but the ball is not empty.
        if (l.rows() == 0) {
            return EvaluationResult<Number>(SOLUTION::FEAS);
        }
        // there is a cost function, but it is zero (we know its dimension nonetheless) and the ball is not empty.
        if (l.nonZeros() == 0) {
            return EvaluationResult<Number>(l, SOLUTION::FEAS);
        }

        // there is a non-zero cost function and the ball is not empty.
        switch (mType) {
            case SF_TYPE::INFTY_BALL: {
                unsigned max = 0;
                for (unsigned i = 1; i < l.rows(); ++i) {
                    max = abs(l(i)) > abs(l(max)) ? i : max;
                }
                result.supportValue = (mRadius / abs(l(max)));
                result.optimumValue = result.supportValue * normalize(l);
                result.errorCode = SOLUTION::FEAS;
                break;
            }
            case SF_TYPE::TWO_BALL: {
                Number length = norm(l, true);
                if (length == 0) {
                    return EvaluationResult<Number>(l, SOLUTION::FEAS);
                }
                DEBUG("hypro.representations.BallSupportFunction", "l: " << l << ", length: " << length);
                result.supportValue = (mRadius / length);
                result.optimumValue = result.supportValue * normalize(l);
                result.errorCode = SOLUTION::FEAS;
                break;
            }
            default:
                assert(false);
        }

        return result;
    }

    template<typename Number>
    std::vector<EvaluationResult<Number>> BallSupportFunction<Number>::multiEvaluate(const matrix_t<Number> &_A) const {
        EvaluationResult<Number> r;
        r.supportValue = mRadius;
        r.errorCode = mRadius > 0 ? SOLUTION::FEAS : SOLUTION::INFEAS;
        std::vector<EvaluationResult<Number>> res(_A.rows(), r);
        unsigned cnt = 0;
        for (auto &singleRes: res) {
            singleRes.optimumValue = singleRes.supportValue * normalize(vector_t<Number>(_A.row(cnt)));
            ++cnt;
        }
        assert(res.size() == unsigned(_A.rows()));

        return res;
    }

    template<typename Number>
    bool BallSupportFunction<Number>::contains(const Point<Number> &_point) const {
        return this->contains(_point.rawCoordinates());
    }

    template<typename Number>
    bool BallSupportFunction<Number>::contains(const vector_t<Number> &_point) const {
        switch (mType) {
            case SF_TYPE::INFTY_BALL: {
                return (abs(_point.maxCoeff()) <= mRadius);
                break;
            }
            case SF_TYPE::TWO_BALL: {
                return (norm(_point, true) <= mRadius);
                break;
            }
            default:
                assert(false);
                return false;
        }
    }

    template<typename Number>
    bool BallSupportFunction<Number>::empty() const {
        return (mRadius == 0);
    }
}  // namespace hypro
