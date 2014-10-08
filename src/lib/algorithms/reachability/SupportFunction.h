/*
 *  This file contains the abstract super class for support function representations
 *  Author: Norman Hansen
 */

//#pragma once
//#define SUPPORTFUNCTION_VERBOSE
#pragma once 
#include "hyreach_utils.h" 

#define SUPPORTFUNCTION_VERBOSE

namespace hypro
{
    // This enum represents the support function type and is used to identify support function without instanceof operations
    enum SupportFunctionType {Box_Type, Polytope_Type, NonLinear_Type};
    
    /*
    * This structure describes the result of a support function evaluation
    */
    struct evaluationResult {
    	double supportValue;	// the value returned by the support function evaluation
    	matrix_t<double> optimumValue;	// the point leading to the support function value (extremum in direction)
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
         
         * For NonLinear:
               
         *
         *
         *
         *
         *
         *
         *
         *
         *
               
         */
    };
    
    class SupportFunction
    {
      public:
               
        /**
    	* This method should compute the evaluation result for a specified direction l
    	*/
        virtual evaluationResult evaluate(matrix_t<double> l)
        { 
                #ifdef  SUPPORTFUNCTION_VERBOSE
                   std::cout << "SupportFunction:evaluate: THIS SHOULD NEVER BE CALLED" << '\n';
                #endif
                evaluationResult result; 
                result.supportValue = 0; 
                result.errorCode = -1000; 
                return result;
        };
          
        /*
        * This method evaluates the support function in all directions from list L
        */  
        void multiEvaluate(std::vector<matrix_t<double>>* L,  matrix_t<double>* result )
        {
            #ifdef  SUPPORTFUNCTION_VERBOSE
                   std::cout << "SupportFunction:evaluate: evaluation of the support function in all directions L" << '\n';
            #endif
            for(unsigned int i=0; i<L->size(); i++)
            {
                 evaluationResult res = this->evaluate(L->at(i));
                 (*result)(i,0) = res.supportValue;
            }
        }
        
        /*
        * This method evaluates the support function in all directions from list L
        */  
        void multiEvaluate(std::vector<matrix_t<double>>* L,  std::vector<double> result )
        {
            #ifdef  SUPPORTFUNCTION_VERBOSE
                   std::cout << "SupportFunction:evaluate: evaluation of the support function in all directions L" << '\n';
            #endif
            for(unsigned int i=0; i<L->size(); i++)
            {
                 evaluationResult res = this->evaluate(L->at(i));
                 result[i] = res.supportValue;
            }
        }
                         
        // getter for the support function type
        SupportFunctionType getSupportFunctionType()
        {
           return support_function_type;
        }
          
        virtual ~SupportFunction(){}
        
      protected:
      
          // the constructor can only be called from sub-classes
          SupportFunction(SupportFunctionType type)
          {
              this->support_function_type = type;
          } 
          
 
      private:
          SupportFunctionType support_function_type;
    };
    
    
    /**
    * This class is used to represent the result of the multiplication between a geometric figure represented by a
    * support function and a matrix
    */
    class MultiplicationSupportfunction : public SupportFunction
    {
      private:
              matrix_t<double> factor;
              SupportFunction* fct;
      public:
          MultiplicationSupportfunction(matrix_t<double> factor, SupportFunction* fct, SupportFunctionType type): SupportFunction(type)
          {
//              #ifdef  SUPPORTFUNCTION_VERBOSE 
//                   std:: cout << "MultiplicationSupportfunction: constructor" << '\n';
//              #endif                                         
              this->factor = factor.transpose();
              this->fct = fct;
          }
          
          evaluationResult evaluate(matrix_t<double> l)
          { 
              #ifdef  SUPPORTFUNCTION_VERBOSE
                  std:: cout << "MultiplicationSupportfunction: evaluate" << '\n';
              #endif
//               #ifdef  SUPPORTFUNCTION_VERBOSE
//                   std::cout << "MultiplicationSupportfunction:evaluate: factor = " << factor << '\n';
//                   std::cout << "MultiplicationSupportfunction:evaluate: l = " << l << '\n';
//                   std::cout << "MultiplicationSupportfunction:evaluate: factor * l = " << factor * l << '\n';
//                   std::cout << "MultiplicationSupportfunction:evaluate: fct(l) = " << (fct->evaluate(l)).supportValue << '\n';
//               #endif
                             
               return fct->evaluate(factor * l);
          };
    };
    
    // overload the * Operator for e.g. B*U (creates MultiplicationSupportfunction)
    const MultiplicationSupportfunction operator*(matrix_t<double> const& lhs, SupportFunction* const& rhs) 
    { 
//      #ifdef  SUPPORTFUNCTION_VERBOSE
//         std::cout << "Multiplication: " << lhs << " with support function (pointer)" << '\n';
//      #endif
      MultiplicationSupportfunction result(lhs,rhs,rhs->getSupportFunctionType());
      return result;
    }
}
