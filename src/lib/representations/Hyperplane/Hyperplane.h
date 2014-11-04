/* 
 * File:   Hyperplane.h
 * Author: jongan
 *
 * Created on August 29, 2014, 3:53 PM
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
        Hyperplane();
        Hyperplane(unsigned int dimension);
        Hyperplane(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& d_vector, Number e_scalar);
        Hyperplane(const Hyperplane<Number>& other);
        
        virtual ~Hyperplane();
        
        unsigned int dimension() const;

        Eigen::Matrix<Number, Eigen::Dynamic, 1> vector() const;
        Number scalar() const;

        void setVector(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& d_vector);
        void setScalar(const Number e_scalar);
        
        bool changeDimension(unsigned int newDimension);
        

};

#include "Hyperplane.tpp"
#endif	/* HYPERPLANE_H */

