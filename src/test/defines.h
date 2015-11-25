/**
 * Defines the datatypes for the tests.
 * @author Benedikt Seidl
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @version 2014-12-18
 * @since	2013-09-01
 */

#pragma once

#include "../lib/config.h"
#include "../lib/util/types.h"
//#include "carl/numbers/numbers.h"


typedef ::testing::Types<
	int,
	double,
	#ifdef USE_MPFR_FLOAT
	carl::FLOAT_T<mpfr_t>,
	#endif
	carl::FLOAT_T<double>
> types;

typedef ::testing::Types<
	#ifdef USE_MPFR_FLOAT
	carl::FLOAT_T<mpfr_t>,
	#endif
	double,
	carl::FLOAT_T<double>
> floatTypes;

typedef ::testing::Types<
	#ifdef USE_MPFR_FLOAT
	carl::FLOAT_T<mpfr_t>,
	#endif
	double,
	carl::FLOAT_T<double>,
	#ifdef USE_CLN_NUMBERS
	carl::FLOAT_T<cln::cl_RA>,
	#endif
	carl::FLOAT_T<mpq_class>
> allTypes;

typedef ::testing::Types<
	#ifdef USE_CLN_NUMBERS
	carl::FLOAT_T<cln::cl_RA>,
	#endif
	carl::FLOAT_T<mpq_class>
> rationalTypes;

typedef ::testing::Types<
	carl::FLOAT_T<mpq_class>
> rationalTypesMPQ;
// List tests which should be typed

// Algorithm
TYPED_TEST_CASE(BoxReachabilityTest, floatTypes);
TYPED_TEST_CASE(VertexEnumerationTest, rationalTypes);

// Benchmark
TYPED_TEST_CASE(Benchmark, floatTypes);

// Datastructure
TYPED_TEST_CASE(HyperplaneTest, allTypes);
TYPED_TEST_CASE(PointTest, allTypes);
TYPED_TEST_CASE(HybridAutomataTest, allTypes);
TYPED_TEST_CASE(VertexContainerTest, allTypes);
TYPED_TEST_CASE(VertexTest, allTypes);

// Representations
TYPED_TEST_CASE(BoxTest, allTypes);
TYPED_TEST_CASE(ConverterTest, allTypes);
TYPED_TEST_CASE(GridTest, allTypes);
TYPED_TEST_CASE(HPolytopeTest, allTypes);
TYPED_TEST_CASE(OrthogonalPolyhedronTest, allTypes);
TYPED_TEST_CASE(PolytopeTest, allTypes);
TYPED_TEST_CASE(PolytopeUtilTest, allTypes);
TYPED_TEST_CASE(PolytopeSupportFunctionTest, allTypes);
TYPED_TEST_CASE(SupportFunctionTest, allTypes);
TYPED_TEST_CASE(TaylorModelTest, floatTypes);
TYPED_TEST_CASE(VPolytopeTest, floatTypes);
TYPED_TEST_CASE(ZonotopeTest, floatTypes);

// Practical term
TYPED_TEST_CASE(PTermBoxTest, floatTypes);
TYPED_TEST_CASE(PTermPolytopeTest, floatTypes);
