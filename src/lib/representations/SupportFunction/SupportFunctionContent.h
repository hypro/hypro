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
#include "../../config.h"

//#define SUPPORTFUNCTION_VERBOSE
//#define MULTIPLICATIONSUPPORTFUNCTION_VERBOSE

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
	matrix_t<Number> a;
	vector_t<Number> b;
	trafoContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, matrix_t<Number> _a, vector_t<Number> _b )
		: origin( _origin ), a( _a ), b( _b ) {}
	trafoContent( const trafoContent<Number>& _origin ) : origin( _origin.origin ), a( _origin.a ), b( _origin.b ) {}
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

/*
* This is the super class for all support function objects.
*/
template <typename Number>
class SupportFunctionContent {
  private:
	SF_TYPE mType;
	unsigned mDimension;
	union {
		sumContent<Number>* mSummands;
		trafoContent<Number>* mLinearTrafoParameters;
		scaleContent<Number>* mScaleParameters;
		unionContent<Number>* mUnionParameters;
		intersectionContent<Number>* mIntersectionParameters;
		PolytopeSupportFunction<Number>* mPolytope;
		BallSupportFunction<Number>* mBall;
	};

	std::weak_ptr<SupportFunctionContent<Number>> pThis;

	SupportFunctionContent( Number _radius, SF_TYPE _type = SF_TYPE::INFTY_BALL );
	SupportFunctionContent( const matrix_t<Number>& _directions, const vector_t<Number>& _distances,
					 SF_TYPE _type = SF_TYPE::POLY );
	SupportFunctionContent( const std::vector<Hyperplane<Number>>& _planes, SF_TYPE _type = SF_TYPE::POLY );
	SupportFunctionContent( std::shared_ptr<SupportFunctionContent<Number>> _lhs, std::shared_ptr<SupportFunctionContent<Number>> _rhs,
					 SF_TYPE _type );
	SupportFunctionContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, const matrix_t<Number>& _a,
					 const vector_t<Number>& _b, SF_TYPE _type );
	SupportFunctionContent( std::shared_ptr<SupportFunctionContent<Number>> _origin, const Number& _factor,
					 SF_TYPE _type = SF_TYPE::SCALE );

  public:
	SupportFunctionContent( const SupportFunctionContent<Number>& _orig );

	static  std::shared_ptr<SupportFunctionContent<Number>> create( SF_TYPE _type, Number _radius ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _radius, _type ) );
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
															const std::vector<Hyperplane<Number>>& _planes ) {
		auto obj = std::shared_ptr<SupportFunctionContent<Number>>( new SupportFunctionContent<Number>( _planes, _type ) );
		obj->pThis = obj;
		return obj;
	}

	static std::shared_ptr<SupportFunctionContent<Number>> create( const std::shared_ptr<SupportFunctionContent<Number>>& orig ) {
		auto obj = std::make_shared<SupportFunctionContent<Number>>(*orig);
                std::cout << "Old adress: " << &*orig << ", new adress: " << &*obj << "\n";
                std::cout << "Old object:" << "\n";
                orig->print();
                std::cout << "New object:" << "\n";
                obj->print();
		obj->pThis = obj;
		return obj;
	}

	virtual ~SupportFunctionContent();

	std::shared_ptr<SupportFunctionContent<Number>>& operator=( const std::shared_ptr<SupportFunctionContent<Number>>& _orig ) ;

	evaluationResult<Number> evaluate( const vector_t<Number>& _direction ) const;
	std::vector<evaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _directions ) const;

	std::size_t dimension() const;
	SF_TYPE type() const;

	// getter for the union types
	sumContent<Number>* summands() const;
	scaleContent<Number>* scaleParameters() const;
	trafoContent<Number>* linearTrafoParameters() const;
	unionContent<Number>* unionParameters() const;
	intersectionContent<Number>* intersectionParameters() const;
	PolytopeSupportFunction<Number>* polytope() const;
	BallSupportFunction<Number>* ball() const;

	std::shared_ptr<SupportFunctionContent<Number>> linearTransformation( const matrix_t<Number>& _A,
																   const vector_t<Number>& _b ) const;
	std::shared_ptr<SupportFunctionContent<Number>> minkowskiSum( std::shared_ptr<SupportFunctionContent<Number>> _rhs ) const;
	std::shared_ptr<SupportFunctionContent<Number>> intersect( std::shared_ptr<SupportFunctionContent<Number>> _rhs ) const;
	bool contains( const Point<Number>& _point ) const;
	bool contains( const vector_t<Number>& _point ) const;
	std::shared_ptr<SupportFunctionContent<Number>> unite( std::shared_ptr<SupportFunctionContent<Number>> _rhs ) const;

	std::shared_ptr<SupportFunctionContent<Number>> scale( const Number& _factor = 1 ) const;
	bool empty() const;

	void print() const;
	friend std::ostream& operator<<( std::ostream& lhs, const std::shared_ptr<SupportFunctionContent<Number>>& rhs ) {
		switch ( rhs->mType ) {
			case SF_TYPE::INFTY_BALL: {
				lhs << "INFTY-BALL" << std::endl;
			} break;
			case SF_TYPE::TWO_BALL: {
				lhs << "2-BALL" << std::endl;
			} break;
			case SF_TYPE::LINTRAFO: {
				lhs << "LINTRAFO" << std::endl;
				lhs << "of" << std::endl;
				rhs->mLinearTrafoParameters->origin->print();
			} break;
			case SF_TYPE::POLY: {
				lhs << "POLY" << std::endl;
	            rhs->mPolytope->print();
			} break;
			case SF_TYPE::SCALE: {
				lhs << "SCALE" << std::endl;
			} break;
			case SF_TYPE::SUM: {
				lhs << "SUM" << std::endl;
				lhs << "of: " << std::endl;
				rhs->mSummands->rhs->print();
				lhs << "and" << std::endl;
				rhs->mSummands->lhs->print();
			} break;
			case SF_TYPE::UNION: {
				lhs << "UNION" << std::endl;
			} break;
			case SF_TYPE::INTERSECT: {
				lhs << "INTERSECTION " << std::endl;
				lhs << "of" << std::endl;
				rhs->mIntersectionParameters->lhs->print();
				lhs << "and" << std::endl;
				rhs->mIntersectionParameters->rhs->print();
			} break;
			default:
				lhs << "NONE" << std::endl;
		}
		return lhs;
	}
};
}  // namespace

#include "SupportFunctionContent.tpp"
