/**
 * The class which represents a hyperplane.
 *
 * @file Hyperplane.h
 * @author jongan
 *
 * @since   2014-08-29 3:53 PM
 * @version
 */

#ifndef HYPERPLANE_H
#define	HYPERPLANE_H
#include <Eigen/Dense>
#include "../../config.h"

template<typename Number>
class Hyperplane
{
    private:
        unsigned int mDimension;
        hypro::vector_t<Number> d_;
        hypro::scalar_t<Number> e_;
    
    public:
        /***************************************************************************
         * Constructors
       	 **************************************************************************/

        /*
         * Creates a hyperplane in dimension 0
         */
        Hyperplane();

        /*
         * Creates a hyperplane with a specified dimension
         * @param dimension Represents the dimension the hyperplane's gonna be
         */
        Hyperplane(unsigned int dimension);

        /*
         * Creates a hyperplane
         * @param e_scalar
         */
        Hyperplane(const hypro::vector_t<Number>& d_vector, hypro::scalar_t<Number> e_scalar);

        /*
         * Creates a hyperplane
         * @param other
         */
        Hyperplane(const Hyperplane<Number>& other);
        
        virtual ~Hyperplane();
        
        /***************************************************************************
       	 * Getters & setters
         **************************************************************************/

        /*
         * @return the dimension of this hyperplane
         */
        unsigned int dimension() const;

        /*
         * @return
         */
        hypro::vector_t<Number> vector() const;

        /*
         * @return
         */
        hypro::scalar_t<Number> scalar() const;

        /*
         * @param d_vector
         */
        void setVector(const hypro::vector_t<Number>& d_vector);

        /*
         * @param e_scalar
         */
        void setScalar(const hypro::scalar_t<Number> e_scalar);
        
        /*
         * Changes the dimension of this hyperplane to a new one
         * @param newDimension The new dimension the hyperplane's gonna get
         */
        bool changeDimension(unsigned int newDimension);
        

};

#include "Hyperplane.tpp"
#endif	/* HYPERPLANE_H */

