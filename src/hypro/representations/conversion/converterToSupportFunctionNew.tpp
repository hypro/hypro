#ifndef INCL_FROM_CONVERTERHEADER
static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

template<typename Number>
typename Converter<Number>::SupportFunctionNew Converter<Number>::toSupportFunctionNew( const SupportFunctionNew& _source, const CONV_MODE  ) {
	return _source;
}

template<typename Number>
typename Converter<Number>::SupportFunctionNew Converter<Number>::toSupportFunctionNew( const Box& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>
typename Converter<Number>::SupportFunctionNew Converter<Number>::toSupportFunctionNew( const ConstraintSet& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>
typename Converter<Number>::SupportFunctionNew Converter<Number>::toSupportFunctionNew( const Ellipsoid& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>
typename Converter<Number>::SupportFunctionNew Converter<Number>::toSupportFunctionNew( const HPolytope& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>
typename Converter<Number>::SupportFunctionNew Converter<Number>::toSupportFunctionNew( const OrthogonalPolyhedron& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>
typename Converter<Number>::SupportFunctionNew Converter<Number>::toSupportFunctionNew( const VPolytope& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>	
typename Converter<Number>::SupportFunctionNew Converter<Number>::toSupportFunctionNew( const DifferenceBounds& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

#ifdef HYPRO_USE_PPL
template<typename Number>
typename Converter<Number>::SupportFunctionNew Converter<Number>::toSupportFunctionNew( const Polytope& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}
#endif

template<typename Number>
typename Converter<Number>::SupportFunctionNew Converter<Number>::toSupportFunctionNew( const SupportFunction& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>
typename Converter<Number>::SupportFunctionNew Converter<Number>::toSupportFunctionNew( const Zonotope& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

