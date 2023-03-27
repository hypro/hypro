/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( const SupportFunctionContent<Number, Setting>& _orig )
	: mType( _orig.type() )
	, mDimension( _orig.dimension() )
	, mDepth( _orig.depth() ) {
	assert( _orig.checkTreeValidity() );

	switch ( mType ) {
		case SF_TYPE::BOX:
			mBox = new BoxSupportFunction<Number, Setting>( _orig.box() );
			break;
		case SF_TYPE::ELLIPSOID:
			mEllipsoid = new EllipsoidSupportFunction<Number>( *_orig.ellipsoid() );
			break;
		case SF_TYPE::INFTY_BALL:
			[[fallthrough]];
		case SF_TYPE::TWO_BALL:
			mBall = new BallSupportFunction<Number>( *_orig.ball() );
			break;
		case SF_TYPE::INTERSECT:
			mIntersectionParameters = new intersectionContent<Number, Setting>( *_orig.intersectionParameters() );
			break;
		case SF_TYPE::LINTRAFO:
			mLinearTrafoParameters = new trafoContent<Number, Setting>( *_orig.linearTrafoParameters() );
			break;
		case SF_TYPE::POLY:
			mPolytope = new PolytopeSupportFunction<Number, Setting>( *_orig.polytope() );
			break;
		case SF_TYPE::PROJECTION:
			mProjectionParameters = new projectionContent<Number, Setting>( *_orig.projectionParameters() );
			break;
		case SF_TYPE::SCALE:
			mScaleParameters = new scaleContent<Number, Setting>( *_orig.scaleParameters() );
			break;
		case SF_TYPE::SUM:
			mSummands = new sumContent<Number, Setting>( *_orig.summands() );
			break;
		case SF_TYPE::UNITE:
			mUnionParameters = new unionContent<Number, Setting>( *_orig.unionParameters() );
			break;
		case SF_TYPE::NONE: {
			std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
			assert( false );
			break;
		}
		default:
			assert( false );
	}
	assert( checkTreeValidity() );
}
/*
template<typename Number, typename Setting>
template<typename FromSetting, carl::DisableIf< std::is_same<Setting,FromSetting> > >
SupportFunctionContent<Number,Setting>::SupportFunctionContent( const SupportFunctionContent<Number,FromSetting>& _orig )
	: mType( _orig.type() ), mDimension( _orig.dimension()), mDepth( _orig.depth()) {
	assert(_orig.checkTreeValidity());

	switch ( mType ) {
		case SF_TYPE::BOX: {
			mBox = new BoxSupportFunction<Number,Setting>(_orig.box().vertices());
		}
		case SF_TYPE::ELLIPSOID: {
			mEllipsoid = new EllipsoidSupportFunction<Number>(_orig.ellipsoid()->shapeMatrix());
			break;
		}
		case SF_TYPE::INFTY_BALL:
		case SF_TYPE::TWO_BALL: {
			mBall = new BallSupportFunction<Number>(_orig.ball()->radius(), _orig.ball()->type());
			break;
		}
		case SF_TYPE::INTERSECT: {
			mIntersectionParameters = new intersectionContent<Number,Setting>(*_orig.intersectionParameters());
			break;
		}
		case SF_TYPE::LINTRAFO: {
			mLinearTrafoParameters = new trafoContent<Number,Setting>(*_orig.linearTrafoParameters());
			break;
		}
		case SF_TYPE::POLY: {
			mPolytope = new PolytopeSupportFunction<Number,Setting>(*_orig.polytope());
			break;
		}
		case SF_TYPE::PROJECTION: {
			mProjectionParameters = new projectionContent<Number,Setting>(*_orig.projectionParameters());
			break;
		}
		case SF_TYPE::SCALE: {
			mScaleParameters = new scaleContent<Number,Setting>(*_orig.scaleParameters());
			break;
		}
		case SF_TYPE::SUM: {
			mSummands = new sumContent<Number,Setting>(*_orig.summands());
			break;
		}
		case SF_TYPE::UNITE: {
			mUnionParameters = new unionContent<Number,Setting>(*_orig.unionParameters());
			break;
		}
		case SF_TYPE::NONE: {
			std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
			assert(false);
			break;
		}
		default:
			assert( false );
	}
	assert(checkTreeValidity());
}
*/

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( const matrix_t<Number>& _shapeMatrix, SF_TYPE _type )
	: mDimension( _shapeMatrix.cols() ) {
	if ( _type == SF_TYPE::ELLIPSOID ) {
		mEllipsoid = new EllipsoidSupportFunction<Number>( _shapeMatrix );
		mType = SF_TYPE::ELLIPSOID;
	} else {
		assert( false );
	}
}

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( Number _radius, unsigned dimension, SF_TYPE _type )
	: mDimension( dimension ) {
	switch ( _type ) {
		case SF_TYPE::INFTY_BALL:
			[[fallthrough]];
		case SF_TYPE::TWO_BALL: {
			mBall = new BallSupportFunction<Number>( _radius, _type );
			mType = _type;
			ball()->setDimension( dimension );
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( const matrix_t<Number>& _directions, const vector_t<Number>& _distances, SF_TYPE _type, bool overrideReduction )
	: mDimension( _directions.cols() ) {
	switch ( _type ) {
		case SF_TYPE::POLY: {
			if ( !overrideReduction ) {
				std::tuple<bool, std::vector<carl::Interval<Number>>> intervals;
				if ( Setting::DETECT_BOX ) {
					intervals = isBox( _directions, _distances );
				}
				if ( std::get<0>( intervals ) ) {
					// TRACE("hypro.representations.supportFunction","Handed polytope actually is a box, use box representation.")
					mBox = new BoxSupportFunction<Number, Setting>( std::get<1>( intervals ) );
					mType = SF_TYPE::BOX;
				} else {
					// TRACE("hypro.representations.supportFunction","Handed polytope indeed is a polytope, use H-representation.")
					mPolytope = new PolytopeSupportFunction<Number, Setting>( _directions, _distances );
					mType = SF_TYPE::POLY;
				}
			} else {
				mPolytope = new PolytopeSupportFunction<Number, Setting>( _directions, _distances );
				mType = SF_TYPE::POLY;
			}
			break;
		}
		case SF_TYPE::BOX: {
			std::tuple<bool, std::vector<carl::Interval<Number>>> intervals;
			if ( Setting::DETECT_BOX ) {
				intervals = isBox( _directions, _distances );
			}
			if ( std::get<0>( intervals ) ) {
				// TRACE("hypro.representations.supportFunction","Handed box indeed is a box.")
				mBox = new BoxSupportFunction<Number, Setting>( std::get<1>( intervals ) );
				mType = SF_TYPE::BOX;
			} else {
				// TRACE("hypro.representations.supportFunction","Handed box actually is a polytope, use H-representation.")
				mPolytope = new PolytopeSupportFunction<Number, Setting>( _directions, _distances );
				mType = SF_TYPE::POLY;
			}
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( const std::vector<Halfspace<Number>>& _planes, SF_TYPE _type ) {
	if ( _type == SF_TYPE::POLY ) {
		mPolytope = new PolytopeSupportFunction<Number, Setting>( _planes );
		mType = SF_TYPE::POLY;
		mDimension = polytope()->dimension();
	} else {
		assert( false );
	}
}

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( const std::vector<Point<Number>>& _points, SF_TYPE _type ) {
	if ( _type == SF_TYPE::POLY ) {
		mPolytope = new PolytopeSupportFunction<Number, Setting>( _points );
		mType = SF_TYPE::POLY;
		mDimension = polytope()->dimension();
	} else {
		assert( false );
	}
}

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( const std::vector<carl::Interval<Number>>& _inbox, SF_TYPE _type )
	: mDimension( _inbox.size() ) {
	if ( _type == SF_TYPE::BOX ) {
		mBox = new BoxSupportFunction<Number, Setting>( _inbox );
		mType = SF_TYPE::BOX;
	} else {
		assert( false );
	}
}

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number, Setting>>& _lhs,
																 const std::shared_ptr<SupportFunctionContent<Number, Setting>>& _rhs, SF_TYPE _type )
	: mDimension( _lhs->dimension() )
	, mOperationCount( _rhs->operationCount() + _lhs->operationCount() + 1 )
	, mDepth( std::max( _lhs->depth(), _rhs->depth() ) ) {
	assert( _lhs->checkTreeValidity() );
	assert( _rhs->checkTreeValidity() );
	switch ( _type ) {
		case SF_TYPE::SUM: {
			mSummands = new sumContent<Number, Setting>( _lhs, _rhs );
			mType = SF_TYPE::SUM;
			assert( _lhs->type() == summands()->lhs->type() && _rhs->type() == summands()->rhs->type() );
			break;
		}
		case SF_TYPE::UNITE: {
			mUnionParameters = new unionContent<Number, Setting>( _lhs, _rhs );
			mType = SF_TYPE::UNITE;
			break;
		}
		case SF_TYPE::INTERSECT: {
			mIntersectionParameters = new intersectionContent<Number, Setting>( _lhs, _rhs );
			mType = SF_TYPE::INTERSECT;
			break;
		}
		default:
			assert( false );
	}
}

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( const std::vector<std::shared_ptr<SupportFunctionContent<Number, Setting>>>& rhs, SF_TYPE type )
	: mDimension( rhs.begin()->dimension() )
	, mDepth( 0 )
	, mOperationCount( 1 ) {
	assert( rhs->checkTreeValidity() );
	if ( type == SF_TYPE::UNITE ) {
		assert( !rhs.empty() );
		mUnionParameters = new unionContent<Number, Setting>( rhs );
		mType = SF_TYPE::UNITE;
		for ( const auto& sf : rhs ) {
			assert( sf->checkTreeValidity() );
			assert( sf->dimension() == mDimension );
			if ( mDepth < sf->depth() ) {
				mDepth = sf->depth();
			}
			mOperationCount += sf->operationCount();
		}
	} else {
		assert( false );
	}
}

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number, Setting>>& _origin, const matrix_t<Number>& A, const vector_t<Number>& b, SF_TYPE _type )
	: mDimension( _origin->dimension() )
	, mDepth( _origin->depth() + 1 )
	, mOperationCount( _origin->operationCount() + 1 ) {
	assert( _origin->checkTreeValidity() );
	if ( _type == SF_TYPE::LINTRAFO ) {
		mLinearTrafoParameters = new trafoContent<Number, Setting>( _origin, A, b );
		mType = SF_TYPE::LINTRAFO;
	} else {
		assert( false );
	}
}

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number, Setting>>& _origin, const Number& _factor,
																 SF_TYPE _type )
	: mDimension( _origin->dimension() )
	, mDepth( _origin->depth() + 1 )
	, mOperationCount( _origin->operationCount() + 1 ) {
	assert( _origin->checkTreeValidity() );
	if ( _type == SF_TYPE::SCALE ) {
		mScaleParameters = new scaleContent<Number, Setting>( _origin, _factor );
		mType = SF_TYPE::SCALE;
	} else {
		assert( false );
	}
}

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number, Setting>>& _origin, const std::vector<std::size_t>& dimensions, SF_TYPE _type )
	: mDimension( _origin->dimension() )
	, mDepth( _origin->depth() + 1 )
	, mOperationCount( _origin->operationCount() + 1 ) {
	assert( _origin->checkTreeValidity() );
	if ( _type == SF_TYPE::PROJECTION ) {
		mProjectionParameters = new projectionContent<Number, Setting>( _origin, dimensions );
		mType = SF_TYPE::PROJECTION;
	} else {
		assert( false );
	}
}

template <typename Number, typename Setting>
SupportFunctionContent<Number, Setting>::~SupportFunctionContent() {
	switch ( mType ) {
		case SF_TYPE::INFTY_BALL:
			[[fallthrough]];
		case SF_TYPE::TWO_BALL:
			delete mBall;
			break;
		case SF_TYPE::LINTRAFO:
			delete linearTrafoParameters();
			break;
		case SF_TYPE::POLY:
			delete mPolytope;
			break;
		case SF_TYPE::BOX:
			delete mBox;
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
			delete ellipsoid();
			break;
		case SF_TYPE::NONE: {
			std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
			assert( false );
			break;
		}
		default:
			assert( false );
			break;
	}
}

template <typename Number, typename Setting>
std::shared_ptr<SupportFunctionContent<Number, Setting>>& SupportFunctionContent<Number, Setting>::operator=(
	  const std::shared_ptr<SupportFunctionContent<Number, Setting>>& _other ) {
	assert( _other->checkTreeValidity() );
	mType = _other->type();
	switch ( mType ) {
		case SF_TYPE::ELLIPSOID:
			mEllipsoid = new EllipsoidSupportFunction<Number>( *_other->ellipsoid() );
			break;
		case SF_TYPE::INFTY_BALL:
			[[fallthrough]];
		case SF_TYPE::TWO_BALL:
			mBall = new BallSupportFunction<Number>( *_other->ball() );
			break;
		case SF_TYPE::LINTRAFO:
			mLinearTrafoParameters = new trafoContent<Number, Setting>( *_other->linearTrafoParameters() );
			break;
		case SF_TYPE::POLY:
			// explicitly invoke copy constructor to avoid pointer copy
			mPolytope = new PolytopeSupportFunction<Number, Setting>( *_other->polytope() );
			break;
		case SF_TYPE::BOX:
			// explicitly invoke copy constructor to avoid pointer copy
			mBox = new BoxSupportFunction<Number, Setting>( *_other->polytope() );
			break;
		case SF_TYPE::PROJECTION:
			mProjectionParameters = new projectionContent<Number, Setting>( *_other->projectionParameters() );
			break;
		case SF_TYPE::SCALE:
			mScaleParameters = new scaleContent<Number, Setting>( *_other->scaleParameters() );
			break;
		case SF_TYPE::SUM:
			mSummands = new sumContent<Number, Setting>( *_other->summands() );
			break;
		case SF_TYPE::UNITE:
			mUnionParameters = new unionContent<Number, Setting>( *_other->unionParameters() );
			break;
		case SF_TYPE::INTERSECT:
			mIntersectionParameters = new intersectionContent<Number, Setting>( *_other->intersectionParameters() );
			break;
		case SF_TYPE::NONE: {
			std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
			assert( false );
			break;
		}
		default:
			assert( false );
	}
	assert( checkTreeValidity() );
	return std::shared_ptr<SupportFunctionContent<Number, Setting>>( this->pThis );
}

template <typename Number, typename Setting>
EvaluationResult<Number> SupportFunctionContent<Number, Setting>::evaluate( const vector_t<Number>& _direction, bool useExact ) const {
	matrix_t<Number> tmp = matrix_t<Number>::Zero( 1, _direction.rows() );
	tmp << _direction.transpose();
	auto res = multiEvaluate( tmp, useExact );
	assert( res.size() == 1 );
	// TRACE("hypro.representations.supportFunction","Return result.");
	return res.at( 0 );
}

template <typename Number, typename Setting>
std::vector<EvaluationResult<Number>> SupportFunctionContent<Number, Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
	assert( checkTreeValidity() );

	using Node = std::shared_ptr<SupportFunctionContent<Number, Setting>>;
	using Param = matrix_t<Number>;
	using Res = std::vector<EvaluationResult<Number>>;

	std::vector<Node> callStack;
	std::vector<Param> paramStack;
	std::vector<std::pair<int, std::vector<Res>>> resultStack;	// The first value is an iterator to the calling frame

	callStack.push_back( getThis() );
	paramStack.push_back( _directions );
	resultStack.push_back( std::make_pair( -1, std::vector<Res>() ) );

	while ( !callStack.empty() ) {
		Node cur = callStack.back();
		Param currentParam = paramStack.back();

		if ( cur->originCount() == 0 ) {
			// Do computation and write results in case recursion ends.

			std::pair<int, std::vector<Res>> currentResult = resultStack.back();

			// update result
			// special case: When the node is a leaf, we directly return the result.
			if ( currentResult.first == -1 ) {
				// we reached the top, exit (or return result or whatever)
				// TRACE("hypro.representations.supportFunction","Is leaf. Evaluate and return.");
				switch ( cur->type() ) {
					case SF_TYPE::ELLIPSOID:
						return ellipsoid()->multiEvaluate( currentParam );
					case SF_TYPE::INFTY_BALL:
						[[fallthrough]];
					case SF_TYPE::TWO_BALL:
						return ball()->multiEvaluate( currentParam );
					case SF_TYPE::POLY:
						return polytope()->multiEvaluate( currentParam, useExact );
					case SF_TYPE::BOX:
						return box()->multiEvaluate( currentParam, useExact );
					default:
						assert( false );
						FATAL( "hypro.representations.supportFunction", "Wrong type." );
				}
			} else {
				// TRACE("hypro.representations.supportFunction","Evaluate and add to results stack.");
				switch ( cur->type() ) {
					case SF_TYPE::ELLIPSOID:
						resultStack.at( currentResult.first ).second.emplace_back( cur->ellipsoid()->multiEvaluate( currentParam ) );
						break;
					case SF_TYPE::INFTY_BALL:
						[[fallthrough]];
					case SF_TYPE::TWO_BALL:
						resultStack.at( currentResult.first ).second.emplace_back( cur->ball()->multiEvaluate( currentParam ) );
						break;
					case SF_TYPE::POLY:
						resultStack.at( currentResult.first ).second.emplace_back( cur->polytope()->multiEvaluate( currentParam, useExact ) );
						break;
					case SF_TYPE::BOX:
						resultStack.at( currentResult.first ).second.emplace_back( cur->box()->multiEvaluate( currentParam, useExact ) );
						break;
					default:
						assert( false );
						FATAL( "hypro.representations.supportFunction", "Wrong type." );
				}
			}
			// TRACE("hypro.representations.supportFunction","Leave recursive call.");

			// leave recursive call.
			callStack.pop_back();
			paramStack.pop_back();
			resultStack.pop_back();

		} else {
			// Detect, if this call is finished or new.
			if ( resultStack.back().second.size() == cur->originCount() ) {
				// the call is finished, perform accumulating operations and forward result.
				// TRACE("hypro.representations.supportFunction", ": Accumulate results.");
				// accumulate results - in this case sum.
				Res accumulatedResult;
				switch ( cur->type() ) {
					case SF_TYPE::LINTRAFO: {
						// TRACE("hypro.representations.supportFunction", ": LINTRAFO, accumulate results.")
						assert( resultStack.back().second.size() == 1 );
						const std::pair<matrix_t<Number>, vector_t<Number>>& parameterPair = cur->linearTrafoParameters()->parameters->getParameterSet( cur->linearTrafoParameters()->currentExponent );
						// TRACE("hypro.representations.supportFunction", "Matrix: " << parameterPair.first);
						// TRACE("hypro.representations.supportFunction", "Vector: " << parameterPair.second);
						if ( resultStack.back().second.front().begin()->errorCode != SOLUTION::INFEAS ) {
							unsigned directionCnt = 0;
							for ( auto& entry : resultStack.back().second.front() ) {
								vector_t<Number> currentDir( currentParam.row( directionCnt ) );
								if ( entry.errorCode == SOLUTION::INFTY ) {
									entry.supportValue = 1;
								} else {
									// TRACE("hypro.representations.supportFunction", ": Entry val before trafo: " << entry.optimumValue);
									entry.optimumValue = parameterPair.first * entry.optimumValue + parameterPair.second;
									// As we know, that the optimal vertex lies on the supporting Halfspace, we can obtain the distance by dot product.
									entry.supportValue = entry.optimumValue.dot( currentDir );
								}
								// auto t = convert<Number,double>(currentParam.row(directionCnt));
								////TRACE("hypro.representations.supportFunction", "Direction: " << t << ", Entry value: " << entry.supportValue);
								++directionCnt;
							}
						}
						// TRACE("hypro.representations.supportFunction",": LINTRAFO, accumulate results done.");
						accumulatedResult = resultStack.back().second.front();
						assert( !accumulatedResult.empty() );
						break;
					}
					case SF_TYPE::PROJECTION: {
						// TRACE("hypro.representations.supportFunction", ": PROJECTION, accumulate results.")
						assert( resultStack.back().second.size() == 1 );
						// simply forward the results
						accumulatedResult = resultStack.back().second.front();
						assert( !accumulatedResult.empty() );
						break;
					}
					case SF_TYPE::SCALE: {
						// TRACE("hypro.representations.supportFunction", ": SCALE, accumulate results.")
						assert( resultStack.back().second.size() == 1 );
						// if one result is infeasible, the others will be too -> do not process.
						if ( resultStack.back().second.front().begin()->errorCode != SOLUTION::INFEAS ) {
							for ( auto& singleRes : resultStack.back().second.front() ) {
								assert( singleRes.errorCode != SOLUTION::INFEAS );
								if ( singleRes.errorCode == SOLUTION::FEAS ) {
									singleRes.supportValue *= cur->scaleParameters()->factor;
									singleRes.optimumValue *= cur->scaleParameters()->factor;
								}
							}
						}
						accumulatedResult = resultStack.back().second.front();
						assert( !accumulatedResult.empty() );
						break;
					}
					case SF_TYPE::SUM: {
						// TRACE("hypro.representations.supportFunction", ": SUM, accumulate results.")
						assert( resultStack.back().second.size() == 2 );
						assert( resultStack.back().second.at( 0 ).size() == std::size_t( currentParam.rows() ) );
						assert( resultStack.back().second.at( 0 ).size() == resultStack.back().second.at( 1 ).size() );
						Res& resA = resultStack.back().second.at( 0 );
						Res& resB = resultStack.back().second.at( 1 );

						// only process if both are feasible. If one result is infeasible, the others will be too, so stop processing.
						if ( resA.begin()->errorCode != SOLUTION::INFEAS && resB.begin()->errorCode != SOLUTION::INFEAS ) {
							for ( unsigned index = 0; index < resA.size(); ++index ) {
								assert( resA.at( index ).errorCode != SOLUTION::INFEAS && resB.at( index ).errorCode != SOLUTION::INFEAS );
								EvaluationResult<Number> r;
								if ( resA[index].errorCode == SOLUTION::INFTY || resB[index].errorCode == SOLUTION::INFTY ) {
									r.errorCode = SOLUTION::INFTY;
									r.supportValue = 1;
								} else {
									r.errorCode = SOLUTION::FEAS;
									r.supportValue = resA[index].supportValue + resB[index].supportValue;
									r.optimumValue = resA[index].optimumValue + resB[index].optimumValue;
								}
								accumulatedResult.emplace_back( r );
							}
							assert( accumulatedResult.size() == std::size_t( currentParam.rows() ) );
							assert( !accumulatedResult.empty() );
						} else {
							accumulatedResult.emplace_back( EvaluationResult<Number>{} );
						}
						assert( !accumulatedResult.empty() );
						break;
					}
					case SF_TYPE::UNITE: {
						// TRACE("hypro.representations.supportFunction", ": UNITE, accumulate results.")
						assert( resultStack.back().second.size() > 0 );
						assert( resultStack.back().second.size() == cur->unionParameters()->items.size() );
						accumulatedResult = resultStack.back().second.front();
						for ( auto resIt = resultStack.back().second.begin(); resIt != resultStack.back().second.end(); ++resIt ) {
							for ( unsigned resultId = 0; resultId < accumulatedResult.size(); ++resultId ) {
								if ( ( *resIt )[resultId].errorCode == SOLUTION::INFEAS ) {
									accumulatedResult[resultId] = ( *resIt )[resultId];
									break;
								} else if ( ( *resIt )[resultId].errorCode == SOLUTION::INFTY ) {
									( *resIt )[resultId].supportValue = 1;
									accumulatedResult[resultId] = ( *resIt )[resultId];
								} else {
									assert( ( *resIt )[resultId].errorCode == SOLUTION::FEAS );
									accumulatedResult[resultId] = ( *resIt )[resultId] > accumulatedResult[resultId] ? ( *resIt )[resultId] : accumulatedResult[resultId];
									// assert(accumulatedResult[resultId].errorCode == SOLUTION::FEAS);
								}
							}
						}
						assert( !accumulatedResult.empty() );
						break;
					}
					case SF_TYPE::INTERSECT: {
						// TRACE("hypro.representations.supportFunction", ": INTERSECT, accumulate results.")
						assert( resultStack.back().second.size() == 2 );
						Res& resA = resultStack.back().second[0];
						Res& resB = resultStack.back().second[1];
						assert( resA.size() == resB.size() );
						// in case one of the results is infeasible (the set is empty), return this result.
						if ( resA.begin()->errorCode == SOLUTION::INFEAS ) {
							accumulatedResult = std::move( resA );
							assert( !accumulatedResult.empty() );
							break;
						}
						if ( resB.begin()->errorCode == SOLUTION::INFEAS ) {
							accumulatedResult = std::move( resB );
							assert( !accumulatedResult.empty() );
							break;
						}
						for ( unsigned i = 0; i < resA.size(); ++i ) {
							EvaluationResult<Number> res;
							// intersection with the empty set is the empty set -> skip further computation
							if ( resA[i].errorCode != SOLUTION::INFEAS && resB[i].errorCode != SOLUTION::INFEAS ) {
								if ( resA[i].errorCode == SOLUTION::INFTY ) {
									// TRACE("hypro.representations.supportFunction","resA infinite");
									res.errorCode = resB[i].errorCode;
									res.supportValue = resB[i].supportValue;
									res.optimumValue = resB[i].optimumValue;
								} else if ( resB[i].errorCode == SOLUTION::INFTY ) {
									// TRACE("hypro.representations.supportFunction","resB infinite");
									assert( resA[i].errorCode == SOLUTION::FEAS );
									res.errorCode = resA[i].errorCode;
									res.supportValue = resA[i].supportValue;
									res.optimumValue = resA[i].optimumValue;
								} else {
									assert( resA[i].errorCode == SOLUTION::FEAS && resB[i].errorCode == SOLUTION::FEAS );
									// TRACE("hypro.representations.supportFunction","Both finite: A " << resA[i].supportValue << " vs B " << resB[i].supportValue);
									res.errorCode = SOLUTION::FEAS;
									if ( resA[i].supportValue < resB[i].supportValue ) {
										res.supportValue = resA[i].supportValue;
										res.optimumValue = resA[i].optimumValue;
									} else {
										res.supportValue = resB[i].supportValue;
										res.optimumValue = resB[i].optimumValue;
									}
								}
							}

							// auto t = convert<Number,double>(res.optimumValue);
							////TRACE("hypro.representations.supportFunction", ": INTERSECT, accumulated result: " << t << " and value: " << res.supportValue );
							accumulatedResult.emplace_back( std::move( res ) );
						}
						assert( accumulatedResult.size() == std::size_t( currentParam.rows() ) );
						assert( !accumulatedResult.empty() );
						break;
					}
					case SF_TYPE::NONE: {
						std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
						assert( false );
						break;
					}
					default: {
						assert( false );
						return std::vector<EvaluationResult<Number>>();
					}
				}

				if ( resultStack.back().first == -1 ) {
					// we reached the top, exit
					// TRACE("hypro.representations.supportFunction","Return accumulated result.");
					assert( !accumulatedResult.empty() );
					return accumulatedResult;
				}

				// forward result.
				////TRACE("hypro.representations.supportFunction","Push accumulated result up.");
				// resultStack.at(resultStack.back().first).second.emplace_back(accumulatedResult);
				assert( !accumulatedResult.empty() );
				resultStack.at( resultStack.back().first ).second.emplace_back( std::move( accumulatedResult ) );

				// delete result frame and close recursive call
				callStack.pop_back();
				paramStack.pop_back();
				resultStack.pop_back();

			} else {
				// this is the branch for calling recursively
				// TRACE("hypro.representations.supportFunction","Invoke recursive call.");

				// here we create the new stack levels.
				std::size_t callingFrame = callStack.size() - 1;

				// Do some parameter transformation, i.e. create passed parameters
				switch ( cur->type() ) {
					case SF_TYPE::ELLIPSOID:
						[[fallthrough]];
					case SF_TYPE::INFTY_BALL:
						[[fallthrough]];
					case SF_TYPE::POLY:
						[[fallthrough]];
					case SF_TYPE::BOX:
						[[fallthrough]];
					case SF_TYPE::TWO_BALL:
						assert( false );
						FATAL( "hypro.representations.supportFunction", "Leaf node cannot be an intermediate case." );
						break;
					case SF_TYPE::LINTRAFO: {
						callStack.push_back( cur->linearTrafoParameters()->origin );
#ifndef HYPRO_USE_VECTOR_CACHING
						paramStack.push_back( currentParam * cur->linearTrafoParameters()->parameters->getParameterSet( cur->linearTrafoParameters()->currentExponent ).first );
#else
						paramStack.push_back( cur->linearTrafoParameters()->parameters->getTransformedDirections( currentParam, cur->linearTrafoParameters()->currentExponent ) );
#endif
						resultStack.emplace_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					}
					case SF_TYPE::PROJECTION: {
						matrix_t<Number> projectedParameters = matrix_t<Number>::Zero( _directions.rows(), _directions.cols() );
						Eigen::Index entryIndex = 0;
						for ( const auto& entry : cur->projectionParameters()->dimensions ) {
							// TRACE("hypro.representations.supportFunction","Entry: " << entry)
							if ( entry < mDimension ) {
								projectedParameters.col( entry ) = currentParam.col( entry );
								++entryIndex;
							}
						}
						assert( entryIndex == Eigen::Index( cur->projectionParameters()->dimensions.size() ) );
						callStack.push_back( cur->projectionParameters()->origin );
						paramStack.emplace_back( projectedParameters );
						resultStack.emplace_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					}
					case SF_TYPE::SCALE: {
						// Do nothing for scaling -> processing is done afterwards.
						callStack.push_back( cur->scaleParameters()->origin );
						paramStack.emplace_back( currentParam );
						resultStack.emplace_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					}
					case SF_TYPE::SUM: {
						// Do nothing for sum -> processing is done afterwards.
						callStack.push_back( cur->summands()->rhs );
						callStack.push_back( cur->summands()->lhs );
						paramStack.emplace_back( currentParam );
						paramStack.emplace_back( currentParam );
						resultStack.emplace_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						resultStack.emplace_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					}
					case SF_TYPE::UNITE: {
						// Do nothing for union -> processing is done afterwards.
						for ( unsigned i = 0; i < cur->unionParameters()->items.size(); ++i ) {
							callStack.push_back( cur->unionParameters()->items.at( i ) );
							paramStack.emplace_back( currentParam );
							resultStack.emplace_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						}
						break;
					}
					case SF_TYPE::INTERSECT: {
						// Do nothing for intersection -> processing is done afterwards.
						callStack.push_back( cur->intersectionParameters()->rhs );
						callStack.push_back( cur->intersectionParameters()->lhs );
						paramStack.emplace_back( currentParam );
						paramStack.emplace_back( currentParam );
						resultStack.emplace_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						resultStack.emplace_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					}
					case SF_TYPE::NONE: {
						std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
						assert( false );
						break;
					}
					default: {
						assert( false );
						return std::vector<EvaluationResult<Number>>();
					}
				}
			}
		}
	}
	assert( false );
	std::cout << "THIS SHOULD NOT HAPPEN." << std::endl;
	return std::vector<EvaluationResult<Number>>();
}

template <typename Number, typename Setting>
std::size_t SupportFunctionContent<Number, Setting>::dimension() const {
	assert( mType != SF_TYPE::NONE );
	return mDimension;
}

template <typename Number, typename Setting>
SF_TYPE SupportFunctionContent<Number, Setting>::type() const {
	return mType;
}

template <typename Number, typename Setting>
unsigned SupportFunctionContent<Number, Setting>::depth() const {
	assert( mType != SF_TYPE::NONE );
	return mDepth;
}

template <typename Number, typename Setting>
unsigned SupportFunctionContent<Number, Setting>::operationCount() const {
	assert( mType != SF_TYPE::NONE );
	return mOperationCount;
}

template <typename Number, typename Setting>
unsigned SupportFunctionContent<Number, Setting>::multiplicationsPerEvaluation() const {
	using Node = std::shared_ptr<SupportFunctionContent<Number, Setting>>;
	using Res = long int;
	std::vector<Node> callStack;
	std::vector<std::pair<std::size_t, std::vector<Res>>> resultStack;	// The first value is an iterator to the calling frame

	callStack.push_back( getThis() );
	resultStack.push_back( std::make_pair( -1, std::vector<Res>() ) );

	while ( !callStack.empty() ) {
		Node cur = callStack.back();

		if ( cur->originCount() == 0 ) {
			// Do computation and write results in case recursion ends.

			std::pair<std::size_t, std::vector<Res>> currentResult = resultStack.back();

			// update result
			// special case: When the node is a leaf, we directly return the result.
			if ( currentResult.first == 1 ) {
				// we reached the top
				assert( currentResult.second.size() == 1 );
				return currentResult.second.front();
			}

			switch ( cur->type() ) {
				case SF_TYPE::INFTY_BALL:
					[[fallthrough]];
				case SF_TYPE::TWO_BALL:
					[[fallthrough]];
				case SF_TYPE::BOX:
					[[fallthrough]];
				case SF_TYPE::ELLIPSOID:
					resultStack.at( currentResult.first ).second.push_back( 1 );
					break;
				case SF_TYPE::POLY: {
					unsigned maxValue = std::max( polytope()->constraints().rows(), polytope()->constraints().cols() );
					resultStack.at( currentResult.first ).second.push_back( carl::pow( maxValue, 2 ) * polytope()->constraints().cols() );
					break;
				}
				default:
					// TODO: Extend for other bottom cases.
					assert( false );
			}

			// leave recursive call.
			callStack.pop_back();
			resultStack.pop_back();

		} else {
			// Detect, if this call is finished or new.
			if ( resultStack.back().second.size() == cur->originCount() ) {
				// the call is finished, perform accumulating operations and forward result.

				// accumulate results
				Res accumulatedResult = 0;
				switch ( cur->type() ) {
					case SF_TYPE::INTERSECT:
						[[fallthrough]];
					case SF_TYPE::PROJECTION:
						[[fallthrough]];
					case SF_TYPE::LINTRAFO:
						accumulatedResult += 1;
						break;
					case SF_TYPE::UNITE:
						for ( auto val : resultStack.back().second ) {
							accumulatedResult += val;
						}
						break;
					case SF_TYPE::NONE: {
						std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
						assert( false );
						break;
					}
					default:
						std::cout << __func__ << ": SF Type unexpected!" << std::endl;
						assert( false );
				}

				if ( resultStack.back().first == -1 ) {
					// we reached the top
					return accumulatedResult;
				}

				resultStack.at( resultStack.back().first ).second.push_back( accumulatedResult );

				// delete result frame and close recursive call
				callStack.pop_back();
				resultStack.pop_back();

			} else {
				// this is the branch for calling recursively

				// here we create the new stack levels. As the parameters are all the same, we do not care for their order (could be extended).
				std::size_t callingFrame = callStack.size() - 1;

				switch ( cur->type() ) {
					case SF_TYPE::SUM:
						callStack.push_back( cur->summands()->rhs );
						callStack.push_back( cur->summands()->lhs );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					case SF_TYPE::INTERSECT:
						callStack.push_back( cur->intersectionParameters()->rhs );
						callStack.push_back( cur->intersectionParameters()->lhs );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					case SF_TYPE::LINTRAFO:
						callStack.push_back( cur->linearTrafoParameters()->origin );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					case SF_TYPE::SCALE:
						callStack.push_back( cur->scaleParameters()->origin );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					case SF_TYPE::UNITE:
						for ( unsigned i = 0; i < cur->unionParameters()->items.size(); ++i ) {
							callStack.push_back( cur->unionParameters()->items.at( i ) );
							resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						}
						break;
					case SF_TYPE::POLY:
						[[fallthrough]];
					case SF_TYPE::INFTY_BALL:
						[[fallthrough]];
					case SF_TYPE::TWO_BALL:
						[[fallthrough]];
					case SF_TYPE::ELLIPSOID:
						[[fallthrough]];
					case SF_TYPE::BOX:
						[[fallthrough]];
					case SF_TYPE::ZONOTOPE:
						assert( false );
						break;
					case SF_TYPE::PROJECTION:
						callStack.push_back( cur->projectionParameters()->origin );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					case SF_TYPE::NONE:
					default:
						assert( false );
				}
			}
		}
	}
	std::cout << __func__ << ": This should not be reachable." << std::endl;
	return 0;
}

template <typename Number, typename Setting>
void SupportFunctionContent<Number, Setting>::forceLinTransReduction() {
	assert( checkTreeValidity() );
	switch ( mType ) {
		case SF_TYPE::LINTRAFO: {
			std::shared_ptr<SupportFunctionContent<Number, Setting>> origin = linearTrafoParameters()->origin;
			std::pair<matrix_t<Number>, vector_t<Number>> parameterPair = linearTrafoParameters()->parameters->getParameterSet( linearTrafoParameters()->currentExponent );
			std::pair<matrix_t<Number>, vector_t<Number>> nextPair;
			while ( origin->type() == SF_TYPE::LINTRAFO ) {
				unsigned currentExponent = origin->linearTrafoParameters()->currentExponent;
				nextPair = origin->linearTrafoParameters()->parameters->getParameterSet( currentExponent );
				// parameterPair.second = parameterPair.second + parameterPair.first * nextPair.second + parameterPair.second;
				parameterPair.second = parameterPair.second + parameterPair.first * nextPair.second;
				parameterPair.first = parameterPair.first * nextPair.first;
				origin = origin->linearTrafoParameters()->origin;
			}
			mDepth = origin->depth() + 1;
			mOperationCount = origin->operationCount() + 1;
			mLinearTrafoParameters = new trafoContent<Number, Setting>( origin, parameterPair.first, parameterPair.second );
			break;
		}
		case SF_TYPE::SUM: {
			summands()->lhs->forceLinTransReduction();
			summands()->rhs->forceLinTransReduction();
			mDepth = std::max( summands()->lhs->operationCount(), summands()->rhs->operationCount() ) + 1;
			mOperationCount = summands()->lhs->operationCount() + summands()->rhs->operationCount() + 1;
			break;
		}
		case SF_TYPE::INTERSECT: {
			intersectionParameters()->rhs->forceLinTransReduction();
			intersectionParameters()->lhs->forceLinTransReduction();
			mDepth = std::max( intersectionParameters()->lhs->operationCount(), intersectionParameters()->rhs->operationCount() ) + 1;
			mOperationCount = intersectionParameters()->lhs->operationCount() + intersectionParameters()->rhs->operationCount() + 1;
			break;
		}
		case SF_TYPE::UNITE: {
			mOperationCount = 1;
			for ( auto& item : unionParameters()->items ) {
				item->forceLinTransReduction();
				mDepth = mDepth > item->depth() ? mDepth : item->depth();
				mOperationCount += item->operationCount();
			}
			break;
		}
		case SF_TYPE::PROJECTION: {
			projectionParameters()->origin->forceLinTransReduction();
			mDepth = projectionParameters()->origin->depth() + 1;
			mOperationCount = projectionParameters()->origin->operationCount() + 1;
			break;
		}
		case SF_TYPE::SCALE: {
			scaleParameters()->origin->forceLinTransReduction();
			mDepth = scaleParameters()->origin->depth() + 1;
			mOperationCount = scaleParameters()->origin->operationCount() + 1;
			break;
		}
		case SF_TYPE::NONE: {
			std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
			assert( false );
			break;
		}
		default:
			break;
	}
	assert( checkTreeValidity() );
}

template <typename Number, typename Setting>
Point<Number> SupportFunctionContent<Number, Setting>::supremumPoint() const {
	assert( checkTreeValidity() );
	switch ( mType ) {
		case SF_TYPE::INFTY_BALL:
			[[fallthrough]];
		case SF_TYPE::TWO_BALL:
			return ball()->supremumPoint();
		case SF_TYPE::LINTRAFO: {
			Point<Number> supPoint = linearTrafoParameters()->origin->supremumPoint();
			if ( supPoint.dimension() == 0 ) {
				return supPoint;
			}
			std::pair<matrix_t<Number>, vector_t<Number>> parameterPair = linearTrafoParameters()->parameters->getParameterSet( linearTrafoParameters()->currentExponent );
			return supPoint.affineTransformation( parameterPair.first, parameterPair.second );
		}
		case SF_TYPE::POLY:
			return polytope()->supremumPoint();
		case SF_TYPE::BOX:
			return box()->supremumPoint();
		case SF_TYPE::PROJECTION: {
			Point<Number> tmpRes = projectionParameters()->origin->supremumPoint();
			vector_t<Number> tmp = vector_t<Number>::Zero( mDimension );
			for ( const auto& entry : projectionParameters()->dimensions ) {
				if ( entry < mDimension ) {
					tmp( entry ) = tmpRes.at( entry );
				}
			}
			return Point<Number>( tmp );
		}
		case SF_TYPE::SCALE: {
			if ( scaleParameters()->factor == 0 ) {
				return Point<Number>::Zero( mDimension );
			} else {
				Point<Number> supPoint = scaleParameters()->origin->supremumPoint();
				if ( supPoint.dimension() == 0 ) {
					return supPoint;
				}
				return supPoint * scaleParameters()->factor;
			}
		}
		case SF_TYPE::SUM: {
			Point<Number> lhsPoint = summands()->lhs->supremumPoint();
			Point<Number> rhsPoint = summands()->rhs->supremumPoint();
			if ( lhsPoint.dimension() == 0 ) {
				return rhsPoint;
			}
			if ( rhsPoint.dimension() == 0 ) {
				return lhsPoint;
			}
			return lhsPoint + rhsPoint;
		}
		case SF_TYPE::UNITE: {
			Point<Number> resPoint = ( *unionParameters()->items.begin() )->supremumPoint();
			if ( resPoint.dimension() == 0 ) {
				return resPoint;
			}
			auto itemIt = unionParameters()->items.begin();
			++itemIt;
			for ( ; itemIt != unionParameters()->items.end(); ++itemIt ) {
				Point<Number> tmpPoint = ( *itemIt )->supremumPoint();
				resPoint = Point<Number>::inftyNorm( resPoint ) > Point<Number>::inftyNorm( tmpPoint ) ? resPoint : tmpPoint;
			}
			return resPoint;
		}
		case SF_TYPE::INTERSECT: {
			Point<Number> lhsPoint = intersectionParameters()->lhs->supremumPoint();
			Point<Number> rhsPoint = intersectionParameters()->rhs->supremumPoint();
			if ( lhsPoint.dimension() == 0 ) {
				return rhsPoint;
			}
			if ( rhsPoint.dimension() == 0 ) {
				return lhsPoint;
			}
			if ( Point<Number>::inftyNorm( lhsPoint ) < Point<Number>::inftyNorm( rhsPoint ) ) {
				return lhsPoint;
			}
			return rhsPoint;
		}
		case SF_TYPE::NONE: {
			std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
			assert( false );
			return Point<Number>();
		}
		default:
			assert( false );
			return Point<Number>();
	}
}

template <typename Number, typename Setting>
std::vector<std::size_t> SupportFunctionContent<Number, Setting>::collectProjections() const {
	using Node = std::shared_ptr<SupportFunctionContent<Number, Setting>>;
	using Res = std::vector<std::size_t>;

	std::vector<Node> callStack;
	// std::vector<vector_t<Number>> paramStack;
	std::vector<std::pair<int, std::vector<Res>>> resultStack;	// The first value is an iterator to the calling frame

	callStack.push_back( getThis() );
	// paramStack.push_back(1);
	resultStack.push_back( std::make_pair( -1, std::vector<Res>() ) );

	while ( !callStack.empty() ) {
		Node cur = callStack.back();
		// T currentParam = paramStack.back();

		// if(cur->children.empty()) {
		if ( cur->mType == SF_TYPE::BOX || cur->mType == SF_TYPE::POLY || cur->mType == SF_TYPE::INFTY_BALL || cur->mType == SF_TYPE::TWO_BALL || cur->mType == SF_TYPE::ELLIPSOID ) {
			// Do computation and write results in case recursion ends.

			std::pair<int, std::vector<Res>> currentResult = resultStack.back();

			// update result
			Res res;
			// DEBUG("hypro.representations.supportFunction","mDimension " << mDimension);
			for ( std::size_t i = 0; i < mDimension; ++i ) {
				// DEBUG("hypro.representations.supportFunction","Added dimension " << i);
				res.emplace_back( i );
			}

			// special case: When the node is a leaf, we directly return the result.
			if ( currentResult.first == -1 ) {
				// we reached the top, exit (or return result or whatever)
				return res;
			}

			resultStack.at( currentResult.first ).second.push_back( res );

			// leave recursive call.
			callStack.pop_back();
			// paramStack.pop_back();
			resultStack.pop_back();

		} else {
			// Detect, if this call is finished or new.
			if ( resultStack.back().second.size() == cur->originCount() ) {
				//
				// the call is finished, perform accumulating operations and forward result.

				// accumulate results - in this case intersect sets.

				if ( resultStack.back().second.size() == 1 ) {
					// TODO: Handle lintrafo here separately.
					// We need to filter, in case the element is a projection.
					if ( cur->type() == SF_TYPE::PROJECTION ) {
						assert( resultStack.back().second.size() == 1 );
						std::vector<std::size_t> tmp = cur->projectionParameters()->dimensions;
						for ( auto dimIt = tmp.begin(); dimIt != tmp.end(); ) {
							if ( std::find( resultStack.back().second.front().begin(), resultStack.back().second.front().end(), *dimIt ) == resultStack.back().second.front().end() ) {
								dimIt = tmp.erase( dimIt );
							} else {
								++dimIt;
							}
						}
						std::swap( resultStack.back().second.front(), tmp );
					}

					if ( resultStack.back().first == -1 ) {
						return resultStack.back().second.front();
					}
					resultStack.at( resultStack.back().first ).second.push_back( resultStack.back().second.front() );
				} else {
					Res accumulatedResult;
					// we create the intersection of all results. Therefore we iterate over the first vector and check the other
					// result vectors, if the respective element is contained. Iterating over the first is sufficient, as elements
					// not in the first vector will not be in the intersection anyways.
					for ( unsigned pos = 0; pos < resultStack.back().second.begin()->size(); ++pos ) {
						std::size_t element = resultStack.back().second.begin()->at( pos );
						bool elementInAllVectors = true;
						for ( unsigned resIndex = 1; resIndex < resultStack.back().second.size(); ++resIndex ) {
							if ( std::find( resultStack.back().second.at( resIndex ).begin(), resultStack.back().second.at( resIndex ).end(), element ) == resultStack.back().second.at( resIndex ).end() ) {
								elementInAllVectors = false;
								break;
							}
						}
						if ( elementInAllVectors ) {
							// if this is a projection, we need to remove non-projected dimensions
							if ( cur->type() != SF_TYPE::PROJECTION ||
								 ( cur->type() == SF_TYPE::PROJECTION && std::find( cur->projectionParameters()->dimensions.begin(), cur->projectionParameters()->dimensions.end(), element ) != cur->projectionParameters()->dimensions.end() ) ) {
								accumulatedResult.emplace_back( element );
							}
						}
					}

					// push result up or return
					if ( resultStack.back().first == -1 ) {
						return accumulatedResult;
					}
					resultStack.at( resultStack.back().first ).second.push_back( accumulatedResult );
				}

				// delete result frame and close recursive call
				callStack.pop_back();
				resultStack.pop_back();

			} else {
				// NEW RECURSIVE CALLS
				int callingFrame = int( callStack.size() ) - 1;

				switch ( cur->type() ) {
					case SF_TYPE::SUM:
						callStack.push_back( cur->summands()->rhs );
						callStack.push_back( cur->summands()->lhs );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					case SF_TYPE::INTERSECT:
						callStack.push_back( cur->intersectionParameters()->rhs );
						callStack.push_back( cur->intersectionParameters()->lhs );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					case SF_TYPE::LINTRAFO:
						callStack.push_back( cur->linearTrafoParameters()->origin );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					case SF_TYPE::SCALE:
						callStack.push_back( cur->scaleParameters()->origin );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					case SF_TYPE::UNITE:
						for ( unsigned i = 0; i < cur->unionParameters()->items.size(); ++i ) {
							callStack.push_back( cur->unionParameters()->items.at( i ) );
							resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						}
						break;
					case SF_TYPE::POLY:
						[[fallthrough]];
					case SF_TYPE::INFTY_BALL:
						[[fallthrough]];
					case SF_TYPE::TWO_BALL:
						[[fallthrough]];
					case SF_TYPE::ELLIPSOID:
						[[fallthrough]];
					case SF_TYPE::BOX:
						[[fallthrough]];
					case SF_TYPE::ZONOTOPE:
						assert( false );
						break;
					case SF_TYPE::PROJECTION:
						callStack.push_back( cur->projectionParameters()->origin );
						resultStack.push_back( std::make_pair( callingFrame, std::vector<Res>() ) );
						break;
					case SF_TYPE::NONE:
					default:
						assert( false );
				}
			}
		}
	}
	assert( false );
	std::cout << "THIS SHOULD NOT HAPPEN." << std::endl;
	return std::vector<std::size_t>();
}

template <typename Number, typename Setting>
sumContent<Number, Setting>* SupportFunctionContent<Number, Setting>::summands() const {
	assert( mType == SF_TYPE::SUM );
	return mSummands;
}

template <typename Number, typename Setting>
trafoContent<Number, Setting>* SupportFunctionContent<Number, Setting>::linearTrafoParameters() const {
	assert( mType == SF_TYPE::LINTRAFO );
	return mLinearTrafoParameters;
}

template <typename Number, typename Setting>
scaleContent<Number, Setting>* SupportFunctionContent<Number, Setting>::scaleParameters() const {
	assert( mType == SF_TYPE::SCALE );
	return mScaleParameters;
}

template <typename Number, typename Setting>
unionContent<Number, Setting>* SupportFunctionContent<Number, Setting>::unionParameters() const {
	assert( mType == SF_TYPE::UNITE );
	return mUnionParameters;
}

template <typename Number, typename Setting>
intersectionContent<Number, Setting>* SupportFunctionContent<Number, Setting>::intersectionParameters() const {
	assert( mType == SF_TYPE::INTERSECT );
	assert( mIntersectionParameters );
	return mIntersectionParameters;
}

template <typename Number, typename Setting>
projectionContent<Number, Setting>* SupportFunctionContent<Number, Setting>::projectionParameters() const {
	assert( mType == SF_TYPE::PROJECTION );
	return mProjectionParameters;
}

template <typename Number, typename Setting>
PolytopeSupportFunction<Number, Setting>* SupportFunctionContent<Number, Setting>::polytope() const {
	assert( mType == SF_TYPE::POLY );
	return mPolytope;
}

template <typename Number, typename Setting>
BoxSupportFunction<Number, Setting>* SupportFunctionContent<Number, Setting>::box() const {
	assert( mType == SF_TYPE::BOX );
	return mBox;
}

template <typename Number, typename Setting>
EllipsoidSupportFunction<Number>* SupportFunctionContent<Number, Setting>::ellipsoid() const {
	assert( mType == SF_TYPE::ELLIPSOID );
	return mEllipsoid;
}

template <typename Number, typename Setting>
BallSupportFunction<Number>* SupportFunctionContent<Number, Setting>::ball() const {
	assert( mType == SF_TYPE::INFTY_BALL || mType == SF_TYPE::TWO_BALL );
	return mBall;
}

template <typename Number, typename Setting>
std::shared_ptr<SupportFunctionContent<Number, Setting>> SupportFunctionContent<Number, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
	return create( getThis(), dimensions );
}

template <typename Number, typename Setting>
std::shared_ptr<SupportFunctionContent<Number, Setting>> SupportFunctionContent<Number, Setting>::affineTransformation(
	  const matrix_t<Number>& A, const vector_t<Number>& b ) const {
	return create( getThis(), A, b );
}

template <typename Number, typename Setting>
std::shared_ptr<SupportFunctionContent<Number, Setting>> SupportFunctionContent<Number, Setting>::minkowskiSum(
	  const std::shared_ptr<SupportFunctionContent<Number, Setting>>& rhs ) const {
	return create( SF_TYPE::SUM, getThis(), rhs );
}

template <typename Number, typename Setting>
std::shared_ptr<SupportFunctionContent<Number, Setting>> SupportFunctionContent<Number, Setting>::intersect(
	  const std::shared_ptr<SupportFunctionContent<Number, Setting>>& rhs ) const {
	return create( SF_TYPE::INTERSECT, getThis(), rhs );
}

template <typename Number, typename Setting>
bool SupportFunctionContent<Number, Setting>::contains( const Point<Number>& _point ) const {
	assert( mType != SF_TYPE::NONE );
	return this->contains( _point.rawCoordinates() );
}

template <typename Number, typename Setting>
bool SupportFunctionContent<Number, Setting>::contains( const vector_t<Number>& _point ) const {
	switch ( mType ) {
		case SF_TYPE::ELLIPSOID:
			return ellipsoid()->contains( _point );
		case SF_TYPE::INFTY_BALL:
			[[fallthrough]];
		case SF_TYPE::TWO_BALL:
			return ball()->contains( _point );
		case SF_TYPE::LINTRAFO: {
			auto& [matrix, vector] = linearTrafoParameters()->parameters->getParameterSet( linearTrafoParameters()->currentExponent );
			return linearTrafoParameters()->origin->contains( ( matrix.transpose() * _point ) - vector );
		}
		case SF_TYPE::POLY:
			return polytope()->contains( _point );
		case SF_TYPE::BOX:
			return box()->contains( _point );
		case SF_TYPE::PROJECTION:
			return projectionParameters()->origin->contains( _point );	// TODO: Correct?
		case SF_TYPE::SCALE:
			if ( scaleParameters()->factor == 0 )
				return false;
			else
				return scaleParameters()->origin->contains( _point / scaleParameters()->factor );
		case SF_TYPE::SUM: {
			// DEBUG("hypro.representations.supportFunction","MINKOWSKI-SUM, point: " << _point);
			//  current approach: Use templated evaluation.
			std::vector<vector_t<Number>> templates = computeTemplate<Number>( this->dimension(), defaultTemplateDirectionCount );
			// use single evaluation, as one invalid eval is enough to determine the point is not contained.
			for ( const auto& dir : templates ) {
				////DEBUG("hypro.representations.supportFunction","Evaluate " << dir);
				EvaluationResult<Number> rhsRes = summands()->rhs->evaluate( dir, false );
				////DEBUG("hypro.representations.supportFunction","Rhsres: " << rhsRes.supportValue);
				EvaluationResult<Number> lhsRes = summands()->lhs->evaluate( dir, false );
				// DEBUG("hypro.representations.supportFunction","Lhsres: " << lhsRes.supportValue);
				// DEBUG("hypro.representations.supportFunction","Summed: " << rhsRes.supportValue + lhsRes.supportValue << " and point dist: " << dir.dot(_point));
				if ( dir.dot( _point ) > ( lhsRes.supportValue + rhsRes.supportValue ) ) {
					return false;
				}
			}
			return true;
		}
		case SF_TYPE::UNITE:
			return std::any_of( unionParameters()->items.begin(), unionParameters()->items.end(), [&_point]( const auto& set ) { return set->contains( _point ); } );
		case SF_TYPE::INTERSECT:
			return ( intersectionParameters()->rhs->contains( _point ) && intersectionParameters()->lhs->contains( _point ) );
		case SF_TYPE::NONE:
			std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
			assert( false );
			return false;
		default:
			assert( false );
			return false;
	}
	return true;
}

template <typename Number, typename Setting>
std::shared_ptr<SupportFunctionContent<Number, Setting>> SupportFunctionContent<Number, Setting>::unite(
	  const std::shared_ptr<SupportFunctionContent<Number, Setting>>& rhs ) const {
	return create( SF_TYPE::UNITE, getThis(), rhs );
}

template <typename Number, typename Setting>
std::shared_ptr<SupportFunctionContent<Number, Setting>> SupportFunctionContent<Number, Setting>::unite( const std::vector<std::shared_ptr<SupportFunctionContent<Number, Setting>>>& rhs ) {
	return create( SF_TYPE::UNITE, rhs );
}

template <typename Number, typename Setting>
std::shared_ptr<SupportFunctionContent<Number, Setting>> SupportFunctionContent<Number, Setting>::scale( const Number& factor ) const {
	return create( getThis(), factor );
}

template <typename Number, typename Setting>
void SupportFunctionContent<Number, Setting>::reduceRepresentation() {
}

template <typename Number, typename Setting>
bool SupportFunctionContent<Number, Setting>::empty() const {
	assert( checkTreeValidity() );
	switch ( mType ) {
		case SF_TYPE::ELLIPSOID:
			return ellipsoid()->empty();
		case SF_TYPE::INFTY_BALL:
			[[fallthrough]];
		case SF_TYPE::TWO_BALL:
			return ball()->empty();
		case SF_TYPE::LINTRAFO:
			return linearTrafoParameters()->origin->empty();
		case SF_TYPE::POLY:
			return polytope()->empty();
		case SF_TYPE::BOX:
			return box()->empty();
		case SF_TYPE::PROJECTION:
			if ( projectionParameters()->dimensions.empty() ) {
				return true;
			}
			return projectionParameters()->origin->empty();
		case SF_TYPE::SCALE:
			if ( scaleParameters()->factor == 0 )
				return true;
			else
				return scaleParameters()->origin->empty();	// TODO What if factor is negative?
		case SF_TYPE::SUM:
			return ( summands()->lhs->empty() || summands()->rhs->empty() );
		case SF_TYPE::UNITE:
			return std::any_of( unionParameters()->items.begin(), unionParameters()->items.end(), []( const auto& set ) { return set->empty(); } );
		case SF_TYPE::INTERSECT: {
			if ( mEmptyState == SETSTATE::UNKNOWN ) {
				if ( intersectionParameters()->rhs->empty() || intersectionParameters()->lhs->empty() ) {
					mEmptyState = SETSTATE::EMPTY;
					return true;
				}
				// Current implementation uses template evaluation.
				std::vector<vector_t<Number>> directions = computeTemplate<Number>( this->dimension(), defaultTemplateDirectionCount );
				for ( const auto& direction : directions ) {
					auto rhsPosEval = intersectionParameters()->rhs->evaluate( direction, false );
					auto lhsNegEval = intersectionParameters()->lhs->evaluate( -direction, false );
					if ( rhsPosEval.supportValue < -lhsNegEval.supportValue && rhsPosEval.errorCode != SOLUTION::INFTY && lhsNegEval.errorCode != SOLUTION::INFTY ) {
						mEmptyState = SETSTATE::EMPTY;
						return true;
					}
					auto rhsNegEval = intersectionParameters()->rhs->evaluate( -direction, false );
					auto lhsPosEval = intersectionParameters()->lhs->evaluate( direction, false );
					if ( -rhsNegEval.supportValue > lhsPosEval.supportValue && rhsNegEval.errorCode != SOLUTION::INFTY && lhsPosEval.errorCode != SOLUTION::INFTY ) {
						mEmptyState = SETSTATE::EMPTY;
						return true;
					}
				}
				mEmptyState = SETSTATE::NONEMPTY;
			}
			return ( mEmptyState == SETSTATE::EMPTY );
		}
		case SF_TYPE::NONE:
			std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
			assert( false );
			return false;
		default:
			assert( false );
			return false;
	}
}

template <typename Number, typename Setting>
void SupportFunctionContent<Number, Setting>::cleanUp() const {
	using Node = std::shared_ptr<SupportFunctionContent<Number, Setting>>;
	std::vector<Node> callStack;

	callStack.push_back( getThis() );

	while ( !callStack.empty() ) {
		Node cur = callStack.back();
		callStack.pop_back();

		if ( cur->originCount() == 0 ) {
			switch ( cur->type() ) {
				case SF_TYPE::POLY:
					cur->polytope()->cleanUp();
					break;
				case SF_TYPE::INFTY_BALL:
					[[fallthrough]];
				case SF_TYPE::TWO_BALL:
					[[fallthrough]];
				case SF_TYPE::BOX:
					[[fallthrough]];
				case SF_TYPE::ELLIPSOID:
					break;
				default:
					assert( false );
			}

		} else {
			// this is the branch for calling recursively
			switch ( cur->type() ) {
				case SF_TYPE::SUM:
					callStack.push_back( cur->summands()->rhs );
					callStack.push_back( cur->summands()->lhs );
					break;
				case SF_TYPE::INTERSECT:
					callStack.push_back( cur->intersectionParameters()->rhs );
					callStack.push_back( cur->intersectionParameters()->lhs );
					break;
				case SF_TYPE::LINTRAFO:
					callStack.push_back( cur->linearTrafoParameters()->origin );
					break;
				case SF_TYPE::SCALE:
					callStack.push_back( cur->scaleParameters()->origin );
					break;
				case SF_TYPE::UNITE:
					for ( unsigned i = 0; i < cur->unionParameters()->items.size(); ++i ) {
						callStack.push_back( cur->unionParameters()->items.at( i ) );
					}
					break;
				case SF_TYPE::POLY:
					[[fallthrough]];
				case SF_TYPE::INFTY_BALL:
					[[fallthrough]];
				case SF_TYPE::TWO_BALL:
					[[fallthrough]];
				case SF_TYPE::ELLIPSOID:
					[[fallthrough]];
				case SF_TYPE::BOX:
					[[fallthrough]];
				case SF_TYPE::ZONOTOPE:
					assert( false );
					break;
				case SF_TYPE::PROJECTION:
					callStack.push_back( cur->projectionParameters()->origin );
					break;
				case SF_TYPE::NONE:
				default:
					assert( false );
			}
		}
	}
}

template <typename Number, typename Setting>
void SupportFunctionContent<Number, Setting>::print() const {
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
		case SF_TYPE::BOX: {
			std::cout << "BOX" << std::endl;
		} break;
		case SF_TYPE::LINTRAFO: {
			std::cout << "LINTRAFO A^" << linearTrafoParameters()->currentExponent << std::endl;
			std::cout << "of" << std::endl;
			linearTrafoParameters()->origin->print();
		} break;
		case SF_TYPE::POLY: {
			std::cout << "POLY" << std::endl;
			polytope()->print();
		} break;
		case SF_TYPE::PROJECTION: {
			std::cout << "PROJECTION" << std::endl;
			std::cout << "of" << std::endl;
			projectionParameters()->origin->print();
		} break;
		case SF_TYPE::SCALE: {
			std::cout << "SCALE" << std::endl;
		} break;
		case SF_TYPE::SUM: {
			std::cout << "SUM" << std::endl;
			std::cout << "of: " << std::endl;
			summands()->rhs->print();
			std::cout << "and" << std::endl;
			summands()->lhs->print();
		} break;
		case SF_TYPE::UNITE: {
			std::cout << "UNITE" << std::endl;
		} break;
		case SF_TYPE::INTERSECT: {
			std::cout << "INTERSECTION " << std::endl;
			std::cout << "of" << std::endl;
			intersectionParameters()->lhs->print();
			std::cout << "and" << std::endl;
			intersectionParameters()->rhs->print();
		} break;
		default:
			std::cout << "NONE" << std::endl;
	}
}

template <typename Number, typename Setting>
sumContent<Number, Setting>* SupportFunctionContent<Number, Setting>::rSummands() {
	assert( mType == SF_TYPE::SUM );
	return mSummands;
}

template <typename Number, typename Setting>
trafoContent<Number, Setting>* SupportFunctionContent<Number, Setting>::rLinearTrafoParameters() {
	assert( mType == SF_TYPE::LINTRAFO );
	return mLinearTrafoParameters;
}

template <typename Number, typename Setting>
scaleContent<Number, Setting>* SupportFunctionContent<Number, Setting>::rScaleParameters() {
	assert( mType == SF_TYPE::SCALE );
	return mScaleParameters;
}

template <typename Number, typename Setting>
unionContent<Number, Setting>* SupportFunctionContent<Number, Setting>::rUnionParameters() {
	assert( mType == SF_TYPE::UNITE );
	return mUnionParameters;
}

template <typename Number, typename Setting>
intersectionContent<Number, Setting>* SupportFunctionContent<Number, Setting>::rIntersectionParameters() {
	assert( mType == SF_TYPE::INTERSECT );
	assert( mIntersectionParameters );
	return mIntersectionParameters;
}

template <typename Number, typename Setting>
projectionContent<Number, Setting>* SupportFunctionContent<Number, Setting>::rProjectionParameters() {
	assert( mType == SF_TYPE::PROJECTION );
	return mProjectionParameters;
}

template <typename Number, typename Setting>
PolytopeSupportFunction<Number, Setting>* SupportFunctionContent<Number, Setting>::rPolytope() {
	assert( mType == SF_TYPE::POLY );
	return mPolytope;
}

template <typename Number, typename Setting>
BoxSupportFunction<Number, Setting>* SupportFunctionContent<Number, Setting>::rBox() {
	assert( mType == SF_TYPE::BOX );
	return mBox;
}

template <typename Number, typename Setting>
EllipsoidSupportFunction<Number>* SupportFunctionContent<Number, Setting>::rEllipsoid() {
	assert( mType == SF_TYPE::ELLIPSOID );
	return mEllipsoid;
}

template <typename Number, typename Setting>
BallSupportFunction<Number>* SupportFunctionContent<Number, Setting>::rBall() {
	assert( mType == SF_TYPE::INFTY_BALL || mType == SF_TYPE::TWO_BALL );
	return mBall;
}

}  // namespace hypro
