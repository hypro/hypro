/**
 * Specialization for a converter to a zonotope.
 * @file converterToZonotope.tpp
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2015-12-17
 */

#include "converterToZonotope.h"

namespace hypro {

    //conversion from Zonotope to Zonotope
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, hypro::Zonotope<Number>& _target, const CONV_MODE mode ){
        _target = _source;
        return true;        
    }
    //TODO
    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, hypro::Zonotope<Number>& _target, const CONV_MODE mode ){
        return true;
    }
    
    //TODO
    //conversion from Box to Zonotope
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, hypro::Zonotope<Number>& _target, const CONV_MODE mode ){
        unsigned dim = _source.dimension();                                             //gets dimension from source object
        std::vector<carl::Interval<Number>> intervals = _source.boundaries();           //gets intervals from source object
        matrix_t<Number> generators = matrix_t<Number>::Zero(dim, dim);                 //defines an empty generator matrix for dim generators
        vector_t<Number> center = vector_t<Number>(dim);                                //defines an empty center vector
        
        for (unsigned i=0; i<dim; ++i){                                                 //for every dimension
            center[i] = (intervals[i].lower() + intervals[i].upper())/2;                //compute center component of the Box
        }
        
        for (unsigned i=0; i<dim; ++i){                                                 //for every dimension
            generators(i, i) = (intervals[i].upper() - intervals[i].lower())/ 2;        //compute the corresponding generator for that dimension by computing the length of the interval and dividing it by 2
        }
        
        _target = Zonotope<Number>(center, generators);                                 //creates a zonotope with the computed center and generators
        
        return true;
    }
    
    //TODO
    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, hypro::Zonotope<Number>& _target, const CONV_MODE mode ){
        return true;
    } 
    
    //TODO
    template <typename Number>
    static bool convert( const hypro::SupportFunction<Number>& _source, hypro::Zonotope<Number>& _target, const CONV_MODE mode){
        return true;
    }

}  // namespace

