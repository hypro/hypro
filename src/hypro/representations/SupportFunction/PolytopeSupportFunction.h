/*
 * This file contains the basic implementation of support functions of polyhedra (template polyhedra) and their
 *evaluation.
 * @file PolytopeSupportFunction.h
 *
 * @author Norman Hansen
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @version	2015-02-27
 */

#pragma once

#include "../../config.h"
#include "../../datastructures/Halfspace.h"
#include "../../datastructures/Point.h"
#include "../../util/adaptions_eigen/adaptions_eigen.h"
#include "../../util/convexHull.h"
#include "../../util/linearOptimization/Optimizer.h"
#include "../../util/logging/Logger.h"
#include "../../util/sequenceGeneration/SequenceGenerator.h"
#include "../../util/statistics/statistics.h"
#include "SupportFunctionSetting.h"
#include "util.h"

#include <map>
#include <queue>


//#define PPOLYTOPESUPPORTFUNCTION_VERBOSE
#define PPOLYTOPESUPPORTFUNCTION_VERIFY

namespace hypro {

template <typename N, typename S>
class SupportFunctionContent;

template <typename N, typename C, typename S>
class SupportFunctionT;

/*
* This class defines a support Function object representing a polytope (might not be closed)
* SupportFunctions can be evaluated in a specified direction l and return a correspondent EvaluationResult
*/
template <typename Number, class Setting>
class PolytopeSupportFunction {
	friend SupportFunctionContent<Number, Setting>;
	template <typename N, typename C, typename S>
	friend class SupportFunctionT;

  private:
	matrix_t<Number> mConstraints;
	vector_t<Number> mConstraintConstants;
	mutable Optimizer<Number> mOpt;
	std::size_t mDimension;
	std::map<vector_t<Number>, Number> mCache;

  public:
	PolytopeSupportFunction( matrix_t<Number> constraints, vector_t<Number> constraintConstants );
	PolytopeSupportFunction( const std::vector<Halfspace<Number>>& _planes );
	PolytopeSupportFunction( const std::vector<Point<Number>>& _points );
	PolytopeSupportFunction( const PolytopeSupportFunction<Number, Setting>& _origin );
	~PolytopeSupportFunction();

	PolytopeSupportFunction<Number, Setting>& operator=( const PolytopeSupportFunction& _orig );

	/**
	 * Returns the dimension of the object.
	 * @return
	 */
	std::size_t dimension() const;

	SF_TYPE type() const;

	bool isTemplate() const { return mCache.size() > 0; }
	matrix_t<Number> constraints() const;
	vector_t<Number> constants() const;

	std::vector<Point<Number>> vertices() const;

	Point<Number> supremumPoint() const;

	/**
	 * Evaluates the support function in the given direction.
	 * @param l
	 * @return
	 */
	EvaluationResult<Number> evaluate( const vector_t<Number>& l, bool useExact ) const;

	/**
	 * @brief Evaluates the support function in the directions given in the passed matrix.
	 * @details Uses the standard evaluate method for multiple directions.
	 *
	 * @param _A Matrix holding the directions in which to evaluate.
	 * @return Vector of support values.
	 */
	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _A, bool useExact, bool setTemplate = false ) const;

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

	void cleanUp() const;

	void print() const;

	std::string getDotRepresentation() const;

	std::string createCode( unsigned index = 0 ) const;

	friend std::ostream& operator<<( std::ostream& lhs, const PolytopeSupportFunction<Number, Setting>& rhs ) {
		lhs << "[";
		for ( unsigned rowIndex = 0; rowIndex < rhs.mConstraints.rows() - 1; ++rowIndex ) {
			lhs << "  ";
			for ( unsigned d = 0; d < rhs.mConstraints.cols(); ++d ) {
				lhs << carl::toDouble( rhs.mConstraints( rowIndex, d ) ) << " ";
			}
			lhs << "<= " << carl::toDouble( rhs.mConstraintConstants( rowIndex ) ) << std::endl;
		}
		lhs << "  ";
		for ( unsigned d = 0; d < rhs.mConstraints.cols(); ++d ) {
			lhs << carl::toDouble( rhs.mConstraints( rhs.mConstraints.rows() - 1, d ) ) << " ";
		}
		lhs << "<= " << carl::toDouble( rhs.mConstraintConstants( rhs.mConstraints.rows() - 1 ) ) << " ]" << std::endl;
		return lhs;
	}

  private:
	void removeRedundancy();
	matrix_t<Number>& rMatrix() { return mConstraints; }
	vector_t<Number>& rVector() { return mConstraintConstants; }
};
}  // namespace hypro
#include "PolytopeSupportFunction.tpp"
