#ifndef INCL_FROM_CONVERTERHEADER
static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const SimplexT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return _source;
}

template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const TemplatePolyhedronT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const BoxT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const CarlPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const ConstraintSetT<Number,inSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const Ellipsoid& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const HPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const OrthogonalPolyhedronT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const VPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const DifferenceBoundsT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

#ifdef HYPRO_USE_PPL
template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const PolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}
#endif

template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const SupportFunctionT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

template<typename Number>
template<typename SimplexSetting, typename inSetting>
SimplexT<Number,Converter<Number>,SimplexSetting> Converter<Number>::toSimplex( const ZonotopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return SimplexT<Number,Converter<Number>,SimplexSetting>();
}

