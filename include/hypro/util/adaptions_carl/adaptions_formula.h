#pragma once
#include "hypro/carlTypes.h"
#include "hypro/flags.h"

#include <variant>

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

template <typename... VarTypes>
const carl::Variable& getVar( const std::variant<VarTypes...>& packedVar ) {
	return std::get<carl::Variable>( packedVar );
}

template <typename VarType>
const carl::Variable& getVar( const VarType& nonPackedVar ) {
	return nonPackedVar;
}

}  // namespace hypro
