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
static_assert( false, "This file may only be included indirectly by Converter.h" );
#endif

namespace hypro {

// conversion from support function to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
template <typename SFSetting, typename inSetting>
SupportFunctionT<Number, Converter<Number>, SFSetting> Converter<Number>::toSupportFunction( const SupportFunctionT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	// TODO: This is non-optimal, we need to proapagate/transfer the new settings instead of over-approximating the new set.
	return SupportFunctionT<Number, Converter<Number>, SFSetting>( _source.matrix(), _source.vector() );
}

// conversion from box to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
template <typename SFSetting, typename inSetting>
SupportFunctionT<Number, Converter<Number>, SFSetting> Converter<Number>::toSupportFunction( const BoxT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return SupportFunctionT<Number, Converter, SFSetting>( _source.intervals() );
}

template <typename Number>
template <typename SFSetting, typename inSetting>
SupportFunctionT<Number, Converter<Number>, SFSetting> Converter<Number>::toSupportFunction( const ConstraintSetT<Number, inSetting>& _source, const CONV_MODE ) {
	return SupportFunctionT<Number, Converter, SFSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template <typename SFSetting>
SupportFunctionT<Number, Converter<Number>, SFSetting> Converter<Number>::toSupportFunction( const Ellipsoid& _source, const CONV_MODE ) {
	return SupportFunctionT<Number, Converter, SFSetting>( _source.matrix() );
}

// conversion from V-Polytope to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
template <typename SFSetting, typename inSetting>
SupportFunctionT<Number, Converter<Number>, SFSetting> Converter<Number>::toSupportFunction( const VPolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE mode ) {
	auto temp = toHPolytope( _source, mode );
	return SupportFunctionT<Number, Converter, SFSetting>( temp.constraints() );
}

// conversion from H-polytope to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
template <typename SFSetting, typename inSetting>
SupportFunctionT<Number, Converter<Number>, SFSetting> Converter<Number>::toSupportFunction( const HPolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return SupportFunctionT<Number, Converter, SFSetting>( _source.matrix(), _source.vector() );
}

// conversion from Zonotope to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
template <typename SFSetting, typename inSetting>
SupportFunctionT<Number, Converter<Number>, SFSetting> Converter<Number>::toSupportFunction( const ZonotopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	typename std::vector<Point<Number>> vertices = _source.vertices();  //computes the vertices from the source zonotope
	if ( vertices.empty() ) {
		return SupportFunctionT<Number, Converter<Number>, SFSetting>();
	}
	HPolytope temp = HPolytope( vertices );
	return SupportFunctionT<Number, Converter, SFSetting>( temp.constraints() );
}

// conversion from PPL polytope to support function (no differentiation between conversion modes - always EXACT)
#ifdef HYPRO_USE_PPL
template <typename Number>
template <typename SFSetting, typename inSetting>
SupportFunctionT<Number, Converter<Number>, SFSetting> Converter<Number>::toSupportFunction( const PolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	auto temp = toHPolytope( _source );
	return SupportFunctionT<Number, Converter, SFSetting>( temp.constraints() );
}
#endif

template <typename Number>
template <typename SFSetting, typename inSetting>
SupportFunctionT<Number, Converter<Number>, SFSetting> Converter<Number>::toSupportFunction( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE mode ) {
	return toSupportFunction<SFSetting, HPolytopeSetting>( toHPolytope<HPolytopeSetting, inSetting>( _source, mode ) );
}

template <typename Number>
template <typename SFSetting, typename inSetting>
SupportFunctionT<Number, Converter<Number>, SFSetting> Converter<Number>::toSupportFunction( const CarlPolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return SupportFunctionT<Number, Converter, SFSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template<typename SFSetting, typename inSetting>
SupportFunctionT<Number,Converter<Number>,SFSetting> Converter<Number>::toSupportFunction( const TemplatePolyhedronT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE ){
    return SupportFunctionT<Number,Converter,SFSetting>(_source.matrix(), _source.vector());
}

//template<typename Number>
//template<typename SupportFunctionSetting, typename inSetting>
//SupportFunctionT<Number,Converter<Number>,SupportFunctionSetting> Converter<Number>::toSupportFunction( const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
//	return SupportFunctionT<Number,Converter<Number>,SupportFunctionSetting>();
//}

//Not implemented since SFNew made to replace SF
template <typename Number>
template <typename SFSetting, typename inSetting>
SupportFunctionT<Number, Converter<Number>, SFSetting> Converter<Number>::toSupportFunction( const SupportFunctionNewT<Number, Converter<Number>, inSetting>&, const CONV_MODE ) {
	return SupportFunctionT<Number, Converter, SFSetting>();
}

}  // namespace hypro
/*
template<typename Number>
template<typename SupportFunctionSetting, typename inSetting>
SupportFunctionT<Number,Converter<Number>,SupportFunctionSetting> Converter<Number>::toSupportFunction( const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
	return SupportFunctionT<Number,Converter<Number>,SupportFunctionSetting>();
}

*/