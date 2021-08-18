/**
 * @file Ellipsoid.h
 * @author Phillip Florian
 */

#pragma once

#include "../../datastructures/Halfspace.h"

#include <cassert>
#include <map>

namespace hypro {

/**
 * @brief      Class for ellipsoids.
 *
 * @tparam     Number  The used number type.
 */
template <typename Number, typename Converter>
class EllipsoidT {
  private:
	unsigned mDimension;
	matrix_t<Number> mShapeMatrix;
	bool mIsEmpty;

  public:
	EllipsoidT( Number _radius, std::size_t _dimension );
	EllipsoidT( matrix_t<Number> _shapeMatrix );
	EllipsoidT( const EllipsoidT& _orig );
	~EllipsoidT();

	/**
	 * Returns the shape matrix of the object.
	 * @return
	 */
	matrix_t<Number> matrix() const;

	/**
	 * @brief Returns the current dimension of the ellipsoid.
	 * @return
	 */
	std::size_t dimension() const;

	/**
	 * @brief Checks, if the ellipsoid is empty.
	 * @return True, if the ellipsoid is empty.
	 */
	bool empty() const;

	/**
	 * @brief Assignment operator.
	 *
	 * @param rhs An EllipsoidT.
	 */
	EllipsoidT<Number, Converter>& operator=( const EllipsoidT<Number, Converter>& rhs ) = default;

	friend bool operator==( const EllipsoidT<Number, Converter>& b1, const EllipsoidT<Number, Converter>& b2 ) { return ( b1.mShapeMatrix == b2.mShapeMatrix ? true : false ); }
	friend bool operator!=( const EllipsoidT<Number, Converter>& b1, const EllipsoidT<Number, Converter>& b2 ) { return !( b1 == b2 ); }

	friend std::ostream& operator<<( std::ostream& ostr, const EllipsoidT<Number, Converter>& ) { return ostr; }
	void print() const;

	/**
	 *
	 * @param A a linear transformation matrix
	 * @param b shiftvector. ignored here and just included to fit the lin. trans of other representations
	 * @return ellipsoid obtained by applying the linear transformation
	 */
	EllipsoidT linearTransformation( const matrix_t<Number>& _A ) const;

	/**
	 *
	 * @param A a linear transformation matrix
	 * @param b shiftvector. ignored here and just included to fit the lin. trans of other representations
	 * @return ellipsoid obtained by applying the linear transformation
	 */
	EllipsoidT affineTransformation( const matrix_t<Number>& _A, const vector_t<Number>& _b ) const;

	/**
	 *
	 * @param rhs second ellipsoid used for the minkowskiSum,
	 * @param l direction of tight approximation
	 * @return ellipsoid overapproximating the mink sum of two ellipsoids
	 */
	EllipsoidT minkowskiSum( const EllipsoidT& _rhs, bool _approx = true ) const;

	/**
	 *
	 * @param l direction in which to evaluate
	 * @return vector to outmost point in direction l
	 */
	vector_t<Number> evaluate( vector_t<Number> const l ) const;

	/**
	 *
	 * @param _matrix a shapematrix of an ellipsoid
	 * @return matrix overapproximating the ellipsoid defined by _matrix
	 */
	matrix_t<Number> approxEllipsoidTMatrix( const matrix_t<Number> _matrix ) const;

	/*
	explicit operator BoxT<Number,Converter>() const {
		vector_t<Number> l(mDimension);
		vector_t<Number> evaluation;
		l.setZero();
		std::vector<carl::Interval<Number>> intervals(mDimension);
		for ( std::size_t i = 0; i < mDimension; i++) {
			l(i) = 1;
			evaluation = evaluate(l);
			intervals.at(i).setLower(evaluation(i));
			intervals.at(i).setUpper(-evaluation(i));
			l(i) = 0;
		}
		return BoxT<Number,Converter>(intervals);
	}

	explicit operator SupportFunction<Number,Converter>() const { return SupportFunction<Number,Converter>(mShapeMatrix); }

	explicit operator HPolytopeT<Number,Converter>() const {
		vector_t<Number> l(mDimension);
		l.setZero();
		vector_t<Number> evaluation;
		std::vector<vector_t<Number>> constraints;
		vector_t<Number> b;
		for ( std::size_t i = 0; i < mDimension; i++) {
			for (std:: size_t j = i+1; j < mDimension; j++ ) {
				// Evaluation in 8 directions for each pair of dimensions
				// only compute 4 directions, as E is symmetric. Comments denote the combination of i,j
				// (1,0)
				l(i) = 1;
				evaluation = evaluate(l);
				constraints.push_back(evaluation);
				constraints.push_back(-evaluation);
				// (1,1)
				l(j) = 1;
				evaluation = evaluate(l);
				constraints.push_back(evaluation);
				constraints.push_back(-evaluation);
				// (-1,1)
				l(i) = -1;
				evaluation = evaluate(l);
				constraints.push_back(evaluation);
				constraints.push_back(-evaluation);
				// (0,1)
				l(i) = 0;
				evaluation = evaluate(l);
				constraints.push_back(evaluation);
				constraints.push_back(-evaluation);
				l(j) = 0;
			}
		}
		b.setOnes(constraints.size());
		matrix_t<Number> constraintMatrix(constraints.size(),mDimension);
		for (std::size_t i = 0; i < constraints.size(); i++){
			constraintMatrix.row(i) = constraints.at(i);
		}
		return HPolytopeT<Number,Converter>(constraintMatrix, b);
	}

	explicit operator VPolytopeT<Number,Converter>() const {
		vector_t<Number> l(mDimension);
		l.setZero();
		vector_t<Number> evaluation;
		std::vector<vector_t<Number>> constraints;
		vector_t<Number> b;
		for ( std::size_t i = 0; i < mDimension; i++) {
			for (std:: size_t j = i+1; j < mDimension; j++ ) {
				// Evaluation in 8 directions for each pair of dimensions
				// only compute 4 directions, as E is symmetric. Comments denote the combination of i,j
				// (1,0)
				l(i) = 1;
				evaluation = evaluate(l);
				constraints.push_back(evaluation);
				constraints.push_back(-evaluation);
				// (1,1)
				l(j) = 1;
				evaluation = evaluate(l);
				constraints.push_back(evaluation);
				constraints.push_back(-evaluation);
				// (-1,1)
				l(i) = -1;
				evaluation = evaluate(l);
				constraints.push_back(evaluation);
				constraints.push_back(-evaluation);
				// (0,1)
				l(i) = 0;
				evaluation = evaluate(l);
				constraints.push_back(evaluation);
				constraints.push_back(-evaluation);
				l(j) = 0;
			}
		}
		b.setOnes(constraints.size());
		matrix_t<Number> constraintMatrix(constraints.size(),mDimension);
		for (std::size_t i = 0; i < constraints.size(); i++){
			constraintMatrix.row(i) = constraints(i);
		}
		return VPolytopeT<Number,Converter> (constraintMatrix, b);
		}

	// Can be done much better if main axis is known.
	explicit operator ZonotopeT<Number,Converter>() const {
		vector_t<Number> l(mDimension);
		l.setZero();
		vector_t<Number> evaluation;
		std::vector<vector_t<Number>> constraints;
		for ( std::size_t i = 0; i < mDimension; i++) {
				l(i) = 1;
				evaluation = evaluate(l);
				constraints.push_back(evaluation);
				l(i) = 0;
		}
		matrix_t<Number> constraintMatrix(constraints.size(),mDimension);
		for (std::size_t i = 0; i < constraints.size(); i++){
			constraintMatrix.row(i) = constraints(i);
		}
		return ZonotopeT<Number,Converter> (constraintMatrix);
		}

	*/
};
}  // namespace hypro
#include "Ellipsoid.tpp"
