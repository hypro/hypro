/**
 * Implementation of principal component analysis for a set of sample points. 
 * @file  pca.tpp
 * @author Simon Froitzheim
 *
 * @since       2015-02-15
 * @version     2015-02-15
 */

#include "pca.h"

namespace hypro {

template<typename Number>
HyperplaneVector computeOrientedBox(const std::vector<vector_t<Number>>& samples){
    //gets dimension of sample points
    unsigned dim = samples[0].rows();
    //gets number of sample points
    unsigned sSize = samples.size()
    
    vector_t<Number> mean = vector_t<Number>::Zero(dim);
    
    //computes the sum of all sample points
    for (unsigned i=0; i < sSize; ++i){
         mean += samples[i];
    }  
    //computes the arithmetic mean of the sample points
    mean = mean*(1/sSize);
    
    std::vector<vector_t<Number>> tSamples = samples;
    
    //computes the set of translated sample points
    for (unsigned i=0; i < sSize; ++i){
        tSamples[i] -= mean;
    } 
    
    matrix_t<Number> sMatrix = matrix_t<Number>::Zero(dim, sSize);
    
    //builds the sampling matrix
    for (unsigned i=0; i < sSize; ++i){
        sMatrix.col(i) = tSamples[i];
    }
    
    //computes the sample covariance matrix (represents the distribution of the samples)
    matrix_t<Number> covMatrix = (1/(sSize-1))*sMatrix*sMatrix.transpose();
    
    //computes the singular value decomposition of the sample covariance matrix (only U component from U*Sigma*V^T needed)
    Eigen::JacobiSVD<matrix_t<Number>> svd = Eigen::JacobiSVD<matrix_t<Number>>(dim, dim, ComputeThinU);
    matrix_t<Number> u = svd.matrixU();
    
    //computes halfspaces with the help of U in two steps
    
    //first step: compute the maximum/minimum product of transposed translated samples (tSamples) with the corresponding column of U
    vector_t<Number> max = vector_t<Number>::Constant(dim, 1, tSamples[0].dot(u.col(0)));
    vector_t<Number> min = vector_t<Number>::Constant(dim, 1, tSamples[0].dot(u.col(0)));
    for (unsigned i=0; i < dim; ++i){
        for (unsigned j=0; j < sSize; ++j){
            unsigned tmp = tSamples[j].dot(u.col(i));
            if ( tmp > max[i]){
                max(i) = tmp;
            }
            if ( tmp < min[i]){
                min(i) = tmp;
            }
        }
    }
    
    //second step: create hyperplanes with the given normals and maximum/minimum products
    HyperplaneVector res = HyperplaneVector(2*dim);
    for (unsigned i=0; i < dim; ++i){
        res[2*i] = Hyperplane<Number>(u.col(i), max(i) + u.col(i).dot(mean));
        res[2*i+1] = Hyperplane<Number>(-u.col(i), -min(i) - u.col(i).dot(mean));    
    }
    
    
    //returns halfspaces
    return res;
   
    
}

} //namespace