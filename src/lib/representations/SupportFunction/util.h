/*
 * @file   util.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	February 24, 2015
 * @version	February 24, 2015
 */

#pragma once

namespace hypro {
/*
* This structure describes the result of a support function evaluation
*/
template <typename Number>
struct evaluationResult {
	Number supportValue;			// the value returned by the support function evaluation
	vector_t<Number> optimumValue;  // the point leading to the support function value (extremum in direction)
	SOLUTION errorCode;				// potential error code indicating success or failure of the evaluation

	friend std::ostream& operator<<(std::ostream& _out, const evaluationResult<Number>& _in) {
		_out << _in.supportValue << "(" << _in.errorCode << ")";
		return _out;
	}
};

// This enum represents the support function type and is used to identify support function without instanceof operations
enum SF_TYPE { SUM, INTERSECT, LINTRAFO, SCALE, UNION, POLY, INFTY_BALL, TWO_BALL, ELLIPSOID, BOX, ZONOTOPE, NONE };
}
