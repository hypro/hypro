/* *
 * Zonotope class representation for use in reachability analysis
 * 
 * File:   Zonotope.h
 * @author Jonathan Gan, Ibtissem Ben Makhlouf {gan, makhlouf} @ embedded.rwth-aachen.de
 * @version 1.0 on June 19, 2014, 10:25 PM
 */

#pragma once

#include <vector>
#include <eigen3/Eigen/Dense>
#include <ppl.hh>
#include <cmath>
#include <algorithm>
#include <valarray>

#include "../Hyperplane/Hyperplane.h"
#include "ZUtility.h"


//using namespace Parma_Polyhedra_Library;


namespace hypro {

template <typename Number>
class Zonotope 
{
    private:
        unsigned int mDimension;
        hypro::vector_t<Number> mCenter;
        hypro::matrix_t<Number> mGenerators;
        
        void removeGenerator(unsigned int colToRemove);
        
        
    public:
        
        // Constructors and Destructors
        
        Zonotope(); 
        /**
         * Constructor with dimension
         * @param dimension Dimensionality of Zonotope
         */
        Zonotope(unsigned int dimension);
        
        /**
         * Constructs a Zonotope with center and generators.
         * @param center A (nx1) vector
         * @param generators A (nxm) vector
         */
        Zonotope(const hypro::vector_t<Number>& center, 
				const hypro::matrix_t<Number>& generators);
        
        /**
         * Copy Constructor - constructs a zonotope from an existing one.
         * @param other Another Zonotope, from which a new zonotope is constructed
         */
        Zonotope(const Zonotope<Number>& other);
        
        
        /**
         * Copy Constructor - constructs a 2D-zonotope of from an existing ND one.
         * @param other : Another Zonotope, from which a new zonotope is constructed
         * @param d1 : 1st dimension (0 <= d1 < other.dimension)
         * @param d2 : 2nd dimension (0 <= d2 < other.dimension) d1!=d2
         */
        Zonotope(const Zonotope<Number>& other, unsigned d1, unsigned d2);
        
        virtual ~Zonotope();
        
        
        /*****************************************************************************
        *                                                                           *
        *      Public Functions - Getters and Setters and some misc functions       *                             
        *                                                                           *
        *****************************************************************************/
  
        /**
         * Dimensionality of Zonotope
         * @return the dimension
         */
        unsigned dimension() const;

        /**
        * Returns, whether the zonotope is empty.
        * @return 
        */
        bool isEmpty() const;
        
        /**
         * Replaces the current center with the parameter center
         * @param center a nx1 matrix
         */
        void setCenter(const hypro::vector_t<Number>& center);
        
        /**
         * Replaces the current matrix of generators with the parameter generators
         * @param new_generators a nxm matrix
         */
        void setGenerators(const hypro::matrix_t<Number>& generators_);
                
        /**
         * Add generators to Zonotope. Simply performs setGenerators if generators was previously not initialized.
         * @param generators
         * @return true if able to add generators
         */
        bool addGenerators(const hypro::matrix_t<Number>& generators);
        
        // Getters and Setters for center and generators
        hypro::vector_t<Number> center() const;
        hypro::matrix_t<Number> generators() const;
        
        /**
         * Number of generators
         * @return number of generators
         */
        unsigned int numGenerators() const ;

        /**
         * Removes empty (null) columns in generator matrix
         */
        void removeEmptyGenerators();
        
        /**
         * Changes the dimension of a Zonotope. if new_dim > old dim, new rows are initialized with null
         * @param new_dim The new dimension of the Zonotope
         * @return True, if change in dimension was successful
         */
        bool changeDimension(unsigned int new_dim);
        
        /**
         * Clears the generators and center of the Zonotope and sets dimensionality to zero
         */
        void clear();
        
        
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
        Zonotope<Number> minkowskiSum(const Zonotope<Number>& rhs) const;
        
        /** 
         * Applies a linear transformation on the given stateset.
         * @param result The resulting stateset.
         * @return True if the operation has been successfully applied.
         */
        Zonotope<Number> linearTransformation(const hypro::matrix_t<Number>& A) const;
        
        /**
         * Compute boundaries of zonotope
         * @return array of points represented as vectors
         */
        std::vector< hypro::vector_t<Number> > computeZonotopeBoundary();
        
        /**
         * Calculates zonotope intersect with halfspace (represented as d*x <= e, where d is a column vector of dimension n and e a scalar)
         * @param result : The resulting intersect 
         * @param d_vec : Vector representing the halfspace
         * @param e_scalar : Scalar representing the halfspace
         * @return true if intersect is found, false otherwise (result parameter is not modified if false)
         */
        Zonotope<Number> intersectWithHalfspace(const hypro::vector_t<Number>& d_vec, hypro::scalar_t<Number> e_scalar) const;
        
        /**
         * Calculates zonotope intersect with halfspace represented as PPL constraint
         * @param result : The resulting stateset of the intersection
         * @param halfspace : Halfspace as represented in PPL (see PPL documentation for more information)
         * @return true if intersect is found, false otherwise (result parameter is not modified if false)
         */
        Zonotope<Number> intersect(const Parma_Polyhedra_Library::Constraint& halfspace) const;
        
        /**
         * Intersects the given stateset with a second one.
         * @param result The resulting stateset of the intersection.
         * @param rhs The right-hand-side stateset. Is not modified.
         * @return True if intersect is found
         */
        Zonotope<Number> intersect(const Hyperplane<Number>& rhs, int method);
        
        /**
         * Intersects the given stateset with a second one and returns min-max only when NDPROJECTION method is used
         * @param result : The resulting stateset of the intersection as zonotope.
         * @param minMaxOfLine : The resulting min-max matrix.
         * @param rhs : The right-hand-side stateset. Is not modified.
         * @return True if intersect is found.
         */
        Zonotope<Number> intersect(const Hyperplane<Number>& rhs, hypro::matrix_t<Number>& minMaxOfLine, int method);
        
        
        /**
         * Calculates zonotope intersect with a closed polyhedron as represented in PPL.
         * @param result : The resulting stateset of the intersection as zonotope.
         * @param rhs : The closed polyhedron as represented in PPL (see PPL documentation for more information).
         * @return true if intersect is found, false otherwise (result parameter is not modified if false)
         */
        Zonotope<Number> intersect(const Parma_Polyhedra_Library::C_Polyhedron& rhs) const;
        
        /**
         * Computes the convex hull of the member zonotope and another given zonotope
         * @param result: resulting convex hull (also itself a zonotope)
         * @param other: the other zonotope
         * @return true for all cases. 
         */
        Zonotope<Number> unite(const Zonotope<Number>& other) const;
        
        /**
         * Computes the interval hull of the member zonotope
         * @param result: the resulting interval hull (also a zonotope)
         * @return true for all cases
         */
        Zonotope<Number> intervalHull() const;
};

} // namespace

#include "Zonotope.tpp"