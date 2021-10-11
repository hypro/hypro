
#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert(
	  false,
	  "This file may only be included indirectly by GeometricObjectBase.h" );
#endif

#include "../../util/linearOptimization/Optimizer.h"
#include "../../util/logging/Logger.h"
#include "../types.h"
#include "../../util/adaptions_eigen/adaptions_eigen.h"
#include "../../util/typetraits.h"
#include "../Polytopes/HPolytope/HPolytope.h"
#include "../Polytopes/HPolytope/HPolytopeSetting.h"
#include "StarsetSetting.h"

namespace hypro {

/**
 * @brief      The class which represents a Starset.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * @tparam	   Settings   The used settings.
 * \ingroup geoState @{
 */
template <typename Number, typename Converter, class Setting, class Representation=HPolytopeT<Number,Converter, HPolytopeSetting>>
class StarsetT : private GeometricObjectBase {
  private:
  public:
	typedef Number NumberType;
	typedef Setting Settings;

  protected:
	/***************************************************************************
   * Members
   **************************************************************************/
    //A*alpha<=d
    //center of the star domain
    vector_t<Number> mCenter;
    
    // A in the given equation above
 /*!< the right side of the condition A*alpha<=d . */

    matrix_t<Number> mGenerator;
    
	 Representation constraints;
    
  public:
	/***************************************************************************
   * Constructors
   **************************************************************************/

	/**
   * @brief      Creates an empty Starset.
   */
	StarsetT();
    
    /*
     * @brief   Creates a star set with generator, intervall and center  
     */
    StarsetT(const vector_t<Number>& center,const matrix_t<Number>& shapematrix,const vector_t<Number>& limits,const matrix_t<Number>& generator);
    /*
     * Starset with assuming standard basis and center as the origin
     * */
    StarsetT(const matrix_t<Number>& shapematrix,const vector_t<Number>& limits);
    StarsetT(const vector_t<Number>& center,const matrix_t<Number>& generator, const Representation Constraints);

   StarsetT(const Representation Constraints);
	/**
   * @brief      Copy constructor.
   * @param[in]  orig  The original.
   */
	StarsetT( const StarsetT& orig );


	/**
   * @brief      Settings conversion constructor.
   * @param[in]  orig  The original.
   */
	template <typename SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>> = carl::dummy>
	StarsetT( const StarsetT<Number, Converter, SettingRhs,Representation>& orig ) {}

	/**
   * @brief      Move constructor.
   * @param[in]  orig  The original.
   */
	StarsetT( StarsetT&& orig );

	/**
   * @brief Destructor.
   */
	~StarsetT() {}

	/***************************************************************************
   * Getters & setters
   **************************************************************************/
    
    //getters for the starset
    vector_t<Number> center() const;
	vector_t<Number> limits() const;
    matrix_t<Number>  shape() const;
    matrix_t<Number>  generator() const;
    Representation constraintss() const;
    
	Setting getSettings() const { return Setting{}; }

	/**
   * @brief Static method for the construction of an empty Starset of
   * required dimension.
   * @param dimension Required dimension.
   * @return Empty Starset.
   */
	static StarsetT<Number, Converter, Setting,Representation> Empty() {
		return StarsetT<Number, Converter, Setting,Representation>();
	}

	/**
   * @brief Determines if the current Starset is empty.
   * @return True, if Starset is empty. False otherwise.
   */
	bool empty() const;

	/**
   * @brief Method returning the supremum point of the Starset, i.e. the
   * maximal point.
   * @return A point representing the supremum of the current Starset.
   */
	Number supremum() const;

	/**
   * @brief Getter for a vertex-representation of the current Starset.
   * @return A vector of points.
   */
	std::vector<Point<Number>> vertices() const;

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
   * @brief Checks if two Starsets are equal.
   * @param b1 Contains the first Starset.
   * @param b2 Contains the second Starset.
   * @return True, if they are equal.
   */
	template <class SettingRhs>
	friend bool
	operator==( const StarsetT<Number, Converter, Setting,Representation>& b1,
				const StarsetT<Number, Converter, SettingRhs,Representation>& b2 ) {
		return false;
	}

	/**
   * @brief Determines inequality of two Starsetes.
   * @param b1 A Starset.
   * @param b2 A Starset.
   * @return False, if both Starsetes are equal.
   */
	friend bool
	operator!=( const StarsetT<Number, Converter, Setting,Representation>& b1,
				const StarsetT<Number, Converter, Setting,Representation>& b2 ) {
		return !( b1 == b2 );
	}

	/**
   * @brief Assignment operator.
   * @param rhs A Starset.
   */
	StarsetT<Number, Converter, Setting,Representation>&
	operator=( const StarsetT<Number, Converter, Setting,Representation>& rhs ) = default;

	/**
   * @brief Move assignment operator.
   * @param rhs A Starset.
   */
	StarsetT<Number, Converter, Setting,Representation>&
	operator=( StarsetT<Number, Converter, Setting,Representation>&& rhs ) = default;

	/**
   * @brief Outstream operator.
   * @param ostr Outstream.
   * @param b A Starset.
   */
	friend std::ostream&
	operator<<( std::ostream& ostr,
				const StarsetT<Number, Converter, Setting,Representation>& b ) {
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
	StarsetT<Number, Converter, Setting,Representation> removeRedundancy();

	/**
   * @brief      Storage size determination.
   * @return     Size of the required memory.
   */
	std::size_t size() const;

	static representation_name type() {
		return representation_name::Starset;
	}

	/**
   * @brief      Function to reduce the number representation
   * (over-approximate).
   * @param[in]  limit      The limit
   */
	const StarsetT<Number, Converter, Setting,Representation>&
	reduceNumberRepresentation();

	std::pair<CONTAINMENT, StarsetT>
	satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT, StarsetT>
	satisfiesHalfspaces( const matrix_t<Number>& _mat,
						 const vector_t<Number>& _vec ) const;
	StarsetT<Number, Converter, Setting,Representation>
	projectOn( const std::vector<std::size_t>& dimensions ) const;
	StarsetT<Number, Converter, Setting,Representation>
	linearTransformation( const matrix_t<Number>& A ) const;
	StarsetT<Number, Converter, Setting,Representation>
	affineTransformation( const matrix_t<Number>& A,
						  const vector_t<Number>& b ) const;
	StarsetT<Number, Converter, Setting,Representation>
	minkowskiSum( const StarsetT<Number, Converter, Setting,Representation>& rhs ) const;

	/**
   * @brief      Computes the intersection of two Starsetes.
   * @param[in]  rhs   The right hand side Starset.
   * @return     The resulting Starset.
   */
	StarsetT<Number, Converter, Setting,Representation>
	intersect( const StarsetT<Number, Converter, Setting,Representation>& rhs ) const;

	StarsetT<Number, Converter, Setting,Representation>
	intersectHalfspace( const Halfspace<Number>& hspace ) const;
	StarsetT<Number, Converter, Setting,Representation>
	intersectHalfspaces( const matrix_t<Number>& _mat,
						 const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& point ) const;
   //StarsetT<Number, Converter, Setting,Representation>
	//checkifin( const Halfspace<Number>& hspace ) const;
   
   Halfspace<Number>	calculateHalfspace( const Halfspace<Number>& hspace ) const;

   std::pair<matrix_t<Number>, vector_t<Number>>
	calculateHalfspaces(const matrix_t<Number>& _mat, const vector_t<Number>& _vec  ) const;
	/**
   * @brief      Containment check for a Starset.
   * @param[in]  Starset   The Starset.
   * @return     True, if the given Starset is contained in the current
   * Starset, false otherwise.
   */
	bool contains(
		  const StarsetT<Number, Converter, Setting,Representation>& Starset ) const;

	/**
   * @brief      Computes the union of two Starsetes.
   * @param[in]  rhs   The right hand side Starset.
   * @return     The resulting Starset.
   */
	StarsetT<Number, Converter, Setting,Representation>
	unite( const StarsetT<Number, Converter, Setting,Representation>& rhs ) const;

	/**
   * @brief      Computes the union of the current Starset with a set of
   * Starsetes.
   * @param[in]  Starsetes  The Starsetes.
   * @return     The resulting Starset.
   */
	static StarsetT<Number, Converter, Setting,Representation>
	unite( const std::vector<StarsetT<Number, Converter, Setting,Representation>>& Starsetes );

	/**
   * @brief      Reduces the representation of the current Starset.
   */
	void reduceRepresentation();

	/**
   * @brief      Makes this Starset equal to the empty Starset.
   */
	void clear();
};
/** @} */
    /*
     * Conversion for different Data types
     */
    template <typename From, typename To, typename Converter, class Setting>
    StarsetT<To, Converter, Setting> convert( const StarsetT<From, Converter, Setting>& in ) {
        return StarsetT<To, Converter, Setting>( convert<From, To>( in.center() ), convert<From, To>( in.shape() ), convert<From, To>( in.limits() ),convert<From, To>( in.generator() ) );
}
}  // namespace hypro

#include "Starset.tpp"
