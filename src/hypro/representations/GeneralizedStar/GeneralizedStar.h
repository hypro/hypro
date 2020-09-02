
#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert( false, "This file may only be included indirectly by GeometricObjectBase.h" );
#endif

#include "../../util/linearOptimization/Optimizer.h"
#include "../../util/logging/Logger.h"
#include "GeneralizedStarSetting.h"

namespace hypro {

/**
 * @brief      The class which represents a GeneralizedStar.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * @tparam	   Settings   The used settings.
 * \ingroup geoState @{
 */
template <typename Number, typename Converter, class Setting>
class GeneralizedStarT : private GeometricObjectBase {
  private:
	vector_t<Number> mCenter;
	matrix_t<Number> mBasis;

  public:
	typedef Number NumberType;
	typedef Setting Settings;

  protected:
	/***************************************************************************
	 * Members
	 **************************************************************************/

  public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

	/**
	 * @brief      Creates an empty GeneralizedStar.
	 */
	GeneralizedStarT();

	/**
	 * @brief      Copy constructor.
	 * @param[in]  orig  The original.
	 */
	GeneralizedStarT( const GeneralizedStarT& orig );

	/**
	 * @brief      Settings conversion constructor.
	 * @param[in]  orig  The original.
	 */
	template <typename SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>> = carl::dummy>
	GeneralizedStarT( const GeneralizedStarT<Number, Converter, SettingRhs>& orig ) {
	}

	/**
	 * @brief      Move constructor.
	 * @param[in]  orig  The original.
	 */
	GeneralizedStarT( GeneralizedStarT&& orig );

	/**
	 * @brief Destructor.
	 */
	~GeneralizedStarT() {}

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

	Setting getSettings() const { return Setting{}; }

	/**
	  * @brief Static method for the construction of an empty GeneralizedStar of required dimension.
	  * @param dimension Required dimension.
	  * @return Empty GeneralizedStar.
	  */
	static GeneralizedStarT Empty() {
		return GeneralizedStarT();
	}

	/**
	 * @brief Determines if the current GeneralizedStar is empty.
	 * @return True, if GeneralizedStar is empty. False otherwise.
	 */
	bool empty() const;

	/**
	 * @brief Method returning the supremum point of the GeneralizedStar, i.e. the maximal point.
	 * @return A point representing the supremum of the current GeneralizedStar.
	 */
	Number supremum() const;

	/**
	 * @brief Getter for a vertex-representation of the current GeneralizedStar.
	 * @return A vector of points.
	 */
	std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero( 0, 0 ) ) const;

	/**
	 * @brief      Evaluation function (convex linear optimization).
	 * @param[in]  _direction  The direction/cost function.
	 * @return     Maximum towards _direction.
	 */
	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction, bool ) const;

	/**
	 * @brief      Multi-evaluation function (convex linear optimization).
	 * @param[in]  _directions  The directions/cost functions.
	 * @return     A set of maxima towards the respective directions.
	 */
	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _directions, bool useExact = true ) const;

	/**
	 * @brief Checks if two GeneralizedStars are equal.
	 * @param b1 Contains the first GeneralizedStar.
	 * @param b2 Contains the second GeneralizedStar.
	 * @return True, if they are equal.
	 */
	template <class SettingRhs>
	friend bool operator==( const GeneralizedStarT<Number, Converter, Setting>& b1, const GeneralizedStarT<Number, Converter, SettingRhs>& b2 ) {
		return false;
	}

	/**
	 * @brief Determines inequality of two GeneralizedStares.
	 * @param b1 A GeneralizedStar.
	 * @param b2 A GeneralizedStar.
	 * @return False, if both GeneralizedStares are equal.
	 */
	friend bool operator!=( const GeneralizedStarT<Number, Converter, Setting>& b1, const GeneralizedStarT<Number, Converter, Setting>& b2 ) { return !( b1 == b2 ); }

	/**
	 * @brief Assignment operator.
	 * @param rhs A GeneralizedStar.
	 */
	GeneralizedStarT<Number, Converter, Setting>& operator=( const GeneralizedStarT<Number, Converter, Setting>& rhs ) = default;

	/**
	 * @brief Move assignment operator.
	 * @param rhs A GeneralizedStar.
	 */
	GeneralizedStarT<Number, Converter, Setting>& operator=( GeneralizedStarT<Number, Converter, Setting>&& rhs ) = default;

	/**
	 * @brief Outstream operator.
	 * @param ostr Outstream.
	 * @param b A GeneralizedStar.
	 */
	friend std::ostream& operator<<( std::ostream& ostr, const GeneralizedStarT<Number, Converter, Setting>& b ) {
		// Put outstream operations here.
		return ostr;
	}

	/***************************************************************************
	 * General interface
	 **************************************************************************/

	/**
	  * @brief      Getter for the space dimension.
	  * @return     The dimension of the space.
	  */
	std::size_t dimension() const;

	/**
	 * @brief      Removes redundancy.
	 */
	void removeRedundancy();

	/**
	 * @brief      Storage size determination.
	 * @return     Size of the required memory.
	 */
	std::size_t size() const;

	static representation_name type() { return representation_name::genStar; }

	/**
	 * @brief      Function to reduce the number representation (over-approximate).
	 * @param[in]  limit      The limit
	 */
	const GeneralizedStarT& reduceNumberRepresentation();

	std::pair<CONTAINMENT, GeneralizedStarT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT, GeneralizedStarT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	GeneralizedStarT projectOn( const std::vector<std::size_t>& dimensions ) const;
	GeneralizedStarT assignIntervals( const std::map<std::size_t, carl::Interval<Number>>& ) const {
		WARN( "hypro", "Not implemented." );
		return *this;
	}
	GeneralizedStarT linearTransformation( const matrix_t<Number>& A ) const;
	GeneralizedStarT affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	GeneralizedStarT minkowskiSum( const GeneralizedStarT& rhs ) const;

	/**
	 * @brief      Computes the intersection of two GeneralizedStares.
	 * @param[in]  rhs   The right hand side GeneralizedStar.
	 * @return     The resulting GeneralizedStar.
	 */
	GeneralizedStarT intersect( const GeneralizedStarT& rhs ) const;

	GeneralizedStarT intersectHalfspace( const Halfspace<Number>& hspace ) const;
	GeneralizedStarT intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& point ) const;

	/**
	 * @brief      Containment check for a GeneralizedStar.
	 * @param[in]  GeneralizedStar   The GeneralizedStar.
	 * @return     True, if the given GeneralizedStar is contained in the current GeneralizedStar, false otherwise.
	 */
	bool contains( const GeneralizedStarT& GeneralizedStar ) const;

	/**
	 * @brief      Computes the union of two GeneralizedStares.
	 * @param[in]  rhs   The right hand side GeneralizedStar.
	 * @return     The resulting GeneralizedStar.
	 */
	GeneralizedStarT unite( const GeneralizedStarT& rhs ) const;

	/**
	 * @brief      Computes the union of the current GeneralizedStar with a set of GeneralizedStares.
	 * @param[in]  GeneralizedStares  The GeneralizedStares.
	 * @return     The resulting GeneralizedStar.
	 */
	static GeneralizedStarT unite( const std::vector<GeneralizedStarT>& GeneralizedStares );

	/**
	 * @brief      Reduces the representation of the current GeneralizedStar.
	 */
	void reduceRepresentation();

	/**
	 * @brief      Makes this GeneralizedStar equal to the empty GeneralizedStar.
	 */
	void clear();
};
/** @} */

}  // namespace hypro

#include "GeneralizedStar.tpp"
