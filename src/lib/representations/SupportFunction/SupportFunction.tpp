/**
 *	File which holds the implementation of support functions.
 * @file SupportFunction.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since	2015-02-20
 * @version	2015-02-27
 */

#include "SupportFunction.h"

namespace hypro {
	
	template<typename Number>
	SupportFunction<Number>::SupportFunction(const SupportFunction<Number>& _orig) : 
		mType(_orig.type()),
		mDimension(_orig.dimension())
	{
		switch(mType){
			case SF_TYPE::INTERSECT: {
				mIntersectionParameters = _orig.intersectionParameters();
				break;
			}
			case SF_TYPE::LINTRAFO: {
				mLinearTrafoParameters = _orig.linearTrafoParameters();
				break;
			}
			case SF_TYPE::POLY: {
				mPolytope = _orig.polytope();
				break;
			}
			case SF_TYPE::SCALE: {
				mScaleParameters = _orig.scaleParameters();
				break;
			}
			case SF_TYPE::SUM: {
				mSummands = _orig.summands();
				break;
			}
			case SF_TYPE::UNION: {
				mUnionParameters = _orig.unionParameters();
				break;
			}
			default:
				assert(false);
		}
	}

	template<typename Number>
	SupportFunction<Number>::SupportFunction(SF_TYPE _type, const matrix_t<Number>& _directions, const vector_t<Number>& _distances) {
		switch (_type) {
			case SF_TYPE::POLY: {
				mPolytope = new PolytopeSupportFunction<Number>(_directions, _distances);
				mType = SF_TYPE::POLY;
				mDimension = _distances.rows();
				break;
				}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	SupportFunction<Number>::SupportFunction(SF_TYPE _type, const SupportFunction<Number>& _lhs, const SupportFunction<Number>& _rhs) {
		assert(_lhs.dimension() == _rhs.dimension());
		switch(_type) {
			case SF_TYPE::SUM: {
				mSummands = new sumContent<Number>(_lhs, _rhs);
				mType = SF_TYPE::SUM;
				mDimension = _lhs.dimension();
				break;
				}
			case SF_TYPE::UNION: {
				mUnionParameters = new unionContent<Number>(_lhs, _rhs);
				mType = SF_TYPE::UNION;
				mDimension = _lhs.dimension();
				break;
				}
			case SF_TYPE::INTERSECT: {
				mIntersectionParameters = new intersectionContent<Number>(_lhs, _rhs);
				mType = SF_TYPE::INTERSECT;
				mDimension = _lhs.dimension();
				break;
				}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	SupportFunction<Number>::SupportFunction(SF_TYPE _type, const SupportFunction<Number>& _origin, const matrix_t<Number>& _a, const vector_t<Number>& _b) {
		switch (_type) {
			case SF_TYPE::LINTRAFO: {
				mLinearTrafoParameters = new trafoContent<Number>(_origin, _a, _b);
				mType = SF_TYPE::LINTRAFO;
				mDimension = _origin.dimension();
				break;
				}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	SupportFunction<Number>::SupportFunction(SF_TYPE _type, const SupportFunction<Number>& _origin, const Number& _factor) {
		switch (_type) {
			case SF_TYPE::SCALE: {
				mScaleParameters = new scaleContent<Number>(_origin, _factor);
				mType = SF_TYPE::SCALE;
				mDimension = _origin.dimension();
				break;
				}
			default:
				assert(false);
		}
	}

	template<typename Number>
	SupportFunction<Number>::~SupportFunction() {
		switch (mType) {
			case SF_TYPE::LINTRAFO:
				delete mLinearTrafoParameters;
				break;
			case SF_TYPE::POLY:
				delete mPolytope;
				break;
			case SF_TYPE::SCALE:
				delete mScaleParameters;
				break;
			case SF_TYPE::SUM:
				delete mSummands;
				break;
			case SF_TYPE::UNION:
				delete mUnionParameters;
				break;
			case SF_TYPE::INTERSECT:
				delete mIntersectionParameters;
				break;
			default:
				assert(false);
		}
	}

	template<typename Number>
	evaluationResult<Number> SupportFunction<Number>::evaluate(const vector_t<Number>& _direction) const {
		switch (mType) {
			case SF_TYPE::LINTRAFO: {
				matrix_t<Number> tmp = mLinearTrafoParameters->a.transpose();
				return mLinearTrafoParameters->origin.evaluate(tmp*_direction);
				}
			case SF_TYPE::POLY: {
				return mPolytope->evaluate(_direction);
				}
			case SF_TYPE::SCALE: {
				evaluationResult<Number> res = mScaleParameters->origin.evaluate(_direction);
				res.optimumValue *= mScaleParameters->factor;
				res.supportValue *= mScaleParameters->factor;
				return res;
				}
			case SF_TYPE::SUM: {
				evaluationResult<Number> resA = mSummands->lhs.evaluate(_direction);
				evaluationResult<Number> resB = mSummands->rhs.evaluate(_direction);
				resA.optimumValue += resB.optimumValue;
				resA.supportValue += resB.supportValue;
				return resA;
				}
			case SF_TYPE::UNION: {
				evaluationResult<Number> resA = mSummands->lhs.evaluate(_direction);
				evaluationResult<Number> resB = mSummands->rhs.evaluate(_direction);
				return (resA.supportValue >= resB.supportValue ? resA : resB);
				}
			case SF_TYPE::INTERSECT: {
				// Todo: Not implemented yet.
				assert(false);
				}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	vector_t<Number> SupportFunction<Number>::multiEvaluate(const matrix_t<Number>& _directions) const {
		switch (mType) {
			case SF_TYPE::LINTRAFO: {
				matrix_t<Number> tmp = mLinearTrafoParameters->a.transpose();
				return mLinearTrafoParameters->origin.multiEvaluate(tmp*_directions);
				}
			case SF_TYPE::POLY: {
				return mPolytope->multiEvaluate(_directions);
				}
			case SF_TYPE::SCALE: {
				return mScaleParameters->origin.multiEvaluate(_directions)*(mScaleParameters->factor);
				}
			case SF_TYPE::SUM: {
				// Todo: Not implemented yet.
				assert(false);
				}
			case SF_TYPE::UNION: {
				// Todo: Not implemented yet.
				assert(false);
				}
			case SF_TYPE::INTERSECT: {
				// Todo: Not implemented yet.
				assert(false);
				}
			default:
				assert(false);
		}
	}

	template<typename Number>
	unsigned SupportFunction<Number>::dimension() const{
		return mDimension;
	}
	
	template<typename Number>
	SF_TYPE SupportFunction<Number>::type() const{
		return mType;
	}
	
	template<typename Number>
	sumContent<Number>* SupportFunction<Number>::summands() const {
		switch (mType) {
			case SF_TYPE::SUM: {
				return mSummands;
				break;
			}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	trafoContent<Number>* SupportFunction<Number>::linearTrafoParameters() const {
		switch (mType) {
			case SF_TYPE::LINTRAFO: {
				return mLinearTrafoParameters;
				break;
			}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	scaleContent<Number>* SupportFunction<Number>::scaleParameters() const {
		switch (mType) {
			case SF_TYPE::SCALE: {
				return mScaleParameters;
				break;
			}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	unionContent<Number>* SupportFunction<Number>::unionParameters() const {
		switch (mType) {
			case SF_TYPE::UNION: {
				return mUnionParameters;
				break;
			}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	intersectionContent<Number>* SupportFunction<Number>::intersectionParameters() const {
		switch (mType) {
			case SF_TYPE::INTERSECT: {
				return mIntersectionParameters;
				break;
			}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	PolytopeSupportFunction<Number>* SupportFunction<Number>::polytope() const {
		switch (mType) {
			case SF_TYPE::POLY: {
				return mPolytope;
				break;
			}
			default:
				assert(false);
		}
	}

	template<typename Number>
	SupportFunction<Number> SupportFunction<Number>::linearTransformation(const matrix_t<Number>& _A, const vector_t<Number>& _b) const {
		return SupportFunction<Number>(SF_TYPE::LINTRAFO, *this, _A, _b);
	}
	
	template<typename Number>
	SupportFunction<Number> SupportFunction<Number>::minkowskiSum(const SupportFunction<Number>& _rhs) const {
		return SupportFunction<Number>(SF_TYPE::SUM, *this, _rhs);
	}
	
	template<typename Number>
	SupportFunction<Number> SupportFunction<Number>::intersect(const SupportFunction<Number>& _rhs) const {
		return SupportFunction<Number>(SF_TYPE::INTERSECT, *this, _rhs);
	}
	
	template<typename Number>
	bool SupportFunction<Number>::contains(const Point<Number>& _point) const {
		return this->contains(_point.rawCoordinates());
	}

	template<typename Number>
	bool SupportFunction<Number>::contains(const vector_t<Number>& _point) const {
		switch (mType) {
			case SF_TYPE::LINTRAFO: {
				matrix_t<Number> tmp = mLinearTrafoParameters->a.transpose();
				return mLinearTrafoParameters->origin.contains(tmp*_point);
				}
			case SF_TYPE::POLY: {
				return mPolytope->contains(_point);
				}
			case SF_TYPE::SCALE: {
				if(mScaleParameters->factor == 0)
					return false;
				else 
					return mScaleParameters->origin.contains(_point/mScaleParameters->factor); 
				}
			case SF_TYPE::SUM: {
				assert(false); // Todo: Not implemented yet.
				return false;
				}
			case SF_TYPE::UNION: {
				assert(false); // Todo: Not implemented yet.
				return false;
				}
			case SF_TYPE::INTERSECT: {
				assert(false); // Todo: Not implemented yet.
				return false;
				}
			default:
				assert(false);
				return false;
		}
		return true;
	}
	
	template<typename Number>
	SupportFunction<Number> SupportFunction<Number>::unite(const SupportFunction<Number>& _rhs) const {
		return SupportFunction<Number>(SF_TYPE::UNION, *this, _rhs);
	}
	
	template<typename Number>
	SupportFunction<Number> SupportFunction<Number>::scale(const Number& _factor) const {
		return SupportFunction<Number>(SF_TYPE::SCALE, *this, _factor);
	}
	
	template<typename Number>
	bool SupportFunction<Number>::isEmpty() const {
		switch (mType) {
			case SF_TYPE::LINTRAFO: {
				assert(false); // Todo: Not implemented yet.
				return false;
				}
			case SF_TYPE::POLY: {
				return mPolytope->empty();
				}
			case SF_TYPE::SCALE: {
				if(mScaleParameters->factor == 0)
					return true;
				else 
					return mScaleParameters->origin.empty(); // Todo: What if factor is negative?
				}
			case SF_TYPE::SUM: {
				return (mSummands->lhs.empty() && mSummands->rhs.empty());
				}
			case SF_TYPE::UNION: {
				return (mUnionParameters->lhs.empty() && mUnionParameters->rhs.empty());
				}
			case SF_TYPE::INTERSECT: {
				assert(false); // Todo: Not implemented yet.
				return false;
				}
			default:
				assert(false);
				return false;
		}
	}

} // namespace