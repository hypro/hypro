/*
 * This file containts the implementation of support functions. It requires the concrete
 * implementation of set representations as support functions for a successful evaluation
 * as it implements the chain of operations created during reachability analysis.
 * @file SupportFunction.h
 * 
 * @author Norman Hansen
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @version	2015-02-27
 */

#pragma once 

#include "../../config.h"
#include "util.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "PolytopeSupportFunction.h"
#include "BallSupportFunction.h"
#include <glpk.h>
#include <vector>

//#define SUPPORTFUNCTION_VERBOSE
//#define MULTIPLICATIONSUPPORTFUNCTION_VERBOSE

namespace hypro
{
	template<typename Number>
	class SupportFunction;
	
	template<typename Number>
	struct sumContent{
		std::shared_ptr<SupportFunction<Number>> lhs;
		std::shared_ptr<SupportFunction<Number>> rhs;
		sumContent(std::shared_ptr<SupportFunction<Number>> _lhs, std::shared_ptr<SupportFunction<Number>> _rhs) : lhs(_lhs), rhs(_rhs) {}
		sumContent(const sumContent<Number>& _origin) : lhs(_origin.lhs), rhs(_origin.rhs) {}
	};
	
	template<typename Number>
	struct trafoContent{
		std::shared_ptr<SupportFunction<Number>> origin;
		matrix_t<Number> a;
		vector_t<Number> b;
		trafoContent(std::shared_ptr<SupportFunction<Number>> _origin, matrix_t<Number> _a, vector_t<Number> _b) : origin(_origin), a(_a), b(_b) {}
		trafoContent(const trafoContent<Number>& _origin) : origin(_origin.origin), a(_origin.a), b(_origin.b) {}
	};
	
	template<typename Number>
	struct scaleContent{
		std::shared_ptr<SupportFunction<Number>> origin;
		Number factor;
		scaleContent(std::shared_ptr<SupportFunction<Number>> _origin, Number _factor) : origin(_origin), factor(_factor) {}
		scaleContent(const scaleContent<Number>& _origin) : origin(_origin.origin), factor(_origin.factor) {}
	};
	
	template<typename Number>
	struct unionContent{
		std::shared_ptr<SupportFunction<Number>> lhs;
		std::shared_ptr<SupportFunction<Number>> rhs;
		unionContent(std::shared_ptr<SupportFunction<Number>> _lhs, std::shared_ptr<SupportFunction<Number>> _rhs) : lhs(_lhs), rhs(_rhs) {}
		unionContent(const unionContent<Number>& _origin) : lhs(_origin.lhs), rhs(_origin.rhs) {}
	};
	
	template<typename Number>
	struct intersectionContent{
		std::shared_ptr<SupportFunction<Number>> lhs;
		std::shared_ptr<SupportFunction<Number>> rhs;
		intersectionContent(std::shared_ptr<SupportFunction<Number>> _lhs, std::shared_ptr<SupportFunction<Number>> _rhs) : lhs(_lhs), rhs(_rhs) {}
		intersectionContent(const intersectionContent<Number>& _origin) : lhs(_origin.lhs), rhs(_origin.rhs) {}
	};
	
	/*
	* This is the super class for all support function objects.
	*/
	template<typename Number>
	class SupportFunction
	{
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

			std::weak_ptr<SupportFunction<Number>> pThis;
		   
			
			SupportFunction(SF_TYPE _type, Number _radius);
			SupportFunction(SF_TYPE _type, const matrix_t<Number>& _directions, const vector_t<Number>& _distances);
			SupportFunction(SF_TYPE _type, const std::vector<Hyperplane<Number>>& _planes);
			SupportFunction(SF_TYPE _type, std::shared_ptr<SupportFunction<Number>> _lhs, std::shared_ptr<SupportFunction<Number>> _rhs);
			SupportFunction(SF_TYPE _type, std::shared_ptr<SupportFunction<Number>> _origin, const matrix_t<Number>& _a, const vector_t<Number>& _b = vector_t<Number>());
			SupportFunction(SF_TYPE _type, std::shared_ptr<SupportFunction<Number>> _origin, const Number& _factor);
		
		public:
			SupportFunction(const SupportFunction<Number>& _orig);

			static std::shared_ptr<SupportFunction<Number>> create(SF_TYPE _type, Number _radius){
				auto obj = std::shared_ptr<SupportFunction<Number>>(new SupportFunction<Number>(_type,_radius));
				obj->pThis = obj;
				return obj;
			}

			static std::shared_ptr<SupportFunction<Number>> create(SF_TYPE _type, const matrix_t<Number>& _directions, const vector_t<Number>& _distances) {
				auto obj = std::shared_ptr<SupportFunction<Number>>(new SupportFunction<Number>(_type,_directions,_distances));
				obj->pThis = obj;
				return obj;
			}

			static std::shared_ptr<SupportFunction<Number>> create(SF_TYPE _type, const std::vector<Hyperplane<Number>>& _planes) {
				auto obj = std::shared_ptr<SupportFunction<Number>>(new SupportFunction<Number>(_type,_planes));
				obj->pThis = obj;
				return obj;
			}

			virtual ~SupportFunction();
			
			std::shared_ptr<SupportFunction<Number>> operator=(std::shared_ptr<SupportFunction<Number>> _orig);
			
			evaluationResult<Number> evaluate(const vector_t<Number>& _direction) const;
			vector_t<Number> multiEvaluate(const matrix_t<Number>& _directions) const;
			
			unsigned dimension() const;
			SF_TYPE type() const;
			
			// getter for the union types
			sumContent<Number>* summands() const;
			scaleContent<Number>* scaleParameters() const;
			trafoContent<Number>* linearTrafoParameters() const;
			unionContent<Number>* unionParameters() const;
			intersectionContent<Number>* intersectionParameters() const;
			PolytopeSupportFunction<Number>* polytope() const;
			BallSupportFunction<Number>* ball() const;
		
			std::shared_ptr<SupportFunction<Number>> linearTransformation(const matrix_t<Number>& _A, const vector_t<Number>& _b = vector_t<Number>()) const;
			std::shared_ptr<SupportFunction<Number>> minkowskiSum(std::shared_ptr<SupportFunction<Number>> _rhs) const;
			std::shared_ptr<SupportFunction<Number>> intersect(std::shared_ptr<SupportFunction<Number>> _rhs) const;
			bool contains(const Point<Number>& _point) const;
			bool contains(const vector_t<Number>& _point) const; 
			std::shared_ptr<SupportFunction<Number>> unite(std::shared_ptr<SupportFunction<Number>> _rhs) const;
			
			std::shared_ptr<SupportFunction<Number>> scale(const Number& _factor = 1) const;
			bool isEmpty() const;

			void print() const;
	};
} // namespace

#include "SupportFunction.tpp"
