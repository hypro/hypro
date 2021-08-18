#pragma once

#include "../../types.h"

namespace hypro {

/**
 * @brief      Struct holding results obtained from the linear optimization engine.
 * @tparam     Number  The used number type.
 */
template <typename Number>
struct EvaluationResult {
	vector_t<Number> optimumValue;			//*< The point leading to the evaluation value (extremum in direction).
	Number supportValue = Number( 0 );		//*< The value returned by the evaluation.
	SOLUTION errorCode = SOLUTION::INFEAS;	//*< Potential error code indicating success or failure of the evaluation.

	EvaluationResult() {}

	explicit EvaluationResult( SOLUTION err )
		: errorCode( err ) {}

	EvaluationResult( const Number& val, SOLUTION err )
		: supportValue( val )
		, errorCode( err ) {}

	EvaluationResult( const vector_t<Number>& val, SOLUTION err )
		: optimumValue( val )
		, errorCode( err ) {}

	EvaluationResult( Number sValue, const vector_t<Number> val, SOLUTION err )
		: optimumValue( val )
		, supportValue( sValue )
		, errorCode( err ) {}

	~EvaluationResult() {
	}

	friend std::ostream& operator<<( std::ostream& _out, const EvaluationResult<Number>& _in ) {
		_out << _in.supportValue << "(" << _in.errorCode << ") : \n"
			 << _in.optimumValue;
		return _out;
	}
};

template <typename Number>
bool operator<( const EvaluationResult<Number>& lhs, const EvaluationResult<Number>& rhs ) {
	if ( lhs.errorCode == SOLUTION::INFEAS ) {
		return true;
	}
	if ( rhs.errorCode == SOLUTION::INFEAS ) {
		return false;
	}
	if ( lhs.errorCode == SOLUTION::INFTY ) {
		// note that if both are infty, this operator does not make sense and always will return false.
		return false;
	}
	if ( rhs.errorCode == SOLUTION::INFTY ) {
		return true;
	}

	return lhs.supportValue < rhs.supportValue;
}

template <typename Number>
bool operator>( const EvaluationResult<Number>& lhs, const EvaluationResult<Number>& rhs ) {
	return rhs < lhs;
}

template <typename Number>
bool operator==( const EvaluationResult<Number>& lhs, const EvaluationResult<Number>& rhs ) {
	if ( lhs.errorCode != rhs.errorCode ) {
		return false;
	}
	if ( lhs.supportValue != rhs.supportValue ) {
		return false;
	}

	return lhs.optimumValue == rhs.optimumValue;
}

}  // namespace hypro
