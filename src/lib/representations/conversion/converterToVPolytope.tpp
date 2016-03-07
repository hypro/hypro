/**
 * Specialization for a converter to a V-polytope.
 * @file converterToVPolytope.tpp
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2015-12-17
 */

#include "Converter.h"

//conversion from V-Polytope to V-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const VPolytope& _source, const CONV_MODE mode ){
    return _source;
}

//TODO overapproximation
//conversion from H-Polytope to V-Polytope (EXACT or OVER)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const HPolytope& _source, const CONV_MODE mode ){
    return VPolytope(_source.matrix(), _source.vector());
}

//conversion from Box to V-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const Box& _source, const CONV_MODE mode ){
    return VPolytope(_source.vertices());
}

//conversion from Zonotope to V-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const Zonotope& _source, const CONV_MODE mode ){
    return VPolytope(_source.vertices());
}

//TODO conversion from Support Function to V-Polytope (OVER or UNDER)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const SupportFunction& _source, const CONV_MODE mode){
    return VPolytope();
}
