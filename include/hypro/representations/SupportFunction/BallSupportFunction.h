/*
 * This file contains the basic implementation of support functions of a ball according to the infinity norm and its
 *evaluation.
 * @file BallSupportFunction.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-04-17
 * @version	2015-04-17
 */

#pragma once

#include "../../config.h"
#include "../../datastructures/Point.h"
#include "util.h"

namespace hypro {
template <typename Number>
class BallSupportFunction {
  private:
	unsigned mDimension = 0;
	Number mRadius;
	SF_TYPE mType;

  public:
	BallSupportFunction( const BallSupportFunction<Number>& _orig );
	BallSupportFunction( Number _radius, SF_TYPE _type );
	~BallSupportFunction();

	/**
	 * Returns the dimension of the object.
	 * @return
	 */
	unsigned dimension() const;

	Number radius() const;
	SF_TYPE type() const;

	void setDimension( unsigned dim ) { mDimension = dim; }

	Point<Number> supremumPoint() const;

	/**
	 * Evaluates the support function in the given direction.
	 * @param l
	 * @return
	 */
	EvaluationResult<Number> evaluate( const vector_t<Number>& l ) const;

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
#include "BallSupportFunction.tpp"
