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

// Do we eliminate dimensions according to a dynamic heuristic.
#define DYNAMICHEURISTIC 0
#define reachLin_PRIMITIVES_LOCATION "../polyhedra/"
#define reachLin_NR_PRIMITIVES 100

#define PI_UP 3.1415926535897932384626433832795028841972
#define PI_DN 3.1415926535897932384626433832795028841971

static const unsigned long fReach_DENOMINATOR = 1000000000;
static const unsigned long default_double_comparison_ulps = 128;
static const unsigned long defaultTemplateDirectionCount = 8;
static const unsigned long MAX_DIMENSION_LIMIT = 100;

/**
 * author: ckugler
 * Defines for implementation of Fukuda's Minkowski Sum algorithm
 */
static const double EPSILON = 0.000001;
static const long POS_CONSTANT = 100;
//#define fukuda_DEBUG
