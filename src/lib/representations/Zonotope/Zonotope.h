/* *
 * Zonotope class representation for use in reachability analysis
 *
 * File:   Zonotope.h
 * @author Jonathan Gan, Ibtissem Ben Makhlouf {gan, makhlouf} @ embedded.rwth-aachen.de
 * @version 1.0 on June 19, 2014, 10:25 PM
 *
 * Reviewed by Leonardo Winter Pereira (leonardowinterpereira@gmail.com)
 * function corners now totally works! (Complexity now is O(2^n), but n is only the amount of different generators (which isn't too much))
 * version 1.1 on September 15, 2015
 */

#pragma once

#include "ZUtility.h"
#include "../../datastructures/Halfspace.h"

#include <vector>
#include <eigen3/Eigen/Dense>
#include <cmath>
#include <algorithm>
#include <valarray>

namespace hypro {

template<typename Number, typename Converter>
class ZonotopeT {
  private:
	std::size_t mDimension;
	hypro::vector_t<Number> mCenter;
	hypro::matrix_t<Number> mGenerators;

	void removeGenerator( unsigned int colToRemove );

  public:
	// Constructors and Destructors

	ZonotopeT();
	/**
	 * Constructor with dimension
	 * @param dimension Dimensionality of ZonotopeT
	 */
	ZonotopeT( std::size_t dimension );

	/**
	 * Constructs a ZonotopeT with center and generators.
	 * @param center A (nx1) vector
	 * @param generators A (nxm) vector
	 */
	ZonotopeT( const hypro::vector_t<Number>& center, const hypro::matrix_t<Number>& generators );

	/**
	 * Copy Constructor - constructs a zonotopeT from an existing one.
	 * @param other Another ZonotopeT, from which a new zonotopeT is constructed
	 */
	ZonotopeT( const ZonotopeT<Number,Converter>& other );

	/**
	 * Copy Constructor - constructs a 2D-zonotopeT of from an existing ND one.
	 * @param other : Another ZonotopeT, from which a new zonotopeT is constructed
	 * @param d1 : 1st dimension (0 <= d1 < other.dimension)
	 * @param d2 : 2nd dimension (0 <= d2 < other.dimension) d1!=d2
	 */
	ZonotopeT( const ZonotopeT<Number,Converter>& other, unsigned d1, unsigned d2 );

	virtual ~ZonotopeT();

	/*****************************************************************************
	*                                                                           *
	*      Public Functions - Getters and Setters and some misc functions       *
	*                                                                           *
	*****************************************************************************/

	/**
	 * Dimensionality of ZonotopeT
	 * @return the dimension
	 */
	std::size_t dimension() const;

	/**
	* Returns, whether the zonotopeT is empty.
	* @return
	*/
	bool empty() const;

	/**
	 * Replaces the current center with the parameter center
	 * @param center a nx1 matrix
	 */
	void setCenter( const hypro::vector_t<Number>& center );

	/**
	 * Replaces the current matrix of generators with the parameter generators
	 * @param new_generators a nxm matrix
	 */
	void setGenerators( const hypro::matrix_t<Number>& generators_ );

	/**
	 * Add generators to ZonotopeT. Simply performs setGenerators if generators was previously not initialized.
	 * @param generators
	 * @return true if able to add generators
	 */
	bool addGenerators( const hypro::matrix_t<Number>& generators );

	// Getters and Setters for center and generators
	hypro::vector_t<Number> center() const;
	hypro::matrix_t<Number> generators() const;

	/**
	 * Number of generators
	 * @return number of generators
	 */
	std::size_t numGenerators() const;

	/**
	 * Removes empty (null) columns in generator matrix
	 */
	void removeEmptyGenerators();

        /*
         * It's important to do it, so we can reduce the necessary amount of calls of corners!
         */
        void uniteEqualVectors();

	/**
	 * Changes the dimension of a ZonotopeT. if new_dim > old dim, new rows are initialized with null
	 * @param new_dim The new dimension of the ZonotopeT
	 * @return True, if change in dimension was successful
	 */
	bool changeDimension( std::size_t new_dim );

	/**
	 * Clears the generators and center of the ZonotopeT and sets dimensionality to zero
	 */
	void clear();

        void print() const;

	/*****************************************************************************
	*                                                                           *
	*                           Algorithm Functions                             *
	*                                                                           *
	*****************************************************************************/

	/**
	 * Applies the Minkowskisum of the given stateset and a second stateset.
	 * @param result The resulting stateset.
	 * @param rhs The other right-hand-side stateset. Is not modified.
	 * @return True if the operation has been successfully applied.
	 */
	ZonotopeT<Number,Converter> minkowskiSum( const ZonotopeT<Number,Converter>& rhs ) const;

	/**
	 * Applies a linear transformation on the given stateset.
	 * @param result The resulting stateset.
	 * @return True if the operation has been successfully applied.
	 */
	ZonotopeT<Number,Converter> linearTransformation( const hypro::matrix_t<Number>& A ) const;

	/**
	 * Compute boundaries of zonotopeT
	 * @return array of points represented as vectors
	 */
	std::vector<hypro::vector_t<Number>> computeZonotopeBoundary();

	/**
	 * @brief Compute a set of points containing the extreme points of a zonotopeT.
	 * @details Compute all possible extreme points of a zonotopeT by considering all combinations of
	 * generators. This gives a set of points, which contains also the real extreme points but also some
	 * internal points.
	 * @return vector of points.
	 */
	std::vector<hypro::vector_t<Number>> vertices() const;

	/**
	 * Calculates zonotopeT intersect with halfspace (represented as d*x <= e, where d is a column vector of dimension n
	 * and e a scalar)
	 * @param result : The resulting intersect
	 * @param d_vec : Vector representing the halfspace
	 * @param e_scalar : Scalar representing the halfspace
	 * @return true if intersect is found, false otherwise (result parameter is not modified if false)
	 */
	ZonotopeT<Number,Converter> intersectWithHalfspace( const hypro::vector_t<Number>& d_vec, Number e_scalar ) const;

	#ifdef USE_PPL
	/**
	 * Calculates zonotopeT intersect with halfspace represented as PPL constraint
	 * @param result : The resulting stateset of the intersection
	 * @param halfspace : Halfspace as represented in PPL (see PPL documentation for more information)
	 * @return true if intersect is found, false otherwise (result parameter is not modified if false)
	 */
	ZonotopeT<Number,Converter> intersect( const Parma_Polyhedra_Library::Constraint& halfspace ) const;
	#endif

	/**
	 * Intersects the given stateset with a second one.
	 * @param result The resulting stateset of the intersection.
	 * @param rhs The right-hand-side stateset. Is not modified.
	 * @return True if intersect is found
	 */
	ZonotopeT<Number,Converter> intersect( const Halfspace<Number>& rhs, int method );

	/**
	 * Intersects the given stateset with a second one and returns min-max only when NDPROJECTION method is used
	 * @param result : The resulting stateset of the intersection as zonotopeT.
	 * @param minMaxOfLine : The resulting min-max matrix.
	 * @param rhs : The right-hand-side stateset. Is not modified.
	 * @return True if intersect is found.
	 */
	ZonotopeT<Number,Converter> intersect( const Halfspace<Number>& rhs, hypro::matrix_t<Number>& minMaxOfLine, int method );

	#ifdef USE_PPL
	/**
	 * Calculates zonotopeT intersect with a closed polyhedron as represented in PPL.
	 * @param result : The resulting stateset of the intersection as zonotopeT.
	 * @param rhs : The closed polyhedron as represented in PPL (see PPL documentation for more information).
	 * @return true if intersect is found, false otherwise (result parameter is not modified if false)
	 */
	ZonotopeT<Number,Converter> intersect( const Parma_Polyhedra_Library::C_Polyhedron& rhs ) const;
	#endif

	/**
	 * Computes the convex hull of the member zonotopeT and another given zonotopeT
	 * @param result: resulting convex hull (also itself a zonotopeT)
	 * @param other: the other zonotopeT
	 * @return true for all cases.
	 */
	ZonotopeT<Number,Converter> unite( const ZonotopeT<Number,Converter>& other ) const;

	/**
	 * Computes the interval hull of the member zonotopeT
	 * @param result: the resulting interval hull (also a zonotopeT)
	 * @return true for all cases
	 */
	ZonotopeT<Number,Converter> intervalHull() const;
};

}  // namespace

#include "Zonotope.tpp"
