#ifndef INCL_FROM_CONVERTERHEADER
static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const TemplatePolyhedronT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return _source;
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const BoxT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const CarlPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const ConstraintSetT<Number,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const Ellipsoid& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const HPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const OrthogonalPolyhedronT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const VPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const DifferenceBoundsT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

#ifdef HYPRO_USE_PPL
template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const PolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}
#endif

template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const SupportFunctionT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}

template<typename Number>
template<typename TemplatePolyhedronSetting, typename inSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const ZonotopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::TemplatePolyhedron();
}


template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const SimplexT<Number,Converter<Number>,InSetting>& source, const CONV_MODE ) {
	return TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting>();
}


template<typename Number>
template<typename TemplatePolyhedronSetting, typename InSetting>
TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting> Converter<Number>::toTemplatePolyhedron( const OrthoplexT<Number,Converter<Number>,InSetting>& source, const CONV_MODE ) {
	return TemplatePolyhedronT<Number,Converter<Number>,TemplatePolyhedronSetting>();
}

