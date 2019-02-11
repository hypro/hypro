/**
 * Specialization of the converter to convert any representation into PPL polytopes.
 *
 * @file converterToPolytope.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Phillip Tse
 */

#include "Converter.h"

//Conversion from ppl poly to ppl poly
template<typename Number>
template<typename PolytopeSetting, typename inSetting>
PolytopeT<Number,Converter,PolytopeSetting> Converter<Number>::toPolytope(const PolytopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE){
	return source;
}

//Conversion from box to ppl poly
template<typename Number>
template<typename PolytopeSetting, typename inSetting>
PolytopeT<Number,Converter,PolytopeSetting> Converter<Number>::toPolytope(const BoxT<Number,Converter<Number>,inSetting>& source, const CONV_MODE){
	return PolytopeT<Number,Converter,PolytopeSetting>(source.matrix(), source.vector());
}

//Conversion from constraintSet to ppl poly
template<typename Number>
template<typename PolytopeSetting, typename inSetting>
PolytopeT<Number,Converter,PolytopeSetting> Converter<Number>::toPolytope(const ConstraintSetT<Number,inSetting>& source, const CONV_MODE){
	return PolytopeT<Number,Converter,PolytopeSetting>(source.matrix(), source.vector());
}

//Conversion from difference bounds to ppl poly
template<typename Number>
template<typename PolytopeSetting, typename inSetting>
PolytopeT<Number,Converter,PolytopeSetting> Converter<Number>::toPolytope(const DifferenceBoundsT<Number,Converter<Number>,inSetting>& source, const CONV_MODE){
	// TODO IMPLEMENT
}

//Conversion from ellipsoid to ppl poly
template<typename Number>
template<typename PolytopeSetting, typename inSetting>
PolytopeT<Number,Converter,PolytopeSetting> Converter<Number>::toPolytope(const Ellipsoid& source, const CONV_MODE){
	Converter<Number>::HPolytope tmp = Converter<Number>::toHPolytope(source);
	return PolytopeT<Number,Converter,PolytopeSetting>(tmp.matrix(), tmp.vector());
}

//Conversion from hpoly to ppl poly
template<typename Number>
template<typename PolytopeSetting, typename inSetting>
PolytopeT<Number,Converter,PolytopeSetting> Converter<Number>::toPolytope(const HPolytopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE){
	return PolytopeT<Number,Converter,PolytopeSetting>(source.matrix(), source.vector());
}

//Conversion from vpoly to ppl poly
template<typename Number>
template<typename PolytopeSetting, typename inSetting>
PolytopeT<Number,Converter,PolytopeSetting> Converter<Number>::toPolytope(const VPolytopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE){
	return PolytopeT<Number,Converter,PolytopeSetting>(source.vertices());
}

//Conversion from supportfunction to ppl poly
template<typename Number>
template<typename PolytopeSetting, typename inSetting>
template<typename sfSetting>
PolytopeT<Number,Converter,PolytopeSetting> Converter<Number>::toPolytope(const SupportFunctionT<Number,Converter<Number>,inSetting>& source, const CONV_MODE, std::size_t numberOfDirections){
	//First convert to HPolytope, afterwards to ppl Polytope
	Converter<Number>::HPolytope tmp = Converter<Number>::toHPolytope(source, std::vector<vector_t<Number>>(), CONV_MODE::EXACT, numberOfDirections);
	return PolytopeT<Number,Converter,PolytopeSetting>(tmp.matrix(), tmp.vector());
}

//Conversion from zonotopoe to ppl poly
template<typename Number>
template<typename PolytopeSetting, typename inSetting>
PolytopeT<Number,Converter,PolytopeSetting> Converter<Number>::toPolytope(const ZonotopeT<Number,Converter<Number>,inSetting>& source, const CONV_MODE){
	return PolytopeT<Number,Converter,PolytopeSetting>(source.vertices());
}