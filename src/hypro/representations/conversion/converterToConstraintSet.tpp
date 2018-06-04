
#include "Converter.h"
#ifndef INCL_FROM_CONVERTERHEADER
	static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

template<typename Number>
typename Converter<Number>::ConstraintSet Converter<Number>::toConstraintSet( const Box& _source, const CONV_MODE  ) {
	return ConstraintSetT<Number,Converter>(_source.matrix(), _source.vector());
}

template<typename Number>
typename Converter<Number>::ConstraintSet Converter<Number>::toConstraintSet( const ConstraintSet& _source, const CONV_MODE  ) {
	return _source;
}

template<typename Number>
typename Converter<Number>::ConstraintSet Converter<Number>::toConstraintSet( const Ellipsoid& _source, const CONV_MODE  ) {
	return ConstraintSetT<Number,Converter>(_source.matrix(), _source.vector());
}

template<typename Number>
typename Converter<Number>::ConstraintSet Converter<Number>::toConstraintSet( const SupportFunction& _source, const CONV_MODE  ) {
	return ConstraintSetT<Number,Converter>(_source.matrix(), _source.vector());
}

template<typename Number>
typename Converter<Number>::ConstraintSet Converter<Number>::toConstraintSet( const VPolytope& _source, const CONV_MODE  ) {
	auto tmp = toHPolytope(_source);
	return ConstraintSetT<Number,Converter>(tmp.matrix(), tmp.vector());
}

template<typename Number>
typename Converter<Number>::ConstraintSet Converter<Number>::toConstraintSet( const HPolytope& _source, const CONV_MODE  ) {
	return ConstraintSetT<Number,Converter>(_source.matrix(), _source.vector());
}

#ifdef HYPRO_USE_PPL
template<typename Number>
typename Converter<Number>::ConstraintSet Converter<Number>::toConstraintSet( const Polytope& _source, const CONV_MODE  ) {
	return ConstraintSetT<Number,Converter>(_source.matrix(), _source.vector());
}
#endif

template<typename Number>
typename Converter<Number>::ConstraintSet Converter<Number>::toConstraintSet( const Zonotope& , const CONV_MODE ) {
	assert(false && "NotImplemented.");
    return ConstraintSetT<Number,Converter>();
}
