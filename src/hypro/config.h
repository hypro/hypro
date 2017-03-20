#pragma once

#include "flags.h"
#include "util/convenienceOperators.h"
#include "util/logging/Logger.h"

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

/**
 * \namespace hypro
 * \brief The most general namespace for the HyPro library.
 */

/**
 * \namespace parser
 * \brief Namespace holding parsing related code and structs.
 */

/**
 * \namespace plotting
 * \brief Namespace holding plotting related code and structs.
 */

/**
 * \namespace reachability
 * \brief Namespace holding reachability analysis related code and structs.
 */

/** \addtogroup globals Global definitions and constants
 * @{
 */

// Do we eliminate dimensions according to a dynamic heuristic.
#define DYNAMICHEURISTIC 0

#define PI_UP 3.1415926535897932384626433832795028841972
#define PI_DN 3.1415926535897932384626433832795028841971

/** The common denominator used for the PPL wrapper class. */
static const unsigned long fReach_DENOMINATOR = 1000000000;

/** The default threshold value for double ULP-comparison. */
static const unsigned long default_double_comparison_ulps = 128;

/** The default number of template directions used in templated evaluation. */
static const unsigned long defaultTemplateDirectionCount = 8;

/** TODO: Document! */
static const unsigned long MAX_DIMENSION_LIMIT = 100;

/** A limit required for Fukudas Minkowski-Sum algorithm. */
static const double EPSILON = 0.000001;

/** Some required positive constant for Fukudas Minkowski-Sum algorithm.*/
static const long POS_CONSTANT = 100;

static const unsigned SF_CACHE_SIZE = 200;

/** Enables debug output for Fukudas Minkowski-Sum algorithm. */
//#define fukuda_DEBUG

/** @} */
