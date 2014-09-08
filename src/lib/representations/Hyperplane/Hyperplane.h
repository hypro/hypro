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
        
        virtual ~Hyperplane();
        
        unsigned int dimension() const;

        Eigen::Matrix<Number, Eigen::Dynamic, 1> getDVector() const;
        Number getEValue() const;

        void setDVector(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& d_vector);
        void setEValue(const Number e_scalar);
        
        
        

};

#include "Hyperplane.tpp"
#endif	/* HYPERPLANE_H */

