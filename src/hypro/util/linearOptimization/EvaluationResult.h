#pragma once

#include "types.h"

namespace hypro {

/**
 * @brief      Struct holding results obtained from the linear optimization engine.
 * @tparam     Number  The used number type.
 */
template <typename Number>
struct EvaluationResult {
	Number supportValue;			//*< The value returned by the evaluation.
	vector_t<Number> optimumValue;  //*< The point leading to the evaluation value (extremum in direction).
	SOLUTION errorCode;				//*< Potential error code indicating success or failure of the evaluation.

	EvaluationResult() : supportValue(Number(0)), optimumValue(vector_t<Number>::Zero(0)), errorCode(SOLUTION::INFEAS)
		{}

	EvaluationResult(SOLUTION err) : supportValue(Number(0)), optimumValue(vector_t<Number>::Zero(0)), errorCode(err)
		{}

	EvaluationResult(const Number& val, SOLUTION err) : supportValue(val), optimumValue(vector_t<Number>::Zero(0)), errorCode(err)
		{}

	EvaluationResult(const vector_t<Number>& val, SOLUTION err) : supportValue(0), optimumValue(val), errorCode(err)
		{}

	EvaluationResult(Number sValue, const vector_t<Number>& val, SOLUTION err) : supportValue(sValue), optimumValue(val), errorCode(err)
	{}

	friend std::ostream& operator<<(std::ostream& _out, const EvaluationResult<Number>& _in) {
		_out << _in.supportValue << "(" << _in.errorCode << ")";
		return _out;
	}
};

} // namespace hypro
