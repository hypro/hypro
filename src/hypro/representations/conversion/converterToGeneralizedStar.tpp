#ifndef INCL_FROM_CONVERTERHEADER
static_assert( false, "This file may only be included indirectly by Converter.h" );
#endif

namespace hypro {

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const GeneralizedStar& _source, const CONV_MODE ) {
	return _source;
}

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const Box& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const CarlPolytope& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const ConstraintSet& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const Ellipsoid& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const HPolytope& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const OrthogonalPolyhedron& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const VPolytope& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const DifferenceBounds& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}

#ifdef HYPRO_USE_PPL
template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const Polytope& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}
#endif

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const SupportFunction& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const Zonotope& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}

template <typename Number>
typename Converter<Number>::GeneralizedStar Converter<Number>::toGeneralizedStar( const SupportFunctionNew& _source, const CONV_MODE ) {
	return Converter<Number>::GeneralizedStar();
}

}  // namespace hypro
