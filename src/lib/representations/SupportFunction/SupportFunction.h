/*
 *  This file contains the abstract super class for support function representations
 *  Author: Norman Hansen
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 */

#pragma once 

//#include "hyreach_utils.h" 
#include "../../config.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "vectorgenerator.h"
#include "helperMethods.h"
#include <glpk.h>
#include <vector>

//#define SUPPORTFUNCTION_VERBOSE
//#define MULTIPLICATIONSUPPORTFUNCTION_VERBOSE

namespace hypro
{
    // This enum represents the support function type and is used to identify support function without instanceof operations
    enum SF_TYPE{SUM, LINTRAFO, SCALE, UNION, POLY};
	
	template<typename Number>
	class PolytopeSupportFunction;
	
    /*
    * This structure describes the result of a support function evaluation
    */
	template<typename Number>
    struct evaluationResult {
    	Number supportValue;	// the value returned by the support function evaluation
    	vector_t<Number> optimumValue;	// the point leading to the support function value (extremum in direction)
    	int errorCode; 	// potential error code indicating success or failure of the evaluation
    
        /*  Potential error codes are:
            
         *  General:
         *  -1000  in case the support function object does not implement a proper evaluate function   
            
         *  For polytopes:
                
         *  GLP_OPT
         *  GLP_FEAS
         *  GLP_INFEAS
         *  GLP_NOFEAS
         *  GLP_UNBND
         *  GLP_UNDEF
         
         * For NonLinear:  // TODO: add error status
         */
    };
	
	template<typename Number>
	class SupportFunction;
	
	template<typename Number>
	struct sumContent{
		SupportFunction<Number>* lhs;
		SupportFunction<Number>* rhs;
	};
	
	template<typename Number>
	struct trafoContent{
		SupportFunction<Number>* origin;
		matrix_t<Number> a;
		vector_t<Number> b;
	};
	
	template<typename Number>
	struct scaleContent{
		SupportFunction<Number>* origin;
		Number factor;
	};
	
	template<typename Number>
	struct unionContent{
		SupportFunction<Number>* lhs;
		SupportFunction<Number>* rhs;
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
				PolytopeSupportFunction<Number>* mPolytope;
			};

		public:
           
			SupportFunction(SF_TYPE _type, const matrix_t<Number>& _directions, const vector_t<Number>& _distances);
			SupportFunction(SF_TYPE _type, SupportFunction<Number>* _lhs, SupportFunction<Number>* _rhs);
			SupportFunction(SF_TYPE _type, SupportFunction<Number>* _origin, const matrix_t<Number>& _a, const vector_t<Number>& _b = vector_t<Number>());
			SupportFunction(SF_TYPE _type, SupportFunction<Number>* _origin, const Number& _factor);
			
			virtual ~SupportFunction();
			
			evaluationResult<Number> evaluate(const vector_t<Number>& _direction) const;
			vector_t<Number> multiEvaluate(const std::vector<vector_t<Number>>& _directions) const;
			
			unsigned dimension() const;
			SF_TYPE type() const;
		
			SupportFunction<Number>* linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b = vector_t<Number>()) const;
			SupportFunction<Number>* minkowskiSum(SupportFunction<Number>* rhs) const;
			SupportFunction<Number>* intersect(SupportFunction<Number>* rhs) const;
			bool contains(const Point<Number>& point) const;
			SupportFunction<Number>* unite(SupportFunction<Number>* rhs) const;
    };
} // namespace
