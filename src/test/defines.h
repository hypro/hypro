/**
 * Defines the datatypes for the tests.
 * @author Benedikt Seidl
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @version 2015-02-01
 * @since	2013-09-01
 */

#pragma once

#include "../hypro/config.h"
#include "../hypro/util/types.h"

typedef ::testing::Types<
	#ifdef USE_MPFR_FLOAT
	carl::FLOAT_T<mpfr_t>,
	#endif
	double,
	carl::FLOAT_T<double>
> floatTypes;

typedef ::testing::Types<
	#ifdef USE_CLN_NUMBERS
	cln::cl_RA,
	#endif
	mpq_class,
	double
	//carl::FLOAT_T<double>,
	//carl::FLOAT_T<mpq_class>
> allTypes;

typedef ::testing::Types<
	carl::FLOAT_T<mpq_class>
> rationalTypesMPQ;
// List tests which should be typed

// Algorithm
TYPED_TEST_CASE(BoxReachabilityTest, allTypes);
TYPED_TEST_CASE(VertexEnumerationTest, allTypes);

// Benchmark
TYPED_TEST_CASE(Benchmark, allTypes);

// Datastructure
TYPED_TEST_CASE(HalfspaceTest, allTypes);
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
TYPED_TEST_CASE(TaylorModelTest, floatTypes); // problem in carl/src/carl/interval/Interval.h:641:19
TYPED_TEST_CASE(VPolytopeTest, allTypes);
TYPED_TEST_CASE(ZonotopeTest, allTypes); // problem in carl/src/carl/numbers/adaption_float/FLOAT_T.h:791:37

// Practical term
TYPED_TEST_CASE(PTermBoxTest, allTypes);
TYPED_TEST_CASE(PTermPolytopeTest, allTypes);
