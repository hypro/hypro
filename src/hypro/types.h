#pragma once

#include <carl/numbers/numbers.h>
#include <carl/util/hash.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <iosfwd>
#include <set>

// global typedefs
namespace hypro {

/**
 * @brief Number type used for timings and time intervals.
 */
using tNumber = mpq_class;

/**
 * typedef wrapping an Eigen::Matrix type with only one column.
 */
template <typename Number>
using vector_t = Eigen::Matrix<Number, Eigen::Dynamic, 1>;

/**
 * typedef wrapping an Eigen::Matrix type.
 */
template <typename Number>
using matrix_t = Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>;

template <typename Number>
using vectorSet = std::set<vector_t<Number>>;

/**
 * @brief      Enum implementing a tribool.
 */
enum class TRIBOOL { TRUE,
					 FALSE,
					 NSET };

enum class REACHABILITY_RESULT {
	SAFE,
	UNKNOWN
};

enum class PLOTTYPE { pdf,
					  png,
					  eps,
					  gen,
					  tex,
					  nset };

/**
 * @brief Enum to represent set states such as empty and universal.
 */
enum class SETSTATE { UNKNOWN,
					  NONEMPTY,
					  EMPTY,
					  UNIVERSAL };

/**
 * @brief      Enum of possible solution types for linear optimization.
 */
enum class SOLUTION { FEAS = 0,
					  INFEAS,
					  INFTY,
					  UNKNOWN };

/**
 * @brief      Enum for set containment results. If known, we can make a statement
 * about full or partial containment, otherwise fall back to YES/NO. Note: BOT is used for UNKNOWN.
 */
enum class CONTAINMENT { NO = -1,
						 BOT = 0,
						 PARTIAL = 1,
						 FULL = 2,
						 YES = 3 };

/**
 * @brief classifies the type of subspace in case subspace decomposition is used.
 */
enum class SUBSPACETYPE { LTI = 0,
						  TIMED = 1,
						  DISCRETE = 2,
						  RECTANGULAR = 3 };

/**
 * @brief classifies the type of location, which reflects the dynamics in case we dynamically detect subspaces.
 */
enum class LOCATIONTYPE { LTILOC = 0,
						  TIMEDLOC = 1,
						  RECTANGULARLOC = 2 };

/**
 * @brief classifies the type of dynamics of a flow for a location.
 */
enum class DynamicType { linear = 0,
						 affine,
						 rectangular,
						 timed,
						 discrete,
						 mixed,
						 undefined };

enum class AGG_SETTING { MODEL,
						 AGG,
						 NO_AGG };

}  // namespace hypro

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

	using Real = carl::FLOAT_T<Number>;
	using NonInteger = carl::FLOAT_T<Number>;
	using Nested = carl::FLOAT_T<Number>;

	static inline Real epsilon() { return std::numeric_limits<Real>::epsilon(); }
	static inline Real dummy_precision() {
		// make sure to override this for floating-point types
		return Real( 0 );
	}
	static inline carl::FLOAT_T<Number> highest() { return carl::FLOAT_T<Number>::maxVal(); }
	static inline carl::FLOAT_T<Number> lowest() { return carl::FLOAT_T<Number>::minVal(); }
};

template <>
struct NumTraits<mpq_class> : GenericNumTraits<mpq_class> {
	typedef mpq_class Real;
	typedef mpq_class NonInteger;
	typedef mpq_class Nested;
	static inline Real epsilon() { return 0; }
	static inline Real dummy_precision() { return 0; }
	static inline Real digits10() { return 0; }
	enum {
		IsInteger = 0,
		IsSigned = 1,
		IsComplex = 0,
		RequireInitialization = 1,
		ReadCost = 6,
		AddCost = 150,
		MulCost = 100
	};
};

/*
namespace internal {
template<> struct scalar_score_coeff_op<mpq_class> {
	struct result_type : boost::totally_ordered1<result_type> {
		std::size_t len;
		result_type(int i = 0) : len(i) {} // Eigen uses Score(0) and Score()
		result_type(mpq_class const& q) :
		  len(mpz_size(q.get_num_mpz_t())+
			  mpz_size(q.get_den_mpz_t())-1) {}
		friend bool operator<(result_type x, result_type y) {
			// 0 is the worst possible pivot
			if (x.len == 0) return y.len > 0;
			if (y.len == 0) return false;
			// Prefer a pivot with a small representation
			return x.len > y.len;
		}
		friend bool operator==(result_type x, result_type y) {
			// Only used to test if the score is 0
			return x.len == y.len;
		}
	};
  result_type operator()(mpq_class const& x) const { return x; }
};
} // namespace internal
*/

}  // namespace Eigen

namespace std {
/**
 * @brief      Outstream operator for the SOLUTION enum.
 * @param      _out  The outstream reference.
 * @param[in]  _in   The enum type.
 * @return     A reference to the outstream.
 */
inline std::ostream& operator<<( std::ostream& _out, const hypro::SOLUTION& _in ) {
	switch ( _in ) {
		case hypro::SOLUTION::FEAS: {
			_out << "FEAS";
			break;
		}
		case hypro::SOLUTION::INFEAS: {
			_out << "INFEAS";
			break;
		}
		case hypro::SOLUTION::INFTY: {
			_out << "INFTY";
			break;
		}
		case hypro::SOLUTION::UNKNOWN: {
			_out << "UNKNOWN";
			break;
		}
		default:
			_out << "Something went terribly wrong.";
	}
	return _out;
}

/**
 * @brief      Outstream operator for the CONTAINMENT enum.
 * @param      _out  The outstream reference.
 * @param[in]  _in   The enum type.
 * @return     A reference to the outstream.
 */
inline std::ostream& operator<<( std::ostream& _out, const hypro::CONTAINMENT& _in ) {
	switch ( _in ) {
		case hypro::CONTAINMENT::NO:
			_out << "N";
			break;
		case hypro::CONTAINMENT::YES:
			_out << "Y";
			break;
		case hypro::CONTAINMENT::FULL:
			_out << "F";
			break;
		case hypro::CONTAINMENT::PARTIAL:
			_out << "P";
			break;
		case hypro::CONTAINMENT::BOT:
			_out << "B";
			break;
		default:
			_out << "Something went terribly wrong.";
	}
	return _out;
}
}  // namespace std

#include "util/adaptions_eigen/adaptions_eigen.h"
#include "util/conversion.h"
