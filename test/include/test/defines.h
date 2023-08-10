/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Defines the datatypes for the tests.
 * @author Benedikt Seidl
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 */

#pragma once

#include "util.h"

#include "gtest/gtest.h"
#include <hypro/config.h>
#include <hypro/paths.h>
#include <hypro/representations/GeometricObjectBase.h>

typedef ::testing::Types<
#ifdef USE_MPFR_FLOAT
        carl::FLOAT_T<mpfr_t>,
#endif
        double
        // carl::FLOAT_T<double>
>
        floatTypes;

typedef ::testing::Types<
#ifdef USE_CLN_NUMBERS
        cln::cl_RA,
#endif
        mpq_class, double
        // carl::FLOAT_T<double>,
        // carl::FLOAT_T<mpq_class>
>
        allTypes;

typedef ::testing::Types<
#ifdef USE_CLN_NUMBERS
        cln::cl_RA,
#endif
        mpq_class>
        rationalTypes;

typedef ::testing::Types<
#ifdef HYPRO_USE_PPL
        hypro::Polytope<mpq_class>,
#endif
        hypro::VPolytope<mpq_class>, hypro::HPolytope<mpq_class>, hypro::CarlPolytope<mpq_class>>
        polyhedralTypes;

typedef ::testing::Types<hypro::Box<double>, hypro::Box<mpq_class>> boxTypes;
// List tests which should be typed

// Algorithm
TYPED_TEST_SUITE(TemplatePolyhedronContextTest, floatTypes);
TYPED_TEST_SUITE(FirstSegmentHandlersTest, floatTypes);
TYPED_TEST_SUITE(BoxReachabilityTest, allTypes);
TYPED_TEST_SUITE(VertexEnumerationTest, allTypes);
TYPED_TEST_SUITE(QuickhullTest, allTypes);
TYPED_TEST_SUITE(QuickIntersectionTest, allTypes);
TYPED_TEST_SUITE(RectangularReachabilityTest, polyhedralTypes);
TYPED_TEST_SUITE(UrgencyCEGARReachabilityTest, boxTypes);

// Benchmark
TYPED_TEST_SUITE(Benchmark, allTypes);

// Core
TYPED_TEST_SUITE(EigenAdaptionsTest, allTypes);
TYPED_TEST_SUITE(OptimizerTest, allTypes);
TYPED_TEST_SUITE(AntlrParserTest, allTypes);
// TYPED_TEST_SUITE(AntlrParserCIFTest, allTypes);

// Datastructure
TYPED_TEST_SUITE(HalfspaceTest, allTypes);
TYPED_TEST_SUITE(PointTest, rationalTypes);
TYPED_TEST_SUITE(HybridAutomataTest, allTypes);
TYPED_TEST_SUITE(VertexContainerTest, allTypes);
TYPED_TEST_SUITE(VertexTest, allTypes);
TYPED_TEST_SUITE(HybridAutomataParallelCompositionTest, allTypes);

// Representations
TYPED_TEST_SUITE(BoxTest, allTypes);
TYPED_TEST_SUITE(CarlPolytopeTest, rationalTypes);
TYPED_TEST_SUITE(ConverterTest, allTypes);
TYPED_TEST_SUITE(GridTest, allTypes);
TYPED_TEST_SUITE(HPolytopeTest, allTypes);
TYPED_TEST_SUITE(OrthogonalPolyhedronTest, allTypes);
TYPED_TEST_SUITE(PolytopeTest, floatTypes);
TYPED_TEST_SUITE(PolytopeUtilTest, allTypes);
TYPED_TEST_SUITE(PolytopeSupportFunctionTest, allTypes);
TYPED_TEST_SUITE(SupportFunctionTest, allTypes);
// TYPED_TEST_SUITE(TaylorModelTest, floatTypes); // problem in carl/src/carl/interval/Interval.h:641:19
TYPED_TEST_SUITE(VPolytopeTest, allTypes);
TYPED_TEST_SUITE(VPolytopeUtilTest, allTypes);
TYPED_TEST_SUITE(StarsetTest, allTypes);

TYPED_TEST_SUITE(ZonotopeTest, allTypes);     // problem in carl/src/carl/numbers/adaption_float/FLOAT_T.h:791:37
TYPED_TEST_SUITE(DifferenceBoundsTest, allTypes);
TYPED_TEST_SUITE(SupportFunctionNewTest, allTypes);
TYPED_TEST_SUITE(TemplatePolyhedronTest, allTypes);
// TYPED_TEST_SUITE(OrthoplexTest, allTypes);

// Practical term
// TYPED_TEST_SUITE(PTermBoxTest, allTypes);
// TYPED_TEST_SUITE(PTermPolytopeTest, allTypes);
