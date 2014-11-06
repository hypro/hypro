/*
 *  This file contains the abstract super class for support function representations
 *  Author: Norman Hansen
 */

#pragma once 

#include "hyreach_utils.h" 

//#define SUPPORTFUNCTION_VERBOSE
//#define MULTIPLICATIONSUPPORTFUNCTION_VERBOSE

namespace hypro
{
    // This enum represents the support function type and is used to identify support function without instanceof operations
    enum SupportFunctionType {Box_Type, Polytope_Type, NonLinear_Type, MinowskiSum_Type, Infinity_Type};
    
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
    class SummationSupportfunction;
    class MultiplicationSupportfunction;
    class ScalarMultiplicationSupportfunction;  
    
    /*
    * This is the super class for all support function objects.
    */
    class SupportFunction
    {
      private:
          SupportFunctionType support_function_type;
      
      protected:
          artificialDirections* aD = 0;
           
          /* 
          * The constructor can only be called from sub-classes (makes the class abstract)
          */
          SupportFunction(SupportFunctionType type, artificialDirections* aD)
          {
              this->support_function_type = type;
              this->aD = aD;
          } 
          
            /*
        	* This method should compute the evaluation result for a specified direction l
        	*/
            virtual evaluationResult specificEvaluation(matrix_t<double> l)
            { 
                    #ifdef  SUPPORTFUNCTION_VERBOSE
                       std::cout << "SupportFunction:evaluate: THIS SHOULD NEVER BE CALLED" << '\n';
                    #endif
                    evaluationResult result; 
                    result.supportValue = 0; 
                    result.errorCode = -1000; 
                    return result;
            }
          
      public:       
        
        /**
        * getter for the pointer to the structure for additional DImensions
        */
        artificialDirections* getAD()
        {
            return aD;
        }
          
        /*
        * Evaluates the support funciton and catches first efficiently the additional dimension cases
        */
        evaluationResult evaluate(matrix_t<double>* l)
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
                    return this->specificEvaluation(*l);
                //}
        };
          
        /*
        * This method evaluates the support function in all directions from list L
        */  
        void multiEvaluate(std::vector<matrix_t<double>>* L,  matrix_t<double>* result )
        {
            #ifdef  SUPPORTFUNCTION_VERBOSE
                   std::cout << "SupportFunction:multiEvaluate1: evaluation of the support function in all directions L" << '\n';
            #endif
            for(unsigned int i=0; i<L->size(); i++)
            {
                 evaluationResult res = this->evaluate(&L->at(i));
                 (*result)(i,0) = res.supportValue;
            }
        }
        
        /*
        * This method evaluates the support function in all directions from list L
        */  
        void multiEvaluate(std::vector<matrix_t<double>>* L,  std::vector<double>* result )
        {
            #ifdef  SUPPORTFUNCTION_VERBOSE
                   std::cout << "SupportFunction:multiEvaluate2: evaluation of the support function in all directions L" << '\n';
                   std::cout << "L: " << BL;
                   printDirectionList(*L);
            #endif
            for(unsigned int i=0; i<L->size(); i++)
            {
                 evaluationResult res = this->evaluate(&L->at(i));
                 (*result)[i] = res.supportValue;
            }
        }
        
        /*
        * This method evaluates the support function in all directions from list L
        */  
        void multiEvaluate(std::vector<matrix_t<double>>* L,  double* result )
        {
            #ifdef  SUPPORTFUNCTION_VERBOSE
                   std::cout << "SupportFunction:multiEvaluate3: evaluation of the support function in all directions L" << '\n';
            #endif

            for(unsigned int i=0; i<L->size(); i++)
            {
                 evaluationResult res = this->evaluate(&L->at(i));
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
        SummationSupportfunction* minowskisum(SupportFunction* lhs);
        MultiplicationSupportfunction* multiply(matrix_t<double> lhs);
        ScalarMultiplicationSupportfunction* multiply(double lhs);
    };
    
    
    /*
    * Class representing the result of the minowski sum of two support functions
    */
    class SummationSupportfunction: public SupportFunction
    {
          private:
              SupportFunction* fctA;
              SupportFunction* fctB;
              
          protected:
              evaluationResult specificEvaluation(matrix_t<double> l);
              
          public:
              SummationSupportfunction(SupportFunction* fctA, SupportFunction* fctB);
    }; 
    
    /*
    * Class representing the result of a scalar multiplication of a support function
    */
    class ScalarMultiplicationSupportfunction : public SupportFunction
    {
      private:
              double factor;
              SupportFunction* fct;
              
      protected:        
              evaluationResult specificEvaluation(matrix_t<double> l)
              { 
                  #ifdef  SUPPORTFUNCTION_VERBOSE
                      #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                          std:: cout << "ScalarMultiplicationSupportfunction: evaluate" << '\n';
                      #endif
                  #endif                             
                  evaluationResult res = (fct->evaluate(&l));
                  res.optimumValue *= factor;
                  res.supportValue *= factor;
                  return res;
              };
          
      public:
          ScalarMultiplicationSupportfunction(double factor, SupportFunction* fct, SupportFunctionType type): SupportFunction(type, fct->getAD())
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
    SummationSupportfunction* SupportFunction::minowskisum(SupportFunction* lhs) 
        { 
          #ifdef  SUPPORTFUNCTION_VERBOSE
              #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                  std::cout << "Minowski Sum +: " << '\n';
              #endif
          #endif
          SummationSupportfunction* result = new SummationSupportfunction(this,lhs);
          return result;
        }
        
         // overload the * Operator for e.g. delta*U (creates ScalarMultiplicationSupportfunction)
   ScalarMultiplicationSupportfunction* SupportFunction::multiply(double lhs) 
        { 
          #ifdef  SUPPORTFUNCTION_VERBOSE
              #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                  std::cout << "Multiplication *: " << lhs << " with support function (pointer)" << '\n';
              #endif
          #endif
          
          ScalarMultiplicationSupportfunction* result = new ScalarMultiplicationSupportfunction(lhs,this,this->getSupportFunctionType());
          return result;
        }
    
    /**
    * This class is used to represent the result of the multiplication between a geometric figure represented by a
    * support function and a matrix
    */
    class MultiplicationSupportfunction : public SupportFunction
    {
      private:
              matrix_t<double> factor;
              SupportFunction* fct;
      
      protected:        
              evaluationResult specificEvaluation(matrix_t<double> l)
              { 
                  #ifdef  SUPPORTFUNCTION_VERBOSE
                      #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                          std:: cout << "MultiplicationSupportfunction: evaluate(l)" << '\n';
                          std::cout << "factor: " << BL << factor << BL << "l: " << BL << l << BL;
                      #endif
                  #endif
                   
                   matrix_t<double> temp = factor * l; 
                   
                   #ifdef  SUPPORTFUNCTION_VERBOSE
                      #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                          std:: cout << "MultiplicationSupportfunction: evaluate(l): temp: " << BL << temp << '\n';
                      #endif
                  #endif
                               
                   return fct->evaluate(&temp);
              }
          
      public:
          MultiplicationSupportfunction(matrix_t<double> factor, SupportFunction* fct, SupportFunctionType type): SupportFunction(type, fct->getAD())
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
    MultiplicationSupportfunction* SupportFunction::multiply(matrix_t<double> lhs) 
    { 
      #ifdef  SUPPORTFUNCTION_VERBOSE
          #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
              std::cout << "Multiplication *: " << lhs << " with support function (pointer)" << '\n';
          #endif
      #endif
      
      MultiplicationSupportfunction* result = new MultiplicationSupportfunction(lhs,this,this->getSupportFunctionType());
      return result;
    }    
    
    SummationSupportfunction::SummationSupportfunction(SupportFunction* fctA, SupportFunction* fctB): SupportFunction(SupportFunctionType::MinowskiSum_Type, fctA->getAD())
              {
                  #ifdef  SUPPORTFUNCTION_VERBOSE 
                      #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                          std:: cout << "SummationSupportfunction: constructor" << '\n';
                      #endif
                  #endif                                         
                  this->fctA = fctA;
                  this->fctB = fctB;
              };
              
    evaluationResult SummationSupportfunction::specificEvaluation(matrix_t<double> l)
              { 
                  #ifdef  SUPPORTFUNCTION_VERBOSE
                      #ifdef MULTIPLICATIONSUPPORTFUNCTION_VERBOSE
                          std:: cout << "SummationSupportfunction: evaluate" << '\n';
                      #endif
                  #endif                             
                  evaluationResult resA = (fctA->evaluate(&l));
                  evaluationResult resB = (fctB->evaluate(&l));
                  
                  resA.optimumValue += resB.optimumValue;
                  resA.supportValue += resB.supportValue;
                  return resA;
              }
              
              
    /*
    * Represents a support function without boundaries (evaluationable in constant time)
    */          
    class InfinitySupportFunction : public SupportFunction
    {
      private:
              evaluationResult result;
              
      protected:        
              evaluationResult specificEvaluation(matrix_t<double> l)
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
          InfinitySupportFunction(artificialDirections* aD) : SupportFunction(SupportFunctionType::Infinity_Type, aD)
          {
                result.supportValue = INFINITY; 
                result.errorCode = 0; 
          }
    };
    
    /*
    * Represents a support function describing the set zero (arbitrary dimensional)
    */          
    class ZeroSupportFunction : public SupportFunction
    {
      private:
              evaluationResult result;
              unsigned int dimensionality;
     
     protected:         
              evaluationResult specificEvaluation(matrix_t<double> l)
              {               
                    return result;
              };
          
      public:
          ZeroSupportFunction(unsigned int dimensionality, artificialDirections* aD) : SupportFunction(SupportFunctionType::Infinity_Type, aD)
          {
                result.supportValue = 0; 
                result.errorCode = 0; 
                this->dimensionality = dimensionality;
          }
    };
}
