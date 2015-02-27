/*
 * This file contains the basic implementation of support functions of polyhedra (template polyhedra) and their evaluation.
 * @file PolytopeSupportFunction.h
 * 
 * @author Norman Hansen
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @version	2015-02-27
 */
 
#pragma once 

#include "../../config.h"
#include "util.h"
#include <glpk.h>

#ifdef SUPPORTFUNCTION_VERBOSE
	//#define PPOLYTOPESUPPORTFUNCTION_VERBOSE
#endif

namespace hypro
{
	
    /*
    * This class defines a support Function object representing a polytope (might not be closed)
    * SupportFunctions can be evaluated in a specified direction l and return a correspondent evaluationResult
    */
	template<typename Number>
    class PolytopeSupportFunction{
    
    	private:
    		
    		glp_prob *lp;
    		int* ia;
            int* ja;
    		double* ar;
    		
    		void createArrays(unsigned size);
    		void deleteArrays();
			
			unsigned mDimension;
    		
    		/**
			 * Initializes the class by setting up the glpk problem with the given parameters.
             * @param constraints
             * @param constraintConstants
             */
            void initialize(matrix_t<Number> constraints, vector_t<Number> constraintConstants);
            
       public:
		
    	PolytopeSupportFunction(matrix_t<Number> constraints, vector_t<Number> constraintConstants);
    	~PolytopeSupportFunction();
		
		/**
		 * Returns the dimension of the object.
         * @return 
         */
        unsigned dimension() const;
		
		/**
		 * Evaluates the support function in the given direction.
		 * @param l
		 * @return
		 */
		evaluationResult<Number> evaluate(const vector_t<Number>& l) const;
		
		bool empty() const;
    };
} // namespace
#include "PolytopeSupportFunction.tpp"
