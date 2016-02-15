/**
 * Specialization for a converter to a zonotope.
 * @file converterToZonotope.tpp
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2015-12-17
 */

#include "Converter.h"

//conversion from Zonotope to Zonotope
template <typename Number>
typename Converter<Number>::Zonotope Converter<Number>::toZonotope( const Zonotope& _source, const CONV_MODE mode ){
    return _source;
}
//TODO
template <typename Number>
typename Converter<Number>::Zonotope Converter<Number>::toZonotope( const HPolytope& _source, const CONV_MODE mode ){
    return std::move(Zonotope());
}

//TODO
//conversion from Box to Zonotope
template <typename Number>
typename Converter<Number>::Zonotope Converter<Number>::toZonotope( const Box& _source, const CONV_MODE mode ){
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

    return std::move(Zonotope(center, generators));
}

//TODO
template <typename Number>
typename Converter<Number>::Zonotope Converter<Number>::toZonotope( const VPolytope& _source, const CONV_MODE mode ){
    return std::move(Zonotope());
}

//TODO
template <typename Number>
typename Converter<Number>::Zonotope Converter<Number>::toZonotope( const SupportFunction& _source, const CONV_MODE mode){
    return std::move(Zonotope());
}
