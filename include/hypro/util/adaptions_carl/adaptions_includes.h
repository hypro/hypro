/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 13.09.22.
 */

#ifndef HYPRO_ADAPTIONS_INCLUDES_H
#define HYPRO_ADAPTIONS_INCLUDES_H

#include <hypro/flags.h>

#ifdef CARL_LOGGING_POST_1910
#else
#include <carl/core/carlLogging.h>
#include <carl/core/carlLoggingHelper.h>
#endif

#ifdef CARL_OLD_STRUCTURE
// clang-format off
#include <carl-logging/logging.h>
#include <carl-logging/Logger.h>
#include <carl-logging/carl-logging.h>
// clang-format on
#include <carl/core/MultivariatePolynomial.h>
#include <carl/core/Relation.h>
#include <carl/core/Variable.h>
#include <carl/core/VariablePool.h>
#include <carl/formula/Constraint.h>
#include <carl/formula/Formula.h>
#include <carl/interval/Interval.h>
#include <carl/interval/IntervalEvaluation.h>
#include <carl/interval/set_theory.h>
#include <carl/io/streamingOperators.h>
#include <carl/numbers/numbers.h>
#include <carl/util/SFINAE.h>
#include <carl/util/Singleton.h>
#include <carl/util/hash.h>
#include <carl/util/tuple_util.h>
#else

#include <carl-arith/constraint/IntervalEvaluation.h>
#include <carl-arith/core/Relation.h>
#include <carl-arith/core/Variable.h>
#include <carl-arith/core/VariablePool.h>
#include <carl-arith/interval/Interval.h>

#ifdef CARL_CAMEL_CASE_HEADERS
#include <carl-arith/interval/SetTheory.h>
#elif CARL_SNAKE_CASE_HEADERS
#include <carl-arith/interval/set_theory.h>
#endif

#include <carl-arith/numbers/numbers.h>
#include <carl-arith/poly/umvpoly/MultivariatePolynomial.h>
#include <carl-common/memory/Singleton.h>
#include <carl-common/meta/SFINAE.h>
#include <carl-common/util/hash.h>
#include <carl-common/util/streamingOperators.h>
#include <carl-common/util/tuple_util.h>
#include <carl-formula/arithmetic/Constraint.h>
#include <carl-formula/formula/Formula.h>
#include <carl-formula/formula/functions/Substitution.h>
// clang-format off
#include <carl-logging/logging.h>
#include <carl-logging/Logger.h>
#include <carl-logging/carl-logging.h>
// clang-format on
#endif

#endif    // HYPRO_ADAPTIONS_INCLUDES_H
