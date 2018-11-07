
#include "Converter.h"
#ifndef INCL_FROM_CONVERTERHEADER
	static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

template<typename Number>
template<typename ConstraintSetSettings>
ConstraintSetT<Number,Converter<Number>,ConstraintSetSettings> Converter<Number>::toConstraintSet( const Box& _source, const CONV_MODE  ) {
	return ConstraintSetT<Number,Converter,ConstraintSetSettings>(_source.matrix(), _source.vector());
}

template<typename Number>
template<typename ConstraintSetSettings>
ConstraintSetT<Number,Converter<Number>,ConstraintSetSettings> Converter<Number>::toConstraintSet( const ConstraintSet& _source, const CONV_MODE  ) {
	return _source;
}

template<typename Number>
template<typename ConstraintSetSettings>
ConstraintSetT<Number,Converter<Number>,ConstraintSetSettings> Converter<Number>::toConstraintSet( const Ellipsoid& _source, const CONV_MODE  ) {
	return ConstraintSetT<Number,Converter,ConstraintSetSettings>(_source.matrix(), _source.vector());
}

template<typename Number>
template<typename ConstraintSetSettings,typename sfSetting>
ConstraintSetT<Number,Converter<Number>,ConstraintSetSettings> Converter<Number>::toConstraintSet( const SupportFunctionT<Number,Converter,sfSetting>& _source, const CONV_MODE  ) {
	return ConstraintSetT<Number,Converter,ConstraintSetSettings>(_source.matrix(), _source.vector());
}

template<typename Number>
template<typename ConstraintSetSettings,typename VPolySettings>
ConstraintSetT<Number,Converter<Number>,ConstraintSetSettings> Converter<Number>::toConstraintSet( const VPolytopeT<Number,Converter<Number>,VPolySettings>& _source, const CONV_MODE  ) {
	auto tmp = toHPolytope(_source);
	return ConstraintSetT<Number,Converter,ConstraintSetSettings>(tmp.matrix(), tmp.vector());
}

template<typename Number>
template<typename ConstraintSetSettings>
ConstraintSetT<Number,Converter<Number>,ConstraintSetSettings> Converter<Number>::toConstraintSet( const HPolytope& _source, const CONV_MODE  ) {
	return ConstraintSetT<Number,Converter,ConstraintSetSettings>(_source.matrix(), _source.vector());
}

#ifdef HYPRO_USE_PPL
template<typename Number>
template<typename ConstraintSetSettings>
ConstraintSetT<Number,Converter<Number>,ConstraintSetSettings> Converter<Number>::toConstraintSet( const Polytope& _source, const CONV_MODE  ) {
	auto tmp = toHPolytope(_source);
	return ConstraintSetT<Number,Converter,ConstraintSetSettings>(tmp.matrix(), tmp.vector());
}
#endif

template<typename Number>
template<typename ConstraintSetSettings>
ConstraintSetT<Number,Converter<Number>,ConstraintSetSettings> Converter<Number>::toConstraintSet( const Zonotope& , const CONV_MODE ) {
	assert(false && "NotImplemented.");
    return ConstraintSetT<Number,Converter,ConstraintSetSettings>();
}
template<typename Number>
template<typename ConstraintSetSettings>
ConstraintSetT<Number,Converter<Number>,ConstraintSetSettings> Converter<Number>::toConstraintSet( const DifferenceBounds& _source, const CONV_MODE mode ) {
	return toConstraintSet<ConstraintSetSettings>(toHPolytope(_source, mode));
}
