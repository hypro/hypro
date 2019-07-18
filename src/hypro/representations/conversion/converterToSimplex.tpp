#ifndef INCL_FROM_CONVERTERHEADER
static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const SimplexT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return _source;
}

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const TemplatePolyhedronT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const BoxT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const CarlPolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const ConstraintSetT<Number,InSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const Ellipsoid& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const HPolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const OrthogonalPolyhedronT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const VPolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const DifferenceBoundsT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const PolytopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const SupportFunctionT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const ZonotopeT<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}


template<typename Number>
template<typename SimplexSetting, typename InSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const OrthoplexT<Number,Converter<Number>,InSetting>& source, const CONV_MODE ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

