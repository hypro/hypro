/*
 *  This file contains the abstract super class for support function representations
 *  Author: Norman Hansen
 */

#pragma once 

//#include "hyreach_utils.h" 
#include "../../config.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "vectorgenerator.h"
#include "helperMethods.h"
#include <glpk.h>

//#define SUPPORTFUNCTION_VERBOSE
//#define MULTIPLICATIONSUPPORTFUNCTION_VERBOSE

namespace hypro
{
    // This enum represents the support function type and is used to identify support function without instanceof operations
    enum SupportFunctionType {Box_Type, Polytope_Type, NonLinear_Type, MinowskiSum_Type, Infinity_Type};
	
    /*
    * This structure describes the result of a support function evaluation
    */
	template<typename Number>
    struct evaluationResult {
    	Number supportValue;	// the value returned by the support function evaluation
    	matrix_t<Number> optimumValue;	// the point leading to the support function value (extremum in direction)
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
    
    // forwardDeclarations for further supportFunction types
	template<typename Number>
    class SummationSupportfunction;
	
	template<typename Number>
    class MultiplicationSupportfunction;
	
	template<typename Number>
    class ScalarMultiplicationSupportfunction;  
    
    /*
    * This is the super class for all support function objects.
    */
	template<typename Number>
    class SupportFunction
    {
      private:
          SupportFunctionType support_function_type;
      
      protected:
		artificialDirections<Number>* aD = 0;
           
          /* 
          * The constructor can only be called from sub-classes (makes the class abstract)
          */
          SupportFunction(SupportFunctionType type, artificialDirections<Number>* aD)
          {
              this->support_function_type = type;
              this->aD = aD;
          } 
          
            /*
        	* This method should compute the evaluation result for a specified direction l
        	*/
            virtual evaluationResult<Number> specificEvaluation(const matrix_t<Number>& l) const
            { 
				CARL_LOG_NOTIMPLEMENTED();	
				#ifdef  SUPPORTFUNCTION_VERBOSE
				   std::cout << "SupportFunction:evaluate: THIS SHOULD NEVER BE CALLED" << '\n';
				#endif
				evaluationResult<Number> result; 
				result.supportValue = Number(0); 
				result.errorCode = -1000; 
				return result;
            }
          
      public:       
        
        /**
        * getter for the pointer to the structure for additional DImensions
        */
        artificialDirections<Number>* getAD()
        {
            return aD;
        }
          
        /*
        * Evaluates the support funciton and catches first efficiently the additional dimension cases
        */
        evaluationResult<Number> evaluate(const matrix_t<Number>& l) const
        { 
                         /*
                bool artificialDirection = (*l)(l->rows()-1,0) != 0;
                
                if( artificialDirection && aD != 0)  // check if l shall be evaluated or is an artificial direction
                {
                    std::cout << "SupportFunction.evaluate(l): l aritifical:"<< BL << *l << BL;
                    evaluationResult result; 
                    if((*l)(l->rows()-1,0) > 0 )
                    {
                         // 0...0 1
                         result.supportValue = aD->dir1_eval;
                    }
                    else
                    {
                        // 0...0 -1
                        result.supportValue = aD->dir2_eval;
                    }
                    result.errorCode = 0; 
                    return result;
                }
                else
                { */
                    return this->specificEvaluation(l);
                //}
        };
          
        /*
        * This method evaluates the support function in all directions from list L
        */  
        void multiEvaluate(std::vector<matrix_t<Number>>* L,  matrix_t<Number>* result )
        {
            #ifdef  SUPPORTFUNCTION_VERBOSE
                   std::cout << "SupportFunction:multiEvaluate1: evaluation of the support function in all directions L" << '\n';
            #endif
            for(unsigned int i=0; i<L->size(); i++)
            {
                 evaluationResult<Number> res = this->evaluate(&L->at(i));
                 (*result)(i,0) = res.supportValue;
            }
        }
        
        /*
        * This method evaluates the support function in all directions from list L
        */  
        void multiEvaluate(std::vector<matrix_t<Number>>* L,  std::vector<Number>* result )
        {
            #ifdef  SUPPORTFUNCTION_VERBOSE
                   std::cout << "SupportFunction:multiEvaluate2: evaluation of the support function in all directions L" << '\n';
                   std::cout << "L: " << std::endl;
                   printDirectionList(*L);
            #endif
            for(unsigned int i=0; i<L->size(); i++)
            {
                 evaluationResult<Number> res = this->evaluate(&L->at(i));
                 (*result)[i] = res.supportValue;
            }
        }
        
        /*
        * This method evaluates the support function in all directions from list L
        */  
        void multiEvaluate(std::vector<matrix_t<Number>>* L,  Number* result )
        {
            #ifdef  SUPPORTFUNCTION_VERBOSE
                   std::cout << "SupportFunction:multiEvaluate3: evaluation of the support function in all directions L" << '\n';
            #endif

            for(unsigned int i=0; i<L->size(); i++)
            {
                 evaluationResult<Number> res = this->evaluate(&L->at(i));
                 result[i] = res.supportValue;
            }
        }
                         
        /*
        * Getter for the support function type
        */
        SupportFunctionType getSupportFunctionType()
        {
           return support_function_type;
        }
          
        virtual ~SupportFunction(){}
        
        // 
        SummationSupportfunction<Number>* minowskisum(SupportFunction<Number>* lhs);
        MultiplicationSupportfunction<Number>* multiply(matrix_t<Number> lhs);
        ScalarMultiplicationSupportfunction<Number>* multiply(Number lhs);
    };
    
    
    /*
    * Class representing the result of the minowski sum of two support functions
    */
	template<typename Number>
    class SummationSupportfunction: public SupportFunction<Number>
    {
          private:
              SupportFunction<Number>* fctA;
              SupportFunction<Number>* fctB;
              
          protected:
              evaluationResult<Number> specificEvaluation(matrix_t<Number> l);
              
          public:
              SummationSupportfunction(SupportFunction<Number>* fctA, SupportFunction<Number>* fctB);
    }; 
    
    /*
    * Class representing the result of a scalar multiplication of a support function
    */
	template<typename Number>
    class ScalarMultiplicationSupportfunction : public SupportFunction<Number>
    {
      private:
              Number factor;
              SupportFunction<Number>* fct;
              
      protected:        
              evaluationResult<Number> specificEvaluation(matrix_t<Number> l)
              { 
                  #ifdef  SUPPORTFUNCTION_VERBOSE
                      #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                          std:: cout << "ScalarMultiplicationSupportfunction: evaluate" << '\n';
                      #endif
                  #endif                             
                  evaluationResult<Number> res = (fct->evaluate(&l));
                  res.optimumValue *= factor;
                  res.supportValue *= factor;
                  return res;
              };
          
      public:
          ScalarMultiplicationSupportfunction(Number factor, SupportFunction<Number>* fct, SupportFunctionType type): SupportFunction<Number>(type, fct->getAD())
          {
              #ifdef  SUPPORTFUNCTION_VERBOSE 
                  #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                      std:: cout << "ScalarMultiplicationSupportfunction: constructor" << '\n';
                  #endif
              #endif                                         
              this->factor = factor;
              this->fct = fct;
          }
    };        
    
        // overload the + Operator for two support function pointers
	template<typename Number>
    SummationSupportfunction<Number>* SupportFunction<Number>::minowskisum(SupportFunction<Number>* lhs) 
        { 
          #ifdef  SUPPORTFUNCTION_VERBOSE
              #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                  std::cout << "Minowski Sum +: " << '\n';
              #endif
          #endif
          SummationSupportfunction<Number>* result = new SummationSupportfunction<Number>(this,lhs);
          return result;
        }
        
         // overload the * Operator for e.g. delta*U (creates ScalarMultiplicationSupportfunction)
	template<typename Number>
	ScalarMultiplicationSupportfunction<Number>* SupportFunction<Number>::multiply(Number lhs) 
        { 
          #ifdef  SUPPORTFUNCTION_VERBOSE
              #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                  std::cout << "Multiplication *: " << lhs << " with support function (pointer)" << '\n';
              #endif
          #endif
          
          ScalarMultiplicationSupportfunction<Number>* result = new ScalarMultiplicationSupportfunction<Number>(lhs,this,this->getSupportFunctionType());
          return result;
        }
    
    /**
    * This class is used to represent the result of the multiplication between a geometric figure represented by a
    * support function and a matrix
    */
	template<typename Number>
    class MultiplicationSupportfunction : public SupportFunction<Number>
    {
      private:
              matrix_t<Number> factor;
              SupportFunction<Number>* fct;
      
      protected:        
              evaluationResult<Number> specificEvaluation(matrix_t<Number> l)
              { 
                  #ifdef  SUPPORTFUNCTION_VERBOSE
                      #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                          std:: cout << "MultiplicationSupportfunction: evaluate(l)" << '\n';
                          std::cout << "factor: " << BL << factor << BL << "l: " << BL << l << BL;
                      #endif
                  #endif
                   
                   matrix_t<Number> temp = factor * l; 
                   
                   #ifdef  SUPPORTFUNCTION_VERBOSE
                      #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                          std:: cout << "MultiplicationSupportfunction: evaluate(l): temp: " << BL << temp << '\n';
                      #endif
                  #endif
                               
                   return fct->evaluate(&temp);
              }
          
      public:
          MultiplicationSupportfunction(matrix_t<Number> factor, SupportFunction<Number>* fct, SupportFunctionType type): SupportFunction<Number>(type, fct->getAD())
          {
              #ifdef  SUPPORTFUNCTION_VERBOSE 
                  #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                      std:: cout << "MultiplicationSupportfunction: constructor" << '\n';
                  #endif
              #endif                                         
              this->factor = factor.transpose();
              this->fct = fct;
          }
    };
    
    // overload the * Operator for e.g. B*U (creates MultiplicationSupportfunction)
	template<typename Number>
    MultiplicationSupportfunction<Number>* SupportFunction<Number>::multiply(matrix_t<Number> lhs) 
    { 
      #ifdef  SUPPORTFUNCTION_VERBOSE
          #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
              std::cout << "Multiplication *: " << lhs << " with support function (pointer)" << '\n';
          #endif
      #endif
      
      MultiplicationSupportfunction<Number>* result = new MultiplicationSupportfunction<Number>(lhs,this,this->getSupportFunctionType());
      return result;
    }    
    
	template<typename Number>
    SummationSupportfunction<Number>::SummationSupportfunction(SupportFunction<Number>* fctA, SupportFunction<Number>* fctB): SupportFunction<Number>(SupportFunctionType::MinowskiSum_Type, fctA->getAD())
	{
		#ifdef  SUPPORTFUNCTION_VERBOSE 
			#ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
				std:: cout << "SummationSupportfunction: constructor" << '\n';
			#endif
		#endif                                         
		this->fctA = fctA;
		this->fctB = fctB;
	};
              
	template<typename Number>
    evaluationResult<Number> SummationSupportfunction<Number>::specificEvaluation(matrix_t<Number> l)
	{ 
		#ifdef  SUPPORTFUNCTION_VERBOSE
			#ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
				std:: cout << "SummationSupportfunction: evaluate" << '\n';
			#endif
		#endif                             
		evaluationResult<Number> resA = (fctA->evaluate(&l));
		evaluationResult<Number> resB = (fctB->evaluate(&l));

		resA.optimumValue += resB.optimumValue;
		resA.supportValue += resB.supportValue;
		return resA;
	}
              
              
    /*
    * Represents a support function without boundaries (evaluationable in constant time)
    */          
	template<typename Number>
    class InfinitySupportFunction : public SupportFunction<Number>
    {
      private:
              evaluationResult<Number> result;
              
      protected:        
              evaluationResult<Number> specificEvaluation(matrix_t<Number> l)
              {     
   /*                 if(aD != 0) // catch artificial directions
                    {  
                            if( l == aD->dir1 )
                            {
                                evaluationResult res;
                                res.supportValue = aD->dir1_eval;
                                return res;
                            }
                            else if ( l == aD->dir2 )
                            {
                                 evaluationResult res;
                                 res.supportValue = aD->dir2_eval;
                                 return res;
                            }
                    }
*/
                    return result;     
              };
      public:
          InfinitySupportFunction(artificialDirections<Number>* aD) : SupportFunction<Number>(SupportFunctionType::Infinity_Type, aD)
          {
                result.supportValue = INFINITY; 
                result.errorCode = 0; 
          }
    };
    
    /*
    * Represents a support function describing the set zero (arbitrary dimensional)
    */          
	template<typename Number>
    class ZeroSupportFunction : public SupportFunction<Number>
    {
      private:
              evaluationResult<Number> result;
              unsigned int dimensionality;
     
     protected:         
              evaluationResult<Number> specificEvaluation(matrix_t<double> l)
              {               
                    return result;
              };
          
      public:
          ZeroSupportFunction(unsigned int dimensionality, artificialDirections<Number>* aD) : SupportFunction<Number>(SupportFunctionType::Infinity_Type, aD)
          {
                result.supportValue = 0; 
                result.errorCode = 0; 
                this->dimensionality = dimensionality;
          }
    };
}
