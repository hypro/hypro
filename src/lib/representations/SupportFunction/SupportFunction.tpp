/**
 *	File which holds the implementation of support functions.
 * @file SupportFunction.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since	20-02-2015
 * @version	20-02-2015
 */

#include "SupportFunction.h"

namespace hypro {

	template<typename Number>
	SupportFunction<Number>::SupportFunction(SF_TYPE _type, const matrix_t<Number>& _directions, const vector_t<Number>& _distances) {
		switch (_type) {
			case SF_TYPE::POLY:
				mPolytope = new PolytopeSupportFunction(_directions, _distances);
				mType = SF_TYPE::POLY;
				mDimension = _distances.rows();
				break;
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	SupportFunction<Number>::SupportFunction(SF_TYPE _type, SupportFunction<Number>* _lhs, SupportFunction<Number>* _rhs) {
		assert(_lhs->dimension() == _rhs->dimension());
		switch(_type) {
			case SF_TYPE::SUM:
				mSummands.lhs = _lhs;
				mSummands.rhs = _rhs;
				mType = SF_TYPE::SUM;
				mDimension = _lhs->dimension();
				break;
			case SF_TYPE::UNION:
				mUnionParameters.lhs = _lhs;
				mUnionParameters.rhs = _rhs;
				mType = SF_TYPE::UNION;
				mDimension = _lhs->dimension();
				break;
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	SupportFunction<Number>::SupportFunction(SF_TYPE _type, SupportFunction<Number>* _origin, const matrix_t<Number>& _a, const vector_t<Number>& _b = vector_t<Number>()) {
		switch (_type) {
			case SF_TYPE::LINTRAFO:
				mLinearTrafoParameters.origin = _origin;
				mLinearTrafoParameters.a = _a;
				mLinearTrafoParameters.b = _b;
				mType = SF_TYPE::LINTRAFO;
				mDimension = _origin->dimension();
				break;
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	SupportFunction<Number>::SupportFunction(SF_TYPE _type, SupportFunction<Number>* _origin, const Number& _factor) {
		switch (_type) {
			case SF_TYPE::SCALE:
				mScaleParameters.origin = _origin;
				mScaleParameters.factor = _factor;
				mType = SF_TYPE::SCALE;
				mDimension = _origin->dimension();
				break;
			default:
				assert(false);
		}
	}

	virtual SupportFunction<Number>::~SupportFunction() {
		switch (mType) {
			case SF_TYPE::LINTRAFO:
				delete mLinearTrafoParameters.origin;
				break;
			case SF_TYPE::POLY:
				delete mPolytope;
				break;
			case SF_TYPE::SCALE:
				delete mScaleParameters.origin;
				break;
			case SF_TYPE::SUM:
				delete mSummands.lhs;
				delete mSummands.rhs;
				break;
			default:
		}
	}

	template<typename Number>
	evaluationResult<Number> SupportFunction<Number>::evaluate(const vector_t<Number>& _direction) const {
		switch (mType) {
			case SF_TYPE::LINTRAFO:
				matrix_t<Number> tmp = mLinearTrafoParameters.a.transpose();
				return mLinearTrafoParameters.origin->evaluate(tmp*_direction);
			case SF_TYPE::POLY:
				return mPolytope->evaluate(_direction);
			case SF_TYPE::SCALE:
				evaluationResult<Number> res = mScaleParameters.origin->evaluate(_direction);
				res.optimumValue *= mScaleParameters.factor;
				res.supportValue *= mScaleParameters.factor;
				return res;
			case SF_TYPE::SUM:
				evaluationResult<Number> resA = mSummands.lhs->evaluate(_direction);
				evaluationResult<Number> resB = mSummands.rhs->evaluate(_direction);
				resA.optimumValue += resB.optimumValue;
				resA.supportValue += resB.supportValue;
				return resA;
			default:
		}
	}
	
	template<typename Number>
	vector_t<Number> SupportFunction<Number>::multiEvaluate(const std::vector<vector_t<Number>>& _directions) const {
		switch (mType) {
			case SF_TYPE::LINTRAFO:
				break;
			case SF_TYPE::POLY:
				break;
			case SF_TYPE::SCALE:
				break;
			case SF_TYPE::SUM:
				break;
			default:
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
	SupportFunction<Number>* SupportFunction<Number>::linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b = vector_t<Number>()) const {
		return new SupportFunction<Number>(SF_TYPE::LINTRAFO, this, A, b);
	}
	
	template<typename Number>
	SupportFunction<Number>* SupportFunction<Number>::minkowskiSum(SupportFunction<Number>* rhs) const {
		return new SupportFunction<Number>(SF_TYPE::SUM, this,rhs);
	}
	
	template<typename Number>
	SupportFunction<Number>* SupportFunction<Number>::intersect(SupportFunction<Number>* rhs) const;
	
	template<typename Number>
	bool SupportFunction<Number>::contains(const Point<Number>& point) const;
	
	template<typename Number>
	SupportFunction<Number>* SupportFunction<Number>::unite(SupportFunction<Number>* rhs) const;

} // namespace