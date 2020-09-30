#pragma once
#include "../../carlTypes.h"
#include "../../flags.h"

namespace hypro {

#ifdef CARL_POLY_MEMBER_SUBSTITUTE
template <typename Polynomial, typename Variable, typename Substitute>
Polynomial substitute( const Polynomial& poly, const Variable& v, const Substitute& substitute ) {
	return poly.substitute( v, substitute );
}
#else
template <typename Polynomial, typename Variable, typename Substitute>
Polynomial substitute( const Polynomial& poly, const Variable& v, const Substitute& substitute ) {
	return carl::substitute( poly, v, substitute );
}
#endif

#ifdef CARL_VARIABLE_VARIANTS
template <typename VarType>
const carl::Variable& getVar( const VarType& packedVar ) {
	return std::get<carl::Variable>( packedVar );
}
#else
template <typename VarType>
const carl::Variable& getVar( const VarType& nonPackedVar ) {
	return nonPackedVar;
}
#endif
}  // namespace hypro
