#ifndef INCL_FROM_CONVERTERHEADER
static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

namespace hypro { 

template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const StarsetT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return _source;
}

template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const TemplatePolyhedronT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return StarsetT<Number,Converter<Number>,StarsetSetting>();
}

template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const BoxT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return StarsetT<Number,Converter<Number>,StarsetSetting>();
}

template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const CarlPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return StarsetT<Number,Converter<Number>,StarsetSetting>();
}

template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const ConstraintSetT<Number,inSetting>& _source, const CONV_MODE  ) {
	return StarsetT<Number,Converter<Number>,StarsetSetting>();
}

template<typename Number>
template<typename StarsetSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const Ellipsoid& _source, const CONV_MODE  ) {
	return StarsetT<Number,Converter<Number>,StarsetSetting>();
}

template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const HPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
    matrix_t<Number> newmGenerator=matrix_t<Number>::Identity(_source.matrix().cols(),_source.matrix().cols()); 
    vector_t<Number> newmCenter=vector_t<Number>::Zero(_source.matrix().cols());
    return StarsetT<Number,Converter<Number>,StarsetSetting>(newmCenter,_source.matrix(),_source.vector(),newmGenerator);
}


template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const VPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return StarsetT<Number,Converter<Number>,StarsetSetting>();
}

template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const DifferenceBoundsT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return StarsetT<Number,Converter<Number>,StarsetSetting>();
}

#ifdef HYPRO_USE_PPL
template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const PolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return StarsetT<Number,Converter<Number>,StarsetSetting>();
}
#endif

template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const SupportFunctionT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return StarsetT<Number,Converter<Number>,StarsetSetting>();
}

template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const ZonotopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return StarsetT<Number,Converter<Number>,StarsetSetting>();
}

template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const SupportFunctionNewT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return StarsetT<Number,Converter<Number>,StarsetSetting>();
}

} //namespace hypro
