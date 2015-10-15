#pragma once

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "flags.h"
#include <carl/numbers/numbers.h>
#include <carl/core/Variable.h>
#include <carl/core/MultivariatePolynomial.h>
#include <carl/io/streamingOperators.h>
#include <carl/util/SFINAE.h>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/src/MatrixFunctions/MatrixExponential.h>


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

#define PI_UP 3.141592655
#define PI_DN 3.141592654

static const unsigned FLOAT_PRECISION = 128;
static const unsigned TOLLERANCE_ULPS = 8192;
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

#include "typedefs.h"
#include "util/adaptions_eigen.h"