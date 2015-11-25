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
<<<<<<< HEAD
TYPED_TEST_CASE(BoxReachabilityTest, allTypes);
TYPED_TEST_CASE(VertexEnumerationTest, rationalTypesMPQ);
=======
TYPED_TEST_CASE(BoxReachabilityTest, floatTypes);
TYPED_TEST_CASE(VertexEnumerationTest, rationalTypes);
>>>>>>> b7f1312fcaf30227f29d0595e39307897614c91c

// Benchmark
TYPED_TEST_CASE(Benchmark, allTypes);

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
TYPED_TEST_CASE(TaylorModelTest, allTypes); // problem in carl/src/carl/interval/Interval.h:641:19
TYPED_TEST_CASE(VPolytopeTest, allTypes);
TYPED_TEST_CASE(ZonotopeTest, floatTypes); // problem in carl/src/carl/numbers/adaption_float/FLOAT_T.h:791:37

// Practical term
TYPED_TEST_CASE(PTermBoxTest, allTypes);
TYPED_TEST_CASE(PTermPolytopeTest, allTypes);
