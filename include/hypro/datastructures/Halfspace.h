/**
 *  Class that holds the implementation of a Halfspace.
 *  @file Halfspace.h
 *
 *  @author Stefan Schupp 	<stefan.schupp@cs.rwth-aachen.de>
 *
 *  @since 	2015-03-16
 *  @version 	2015-03-16
 */

#pragma once
#include "../representations/types.h"
#include "../util/VariablePool.h"
#include "../util/adaptions_eigen/adaptions_eigen.h"
#include "../util/linearOptimization/EvaluationResult.h"
#include "../util/logging/Logger.h"
#include "../util/typetraits.h"
#include "Point.h"

#include <cassert>
#include <glpk.h>

namespace hypro {
template <typename Number>
class Halfspace {
  private:
	vector_t<Number> mNormal = vector_t<Number>::Zero( 0 );
	Number mScalar = Number( 0 );

  public:
	Halfspace() = default;

	/**
	 * @brief      Constructor from a normal vector given as a point and an offset.
	 * @param[in]  _vector  The vector.
	 * @param[in]  _off     The offset.
	 */
	Halfspace( const Point<Number>& _vector, const Number& _off );

	/**
	 * @brief      Constructor from an initializer list for the normal vector and an offset.
	 * @param[in]  _coordinates  The normal vector.
	 * @param[in]  _off          The offset.
	 */
	Halfspace( std::initializer_list<Number> _coordinates, const Number& _off );

	/**
	 * @brief      Constructor from a normal vector and an offset with perfect forwarding.
	 * @param[in]  _vector  The vector.
	 * @param[in]  _off     The offset.
	 */
	template <
		  typename Normal, typename Offset, enable_if<convertible<Normal, vector_t<Number>> && convertible<Offset, Number>> = 0>
	Halfspace( Normal&& normal, Offset&& offset );

	/**
	 * @brief      Constructor from an offset vector and a set of points lying in the plane.
	 * @param[in]  _vec        The offset vector.
	 * @param[in]  _vectorSet  The point-set defining the plane.
	 */
	Halfspace( const vector_t<Number>& _vec, const std::vector<vector_t<Number>>& _vectorSet );

	/**
	 * @brief Construct a new Halfspace object from a set of points.
	 * @param points
	 */
	Halfspace( const std::vector<Point<Number>>& points );

	/**
	 * @brief Construct a new Halfspace object from a set of points given as vector_t.
	 * @param points
	 */
	Halfspace( const std::vector<vector_t<Number>>& points );

	/**
	 * @brief      Size function returning the estimated storage usage of this plane.
	 * @return     An estimated storage usage.
	 */
	double sizeOfHalfspace() { return sizeof( *this ) + this->mNormal.size() * sizeof( Number ); }

	/**
	 * @brief      Returns the space dimension.
	 * @return     The space dimension.
	 */
	unsigned dimension() const;

	template <typename N = Number, carl::DisableIf<std::is_same<N, double>> = carl::dummy>
	void makeInteger() {
		if ( !isInteger() ) {
			Number scaling = Number( getDenominator( mScalar ) );
			for ( unsigned i = 0; i < mNormal.rows(); ++i ) {
				scaling = scaling * Number( getDenominator( mNormal( i ) ) );
			}

			mScalar = mScalar * scaling;
			assert( isInteger( mScalar ) );

			for ( unsigned i = 0; i < mNormal.rows(); ++i ) {
				mNormal( i ) = mNormal( i ) * scaling;
				assert( isInteger( mNormal( i ) ) );
			}
		}
	}

	template <typename N = Number, carl::EnableIf<std::is_same<N, double>> = carl::dummy>
	void makeInteger() {
		// TODO: As this function is currently only used for number reduction, do nothing for doubles -> fix!
	}

	/**
	 * @brief      Determines if the plane coefficients are integers.
	 * @return     True if integer, False otherwise.
	 */
	bool isInteger() const {
		for ( int row = 0; row < mNormal.rows(); ++row ) {
			if ( !hypro::isInteger( Number( mNormal[row] ) ) ) return false;
		}
		return true;
	}

	/**
	 * @brief      Returns the plane normal.
	 * @return     The normal.
	 */
	const vector_t<Number>& normal() const&;

	/**
	 * @brief      Returns the plane normal as an rvalue if this is an rvalue.
	 * @return     The normal.
	 */
	vector_t<Number>&& normal() &&;

	/**
	 * @brief      Sets the normal.
	 * @param[in]  _normal  The normal.
	 */
	void setNormal( const vector_t<Number>& _normal );

	/**
	 * @brief      Inverts the halfspace by negating the plane normal and the offset.
	 */
	Halfspace<Number>& invert();

	/**
	 * @brief      Returns the plane offset.
	 * @return     The offset.
	 */
	Number offset() const&;

	/**
	 * @brief      Returns the plane offset as an rvalue if this is an rvalue.
	 * @return     The offset.
	 */
	Number&& offset() &&;

	/**
	 * @brief      Sets the offset.
	 * @param[in]  _offset  The offset.
	 */
	void setOffset( Number _offset );

	/**
	 * @brief      Returns the signed distance of a point to the hyperplane.
	 * @param[in]  _point  The point.
	 * @return     The signed distance.
	 */
	Number signedDistance( const vector_t<Number>& _point ) const;

	/**
	 * @brief      Evaluates the halfspace in the given direction.
	 * @details    Note that all evaluations not in direction of the normal will result in infty.
	 * @param[in]  _direction  The direction.
	 * @return     The maximal distance to the limiting plane in the given direction.
	 */
	Number evaluate( const vector_t<Number>& _direction ) const;

	/**
	 * @brief      Projects a given point on the plane.
	 * @param[in]  <unnamed>  The point.
	 * @return     A point lying on the plane which is a projection of the input.
	 */
	Point<Number> projectPointOnPlane( const Point<Number> ) const;

	/**
	 * @brief      Computes the intersection of a vector with the plane.
	 * @param      _result  The resulting scaling factor required to determine the intersection point.
	 * @param[in]  _vector  The vector.
	 * @return     True, if the vector intersects the plane, false otherwise.
	 */
	bool intersection( Number& _result, const vector_t<Number>& _vector ) const;

	/**
	 * @brief      Computes the intersection of a vector with the plane.
	 * @param      _result  The resulting scaling factor required to determine the intersection point.
	 * @param[in]  _vector  The vector.
	 * @return     True, if the vector intersects the plane, false otherwise.
	 */
	bool intersection( Number& _result, const Point<Number>& _vector ) const;

	/**
	 * @brief      Projects the halfspace on the given dimensions. Note that this corresponds to a projection
	 * of the normal vector without any re-scaling.
	 * @param[in]  dimensions  The dimensions.
	 * @return     The projected halfspace.
	 */
	Halfspace<Number> projectOn( const std::vector<size_t>& dimensions ) const;

	/**
	 * @brief      Computes the linear transformation of the plane.
	 * @param[in]  A     The transformation matrix.
	 * @return     The resulting halfspace.
	 */
	Halfspace<Number> linearTransformation( const matrix_t<Number>& A ) const;

	/**
	 * @brief      Computes the affine transformation of the plane.
	 * @param[in]  A     The transformation matrix.
	 * @param[in]  b     The transformation vector.
	 * @return     The resulting halfspace.
	 */
	Halfspace<Number> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;

	/**
	 * @brief      Computes the vector describing the intersection of two hyperplanes.
	 * @param[in]  _rhs  The right hand side.
	 * @return     The intersection vector.
	 */
	vector_t<Number> intersectionVector( const Halfspace<Number>& _rhs ) const;

	static vector_t<Number> fastIntersect( const std::vector<Halfspace<Number>>& _planes );
	static vector_t<Number> saveIntersect( const std::vector<Halfspace<Number>>& _planes, Number threshold = 0 );

	/**
	 * @brief      Determines, whether the point given as a vector is contained in the halfspace.
	 * @param[in]  _vector  The vector.
	 * @return     True, if it is contained, false otherwise.
	 */
	bool contains( const vector_t<Number> _vector ) const;

	/**
	 * @brief      Determines whether the given point is contained inside the halfspace.
	 * @param[in]  _vector  The point.
	 * @return     True, if it is contained, false otherwise.
	 */
	bool contains( const Point<Number> _vector ) const;

	/**
	 * @brief      Determines, whether the given set of points is contained inside the halfspace.
	 * @param[in]  _points  The points.
	 * @return     True, if all points are contained, false otherwise.
	 */
	bool contains( const std::vector<Point<Number>>& _points ) const;

	/**
	 * @brief Determines, whether the given point is contained inside the halfspace using exact arithmetic.
	 * @param[in] point The point.
	 * @return True iff the point is contained.
	 */
	bool exactContains( vector_t<Number> const& point ) const;

	/**
	 * @brief      Determines, whether the point given as a vector saturates the halfspace, i.e. lies on
	 * its bounding plane.
	 * @param[in]  _vector  The vector.
	 * @return     True, if the point lies on the plane, false otherwise.
	 */
	bool holds( const vector_t<Number> _vector ) const;

	/**
	 * @brief      The swap operator.
	 * @param      a     The left-hand-side.
	 * @param      b     The right-hand-side.
	 */
	friend void swap( Halfspace<Number>& a, Halfspace<Number>& b ) {
		swap( a.mNormal, b.mNormal );
		swap( a.mScalar, b.mScalar );
	}

	/**
	 * @author 	Chris K
	 * @brief 	Method to compute the normal of a plane based on two direction vectors
	 * simply computing the cross product does not work since the dimension is not necessarily 3.
	 * @param[in] The set of vectors.
	 * @return 		A vector representing the resulting plane normal.
	 */
	static vector_t<Number> computePlaneNormal( const std::vector<vector_t<Number>>& pointSet );

	/**
	 * @brief      Calculates the plane offset of a given normal vector for that plane and a point lying on the plane.
	 * This corresponds to the dot product of the normal vector and the negated point coordinates.
	 * @param[in]  normal        The normal.
	 * @param[in]  pointOnPlane  The point on plane.
	 * @return     The plane offset.
	 */
	static Number computePlaneOffset( const vector_t<Number>& normal, const Point<Number>& pointOnPlane );

	/**
	 * Functions for SupportFunctionNew where it is seen as a representation
	 */

	/**
	 * @brief Return mNormal as a matrix
	 */
	matrix_t<Number> matrix() const;

	/**
	 * @brief Return mScalar as a vector
	 */
	vector_t<Number> vector() const;

	/**
	 * @brief Return whether the halfspace is empty.
	 * @detail A halfspace itself cannot be empty, except its normal is the zero vector and the scalar is smaller than 0
	 */
	bool empty() const;

	/**
	 * @brief Removes redundancy.
	 */
	void removeRedundancy() { /* Does nothing since a halfpsace cannot have redundancy */
	}

	/**
	 * @brief Return the steps needed in the given direction to reach the optimal point.
	 * @param[in] direction The direction to evaluate
	 * @return Whether it is feasible, and if it is, how much steps are needed.
	 */
	EvaluationResult<Number> evaluate( const vector_t<Number>& direction, bool /*useExact*/ ) const;

	/**
	 * @brief Return the evaluation result for multiple directions
	 * @param[in] _directions The directions to evaluate
	 * @return For each direction, whether the evaluation is feasible, and if it is, how many steps are needed
	 */
	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _directions, bool /*useExact*/ ) const;

	/**
	 * @brief Returns a point representation of the halfspace. which does not exist.
	 * @detail Although this function is nonsensical, it is needed in order to use the Halfspace class as a leaf in the
	 * SupportFunctionNew.
	 */
	std::vector<Point<Number>> vertices() const { return std::vector<Point<Number>>(); }

	/**
	 * @brief Returns the representation type of the halfspace.
	 * @detail Since adding an own representation name for halfspaces would greatly affect the code, it just returns
	 * constraint_set as the representation name as it is usually not used as a representation but still has defined
	 * representation name.
	 */
	static representation_name type() { return representation_name::constraint_set; }
};

/**
 * @brief      Conversion operator for the number type.
 * @param[in]  in    The plane to convert
 * @tparam     From  The original number type.
 * @tparam     To    The target number type.
 * @return     A halfspace in the desired number type.
 */
template <typename From, typename To>
Halfspace<To> convert( const Halfspace<From>& in ) {
	return Halfspace<To>( convert<From, To>( in.normal() ), carl::convert<From, To>( in.offset() ) );
}

/**
 * @brief      Outstream operator.
 * @param      _lhs    The outstream.
 * @param[in]  _rhs    The halfspace.
 * @tparam     Number  The number type of the halfspace.
 * @return     A reference to the outstream.
 */
template <typename Number>
std::ostream& operator<<( std::ostream& ostr, const Halfspace<Number>& _rhs ) {
	auto& pool = VariablePool::getInstance();
	ostr << "( ";
	bool first = true;
	for ( Eigen::Index i = 0; i < _rhs.normal().rows(); ++i ) {
		bool notnull = _rhs.normal()( i ) != 0;
		bool printVal = notnull && abs( _rhs.normal()( i ) ) != 1;
		bool neg = _rhs.normal()( i ) < 0;
		std::string varname = pool.carlVarByIndex( i ).name().empty() ? pool.carlVarByIndex( i ).name() : "x" + std::to_string( i );
		if ( notnull ) {
			if ( printVal ) {
				if ( first ) {
					first = false;
					if ( neg ) {
						ostr << " - " << -_rhs.normal()( i );
					} else {
						ostr << _rhs.normal()( i );
					}
					ostr << "·" << varname;
				} else {
					if ( neg ) {
						ostr << " - " << -_rhs.normal()( i );
					} else {
						ostr << " + " << _rhs.normal()( i );
					}
					ostr << "·" << varname;
				}
			} else {
				if ( first ) {
					first = false;
					if ( neg ) {
						ostr << "- ";
					}
					ostr << varname;
				} else {
					if ( neg ) {
						ostr << " - ";
					} else {
						ostr << " + ";
					}
					ostr << varname;
				}
			}
		}
	}
	ostr << " ≤ " << Number( _rhs.offset() ) << " )";
	return ostr;
}

/**
 * @brief      Comparison operator.
 * @param[in]  lhs     The left hand side.
 * @param[in]  rhs     The right hand side.
 * @tparam     Number  The number type.
 * @return     True, if both halfspaces are equal in terms of coefficients, false otherwise.
 */
template <typename Number>
bool operator==( const Halfspace<Number>& lhs, const Halfspace<Number>& rhs ) {
	return ( lhs.normal() == rhs.normal() && lhs.offset() == rhs.offset() );
}

/**
 * @brief      Operator less.
 * @details    Note that this operator uses SOME comparison (dimension wise) without any meaning. Only used
 * for STL containers.
 * @param[in]  lhs     The left hand side.
 * @param[in]  rhs     The right hand side.
 * @tparam     Number  The number type.
 * @return     True, if lhs < rhs according to the normal vector and the scalar, false otherwise.
 */
template <typename Number>
bool operator<( const Halfspace<Number>& lhs, const Halfspace<Number>& rhs ) {
	return ( lhs.normal() < rhs.normal() || ( lhs.normal() == rhs.normal() && lhs.offset() < rhs.offset() ) );
}

/**
 * @brief      Operator unary minus.
 * @details    Used to invert the halfspace.
 * @param[in]  _in     The halfspace.
 * @tparam     Number  The number type.
 * @return     The inverted halfspace.
 */
template <typename Number>
Halfspace<Number> operator-( const Halfspace<Number>& _in ) {
	Halfspace<Number> tmp( _in );
	tmp.invert();
	return tmp;
}

#ifdef EXTERNALIZE_CLASSES
extern template class Halfspace<double>;
extern template class Halfspace<mpq_class>;
#endif
}  // namespace hypro

namespace std {
/**
 * @brief      Hash operator for halfspaces.
 * @tparam     Number  The number type.
 */
template <class Number>
struct hash<hypro::Halfspace<Number>> {
	std::size_t operator()( hypro::Halfspace<Number> const& Halfspace ) const {
		size_t seed = 0;
		hypro::vector_t<Number> normal = Halfspace.normal();
		Number scalar = Halfspace.scalar();
		std::hash<hypro::vector_t<Number>> vectorHasher;
		std::hash<Number> numberHasher;
		seed = vectorHasher( normal );
		carl::hash_add( seed, numberHasher( scalar ) );
		return seed;
	}
};
}  // namespace std

#include "Halfspace.tpp"
