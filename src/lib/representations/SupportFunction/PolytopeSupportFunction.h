/*
 *  This file contains everything related directly to support functions of polyhedra and their evaluation
 *  Author: Norman Hansen
 */
 
#pragma once 
 
//#define SUPPORTFUNCTION_VERBOSE 
//#define PPOLYTOPESUPPORTFUNCTION_VERBOSE

#include "../../config.h"
#include "SupportFunction.h"
#include <glpk.h>
    
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
    		
    		void createArrays(unsigned int size);
    		void deleteArrays();
			
			unsigned int mDimension;
    		
    		/**
            * Implements the functionality of the constructor. Used by both "real" constructors of this class
            */
            void initialize(matrix_t<Number> constraints, vector_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality);
            
       public:
		/*
		* This method computes the evaluation result for a specified direction l
		*/
		evaluationResult<Number> evaluate(const vector_t<Number>& l) const;
            
    	/*
    	* Creates a new supportFunction for the closed convex set described by constraints * x operation(>= or <=) constraintConstants
    	*/
    	PolytopeSupportFunction(matrix_t<Number> constraints, matrix_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality, artificialDirections<Number>* aD);
    	PolytopeSupportFunction(matrix_t<Number> constraints, vector_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality, artificialDirections<Number>* aD);
   
        // destructor
    	~PolytopeSupportFunction();
		
		/**
		* Returns the dimension of this object.
		* 
		* @return  the dimension
		*/
        unsigned int dimension();
    };
} // namespace
#include "PolytopeSupportFunction.tpp"
