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
typename Converter<Number>::Polytope Converter<Number>::toPolytope(const Polytope& source, const CONV_MODE){
	return source;
}

//Conversion from box to ppl poly
template<typename Number>
typename Converter<Number>::Polytope Converter<Number>::toPolytope(const Box& source, const CONV_MODE){
	return Converter<Number>::Polytope(source.matrix(), source.vector());
}

//Conversion from constraintSet to ppl poly
template<typename Number>
typename Converter<Number>::Polytope Converter<Number>::toPolytope(const ConstraintSet& source, const CONV_MODE){
	return Converter<Number>::Polytope(source.matrix(), source.vector());
}

//Conversion from difference bounds to ppl poly
template<typename Number>
typename Converter<Number>::Polytope Converter<Number>::toPolytope(const DifferenceBounds& source, const CONV_MODE){
	// TODO IMPLEMENT
}

//Conversion from ellipsoid to ppl poly
template<typename Number>
typename Converter<Number>::Polytope Converter<Number>::toPolytope(const Ellipsoid& source, const CONV_MODE){
	Converter<Number>::HPolytope tmp = Converter<Number>::toHPolytope(source);
	return Converter<Number>::Polytope(tmp.matrix(), tmp.vector());
}

//Conversion from hpoly to ppl poly
template<typename Number>
typename Converter<Number>::Polytope Converter<Number>::toPolytope(const HPolytope& source, const CONV_MODE){
	return Converter<Number>::Polytope(source.matrix(), source.vector());
}

//Conversion from vpoly to ppl poly
template<typename Number>
typename Converter<Number>::Polytope Converter<Number>::toPolytope(const VPolytope& source, const CONV_MODE){
	return Converter<Number>::Polytope(source.vertices());
}

//Conversion from supportfunction to ppl poly
template<typename Number>
typename Converter<Number>::Polytope Converter<Number>::toPolytope(const SupportFunction& source, const CONV_MODE, std::size_t numberOfDirections){
	//First convert to HPolytope, afterwards to ppl Polytope
	Converter<Number>::HPolytope tmp = Converter<Number>::toHPolytope(source, std::vector<vector_t<Number>>(), CONV_MODE::EXACT, numberOfDirections);
	return Converter<Number>::Polytope(tmp.matrix(), tmp.vector());
}

//Conversion from zonotopoe to ppl poly 
template<typename Number>
typename Converter<Number>::Polytope Converter<Number>::toPolytope(const Zonotope& source, const CONV_MODE){
	return Converter<Number>::Polytope(source.vertices());
}
