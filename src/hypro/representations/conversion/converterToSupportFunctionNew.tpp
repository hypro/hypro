#ifndef INCL_FROM_CONVERTERHEADER
static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const SupportFunctionNewT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE ){ 
	return _source;
}

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const BoxT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const ConstraintSetT<Number,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>
template<typename SFNSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const Ellipsoid& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const HPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

//template<typename Number>
//template<typename SFNSetting, typename inSetting>
//SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const OrthogonalPolyhedronT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
//	return Converter<Number>::SupportFunctionNew();
//}

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const VPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>	
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const DifferenceBoundsT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

#ifdef HYPRO_USE_PPL
template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const PolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}
#endif

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const SupportFunctionT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const ZonotopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	return Converter<Number>::SupportFunctionNew();
}

