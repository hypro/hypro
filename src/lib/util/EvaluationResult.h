#pragma once
#include "../types.h"

namespace hypro {

template <typename Number>
struct EvaluationResult {
	Number supportValue;			// the value returned by the evaluation
	vector_t<Number> optimumValue;  // the point leading to the evaluation value (extremum in direction)
	SOLUTION errorCode;				// potential error code indicating success or failure of the evaluation

	EvaluationResult() : supportValue(Number(0)), optimumValue(vector_t<Number>::Zero(0)), errorCode(SOLUTION::INFEAS)
		{}

	EvaluationResult(const Number& val, SOLUTION err) : supportValue(val), optimumValue(vector_t<Number>::Zero(0)), errorCode(err)
		{}

	EvaluationResult(const vector_t<Number>& val, SOLUTION err) : supportValue(0), optimumValue(val), errorCode(err)
		{}

	friend std::ostream& operator<<(std::ostream& _out, const EvaluationResult<Number>& _in) {
		_out << _in.supportValue << "(" << _in.errorCode << ")";
		return _out;
	}
};

} // namespace hypro