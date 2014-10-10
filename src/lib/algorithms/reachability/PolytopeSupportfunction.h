/*
 *  This file contains everything related directly to support functions of polyhedra and their evaluation
 *  Author: Norman Hansen
 */
 
#pragma once 
 
//#define PPOLYTOPESUPPORTFUNCTION_VERBOSE
#include "hyreach_utils.h" 
    
namespace hypro
{         
    /*
    * This class defines a support Function object representing a polytope (might not be closed)
    * SupportFunctions can be evaluated in a specified direction l and return a correspondent evaluationResult
    */
    class PolytopeSupportFunction : public SupportFunction{
    
    	private:
    		matrix_t<double> constraints;	// matrix describing constraints of a closed convex polyhedra
    		matrix_t<double> constraintConstants;	// vector describing constraints of a closed closed convex polyhedra
    
    		glp_prob *lp;
    		int ia[1 + 1000], ja[1 + 1000];
    		double ar[1 + 1000];
    
            /**
            * Implements the functionality of the constructor. Used by both "real" constructors of this class
            */
            void initialize(matrix_t<double> constraints, matrix_t<double> constraintConstants, operator_e operation, unsigned int dimensionality)
            {
                 #ifdef SUPPORTFUNCTION_VERBOSE
    		         #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
    			       std::string method = "PolytopeSupportFunction:";
                     #endif
                 #endif
    
        		// TODO: depending on the operator, invert constraints
        		(*this).constraints = constraints;
        		(*this).constraintConstants = constraintConstants;
        
        		#ifdef SUPPORTFUNCTION_VERBOSE
        		    #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
        			    std::cout << method << " copied constraint pointers" << '\n';
        			#endif
        		#endif
    
        		/* create glpk problem */
        		lp = glp_create_prob();
        		glp_set_prob_name(lp, "supportfunction");
        		glp_set_obj_dir(lp, GLP_MAX);
    
                int numberOfConstraints = constraints.rows();
                #ifdef SUPPORTFUNCTION_VERBOSE
        		    #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
                		// check dimensionalities
                		int numberOfConstraintConstant = constraintConstants.size();
                		if (numberOfConstraints != numberOfConstraintConstant)
                		{
                			std::cout << method << " incompatible number of constraints and correspondent values";
                		}
                		
                		if (constraints.cols() != dimensionality)
                		{
                			std::cout << method << " constraints are of invalid dimensionality";
                		}
                    #endif
        		#endif
    		
        		// convert constraint constants
        		glp_add_rows(lp, numberOfConstraints);
        
        		#ifdef SUPPORTFUNCTION_VERBOSE
        		    #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
        			    std::cout << method << " Constructed GLPK problem" << '\n' << "dimensionality: " << dimensionality << '\n';
        			#endif
        		#endif
        
        		for (int i = 0; i < numberOfConstraints; i++)
        		{
        			glp_set_row_bnds(lp, i + 1, GLP_UP, 0.0, constraintConstants(i).toDouble());
        		}
    		
        		// add cols here
        		glp_add_cols(lp, dimensionality);
        
        		#ifdef SUPPORTFUNCTION_VERBOSE
        		    #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
        			    std::cout << method << " added constraints (values)" << '\n';
        			#endif
        		#endif
        
        		// convert constraint matrix
        		for (int i = 0; i < constraints.size(); i++)
        		{
        			ia[i+1] = ((int)(i / dimensionality))+1;
        
        			#ifdef SUPPORTFUNCTION_VERBOSE
        			    #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
        				    std::cout << method << " index i: " << ia[i+1]  << '\n';
    			        #endif
        			#endif
        			ja[i+1] = ((int)(i%dimensionality))+1;
        
        			#ifdef SUPPORTFUNCTION_VERBOSE
        			    #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
        				    std::cout << method << " index j: " << ja[i+1] << '\n';
        				#endif
        			#endif
        			ar[i+1] = constraints((int)(i / dimensionality), (int)(i%dimensionality)).toDouble();
        
        			#ifdef SUPPORTFUNCTION_VERBOSE
        			    #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
        				    std::cout << method << " value: " << ar[i+1] << '\n';
        				#endif
        			#endif
        		}
    
        		#ifdef SUPPORTFUNCTION_VERBOSE
        		    #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
        			    std::cout << method << " terminated matrix construction" << '\n';
        			    std::cout << method << " number of matrix elements: " << constraints.size() << '\n';
        			    std::cout << "ia: " << ia << '\n';
        			    std::cout << "ja: " << ja << '\n';
        			    std::cout << "ar: " << ar << '\n';
        			#endif
        		#endif
        
        		glp_load_matrix(lp, constraints.size(), ia, ja, ar);
        		
        		#ifdef SUPPORTFUNCTION_VERBOSE
        		    #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
        			    std::cout << method << " added constraints (matrix)" << '\n';
       			    #endif
        		#endif
            }
            
        public:
    
    	/*
    	* Creates a new supportFunction for the closed convex set described by constraints * x operation(>= or <=) constraintConstants
    	*/
    	PolytopeSupportFunction(matrix_t<double> constraints, matrix_t<double> constraintConstants, operator_e operation, unsigned int dimensionality) : SupportFunction(SupportFunctionType::Polytope_Type)
    	{          
            // call constructor functionality                                      
    		initialize(constraints, constraintConstants, operation, dimensionality);
    	}
    	
    	PolytopeSupportFunction(matrix_t<double> constraints, vector_t<double> constraintConstants, operator_e operation, unsigned int dimensionality) : SupportFunction(SupportFunctionType::Polytope_Type)
    	{
             // transform vector_t into matrix_t
       /*      matrix_t<double> constraintConstantsMatrix(constraints.rows(),1);
             unsigned int count = 0;
             for(auto iterator = constraintConstants.begin(); iterator != constraintConstants.end(); ++iterator)
             {
                 constraintConstantsMatrix(count,0) = iterator->second;
                 count++;
             }
       */      
             // call constructor functionality
             initialize(constraints, constraintConstants, operation, dimensionality);
        }
    	
    	/**
    	* This method computes the evaluation result for a specified direction l
    	*/
    	evaluationResult evaluate(matrix_t<double> l)
    	{
            #ifdef SUPPORTFUNCTION_VERBOSE
    		    #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
    			    std::cout << "PolytopeSupportFunction: evaluate" << '\n';
   			    #endif
    		#endif             
    		int dimensions = l.size();
    			
    		for (int i = 0; i < dimensions; i++)
    		{
    			glp_set_col_bnds(lp, i+1, GLP_FR, 0.0, 0.0);
    			glp_set_obj_coef(lp, i+1, l(i,0).toDouble());
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
                   #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
    		           printf("fx = %g; x = ", result.supportValue);
    		           std::cout << x;
    		           std::cout << '\n' << "size x: " << x.size() << '\n';
    		       #endif
            #endif
            
    		return result;
    	}
              
        // destructor
    	~PolytopeSupportFunction()
    	{
            #ifdef SUPPORTFUNCTION_VERBOSE
                #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
    		        std::cout << "PolytopeSupportFunction: destructor" << '\n';
    		    #endif
            #endif
            
            // free glpk resources
    		glp_delete_prob(lp);
    		
    		#ifdef SUPPORTFUNCTION_VERBOSE
    		    #ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
    			    std::cout << "PolytopeSupportFunction: destructor - complete" << '\n';
	            #endif
	        #endif 
    	}
    };
}
