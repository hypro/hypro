#pragma once

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "flags.h"
#include "util/platform.h"
#include "util/convenienceOperators.h"
#include <carl/numbers/numbers.h>
#include <carl/core/Variable.h>
#include <carl/core/MultivariatePolynomial.h>
#include <carl/io/streamingOperators.h>
#include <carl/util/SFINAE.h>
CLANG_WARNING_DISABLE("-Wdeprecated-register")
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/src/MatrixFunctions/MatrixExponential.h>
CLANG_WARNING_RESET


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

#define PI_UP 3.1415926535897932384626433832795028841972
#define PI_DN 3.1415926535897932384626433832795028841971

static const unsigned FLOAT_PRECISION = 128;
//static const unsigned TOLLERANCE_ULPS = 8192;
static const unsigned MAX_DIMENSION_LIMIT = 128;

/**
 * Default values for reachability algorithms
 */
static const double fReach_TIMEBOUND = 2;
static const std::size_t fReach_ITERATIONDEPTH = 1;
static const std::size_t fReach_TIMEDISCRETIZATION = 100;
static const unsigned long fReach_DENOMINATOR = 1000000;

/**
 * author: ckugler
 * Defines for implementation of Fukuda's Minkowski Sum algorithm
 */
static const double EPSILON = 0.000001;
static const long POS_CONSTANT = 100;
// define for debugging: triggers console output
//#define fukuda_DEBUG

<<<<<<< HEAD
namespace Eigen {
template <typename Number>
bool operator<( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() ) return false;

	for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
		if ( lhs( dim ) > rhs( dim ) ) {
			return false;
		} else if ( lhs( dim ) < rhs( dim ) ) {
			return true;
		}
	}
	return false;
}

template <typename Number>
bool operator==( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() ) return false;

	for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
		// std::cout << lhs(dim) << std::endl;
		// std::cout << rhs(dim) << std::endl;

		// std::cout << "carl::AlmostEqual2sComplement(" << lhs(dim) << ", " << rhs(dim) << ", " << TOLLERANCE_ULPS <<
		// "): " <<  carl::AlmostEqual2sComplement(lhs(dim),rhs(dim),TOLLERANCE_ULPS) << std::endl;
		if ( !carl::AlmostEqual2sComplement( lhs( dim ), rhs( dim ), TOLLERANCE_ULPS ) ) {
			return false;
		}
	}
	return true;
}

// according to http://eigen.tuxfamily.org/bz/show_bug.cgi?id=257 comment 14 we use this:
template <typename Number>
hypro::matrix_t<Number> pseudoInverse( const hypro::matrix_t<Number>& a, Number epsilon = std::numeric_limits<Number>::epsilon() ) {
	Eigen::JacobiSVD<hypro::matrix_t<Number>> svd( a, Eigen::ComputeThinU | Eigen::ComputeThinV );
	Number tolerance = epsilon * std::max( a.cols(), a.rows() ) * svd.singularValues().array().abs()( 0 );
	return svd.matrixV() *
		   ( svd.singularValues().array().abs() > tolerance )
				 .select( svd.singularValues().array().inverse(), 0 )
				 .matrix()
				 .asDiagonal() *
		   svd.matrixU().adjoint();
}
}
=======
#include "typedefs.h"
#include "util/adaptions_eigen.h"
>>>>>>> 4f0e6cccca664d2a209de7238d58921fdbd8b6bc
