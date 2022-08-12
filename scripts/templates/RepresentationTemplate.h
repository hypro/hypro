
#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert(
	  false,
	  "This file may only be included indirectly by GeometricObjectBase.h" );
#endif

#include "../../util/linearOptimization/Optimizer.h"
#include "../../util/logging/Logger.h"
#include "REPRESENTATIONSetting.h"

namespace hypro {

/**
 * @brief      The class which represents a REPRESENTATION.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * @tparam	   Settings   The used settings.
 * \ingroup geoState @{
 */
template <typename Number, typename Converter, class Setting>
class REPRESENTATIONT : private GeometricObjectBase {
  private:
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
   * @brief      Creates an empty REPRESENTATION.
   */
	REPRESENTATIONT();

	/**
   * @brief      Copy constructor.
   * @param[in]  orig  The original.
   */
	REPRESENTATIONT( const REPRESENTATIONT& orig );

	/**
   * @brief      Settings conversion constructor.
   * @param[in]  orig  The original.
   */
	template <typename SettingRhs,
			  carl::DisableIf<std::is_same<Setting, SettingRhs>> = carl::dummy>
	REPRESENTATIONT( const REPRESENTATIONT<Number, Converter, SettingRhs>& orig ) {}

	/**
   * @brief      Move constructor.
   * @param[in]  orig  The original.
   */
	REPRESENTATIONT( REPRESENTATIONT&& orig );

	/**
   * @brief Destructor.
   */
	~REPRESENTATIONT() {}

	/***************************************************************************
   * Getters & setters
   **************************************************************************/

	Setting getSettings() const { return Setting{}; }

	/**
   * @brief Static method for the construction of an empty REPRESENTATION of
   * required dimension.
   * @param dimension Required dimension.
   * @return Empty REPRESENTATION.
   */
	static REPRESENTATIONT<Number, Converter, Setting> Empty() {
		return REPRESENTATIONT<Number, Converter, Setting>();
	}

	/**
   * @brief Determines if the current REPRESENTATION is empty.
   * @return True, if REPRESENTATION is empty. False otherwise.
   */
	bool empty() const;

	/**
   * @brief Method returning the supremum point of the REPRESENTATION, i.e. the
   * maximal point.
   * @return A point representing the supremum of the current REPRESENTATION.
   */
	Number supremum() const;

	/**
   * @brief Getter for a vertex-representation of the current REPRESENTATION.
   * @return A vector of points.
   */
	std::vector<Point<Number>>
	vertices( const matrix_t<Number>& = matrix_t<Number>::Zero( 0, 0 ) ) const;

	/**
   * @brief      Evaluation function (convex linear optimization).
   * @param[in]  _direction  The direction/cost function.
   * @return     Maximum towards _direction.
   */
	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction,
									   bool ) const;

	/**
   * @brief      Multi-evaluation function (convex linear optimization).
   * @param[in]  _directions  The directions/cost functions.
   * @return     A set of maxima towards the respective directions.
   */
	std::vector<EvaluationResult<Number>>
	multiEvaluate( const matrix_t<Number>& _directions,
				   bool useExact = true ) const;

	/**
   * @brief Checks if two REPRESENTATIONs are equal.
   * @param b1 Contains the first REPRESENTATION.
   * @param b2 Contains the second REPRESENTATION.
   * @return True, if they are equal.
   */
	template <class SettingRhs>
	friend bool
	operator==( const REPRESENTATIONT<Number, Converter, Setting>& b1,
				const REPRESENTATIONT<Number, Converter, SettingRhs>& b2 ) {
		return false;
	}

	/**
   * @brief Determines inequality of two REPRESENTATIONes.
   * @param b1 A REPRESENTATION.
   * @param b2 A REPRESENTATION.
   * @return False, if both REPRESENTATIONes are equal.
   */
	friend bool
	operator!=( const REPRESENTATIONT<Number, Converter, Setting>& b1,
				const REPRESENTATIONT<Number, Converter, Setting>& b2 ) {
		return !( b1 == b2 );
	}

	/**
   * @brief Assignment operator.
   * @param rhs A REPRESENTATION.
   */
	REPRESENTATIONT<Number, Converter, Setting>&
	operator=( const REPRESENTATIONT<Number, Converter, Setting>& rhs ) = default;

	/**
   * @brief Move assignment operator.
   * @param rhs A REPRESENTATION.
   */
	REPRESENTATIONT<Number, Converter, Setting>&
	operator=( REPRESENTATIONT<Number, Converter, Setting>&& rhs ) = default;

	/**
   * @brief Outstream operator.
   * @param ostr Outstream.
   * @param b A REPRESENTATION.
   */
	friend std::ostream&
	operator<<( std::ostream& ostr,
				const REPRESENTATIONT<Number, Converter, Setting>& b ) {
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

	static representation_name type() {
		return representation_name::REPRESENTATION_SHORT;
	}

	/**
   * @brief      Function to reduce the number representation
   * (over-approximate).
   * @param[in]  limit      The limit
   */
	const REPRESENTATIONT<Number, Converter, Setting>&
	reduceNumberRepresentation();

	std::pair<CONTAINMENT, REPRESENTATIONT>
	satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT, REPRESENTATIONT>
	satisfiesHalfspaces( const matrix_t<Number>& _mat,
						 const vector_t<Number>& _vec ) const;
	REPRESENTATIONT<Number, Converter, Setting>
	projectOn( const std::vector<std::size_t>& dimensions ) const;
	REPRESENTATIONT<Number, Converter, Setting>
	linearTransformation( const matrix_t<Number>& A ) const;
	REPRESENTATIONT<Number, Converter, Setting>
	affineTransformation( const matrix_t<Number>& A,
						  const vector_t<Number>& b ) const;
	REPRESENTATIONT<Number, Converter, Setting>
	minkowskiSum( const REPRESENTATIONT<Number, Converter, Setting>& rhs ) const;

	/**
   * @brief      Computes the intersection of two REPRESENTATIONes.
   * @param[in]  rhs   The right hand side REPRESENTATION.
   * @return     The resulting REPRESENTATION.
   */
	REPRESENTATIONT<Number, Converter, Setting>
	intersect( const REPRESENTATIONT<Number, Converter, Setting>& rhs ) const;

	REPRESENTATIONT<Number, Converter, Setting>
	intersectHalfspace( const Halfspace<Number>& hspace ) const;
	REPRESENTATIONT<Number, Converter, Setting>
	intersectHalfspaces( const matrix_t<Number>& _mat,
						 const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& point ) const;

	/**
   * @brief      Containment check for a REPRESENTATION.
   * @param[in]  REPRESENTATION   The REPRESENTATION.
   * @return     True, if the given REPRESENTATION is contained in the current
   * REPRESENTATION, false otherwise.
   */
	bool contains(
		  const REPRESENTATIONT<Number, Converter, Setting>& REPRESENTATION ) const;

	/**
   * @brief      Computes the union of two REPRESENTATIONes.
   * @param[in]  rhs   The right hand side REPRESENTATION.
   * @return     The resulting REPRESENTATION.
   */
	REPRESENTATIONT<Number, Converter, Setting>
	unite( const REPRESENTATIONT<Number, Converter, Setting>& rhs ) const;

	/**
   * @brief      Computes the union of the current REPRESENTATION with a set of
   * REPRESENTATIONes.
   * @param[in]  REPRESENTATIONes  The REPRESENTATIONes.
   * @return     The resulting REPRESENTATION.
   */
	static REPRESENTATIONT<Number, Converter, Setting>
	unite( const std::vector<REPRESENTATIONT<Number, Converter, Setting>>& REPRESENTATIONes );

	/**
   * @brief      Reduces the representation of the current REPRESENTATION.
   */
	void reduceRepresentation();

	/**
   * @brief      Makes this REPRESENTATION equal to the empty REPRESENTATION.
   */
	void clear();
};
/** @} */

}  // namespace hypro

#include "REPRESENTATION.tpp"
