
#pragma once

#ifndef INCL_FROM_GOHEADER
	static_assert(false, "This file may only be included indirectly by GeometricObject.h");
#endif

#include "SimplexSetting.h"
#include "../../util/linearOptimization/Optimizer.h"
#include "../../util/logging/Logger.h"

namespace hypro {


/**
 * @brief      The class which represents a Simplex.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * @tparam	   Settings   The used settings.
 * \ingroup geoState @{
 */
template <typename Number, typename Converter, class Setting>
class SimplexT : public GeometricObject<Number, SimplexT<Number,Converter,Setting>> {
  private:
  public:
  protected:

	/***************************************************************************
	 * Members
	 **************************************************************************/

  public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

	/**
	 * @brief      Creates an empty Simplex.
	 */
	SimplexT();

	/**
	 * @brief      Copy constructor.
	 * @param[in]  orig  The original.
	 */
	SimplexT( const SimplexT& orig );

	/**
	 * @brief      Settings conversion constructor.
	 * @param[in]  orig  The original.
	 */
	template<typename SettingRhs, carl::DisableIf< std::is_same<Setting, SettingRhs> > = carl::dummy>
	SimplexT(const SimplexT<Number,Converter,SettingRhs>& orig) {

	}

	/**
	 * @brief      Move constructor.
	 * @param[in]  orig  The original.
	 */
	SimplexT( SimplexT&& orig );

	/**
	 * @brief Destructor.
	 */
	~SimplexT() {}

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

	Setting getSettings() const { return Setting{}; }

	 /**
	  * @brief Static method for the construction of an empty Simplex of required dimension.
	  * @param dimension Required dimension.
	  * @return Empty Simplex.
	  */
	static SimplexT<Number,Converter,Setting> Empty(std::size_t dimension = 1) {
		return SimplexT<Number,Converter,Setting>();
	}

	/**
	 * @brief Determines if the current Simplex is empty.
	 * @return True, if Simplex is empty. False otherwise.
	 */
	bool empty() const;

	/**
	 * @brief Method returning the supremum point of the Simplex, i.e. the maximal point.
	 * @return A point representing the supremum of the current Simplex.
	 */
	Number supremum() const;

	/**
	 * @brief Getter for a vertex-representation of the current Simplex.
	 * @return A vector of points.
	 */
	std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero(0,0) ) const;

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
	 * @brief Checks if two Simplexs are equal.
	 * @param b1 Contains the first Simplex.
	 * @param b2 Contains the second Simplex.
	 * @return True, if they are equal.
	 */
	template<class SettingRhs>
	friend bool operator==( const SimplexT<Number,Converter,Setting>& b1, const SimplexT<Number,Converter,SettingRhs>& b2 ) {
		return false;
	}

	/**
	 * @brief Determines inequality of two Simplexes.
	 * @param b1 A Simplex.
	 * @param b2 A Simplex.
	 * @return False, if both Simplexes are equal.
	 */
	friend bool operator!=( const SimplexT<Number,Converter,Setting>& b1, const SimplexT<Number,Converter,Setting>& b2 ) { return !( b1 == b2 ); }

	/**
	 * @brief Assignment operator.
	 * @param rhs A Simplex.
	 */
	SimplexT<Number,Converter,Setting>& operator=( const SimplexT<Number,Converter,Setting>& rhs ) = default;

	/**
	 * @brief Move assignment operator.
	 * @param rhs A Simplex.
	 */
	SimplexT<Number,Converter,Setting>& operator=(SimplexT<Number,Converter,Setting>&& rhs) = default;

	/**
	 * @brief Outstream operator.
	 * @param ostr Outstream.
	 * @param b A Simplex.
	 */
#ifdef HYPRO_LOGGING
	friend std::ostream& operator<<( std::ostream& ostr, const SimplexT<Number,Converter,Setting>& b ) {
		// Put outstream operations here.
#else
	friend std::ostream& operator<<( std::ostream& ostr, const SimplexT<Number,Converter,Setting>& ) {
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

	static representation_name type() { return representation_name::simplex; }

	/**
	 * @brief      Function to reduce the number representation (over-approximate).
	 * @param[in]  limit      The limit
	 */
	const SimplexT<Number,Converter,Setting>& reduceNumberRepresentation();


	std::pair<CONTAINMENT, SimplexT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT, SimplexT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	SimplexT<Number,Converter,Setting> project(const std::vector<std::size_t>& dimensions) const;
	SimplexT<Number,Converter,Setting> linearTransformation( const matrix_t<Number>& A ) const;
	SimplexT<Number,Converter,Setting> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	SimplexT<Number,Converter,Setting> minkowskiSum( const SimplexT<Number,Converter,Setting>& rhs ) const;

	/**
	 * @brief      Computes the intersection of two Simplexes.
	 * @param[in]  rhs   The right hand side Simplex.
	 * @return     The resulting Simplex.
	 */
	SimplexT<Number,Converter,Setting> intersect( const SimplexT<Number,Converter,Setting>& rhs ) const;

	SimplexT<Number,Converter,Setting> intersectHalfspace( const Halfspace<Number>& hspace ) const;
	SimplexT<Number,Converter,Setting> intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& point ) const;

	/**
	 * @brief      Containment check for a Simplex.
	 * @param[in]  Simplex   The Simplex.
	 * @return     True, if the given Simplex is contained in the current Simplex, false otherwise.
	 */
	bool contains( const SimplexT<Number,Converter,Setting>& Simplex ) const;

	/**
	 * @brief      Computes the union of two Simplexes.
	 * @param[in]  rhs   The right hand side Simplex.
	 * @return     The resulting Simplex.
	 */
	SimplexT<Number,Converter,Setting> unite( const SimplexT<Number,Converter,Setting>& rhs ) const;

	/**
	 * @brief      Computes the union of the current Simplex with a set of Simplexes.
	 * @param[in]  Simplexes  The Simplexes.
	 * @return     The resulting Simplex.
	 */
	static SimplexT<Number,Converter,Setting> unite( const std::vector<SimplexT<Number,Converter,Setting>>& Simplexes );

	/**
	 * @brief      Reduces the representation of the current Simplex.
	 */
	void reduceRepresentation();

	/**
	 * @brief      Makes this Simplex equal to the empty Simplex.
	 */
	void clear();

};
/** @} */


} // namespace hypro

#include "Simplex.tpp"
