#pragma once

#include <set>
#include <map>
#include <cassert>

#include "types.h"
//#include <carl/core/logging.h>
#include <carl/core/MultivariatePolynomial.h>
#include <carl/numbers/numbers.h>
#include <carl/numbers/FLOAT_T.h>
#include <carl/core/Variable.h>
//#include <carl/core/carlLoggingHelper.h>
#include <carl/util/SFINAE.h>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/src/MatrixFunctions/MatrixExponential.h>
#include "util/operators.h"

#ifdef COMPARE_CDD
#ifdef __cplusplus
extern "C" {
#endif
	#include <setoper.h>
	#include <cdd.h>
#ifdef __cplusplus
}
#endif
#endif

#include "util/VariablePool.h"

// needed for vector outstream operator:
using carl::operator<<;

#define reachLin_VERSION_MAJOR 0
#define reachLin_VERSION_MINOR 1

#define DEBUG 1

#define DEFAULT_DIM 5
#define MAXIMAL_DIMENSION 5

// Do we eliminate dimensions according to a dynamic heuristic.
#define DYNAMICHEURISTIC 0
#define reachLin_PRIMITIVES_LOCATION "../polyhedra/"
#define reachLin_NR_PRIMITIVES 100

#define PI_UP 3.141592655
#define PI_DN 3.141592654

namespace hypro
{
template<typename Number>
using vector_t = Eigen::Matrix<Number, Eigen::Dynamic, 1>;

template<typename Number>
using matrix_t = Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>;

template<typename Number>
class Polytope;

template<typename Number>
using valuation_t = Polytope<Number>;

template<typename Number>
using vectorSet = std::set<vector_t<Number>>;
}

/**
 * Defines for reachability algorithm based on polytopes
 */
#define fReach_TIMEBOUND 2
#define fReach_TIMEDISCRETIZATION 5
#define fReach_DENOMINATOR 1000000000
//define for debugging: triggers console output
#define fReach_DEBUG

/**
 * author: ckugler
 * Defines for implementation of Fukuda's Minkowski Sum algorithm
 */
#define EPSILON 0.000001
#define POS_CONSTANT 100
//define for debugging: triggers console output
//#define fukuda_DEBUG

namespace Eigen
{
	template<typename Number> 
	struct NumTraits<carl::FLOAT_T<Number>>
	{
		enum
		{
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

		static inline Real epsilon() { return Real(0); }
		static inline Real dummy_precision()
		{
			// make sure to override this for floating-point types
			return Real(0);
		}
		//static inline carl::FLOAT_T<Number> highest() { return carl::FLOAT_T<Number>::maxVal(); }
		//static inline carl::FLOAT_T<Number> lowest()  { return carl::FLOAT_T<Number>::minVal(); }
	};
	
	template<typename Number>
	bool operator<(const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs) {
		if(lhs.rows() != rhs.rows())
			return false;
			
		for(unsigned dim = 0; dim < lhs.rows(); ++dim) {
			if(lhs(dim) > rhs(dim)) {
				return false;
			} else if( lhs(dim) < rhs(dim) ) {
				return true;
			}
		}
		return false;
	}

	template<typename Number>
	bool operator==(const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs) {
		if(lhs.rows() != rhs.rows())
			return false;
		
		for(unsigned dim = 0; dim < lhs.rows(); ++dim) {
			if(lhs(dim) != rhs(dim)) {
				return false;
			}
		}
		return true;
	}
}
