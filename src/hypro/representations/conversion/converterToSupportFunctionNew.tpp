#ifndef INCL_FROM_CONVERTERHEADER
static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

// conversion from support function to support function (no differentiation between conversion modes - always EXACT)
template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const SupportFunctionNewT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE ){ 
	return SupportFunctionNewT<Number,Converter<Number>,SFNSetting>(_source);
}

// conversion from box to support function (no differentiation between conversion modes - always EXACT)
template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const BoxT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	BoxT<Number,Converter<Number>,inSetting> tmp(_source);
	return SupportFunctionNewT<Number,Converter<Number>,SFNSetting>(static_cast<GeometricObject<Number,BoxT<Number,Converter<Number>,inSetting>>*>(&tmp));
}

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const ConstraintSetT<Number,inSetting>& _source, const CONV_MODE  ) {
	ConstraintSetT<Number,inSetting> tmp(_source);
	return SupportFunctionNewT<Number,Converter<Number>,SFNSetting>(static_cast<GeometricObject<Number,ConstraintSetT<Number,inSetting>>*>(&tmp));
}

template<typename Number>
template<typename SFNSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const Ellipsoid& _source, const CONV_MODE  ) {
	Ellipsoid tmp(_source);
	return SupportFunctionNewT<Number,Converter<Number>,SFNSetting>(static_cast<GeometricObject<Number,Ellipsoid>*>(&tmp));
}

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const HPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	HPolytopeT<Number,Converter<Number>,inSetting> tmp(_source);
	return SupportFunctionNewT<Number,Converter<Number>,SFNSetting>(static_cast<GeometricObject<Number,HPolytopeT<Number,Converter<Number>,inSetting>>*>(&tmp));
}

//template<typename Number>
//template<typename SFNSetting, typename inSetting>
//SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const OrthogonalPolyhedronT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
//	OrthogonalPolyhedronT<Number,Converter<Number>,inSetting> tmp(_source);
//	return SupportFunctionNewT<Number,Converter<Number>,SFNSetting>(static_cast<GeometricObject<Number,>*>(&tmp));
//}

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const VPolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	VPolytopeT<Number,Converter<Number>,inSetting> tmp(_source);
	return SupportFunctionNewT<Number,Converter<Number>,SFNSetting>(static_cast<GeometricObject<Number,VPolytopeT<Number,Converter<Number>,inSetting>>*>(&tmp));
}

template<typename Number>	
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const DifferenceBoundsT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	DifferenceBoundsT<Number,Converter<Number>,inSetting> tmp(_source);
	return SupportFunctionNewT<Number,Converter<Number>,SFNSetting>(static_cast<GeometricObject<Number,DifferenceBoundsT<Number,Converter<Number>,inSetting>>*>(&tmp));
}

#ifdef HYPRO_USE_PPL
template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const PolytopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	PolytopeT<Number,Converter<Number>,inSetting> tmp(_source);
	return SupportFunctionNewT<Number,Converter<Number>,SFNSetting>(static_cast<GeometricObject<Number,PolytopeT<Number,Converter<Number>,inSetting>>*>(&tmp));
}
#endif

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const SupportFunctionT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	SupportFunctionT<Number,Converter<Number>,inSetting> tmp(_source);
	return SupportFunctionNewT<Number,Converter<Number>,SFNSetting>(static_cast<GeometricObject<Number,SupportFunctionT<Number,Converter<Number>,inSetting>>*>(&tmp));
}

template<typename Number>
template<typename SFNSetting, typename inSetting>
SupportFunctionNewT<Number,Converter<Number>,SFNSetting> Converter<Number>::toSupportFunctionNew( const ZonotopeT<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {
	ZonotopeT<Number,Converter<Number>,inSetting> tmp(_source);
	return SupportFunctionNewT<Number,Converter<Number>,SFNSetting>(static_cast<GeometricObject<Number,ZonotopeT<Number,Converter<Number>,inSetting>>*>(&tmp));
}

