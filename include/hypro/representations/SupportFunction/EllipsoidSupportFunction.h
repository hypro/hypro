/*
 * This file contains the basic implementation of support functions of a ball according to the infinity norm and its
 *evaluation.
 * @file EllipsoidSupportFunction.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Phillip Florian
 *
 * @since	2015-04-17
 * @version	2016-05-04
 */

#pragma once

#include "../../config.h"
#include "util.h"

namespace hypro {

/*
 * This class defines a support Function object representing an ellipsoid
 * SupportFunctions can be evaluated in a specified direction l and return a correspondent EvaluationResult
 */
template <typename Number>
class EllipsoidSupportFunction {
  private:
	unsigned mDimension;
	matrix_t<Number> mShapeMatrix;
	SF_TYPE mType;

  public:
	EllipsoidSupportFunction( const EllipsoidSupportFunction<Number>& _orig );
	EllipsoidSupportFunction( matrix_t<Number> _shapeMatrix );
	~EllipsoidSupportFunction();

	/**
	 * Returns the dimension of the object.
	 * @return
	 */
	unsigned dimension() const;

	matrix_t<Number> shapeMatrix() const;
	SF_TYPE type() const;

	/**
	 * Evaluates the support function in the given direction.
	 * @param l
	 * @return
	 */
	// EvaluationResult<Number> evaluate( const vector_t<Number>& _l ) const;

	template <typename N = Number, carl::DisableIf<std::is_same<N, double>> = carl::dummy>
	EvaluationResult<Number> evaluate( const vector_t<Number>& _l ) const {
		EvaluationResult<Number> result;
		result.supportValue = carl::sqrt_safe( _l.dot( this->mShapeMatrix * _l ) ).first;
		result.optimumValue = result.supportValue * _l;
		result.errorCode = SOLUTION::FEAS;
		return result;
	}

	template <typename N = Number, carl::EnableIf<std::is_same<N, double>> = carl::dummy>
	EvaluationResult<Number> evaluate( const vector_t<Number>& _l ) const {
		EvaluationResult<Number> result;
		result.supportValue = std::sqrt( _l.dot( this->mShapeMatrix * _l ) );
		result.optimumValue = result.supportValue * _l;
		result.errorCode = SOLUTION::FEAS;
		return result;
	}

	/**
	 * @brief Evaluates the support function in the directions given in the passed matrix.
	 * @details Uses the standard evaluate method for multiple directions.
	 *
	 * @param _A Matrix holding the directions in which to evaluate.
	 * @return Vector of support values.
	 */
	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _A ) const;

	/**
	 * @brief Check if point is contained in the support function.
	 * @details To check if the given point is contained in the support function we evaluate it in all its directions
	 *(uses multiEvaluate).
	 *
	 * @param _point The point to check.
	 * @return True, if the point is inside the support function.
	 */
	bool contains( const Point<Number>& _point ) const;

	/**
	 * @brief Check if point is contained in the support function.
	 * @details To check if the given point is contained in the support function we evaluate it in all its directions
	 *(uses multiEvaluate).
	 *
	 * @param _point The point to check.
	 * @return True, if the point is inside the support function.
	 */
	bool contains( const vector_t<Number>& _point ) const;

	bool empty() const;
};
}  // namespace hypro
#include "EllipsoidSupportFunction.tpp"
