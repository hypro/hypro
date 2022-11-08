#pragma once
#include "hypro/carlTypes.h"
#include "hypro/flags.h"

#include <variant>

namespace hypro {

template <typename Polynomial, typename Variable, typename Substitute>
Polynomial substitute( const Polynomial& poly, const Variable& v, const Substitute& substitute ) {
	/*#ifdef CARL_OLD_STRUCTURE
		return poly.substitute( v, substitute );
	#else*/
	return carl::substitute( poly, v, substitute );
	// #endif
}

template <typename Number>
FormulaT<Number> substitute( const FormulaT<Number>& formula, const carl::Variable& v, const PolyT<Number>& substitute ) {
#ifdef CARL_OLD_STRUCTURE
	return formula.substitute( v, substitute );
#else
	return carl::substitute( formula, v, substitute );
#endif
}

template <typename Number>
inline Number constantPart( const PolyT<Number>& in ) {
#ifdef CARL_OLD_STRUCTURE
	return in.constantPart();
#else
	return in.constant_part();
#endif
}

template <typename Number>
bool hasVariable( const ConstraintT<Number>& in, const carl::Variable& var ) {
#ifdef CARL_OLD_STRUCTURE
	return in.hasVariable( var );
#else
	return std::find( std::begin( in.variables() ), std::end( in.variables() ), var ) != std::end( in.variables() );
#endif
}

template <typename... VarTypes>
const carl::Variable& getVar( const std::variant<VarTypes...>& packedVar ) {
	return std::get<carl::Variable>( packedVar );
}

template <typename VarType>
const carl::Variable& getVar( const VarType& nonPackedVar ) {
	return nonPackedVar;
}

template <typename Number>
bool isNary( const FormulaT<Number>& in ) {
#ifdef CARL_OLD_STRUCTURE
	return in.isNary();
#else
	return in.is_nary();
#endif
}

template <typename Number>
bool isNumber( const PolyT<Number>& in ) {
#ifdef CARL_OLD_STRUCTURE
	return in.isNumber();
#else
	return in.is_number();
#endif
}

template <typename Number>
bool isLinear( const PolyT<Number>& in ) {
#ifdef CARL_OLD_STRUCTURE
	return in.isLinear();
#else
	return in.is_linear();
#endif
}

template <typename Number>
carl::FormulaType getType( const FormulaT<Number>& in ) {
#ifdef CARL_OLD_STRUCTURE
	return in.getType();
#else
	return in.type();
#endif
}

template <typename Number>
void getConstraints( const FormulaT<Number>& in, std::vector<ConstraintT<tNumber>>& newConstraints ) {
#ifdef CARL_OLD_STRUCTURE
	in.getConstraints( newConstraints );
#else
	carl::arithmetic_constraints( in, newConstraints );
#endif
}

template <typename Number>
bool isFalse( const FormulaT<Number>& formula ) {
#ifdef CARL_OLD_STRUCTURE
	return formula.isFalse();
#else
	return formula.is_false();
#endif
}

template <typename Number>
bool isTrue( const FormulaT<Number>& formula ) {
#ifdef CARL_OLD_STRUCTURE
	return formula.isTrue();
#else
	return formula.is_true();
#endif
}

inline carl::Variable freshRealVariable( const std::string& name ) {
#ifdef CARL_OLD_STRUCTURE
	return carl::freshRealVariable( name );
#else
	return carl::fresh_real_variable( name );
#endif
}

}  // namespace hypro
