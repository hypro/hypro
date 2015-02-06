/*
 *  This file contains everything related directly to support functions of polyhedra and their evaluation
 *  Author: Norman Hansen
 */
 
#pragma once 
 
#define SUPPORTFUNCTION_VERBOSE 
#define PPOLYTOPESUPPORTFUNCTION_VERBOSE

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
			
			unsigned int mDimension;
    		
    		/**
            * Implements the functionality of the constructor. Used by both "real" constructors of this class
            */
            void initialize(matrix_t<Number> constraints, vector_t<Number> constraintConstants, operator_e operation, unsigned int dimensionality);
            
       protected:
            /*
        	* This method computes the evaluation result for a specified direction l
        	*/
        	evaluationResult<Number> specificEvaluation(const matrix_t<Number>& l) const;
            
        public:
			
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
        
		/**
		 * Applies a linear transformation on the given stateset.
		 * @param result The resulting stateset.
		 * @return True if the operation has been successfully applied.
		 */
        bool linearTransformation(PolytopeSupportFunction<Number>& result, const matrix_t<Number>& A, const vector_t<Number>& b = vector_t<Number>());
		
		/**
		 * Applies the Minkowskisum of the given stateset and a second stateset.
		 * @param result The resulting stateset.
		 * @param rhs The other righthand-side stateset.
		 * @return True if the operation has been successfully applied.
		 */
        bool minkowskiSum(PolytopeSupportFunction<Number>& result, const PolytopeSupportFunction<Number>& rhs);
		
		/**
		 * Intersects the given stateset with a second one.
		 * @param result The resulting stateset of the intersection.
		 * @param rhs The righthand-side stateset.
		 * @return ç
		 */
        bool intersect(PolytopeSupportFunction<Number>& result, const PolytopeSupportFunction<Number>& rhs);
		
		/**
		 * Computes the convex hull of the stateset.
		 * @param result The resulting stateset.
		 * @return True if the operation has been successfully applied.
		 */
        bool hull(PolytopeSupportFunction<Number>& result);
		
		/**
		 * Checks the membership of a point.
		 * @param point The point which is to be checked for membership.
		 * @return True if the point is contained in the stateset.
		 */
        bool contains(const Point<Number>& point);
		
		/**
		 * Computes the union of the given stateset with a second one. Note that
		 * the convex hull is applied, if the representations are not closed under
		 * this computation.
		 * @param result The resulting stateset.
		 * @param rhs The righthand-side stateset.
		 * @return True if the operation has been successfully applied.
		 */
        bool unite(PolytopeSupportFunction<Number>& result, const PolytopeSupportFunction<Number>& rhs);
		
    };
} // namespace
#include "PolytopeSupportFunction.tpp"
