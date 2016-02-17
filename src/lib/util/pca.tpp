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
    for (unsigned i=0; i< sSize; ++i){
        tSamples[i] -= mean;
    } 
    
    matrix_t<Number> sMatrix = matrix_t<Number>::Zero(dim, sSize);
    
    //builds the sampling matrix
    for (unsigned i=0; i < sSize; ++i){
        sMatrix.col(i) = tSamples[i];
    }
    
    //computes the sample covariance matrix (represents the distribution of the samples)
    matrix_t<Number> covMatrix = (1/(sSize-1))*sMatrix*sMatrix.transpose();
    
    //TODO computes the singular value decomposition of the sample covariance matrix
    
    //TODO reads out halfspaces
    
    //TODO returns halfspaces
   
    
}

} //namespace