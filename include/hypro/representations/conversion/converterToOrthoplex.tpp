/*
#ifndef INCL_FROM_CONVERTERHEADER
static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

namespace hypro {

template<typename Number>
template<typename OrthoplexSetting, typename inSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const OrthoplexT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return _source;
}

template<typename Number>
template<typename OrthoplexSetting, typename inSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const TemplatePolyhedronT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename inSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const BoxT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename inSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const CarlPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename inSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const ConstraintSetT<Number,inSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const Ellipsoid& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename inSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const HPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename inSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const VPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename inSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const DifferenceBoundsT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

#ifdef HYPRO_USE_PPL
template<typename Number>
template<typename OrthoplexSetting, typename inSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const PolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}
#endif

template<typename Number>
template<typename OrthoplexSetting, typename inSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const SupportFunctionT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename inSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const ZonotopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

} //namespace hypro
*/