/**
 * @file    SamplingHeuristicsTest.h
 *
 * @covers  SamplingHeuristics
 *
 * @author  Lyudmila Vatskicheva
 *
 */

#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/Location.h>
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/src	 //hypro/util/sampling/sampling.h>

using namespace hypro;

template <typename Number>
class SamplingHeuristicsTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		// box
		std::vector<carl::Interval<Number>> boundaries;
		boundaries.push_back( carl::Interval<Number>( 2, 5 ) );
		boundaries.push_back( carl::Interval<Number>( 1, 3 ) );
		box = hypro::Box<Number>( boundaries );

		// smpl
		smpl = hypro::SimulationSample<Number>( { 2, 5 } );
	}

	virtual void TearDown() {}

	hypro::Box<Number> box;
	hypro::SimulationSample<Number> smpl;
};

TYPED_TEST( SamplingHeuristicsTest, Set ) {
	std::vector<carl::Interval<TypeParam>> boundaries;
	boundaries.push_back( carl::Interval<TypeParam>( 2, 4 ) );
	boundaries.push_back( carl::Interval<TypeParam>( 1, 3 ) );
	hypro::Box<TypeParam> box = hypro::Box<TypeParam>( boundaries );

	hypro::State_t<TypeParam> stateSet;
	hypro::Location<TypeParam>* dummyLoc;
	stateSet.setLocation( dummyLoc );
	stateSet.setSet( box );

	std::vector<hypro::SimulationSample<TypeParam>> vecCenter =
		  sample<hypro::Box<TypeParam>, TypeParam, CENTER>( std::get<hypro::Box<TypeParam>>( stateSet.getSet() ) );
	EXPECT_EQ( std::vector<hypro::SimulationSample<TypeParam>>( { SimulationSample<TypeParam>( { 3, 2 } ) } ),
			   vecCenter );

	std::vector<hypro::SimulationSample<TypeParam>> vecVert =
		  sample<hypro::Box<TypeParam>, TypeParam, VERTICES>( std::get<hypro::Box<TypeParam>>( stateSet.getSet() ) );
	EXPECT_EQ( std::vector<hypro::SimulationSample<TypeParam>>(
					 { SimulationSample<TypeParam>( { 2, 1 } ), SimulationSample<TypeParam>( { 4, 1 } ),
					   SimulationSample<TypeParam>( { 2, 3 } ), SimulationSample<TypeParam>( { 4, 3 } ) } ),
			   vecVert );

	// std::vector< hypro::SimulationSample<TypeParam> > vecRand = sample<hypro::Box<TypeParam>, TypeParam,
	// RANDOM_SET_K>(std::get<hypro::Box<TypeParam>>(stateSet.getSet()),10); EXPECT_EQ( 10, vecRand.size());
}

// cannot test, constraintSet::vertices not implemented!
// TYPED_TEST(SamplingHeuristicsTest, ConstraintSet)
// {
//     matrix_t<TypeParam> matrix = matrix_t<TypeParam>(4,2);
// 	vector_t<TypeParam> vector = vector_t<TypeParam>(4);
// 	matrix << -1, 0,
//     1, 0,
//     0, -1,
//     0, 1;
// 	vector << -2, 4, -1, 3;
// 	ConstraintSet<TypeParam> consSet = ConstraintSet<TypeParam>(matrix, vector);

//     hypro::State_t<TypeParam> stateSet;
//     hypro::Location<TypeParam>* dummyLoc;
//     stateSet.setLocation(dummyLoc);
//     stateSet.setSet(consSet);

//     std::vector< hypro::SimulationSample<TypeParam> > vecCenter = sampleSet<TypeParam, CENTER>(stateSet);
// 	EXPECT_EQ( std::vector< hypro::SimulationSample<TypeParam> > ({SimulationSample<TypeParam>({3,2})}), vecCenter);

//     std::vector< hypro::SimulationSample<TypeParam> > vecVert = sampleSet<TypeParam, VERTICES>(stateSet);
// 	EXPECT_EQ( std::vector< hypro::SimulationSample<TypeParam> > ({SimulationSample<TypeParam>({2,1}),
// SimulationSample<TypeParam>({4,1}), SimulationSample<TypeParam>({2,3}), SimulationSample<TypeParam>({4,3})}),
// vecVert);
// }

TYPED_TEST( SamplingHeuristicsTest, Interval ) {
	// construct interval
	carl::Interval<mpq_class> boundaries = carl::Interval<mpq_class>( 2, 10 );
	EXPECT_EQ( boundaries.sample(), 6 );

	// sample interval using BORDERS heuristic
	std::vector<mpq_class> intervalBorders = sample<mpq_class, BORDERS>( boundaries );
	std::vector<mpq_class> resultBorders;
	mpq_class lower = { 2 };
	mpq_class upper = { 10 };
	resultBorders.emplace_back( lower );
	resultBorders.emplace_back( upper );
	EXPECT_EQ( resultBorders, intervalBorders );

	// sample interval using UNIFORM_K heuristic
	std::vector<mpq_class> uniformSamples = sample<mpq_class, UNIFORM_K>( boundaries, 3 );
	std::vector<mpq_class> resultUniform;
	mpq_class upper1 = { 4 };
	mpq_class upper2 = { 6 };
	mpq_class upper3 = { 8 };
	resultUniform.emplace_back( upper1 );
	resultUniform.emplace_back( upper2 );
	resultUniform.emplace_back( upper3 );
	EXPECT_EQ( resultUniform, uniformSamples );

	// sample interval using RANDOM_INTV_K heuristic
	std::vector<mpq_class> randomSamples = sample<mpq_class, RANDOM_INTV_K>( boundaries, 4 );
	EXPECT_EQ( 4, randomSamples.size() );
}
