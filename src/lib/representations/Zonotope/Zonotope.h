/* 
 * File:   Zonotope.h
 * Author: jongan
 *
 * Created on June 19, 2014, 10:25 PM
 */

#ifndef ZONOTOPE_H
#define	ZONOTOPE_H

#include <vector>
#include "../Hyperplane/Hyperplane.h"
#include <eigen3/Eigen/Dense>
#include <ppl.hh>
#include <cmath>
#include <algorithm>
#include <valarray>


//using namespace Parma_Polyhedra_Library;




template <typename Number>
class Zonotope 
{
    private:
        unsigned int mDimension;
        Eigen::Matrix<Number, Eigen::Dynamic, 1> mCenter;
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> mGenerators;
        
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
        Zonotope(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& center, 
				const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& generators);
        
        /**
         * Copy Constructor - constructs a zonotope from an existing one.
         * @param other Another Zonotope, from which a new zonotope is constructed
         */
        Zonotope(const Zonotope<Number>& other);
        
        virtual ~Zonotope();
        
        
  
        /**
         * Dimensionality of Zonotope
         * @return the dimension
         */
        unsigned int dimension() const;
        
        /**
         * Applies the Minkowskisum of the given stateset and a second stateset.
         * @param result The resulting stateset.
         * @param rhs The other right-hand-side stateset. Is not modified.
         * @return True if the operation has been successfully applied.
         */
        bool minkowskiSum(Zonotope<Number>& result, const Zonotope<Number>& rhs);
        
        /** 
         * Applies a linear transformation on the given stateset.
         * @param result The resulting stateset.
         * @return True if the operation has been successfully applied.
         */
        bool linearTransformation(Zonotope<Number>& result, const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& A);
        
        
        std::vector< Eigen::Matrix<Number, Eigen::Dynamic,1> > computeZonotopeBoundary();
        
        /**
         * Intersects the given stateset with a second one.
         * @param result The resulting stateset of the intersection.
         * @param rhs The right-hand-side stateset. Is not modified.
         * @return True if intersect is found
         */
        bool intersect(Zonotope<Number>& result, 
                        const Hyperplane<Number>& rhs,
                        int method);
        
        bool intersect(Zonotope<Number>& result, 
                        const Hyperplane<Number>& rhs, 
                        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& minMaxOfLine,
                        int method);
        
        // Intersection between Zonotope and Polyhedron 
        bool intersect(Zonotope<Number>& result, const Parma_Polyhedra_Library::C_Polyhedron& rhs);
        
        
        // Getters and Setters for center and generators
        
        Eigen::Matrix<Number, Eigen::Dynamic, 1> center() const;
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> generators() const;
        
        /**
         * Replaces the current center with the parameter center
         * @param center a nx1 matrix
         */
        void setCenter(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& center);
        
        /**
         * Replaces the current matrix of generators with the parameter generators
         * @param new_generators a nxm matrix
         */
        void setGenerators(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& new_generators);
        
        /**
         * Add generators to Zonotope. Simply performs setGenerators if generators was previously not initialized.
         * @param generators
         * @return true if able to add generators
         */
        bool addGenerators(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& generators);
        
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
        
};
#include "Zonotope.tpp"

#endif	/* ZONOTOPE_H */

