
#include "Converter.h"
#ifndef INCL_FROM_CONVERTERHEADER
static_assert( false, "This file may only be included indirectly by Converter.h" );
#endif

namespace hypro {

template <typename Number>
template <typename CSSetting, typename inSetting>
ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const BoxT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return ConstraintSetT<Number, CSSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template <typename CSSetting, typename inSetting>
ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const CarlPolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return ConstraintSetT<Number, CSSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template <typename CSSetting, typename inSetting>
ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const ConstraintSetT<Number, inSetting>& _source, const CONV_MODE ) {
	return _source;
}

template <typename Number>
template <typename CSSetting>
ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const Ellipsoid& _source, const CONV_MODE ) {
	return ConstraintSetT<Number, CSSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template <typename CSSetting, typename inSetting>
ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const SupportFunctionT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return ConstraintSetT<Number, CSSetting>( _source.matrix(), _source.vector() );
}
template <typename Number>
template <typename CSSetting, typename inSetting>
ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const VPolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	auto tmp = toHPolytope( _source );
	return ConstraintSetT<Number, CSSetting>( tmp.matrix(), tmp.vector() );
}

template <typename Number>
template <typename CSSetting, typename inSetting>
ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const HPolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return ConstraintSetT<Number, CSSetting>( _source.matrix(), _source.vector() );
}

#ifdef HYPRO_USE_PPL
template <typename Number>
template <typename CSSetting, typename inSetting>
ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const PolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	auto tmp = toHPolytope( _source );
	return ConstraintSetT<Number, CSSetting>( tmp.matrix(), tmp.vector() );
}
#endif

template <typename Number>
template <typename CSSetting, typename inSetting>
ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const ZonotopeT<Number, Converter<Number>, inSetting>&, const CONV_MODE ) {
	assert( false && "NotImplemented." );
	return ConstraintSetT<Number, CSSetting>();
}

template <typename Number>
template <typename CSSetting, typename inSetting>
ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE mode ) {
	return toConstraintSet( toHPolytope( _source, mode ) );
}

template <typename Number>
template <typename ConstraintSetSetting, typename inSetting>
ConstraintSetT<Number, ConstraintSetSetting> Converter<Number>::toConstraintSet( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE ) {
	return ConstraintSetT<Number, ConstraintSetSetting>( source.matrix(), source.vector() );
}

// template<typename Number>
// template<typename ConstraintSetSetting, typename inSetting>
// ConstraintSetT<Number,ConstraintSetSetting> Converter<Number>::toConstraintSet( const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
//	return ConstraintSetT<Number,ConstraintSetSetting>();
// }

template <typename Number>
template <typename CSSetting, typename inSetting>
ConstraintSetT<Number, CSSetting> Converter<Number>::toConstraintSet( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return ConstraintSetT<Number, CSSetting>( _source.matrix(), _source.vector() );
}

  // namespace hypro

template<typename Number>
template<typename ConstraintSetSetting, typename inSetting>
ConstraintSetT<Number,ConstraintSetSetting> Converter<Number>::toConstraintSet( const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
	return ConstraintSetT<Number,ConstraintSetSetting>();
}
}
