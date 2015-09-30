#pragma once 

#define SUPPORT_MPFR
/* #undef COMPARE_CDD */
/* #undef COMPARE_POLYMAKE */

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

#include <carl/numbers/numbers.h>
#include <carl/numbers/FLOAT_T.h>
#include <carl/interval/Interval.h>
#include <carl/core/Variable.h>
#include <carl/io/streamingOperators.h>
#include <carl/util/SFINAE.h>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/src/MatrixFunctions/MatrixExponential.h>

static const unsigned TOLLERANCE_ULPS = 8192;

// global typedefs
namespace hypro {
template <typename Number>
using vector_t = Eigen::Matrix<Number, Eigen::Dynamic, 1>;

template <typename Number>
using matrix_t = Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>;

template <typename Number>
class Polytope;

template <typename Number>
using valuation_t = Polytope<Number>;

template <typename Number>
using vectorSet = std::set<vector_t<Number>>;
}

namespace Eigen {
template <typename Number>
struct NumTraits<carl::FLOAT_T<Number>> {
	enum {
		IsComplex = 0,
		IsInteger = 0,
		ReadCost = 1,
		AddCost = 1,
		MulCost = 1,
		IsSigned = 1,
		RequireInitialization = 1
	};

	typedef carl::FLOAT_T<Number> Real;
	typedef carl::FLOAT_T<Number> NonInteger;
	typedef carl::FLOAT_T<Number> Nested;

	static inline Real epsilon() { return std::numeric_limits<Real>::epsilon(); }
	static inline Real dummy_precision() {
		// make sure to override this for floating-point types
		return Real( 0 );
	}
	static inline carl::FLOAT_T<Number> highest() { return carl::FLOAT_T<Number>::maxVal(); }
	static inline carl::FLOAT_T<Number> lowest() { return carl::FLOAT_T<Number>::minVal(); }
};