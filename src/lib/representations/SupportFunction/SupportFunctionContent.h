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

#include "util.h"
#include "PolytopeSupportFunction.h"
#include "BallSupportFunction.h"
#include "EllipsoidSupportFunction.h"
#include "../../config.h"

//#define SUPPORTFUNCTION_VERBOSE
//#define MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
#define USE_LIN_TRANS_REDUCTION

namespace hypro {
template <typename Number>
class SupportFunctionContent;

template <typename Number>
struct sumContent {
	std::shared_ptr<SupportFunctionContent<Number>> lhs;
	std::shared_ptr<SupportFunctionContent<Number>> rhs;
	sumContent( std::shared_ptr<SupportFunctionContent<Number>> _lhs, std::shared_ptr<SupportFunctionContent<Number>> _rhs )
		: lhs( _lhs ), rhs( _rhs ) {}
	sumContent( const sumContent<Number>& _origin ) : lhs( _origin.lhs ), rhs( _origin.rhs ) {}
};

template <typename Number>
struct trafoContent {
	std::shared_ptr<SupportFunctionContent<Number>> origin;
	std::shared_ptr<const lintrafoParameters<Number>> parameters;
	unsigned currentExponent;
	std::size_t successiveTransformations;
	// 2^power defines the max. number of successive lin.trans before reducing the SF
        
	trafoContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, const std::shared_ptr<const lintrafoParameters<Number>>& _parameters )
		: origin( _origin ), parameters( _parameters ), currentExponent(1) {
#define USE_LIN_TRANS_REDUCTION
#ifdef USE_LIN_TRANS_REDUCTION
		// best points for reduction are powers of 2 thus we only use these points for possible reduction points
		bool reduced;
		do {
			reduced = false;
			if ( (origin.get()->type() == SF_TYPE::LINTRAFO) && (*origin.get()->linearTrafoParameters()->parameters == *_parameters) && origin->linearTrafoParameters()->currentExponent == currentExponent ) {
				std::cout << "origin exponent: " << origin.get()->linearTrafoParameters()->currentExponent << std::endl;
				std::cout << "origin successive transformations: " << origin.get()->linearTrafoParameters()->successiveTransformations << std::endl;
				successiveTransformations = origin.get()->linearTrafoParameters()->successiveTransformations +1 ;
			} else {
				successiveTransformations = 0;
			}
			//std::cout << "successiveTransformations with exponent " << currentExponent << ": " << successiveTransformations << std::endl;
			if (successiveTransformations == unsigned(carl::pow(2,_parameters->power)-1)) {
				std::cout << "Enough successive transformations: " << successiveTransformations << std::endl;
				reduced = true;
				currentExponent = currentExponent*(carl::pow(2,_parameters->power));
				std::cout << "After Reduction, new Exponent is " << currentExponent << std::endl;
				for(std::size_t i = 0; i < unsigned(carl::pow(2,_parameters->power)-1); i++ ){
					origin = origin.get()->linearTrafoParameters()->origin;
				}
				assert(origin.get()->type() != SF_TYPE::LINTRAFO || (origin.get()->linearTrafoParameters()->parameters == this->parameters && origin.get()->linearTrafoParameters()->currentExponent >= currentExponent) );
			}
		} while (reduced == true);
#endif
	}

	trafoContent( const trafoContent<Number>& _origin ) : origin( _origin.origin ), parameters(_origin.parameters), currentExponent(_origin.currentExponent), successiveTransformations( _origin.successiveTransformations )
	{}

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
	scaleContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, Number _factor )
		: origin( _origin ), factor( _factor ) {}
	scaleContent( const scaleContent<Number>& _origin ) : origin( _origin.origin ), factor( _origin.factor ) {}
};

template <typename Number>
struct unionContent {
	std::shared_ptr<SupportFunctionContent<Number>> lhs;
	std::shared_ptr<SupportFunctionContent<Number>> rhs;
	unionContent( std::shared_ptr<SupportFunctionContent<Number>> _lhs, std::shared_ptr<SupportFunctionContent<Number>> _rhs )
		: lhs( _lhs ), rhs( _rhs ) {}
	unionContent( const unionContent<Number>& _origin ) : lhs( _origin.lhs ), rhs( _origin.rhs ) {}
};

template <typename Number>
struct intersectionContent {
	std::shared_ptr<SupportFunctionContent<Number>> lhs;
	std::shared_ptr<SupportFunctionContent<Number>> rhs;
	intersectionContent( std::shared_ptr<SupportFunctionContent<Number>> _lhs, std::shared_ptr<SupportFunctionContent<Number>> _rhs )
		: lhs( _lhs ), rhs( _rhs ) {}
	intersectionContent( const intersectionContent<Number>& _origin ) : lhs( _origin.lhs ), rhs( _origin.rhs ) {}
};

template<typename Number>
struct projectionContent {
	std::shared_ptr<SupportFunctionContent<Number>> origin;
	std::vector<unsigned> dimensions;
	projectionContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, const std::vector<unsigned>& _dimensions )
		: origin(_origin), dimensions(_dimensions) {}
	projectionContent( const projectionContent<Number>& _original ) : origin(_original.origin), dimensions(_original.dimensions) {}
};

/*
* This is the super class for all support function objects.
*/
template <typename Number>
class SupportFunctionContent {
  private:
	SF_TYPE mType;
	unsigned mDepth;
	unsigned mOperationCount;
	unsigned mDimension;
	union {
		sumContent<Number>* mSummands;
		trafoContent<Number>* mLinearTrafoParameters;
		scaleContent<Number>* mScaleParameters;
		unionContent<Number>* mUnionParameters;
		intersectionContent<Number>* mIntersectionParameters;
		projectionContent<Number>* mProjectionParameters;
		PolytopeSupportFunction<Number>* mPolytope;
		BallSupportFunction<Number>* mBall;
		EllipsoidSupportFunction<Number>* mEllipsoid;
	};

	std::weak_ptr<SupportFunctionContent<Number>> pThis;

	SupportFunctionContent( const matrix_t<Number>& _shapeMatrix, SF_TYPE _type = SF_TYPE::ELLIPSOID );
	SupportFunctionContent( Number _radius, SF_TYPE _type = SF_TYPE::INFTY_BALL );
	SupportFunctionContent( const matrix_t<Number>& _directions, const vector_t<Number>& _distances,
					 SF_TYPE _type = SF_TYPE::POLY );
	SupportFunctionContent( const std::vector<Halfspace<Number>>& _planes, SF_TYPE _type = SF_TYPE::POLY );
	SupportFunctionContent( const std::vector<Point<Number>>& _points, SF_TYPE _type = SF_TYPE::POLY );
	SupportFunctionContent( std::shared_ptr<SupportFunctionContent<Number>> _lhs, std::shared_ptr<SupportFunctionContent<Number>> _rhs,
					 SF_TYPE _type );
	SupportFunctionContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, const std::shared_ptr<const lintrafoParameters<Number>>& _parameters, SF_TYPE _type );
	SupportFunctionContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, const Number& _factor,
					 SF_TYPE _type = SF_TYPE::SCALE );
	SupportFunctionContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, const std::vector<unsigned>& dimensions, SF_TYPE _type = SF_TYPE::PROJECTION );

  public:
	SupportFunctionContent( const SupportFunctionContent<Number>& _orig );

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type, Number _radius ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _radius, _type ) );
		obj->pThis = obj;
		return obj;
	}	
        
	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type, matrix_t<Number> _shapeMatrix ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _shapeMatrix, _type ) );
		obj->pThis = obj;
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type, const matrix_t<Number>& _directions,
															const vector_t<Number>& _distances ) {
		auto obj =
			  std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _directions, _distances, _type ) );
		obj->pThis = obj;
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type,
															const std::vector<Halfspace<Number>>& _planes ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _planes, _type ) );
		obj->pThis = obj;
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type,
															const std::vector<Point<Number>>& _points ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _points, _type ) );
		obj->pThis = obj;
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( const std::shared_ptr<SupportFunctionContent<Number>>& orig ) {
		auto obj = std::make_shared<SupportFunctionContent<Number>>(*orig);
		obj->pThis = obj;
		return obj;
	}

	virtual ~SupportFunctionContent();

	std::shared_ptr<SupportFunctionContent<Number>>& operator=( const std::shared_ptr<SupportFunctionContent<Number>>& _orig ) ;

	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction ) const;
	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _directions ) const;

	std::size_t dimension() const;
	SF_TYPE type() const;
	unsigned depth() const;
	unsigned operationCount() const;
        
	/**
	 * Returns an approximation of the number of mv multiplications neccessary for an evaluation of the SF
	 */
	unsigned multiplicationsPerEvaluation() const;

	void forceLinTransReduction();

	Point<Number> supremumPoint() const;

	std::list<unsigned> collectProjections() const;

	// getter for the union types
	sumContent<Number>* summands() const;
	scaleContent<Number>* scaleParameters() const;
	trafoContent<Number>* linearTrafoParameters() const;
	unionContent<Number>* unionParameters() const;
	intersectionContent<Number>* intersectionParameters() const;
	projectionContent<Number>* projectionParameters() const;
	PolytopeSupportFunction<Number>* polytope() const;
	BallSupportFunction<Number>* ball() const;
	EllipsoidSupportFunction<Number>* ellipsoid() const;

	std::shared_ptr<SupportFunctionContent<Number>> project(const std::vector<unsigned>& dimensions) const;
	std::shared_ptr<SupportFunctionContent<Number>> linearTransformation( const std::shared_ptr<const lintrafoParameters<Number>>& parameters ) const;
	std::shared_ptr<SupportFunctionContent<Number>> minkowskiSum( std::shared_ptr<SupportFunctionContent<Number>> _rhs ) const;
	std::shared_ptr<SupportFunctionContent<Number>> intersect( std::shared_ptr<SupportFunctionContent<Number>> _rhs ) const;
	bool contains( const Point<Number>& _point ) const;
	bool contains( const vector_t<Number>& _point ) const;
	std::shared_ptr<SupportFunctionContent<Number>> unite( std::shared_ptr<SupportFunctionContent<Number>> _rhs ) const;
	std::shared_ptr<SupportFunctionContent<Number>> scale( const Number& _factor = 1 ) const;

	bool empty() const;

	void print() const;
	friend std::ostream& operator<<( std::ostream& lhs, const std::shared_ptr<SupportFunctionContent<Number>>& rhs ) {
		unsigned level = 0;
		std::cout << "Depth: " << rhs->mDepth << std::endl;
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

private:
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
				std::vector<SF_TYPE> tmpItems = mLinearTrafoParameters->origin->collectLevelEntries(level-1);
				items.insert(items.end(), tmpItems.begin(), tmpItems.end());
				return items;
			}
			case SF_TYPE::SCALE: {
				//std::cout << "Current: scale" << std::endl;
				std::vector<SF_TYPE> tmpItems = mScaleParameters->origin->collectLevelEntries(level-1);
				items.insert(items.end(), tmpItems.begin(), tmpItems.end());
				return items;
			}
			case SF_TYPE::SUM: {
				//std::cout << "Current: sum" << std::endl;
				std::vector<SF_TYPE> lhsItems = mSummands->lhs->collectLevelEntries(level-1);
				std::vector<SF_TYPE> rhsItems = mSummands->rhs->collectLevelEntries(level-1);
				items.insert(items.end(), lhsItems.begin(), lhsItems.end());
				items.insert(items.end(), rhsItems.begin(), rhsItems.end());
				return items;
			}
			case SF_TYPE::UNION: {
				//std::cout << "Current: union" << std::endl;
				std::vector<SF_TYPE> lhsItems = mUnionParameters->lhs->collectLevelEntries(level-1);
				std::vector<SF_TYPE> rhsItems = mUnionParameters->rhs->collectLevelEntries(level-1);
				items.insert(items.end(), lhsItems.begin(), lhsItems.end());
				items.insert(items.end(), rhsItems.begin(), rhsItems.end());
				return items;
			}
			case SF_TYPE::INTERSECT: {
				//std::cout << "Current: intersect" << std::endl;
				std::vector<SF_TYPE> lhsItems = mIntersectionParameters->lhs->collectLevelEntries(level-1);
				std::vector<SF_TYPE> rhsItems = mIntersectionParameters->rhs->collectLevelEntries(level-1);
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
				case SF_TYPE::UNION: {
					level += "UNION" + separator + "     " + separator;
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
