#ifndef INCL_FROM_CONVERTERHEADER
static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const TemplatePolyhedronT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return _source;
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const BoxT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const CarlPolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const ConstraintSetT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const EllipsoidT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const HPolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const OrthogonalPolyhedronT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const VPolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const DifferenceBoundsT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

#ifdef HYPRO_USE_PPL
template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const PolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}
#endif

template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const SupportFunctionT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const ZonotopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

