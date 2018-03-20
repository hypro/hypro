/* *
 * Zonotope class representation for use in reachability analysis
 *
 * File:   Zonotope.h
 * @author Jonathan Gan, Ibtissem Ben Makhlouf {gan, makhlouf} @ embedded.rwth-aachen.de
 * @version 1.0 on June 19, 2014, 10:25 PM
 *
 * Reviewed by Leonardo Winter Pereira (leonardowinterpereira@gmail.com)
 * version 1.1 on September 15, 2015
 */

#pragma once

#ifndef INCL_FROM_GOHEADER
	static_assert(false, "This file may only be included indirectly by GeometricObject.h");
#endif

#include "ZUtility.h"
#include "ZonotopeSetting.h"
#include "../../datastructures/Halfspace.h"
#include "../../util/pca.h"
#include "../../util/adaptions_eigen/adaptions_eigen.h"

#include <vector>
#include <eigen3/Eigen/Dense>
#include <cmath>
#include <algorithm>
#include <valarray>

namespace hypro {

/**
 * @brief      Class for Zonotopes.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The converter.
 * \ingroup geoState @{
 */
template<typename Number, typename Converter>
class ZonotopeT : public GeometricObject<Number, ZonotopeT<Number,Converter>> {
  private:
	std::size_t mDimension;
	vector_t<Number> mCenter;
	//Each column in mGenerators is a generator
	matrix_t<Number> mGenerators;

	void removeGenerator( unsigned int colToRemove );

  public:
	// Constructors and Destructors

	ZonotopeT();
	/**
	 * Constructor with dimension
	 * @param dimension Dimensionality of ZonotopeT
	 */
	explicit ZonotopeT( std::size_t dimension );

	/**
	 * Constructs a ZonotopeT with center and generators.
	 * @param center A (nx1) vector
	 * @param generators A (nxm) vector
	 */
	ZonotopeT( const vector_t<Number>& center, const matrix_t<Number>& generators );

	/**
	 * Copy Constructor - constructs a zonotopeT from an existing one.
	 * @param other Another ZonotopeT, from which a new zonotopeT is constructed
	 */
	ZonotopeT( const ZonotopeT<Number,Converter>& other ) = default;

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

	Number supremum() const;

	/**
	* Returns, whether the zonotopeT is empty.
	* @return
	*/
	bool empty() const;


	static ZonotopeT<Number,Converter> Empty(std::size_t dimension = 1) {
		return ZonotopeT<Number,Converter>(vector_t<Number>::Zero(dimension), matrix_t<Number>(dimension,0));
	}

	static representation_name type() { return representation_name::zonotope; }

	/**
	 * Replaces the current center with the parameter center
	 * @param center a nx1 matrix
	 */
	void setCenter( const vector_t<Number>& center );

	/**
	 * Replaces the current matrix of generators with the parameter generators
	 * @param new_generators a nxm matrix
	 */
	void setGenerators( const matrix_t<Number>& generators_ );

	/**
	 * Add generators to ZonotopeT. Simply performs setGenerators if generators was previously not initialized.
	 * @param generators
	 * @return true if able to add generators
	 */
	bool addGenerators( const matrix_t<Number>& generators );

	// Getters and Setters for center and generators
	const vector_t<Number>& center() const;
	const matrix_t<Number>& generators() const;
	Number order() const;

	/**
	 * Number of generators
	 * @return number of generators
	 */
	std::size_t size() const;

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

    bool operator==(const ZonotopeT<Number,Converter>& rhs) const {
    	if(this->mDimension != rhs.dimension()) {
    		return false;
    	}
    	if(this->mCenter != rhs.center()) {
    		return false;
    	}
    	if(this->mGenerators != rhs.generators()) {
    		return false;
    	}
    	return true;
    }

    void removeRedundancy() const {}

    template<class Setting>
    void reduceOrder( Number limit = Number(Setting::ZONOTOPE_ORDERLIMIT) );

    void reduceNumberRepresentation();

	/*****************************************************************************
	*                                                                           *
	*                           Algorithm Functions                             *
	*                                                                           *
	*****************************************************************************/

	ZonotopeT<Number,Converter> minkowskiSum( const ZonotopeT<Number,Converter>& rhs ) const;
	ZonotopeT<Number,Converter> project( const std::vector<std::size_t>& dimensions ) const;
	ZonotopeT<Number,Converter> linearTransformation( const matrix_t<Number>& A) const;
	ZonotopeT<Number,Converter> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;

	/**
	 * Compute boundaries of zonotopeT
	 * @return array of points represented as vectors
	 */
	std::vector<vector_t<Number>> computeZonotopeBoundary();

	/**
	 * @brief Compute a set of points containing the extreme points of a zonotopeT.
	 * @details Compute all possible extreme points of a zonotopeT by considering all combinations of
	 * generators. This gives a set of points, which contains also the real extreme points but also some
	 * internal points.
	 * @return vector of points.
	 */
	std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero(0,0) ) const;

	ZonotopeT<Number,Converter> intersectHalfspace( const Halfspace<Number>& rhs ) const;
	ZonotopeT<Number,Converter> intersectHalfspaces( const matrix_t<Number>& mat, const vector_t<Number>& vec ) const;

	std::pair<CONTAINMENT,ZonotopeT<Number,Converter>> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT,ZonotopeT<Number,Converter>> satisfiesHalfspaces( const matrix_t<Number>& mat, const vector_t<Number>& vec ) const;

	#ifdef HYPRO_USE_PPL
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
	 * Intersects the given stateset with a second one.
	 * @param result The resulting stateset of the intersection.
	 * @param rhs The right-hand-side stateset. Is not modified.
	 * @return True if intersect is found
	 */
	ZonotopeT<Number,Converter> intersectHalfspaces( const matrix_t<Number>& mat, const vector_t<Number> vec, int method );

	/**
	 * Intersects the given stateset with a second one and returns min-max only when NDPROJECTION method is used
	 * @param result : The resulting stateset of the intersection as zonotopeT.
	 * @param minMaxOfLine : The resulting min-max matrix.
	 * @param rhs : The right-hand-side stateset. Is not modified.
	 * @return True if intersect is found.
	 */
	ZonotopeT<Number,Converter> intersect( const Halfspace<Number>& rhs, matrix_t<Number>& minMaxOfLine, int method );

	#ifdef HYPRO_USE_PPL
	/**
	 * Calculates zonotopeT intersect with a closed polyhedron as represented in PPL.
	 * @param result : The resulting stateset of the intersection as zonotopeT.
	 * @param rhs : The closed polyhedron as represented in PPL (see PPL documentation for more information).
	 * @return true if intersect is found, false otherwise (result parameter is not modified if false)
	 */
	ZonotopeT<Number,Converter> intersect( const Parma_Polyhedra_Library::C_Polyhedron& rhs ) const;
	#endif

	ZonotopeT<Number,Converter> unite( const ZonotopeT<Number,Converter>& other ) const;

	static ZonotopeT<Number,Converter> unite( const std::vector<ZonotopeT<Number,Converter>>& sets );

	/**
	 * Computes the interval hull of the member zonotopeT
	 * @param result: the resulting interval hull (also a zonotopeT)
	 * @return true for all cases
	 */
	ZonotopeT<Number,Converter> intervalHull() const;

	bool contains(const Point<Number>& point) const;

	bool contains(const ZonotopeT<Number,Converter>&) const {assert(false && "NOT IMPLEMENTED."); return false; }
};

/** @} */

template<typename Number, typename Converter>
std::ostream& operator<<(std::ostream& out, const ZonotopeT<Number,Converter>& in ) {
	out << "< c: " << convert<Number,double>(in.center()).transpose() << "," << std::endl;
	for(unsigned i = 0; i < in.generators().rows(); ++i) {
		for(unsigned j = 0; j < in.generators().cols(); ++j) {
			if(i != in.generators().rows()-1) {
				out << carl::convert<Number,double>(in.generators()(i,j)) << " ";
			} else {
				if(j != in.generators().cols()-1) {
					out << carl::convert<Number,double>(in.generators()(i,j)) << ",";
				} else {
					out << carl::convert<Number,double>(in.generators()(i,j)) << " >";
				}
			}
		}
		out << std::endl;
	}
	return out;
}

}  // namespace

#include "Zonotope.tpp"
