
#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert( false, "This file may only be included indirectly by GeometricObject.h" );
#endif

#include "../../util/linearOptimization/Optimizer.h"
#include "../../util/logging/Logger.h"
#include "OrthoplexSetting.h"

namespace hypro {

/**
 * @brief      The class which represents a Orthoplex.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * @tparam	   Settings   The used settings.
 * \ingroup geoState @{
 */
template <typename Number, typename Converter, class Setting>
class OrthoplexT : public GeometricObject<Number, OrthoplexT<Number, Converter, Setting>> {
  private:
  public:
	//Needed for Converter
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
	 * @brief      Creates an empty Orthoplex.
	 */
	OrthoplexT();

	/**
	 * @brief      Copy constructor.
	 * @param[in]  orig  The original.
	 */
	OrthoplexT( const OrthoplexT& orig );

	/**
	 * @brief      Settings conversion constructor.
	 * @param[in]  orig  The original.
	 */
	template <typename SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>> = carl::dummy>
	OrthoplexT( const OrthoplexT<Number, Converter, SettingRhs>& orig ) {
	}

	/**
	 * @brief      Move constructor.
	 * @param[in]  orig  The original.
	 */
	OrthoplexT( OrthoplexT&& orig );

	/**
	 * @brief Destructor.
	 */
	~OrthoplexT() {}

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

	Setting getSettings() const { return Setting{}; }

	/**
	  * @brief Static method for the construction of an empty Orthoplex of required dimension.
	  * @param dimension Required dimension.
	  * @return Empty Orthoplex.
	  */
	static OrthoplexT<Number, Converter, Setting> Empty( std::size_t dimension = 1 ) {
		return OrthoplexT<Number, Converter, Setting>();
	}

	/**
	 * @brief Determines if the current Orthoplex is empty.
	 * @return True, if Orthoplex is empty. False otherwise.
	 */
	bool empty() const;

	/**
	 * @brief Method returning the supremum point of the Orthoplex, i.e. the maximal point.
	 * @return A point representing the supremum of the current Orthoplex.
	 */
	Number supremum() const;

	/**
	 * @brief Getter for a vertex-representation of the current Orthoplex.
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
	 * @brief Checks if two Orthoplexs are equal.
	 * @param b1 Contains the first Orthoplex.
	 * @param b2 Contains the second Orthoplex.
	 * @return True, if they are equal.
	 */
	template <class SettingRhs>
	friend bool operator==( const OrthoplexT<Number, Converter, Setting>& b1, const OrthoplexT<Number, Converter, SettingRhs>& b2 ) {
		return false;
	}

	/**
	 * @brief Determines inequality of two Orthoplexes.
	 * @param b1 A Orthoplex.
	 * @param b2 A Orthoplex.
	 * @return False, if both Orthoplexes are equal.
	 */
	friend bool operator!=( const OrthoplexT<Number, Converter, Setting>& b1, const OrthoplexT<Number, Converter, Setting>& b2 ) { return !( b1 == b2 ); }

	/**
	 * @brief Assignment operator.
	 * @param rhs A Orthoplex.
	 */
	OrthoplexT<Number, Converter, Setting>& operator=( const OrthoplexT<Number, Converter, Setting>& rhs ) = default;

	/**
	 * @brief Move assignment operator.
	 * @param rhs A Orthoplex.
	 */
	OrthoplexT<Number, Converter, Setting>& operator=( OrthoplexT<Number, Converter, Setting>&& rhs ) = default;

	/**
	 * @brief Outstream operator.
	 * @param ostr Outstream.
	 * @param b A Orthoplex.
	 */
#ifdef HYPRO_LOGGING
	friend std::ostream& operator<<( std::ostream& ostr, const OrthoplexT<Number, Converter, Setting>& b ) {
		// Put outstream operations here.
#else
	friend std::ostream& operator<<( std::ostream& ostr, const OrthoplexT<Number, Converter, Setting>& ) {
#endif
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

	static representation_name type() { return representation_name::orthoplex; }

	/**
	 * @brief      Function to reduce the number representation (over-approximate).
	 * @param[in]  limit      The limit
	 */
	const OrthoplexT<Number, Converter, Setting>& reduceNumberRepresentation();

	std::pair<CONTAINMENT, OrthoplexT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT, OrthoplexT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	OrthoplexT<Number, Converter, Setting> projectOn( const std::vector<std::size_t>& dimensions ) const;
	OrthoplexT<Number, Converter, Setting> linearTransformation( const matrix_t<Number>& A ) const;
	OrthoplexT<Number, Converter, Setting> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	OrthoplexT<Number, Converter, Setting> minkowskiSum( const OrthoplexT<Number, Converter, Setting>& rhs ) const;

	/**
	 * @brief      Computes the intersection of two Orthoplexes.
	 * @param[in]  rhs   The right hand side Orthoplex.
	 * @return     The resulting Orthoplex.
	 */
	OrthoplexT<Number, Converter, Setting> intersect( const OrthoplexT<Number, Converter, Setting>& rhs ) const;

	OrthoplexT<Number, Converter, Setting> intersectHalfspace( const Halfspace<Number>& hspace ) const;
	OrthoplexT<Number, Converter, Setting> intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& point ) const;

	/**
	 * @brief      Containment check for a Orthoplex.
	 * @param[in]  Orthoplex   The Orthoplex.
	 * @return     True, if the given Orthoplex is contained in the current Orthoplex, false otherwise.
	 */
	bool contains( const OrthoplexT<Number, Converter, Setting>& Orthoplex ) const;

	/**
	 * @brief      Computes the union of two Orthoplexes.
	 * @param[in]  rhs   The right hand side Orthoplex.
	 * @return     The resulting Orthoplex.
	 */
	OrthoplexT<Number, Converter, Setting> unite( const OrthoplexT<Number, Converter, Setting>& rhs ) const;

	/**
	 * @brief      Computes the union of the current Orthoplex with a set of Orthoplexes.
	 * @param[in]  Orthoplexes  The Orthoplexes.
	 * @return     The resulting Orthoplex.
	 */
	OrthoplexT<Number, Converter, Setting> unite( const std::vector<OrthoplexT<Number, Converter, Setting>>& Orthoplexes );

	/**
	 * @brief      Reduces the representation of the current Orthoplex.
	 */
	void reduceRepresentation();

	/**
	 * @brief      Makes this Orthoplex equal to the empty Orthoplex.
	 */
	void clear();
};
/** @} */

}  // namespace hypro

#include "Orthoplex.tpp"
