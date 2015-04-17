/*
 * This file contains the basic implementation of support functions of polyhedra (template polyhedra) and their evaluation.
 * @file ElipsoidSupportFunction.tpp
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since	2015-04-17
 * @version	2015-04-17
 */

#include "ElipsoidSupportFunction.h"

namespace hypro {
	
	template<typename Number>
	ElipsoidSupportFunction<Number>::ElipsoidSupportFunction(matrix_t<Number> _matrix, Number _distance) : 
		mDimension(_matrix.rows()),
		mRadius(_radius),
		mType(_type)
	{
		assert(_matrix.transpose() == _matrix); // symmetric
		// Todo: _matrix is positive definite?
	}	
	
	template<typename Number>
	ElipsoidSupportFunction<Number>::~ElipsoidSupportFunction()
	{}
	
	template<typename Number>
	unsigned ElipsoidSupportFunction<Number>::dimension() const {
		return mDimension;
	}
	
	template<typename Number>
	evaluationResult<Number> ElipsoidSupportFunction<Number>::evaluate(const vector_t<Number>& l) const {
		evaluationResult<Number> result;
		result.supportValue = mRadius;

		return result;
	}

	template<typename Number>
	vector_t<Number> ElipsoidSupportFunction<Number>::multiEvaluate(const matrix_t<Number>& _A) const {
		vector_t<Number> res(_A.rows());

		for(unsigned index = 0; index < _A.rows(); ++index) {
			res(index) = mRadius;
		}

		return res;
	}

	template<typename Number>
	bool ElipsoidSupportFunction<Number>::contains(const Point<Number>& _point) const {
		return this->contains(_point.rawCoordinates());
	}

	template<typename Number>
	bool ElipsoidSupportFunction<Number>::contains(const vector_t<Number>& _point) const {
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
	bool ElipsoidSupportFunction<Number>::empty() const {
		return (mRadius == 0);
	}
} // namespace
