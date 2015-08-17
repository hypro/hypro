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
		//std::cout << "Copy constructor, this->type:" << mType << std::endl;
		switch(mType){
			case SF_TYPE::INFTY_BALL:
			case SF_TYPE::TWO_BALL: {
				mBall = _orig.ball();
				break;
			}
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
	SupportFunction<Number>::SupportFunction( Number _radius, SF_TYPE _type) {
		switch (_type) {
			case SF_TYPE::INFTY_BALL:
			case SF_TYPE::TWO_BALL:{
				mBall = new BallSupportFunction<Number>(_radius, _type);
				mType = _type;
				mDimension = 0;
				break;
				}
			default:
				assert(false);
		}
	}

	template<typename Number>
	SupportFunction<Number>::SupportFunction( const matrix_t<Number>& _directions, const vector_t<Number>& _distances, SF_TYPE _type) {
		switch (_type) {
			case SF_TYPE::POLY: {
				mPolytope = new PolytopeSupportFunction<Number>(_directions, _distances);
				mType = SF_TYPE::POLY;
				mDimension = _directions.cols();
				break;
				}
			default:
				assert(false);
		}
	}

	template<typename Number>
	SupportFunction<Number>::SupportFunction( const std::vector<Hyperplane<Number>>& _planes, SF_TYPE _type) {
		switch (_type) {
			case SF_TYPE::POLY: {
				mPolytope = new PolytopeSupportFunction<Number>(_planes);
				mType = SF_TYPE::POLY;
				mDimension = mPolytope->dimension();
				break;
				}
			default:
				assert(false);
		}	
	}
	
	template<typename Number>
	SupportFunction<Number>::SupportFunction( std::shared_ptr<SupportFunction<Number>> _lhs, std::shared_ptr<SupportFunction<Number>> _rhs, SF_TYPE _type) {
		//assert(_lhs.dimension() == _rhs.dimension());
		switch(_type) {
			case SF_TYPE::SUM: {
				mSummands = new sumContent<Number>(_lhs, _rhs);
				mType = SF_TYPE::SUM;
				mDimension = _lhs->dimension();
				assert(_lhs->type() == mSummands->lhs->type() && _rhs->type() == mSummands->rhs->type());
				break;
				}
			case SF_TYPE::UNION: {
				mUnionParameters = new unionContent<Number>(_lhs, _rhs);
				mType = SF_TYPE::UNION;
				mDimension = _lhs->dimension();
				break;
				}
			case SF_TYPE::INTERSECT: {
				mIntersectionParameters = new intersectionContent<Number>(_lhs, _rhs);
				mType = SF_TYPE::INTERSECT;
				mDimension = _lhs->dimension();
				break;
				}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	SupportFunction<Number>::SupportFunction( std::shared_ptr<SupportFunction<Number>> _origin, const matrix_t<Number>& _a, const vector_t<Number>& _b, SF_TYPE _type) {
		switch (_type) {
			case SF_TYPE::LINTRAFO: {
				mLinearTrafoParameters = new trafoContent<Number>(_origin, _a, _b);
				mType = SF_TYPE::LINTRAFO;
				mDimension = _origin->dimension();
				break;
				}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	SupportFunction<Number>::SupportFunction( std::shared_ptr<SupportFunction<Number>> _origin, const Number& _factor, SF_TYPE _type) {
		switch (_type) {
			case SF_TYPE::SCALE: {
				mScaleParameters = new scaleContent<Number>(_origin, _factor);
				mType = SF_TYPE::SCALE;
				mDimension = _origin->dimension();
				break;
				}
			default:
				assert(false);
		}
	}

	template<typename Number>
	SupportFunction<Number>::~SupportFunction() {
		//std::cout << "Destructor of type " << mType << std::endl;
		switch (mType) {
			case SF_TYPE::INFTY_BALL:
			case SF_TYPE::TWO_BALL:
				delete mBall;
				break;
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
	std::shared_ptr<SupportFunction<Number>> SupportFunction<Number>::operator=(std::shared_ptr<SupportFunction<Number>> _other) {
		//std::cout << "Assignment, this->type:" << _other->type() << std::endl;
		mType = _other->type();
		switch (mType) {
			case SF_TYPE::INFTY_BALL:
			case SF_TYPE::TWO_BALL:
				mBall = _other->ball();
				break;
			case SF_TYPE::LINTRAFO:
				mLinearTrafoParameters = _other->linearTrafoParameters();
				break;
			case SF_TYPE::POLY:
				mPolytope = _other->polytope();
				break;
			case SF_TYPE::SCALE:
				mScaleParameters = _other->scaleParameters();
				break;
			case SF_TYPE::SUM:
				mSummands = _other->summands();
				break;
			case SF_TYPE::UNION:
				mUnionParameters = _other->unionParameters();
				break;
			case SF_TYPE::INTERSECT:
				mIntersectionParameters = _other->intersectionParameters();
				break;
			default:
				assert(false);
		}
		return std::shared_ptr<SupportFunction<Number>>(this->pThis);
	}

	template<typename Number>
	evaluationResult<Number> SupportFunction<Number>::evaluate(const vector_t<Number>& _direction) const {
		switch (mType) {
			case SF_TYPE::INFTY_BALL:
			case SF_TYPE::TWO_BALL: {
				return mBall->evaluate(_direction);
				}	
			case SF_TYPE::LINTRAFO: {
				matrix_t<Number> tmp = mLinearTrafoParameters->a.transpose();
				return mLinearTrafoParameters->origin->evaluate(tmp*_direction);
				}
			case SF_TYPE::POLY: {
				return mPolytope->evaluate(_direction);
				}
			case SF_TYPE::SCALE: {
				evaluationResult<Number> res = mScaleParameters->origin->evaluate(_direction);
				res.optimumValue *= mScaleParameters->factor;
				res.supportValue *= mScaleParameters->factor;
				return res;
				}
			case SF_TYPE::SUM: {
				evaluationResult<Number> resA = mSummands->lhs->evaluate(_direction);
				evaluationResult<Number> resB = mSummands->rhs->evaluate(_direction);
				resA.optimumValue += resB.optimumValue;
				resA.supportValue += resB.supportValue;
				return resA;
				}
			case SF_TYPE::UNION: {
				evaluationResult<Number> resA = mSummands->lhs->evaluate(_direction);
				evaluationResult<Number> resB = mSummands->rhs->evaluate(_direction);
				return (resA.supportValue >= resB.supportValue ? resA : resB);
				}
			case SF_TYPE::INTERSECT: {
				evaluationResult<Number> resA = mIntersectionParameters->lhs->evaluate(_direction);
				evaluationResult<Number> resB = mIntersectionParameters->rhs->evaluate(_direction);
				return (resA.supportValue <= resB.supportValue ? resA : resB);
				}
			default:
				assert(false);
		}
	}
	
	template<typename Number>
	vector_t<Number> SupportFunction<Number>::multiEvaluate(const matrix_t<Number>& _directions) const {
		//std::cout << "Multi-evaluate, type: " << mType << std::endl;
		switch (mType) {
			case SF_TYPE::INFTY_BALL:
			case SF_TYPE::TWO_BALL: {
				return mBall->multiEvaluate(_directions);
				}
			case SF_TYPE::LINTRAFO: {
				matrix_t<Number> tmp = mLinearTrafoParameters->a.transpose();
				return mLinearTrafoParameters->origin->multiEvaluate(_directions*tmp);
				}
			case SF_TYPE::POLY: {
				return mPolytope->multiEvaluate(_directions);
				}
			case SF_TYPE::SCALE: {
				return mScaleParameters->origin->multiEvaluate(_directions)*(mScaleParameters->factor);
				}
			case SF_TYPE::SUM: {
				vector_t<Number> resA = mSummands->lhs->multiEvaluate(_directions);
				vector_t<Number> resB = mSummands->rhs->multiEvaluate(_directions);
				//std::cout << resA.cols() << "," << resA.rows() << " added to " << resB.cols() << "," << resB.rows() <<std::endl;
				return (resA + resB);
				}
			case SF_TYPE::UNION: {
				vector_t<Number> resA = mUnionParameters->lhs->multiEvaluate(_directions);
				vector_t<Number> resB = mUnionParameters->rhs->multiEvaluate(_directions);
				assert(resA.rows() == resB.rows());
				vector_t<Number> result = vector_t<Number>(resA.rows());
				for(unsigned i=0; i<result.rows(); ++i) {
					result(i) = resA(i) > resB(i) ? resA(i) : resB(i);
				}
				return result;
				}
			case SF_TYPE::INTERSECT: {
				vector_t<Number> resA = mIntersectionParameters->lhs->multiEvaluate(_directions);
				vector_t<Number> resB = mIntersectionParameters->rhs->multiEvaluate(_directions);
				assert(resA.rows() == resB.rows());
				vector_t<Number> result = vector_t<Number>(resA.rows());
				for(unsigned i=0; i<result.rows(); ++i) {
					result(i) = resA(i) < resB(i) ? resA(i) : resB(i);
				}
				return result;
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
	BallSupportFunction<Number>* SupportFunction<Number>::ball() const {
		switch (mType) {
			case SF_TYPE::INFTY_BALL:
			case SF_TYPE::TWO_BALL: {
				return mBall;
				break;
			}
			default:
				assert(false);
		}
	}

	template<typename Number>
	std::shared_ptr<SupportFunction<Number>> SupportFunction<Number>::linearTransformation(const matrix_t<Number>& _A, const vector_t<Number>& _b) const {
		auto obj = std::shared_ptr<SupportFunction<Number>>(new SupportFunction<Number>( std::shared_ptr<SupportFunction<Number>>(this->pThis), _A, _b, SF_TYPE::LINTRAFO));
		obj->pThis = obj;
		return obj;
	}
	
	template<typename Number>
	std::shared_ptr<SupportFunction<Number>> SupportFunction<Number>::minkowskiSum(std::shared_ptr<SupportFunction<Number>> _rhs) const {
		auto obj = std::shared_ptr<SupportFunction<Number>>(new SupportFunction<Number>( std::shared_ptr<SupportFunction<Number>>(this->pThis), _rhs, SF_TYPE::SUM));
		obj->pThis = obj;
		return obj;
	}
	
	template<typename Number>
	std::shared_ptr<SupportFunction<Number>> SupportFunction<Number>::intersect(std::shared_ptr<SupportFunction<Number>> _rhs) const {
		auto obj = std::shared_ptr<SupportFunction<Number>>(new SupportFunction<Number>( std::shared_ptr<SupportFunction<Number>>(this->pThis), _rhs, SF_TYPE::INTERSECT));
		obj->pThis = obj;
		return obj;
	}
	
	template<typename Number>
	bool SupportFunction<Number>::contains(const Point<Number>& _point) const {
		return this->contains(_point.rawCoordinates());
	}

	template<typename Number>
	bool SupportFunction<Number>::contains(const vector_t<Number>& _point) const {
		switch (mType) {
			case SF_TYPE::INFTY_BALL:
			case SF_TYPE::TWO_BALL: {
				return mBall->contains(_point);
				}
			case SF_TYPE::LINTRAFO: {
				matrix_t<Number> tmp = mLinearTrafoParameters->a.transpose();
				return mLinearTrafoParameters->origin->contains(tmp*_point);
				}
			case SF_TYPE::POLY: {
				return mPolytope->contains(_point);
				}
			case SF_TYPE::SCALE: {
				if(mScaleParameters->factor == 0)
					return false;
				else 
					return mScaleParameters->origin->contains(_point/mScaleParameters->factor); 
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
	std::shared_ptr<SupportFunction<Number>> SupportFunction<Number>::unite(std::shared_ptr<SupportFunction<Number>> _rhs) const {
		auto obj = std::shared_ptr<SupportFunction<Number>>(new SupportFunction<Number>( std::shared_ptr<SupportFunction<Number>>(this->pThis), _rhs, SF_TYPE::UNION));
		obj->pThis = obj;
		return obj;
	}
	
	template<typename Number>
	std::shared_ptr<SupportFunction<Number>> SupportFunction<Number>::scale(const Number& _factor) const {
		auto obj = std::shared_ptr<SupportFunction<Number>>(new SupportFunction<Number>( std::shared_ptr<SupportFunction<Number>>(this->pThis), _factor, SF_TYPE::SCALE));
		obj->pThis = obj;
		return obj;
	}
	
	template<typename Number>
	bool SupportFunction<Number>::isEmpty() const {
		switch (mType) {
			case SF_TYPE::INFTY_BALL:
			case SF_TYPE::TWO_BALL: {
				return mBall->empty();
				}
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
				return (mSummands->lhs->empty() && mSummands->rhs->empty());
				}
			case SF_TYPE::UNION: {
				return (mUnionParameters->lhs->empty() && mUnionParameters->rhs->empty());
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

	template<typename Number>
	void SupportFunction<Number>::print() const {
		switch (mType) {
			case SF_TYPE::INFTY_BALL:{
				std::cout << "INFTY-BALL" << std::endl;
				}
				break;
			case SF_TYPE::TWO_BALL: {
				std::cout << "2-BALL" << std::endl;
				}
				break;
			case SF_TYPE::LINTRAFO: {
				std::cout << "LINTRAFO" << std::endl;
				std::cout << "of" << std::endl;
				mLinearTrafoParameters->origin->print();
				}
				break;
			case SF_TYPE::POLY: {
				std::cout << "POLY" << std::endl;
				}
				break;
			case SF_TYPE::SCALE: {
				std::cout << "SCALE" << std::endl;
				}
				break;
			case SF_TYPE::SUM: {
				std::cout << "SUM" << std::endl;
				std::cout << "of: " << std::endl;
				mSummands->rhs->print();
				std::cout << "and" << std::endl;
				mSummands->lhs->print();
				}
				break;
			case SF_TYPE::UNION: {
				std::cout << "UNION" << std::endl;
				}
				break;
			case SF_TYPE::INTERSECT: {
				std::cout << "INTERSECT" << std::endl;
				}
				break;
			default:
				std::cout << "NONE" << std::endl;
		}	
	}
	
} // namespace