/*
 *  This file contains everything related directly to support functions and their evaluation
 *  Author: Norman Hansen
 */

//#define SUPPORTFUNCTION_VERBOSE
 
#include "hyreach_utils.h" 

// GLPK includes
#include <stdio.h>            /* C input/output                       */
#include <stdlib.h>           /* C standard library                   */
#include <glpk.h>             /* GNU GLPK linear/mixed integer solver */
    
namespace hypro
{     
    /*
    * This structure describes the result of a support function evaluation
    */
    struct evaluationResult {
    	double supportValue;	// the value returned by the support function evaluation
    	matrix_t<double> optimumValue;	// the point leading to the support function value (extremum in direction)
    	int errorCode; 	// potential error code indicating success or failure of the evaluation
    
        /*  Potential error codes are:
         *  GLP_OPT
         *  GLP_FEAS
         *  GLP_INFEAS
         *  GLP_NOFEAS
         *  GLP_UNBND
         *  GLP_UNDEF
         */
    };
    
    /*
    * This class defines a support Function object
    * SupportFunctions can be evaluated in a specified direction l and return a correspondent evaluationResult
    */
    class SupportFunction {
    
    	private:
    		matrix_t<double> constraints;	// matrix describing constraints of a closed convex polyhedra
    		matrix_t<double> constraintConstants;	// vector describing constraints of a closed closed convex polyhedra
    
    		glp_prob *lp;
    		int ia[1 + 1000], ja[1 + 1000];
    		double ar[1 + 1000];
    
        public:
    
    	/*
    	* Creates a new supportFunction for the closed convex set described by constraints * x operation(>= or <=) constraintConstants
    	*/
    	SupportFunction(matrix_t<double> constraints, matrix_t<double> constraintConstants, operator_e operation, int dimensionality)
    	{
    		#ifdef SUPPORTFUNCTION_VERBOSE
    			string method = "Supportfunction:";
    		#endif
    
    		// TODO: depending on the operator, invert constraints
    		(*this).constraints = constraints;
    		(*this).constraintConstants = constraintConstants;
    
    		#ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << method << " copied constraint pointers" << '\n';
    		#endif
    
    		/* create glpk problem */
    		lp = glp_create_prob();
    		glp_set_prob_name(lp, "supportfunction");
    		glp_set_obj_dir(lp, GLP_MAX);
    
    		// check dimensionalities
    		int numberOfConstraints = constraints.rows();
    		int numberOfConstraintConstant = constraintConstants.size();
    		if (numberOfConstraints != numberOfConstraintConstant)
    		{
    			std::cout << "Supportfunction: incompatible number of constraints and correspondent values";
    		}
    
    		// convert constraint constants
    		glp_add_rows(lp, numberOfConstraints);
    
    		#ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << method << " Constructed GLPK problem" << '\n' << "dimensionality: " << dimensionality << '\n';
    		#endif
    
    		for (int i = 0; i < numberOfConstraints; i++)
    		{
    			glp_set_row_bnds(lp, i + 1, GLP_UP, 0.0, constraintConstants(i));
    		}
    		
    		// add cols here
    		glp_add_cols(lp, dimensionality);
    
    		#ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << method << " added constraints (values)" << '\n';
    		#endif
    
    		// convert constraint matrix
    		for (int i = 0; i < constraints.size(); i++)
    		{
    			ia[i+1] = ((int)(i / dimensionality))+1;
    
    			#ifdef SUPPORTFUNCTION_VERBOSE
    				std::cout << method << " index i: " << ia[i+1]  << '\n';
    			#endif
    			ja[i+1] = ((int)(i%dimensionality))+1;
    
    			#ifdef SUPPORTFUNCTION_VERBOSE
    				std::cout << method << " index j: " << ja[i+1] << '\n';
    			#endif
    			ar[i+1] = constraints((int)(i / dimensionality), (int)(i%dimensionality));
    
    			#ifdef SUPPORTFUNCTION_VERBOSE
    				std::cout << method << " value: " << ar[i+1] << '\n';
    			#endif
    		}
    
    		#ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << method << " terminated matrix construction" << '\n';
    			std::cout << method << " number of matrix elements: " << constraints.size() << '\n';
    			std::cout << "ia: " << ia << '\n';
    			std::cout << "ja: " << ja << '\n';
    			std::cout << "ar: " << ar << '\n';
    		#endif
    
    		glp_load_matrix(lp, constraints.size(), ia, ja, ar);
    		
    		#ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << method << " added constraints (matrix)" << '\n';
    		#endif
    	}
    	
    	/**
    	* This method computes the evaluation result for a specified direction l
    	*/
    	evaluationResult evaluate(matrix_t<double> l)
    	{
    		int dimensions = l.size();
    			
    		for (int i = 0; i < dimensions; i++)
    		{
    			glp_set_col_bnds(lp, i+1, GLP_FR, 0.0, 0.0);
    			glp_set_obj_coef(lp, i+1, l(i));
    		}
    
    
    		/* solve problem */
    		glp_simplex(lp, NULL);
    
    		evaluationResult result;
    
    		/* recover and display results */
    		result.supportValue = glp_get_obj_val(lp);
    
    		matrix_t<double> x(dimensions, 1);
    		for (int i = 0; i < dimensions; i++)
    		{
    			x(i) = glp_get_col_prim(lp, i+1);
    		}
            result.optimumValue = x;
            result.errorCode = glp_get_status(lp);
            
            // display potential problems
            switch(result.errorCode)
            {
                case GLP_OPT:
                case GLP_FEAS:
                     break;
                case GLP_UNBND:
                     result.supportValue = INFINITY;
                     break;
                default: 
                     std::cout << "Unable to find a suitable solution for the support function (linear program)";             
            }
            
            #ifdef SUPPORTFUNCTION_VERBOSE
    		       printf("fx = %g; x = ", result.supportValue);
    		       std::cout << x;
    		       std::cout << '\n' << "size x: " << x.size() << '\n';
            #endif
            
    		return result;
    	}
    
    	~SupportFunction()
    	{
    		glp_delete_prob(lp);
    		glp_free_env();
    	}
    };
}
