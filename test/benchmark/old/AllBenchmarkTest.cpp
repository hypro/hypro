/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Typed tests to run all representations with all operations in a benchmark.
 * @file AllBenchmarkTest.cpp
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since 	2015-03-20
 * @version 	2015-03-20
 */

#include "../../src/hypro/representations/GeometricObjectBase.h"
#include "../defines.h"
#include "Benchmark.h"
#include "Timer.h"
#include "gtest/gtest.h"
#include <random>

template <typename Number>
class Benchmark : public ::testing::Test {
  protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
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
/*
TYPED_TEST(Benchmark, BoxIntersectHalfspaces){

	hypro::BenchmarkSetup<TypeParam> setup;
	setup.size = 10000;		//Amount of benchmarks being generated
	setup.vertices = 2;		//The randomly generated vertices of the box according to minValue and maxValue
	setup.dimension = 2;	//Initial dimensionaliy
	setup.minValue = 0;		//Minimal coordinate value for each dimension
	setup.maxValue = 10;	//Maximal coordinate value for each dimension

	unsigned maxDim = 10;
	while(setup.dimension <= maxDim){
		hypro::Benchmark<hypro::Box<TypeParam>, TypeParam, hypro::operation::INTERSECTHALFSPACE>
intersectHalfspace(setup); std::cout << "Repeat with slow boxes." << std::endl; auto gen =
intersectHalfspace.getGenerator(); auto gen2 =
hypro::BenchmarkGenerator<hypro::BoxT<TypeParam,hypro::Converter<TypeParam>,hypro::BoxAllOff>, TypeParam,
hypro::operation::INTERSECTHALFSPACE>(setup); gen2.setBenchmark(gen.convert<hypro::Box<TypeParam> >());
		hypro::Benchmark<hypro::BoxT<TypeParam,hypro::Converter<TypeParam>,hypro::BoxAllOff>, TypeParam,
hypro::operation::INTERSECTHALFSPACE> intersectHalfspace2(setup,gen); setup.dimension++;
	}
}
*/
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

TYPED_TEST( Benchmark, BoxSampleSupport ) {
	std::size_t maxDimension = 200;
	std::size_t samples = 1000;
	std::vector<std::vector<hypro::vector_t<TypeParam>>> directions;

	std::random_device rd;	   // Will be used to obtain a seed for the random number engine
	std::mt19937 gen( rd() );  // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis( 0.0, 1.0 );

	// for each dimension
	hypro::Timer generatorTimer;
	for ( std::size_t d = 1; d <= maxDimension; ++d ) {
		directions.push_back( std::vector<hypro::vector_t<TypeParam>>() );
		// create all sample directions
		for ( std::size_t i = 0; i < samples; ++i ) {
			hypro::vector_t<TypeParam> sample = hypro::vector_t<TypeParam>( d );
			for ( Eigen::Index r = 0; r < d; ++r ) {
				sample( r ) = dis( gen );
			}
			directions[d - 1].push_back( sample );
		}
	}
	double generationTime = generatorTimer.elapsed();

	std::cout << "Created " << maxDimension * samples << " samples in " << generationTime << " ms." << std::endl;

	// actual benchmark.
	hypro::Box<TypeParam> box;
	for ( std::size_t d = 1; d <= maxDimension; ++d ) {
		std::cout << "Benchmark dimension " << d << std::endl;
		box.insert( carl::Interval<TypeParam>( -1, 1 ) );
		assert( box.dimension() == d );

		hypro::Timer bmTimer;
		for ( auto sIt = directions[d - 1].begin(); sIt != directions[d - 1].end(); ++sIt ) {
			box.evaluate( *sIt );
		}
		double rt = bmTimer.elapsed();
		std::cout << "Took " << rt << " ms." << std::endl;
	}
}
