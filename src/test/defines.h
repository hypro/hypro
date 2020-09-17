/**
 * Defines the datatypes for the tests.
 * @author Benedikt Seidl
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @version 2015-02-01
 * @since	2013-09-01
 */

#pragma once

#include "util.h"
#include "gtest/gtest.h"
#include <hypro/config.h>


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
// List tests which should be typed

// Algorithm
TYPED_TEST_CASE( TemplatePolyhedronContextTest, floatTypes );
TYPED_TEST_CASE( FirstSegmentHandlersTest, floatTypes );
TYPED_TEST_CASE( BoxReachabilityTest, allTypes );
TYPED_TEST_CASE( VertexEnumerationTest, allTypes );
TYPED_TEST_CASE( QuickhullTest, allTypes );
TYPED_TEST_CASE( QuickIntersectionTest, allTypes );

// Benchmark
TYPED_TEST_CASE( Benchmark, allTypes );

// Core
TYPED_TEST_CASE( EigenAdaptionsTest, allTypes );
TYPED_TEST_CASE( OptimizerTest, allTypes );
TYPED_TEST_CASE( AntlrParserTest, allTypes );
// TYPED_TEST_CASE(AntlrParserCIFTest, allTypes);

// Datastructure
TYPED_TEST_CASE( HalfspaceTest, allTypes );
TYPED_TEST_CASE( PointTest, rationalTypes );
TYPED_TEST_CASE( HybridAutomataTest, allTypes );
TYPED_TEST_CASE( VertexContainerTest, allTypes );
TYPED_TEST_CASE( VertexTest, allTypes );
TYPED_TEST_CASE( HybridAutomataParallelCompositionTest, allTypes );

// Representations
TYPED_TEST_CASE( BoxTest, allTypes );
TYPED_TEST_CASE( CarlPolytopeTest, rationalTypes );
TYPED_TEST_CASE( ConverterTest, allTypes );
TYPED_TEST_CASE( GridTest, allTypes );
TYPED_TEST_CASE( HPolytopeTest, allTypes );
TYPED_TEST_CASE( OrthogonalPolyhedronTest, allTypes );
TYPED_TEST_CASE( PolytopeTest, floatTypes );
TYPED_TEST_CASE( PolytopeUtilTest, allTypes );
TYPED_TEST_CASE( PolytopeSupportFunctionTest, allTypes );
TYPED_TEST_CASE( SupportFunctionTest, allTypes );
// TYPED_TEST_CASE(TaylorModelTest, floatTypes); // problem in carl/src/carl/interval/Interval.h:641:19
TYPED_TEST_CASE( VPolytopeTest, allTypes );
TYPED_TEST_CASE( ZonotopeTest, allTypes );	// problem in carl/src/carl/numbers/adaption_float/FLOAT_T.h:791:37
TYPED_TEST_CASE( DifferenceBoundsTest, allTypes );
TYPED_TEST_CASE( SupportFunctionNewTest, allTypes );
TYPED_TEST_CASE( TemplatePolyhedronTest, allTypes );
// TYPED_TEST_CASE(OrthoplexTest, allTypes);

// Practical term
// TYPED_TEST_CASE(PTermBoxTest, allTypes);
// TYPED_TEST_CASE(PTermPolytopeTest, allTypes);
