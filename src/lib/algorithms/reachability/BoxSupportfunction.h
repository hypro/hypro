/*
 *  This file contains everything related directly to support functions of symmetric boxes and their evaluation
 *  Author: Norman Hansen
 */
#pragma once
 
#include "hyreach_utils.h" 

#define SUPPORTFUNCTION_VERBOSE
//#define BOXSUPPORTFUNCTION_VERBOSE

namespace hypro
{         
    /*
    * This class defines a support Function object representing a polytope (might not be closed)
    * SupportFunctions can be evaluated in a specified direction l and return a correspondent evaluationResult
    */
    class SymmetricCenteredBoxSupportFunction : public SupportFunction{
          private:
                  
             matrix_t<double> e;        
             matrix_t<double> e_t; // e is stored in transposed format
          
          public:
                 
             SymmetricCenteredBoxSupportFunction(matrix_t<double> e): SupportFunction(SupportFunctionType::Box_Type)
             {
                 #ifdef SUPPORTFUNCTION_VERBOSE
                     #ifdef BOXSUPPORTFUNCTION_VERBOSE
                     std::cout << "SymmetricCenteredBoxSupportFunction: constructor" << '\n';
                     #endif
                 #endif
                 this-> e = e;
                 this-> e_t = e.transpose();
             }    
             
             /**
 	          * This method computes the evaluation result for a specified direction l
    	      */
       	     evaluationResult evaluate(matrix_t<double> l)
        	 {
                 #ifdef SUPPORTFUNCTION_VERBOSE
                     #ifdef BOXSUPPORTFUNCTION_VERBOSE
                         std::cout << "SymmetricCenteredBoxSupportFunction: evaluate" << '\n';
                         std::cout << "e_t: " << e_t << '\n';
                         std::cout << "abs(l): " << (l.array().abs()).matrix() << '\n';
                     #endif
                 #endif
                 
                 evaluationResult result;
                 result.errorCode = 1;
                 
                 matrix_t<double> temp = e_t * (l.array().abs()).matrix();   
                             
                 result.supportValue =  temp(0);
                 result.optimumValue = l*temp;
                 
                 #ifdef SUPPORTFUNCTION_VERBOSE
                     #ifdef BOXSUPPORTFUNCTION_VERBOSE
                         std::cout << "supportvalue: " << result.supportValue << '\n';
                     #endif
                 #endif
                                 
                 return result;
             }
             
             // getter for const e
             matrix_t<double> getE()
             {
                 return e;
             } 
    };
}
