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
#include "carl/numbers/numbers.h"


typedef ::testing::Types<
	int,
	double,
	#ifdef USE_MPFR_FLOAT
	carl::FLOAT_T<mpfr_t>,
	#endif
	carl::FLOAT_T<double>
> types;

typedef ::testing::Types<
	double,
	#ifdef USE_MPFR_FLOAT
	carl::FLOAT_T<mpfr_t>,
	#endif
	carl::FLOAT_T<double>
> floatTypes;

typedef ::testing::Types<
	double,
	carl::FLOAT_T<double>,
	#ifdef USE_MPFR_FLOAT
	carl::FLOAT_T<mpfr_t>,
	#endif
	#ifdef USE_CLN_NUMBERS
	carl::FLOAT_T<cln::cl_RA>,
	#endif
	carl::FLOAT_T<mpq_class>
> allTypes;

// List tests which should be typed

// Benchmark
TYPED_TEST_CASE(Benchmark, floatTypes);

// Datastructure
TYPED_TEST_CASE(HyperplaneTest, floatTypes);
TYPED_TEST_CASE(PointTest, floatTypes);
TYPED_TEST_CASE(HybridAutomataTest, floatTypes);
TYPED_TEST_CASE(VertexContainerTest, floatTypes);
TYPED_TEST_CASE(VertexTest, floatTypes);

// Representations
TYPED_TEST_CASE(BoxTest, floatTypes);
TYPED_TEST_CASE(ConverterTest, floatTypes);
TYPED_TEST_CASE(GridTest, floatTypes);
TYPED_TEST_CASE(HPolytopeTest, floatTypes);
TYPED_TEST_CASE(OrthogonalPolyhedronTest, types);
TYPED_TEST_CASE(PolytopeTest, floatTypes);
TYPED_TEST_CASE(PolytopeUtilTest, floatTypes);
TYPED_TEST_CASE(PolytopeSupportFunctionTest, floatTypes);
TYPED_TEST_CASE(SupportFunctionTest, floatTypes);
TYPED_TEST_CASE(TaylorModelTest, floatTypes);
TYPED_TEST_CASE(VPolytopeTest, floatTypes);
TYPED_TEST_CASE(ZonotopeTest, floatTypes);
