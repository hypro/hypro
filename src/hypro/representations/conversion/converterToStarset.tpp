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
	
	return StarsetT<Number, Converter<Number>, StarsetSetting>( _source.matrix(), _source.vector() );

}

template<typename Number>
template<typename StarsetSetting, typename inSetting>
StarsetT<Number,Converter<Number>,StarsetSetting> Converter<Number>::toStarset( const BoxT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	StarsetT<Number,Converter<Number>,StarsetSetting> ccc=StarsetT<Number,Converter<Number>,StarsetSetting>( _source.matrix(), _source.vector() );

	return ccc;
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
    return StarsetT<Number,Converter<Number>,StarsetSetting>(_source.matrix(),_source.vector());
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
