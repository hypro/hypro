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
	//std::cout << "Copy constructor, this->type:" << mType << std::endl;
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
			mPolytope = new PolytopeSupportFunction<Number>(*_orig.polytope());
			break;
		}
		case SF_TYPE::PROJECTION: {
			mProjectionParameters = _orig.projectionParameters();
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
		case SF_TYPE::UNITE: {
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
SupportFunctionContent<Number>::SupportFunctionContent( Number _radius, unsigned dimension, SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			mBall = new BallSupportFunction<Number>( _radius, _type );
			mBall->setDimension(dimension);
			mType = _type;
			mDimension = dimension;
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
SupportFunctionContent<Number>::SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number>>& _lhs,
										  const std::shared_ptr<SupportFunctionContent<Number>>& _rhs, SF_TYPE _type ) {
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
		case SF_TYPE::UNITE: {
			mUnionParameters = new unionContent<Number>( _lhs, _rhs );
			mType = SF_TYPE::UNITE;
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
SupportFunctionContent<Number>::SupportFunctionContent( const std::vector<std::shared_ptr<SupportFunctionContent<Number>>>& _rhs, SF_TYPE _type ) {
	// assert(_lhs.dimension() == _rhs.dimension());
	switch ( _type ) {
		case SF_TYPE::UNITE: {
			assert(!_rhs.empty());
			mUnionParameters = new unionContent<Number>( _rhs );
			mType = SF_TYPE::UNITE;
			mDimension = _rhs.begin()->dimension();
			mDepth = 0;
			mOperationCount = 1;
			for(const auto& sf : _rhs ) {
				assert(sf->dimension() == mDimension);
				if(mDepth < sf->depth()) {
					mDepth = sf->depth();
				}
				mOperationCount += sf->operationCount();
			}
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number>>& _origin, const matrix_t<Number>& A, const vector_t<Number>& b
			, SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::LINTRAFO: {
			mLinearTrafoParameters = new trafoContent<Number>( _origin, A, b );
			mType = SF_TYPE::LINTRAFO;
			mDimension = _origin->dimension();
			mDepth = mLinearTrafoParameters->origin.get()->depth() +1;
            mOperationCount = mLinearTrafoParameters->origin.get()->operationCount() + 1;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number>>& _origin, const Number &_factor,
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

template<typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number>>& _origin, const std::vector<unsigned>& dimensions, SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::PROJECTION: {
			mProjectionParameters = new projectionContent<Number>(_origin,dimensions);
			mType = SF_TYPE::PROJECTION;
			mDimension = _origin->dimension();
			mDepth = _origin->depth() + 1;
			mOperationCount = _origin->operationCount() + 1;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::~SupportFunctionContent() {
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
		case SF_TYPE::PROJECTION:
			delete mProjectionParameters;
			break;
		case SF_TYPE::SCALE:
			delete mScaleParameters;
			break;
		case SF_TYPE::SUM:
			delete mSummands;
			break;
		case SF_TYPE::UNITE:
			delete mUnionParameters;
			break;
		case SF_TYPE::INTERSECT:
			delete mIntersectionParameters;
			break;
		case SF_TYPE::ELLIPSOID:
			delete mEllipsoid;
			break;
		default:
			assert(false);
			break;
	}
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>>& SupportFunctionContent<Number>::operator=(
	  const std::shared_ptr<SupportFunctionContent<Number>>& _other ){
        // std::cout << "SupportFunctionContent Copy\n";
	//std::cout << "Assignment, this->type:" << _other->type() << std::endl;
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
			// explicitly invoke copy constructor to avoid pointer copy
			mPolytope = new PolytopeSupportFunction<Number>(*_other->polytope());
			break;
		case SF_TYPE::PROJECTION:
			mProjectionParameters = _other->projectionParameters();
			break;
		case SF_TYPE::SCALE:
			mScaleParameters = _other->scaleParameters();
			break;
		case SF_TYPE::SUM:
			mSummands = _other->summands();
			break;
		case SF_TYPE::UNITE:
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
EvaluationResult<Number> SupportFunctionContent<Number>::evaluate( const vector_t<Number> &_direction, bool useExact ) const {
	switch ( mType ) {
		case SF_TYPE::ELLIPSOID: {
			return mEllipsoid->evaluate( _direction );
		}
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			return mBall->evaluate( _direction );
		}
		case SF_TYPE::LINTRAFO: {
			TRACE("hypro.representations.supportFunction","Direction rows: " << _direction.rows());
			std::pair<matrix_t<Number>, vector_t<Number>> parameterPair = mLinearTrafoParameters->parameters->getParameterSet(mLinearTrafoParameters->currentExponent);
			#ifndef HYPRO_USE_VECTOR_CACHING
			//matrix_t<Number> tmp = parameterPair.first.transpose();
			//EvaluationResult<Number> res = mLinearTrafoParameters->origin->evaluate( tmp * _direction, useExact);
			EvaluationResult<Number> res = mLinearTrafoParameters->origin->evaluate( mLinearTrafoParameters->parameters->getTransformedDirection(_direction, mLinearTrafoParameters->currentExponent), useExact);
			#else
			EvaluationResult<Number> res = mLinearTrafoParameters->origin->evaluate( mLinearTrafoParameters->parameters->getTransformedDirection(_direction, mLinearTrafoParameters->currentExponent), useExact);
			#endif
			switch(res.errorCode){
				case SOLUTION::INFTY:
				case SOLUTION::INFEAS:{
					return res;
				}
				default:{
					TRACE("hypro.representations.supportFunction","opt val rows: " << res.optimumValue.rows() << " and direction rows: " << _direction.rows());
					assert(res.errorCode == SOLUTION::FEAS);
					assert(res.optimumValue.rows() == _direction.rows());
					res.optimumValue = parameterPair.first * res.optimumValue + parameterPair.second;
					assert(res.optimumValue.rows() == _direction.rows());
					// As we know, that the optimal vertex lies on the supporting hyperplane, we can obtain the distance by dot product.
					res.supportValue = res.optimumValue.dot(_direction);
					return res;
				}
			}
		}
		case SF_TYPE::POLY: {
			return mPolytope->evaluate( _direction, useExact);
		}
		case SF_TYPE::PROJECTION: {
			vector_t<Number> projectedDirection = vector_t<Number>::Zero(mDimension);
			// reduce evaluation to projection dimensions
			for(const auto& projectionDimension : mProjectionParameters->dimensions) {
				if(projectionDimension < mDimension)
					projectedDirection(projectionDimension) = _direction(projectionDimension);
			}
			// in case the result direction is zero (i.e. it has no influence at all) return INFTY.
			if(projectedDirection.nonZeros() == 0) {
				return EvaluationResult<Number>(0,projectedDirection, SOLUTION::INFTY);
			}
			return mProjectionParameters->origin->evaluate(projectedDirection, useExact);
		}
		case SF_TYPE::SCALE: {
			EvaluationResult<Number> res = mScaleParameters->origin->evaluate( _direction, useExact);
			res.optimumValue *= mScaleParameters->factor;
			res.supportValue *= mScaleParameters->factor;
			return res;
		}
		case SF_TYPE::SUM: {
			EvaluationResult<Number> resA = mSummands->lhs->evaluate( _direction, useExact);
			if(resA.errorCode == SOLUTION::INFEAS){
				return resA;
			}
			EvaluationResult<Number> resB = mSummands->rhs->evaluate( _direction, useExact);
			resA.optimumValue += resB.optimumValue;
			resA.supportValue += resB.supportValue;
			return resA;
		}
		case SF_TYPE::UNITE: {
			EvaluationResult<Number> res = (*mUnionParameters->items.begin())->evaluate( _direction, useExact );
			if(res.errorCode == SOLUTION::INFEAS) {
				return res;
			}
			if(res.errorCode == SOLUTION::INFTY) {
				res.supportValue = 1;
				return res;
			}
			for(auto sfIt = (mUnionParameters->items.begin()); sfIt != mUnionParameters->items.end(); ++sfIt) {
				EvaluationResult<Number> tmp = (*sfIt)->evaluate( _direction, useExact );
				if(tmp.errorCode == SOLUTION::INFEAS) {
					return tmp;
				}
				if(tmp.errorCode == SOLUTION::INFTY) {
					tmp.supportValue = 1;
					return tmp;
				}
				res = tmp > res ? tmp : res;
			}
			assert(res.errorCode == SOLUTION::FEAS);
			return ( res );
		}
		case SF_TYPE::INTERSECT: {
			// easy checks for infeasibility and unboundedness first
			EvaluationResult<Number> resA = mIntersectionParameters->lhs->evaluate( _direction, useExact);
			if(resA.errorCode == SOLUTION::INFEAS){
				return resA;
			}
			EvaluationResult<Number> resB = mIntersectionParameters->rhs->evaluate( _direction, useExact);
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
std::vector<EvaluationResult<Number>> SupportFunctionContent<Number>::multiEvaluate( const matrix_t<Number> &_directions, bool useExact ) const {
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
			//std::vector<EvaluationResult<Number>> res = mLinearTrafoParameters->origin->multiEvaluate( _directions * parameterPair.first, useExact );
			assert((_directions * parameterPair.first) == (mLinearTrafoParameters->parameters->getTransformedDirections(_directions, mLinearTrafoParameters->currentExponent)));
			std::vector<EvaluationResult<Number>> res = mLinearTrafoParameters->origin->multiEvaluate( mLinearTrafoParameters->parameters->getTransformedDirections(_directions, mLinearTrafoParameters->currentExponent), useExact );
			if(res.begin()->errorCode != SOLUTION::INFEAS) {
				unsigned directionCnt = 0;
				for(auto& entry : res){
					vector_t<Number> currentDir(_directions.row(directionCnt));
					if(entry.errorCode == SOLUTION::INFTY) {
						entry.optimumValue = entry.optimumValue;
						entry.supportValue = 1;
					} else {
						entry.optimumValue = parameterPair.first * entry.optimumValue + parameterPair.second;
						// As we know, that the optimal vertex lies on the supporting Halfspace, we can obtain the distance by dot product.
						entry.supportValue = entry.optimumValue.dot(currentDir);
					}
					++directionCnt;
					//std::cout << "Entry value: " << entry.supportValue << std::endl;
				}
			}
			return res;
		}
		case SF_TYPE::POLY: {
			return mPolytope->multiEvaluate( _directions, useExact );
		}
		case SF_TYPE::PROJECTION: {
			matrix_t<Number> tmp = matrix_t<Number>::Zero(_directions.rows(), _directions.cols());
			for(const auto& entry : mProjectionParameters->dimensions) {
				if(entry < mDimension)
					tmp.col(entry) = _directions.col(entry);
			}
			return mProjectionParameters->origin->multiEvaluate(tmp, useExact);
		}
		case SF_TYPE::SCALE: {
			std::vector<EvaluationResult<Number>> res = mScaleParameters->origin->multiEvaluate( _directions, useExact );
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
			std::vector<EvaluationResult<Number>> resA = mSummands->lhs->multiEvaluate( _directions, useExact );
			std::vector<EvaluationResult<Number>> resB = mSummands->rhs->multiEvaluate( _directions, useExact );
			std::vector<EvaluationResult<Number>> res;
			assert( resA.size() == std::size_t(_directions.rows()));
			assert(resA.size() == resB.size());
			// only process if both are feasible. If one result is infeasible, the others will be too, so stop processing.
			if(resA.begin()->errorCode != SOLUTION::INFEAS && resB.begin()->errorCode != SOLUTION::INFEAS) {
				for(unsigned index = 0; index < resA.size(); ++index){
					assert(resA.at(index).errorCode != SOLUTION::INFEAS && resB.at(index).errorCode != SOLUTION::INFEAS);
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
				assert( res.size() == std::size_t(_directions.rows()));
			}
			return ( res );
		}
		case SF_TYPE::UNITE: {
			std::vector<EvaluationResult<Number>> res = (*mUnionParameters->items.begin())->multiEvaluate( _directions, useExact );
			for(const auto& result : res ) {
				if(result.errorCode == SOLUTION::INFEAS) {
					return res;
				}
				if(result.errorCode == SOLUTION::INFTY) {
					return res;
				}
			}
			for(auto sfIt = (mUnionParameters->items.begin()); sfIt != mUnionParameters->items.end(); ++sfIt) {
				std::vector<EvaluationResult<Number>> tmp = (*sfIt)->multiEvaluate( _directions, useExact );
				assert(tmp.size() == res.size());
				for( unsigned resultId = 0; resultId < res.size(); ++resultId ) {
					if(tmp[resultId].errorCode == SOLUTION::INFEAS) {
						res[resultId] = tmp[resultId];
						return tmp;
					} else if(tmp[resultId].errorCode == SOLUTION::INFTY) {
						tmp[resultId].supportValue = 1;
						res[resultId] = tmp[resultId];
					} else {
						res[resultId] = tmp[resultId] > res[resultId] ? tmp[resultId] : res[resultId];
						assert(res[resultId].errorCode == SOLUTION::FEAS);
					}
				}
			}
			return ( res );
		}
		case SF_TYPE::INTERSECT: {
			std::vector<EvaluationResult<Number>> resA = mIntersectionParameters->lhs->multiEvaluate( _directions, useExact );
			std::vector<EvaluationResult<Number>> resB = mIntersectionParameters->rhs->multiEvaluate( _directions, useExact );
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
            return carl::pow(maxValue,2)*mPolytope->constraints().cols();
        }
        case SF_TYPE::SUM: {
            return (mSummands->lhs.get()->multiplicationsPerEvaluation() + mSummands->rhs.get()->multiplicationsPerEvaluation());
        }
        case SF_TYPE::UNITE: {
        	unsigned res = 0;
        	for(const auto& item : mUnionParameters->items) {
        		res += item.get()->multiplicationsPerEvaluation();
        	}
        	return res;
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
                //parameterPair.second = parameterPair.second + parameterPair.first * nextPair.second + parameterPair.second;
				parameterPair.second = parameterPair.second + parameterPair.first * nextPair.second;
                parameterPair.first = parameterPair.first * nextPair.first;
                origin = origin.get()->linearTrafoParameters()->origin;
            }
			mDepth = origin.get()->depth() + 1;
			mOperationCount = origin.get()->operationCount() +1;
            mLinearTrafoParameters = new trafoContent<Number>( origin, std::make_shared<lintrafoParameters<Number>>(parameterPair.first, parameterPair.second) );
        }   break;
        case SF_TYPE::SUM: {
            mSummands->lhs.get()->forceLinTransReduction();
            mSummands->rhs.get()->forceLinTransReduction();
			mDepth = std::max(mSummands->lhs.get()->operationCount(), mSummands->rhs.get()->operationCount()) +1;
			mOperationCount = mSummands->lhs.get()->operationCount() + mSummands->rhs.get()->operationCount() +1;
        }   break;
        case SF_TYPE::INTERSECT: {
            mIntersectionParameters->rhs.get()->forceLinTransReduction();
            mIntersectionParameters->lhs.get()->forceLinTransReduction();
			mDepth = std::max(mSummands->lhs.get()->operationCount(), mSummands->rhs.get()->operationCount()) +1;
			mOperationCount = mSummands->lhs.get()->operationCount() + mSummands->rhs.get()->operationCount() +1;
        }   break;
        case SF_TYPE::UNITE: {
        	mOperationCount = 1;
        	for(auto& item : mUnionParameters->items) {
        		item->forceLinTransReduction();
        		mDepth = mDepth > item->depth() ? mDepth : item->depth();
        		mOperationCount += item->operationCount();
        	}
        }   break;
		case SF_TYPE::PROJECTION: {
			mProjectionParameters->origin.get()->forceLinTransReduction();
			mDepth = mProjectionParameters->origin.get()->depth() + 1;
			mOperationCount = mProjectionParameters->origin.get()->operationCount() +1;
			break;
		}
		case SF_TYPE::SCALE: {
            mScaleParameters->origin.get()->forceLinTransReduction();
			mDepth = mScaleParameters->origin.get()->depth() + 1;
			mOperationCount = mScaleParameters->origin.get()->operationCount() +1;
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
			return supPoint.affineTransformation(parameterPair.first, parameterPair.second);
		}
		case SF_TYPE::POLY: {
			return mPolytope->supremumPoint();
		}
		case SF_TYPE::PROJECTION: {
			Point<Number> tmpRes = mProjectionParameters->origin->supremumPoint();
			vector_t<Number> tmp = vector_t<Number>::Zero(mDimension);
			for(const auto& entry : mProjectionParameters->dimensions){
				if(entry < mDimension) {
					tmp(entry) = tmpRes.at(entry);
				}
			}
			return Point<Number>(tmp);
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
		case SF_TYPE::UNITE: {
			Point<Number> resPoint = (*mUnionParameters->items.begin())->supremumPoint();
			if(resPoint.dimension() == 0) {
				return resPoint;
			}
			for(auto itemIt = ++(mUnionParameters->items.begin()); itemIt != mUnionParameters->items.end(); ++itemIt) {
				Point<Number> tmpPoint = (*itemIt)->supremumPoint();
				resPoint = Point<Number>::inftyNorm(resPoint) > Point<Number>::inftyNorm(tmpPoint) ? resPoint : tmpPoint;
			}
			return resPoint;
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

template<typename Number>
std::vector<unsigned> SupportFunctionContent<Number>::collectProjections() const {
	switch ( mType ) {
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL:
		case SF_TYPE::POLY:
		case SF_TYPE::ELLIPSOID: {
			std::vector<unsigned> res;
			DEBUG("hypro.representations.supportFunction","mDimension " << mDimension);
			for(unsigned i = 0; i < mDimension; ++i){
				DEBUG("hypro.representations.supportFunction","Added dimension " << i);
				res.emplace_back(i);
			}
			return res;
		}
		case SF_TYPE::LINTRAFO: {
			return mLinearTrafoParameters->origin->collectProjections();
		}
		case SF_TYPE::PROJECTION: {
			DEBUG("hypro.representations.supportFunction","Projection Object.");
			std::vector<unsigned> tmp = mProjectionParameters->origin->collectProjections();
			std::vector<unsigned> res = mProjectionParameters->dimensions;
			DEBUG("hypro.representations.supportFunction","Projection Object: got " << res.size() << " dimensions.");

			for(auto resIt = res.begin(); resIt != res.end(); ){
				if(std::find(tmp.begin(), tmp.end(), *resIt) == res.end()) {
					DEBUG("hypro.representations.supportFunction","Delete dim " << *resIt);
					resIt = res.erase(resIt);
				} else {
					DEBUG("hypro.representations.supportFunction","Keep dim " << *resIt);
					++resIt;
				}
			}
			return res;
		}
		case SF_TYPE::SCALE: {
			return mScaleParameters->origin->collectProjections();
		}
		case SF_TYPE::SUM: {
			std::vector<unsigned> lhsProjections = mSummands->lhs->collectProjections();
			std::vector<unsigned> rhsProjections = mSummands->rhs->collectProjections();
			std::vector<unsigned> res;
			while(!lhsProjections.empty() && !rhsProjections.empty()){
				if(lhsProjections.front() == rhsProjections.front()){
					res.emplace_back(lhsProjections.front());
					DEBUG("hypro.representations.supportFunction","Sum, add dimension " << res.back());
					lhsProjections.erase(lhsProjections.begin());
					rhsProjections.erase(rhsProjections.begin());
				} else {
					if(lhsProjections.front() < rhsProjections.front()){
						DEBUG("hypro.representations.supportFunction","Sum, dimension " << lhsProjections.front() << " not part in rhs, drop.");
						lhsProjections.erase(lhsProjections.begin());
					} else {
						DEBUG("hypro.representations.supportFunction","Sum, dimension " << rhsProjections.front() << " not part in lhs, drop.");
						rhsProjections.erase(rhsProjections.begin());
					}
				}
			}
			return res;
		}
		case SF_TYPE::UNITE: {
			std::vector<std::vector<unsigned>> projections;
			std::vector<unsigned> res;
			bool allNotEmpty = true;
			for(const auto& set : mUnionParameters->items) {
				projections.push_back(set->collectProjections());
				if(projections.back().empty()) {
					allNotEmpty = false;
				}
			}
			while(allNotEmpty) {
				unsigned frontDimension = projections[0].front();
				bool allHaveFrontDimensionInCommon = true;
				for(const auto& row : projections) {
					if(row.front() != frontDimension ) {
						allHaveFrontDimensionInCommon = false;
					}
				}
				if(allHaveFrontDimensionInCommon) {
					res.push_back(frontDimension);
				}
				// in any case erase all fronts that are equal to the current front dimension
				for(auto& row : projections) {
					if(row.front() == frontDimension ) {
						row.erase(row.begin());
						if(row.empty()){
							allNotEmpty = false;
						}
					}
				}
			}
			return res;
		}
		case SF_TYPE::INTERSECT: {
			std::vector<unsigned> lhsProjections = mIntersectionParameters->lhs->collectProjections();
			std::vector<unsigned> rhsProjections = mIntersectionParameters->rhs->collectProjections();
			std::vector<unsigned> res;
			while(!lhsProjections.empty() && !rhsProjections.empty()){
				if(lhsProjections.front() == rhsProjections.front()){
					res.emplace_back(lhsProjections.front());
					DEBUG("hypro.representations.supportFunction","Intersection, add dimension " << res.back());
					lhsProjections.erase(lhsProjections.begin());
					rhsProjections.erase(rhsProjections.begin());
				} else {
					if(lhsProjections.front() < rhsProjections.front()){
						DEBUG("hypro.representations.supportFunction","Intersection, dimension " << lhsProjections.front() << " not part in rhs, drop.");
						lhsProjections.erase(lhsProjections.begin());
					} else {
						DEBUG("hypro.representations.supportFunction","Intersection, dimension " << rhsProjections.front() << " not part in lhs, drop.");
						rhsProjections.erase(rhsProjections.begin());
					}
				}
			}
			return res;
		}
		default:
			assert(false);
			return std::vector<unsigned>();
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
	assert( mType == SF_TYPE::UNITE);
	return mUnionParameters;
}

template <typename Number>
intersectionContent<Number> *SupportFunctionContent<Number>::intersectionParameters() const {
	assert( mType == SF_TYPE::INTERSECT );
	return mIntersectionParameters;
}

template<typename Number>
projectionContent<Number>* SupportFunctionContent<Number>::projectionParameters() const {
	assert( mType == SF_TYPE::PROJECTION );
	return mProjectionParameters;
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

template<typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::project(const std::vector<unsigned>& dimensions) const {
	auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(
			std::shared_ptr<SupportFunctionContent<Number>>( this->pThis ), dimensions, SF_TYPE::PROJECTION ) );
	obj->pThis = obj;
	DEBUG("hypro.representations.supportFunction","Created ");
	//obj->print();
	return obj;
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::affineTransformation(
	  const matrix_t<Number>& A, const vector_t<Number>& b ) const {
	auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(
		  std::shared_ptr<SupportFunctionContent<Number>>( this->pThis ), A, b, SF_TYPE::LINTRAFO ) );
	obj->pThis = obj;
	return obj;
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::minkowskiSum(
	  const std::shared_ptr<SupportFunctionContent<Number>>& _rhs ) const {
	auto obj = std::shared_ptr<SupportFunctionContent<Number>>(
		  new SupportFunctionContent<Number>( std::shared_ptr<SupportFunctionContent<Number>>( this->pThis ), _rhs, SF_TYPE::SUM ) );
	obj->pThis = obj;
	return obj;
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::intersect(
	  const std::shared_ptr<SupportFunctionContent<Number>>& _rhs ) const {
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
			DEBUG("hypro.representations.supportFunction","ELLIPSOID, point: " << _point);
		    return mEllipsoid->contains( _point );
		}
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			DEBUG("hypro.representations.supportFunction","BALL, point: " << _point);
			return mBall->contains( _point );
		}
		case SF_TYPE::LINTRAFO: {
			// TODO: Verify.
			DEBUG("hypro.representations.supportFunction","TRANSFORMATION, point: " << _point);
			std::pair<matrix_t<Number>, vector_t<Number>> parameterPair = mLinearTrafoParameters->parameters->getParameterSet(mLinearTrafoParameters->currentExponent);
			return mLinearTrafoParameters->origin->contains( (parameterPair.first.transpose() * _point) - parameterPair.second );
		}
		case SF_TYPE::POLY: {
			DEBUG("hypro.representations.supportFunction","POLY, point: " << _point);
			return mPolytope->contains( _point );
		}
		case SF_TYPE::PROJECTION: {
			DEBUG("hypro.representations.supportFunction","PROJECTION, point: " << _point);
			return mProjectionParameters->origin->contains( _point ); // TODO: Correct?
		}
		case SF_TYPE::SCALE: {
			DEBUG("hypro.representations.supportFunction","SCALE, point: " << _point);
			if ( mScaleParameters->factor == 0 )
				return false;
			else
				return mScaleParameters->origin->contains( _point / mScaleParameters->factor );
		}
		case SF_TYPE::SUM: {
			DEBUG("hypro.representations.supportFunction","MINKOWSKI-SUM, point: " << _point);
			// current approach: Use templated evaluation.
			std::vector<vector_t<Number>> templates = computeTemplate<Number>(this->dimension(), defaultTemplateDirectionCount);
			// use single evaluation, as one invalid eval is enough to determine the point is not contained.
			for(const auto& dir : templates) {
				DEBUG("hypro.representations.supportFunction","Evaluate " << dir);
				EvaluationResult<Number> rhsRes =  mSummands->rhs->evaluate(dir, false);
				DEBUG("hypro.representations.supportFunction","Rhsres: " << rhsRes.supportValue);
				EvaluationResult<Number> lhsRes =  mSummands->lhs->evaluate(dir, false);
				DEBUG("hypro.representations.supportFunction","Lhsres: " << lhsRes.supportValue);
				DEBUG("hypro.representations.supportFunction","Summed: " << rhsRes.supportValue + lhsRes.supportValue << " and point dist: " << dir.dot(_point));
				if(dir.dot(_point) > (lhsRes.supportValue + rhsRes.supportValue)) {
					return false;
				}
			}
			return true;
		}
		case SF_TYPE::UNITE: {
			DEBUG("hypro.representations.supportFunction","UNION, point: " << _point);
			for(const auto& set : mUnionParameters->items) {
				if(set->contains(_point)) {
					return true;
				}
			}
			return false;
		}
		case SF_TYPE::INTERSECT: {
			DEBUG("hypro.representations.supportFunction","INTERSECTION, point: " << _point);
			return (mIntersectionParameters->rhs->contains(_point) && mIntersectionParameters->lhs->contains(_point));
		}
		default:
			DEBUG("hypro.representations.supportFunction","UNKNOWN, point: " << _point);
			assert( false );
			return false;
	}
	return true;
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::unite(
	  const std::shared_ptr<SupportFunctionContent<Number>>& _rhs ) const {
	auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(
		  std::shared_ptr<SupportFunctionContent<Number>>( this->pThis ), _rhs, SF_TYPE::UNITE ) );
	obj->pThis = obj;
	return obj;
}

template<typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::unite( const std::vector<std::shared_ptr<SupportFunctionContent<Number>>>& _rhs ) {
	if(!_rhs.empty()) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _rhs, SF_TYPE::UNITE ) );
		obj->pThis = obj;
		return obj;
	}
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
			return mLinearTrafoParameters->origin->empty();
		}
		case SF_TYPE::POLY: {
			return mPolytope->empty();
		}
		case SF_TYPE::PROJECTION: {
			if(mProjectionParameters->dimensions.empty()){
				return true;
			}
			return mProjectionParameters->origin->empty();
		}
		case SF_TYPE::SCALE: {
			if ( mScaleParameters->factor == 0 )
				return true;
			else
				return mScaleParameters->origin->empty();  // Todo: What if factor is negative?
		}
		case SF_TYPE::SUM: {
			return ( mSummands->lhs->empty() && mSummands->rhs->empty() );
		}
		case SF_TYPE::UNITE: {
			for(const auto& item : mUnionParameters->items) {
				if(item->empty()) {
					return true;
				}
			}
			return false;
		}
		case SF_TYPE::INTERSECT: {
			if (mIntersectionParameters->rhs->empty() || mIntersectionParameters->lhs->empty()) {
				return true;
			}
			// TODO: Current implementation uses template evaluation.
			std::vector<vector_t<Number>> directions = computeTemplate<Number>(this->dimension(), defaultTemplateDirectionCount);
			for(const auto& direction : directions){
				Number rhsPos = mIntersectionParameters->rhs->evaluate(direction, false).supportValue;
				Number lhsNeg = mIntersectionParameters->lhs->evaluate(-direction, false).supportValue;
				if(rhsPos < -lhsNeg) return true;
				Number rhsNeg = mIntersectionParameters->rhs->evaluate(-direction, false).supportValue;
				Number lhsPos = mIntersectionParameters->lhs->evaluate(direction, false).supportValue;
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
		case SF_TYPE::PROJECTION: {
			std::cout << "PROJECTION" << std::endl;
			std::cout << "of" << std::endl;
			mProjectionParameters->origin->print();
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
		case SF_TYPE::UNITE: {
			std::cout << "UNITE" << std::endl;
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
