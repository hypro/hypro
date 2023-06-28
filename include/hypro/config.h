/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "util/convenienceOperators.h"

#include <hypro/flags.h>

#ifdef COMPARE_CDD
#ifdef __cplusplus
extern "C" {
#endif
#include <cdd.h>
#include <setoper.h>
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

namespace hypro {

    constexpr double PI_UP = 3.1415926535897932384626433832795028841972;
    constexpr double PI_DN = 3.1415926535897932384626433832795028841971;
/// Do we eliminate dimensions according to a dynamic heuristic.
    constexpr int DYNAMICHEURISTIC = 0;

    constexpr unsigned long fReach_DENOMINATOR = 1000000000;  //!< @brief The common denominator used for the PPL wrapper class.

    constexpr unsigned long default_double_comparison_ulps = 128;  //!< @brief The default threshold value for double ULP-comparison.
// constexpr unsigned long default_double_comparison_ulps = 4096; //!< @brief The default threshold value for double
// ULP-comparison.

    constexpr unsigned long defaultTemplateDirectionCount = 8;    //!< @brief The default number of template directions used in templated evaluation.

    constexpr unsigned long defaultPPLDenominator = 1000000;

    constexpr unsigned long MAX_DIMENSION_LIMIT = 100;    //!< @brief

    constexpr double EPSILON = 0.000001;  //!< @brief A limit required for Fukudas Minkowski-Sum algorithm.

    constexpr long POS_CONSTANT = 100;    //!< @brief Some required positive constant for Fukudas Minkowski-Sum algorithm.

    constexpr unsigned SF_CACHE_SIZE = 200;     //!< @brief

/** Enables debug output for Fukudas Minkowski-Sum algorithm. */
//#define fukuda_DEBUG

}  // namespace hypro

/** @} */
