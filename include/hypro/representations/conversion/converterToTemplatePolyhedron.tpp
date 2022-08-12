#ifndef INCL_FROM_CONVERTERHEADER
static_assert( false, "This file may only be included indirectly by Converter.h" );
#endif

namespace hypro {

template <typename Number>
template <typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting>( _source );
}

template <typename Number>
template <typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const BoxT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template <typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const CarlPolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template <typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const ConstraintSetT<Number, inSetting>& _source, const CONV_MODE ) {
	return TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template <typename TemplatePolyhedronSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const Ellipsoid& _source, const CONV_MODE ) {
	// TODO: do i even need to maintenance this?
	return Converter<Number>::TemplatePolyhedron();
}

template <typename Number>
template <typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const HPolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template <typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const VPolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	auto tmp = typename Converter::HPolytope( _source.vertices() );
	return TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting>( tmp.matrix(), tmp.vector() );
}

template <typename Number>
template <typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& /*_source*/, const CONV_MODE ) {
	// TODO: Is that even possible?
	return Converter<Number>::TemplatePolyhedron();
}

#ifdef HYPRO_USE_PPL
template <typename Number>
template <typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const PolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	auto tmp = typename Converter::HPolytope( _source );
	return TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting>( tmp.matrix(), tmp.vector() );
}
#endif

template <typename Number>
template <typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const SupportFunctionT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template <typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template <typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const ZonotopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	auto tmp = typename Converter::HPolytope( _source.vertices() );
	return TemplatePolyhedronT<Number, Converter<Number>, TemplatePolyhedronSetting>( tmp.matrix(), tmp.vector() );
}

// template<typename Number>
// template<typename TemplatePolyhedronSetting, typename inSetting>
// TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
//	//TODO
//	return TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting>();
// }

  // namespace hypro
template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
	return TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting>();
}

}
