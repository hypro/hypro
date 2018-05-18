/*
 * This file containts the implementation of support functions. It requires the concrete
 * implementation of set representations as support functions for a successful evaluation
 * as it implements the chain of operations created during reachability analysis.
 * @file SupportFunctionContent.h
 *
 * @author Norman Hansen
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @version	2015-02-27
 */

#pragma once

#include "../../config.h"
#include "util.h"
#include "SupportFunctionSetting.h"
#include "BoxSupportFunction.h"
#include "PolytopeSupportFunction.h"
#include "BallSupportFunction.h"
#include "EllipsoidSupportFunction.h"
#include "../../util/templateDirections.h"

namespace hypro {
template <typename Number>
class SupportFunctionContent;

template <typename Number>
struct sumContent {
	std::shared_ptr<SupportFunctionContent<Number>> lhs;
	std::shared_ptr<SupportFunctionContent<Number>> rhs;
	sumContent( const std::shared_ptr<SupportFunctionContent<Number>>& _lhs, const std::shared_ptr<SupportFunctionContent<Number>>& _rhs )
		: lhs( _lhs ), rhs( _rhs ) {}
	sumContent( const sumContent<Number>& _origin ) : lhs( _origin.lhs ), rhs( _origin.rhs ) {}

	std::size_t originCount() const { return 2; }
};

template <typename Number, class Setting>
struct trafoContent {
	std::shared_ptr<SupportFunctionContent<Number>> origin;
	std::shared_ptr<const lintrafoParameters<Number>> parameters;
	unsigned currentExponent;
	std::size_t successiveTransformations;
	// 2^power defines the max. number of successive lin.trans before reducing the SF

	trafoContent( const std::shared_ptr<SupportFunctionContent<Number>>& _origin, const matrix_t<Number>& A, const vector_t<Number>& b )
		: origin( _origin ), currentExponent(1) {
		// Determine, if we need to create new parameters or if this matrix and vector pair has already been used (recursive).
		parameters = std::make_shared<const lintrafoParameters<Number>>(A,b);
		// in case this transformation has already been performed, parameters will be updated.
		_origin->hasTrafo(parameters, A, b);
		if(Setting::USE_LIN_TRANS_REDUCTION){
			// best points for reduction are powers of 2 thus we only use these points for possible reduction points
			bool reduced;
			do {
				reduced = false;
				if ( (origin->type() == SF_TYPE::LINTRAFO) && (*origin->linearTrafoParameters()->parameters == *parameters) && origin->linearTrafoParameters()->currentExponent == currentExponent ) {
					successiveTransformations = origin->linearTrafoParameters()->successiveTransformations +1 ;
				} else {
					successiveTransformations = 0;
				}
				//std::cout << "successiveTransformations with exponent " << currentExponent << ": " << successiveTransformations << std::endl;
				if (successiveTransformations == unsigned(carl::pow(2,parameters->power)-1)) {
					reduced = true;
					currentExponent = currentExponent*(carl::pow(2,parameters->power));
					for(std::size_t i = 0; i < unsigned(carl::pow(2,parameters->power)-1); i++ ){
						origin = origin->linearTrafoParameters()->origin;
					}
					// Note: The following assertion does not hold in combination with the current reduction techniques.
					//assert(origin->type() != SF_TYPE::LINTRAFO || (origin->linearTrafoParameters()->parameters == this->parameters && origin->linearTrafoParameters()->currentExponent >= currentExponent) );
				}
			} while (reduced == true);
			assert(origin->checkTreeValidity());
		}
	}

	trafoContent( const trafoContent<Number,Setting>& _origin ) : origin( _origin.origin ), parameters(_origin.parameters), currentExponent(_origin.currentExponent), successiveTransformations( _origin.successiveTransformations )
	{}

	std::size_t originCount() const { return 1; }

	std::pair<matrix_t<Number>, vector_t<Number>> reduceLinTrans(const matrix_t<Number>& _a, const vector_t<Number>& _b, std::size_t _power){
		std::size_t powerOfTwo = carl::pow(2, _power);
			// first compute the new b
		vector_t<Number> bTrans = _b;
		matrix_t<Number> aTrans = _a;
		for (std::size_t i = 1; i < powerOfTwo ; i++){
			bTrans = _a*bTrans + _b;
		}
		// now compute a^i efficiently
		for (std::size_t i = 0; i < _power; i++){
			aTrans = aTrans*aTrans;
		}
		return std::make_pair(aTrans, bTrans);
	}
};

template <typename Number>
struct scaleContent {
	std::shared_ptr<SupportFunctionContent<Number>> origin;
	Number factor;
	scaleContent( const std::shared_ptr<SupportFunctionContent<Number>>& _origin, Number _factor )
		: origin( _origin ), factor( _factor ) {}
	scaleContent( const scaleContent<Number>& _origin ) : origin( _origin.origin ), factor( _origin.factor ) {}

	std::size_t originCount() const { return 1; }
};

template <typename Number>
struct unionContent {
	std::vector<std::shared_ptr<SupportFunctionContent<Number>>> items;
	unionContent( const std::shared_ptr<SupportFunctionContent<Number>>& _lhs, const std::shared_ptr<SupportFunctionContent<Number>>& _rhs )
	{
		// This constructor is legacy.
		items.push_back(_lhs);
		items.push_back(_rhs);
		assert(items.size() == 2);
	}

	unionContent( const std::vector<std::shared_ptr<SupportFunctionContent<Number>>>& sfVector ) : items(sfVector) {}
	unionContent( const unionContent<Number>& _origin ) = default;

	std::size_t originCount() const { return items.size(); }
};

template <typename Number>
struct intersectionContent {
	std::shared_ptr<SupportFunctionContent<Number>> lhs;
	std::shared_ptr<SupportFunctionContent<Number>> rhs;
	intersectionContent( const std::shared_ptr<SupportFunctionContent<Number>>& _lhs, const std::shared_ptr<SupportFunctionContent<Number>>& _rhs )
		: lhs( _lhs ), rhs( _rhs ) {}
	intersectionContent( const intersectionContent<Number>& _origin ) = default;

	std::size_t originCount() const { return 2; }
};

template<typename Number>
struct projectionContent {
	std::shared_ptr<SupportFunctionContent<Number>> origin;
	std::vector<std::size_t> dimensions;
	projectionContent( const std::shared_ptr<SupportFunctionContent<Number>>& _origin, const std::vector<std::size_t>& _dimensions )
		: origin(_origin), dimensions(_dimensions) {}
	projectionContent( const projectionContent<Number>& _original ) : origin(_original.origin), dimensions(_original.dimensions) {}

	std::size_t originCount() const { return 1; }
};

/**
 * @brief      Class for support function content.
 * @tparam     Number  The used number type.
 */
template <typename Number>
class SupportFunctionContent {
	friend trafoContent<Number,SupportFunctionContentSetting>;

  private:
	SF_TYPE mType = SF_TYPE::NONE;
	unsigned mDepth;
	unsigned mOperationCount;
	std::size_t mDimension;
	bool mContainsProjection;
	union {
		sumContent<Number>* mSummands;
		trafoContent<Number,SupportFunctionContentSetting>* mLinearTrafoParameters;
		scaleContent<Number>* mScaleParameters;
		unionContent<Number>* mUnionParameters;
		intersectionContent<Number>* mIntersectionParameters;
		projectionContent<Number>* mProjectionParameters;
		PolytopeSupportFunction<Number,PolytopeSupportFunctionSetting>* mPolytope;
		BoxSupportFunction<Number>* mBox;
		BallSupportFunction<Number>* mBall;
		EllipsoidSupportFunction<Number>* mEllipsoid;
	};

	std::weak_ptr<SupportFunctionContent<Number>> pThis;

	SupportFunctionContent( const matrix_t<Number>& _shapeMatrix, SF_TYPE _type = SF_TYPE::ELLIPSOID );
	SupportFunctionContent( Number _radius, unsigned dimension, SF_TYPE _type = SF_TYPE::INFTY_BALL );
	SupportFunctionContent( const matrix_t<Number>& _directions, const vector_t<Number>& _distances,
					 SF_TYPE _type = SF_TYPE::POLY );
	SupportFunctionContent( const std::vector<Halfspace<Number>>& _planes, SF_TYPE _type = SF_TYPE::POLY );
	SupportFunctionContent( const std::vector<Point<Number>>& _points, SF_TYPE _type = SF_TYPE::POLY );
	SupportFunctionContent( const std::vector<carl::Interval<Number>>& _inbox, SF_TYPE _type = SF_TYPE::BOX );
	SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number>>& _lhs, const std::shared_ptr<SupportFunctionContent<Number>>& _rhs,
					 SF_TYPE _type );
	SupportFunctionContent( const std::vector<std::shared_ptr<SupportFunctionContent<Number>>>& rhs, SF_TYPE type = SF_TYPE::UNITE );
	SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number>>& _origin, const matrix_t<Number>& A, const vector_t<Number>& b, SF_TYPE _type );
	SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number>>& _origin, const Number& _factor,
					 SF_TYPE _type = SF_TYPE::SCALE );
	SupportFunctionContent( const std::shared_ptr<SupportFunctionContent<Number>>& _origin, const std::vector<std::size_t>& dimensions, SF_TYPE _type = SF_TYPE::PROJECTION );
	SupportFunctionContent( const SupportFunctionContent<Number>& _orig );

  public:

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type, matrix_t<Number> _shapeMatrix ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _shapeMatrix, _type ));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type, Number _radius, unsigned dimension ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _radius, dimension, _type ));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type, const matrix_t<Number>& _directions,
																	const vector_t<Number>& _distances ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _directions, _distances, _type ));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type, const std::vector<carl::Interval<Number>>& inbox  ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( inbox, _type ));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type, const std::vector<Halfspace<Number>>& _planes ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _planes, _type ));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type, const std::vector<Point<Number>>& _points ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _points, _type ));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE type, const std::shared_ptr<SupportFunctionContent<Number>>& lhs, const std::shared_ptr<SupportFunctionContent<Number>>& rhs ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( lhs, rhs, type ));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE type, const std::vector<std::shared_ptr<SupportFunctionContent<Number>>>& rhs ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(rhs, type));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( const std::shared_ptr<SupportFunctionContent<Number>>& orig, const matrix_t<Number>& constraints,
															const vector_t<Number>& constants ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(orig, constraints, constants, SF_TYPE::LINTRAFO));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( const std::shared_ptr<SupportFunctionContent<Number>>& orig, Number factor ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(orig, factor, SF_TYPE::SCALE));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( const std::shared_ptr<SupportFunctionContent<Number>>& orig, const std::vector<std::size_t>& dimensions ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(orig, dimensions, SF_TYPE::PROJECTION));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( const std::shared_ptr<SupportFunctionContent<Number>>& orig ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>(orig));
		obj->pThis = obj;
		assert(obj->checkTreeValidity());
		return obj;
	}

	virtual ~SupportFunctionContent();

	std::shared_ptr<SupportFunctionContent<Number>>& operator=( const std::shared_ptr<SupportFunctionContent<Number>>& _orig ) ;

	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction, bool useExact ) const;
	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const;

	std::size_t dimension() const;
	SF_TYPE type() const;
	unsigned depth() const;
	unsigned operationCount() const;
	std::shared_ptr<SupportFunctionContent<Number>> getThis() const { return std::shared_ptr<SupportFunctionContent<Number>>(pThis); }

	/**
	 * Returns an approximation of the number of mv multiplications neccessary for an evaluation of the SF
	 */
	unsigned multiplicationsPerEvaluation() const;

	void forceLinTransReduction();

	Point<Number> supremumPoint() const;

	std::vector<std::size_t> collectProjections() const;
	std::vector<std::size_t> collectProjectionsIterative() const;

	// getter for the union types
	sumContent<Number>* summands() const;
	scaleContent<Number>* scaleParameters() const;
	trafoContent<Number,SupportFunctionContentSetting>* linearTrafoParameters() const;
	unionContent<Number>* unionParameters() const;
	intersectionContent<Number>* intersectionParameters() const;
	projectionContent<Number>* projectionParameters() const;
	PolytopeSupportFunction<Number,PolytopeSupportFunctionSetting>* polytope() const;
	BoxSupportFunction<Number>* box() const;
	BallSupportFunction<Number>* ball() const;
	EllipsoidSupportFunction<Number>* ellipsoid() const;

	std::shared_ptr<SupportFunctionContent<Number>> project(const std::vector<std::size_t>& dimensions) const;
	std::shared_ptr<SupportFunctionContent<Number>> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	std::shared_ptr<SupportFunctionContent<Number>> minkowskiSum( const std::shared_ptr<SupportFunctionContent<Number>>& _rhs ) const;
	std::shared_ptr<SupportFunctionContent<Number>> intersect( const std::shared_ptr<SupportFunctionContent<Number>>& _rhs ) const;
	bool contains( const Point<Number>& _point ) const;
	bool contains( const vector_t<Number>& _point ) const;
	std::shared_ptr<SupportFunctionContent<Number>> unite( const std::shared_ptr<SupportFunctionContent<Number>>& _rhs ) const;
	static std::shared_ptr<SupportFunctionContent<Number>> unite( const std::vector<std::shared_ptr<SupportFunctionContent<Number>>>& _rhs );
	std::shared_ptr<SupportFunctionContent<Number>> scale( const Number& _factor = 1 ) const;

	bool empty() const;

	void cleanUp() const;

	void print() const;
	friend std::ostream& operator<<( std::ostream& lhs, const std::shared_ptr<SupportFunctionContent<Number>>& rhs ) {
		unsigned level = 0;
		//std::cout << "Depth: " << rhs->mDepth << std::endl;
		while(true){
			std::string tmp = rhs->printLevel(level, "   ");
			if(!tmp.empty()) {
				lhs << rhs->printLevel(level, "   ") << std::endl;
				++level;
			} else {
				break;
			}
		}
		return lhs;
	}

	bool checkTreeValidity() const {
		#ifndef NDEBUG
		using Node = std::shared_ptr<SupportFunctionContent<Number>>;
		using Res = bool;
		std::vector<Node> callStack;
		std::vector<std::pair<int,std::vector<Res>>> resultStack; // The first value is an iterator to the calling frame

		callStack.push_back(getThis());
		resultStack.push_back(std::make_pair(-1, std::vector<Res>()));

		while(!callStack.empty()) {
			Node cur = callStack.back();

			if(cur->originCount() == 0) {
				// Do computation and write results in case recursion ends.

				std::pair<int,std::vector<Res>> currentResult = resultStack.back();

				// update result
				// special case: When the node is a leaf, we directly return the result.
				if(currentResult.first == -1) {
					// first item is also top.
					return true;
				}

				switch(cur->type()) {
					case SF_TYPE::INFTY_BALL:
					case SF_TYPE::TWO_BALL:
					case SF_TYPE::POLY:
					case SF_TYPE::BOX:
					case SF_TYPE::ELLIPSOID: {
			            resultStack.at(currentResult.first).second.push_back(true);
			            break;
			        }
			        default:
			        	assert(false);
				}

				// leave recursive call.
				callStack.pop_back();
				resultStack.pop_back();

			} else {
				// Detect, if this call is finished or new.
				if(resultStack.back().second.size() == cur->originCount()) {
					// the call is finished, perform accumulating operations and forward result.

					// accumulate results
					Res accumulatedResult = 0;
					switch(cur->type()) {
						case SF_TYPE::INTERSECT:
				        case SF_TYPE::SUM:
				        case SF_TYPE::LINTRAFO:
				        case SF_TYPE::UNITE:
				        case SF_TYPE::SCALE:
				        case SF_TYPE::PROJECTION:
				        	accumulatedResult = true;
				        	for(auto val : resultStack.back().second) {
				        		if(!val){
				        			accumulatedResult = false;
				        			break;
				        		}
				        	}
				        	break;
				        case SF_TYPE::NONE: {
							std::cout << __func__ << ": SF Type not properly initialized!" << std::endl;
							assert(false);
							break;
						}
						default:
							std::cout << __func__ << ": SF Type unexpected!" << std::endl;
							assert(false);
					}

					if(resultStack.back().first == -1) {
						// we reached the top
						return accumulatedResult;
					}

					resultStack.at(resultStack.back().first).second.push_back(accumulatedResult);

					// delete result frame and close recursive call
					callStack.pop_back();
					resultStack.pop_back();

				} else {
					// this is the branch for calling recursively

					// here we create the new stack levels. As the parameters are all the same, we do not care for their order (could be extended).
					int callingFrame = int(callStack.size()) - 1 ;

					switch ( cur->type() ) {
				        case SF_TYPE::SUM: {
							callStack.push_back(cur->summands()->rhs);
							callStack.push_back(cur->summands()->lhs);
							resultStack.push_back(std::make_pair(callingFrame,std::vector<Res>()));
							resultStack.push_back(std::make_pair(callingFrame,std::vector<Res>()));
							break;
						}
						case SF_TYPE::INTERSECT: {
							callStack.push_back(cur->intersectionParameters()->rhs);
							callStack.push_back(cur->intersectionParameters()->lhs);
							resultStack.push_back(std::make_pair(callingFrame,std::vector<Res>()));
							resultStack.push_back(std::make_pair(callingFrame,std::vector<Res>()));
							break;
						}
						case SF_TYPE::LINTRAFO: {
							callStack.push_back(cur->linearTrafoParameters()->origin);
							resultStack.push_back(std::make_pair(callingFrame,std::vector<Res>()));
							break;
						}
						case SF_TYPE::SCALE: {
							callStack.push_back(cur->scaleParameters()->origin);
							resultStack.push_back(std::make_pair(callingFrame,std::vector<Res>()));
							break;
						}
						case SF_TYPE::UNITE: {
							for(unsigned i = 0; i < cur->unionParameters()->items.size(); ++i){
								callStack.push_back(cur->unionParameters()->items.at(i));
								resultStack.push_back(std::make_pair(callingFrame,std::vector<Res>()));
							}
							break;
						}
						case SF_TYPE::POLY:
						case SF_TYPE::INFTY_BALL:
						case SF_TYPE::TWO_BALL:
						case SF_TYPE::ELLIPSOID:
						case SF_TYPE::BOX:
						case SF_TYPE::ZONOTOPE: {
							assert(false);
							break;
						}
						case SF_TYPE::PROJECTION: {
							callStack.push_back(cur->projectionParameters()->origin);
							resultStack.push_back(std::make_pair(callingFrame,std::vector<Res>()));
							break;
						}
						case SF_TYPE::NONE:
						default:
							assert(false);
				    }
				}
			}
		}

		assert(false);
		std::cout << "THIS SHOULD NOT HAPPEN." << std::endl;
		return false;
		#endif
		// in case this function is not put into an assertion, always return true in productive code.
		return true;
	}

	std::size_t getDotRepresentation(std::size_t startIndex, std::string& nodes, std::string& transitions) const {
		std::stringstream s;
		s << "node" << startIndex << " [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">";
		// add common info
		std::size_t colspan = 1;
		s << "<TR><TD COLSPAN=\""<< colspan << "\">@" << this << "<BR/>"<< this->mType << "</TD></TR>";
		switch ( mType ) {
			case SF_TYPE::BOX: {

				break;
			}
			case SF_TYPE::ELLIPSOID: {

				break;
			}
			case SF_TYPE::INFTY_BALL: {

				break;
			}
			case SF_TYPE::TWO_BALL: {

				break;
			}
			case SF_TYPE::LINTRAFO: {

				break;
			}
			case SF_TYPE::POLY: {
				s << polytope()->getDotRepresentation();
				break;
			}
			case SF_TYPE::PROJECTION: {

				break;
			}
			case SF_TYPE::SCALE: {

				break;
			}
			case SF_TYPE::SUM: {

				break;
			}
			case SF_TYPE::UNITE: {

				break;
			}
			case SF_TYPE::INTERSECT: {

				break;
			}
			case SF_TYPE::ZONOTOPE: {

				break;
			}
			default:
				break;
		}
		s << "</TABLE>>];" << std::endl;
		nodes += s.str();
		std::size_t offset = ++startIndex;
		switch ( mType ) {
			case SF_TYPE::BOX: {
				break;
			}
			case SF_TYPE::ELLIPSOID: {
				break;
			}
			case SF_TYPE::INFTY_BALL: {
				break;
			}
			case SF_TYPE::TWO_BALL: {
				break;
			}
			case SF_TYPE::LINTRAFO: {
				std::stringstream t;
				t << "node" << (startIndex-1) << " -> node" << offset << std::endl;
				transitions += t.str();;
				offset = linearTrafoParameters()->origin->getDotRepresentation(offset,nodes,transitions);
				break;
			}
			case SF_TYPE::POLY: {
				break;
			}
			case SF_TYPE::PROJECTION: {
				std::stringstream t;
				t << "node" << (startIndex-1) << " -> node" << offset << std::endl;
				transitions += t.str();;
				offset = projectionParameters()->origin->getDotRepresentation(offset,nodes,transitions);
				break;
			}
			case SF_TYPE::SCALE: {
				std::stringstream t;
				t << "node" << (startIndex-1) << " -> node" << offset << std::endl;
				transitions += t.str();;
				offset = scaleParameters()->origin->getDotRepresentation(offset,nodes,transitions);
				break;
			}
			case SF_TYPE::SUM: {
				std::stringstream t;
				t << "node" << (startIndex-1) << " -> node" << offset << std::endl;
				offset = summands()->lhs->getDotRepresentation(offset,nodes,transitions);
				t << "node" << (startIndex-1) << " -> node" << offset << std::endl;
				offset = summands()->rhs->getDotRepresentation(offset,nodes,transitions);
				transitions += t.str();;
				break;
			}
			case SF_TYPE::UNITE: {
				std::stringstream t;
				for(auto i : unionParameters()->items) {
					t << "node" << (startIndex-1) << " -> node" << offset << std::endl;
					offset = i->getDotRepresentation(offset,nodes,transitions);
				}

				transitions += t.str();;
				break;
			}
			case SF_TYPE::INTERSECT: {
				std::stringstream t;
				t << "node" << (startIndex-1) << " -> node" << offset << std::endl;
				offset = intersectionParameters()->lhs->getDotRepresentation(offset,nodes,transitions);
				t << "node" << (startIndex-1) << " -> node" << offset << std::endl;
				offset = intersectionParameters()->rhs->getDotRepresentation(offset,nodes,transitions);
				transitions += t.str();;
				break;
			}
			case SF_TYPE::ZONOTOPE: {
				break;
			}
			default:
				break;
		}
		return offset;
	}

	private:

	std::size_t originCount() const {
		switch ( mType ) {
			case SF_TYPE::SUM: {
				return summands()->originCount();
			}
			case SF_TYPE::INTERSECT: {
				return intersectionParameters()->originCount();
			}
			case SF_TYPE::LINTRAFO: {
				return linearTrafoParameters()->originCount();
			}
			case SF_TYPE::SCALE: {
				return scaleParameters()->originCount();
			}
			case SF_TYPE::UNITE: {
				return unionParameters()->originCount();
			}
			case SF_TYPE::POLY:
			case SF_TYPE::INFTY_BALL:
			case SF_TYPE::TWO_BALL:
			case SF_TYPE::ELLIPSOID:
			case SF_TYPE::BOX:
			case SF_TYPE::ZONOTOPE: {
				return 0;
			}
			case SF_TYPE::PROJECTION: {
				return projectionParameters()->originCount();
			}
			case SF_TYPE::NONE:
			default:
				assert(false);
				return 0;
		}
	}

	bool hasTrafo(std::shared_ptr<const lintrafoParameters<Number>>& resNode, const matrix_t<Number>& A, const vector_t<Number>& b) const {
		switch ( mType ) {
			case SF_TYPE::SUM: {
				bool res = summands()->lhs->hasTrafo(resNode, A, b);
				if(!res) {
					res = summands()->rhs->hasTrafo(resNode, A, b);
				}
				return res;
			}
			case SF_TYPE::INTERSECT: {
				bool res = intersectionParameters()->lhs->hasTrafo(resNode, A, b);
				if(!res) {
					res = intersectionParameters()->rhs->hasTrafo(resNode, A, b);
				}
				return res;
			}
			case SF_TYPE::LINTRAFO: {
				if(linearTrafoParameters()->parameters->matrix() == A && linearTrafoParameters()->parameters->vector() == b) {
					resNode = linearTrafoParameters()->parameters;
					return true;
				}
				return linearTrafoParameters()->origin->hasTrafo(resNode, A, b);
			}
			case SF_TYPE::SCALE: {
				return scaleParameters()->origin->hasTrafo(resNode, A, b);
			}
			case SF_TYPE::UNITE: {
				for(const auto& item : unionParameters()->items) {
					if(item->hasTrafo(resNode,A,b)) {
						return true;
					}
				}
				return false;
			}
			case SF_TYPE::POLY:
			case SF_TYPE::INFTY_BALL:
			case SF_TYPE::TWO_BALL:
			case SF_TYPE::ELLIPSOID:
			case SF_TYPE::BOX:
			case SF_TYPE::ZONOTOPE: {
				return false;
			}
			case SF_TYPE::PROJECTION: {
				return projectionParameters()->origin->hasTrafo(resNode, A, b);
				break;
			}
			case SF_TYPE::NONE:
			default:
				assert(false);
				return false;
		}
	}

	std::vector<SF_TYPE> collectLevelEntries(unsigned level) const {
		//std::cout << __func__ << ": level: " << level << std::endl;
		std::vector<SF_TYPE> items;
		if(level == 0) {
			items.push_back(this->mType);
			//std::cout << "items push " << this->mType << std::endl;
			//std::cout << "items size: " << items.size() << std::endl;
			return items;
		}

		// Note that at this point we can omit terminal cases, as the level is larger than the depht of this subtree.
		switch ( mType ) {
			case SF_TYPE::LINTRAFO: {
				//std::cout << "Current: lintrafor" << std::endl;
				std::vector<SF_TYPE> tmpItems = linearTrafoParameters()->origin->collectLevelEntries(level-1);
				items.insert(items.end(), tmpItems.begin(), tmpItems.end());
				return items;
			}
			case SF_TYPE::SCALE: {
				//std::cout << "Current: scale" << std::endl;
				std::vector<SF_TYPE> tmpItems = scaleParameters()->origin->collectLevelEntries(level-1);
				items.insert(items.end(), tmpItems.begin(), tmpItems.end());
				return items;
			}
			case SF_TYPE::PROJECTION: {
				//std::cout << "Current: projection" << std::endl;
				std::vector<SF_TYPE> tmpItems = projectionParameters()->origin->collectLevelEntries(level-1);
				items.insert(items.end(), tmpItems.begin(), tmpItems.end());
				return items;
			}
			case SF_TYPE::SUM: {
				//std::cout << "Current: sum" << std::endl;
				std::vector<SF_TYPE> lhsItems = summands()->lhs->collectLevelEntries(level-1);
				std::vector<SF_TYPE> rhsItems = summands()->rhs->collectLevelEntries(level-1);
				items.insert(items.end(), lhsItems.begin(), lhsItems.end());
				items.insert(items.end(), rhsItems.begin(), rhsItems.end());
				return items;
			}
			case SF_TYPE::UNITE: {
				//std::cout << "Current: union" << std::endl;
				std::vector<SF_TYPE> res;
				for(const auto& item : unionParameters()->items) {
					std::vector<SF_TYPE> tmp = item->collectLevelEntries(level-1);
					res.insert(res.end(), tmp.begin(), tmp.end());
				}
				return res;
			}
			case SF_TYPE::INTERSECT: {
				//std::cout << "Current: intersect" << std::endl;
				std::vector<SF_TYPE> lhsItems = intersectionParameters()->lhs->collectLevelEntries(level-1);
				std::vector<SF_TYPE> rhsItems = intersectionParameters()->rhs->collectLevelEntries(level-1);
				items.insert(items.end(), lhsItems.begin(), lhsItems.end());
				items.insert(items.end(), rhsItems.begin(), rhsItems.end());
				return items;
			}
			default:
				return std::vector<SF_TYPE>();
		}
	}

	std::string printLevel(unsigned l, std::string separator = "\t") const {
		//std::cout << "Print level" << std::endl;
		std::string level;
		std::vector<SF_TYPE> items = this->collectLevelEntries(l);
		if(items.empty())
			return level;

		//std::cout << "With " << items.size() << " entries." << std::endl;
		std::string unaryLevelTransition 	= "  |  "; // 1
		std::string binaryLevelTransition 	= "  |  " + separator + "\\    "; // 2
		std::string emptyLevelTransition 	= "     "; // 0
		std::vector<unsigned> transitionType;

		for(unsigned index = 0; index < items.size(); ++index) {
			switch ( items.at(index) ) {
				case SF_TYPE::BOX: {
					level += "BOX  " + separator;
					transitionType.push_back(0);
					break;
				}
				case SF_TYPE::ELLIPSOID: {
					level += "ELLIP" + separator;
					transitionType.push_back(0);
					break;
				}
				case SF_TYPE::INFTY_BALL: {
					level += "IBALL" + separator;
					transitionType.push_back(0);
					break;
				}
				case SF_TYPE::TWO_BALL: {
					level += "2BALL" + separator;
					transitionType.push_back(0);
					break;
				}
				case SF_TYPE::LINTRAFO: {
					level += "LINTR" + separator;
					transitionType.push_back(1);
					break;
				}
				case SF_TYPE::POLY: {
					level += "POLY " + separator;
					transitionType.push_back(0);
					break;
				}
				case SF_TYPE::PROJECTION: {
					level += "PROJ " + separator;
					transitionType.push_back(1);
					break;
				}
				case SF_TYPE::SCALE: {
					level += "SCALE" + separator;
					transitionType.push_back(1);
					break;
				}
				case SF_TYPE::SUM: {
					level += "SUM   " + separator + "     " + separator;
					transitionType.push_back(2);
					break;
				}
				case SF_TYPE::UNITE: {
					level += "UNITE" + separator + "     " + separator;
					transitionType.push_back(2);
					break;
				}
				case SF_TYPE::INTERSECT: {
					level += "INTSC" + separator + "     " + separator;
					transitionType.push_back(2);
					break;
				}
				case SF_TYPE::ZONOTOPE: {
					level += "ZONO " + separator;
					transitionType.push_back(0);
					break;
				}
				default:
					level += "NONE " + separator;
					transitionType.push_back(0);
			}
		}

		level += "\n";

		for(unsigned index = 0; index < transitionType.size(); ++index){
			switch (transitionType.at(index)){
				case 0: {
					level += emptyLevelTransition + separator;
					break;
				}
				case 1: {
					level += unaryLevelTransition + separator;
					break;
				}
				case 2: {
					level += binaryLevelTransition + separator;
					break;
				}
				default:
					assert(false);
			}
		}

		return level;
	}
};
}  // namespace

#include "SupportFunctionContent.tpp"
