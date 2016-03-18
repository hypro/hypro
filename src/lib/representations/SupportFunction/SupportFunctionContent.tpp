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
	: mType( _orig.type() ), mDimension( _orig.dimension() ) {
	// std::cout << "Copy constructor, this->type:" << mType << std::endl;
	switch ( mType ) {
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
SupportFunctionContent<Number>::SupportFunctionContent( Number _radius, SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			mBall = new BallSupportFunction<Number>( _radius, _type );
			mType = _type;
			mDimension = 0;
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
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( const std::vector<Hyperplane<Number>> &_planes, SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::POLY: {
			mPolytope = new PolytopeSupportFunction<Number>( _planes );
			mType = SF_TYPE::POLY;
			mDimension = mPolytope->dimension();
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
			break;
		}
		case SF_TYPE::UNION: {
			mUnionParameters = new unionContent<Number>( _lhs, _rhs );
			mType = SF_TYPE::UNION;
			mDimension = _lhs->dimension();
			break;
		}
		case SF_TYPE::INTERSECT: {
			mIntersectionParameters = new intersectionContent<Number>( _lhs, _rhs );
			mType = SF_TYPE::INTERSECT;
			mDimension = _lhs->dimension();
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
SupportFunctionContent<Number>::SupportFunctionContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, const matrix_t<Number> &_a,
										  const vector_t<Number> &_b, SF_TYPE _type ) {
	switch ( _type ) {
		case SF_TYPE::LINTRAFO: {
			mLinearTrafoParameters = new trafoContent<Number>( _origin, _a, _b );
			mType = SF_TYPE::LINTRAFO;
			mDimension = _origin->dimension();
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
		default:
			assert( false );
	}
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>>& SupportFunctionContent<Number>::operator=(
	  const std::shared_ptr<SupportFunctionContent<Number>>& _other ){
        // std::cout << "SupportFunctionContent Copy\n";
	// std::cout << "Assignment, this->type:" << _other->type() << std::endl;
	mType = _other->type();
	switch ( mType ) {
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
evaluationResult<Number> SupportFunctionContent<Number>::evaluate( const vector_t<Number> &_direction ) const {
	switch ( mType ) {
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			return mBall->evaluate( _direction );
		}
		case SF_TYPE::LINTRAFO: {
			matrix_t<Number> tmp = mLinearTrafoParameters->a.transpose();
			//std::cout << "Tmp rows " << tmp.rows() << " cols " << tmp.cols() << " direction rows: " << _direction.rows() << std::endl;
			evaluationResult<Number> res = mLinearTrafoParameters->origin->evaluate( tmp * _direction );
			if(res.errorCode != SOLUTION::INFTY){
				res.supportValue += ((mLinearTrafoParameters->b).dot(_direction))/norm((_direction));
			}
			return res;
		}
		case SF_TYPE::POLY: {
			return mPolytope->evaluate( _direction );
		}
		case SF_TYPE::SCALE: {
			evaluationResult<Number> res = mScaleParameters->origin->evaluate( _direction );
			res.optimumValue *= mScaleParameters->factor;
			res.supportValue *= mScaleParameters->factor;
			return res;
		}
		case SF_TYPE::SUM: {
			evaluationResult<Number> resA = mSummands->lhs->evaluate( _direction );
			evaluationResult<Number> resB = mSummands->rhs->evaluate( _direction );
			resA.optimumValue += resB.optimumValue;
			resA.supportValue += resB.supportValue;
			return resA;
		}
		case SF_TYPE::UNION: {
			evaluationResult<Number> resA = mSummands->lhs->evaluate( _direction );
			evaluationResult<Number> resB = mSummands->rhs->evaluate( _direction );
			if(resA.errorCode == SOLUTION::INFTY || resB.errorCode == SOLUTION::INFTY){
				evaluationResult<Number> res;
				res.errorCode = SOLUTION::INFTY;
				res.supportValue = 1;
				return res;
			}
			return ( resA.supportValue >= resB.supportValue ? resA : resB );
		}
		case SF_TYPE::INTERSECT: {
			evaluationResult<Number> resA = mIntersectionParameters->lhs->evaluate( _direction );
			evaluationResult<Number> resB = mIntersectionParameters->rhs->evaluate( _direction );
			if(resA.errorCode == SOLUTION::INFTY && resB.errorCode == SOLUTION::INFTY){
				evaluationResult<Number> res;
				res.errorCode = SOLUTION::INFTY;
				res.supportValue = 1;
				return res;
			}
			return ( resA.supportValue <= resB.supportValue ? resA : resB );
		}
	}
}

template <typename Number>
std::vector<evaluationResult<Number>> SupportFunctionContent<Number>::multiEvaluate( const matrix_t<Number> &_directions ) const {
	std::cout << "Multi-evaluate, type: " << mType << std::endl;
	switch ( mType ) {
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			return mBall->multiEvaluate( _directions );
		}
		case SF_TYPE::LINTRAFO: {
			matrix_t<Number> tmp = mLinearTrafoParameters->a.transpose();
			matrix_t<Number> t = _directions * tmp;
			std::cout << "Evaluate in " << convert<Number,double>(t) << std::endl;
			std::vector<evaluationResult<Number>> res = mLinearTrafoParameters->origin->multiEvaluate( _directions * tmp );
			unsigned cnt = 0;
			for(auto& entry : res){
				vector_t<Number> dir = _directions.row(cnt);
				std::cout << "Add translation of " << mLinearTrafoParameters->b << " adds " << carl::toDouble(((mLinearTrafoParameters->b).dot(dir))/norm(dir)) << std::endl;
				entry.supportValue += ((mLinearTrafoParameters->b).dot(dir))/norm(dir);
				++cnt;
			}
			return res;
		}
		case SF_TYPE::POLY: {
			return mPolytope->multiEvaluate( _directions );
		}
		case SF_TYPE::SCALE: {
			std::vector<evaluationResult<Number>> res = mScaleParameters->origin->multiEvaluate( _directions );
			for(auto& singleRes : res)
				singleRes.supportValue *= mScaleParameters->factor;

			return res;
		}
		case SF_TYPE::SUM: {
			std::vector<evaluationResult<Number>> resA = mSummands->lhs->multiEvaluate( _directions );
			std::vector<evaluationResult<Number>> resB = mSummands->rhs->multiEvaluate( _directions );
			std::vector<evaluationResult<Number>> res;
			assert( resA.size() == _directions.rows());
			assert(resA.size() == resB.size());
			for(unsigned index = 0; index < resA.size(); ++index){
				evaluationResult<Number> r;
				if(resA[index].errorCode == SOLUTION::INFTY || resB[index].errorCode == SOLUTION::INFTY){
					r.errorCode = SOLUTION::INFTY;
					r.supportValue = 1;
				} else {
					r.errorCode = SOLUTION::FEAS;
					r.supportValue = resA[index].supportValue + resB[index].supportValue;
				}
				res.push_back(r);
			}
			assert( res.size() == _directions.rows());
			return ( res );
		}
		case SF_TYPE::UNION: {
			std::vector<evaluationResult<Number>> resA = mUnionParameters->lhs->multiEvaluate( _directions );
			std::vector<evaluationResult<Number>> resB = mUnionParameters->rhs->multiEvaluate( _directions );
			assert( resA.size() == _directions.rows());
			assert( resA.size() == resB.size() );
			std::vector<evaluationResult<Number>> result;
			for ( unsigned i = 0; i < resA.size(); ++i ) {
				evaluationResult<Number> res;
				if(resA[i].errorCode == SOLUTION::INFTY || resB[i].errorCode == SOLUTION::INFTY){
					res.errorCode = SOLUTION::INFTY;
					res.supportValue = 1;
				} else {
					res.errorCode = SOLUTION::FEAS;
					res.supportValue = resA[i].supportValue > resB[i].supportValue ? resA[i].supportValue : resB[i].supportValue;
				}
				result.push_back(res);
			}
			assert(result.size() == _directions.rows());
			return result;
		}
		case SF_TYPE::INTERSECT: {
			std::vector<evaluationResult<Number>> resA = mIntersectionParameters->lhs->multiEvaluate( _directions );
			std::vector<evaluationResult<Number>> resB = mIntersectionParameters->rhs->multiEvaluate( _directions );
			assert( resA.size() == resB.size() );
			std::vector<evaluationResult<Number>> result;
			for ( unsigned i = 0; i < resA.size(); ++i ) {
				evaluationResult<Number> res;
				if(resA[i].errorCode == SOLUTION::INFTY && resB[i].errorCode == SOLUTION::INFTY){
					res.errorCode = SOLUTION::INFTY;
					res.supportValue = 1;
				} else if (resA[i].errorCode == SOLUTION::INFTY) {
					res.errorCode = SOLUTION::FEAS;
					res.supportValue = resB[i].supportValue;
				} else if (resB[i].errorCode == SOLUTION::INFTY) {
					res.errorCode = SOLUTION::FEAS;
					res.supportValue = resA[i].supportValue;
				} else {
					res.errorCode = SOLUTION::FEAS;
					res.supportValue = resA[i].supportValue < resB[i].supportValue ? resA[i].supportValue : resB[i].supportValue;
				}
				result.push_back(res);
			}
			assert(result.size() == _directions.rows());
			return result;
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
sumContent<Number> *SupportFunctionContent<Number>::summands() const {
	switch ( mType ) {
		case SF_TYPE::SUM: {
			return mSummands;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
trafoContent<Number> *SupportFunctionContent<Number>::linearTrafoParameters() const {
	switch ( mType ) {
		case SF_TYPE::LINTRAFO: {
			return mLinearTrafoParameters;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
scaleContent<Number> *SupportFunctionContent<Number>::scaleParameters() const {
	switch ( mType ) {
		case SF_TYPE::SCALE: {
			return mScaleParameters;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
unionContent<Number> *SupportFunctionContent<Number>::unionParameters() const {
	switch ( mType ) {
		case SF_TYPE::UNION: {
			return mUnionParameters;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
intersectionContent<Number> *SupportFunctionContent<Number>::intersectionParameters() const {
	switch ( mType ) {
		case SF_TYPE::INTERSECT: {
			return mIntersectionParameters;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
PolytopeSupportFunction<Number> *SupportFunctionContent<Number>::polytope() const {
	switch ( mType ) {
		case SF_TYPE::POLY: {
			return mPolytope;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
BallSupportFunction<Number> *SupportFunctionContent<Number>::ball() const {
	switch ( mType ) {
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			return mBall;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number>
std::shared_ptr<SupportFunctionContent<Number>> SupportFunctionContent<Number>::linearTransformation(
	  const matrix_t<Number> &_A, const vector_t<Number> &_b ) const {
	auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(
		  std::shared_ptr<SupportFunctionContent<Number>>( this->pThis ), _A, _b, SF_TYPE::LINTRAFO ) );
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
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			return mBall->contains( _point );
		}
		case SF_TYPE::LINTRAFO: {
			matrix_t<Number> tmp = mLinearTrafoParameters->a.transpose();
			return mLinearTrafoParameters->origin->contains( tmp * _point );
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
			assert( false );  // Todo: Not implemented yet.
			return false;
		}
		case SF_TYPE::UNION: {
			assert( false );  // Todo: Not implemented yet.
			return false;
		}
		case SF_TYPE::INTERSECT: {
			assert( false );  // Todo: Not implemented yet.
			return false;
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
			std::vector<vector_t<Number>> directions = computeTemplate(this->dimension(), fReach_TEMPLATEDIRECTIONS);
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
		case SF_TYPE::INFTY_BALL: {
			std::cout << "INFTY-BALL" << std::endl;
		} break;
		case SF_TYPE::TWO_BALL: {
			std::cout << "2-BALL" << std::endl;
		} break;
		case SF_TYPE::LINTRAFO: {
			std::cout << "LINTRAFO" << std::endl;
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
