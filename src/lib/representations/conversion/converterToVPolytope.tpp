/**
 * Specialization for a converter to a V-polytope.
 * @file converterToVPolytope.tpp
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2015-12-17
 */

#include "Converter.h"

template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const VPolytope& _source, const CONV_MODE mode ){
    return _source;
}
//TODO
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const HPolytope& _source, const CONV_MODE mode ){
    return std::move(VPolytope());
}

//TODO
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const Box& _source, const CONV_MODE mode ){
    return std::move(VPolytope(_source.vertices()));
}

//TODO
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const Zonotope& _source, const CONV_MODE mode ){
    return std::move(VPolytope());
}

//TODO
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const SupportFunction& _source, const CONV_MODE mode){
    return std::move(VPolytope());
}
