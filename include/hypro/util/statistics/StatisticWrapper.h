#include "../../representations/GeometricObjectBase.h"

namespace hypro {

/**
 * @brief      Wrapper class which allows to create traces of operations on state set representations.
 * @tparam     Representation  { The underlying state set representation. }
 */
template <typename Representation>
class StatisticWrapper : private GeometricObjectBase {
  private:
	Representation mObject;

  public:
	/**
	 * @brief      Destroys the object.
	 */
	virtual ~GeometricObjectBase() {}

	/**
	 * @brief      Returns the space dimension of the object.
	 * @return     The dimension.
	 */
	std::size_t dimension() const {
		return mObject.dimension();
	}

	/**
	 * @brief      Determines, whether the set is empty.
	 * @return     True, if the set is empty, false otherwise.
	 */
	bool empty() const {
		return mObject.empty();
	}

	/**
	 * @brief      Computes the set of extreme vertices, whose convex hull is the smallest convex set containing this set.
	 * @return     A set of extreme vertices.
	 */
	std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero( 0, 0 ) ) const {
		return mObject.vertices();
	}

	/**
	 * @brief      Method combining the intersection of the set with a halfspace and a test for emptiness of the resulting set.
	 * @param[in]  rhs   The halfspace. Note that this check is at least as fast as
	 * 			   performing the intersection and testing for emptiness, but in general we encourage to use this method instead.
	 * @return     A pair of a CONTAINMENT type stating whether the resulting set is empty and the resulting set.
	 */
	std::pair<CONTAINMENT, StatisticWrapper<Representation>> satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
		return mObject.satisfiesHalfspace( rhs );
	}

	/**
	 * @brief      Method combining the intersection of the set with a set of halfspaces and a test for emptiness of the resulting set.
	 * @details    The halfspaces are given as a matrix A and a vector b such that the resulting intersection of the set S with the set
	 * 			   of halfspaces is the set R = \f$ \{ x | x \in S \land A\cdot x \leq b \} \f$. Note that this check is at least as fast as
	 * 			   performing the intersection and testing for emptiness, but in general we encourage to use this method instead.
	 * @param[in]  _mat  The matrix.
	 * @param[in]  _vec  The vector.
	 * @return     A pair of a CONTAINMENT type stating whether the resulting set is empty and the resulting set.
	 */
	std::pair<CONTAINMENT, StatisticWrapper<Representation>> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
		return mObject.satisfiesHalfspaces( _mat, _vec );
	}

	/**
	 * @brief      Projects the set on the ordered set of given dimensions.
	 * @param[in]  dimensions  The dimensions.
	 * @return     The resulting set.
	 */
	StatisticWrapper<Representation> projectOn( const std::vector<std::size_t>& dimensions ) const {
		return mObject.projectOn( dimensions );
	}

	/**
	 * @brief      Applies a linear transformation with the matrix A to the set.
	 * @details    The resulting set R is the result of the linear transformation of the set S with A such that \f$ R = \{ x | x \in A\cdot S \} \f$
	 * @param[in]  A     The matrix.
	 * @return     The resulting set.
	 */
	StatisticWrapper<Representation> linearTransformation( const matrix_t<Number>& A ) const {
		return mObject.linearTransformation( A );
	}

	/**
	 * @brief      Applies an affine transformation with the matrix A and the translation vector b to the set.
	 * @details    The resulting set R is the result of the affine transformation of the set S with A and b such that \f$ R = \{ x | x \in A\cdot S + b \} \f$
	 * @param[in]  A     The matrix.
	 * @param[in]  b     The vector.
	 * @return     The resulting set.
	 */
	StatisticWrapper<Representation> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
		return mObject.affineTransformation( A, b );
	}

	/**
	 * @brief      Computes Minkowski's sum of the current set and the passed set.
	 * @param[in]  rhs   The other passed set.
	 * @return     The resulting set.
	 */
	StatisticWrapper<Representation> minkowskiSum( const StatisticWrapper<Representation>& rhs ) const {
		return mObject.minkowskiSum( rhs );
	}

	/**
	 * @brief      Computes the intersection of the set with the given halfspace.
	 * @param[in]  rhs   The halfspace.
	 * @return     The resulting set.
	 */
	StatisticWrapper<Representation> intersectHalfspace( const Halfspace<Number>& rhs ) const {
		return mObject.intersectHalfspace( rhs );
	}

	/**
	 * @brief      Computes the intersection of the set with a set of halfspaces.
	 * @details    The halfspaces are given as a matrix A and a vector b such that the resulting intersection of the set S with the set
	 * 			   of halfspaces is the set R = \f$ \{ x | x \in S \land A\cdot x \leq b \} \f$.
	 * @param[in]  _mat  The matrix.
	 * @param[in]  _vec  The vector.
	 * @return     The resulting set.
	 */
	StatisticWrapper<Representation> intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
		return mObject.intersectHalfspaces( _mat, _vec );
	}

	/**
	 * @brief      Checks, whether the set contains the passed point.
	 * @param[in]  point  The point.
	 * @return     True, if the point lies inside the set, false otherwise.
	 */
	bool contains( const Point<Number>& point ) const {
		return mObject.contains( point );
	}

	/**
	 * @brief      Computes the convex hull of the union of the set and the passed set.
	 * @param[in]  rhs   The passed set.
	 * @return     The resulting set.
	 */
	StatisticWrapper<Representation> unite( const StatisticWrapper<Representation>& rhs ) const {
		return mObject.unite( rhs );
	}

	/**
	 * @brief      Outstream operator.
	 * @param      out   The outstream.
	 * @param[in]  obj   The object.
	 * @return     Reference to the passed outstream.
	 */
	friend std::ostream& operator<<( std::ostream& out, const GeometricObjectBase<Number, StatisticWrapper<Representation>>& in ) {
		return out << mObject;
	}
};

}  // namespace hypro
