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
#include "carl/numbers/FLOAT_T.h"

typedef ::testing::Types<int, double, carl::FLOAT_T<double>, number > types;
typedef ::testing::Types<double, carl::FLOAT_T<double>, number > floatTypes;

// List tests which should be typed
// Datastructure
TYPED_TEST_CASE(PointTest, floatTypes);
TYPED_TEST_CASE(HybridAutomataTest, floatTypes);
TYPED_TEST_CASE(VertexContainerTest, floatTypes);
TYPED_TEST_CASE(VertexTest, floatTypes);

// Representations
TYPED_TEST_CASE(GridTest, floatTypes);
TYPED_TEST_CASE(BoxTest, types);
TYPED_TEST_CASE(OrthogonalPolyhedronTest, types);
TYPED_TEST_CASE(PolytopeTest, floatTypes);
TYPED_TEST_CASE(PolytopeUtilTest, floatTypes);
TYPED_TEST_CASE(PolytopeSupportFunctionTest, floatTypes);
TYPED_TEST_CASE(VPolytopeTest, floatTypes);
