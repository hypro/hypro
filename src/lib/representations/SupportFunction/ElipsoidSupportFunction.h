/*
 * This file contains the basic implementation of support functions of a ball according to the infinity norm and its evaluation.
 * @file ElipsoidSupportFunction.h
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since	2015-04-17
 * @version	2015-04-17
 */
 
#pragma once 

#include "../../config.h"
#include "util.h"


namespace hypro
{
	template<typename Number>
	class ElipsoidSupportFunction{
	
	private:
		unsigned mDimension;
		matrix_t<Number> mMatrix;
		Number mDistance;

	public:
		
		ElipsoidSupportFunction(matrix_t<Number> _matrix, Number _distance);
		~ElipsoidSupportFunction();
		
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
		
		/**
		 * @brief Evaluates the support function in the directions given in the passed matrix.
		 * @details Uses the standard evaluate method for multiple directions.
		 * 
		 * @param _A Matrix holding the directions in which to evaluate.
		 * @return Vector of support values.
		 */
		vector_t<Number> multiEvaluate(const matrix_t<Number>& _A) const;

		/**
		 * @brief Check if point is contained in the support function.
		 * @details To check if the given point is contained in the support function we evaluate it in all its directions (uses multiEvaluate).
		 * 
		 * @param _point The point to check.
		 * @return True, if the point is inside the support function.
		 */
		bool contains(const Point<Number>& _point) const;

		/**
		 * @brief Check if point is contained in the support function.
		 * @details To check if the given point is contained in the support function we evaluate it in all its directions (uses multiEvaluate).
		 * 
		 * @param _point The point to check.
		 * @return True, if the point is inside the support function.
		 */
		bool contains(const vector_t<Number>& _point) const;

		bool empty() const;
	};
} // namespace
#include "ElipsoidSupportFunction.tpp"
