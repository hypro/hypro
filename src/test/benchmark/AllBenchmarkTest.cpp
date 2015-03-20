/**
 * Typed tests to run all representations with all operations in a benchmark.
 * @file AllBenchmarkTest.cpp
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since 	2015-03-20
 * @version 	2015-03-20
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "Benchmark.h"
 #include "../../src/lib/representations/Box/Box.h"
#include "../../src/lib/representations/Polytopes/VPolytope/VPolytope.h"


template<typename Number>
class Benchmark : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
	}
	
	virtual void TearDown()
	{
	}
};

TYPED_TEST(Benchmark, Box)
{
	hypro::BenchmarkSetup<TypeParam> setup;
	setup.size = 1000;
	setup.vertices = 3;
	setup.dimension = 8;
	setup.minValue = 0;
	setup.maxValue = 10;

	hypro::Benchmark<hypro::Box<TypeParam>, hypro::operation::LINEARTRAFO> linearTrafo(setup);
	hypro::Benchmark<hypro::Box<TypeParam>, hypro::operation::MINKOWSKISUM> minkowskiSum(setup);
	hypro::Benchmark<hypro::Box<TypeParam>, hypro::operation::INTERSECTION> intersection(setup);
	hypro::Benchmark<hypro::Box<TypeParam>, hypro::operation::CONTAINS> contains(setup);
	hypro::Benchmark<hypro::Box<TypeParam>, hypro::operation::UNION> unite(setup);
}

TYPED_TEST(Benchmark, VPolytope)
{
	hypro::BenchmarkSetup<TypeParam> setup;
	setup.size = 1000;
	setup.vertices = 3;
	setup.dimension = 8;
	setup.minValue = 0;
	setup.maxValue = 10;

	hypro::Benchmark<hypro::VPolytope<TypeParam>, hypro::operation::LINEARTRAFO> linearTrafo(setup);
	hypro::Benchmark<hypro::VPolytope<TypeParam>, hypro::operation::MINKOWSKISUM> minkowskiSum(setup);
	hypro::Benchmark<hypro::VPolytope<TypeParam>, hypro::operation::INTERSECTION> intersection(setup);
	hypro::Benchmark<hypro::VPolytope<TypeParam>, hypro::operation::CONTAINS> contains(setup);
	hypro::Benchmark<hypro::VPolytope<TypeParam>, hypro::operation::UNION> unite(setup);
}
