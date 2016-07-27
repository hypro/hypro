/**
 *	File which holds the implementation of support functions.
 * @file SupportFunctionContent.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-02-20
 * @version	2015-02-27
 */

#include "SupportFunctionContent.h"

namespace hypro {

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( const SupportFunctionContent<Number> &_orig )
	: mType( _orig.type() ), mDimension( _orig.dimension(), mDepth( _orig.depth()) ) {
	// std::cout << "Copy constructor, this->type:" << mType << std::endl;
	switch ( mType ) {
		case SF_TYPE::ELLIPSOID: {
                    mEllipsoid = _orig.ellipsoid();
                    break;
                }
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
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( const matrix_t<Number>& _shapeMatrix, SF_TYPE _type ) {
    	switch ( _type ) {
		case SF_TYPE::ELLIPSOID: {
			mEllipsoid = new EllipsoidSupportFunction<Number>( _shapeMatrix);
			mType = SF_TYPE::ELLIPSOID;
			mDimension = _shapeMatrix.cols();
                        mDepth = 0;
                        mOperationCount = 1;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( Number _radius, SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			mBall = new BallSupportFunction<Number>( _radius, _type );
			mType = _type;
			mDimension = 0;
                        mDepth = 0;
                        mOperationCount = 0;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( const matrix_t<Number> &_directions, const vector_t<Number> &_distances,
										  SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::POLY: {
			mPolytope = new PolytopeSupportFunction<Number>( _directions, _distances );
			mType = SF_TYPE::POLY;
			mDimension = _directions.cols();
                        mDepth = 0;
                        mOperationCount = 0;
                        
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( const std::vector<Halfspace<Number>>& _planes, SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::POLY: {
			mPolytope = new PolytopeSupportFunction<Number>( _planes );
			mType = SF_TYPE::POLY;
			mDimension = mPolytope->dimension();
                        mDepth = 0;
                        mOperationCount = 0;
			break;
		}
		default:
			assert( false );
	}
}

template<typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( const std::vector<Point<Number>>& _points, SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::POLY: {
			mPolytope = new PolytopeSupportFunction<Number>( _points );
			mType = SF_TYPE::POLY;
			mDimension = mPolytope->dimension();
                        mDepth = 0;
                        mOperationCount = 0;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( std::shared_ptr<SupportFunctionContent<Number>> _lhs,
										  std::shared_ptr<SupportFunctionContent<Number>> _rhs, SF_TYPE _type ) {
	// assert(_lhs.dimension() == _rhs.dimension());
	switch ( _type ) {
		case SF_TYPE::SUM: {
			mSummands = new sumContent<Number>( _lhs, _rhs );
			mType = SF_TYPE::SUM;
			mDimension = _lhs->dimension();
			assert( _lhs->type() == mSummands->lhs->type() && _rhs->type() == mSummands->rhs->type() );
                        if (_rhs->depth() > _lhs->depth()){
                            mDepth = _rhs->depth();
                        } else {
                            mDepth = _lhs->depth();
                        }
                        mOperationCount = _rhs->operationCount() + _lhs->operationCount()+1;
			break;
		}
		case SF_TYPE::UNION: {
			mUnionParameters = new unionContent<Number>( _lhs, _rhs );
			mType = SF_TYPE::UNION;
			mDimension = _lhs->dimension();
                        if (_rhs->depth() > _lhs->depth()){
                            mDepth = _rhs->depth();
                        } else {
                            mDepth = _lhs->depth();
                        }
                        mOperationCount = _rhs->operationCount() + _lhs->operationCount()+1;
			break;
		}
		case SF_TYPE::INTERSECT: {
			mIntersectionParameters = new intersectionContent<Number>( _lhs, _rhs );
			mType = SF_TYPE::INTERSECT;
			mDimension = _lhs->dimension();
                        if (_rhs->depth() > _lhs->depth()){
                            mDepth = _rhs->depth();
                        } else {
                            mDepth = _lhs->depth();
                        }
                        mOperationCount = _rhs->operationCount() + _lhs->operationCount()+1;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, const std::shared_ptr<const lintrafoParameters<Number>>& _parameters
			, SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::LINTRAFO: {
			mLinearTrafoParameters = new trafoContent<Number>( _origin, _parameters );
			mType = SF_TYPE::LINTRAFO;
			mDimension = _origin->dimension();
			mDepth = _origin->depth() +1;
            mOperationCount = _origin->operationCount() + 1;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, const Number &_factor,
										  SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::SCALE: {
			mScaleParameters = new scaleContent<Number>( _origin, _factor );
			mType = SF_TYPE::SCALE;
			mDimension = _origin->dimension();
                        mDepth = _origin->depth() +1; 
                        mOperationCount = _origin->operationCount() + 1;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::~SupportFunctionContent() {
        //std::cout << "Destructor of type " << mType <<  std::endl;
	switch ( mType ) {
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
                case SF_TYPE::ELLIPSOID:
                        delete mEllipsoid;
                        break;
                     // TODO delete ellipsoid
		default:
			break;
	}
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>>& SupportFunctionContent<Number>::operator=(
	  const std::shared_ptr<SupportFunctionContent<Number>>& _other ){
        // std::cout << "SupportFunctionContent Copy\n";
	// std::cout << "Assignment, this->type:" << _other->type() << std::endl;
	mType = _other->type();
	switch ( mType ) {
                case SF_TYPE::ELLIPSOID:
                        mEllipsoid = _other->ellipsoid();
                        break;
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
			assert( false );
	}
	return std::shared_ptr<SupportFunctionContent<Number>>( this->pThis );
}

template <typename Number>
EvaluationResult<Number> SupportFunctionContent<Number>::evaluate( const vector_t<Number> &_direction ) const {
    
	switch ( mType ) {
		case SF_TYPE::ELLIPSOID: {
                        return mEllipsoid->evaluate( _direction );
                }
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			return mBall->evaluate( _direction );
		}
		case SF_TYPE::LINTRAFO: {
			std::pair<matrix_t<Number>, vector_t<Number>> parameterPair = mLinearTrafoParameters->parameters->getParameterSet(mLinearTrafoParameters->currentExponent);
			matrix_t<Number> tmp = parameterPair.first.transpose();
			EvaluationResult<Number> res = mLinearTrafoParameters->origin->evaluate( tmp * _direction );
			switch(res.errorCode){
				case SOLUTION::INFTY:
				case SOLUTION::INFEAS:{
					return res;
				}
				default:{
					assert(res.errorCode == SOLUTION::FEAS);
					res.optimumValue = parameterPair.first * res.optimumValue + parameterPair.second;
					// As we know, that the optimal vertex lies on the supporting Halfspace, we can obtain the distance by dot product.
					res.supportValue = res.optimumValue.dot(_direction);
					return res;
				}
			}
		}
		case SF_TYPE::POLY: {
			return mPolytope->evaluate( _direction );
		}
		case SF_TYPE::SCALE: {
			EvaluationResult<Number> res = mScaleParameters->origin->evaluate( _direction );
			res.optimumValue *= mScaleParameters->factor;
			res.supportValue *= mScaleParameters->factor;
			return res;
		}
		case SF_TYPE::SUM: {
			EvaluationResult<Number> resA = mSummands->lhs->evaluate( _direction );
			if(resA.errorCode == SOLUTION::INFEAS){
				return resA;
			}
			EvaluationResult<Number> resB = mSummands->rhs->evaluate( _direction );
			resA.optimumValue += resB.optimumValue;
			resA.supportValue += resB.supportValue;
			return resA;
		}
		case SF_TYPE::UNION: {
			EvaluationResult<Number> resA = mSummands->lhs->evaluate( _direction );
			EvaluationResult<Number> resB = mSummands->rhs->evaluate( _direction );
			if(resA.errorCode == SOLUTION::INFTY || resB.errorCode == SOLUTION::INFTY){
				EvaluationResult<Number> res;
				res.errorCode = SOLUTION::INFTY;
				res.supportValue = 1;
				res.optimumValue = resA.errorCode == SOLUTION::INFTY ? resA.optimumValue : resB.optimumValue;
				return res;
			}
			if(resA.errorCode == SOLUTION::INFEAS){
				return resB;
			}
			if(resB.errorCode == SOLUTION::INFEAS){
				assert(resA.errorCode == SOLUTION::FEAS);
				return resA;
			}
			assert(resA.errorCode == SOLUTION::FEAS && resB.errorCode == SOLUTION::FEAS);
			return ( resA.supportValue >= resB.supportValue ? resA : resB );
		}
		case SF_TYPE::INTERSECT: {
			// easy checks for infeasibility and unboundedness first
			EvaluationResult<Number> resA = mIntersectionParameters->lhs->evaluate( _direction );
			if(resA.errorCode == SOLUTION::INFEAS){
				return resA;
			}
			EvaluationResult<Number> resB = mIntersectionParameters->rhs->evaluate( _direction );
			if(resB.errorCode == SOLUTION::INFEAS){
				return resB;
			}
			assert(resA.errorCode != SOLUTION::INFEAS && resB.errorCode != SOLUTION::INFEAS);
			if(resA.errorCode == SOLUTION::INFTY){
				return resB;
			}
			if(resB.errorCode == SOLUTION::INFTY){
				return resA;
			}
			// complete checks -> real containment TODO!!
			assert(resA.errorCode == SOLUTION::FEAS && resB.errorCode == SOLUTION::FEAS);
			return ( resA.supportValue <= resB.supportValue ? resA : resB );
		}
		default:{
			assert(false);
			return EvaluationResult<Number>();
		}
	}
}

template <typename Number>
std::vector<EvaluationResult<Number>> SupportFunctionContent<Number>::multiEvaluate( const matrix_t<Number> &_directions ) const {
	//std::cout << "Multi-evaluate, type: " << mType << std::endl;
	switch ( mType ) {
		case SF_TYPE::ELLIPSOID: {
                    return mEllipsoid->multiEvaluate( _directions );
                }
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			return mBall->multiEvaluate( _directions );
		}
		case SF_TYPE::LINTRAFO: {
			// std::cout << "Directions " << convert<Number,double>(_directions) << std::endl << "A:" << convert<Number,double>(mLinearTrafoParameters->a) << std::endl;
			std::pair<matrix_t<Number>, vector_t<Number>> parameterPair = mLinearTrafoParameters->parameters->getParameterSet(mLinearTrafoParameters->currentExponent);
			std::vector<EvaluationResult<Number>> res = mLinearTrafoParameters->origin->multiEvaluate( _directions * parameterPair.first );
			if(res.begin()->errorCode != SOLUTION::INFEAS) {
				unsigned directionCnt = 0;
				for(auto& entry : res){
					vector_t<Number> currentDir = _directions.row(directionCnt);
					entry.optimumValue = parameterPair.first * entry.optimumValue + parameterPair.second;
					// As we know, that the optimal vertex lies on the supporting Halfspace, we can obtain the distance by dot product.
					entry.supportValue = entry.optimumValue.dot(currentDir);
					++directionCnt;
				}
			}
			return res;
		}
		case SF_TYPE::POLY: {
			return mPolytope->multiEvaluate( _directions );
		}
		case SF_TYPE::SCALE: {
			std::vector<EvaluationResult<Number>> res = mScaleParameters->origin->multiEvaluate( _directions );
			// if one result is infeasible, the others will be too -> do not process.
			if(res.begin()->errorCode != SOLUTION::INFEAS){
				for(auto& singleRes : res){
					assert(singleRes.errorCode != SOLUTION::INFEAS);
					if(singleRes.errorCode == SOLUTION::FEAS){
						singleRes.supportValue *= mScaleParameters->factor;
						singleRes.optimumValue *= mScaleParameters->factor;
					}
				}
			}
			return res;
		}
		case SF_TYPE::SUM: {
			std::vector<EvaluationResult<Number>> resA = mSummands->lhs->multiEvaluate( _directions );
			std::vector<EvaluationResult<Number>> resB = mSummands->rhs->multiEvaluate( _directions );
			std::vector<EvaluationResult<Number>> res;
			assert( resA.size() == std::size_t(_directions.rows()));
			assert(resA.size() == resB.size());
			// only process if both are feasible. If one result is infeasible, the others will be too, so stop processing.
			if(resA.begin()->errorCode != SOLUTION::INFEAS && resB.begin()->errorCode != SOLUTION::INFEAS) {
				for(unsigned index = 0; index < resA.size(); ++index){
					assert(resA[index].errorCode != SOLUTION::INFEAS && resB[index].errorCode != SOLUTION::INFEAS);
					EvaluationResult<Number> r;
					if(resA[index].errorCode == SOLUTION::INFTY || resB[index].errorCode == SOLUTION::INFTY){
						r.errorCode = SOLUTION::INFTY;
						r.supportValue = 1;
					} else {
						r.errorCode = SOLUTION::FEAS;
						r.supportValue = resA[index].supportValue + resB[index].supportValue;
						r.optimumValue = resA[index].optimumValue + resB[index].optimumValue;
					}
					res.push_back(r);
				}
			}
			assert( res.size() == std::size_t(_directions.rows()));
			return ( res );
		}
		case SF_TYPE::UNION: {
			std::vector<EvaluationResult<Number>> resA = mUnionParameters->lhs->multiEvaluate( _directions );
			std::vector<EvaluationResult<Number>> resB = mUnionParameters->rhs->multiEvaluate( _directions );
			assert( resA.size() == std::size_t(_directions.rows()));
			assert( resA.size() == resB.size() );
			std::vector<EvaluationResult<Number>> result;
			// in case one of the results is empty, return the other result (if both are empty, this is correct as well).
			if(resA.begin()->errorCode == SOLUTION::INFEAS){
				return resB;
			}
			if(resB.begin()->errorCode == SOLUTION::INFEAS){
				return resA;
			}

			for ( unsigned i = 0; i < resA.size(); ++i ) {
				assert(resA[i].errorCode != SOLUTION::INFEAS && resB[i].errorCode != SOLUTION::INFEAS);
				EvaluationResult<Number> res;
				if(resA[i].errorCode == SOLUTION::INFTY || resB[i].errorCode == SOLUTION::INFTY){
					res.errorCode = SOLUTION::INFTY;
					res.supportValue = 1;
				} else {
					res.errorCode = SOLUTION::FEAS;
					if(resA[i].supportValue > resB[i].supportValue){
						res.supportValue = resA[i].supportValue;
						res.optimumValue = resA[i].optimumValue;
					} else {
						res.supportValue = resB[i].supportValue;
						res.optimumValue = resB[i].optimumValue;
					}
				}
				result.push_back(res);
			}
			assert(result.size() == std::size_t(_directions.rows()));
			return result;
		}
		case SF_TYPE::INTERSECT: {
			std::vector<EvaluationResult<Number>> resA = mIntersectionParameters->lhs->multiEvaluate( _directions );
			std::vector<EvaluationResult<Number>> resB = mIntersectionParameters->rhs->multiEvaluate( _directions );
			assert( resA.size() == resB.size() );
			// in case one of the results is infeasible (the set is empty), return this result.
			if(resA.begin()->errorCode == SOLUTION::INFEAS){
				return resA;
			}
			if(resB.begin()->errorCode == SOLUTION::INFEAS){
				return resB;
			}
			std::vector<EvaluationResult<Number>> result;
 			for ( unsigned i = 0; i < resA.size(); ++i ) {
 				//std::cout << "Eval in direction " << convert<Number,double>(_directions.row(i)).transpose() << std::endl;
				assert(resA[i].errorCode != SOLUTION::INFEAS && resB[i].errorCode != SOLUTION::INFEAS);
				EvaluationResult<Number> res;
				if (resA[i].errorCode == SOLUTION::INFTY) {
					//std::cout << "resA infinite" << std::endl;
					res.errorCode = resB[i].errorCode;
					res.supportValue = resB[i].supportValue;
					res.optimumValue = resB[i].optimumValue;
				} else if (resB[i].errorCode == SOLUTION::INFTY) {
					//std::cout << "resB infinite" << std::endl;
					assert(resA[i].errorCode == SOLUTION::FEAS);
					res.errorCode = resA[i].errorCode;
					res.supportValue = resA[i].supportValue;
					res.optimumValue = resA[i].optimumValue;
				} else {
					assert(resA[i].errorCode == SOLUTION::FEAS && resB[i].errorCode == SOLUTION::FEAS);
					//std::cout << "Both finite: A " << resA[i].supportValue << " vs B " << resB[i].supportValue << std::endl;
					res.errorCode = SOLUTION::FEAS;
					if(resA[i].supportValue < resB[i].supportValue){
						res.supportValue = resA[i].supportValue;
						res.optimumValue = resA[i].optimumValue;
					} else {
						res.supportValue = resB[i].supportValue;
						res.optimumValue = resB[i].optimumValue;
					}
				}
				result.push_back(res);
			}
			assert(result.size() == std::size_t(_directions.rows()));
			return result;
		}
		default:{
			assert(false);
			return std::vector<EvaluationResult<Number>>();
		}
	}
}

template <typename Number>
std::size_t SupportFunctionContent<Number>::dimension() const {
	return mDimension;
}

template <typename Number>
SF_TYPE SupportFunctionContent<Number>::type() const {
	return mType;
}

template <typename Number>
unsigned SupportFunctionContent<Number>::depth() const {
	return mDepth;
}

template <typename Number>
unsigned SupportFunctionContent<Number>::operationCount() const {
	return mOperationCount;
}

template <typename Number>
unsigned SupportFunctionContent<Number>::multiplicationsPerEvaluation() const {
    switch ( mType ) {
        case SF_TYPE::ELLIPSOID: {         
            return 1;
        }             
        case SF_TYPE::INTERSECT: {         
            return (mIntersectionParameters->rhs.get()->multiplicationsPerEvaluation() + mIntersectionParameters->lhs.get()->multiplicationsPerEvaluation());
        }             
        case SF_TYPE::LINTRAFO: {         
            return mLinearTrafoParameters->origin.get()->multiplicationsPerEvaluation() + 1;
        } 
        case SF_TYPE::POLY: {         
            unsigned maxValue = std::max(mPolytope->constraints().rows(), mPolytope->constraints().cols());
            return carl::pow(maxValue,2);
        } 
        case SF_TYPE::SUM: {         
            return (mSummands->lhs.get()->multiplicationsPerEvaluation() + mSummands->rhs.get()->multiplicationsPerEvaluation());
        } 
        case SF_TYPE::UNION: {         
            return (mUnionParameters->rhs.get()->multiplicationsPerEvaluation() + mUnionParameters->lhs.get()->multiplicationsPerEvaluation());
        }
        default:
            return 0;
    }            
}

template <typename Number>
void SupportFunctionContent<Number>::forceLinTransReduction(){
    switch ( mType ) {
        case SF_TYPE::LINTRAFO: {
            std::shared_ptr<SupportFunctionContent<Number>> origin = mLinearTrafoParameters->origin;
            std::pair<matrix_t<Number>, vector_t<Number>> parameterPair = mLinearTrafoParameters->parameters->getParameterSet(mLinearTrafoParameters->currentExponent);
            std::pair<matrix_t<Number>, vector_t<Number>> nextPair;
            while(origin.get()->type() == SF_TYPE::LINTRAFO){
                unsigned currentExponent = origin.get()->linearTrafoParameters()->currentExponent;
                nextPair = origin.get()->linearTrafoParameters()->parameters->getParameterSet(currentExponent);
                parameterPair.second = parameterPair.second + parameterPair.first * nextPair.second + parameterPair.second;
                parameterPair.first = parameterPair.first * nextPair.first;
                origin = origin.get()->linearTrafoParameters()->origin;
            }
            mLinearTrafoParameters = new trafoContent<Number>( origin, std::make_shared<lintrafoParameters<Number>>(parameterPair.first, parameterPair.second) );
        }   break;
        case SF_TYPE::SUM: {
            mSummands->lhs.get()->forceLinTransReduction();
            mSummands->rhs.get()->forceLinTransReduction();
        }   break;
        case SF_TYPE::INTERSECT: {
            mIntersectionParameters->rhs.get()->forceLinTransReduction();
            mIntersectionParameters->lhs.get()->forceLinTransReduction();
        }   break;
        case SF_TYPE::UNION: {
            mUnionParameters->rhs.get()->forceLinTransReduction();
            mUnionParameters->lhs.get()->forceLinTransReduction();
        }   break;
        case SF_TYPE::SCALE: {
            mScaleParameters->origin.get()->forceLinTransReduction();
        }   break;
        default:
            break;
    }
}


template<typename Number>
Point<Number> SupportFunctionContent<Number>::supremumPoint() const {
	switch ( mType ) {
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			return mBall->supremumPoint();
		}
		case SF_TYPE::LINTRAFO: {
			Point<Number> supPoint = mLinearTrafoParameters->origin->supremumPoint();
			if(supPoint.dimension() == 0){
				return supPoint;
			}
			std::pair<matrix_t<Number>, vector_t<Number>> parameterPair = mLinearTrafoParameters->parameters->getParameterSet(mLinearTrafoParameters->currentExponent);
			return supPoint.linearTransformation(parameterPair.first, parameterPair.second);
		}
		case SF_TYPE::POLY: {
			return mPolytope->supremumPoint();
		}
		case SF_TYPE::SCALE: {
			if ( mScaleParameters->factor == 0 ) {
				return Point<Number>::Zero(mDimension);
			} else {
				Point<Number> supPoint = mScaleParameters->origin->supremumPoint();
				if(supPoint.dimension() == 0){
					return supPoint;
				}
				return supPoint* mScaleParameters->factor;
			}
		}
		case SF_TYPE::SUM: {
			Point<Number> lhsPoint = mSummands->lhs->supremumPoint();
			Point<Number> rhsPoint = mSummands->rhs->supremumPoint();
			if(lhsPoint.dimension() == 0) {
				return rhsPoint;
			}
			if(rhsPoint.dimension() == 0) {
				return lhsPoint;
			}
			return lhsPoint+rhsPoint;
		}
		case SF_TYPE::UNION: {
			Point<Number> lhsPoint = mUnionParameters->lhs->supremumPoint();
			Point<Number> rhsPoint = mUnionParameters->rhs->supremumPoint();
			if(lhsPoint.dimension() == 0) {
				return lhsPoint;
			}
			if(rhsPoint.dimension() == 0) {
				return rhsPoint;
			}
			if(Point<Number>::inftyNorm(lhsPoint) > Point<Number>::inftyNorm(rhsPoint)) {
				return lhsPoint;
			}
			return rhsPoint;
		}
		case SF_TYPE::INTERSECT: {
			Point<Number> lhsPoint = mIntersectionParameters->lhs->supremumPoint();
			Point<Number> rhsPoint = mIntersectionParameters->rhs->supremumPoint();
			if(lhsPoint.dimension() == 0) {
				return rhsPoint;
			}
			if(rhsPoint.dimension() == 0) {
				return lhsPoint;
			}
			if(Point<Number>::inftyNorm(lhsPoint) < Point<Number>::inftyNorm(rhsPoint)) {
				return lhsPoint;
			}
			return rhsPoint;
		}
		default:
			assert(false);
			return Point<Number>();
	}
}

template <typename Number>
sumContent<Number> *SupportFunctionContent<Number>::summands() const {
	assert( mType == SF_TYPE::SUM);
	return mSummands;
}

template <typename Number>
trafoContent<Number> *SupportFunctionContent<Number>::linearTrafoParameters() const {
	assert(mType == SF_TYPE::LINTRAFO);
	return mLinearTrafoParameters;
}

template <typename Number>
scaleContent<Number> *SupportFunctionContent<Number>::scaleParameters() const {
	assert( mType == SF_TYPE::SCALE);
	return mScaleParameters;
}

template <typename Number>
unionContent<Number> *SupportFunctionContent<Number>::unionParameters() const {
	assert( mType == SF_TYPE::UNION);
	return mUnionParameters;
}

template <typename Number>
intersectionContent<Number> *SupportFunctionContent<Number>::intersectionParameters() const {
	assert( mType == SF_TYPE::INTERSECT );
	return mIntersectionParameters;
}

template <typename Number>
PolytopeSupportFunction<Number> *SupportFunctionContent<Number>::polytope() const {
	assert( mType == SF_TYPE::POLY );
	return mPolytope;
}

template <typename Number>
EllipsoidSupportFunction<Number> *SupportFunctionContent<Number>::ellipsoid() const {
	assert( mType == SF_TYPE::ELLIPSOID );
	return mEllipsoid;
}

template <typename Number>
BallSupportFunction<Number> *SupportFunctionContent<Number>::ball() const {
	assert( mType == SF_TYPE::INFTY_BALL || mType == SF_TYPE::TWO_BALL);
	return mBall;
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::linearTransformation(
	  const std::shared_ptr<const lintrafoParameters<Number>>& parameters ) const {
	auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(
		  std::shared_ptr<SupportFunctionContent<Number>>( this->pThis ), parameters, SF_TYPE::LINTRAFO ) );
	obj->pThis = obj;
	return obj;
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::minkowskiSum(
	  std::shared_ptr<SupportFunctionContent<Number>> _rhs ) const {
	auto obj = std::shared_ptr<SupportFunctionContent<Number>>(
		  new SupportFunctionContent<Number>( std::shared_ptr<SupportFunctionContent<Number>>( this->pThis ), _rhs, SF_TYPE::SUM ) );
	obj->pThis = obj;
	return obj;
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::intersect(
	  std::shared_ptr<SupportFunctionContent<Number>> _rhs ) const {
	auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(
		  std::shared_ptr<SupportFunctionContent<Number>>( this->pThis ), _rhs, SF_TYPE::INTERSECT ) );
	obj->pThis = obj;
	return obj;
}

template <typename Number>
bool SupportFunctionContent<Number>::contains( const Point<Number> &_point ) const {
	return this->contains( _point.rawCoordinates() );
}

template <typename Number>
bool SupportFunctionContent<Number>::contains( const vector_t<Number> &_point ) const {
	switch ( mType ) {
		case SF_TYPE::ELLIPSOID: {
                        return mEllipsoid->contains( _point );  
                }
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			return mBall->contains( _point );
		}
		case SF_TYPE::LINTRAFO: {
			std::pair<matrix_t<Number>, vector_t<Number>> parameterPair = mLinearTrafoParameters->parameters->getParameterSet(mLinearTrafoParameters->currentExponent);
			return mLinearTrafoParameters->origin->contains( parameterPair.first * _point + parameterPair.second );
		}
		case SF_TYPE::POLY: {
			return mPolytope->contains( _point );
		}
		case SF_TYPE::SCALE: {
			if ( mScaleParameters->factor == 0 )
				return false;
			else
				return mScaleParameters->origin->contains( _point / mScaleParameters->factor );
		}
		case SF_TYPE::SUM: {
			assert(false);
			return false;
		}
		case SF_TYPE::UNION: {
			return (mUnionParameters->rhs->contains(_point) || mUnionParameters->lhs->contains(_point));
		}
		case SF_TYPE::INTERSECT: {
			return (mIntersectionParameters->rhs->contains(_point) && mIntersectionParameters->lhs->contains(_point));
		}
		default:
			assert( false );
			return false;
	}
	return true;
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::unite(
	  std::shared_ptr<SupportFunctionContent<Number>> _rhs ) const {
	auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(
		  std::shared_ptr<SupportFunctionContent<Number>>( this->pThis ), _rhs, SF_TYPE::UNION ) );
	obj->pThis = obj;
	return obj;
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::scale( const Number &_factor ) const {
	auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(
		  std::shared_ptr<SupportFunctionContent<Number>>( this->pThis ), _factor, SF_TYPE::SCALE ) );
	obj->pThis = obj;
	return obj;
}

template <typename Number>
bool SupportFunctionContent<Number>::empty() const {
	switch ( mType ) {
		case SF_TYPE::ELLIPSOID: {
                        return mEllipsoid->empty();
                }
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			return mBall->empty();
		}
		case SF_TYPE::LINTRAFO: {
			return mLinearTrafoParameters->origin.empty();
		}
		case SF_TYPE::POLY: {
			return mPolytope->empty();
		}
		case SF_TYPE::SCALE: {
			if ( mScaleParameters->factor == 0 )
				return true;
			else
				return mScaleParameters->origin.empty();  // Todo: What if factor is negative?
		}
		case SF_TYPE::SUM: {
			return ( mSummands->lhs->empty() && mSummands->rhs->empty() );
		}
		case SF_TYPE::UNION: {
			return ( mUnionParameters->lhs->empty() && mUnionParameters->rhs->empty() );
		}
		case SF_TYPE::INTERSECT: {
			// TODO: Current implementation uses template evaluation.
			std::vector<vector_t<Number>> directions = computeTemplate(this->dimension(), defaultTemplateDirectionCount);
			for(const auto& direction : directions){
				Number rhsPos = mIntersectionParameters->rhs.evaluate(direction);
				Number lhsNeg = mIntersectionParameters->lhs.evaluate(-direction);
				if(rhsPos < -lhsNeg) return true;
				Number rhsNeg = mIntersectionParameters->rhs.evaluate(-direction);
				Number lhsPos = mIntersectionParameters->lhs.evaluate(direction);
				if(-rhsNeg > lhsPos) return true;
			}
			return false;
		}
		default:
			assert( false );
			return false;
	}
}

template <typename Number>
void SupportFunctionContent<Number>::print() const {
	switch ( mType ) {
		case SF_TYPE::ELLIPSOID: {
			std::cout << "ELLIPSOID" << std::endl;
		} break;
		case SF_TYPE::INFTY_BALL: {
			std::cout << "INFTY-BALL" << std::endl;
		} break;
		case SF_TYPE::TWO_BALL: {
			std::cout << "2-BALL" << std::endl;
		} break;
		case SF_TYPE::LINTRAFO: {
			std::cout << "LINTRAFO A^" << mLinearTrafoParameters->currentExponent << std::endl;
			std::cout << "of" << std::endl;
			mLinearTrafoParameters->origin->print();
		} break;
		case SF_TYPE::POLY: {
			std::cout << "POLY" << std::endl;
                        mPolytope->print();
		} break;
		case SF_TYPE::SCALE: {
			std::cout << "SCALE" << std::endl;
		} break;
		case SF_TYPE::SUM: {
			std::cout << "SUM" << std::endl;
			std::cout << "of: " << std::endl;
			mSummands->rhs->print();
			std::cout << "and" << std::endl;
			mSummands->lhs->print();
		} break;
		case SF_TYPE::UNION: {
			std::cout << "UNION" << std::endl;
		} break;
		case SF_TYPE::INTERSECT: {
			std::cout << "INTERSECTION " << std::endl;
			std::cout << "of" << std::endl;
			mIntersectionParameters->lhs->print();
			std::cout << "and" << std::endl;
			mIntersectionParameters->rhs->print();
		} break;
		default:
			std::cout << "NONE" << std::endl;
	}
}

}  // namespace
