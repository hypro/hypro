/**
 * Implementation of principal component analysis for a set of sample points. 
 * @file  pca.h
 * @author Simon Froitzheim
 *
 * @since       2015-02-15
 * @version     2015-02-15
 */

#pragma once

#include "../representations/conversion/Converter.h"

namespace hypro {

template <typename Number>
class pca{
    public:
        
        static HyperplaneVector computeOrientedBox(const std::vector<vector_t<Number>>& samples);
     
};
    
    
    
    
#include "pca.tpp"    
    
} //namespace

