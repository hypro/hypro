#ifndef INCL_FROM_CONVERTERHEADER
static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const OrthoplexT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return _source;
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const SimplexT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const TemplatePolyhedronT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const BoxT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const CarlPolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const ConstraintSetT<Number,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const Ellipsoid& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const HPolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const OrthogonalPolyhedronT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const VPolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const DifferenceBoundsT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const PolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const SupportFunctionT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

template<typename Number>
template<typename OrthoplexSetting, typename InSetting>
OrthoplexT<Number,Converter<Number>,OrthoplexSetting> Converter<Number>::toOrthoplex( const ZonotopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return OrthoplexT<Number,Converter<Number>,OrthoplexSetting>();
}

