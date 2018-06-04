/**
 * Specialization for a converter to a support function.
 * @file converterToSupportFunction.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @since	2015-05-13
 * @version	2016-03-17
 */

#include "Converter.h"
#ifndef INCL_FROM_CONVERTERHEADER
	static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

// conversion from support function to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const SupportFunction& _source, const CONV_MODE ){
    return _source;
}

// conversion from box to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const Box& _source, const CONV_MODE ) {
    return SupportFunction(_source.boundaries());
}

template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const ConstraintSet& _source, const CONV_MODE ){
    return SupportFunctionT<Number,Converter>(_source.matrix(), _source.vector());
}

template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const Ellipsoid& _source, const CONV_MODE ){
    return SupportFunctionT<Number,Converter>(_source.matrix());
}

// conversion from V-Polytope to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const VPolytope& _source, const CONV_MODE mode) {
    auto temp = toHPolytope(_source, mode);
    return SupportFunction( temp.constraints() );
}



// conversion from H-polytope to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const HPolytope& _source, const CONV_MODE ) {
    return SupportFunction( _source.constraints() );
}

// conversion from Zonotope to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const Zonotope& _source, const CONV_MODE ) {
    typename std::vector<Point<Number>> vertices = _source.vertices();           //computes the vertices from the source zonotope
    if(vertices.empty()){
    	return SupportFunctionT<Number,Converter>();
    }

    HPolytope temp = HPolytope(vertices);

    return SupportFunction( temp.constraints() );
}
