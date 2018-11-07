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
template<typename sfSettingIn, typename sfSettingOut>
SupportFunctionT<Number,Converter<Number>,sfSettingOut> Converter<Number>::toSupportFunction( const SupportFunctionT<Number,Converter<Number>,sfSettingIn>& _source, const CONV_MODE ){
    return _source;
}

// conversion from box to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const Box& _source, const CONV_MODE ) {
    return SupportFunction(_source.intervals());
}

template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const ConstraintSet& _source, const CONV_MODE ){
    return SupportFunctionT<Number,Converter,SupportFunctionSetting>(_source.matrix(), _source.vector());
}

template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const Ellipsoid& _source, const CONV_MODE ){
    return SupportFunctionT<Number,Converter,SupportFunctionSetting>(_source.matrix());
}

// conversion from V-Polytope to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
template<typename VPolySettings>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const VPolytopeT<Number,Converter<Number>,VPolySettings>& _source, const CONV_MODE mode) {
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
    	return SupportFunctionT<Number,Converter,SupportFunctionSetting>();
    }

    HPolytope temp = HPolytope(vertices);

    return SupportFunction( temp.constraints() );
}

// conversion from PPL polytope to support function (no differentiation between conversion modes - always EXACT)
#ifdef HYPRO_USE_PPL
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const Polytope& _source, const CONV_MODE){
    auto temp = toHPolytope(_source);
    return SupportFunction(temp.constraints());
}
#endif

template<typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const DifferenceBounds& _source, const CONV_MODE mode ) {
    return toSupportFunction(toHPolytope(_source, mode));
}
