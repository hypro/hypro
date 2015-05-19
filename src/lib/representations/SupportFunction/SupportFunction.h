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
		const SupportFunction<Number>& lhs;
		const SupportFunction<Number>& rhs;
		sumContent(const SupportFunction<Number>& _lhs, const SupportFunction<Number>& _rhs) : lhs(_lhs), rhs(_rhs) {}
	};
	
	template<typename Number>
	struct trafoContent{
		const SupportFunction<Number>& origin;
		matrix_t<Number> a;
		vector_t<Number> b;
		trafoContent(const SupportFunction<Number>& _origin, matrix_t<Number> _a, vector_t<Number> _b) : origin(_origin), a(_a), b(_b) {}
	};
	
	template<typename Number>
	struct scaleContent{
		const SupportFunction<Number>& origin;
		Number factor;
		scaleContent(const SupportFunction<Number>& _origin, Number _factor) : origin(_origin), factor(_factor) {}
	};
	
	template<typename Number>
	struct unionContent{
		const SupportFunction<Number>& lhs;
		const SupportFunction<Number>& rhs;
		unionContent(const SupportFunction<Number>& _lhs, const SupportFunction<Number>& _rhs) : lhs(_lhs), rhs(_rhs) {}
	};
	
	template<typename Number>
	struct intersectionContent{
		const SupportFunction<Number>& lhs;
		const SupportFunction<Number>& rhs;
		intersectionContent(const SupportFunction<Number>& _lhs, const SupportFunction<Number>& _rhs) : lhs(_lhs), rhs(_rhs) {}
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
				std::shared_ptr<PolytopeSupportFunction<Number>> mPolytope;
				std::shared_ptr<BallSupportFunction<Number>> mBall;
			};

		public:
		   
			SupportFunction(const SupportFunction<Number>& _orig);
			SupportFunction(SF_TYPE _type, Number _radius);
			SupportFunction(SF_TYPE _type, const matrix_t<Number>& _directions, const vector_t<Number>& _distances);
			SupportFunction(SF_TYPE _type, const std::vector<Hyperplane<Number>>& _planes);
			SupportFunction(SF_TYPE _type, const SupportFunction<Number>& _lhs, const SupportFunction<Number>& _rhs);
			SupportFunction(SF_TYPE _type, const SupportFunction<Number> _origin, const matrix_t<Number>& _a, const vector_t<Number>& _b = vector_t<Number>());
			SupportFunction(SF_TYPE _type, const SupportFunction<Number>& _origin, const Number& _factor);
			
			virtual ~SupportFunction();
			
			SupportFunction& operator=(const SupportFunction& _orig);
			
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
			std::shared_ptr<PolytopeSupportFunction<Number>> polytope() const;
			std::shared_ptr<BallSupportFunction<Number>> ball() const;
		
			SupportFunction<Number> linearTransformation(const matrix_t<Number>& _A, const vector_t<Number>& _b = vector_t<Number>()) const;
			SupportFunction<Number> minkowskiSum(const SupportFunction<Number>& _rhs) const;
			SupportFunction<Number> intersect(const SupportFunction<Number>& _rhs) const;
			bool contains(const Point<Number>& _point) const;
			bool contains(const vector_t<Number>& _point) const; 
			SupportFunction<Number> unite(const SupportFunction<Number>& _rhs) const;
			
			SupportFunction<Number> scale(const Number& _factor = 1) const;
			bool isEmpty() const;

		//private:
		//	void clear();
	};
} // namespace

#include "SupportFunction.tpp"
