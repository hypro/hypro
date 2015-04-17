/*
 * This file contains the basic implementation of support functions of polyhedra (template polyhedra) and their evaluation.
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
	BallSupportFunction<Number>::BallSupportFunction(Number _radius, SF_TYPE _type) : 
		mDimension(0),
		mRadius(_radius),
		mType(_type)
	{
		assert(_type == SF_TYPE::INFTY_BALL || _type == SF_TYPE::TWO_BALL);
	}

	template<typename Number>
	BallSupportFunction<Number>::BallSupportFunction(const BallSupportFunction<Number>& _orig) : 
		mDimension(0),
		mRadius(_orig.radius()),
		mType(_orig.type())
	{}
	
	template<typename Number>
	BallSupportFunction<Number>::~BallSupportFunction()
	{}
	
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
	evaluationResult<Number> BallSupportFunction<Number>::evaluate(const vector_t<Number>& l) const {
		evaluationResult<Number> result;
		switch(mType) {
			case SF_TYPE::INFTY_BALL: {
				unsigned max = 0;
				for(unsigned i = 1; i<l.rows(); ++i) {
					max = abs(l(i)) > abs(l(max)) ? i : max;
				}
				result.supportValue = (mRadius/abs(l(max)));
				break;
			}
			case SF_TYPE::TWO_BALL: {
				Number length = l.norm();
				result.supportValue = (mRadius/length);
				break;
			}
			default:
				assert(false);
		}

		return result;
	}

	template<typename Number>
	vector_t<Number> BallSupportFunction<Number>::multiEvaluate(const matrix_t<Number>& _A) const {
		vector_t<Number> res(_A.rows());

		for(unsigned index = 0; index < _A.rows(); ++index) {
			res(index) = mRadius;
		}

		return res;
	}

	template<typename Number>
	bool BallSupportFunction<Number>::contains(const Point<Number>& _point) const {
		return this->contains(_point.rawCoordinates());
	}

	template<typename Number>
	bool BallSupportFunction<Number>::contains(const vector_t<Number>& _point) const {
		switch(mType) {
			case SF_TYPE::INFTY_BALL: {
				return (abs(_point.maxCoeff()) <= mRadius);
				break;
			}
			case SF_TYPE::TWO_BALL: {
				return (_point.norm() <= mRadius);
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
} // namespace
