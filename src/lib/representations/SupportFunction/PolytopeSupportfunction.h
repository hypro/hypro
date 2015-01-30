/*
 *  This file contains everything related directly to support functions of polyhedra and their evaluation
 *  Author: Norman Hansen
 */
 
#pragma once 
 
//#define SUPPORTFUNCTION_VERBOSE 
//#define PPOLYTOPESUPPORTFUNCTION_VERBOSE

//#include "hyreach_utils.h" 
#include "SupportFunction.h"
    
namespace hypro
{         
    /*
    * This class defines a support Function object representing a polytope (might not be closed)
    * SupportFunctions can be evaluated in a specified direction l and return a correspondent evaluationResult
    */
	template<typename Number>
    class PolytopeSupportFunction : public SupportFunction<Number>{
    
    	private:
    		
    		glp_prob *lp;
    		int* ia;
            int* ja;
    		double* ar;
    		
    		void createArrays(unsigned int size);
    		void deleteArrays();
    		
    		/**
            * Implements the functionality of the constructor. Used by both "real" constructors of this class
            */
            void initialize(matrix_t<Number> constraints, matrix_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality);
            
       protected:
            /*
        	* This method computes the evaluation result for a specified direction l
        	*/
        	evaluationResult<Number> specificEvaluation(matrix_t<Number> l);
            
        public:
			
    	/*
    	* Creates a new supportFunction for the closed convex set described by constraints * x operation(>= or <=) constraintConstants
    	*/
    	PolytopeSupportFunction(matrix_t<Number> constraints, matrix_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality, artificialDirections<Number>* aD);
    	PolytopeSupportFunction(matrix_t<Number> constraints, vector_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality, artificialDirections<Number>* aD);
        
        // supports only <= operator by design -> !!!! See first std::cout !!!!
        PolytopeSupportFunction(std::vector<matrix_t<Number>>* constraints, matrix_t<Number> constraintConstants, unsigned int dimensionality, artificialDirections<Number>* aD);
    	       
        // destructor
    	~PolytopeSupportFunction();
    };
} // namespace
#include "PolytopeSupportFunction.tpp"
