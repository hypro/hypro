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
#include "../../src/hypro/representations/GeometricObject.h"


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
/*
TYPED_TEST(Benchmark, Box)
{
	hypro::BenchmarkSetup<TypeParam> setup;
	setup.size = 1000;
	setup.vertices = 3;
	setup.dimension = 8;
	setup.minValue = 0;
	setup.maxValue = 10;

	hypro::Benchmark<hypro::Box<TypeParam>, TypeParam, hypro::operation::LINEARTRAFO> linearTrafo(setup);
	hypro::Benchmark<hypro::Box<TypeParam>, TypeParam, hypro::operation::MINKOWSKISUM> minkowskiSum(setup);
	hypro::Benchmark<hypro::Box<TypeParam>, TypeParam, hypro::operation::INTERSECTION> intersection(setup);
	hypro::Benchmark<hypro::Box<TypeParam>, TypeParam, hypro::operation::CONTAINS> contains(setup);
	hypro::Benchmark<hypro::Box<TypeParam>, TypeParam, hypro::operation::UNION> unite(setup);
}
*/

/*
 * Benchmark for intersection of a halfspace with a box.
 * Idea: For each box generated, generate random halfspaces one at a time and intersect each one of them with the box.
 * During this, stepwise increase the dimensionality.
 */
TYPED_TEST(Benchmark, BoxIntersectHalfspaces){

	hypro::BenchmarkSetup<TypeParam> setup;
	setup.size = 10000;		//Amount of benchmarks being generated
	setup.vertices = 2;		//The randomly generated vertices of the box according to minValue and maxValue
	setup.dimension = 2;	//Initial dimensionaliy
	setup.minValue = 0;		//Minimal coordinate value for each dimension
	setup.maxValue = 10;	//Maximal coordinate value for each dimension

	unsigned maxDim = 10;
	while(setup.dimension <= maxDim){
		hypro::Benchmark<hypro::Box<TypeParam>, TypeParam, hypro::operation::INTERSECTHALFSPACE> intersectHalfspace(setup);
		std::cout << "Repeat with slow boxes." << std::endl;
		auto gen = intersectHalfspace.getGenerator();
		auto gen2 = hypro::BenchmarkGenerator<hypro::BoxT<TypeParam,hypro::Converter<TypeParam>,hypro::BoxAllOff>, TypeParam, hypro::operation::INTERSECTHALFSPACE>(setup);
		gen2.setBenchmark(gen.convert<hypro::Box<TypeParam> >());
		hypro::Benchmark<hypro::BoxT<TypeParam,hypro::Converter<TypeParam>,hypro::BoxAllOff>, TypeParam, hypro::operation::INTERSECTHALFSPACE> intersectHalfspace2(setup,gen);
		setup.dimension++;
	}
}

/*
TYPED_TEST(Benchmark, VPolytope)
{
	hypro::BenchmarkSetup<TypeParam> setup;
	setup.size = 1000;
	setup.vertices = 3;
	setup.dimension = 8;
	setup.minValue = 0;
	setup.maxValue = 10;

	hypro::Benchmark<hypro::VPolytope<TypeParam>, TypeParam, hypro::operation::LINEARTRAFO> linearTrafo(setup);
	hypro::Benchmark<hypro::VPolytope<TypeParam>, TypeParam, hypro::operation::MINKOWSKISUM> minkowskiSum(setup);
	hypro::Benchmark<hypro::VPolytope<TypeParam>, TypeParam, hypro::operation::INTERSECTION> intersection(setup);
	hypro::Benchmark<hypro::VPolytope<TypeParam>, TypeParam, hypro::operation::CONTAINS> contains(setup);
	hypro::Benchmark<hypro::VPolytope<TypeParam>, TypeParam, hypro::operation::UNION> unite(setup);
}
*/
