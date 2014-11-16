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

template<typename Number>
class Hyperplane
{
    private:
        unsigned int mDimension;
        Eigen::Matrix<Number, Eigen::Dynamic, 1> d_;
        Number e_;
    
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
        Hyperplane(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& d_vector, Number e_scalar);

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
        Eigen::Matrix<Number, Eigen::Dynamic, 1> vector() const;

        /*
         * @return
         */
        Number scalar() const;

        /*
         * @param d_vector
         */
        void setVector(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& d_vector);

        /*
         * @param e_scalar
         */
        void setScalar(const Number e_scalar);
        
        /*
         * Changes the dimension of this hyperplane to a new one
         * @param newDimension The new dimension the hyperplane's gonna get
         */
        bool changeDimension(unsigned int newDimension);
        

};

#include "Hyperplane.tpp"
#endif	/* HYPERPLANE_H */

