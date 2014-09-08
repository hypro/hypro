/* 
 * File:   Zonotope.h
 * Author: jongan
 *
 * Created on June 19, 2014, 10:25 PM
 */

#ifndef ZONOTOPE_H
#define	ZONOTOPE_H

#include <vector>
#include "Hyperplane.h"
#include <eigen3/Eigen/Dense>

template <typename Number>
class Zonotope : hypro::GeometricObject<Number>
{
    private:
        unsigned int mDimension;
        Eigen::Matrix<Number, Eigen::Dynamic, 1> mCenter;
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> mGenerators;
        
        void removeGenerator(unsigned int colToRemove);
        
    public:
        Zonotope(); 
        Zonotope(unsigned int dimension);
        Zonotope(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& center, 
				const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& generators);
        
        virtual ~Zonotope();
  
        unsigned int dimension() const;
        bool minkowskiSum(Zonotope<Number>& result, const Zonotope<Number>& rhs);
        bool linearTransformation(Zonotope<Number>& result, const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& A);
        bool intersect(Zonotope<Number>& result, const Hyperplane<Number>& rhs);
        
        Eigen::Matrix<Number, Eigen::Dynamic, 1> getCenter() const;
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> getGenerators() const;

        void setCenter(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& center);
        void setGenerators(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& new_generators);
        bool addGenerators(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& generators);
        unsigned int numGenerators() const ;

      
        void removeEmptyGenerators();
        bool changeDimension(unsigned int new_dim);
        
};
#include "Zonotope.tpp"

#endif	/* ZONOTOPE_H */

