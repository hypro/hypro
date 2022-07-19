/**
 * Testfile for parallel composition of hybrid automata.
 */

#include "../include/test/defines.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "util/plotting/HybridAutomatonPlotter.h"

#include "gtest/gtest.h"

using namespace hypro;
using namespace carl;

template <typename Number>
using valuation_t = VPolytope<Number>;

template <typename Number>
class HybridAutomataParallelCompositionTest : public ::testing::Test {
	/**
	 * Test Setup:
	 * Something
	 */
  protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};

/**
 * combine condition test, also overs combine for matrix_t
 */
TYPED_TEST( HybridAutomataParallelCompositionTest, combineCondition ) {
	using namespace hypro;

	std::vector<std::string> haVar;
	std::vector<std::string> lhsVar;
	std::vector<std::string> rhsVar;
	hypro::Condition<TypeParam> firstCondition;
	hypro::Condition<TypeParam> secondCondition;
	hypro::Condition<TypeParam> resultCondition;
	matrix_t<TypeParam> firstInvariant;
	vector_t<TypeParam> firstInvConsts;
	matrix_t<TypeParam> secondInvariant;
	vector_t<TypeParam> secondInvConsts;
	matrix_t<TypeParam> resultInvariant;
	vector_t<TypeParam> resultInvConsts;

	// no shared variables
	haVar = { "a", "b", "c", "d" };
	lhsVar = { "a", "c" };
	rhsVar = { "b", "d" };

	// two empty conditions
	EXPECT_EQ( hypro::Condition<TypeParam>(),
			   combine( hypro::Condition<TypeParam>(), hypro::Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// one empty condition
	firstInvariant = matrix_t<TypeParam>( 2, 2 );
	firstInvariant << 3, 1, 1, 2;
	firstInvConsts = vector_t<TypeParam>( 2 );
	firstInvConsts << 0, 1;
	firstCondition = hypro::Condition<TypeParam>( firstInvariant, firstInvConsts );

	resultInvariant = matrix_t<TypeParam>( 2, 4 );
	resultInvariant << 3, 0, 1, 0, 1, 0, 2, 0;
	resultInvConsts = vector_t<TypeParam>( 2 );
	resultInvConsts << 0, 1;
	resultCondition = hypro::Condition<TypeParam>( resultInvariant, resultInvConsts );
	EXPECT_EQ( resultCondition, combine( firstCondition, hypro::Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// no empty condition
	secondInvariant = matrix_t<TypeParam>( 2, 2 );
	secondInvariant << 1, 1, 1, 2;
	secondInvConsts = vector_t<TypeParam>( 2 );
	secondInvConsts << 0, 1;
	secondCondition = hypro::Condition<TypeParam>( secondInvariant, secondInvConsts );

	resultInvariant = matrix_t<TypeParam>( 4, 4 );
	resultInvariant << 3, 0, 1, 0, 1, 0, 2, 0, 0, 1, 0, 1, 0, 1, 0, 2;
	resultInvConsts = vector_t<TypeParam>( 4 );
	resultInvConsts << 0, 1, 0, 1;
	resultCondition = hypro::Condition<TypeParam>( resultInvariant, resultInvConsts );
	EXPECT_EQ( resultCondition, combine( firstCondition, secondCondition, haVar, lhsVar, rhsVar ) );

	// only shared variables
	haVar = { "a", "b" };
	lhsVar = { "a", "b" };
	rhsVar = { "a", "b" };

	// two empty conditions
	EXPECT_EQ( hypro::Condition<TypeParam>(),
			   combine( hypro::Condition<TypeParam>(), hypro::Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// one empty condition
	EXPECT_EQ( firstCondition, combine( firstCondition, hypro::Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// no empty condition
	resultInvariant = matrix_t<TypeParam>( 4, 2 );
	resultInvariant << 3, 1, 1, 2, 1, 1, 1, 2;
	resultInvConsts = vector_t<TypeParam>( 4 );
	resultInvConsts << 0, 1, 0, 1;
	resultCondition = hypro::Condition<TypeParam>( resultInvariant, resultInvConsts );
	EXPECT_EQ( resultCondition, combine( firstCondition, secondCondition, haVar, lhsVar, rhsVar ) );

	// shared and non shared variables
	haVar = { "a", "b", "c" };
	lhsVar = { "a", "b" };
	rhsVar = { "b", "c" };

	// two empty conditions
	EXPECT_EQ( hypro::Condition<TypeParam>(),
			   combine( hypro::Condition<TypeParam>(), hypro::Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// one empty condition
	resultInvariant = matrix_t<TypeParam>( 2, 3 );
	resultInvariant << 3, 1, 0, 1, 2, 0;
	resultInvConsts = vector_t<TypeParam>( 2 );
	resultInvConsts << 0, 1;
	resultCondition = hypro::Condition<TypeParam>( resultInvariant, resultInvConsts );
	EXPECT_EQ( resultCondition, combine( firstCondition, hypro::Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// no empty condition
	resultInvariant = matrix_t<TypeParam>( 4, 3 );
	resultInvariant << 3, 1, 0, 1, 2, 0, 0, 1, 1, 0, 1, 2;
	resultInvConsts = vector_t<TypeParam>( 4 );
	resultInvConsts << 0, 1, 0, 1;
	resultCondition = hypro::Condition<TypeParam>( resultInvariant, resultInvConsts );
	EXPECT_EQ( resultCondition, combine( firstCondition, secondCondition, haVar, lhsVar, rhsVar ) );
}

/**
 * combine reset test
 */
TYPED_TEST( HybridAutomataParallelCompositionTest, combineRest1 ) {
	std::vector<std::string> haVar;
	std::vector<std::string> lhsVar;
	std::vector<std::string> rhsVar;
	Reset<TypeParam> firstReset;
	Reset<TypeParam> secondReset;
	Reset<TypeParam> resultReset;
	matrix_t<TypeParam> firstMatrix;
	vector_t<TypeParam> firstConsts;
	matrix_t<TypeParam> secondMatrix;
	vector_t<TypeParam> secondConst;
	matrix_t<TypeParam> resultMatrix;
	vector_t<TypeParam> resultConsts;

	// no shared variables
	haVar = { "a", "b", "c", "d" };
	lhsVar = { "a", "c" };
	rhsVar = { "b", "d" };

	// two empty resets
	// EXPECT_EQ(Reset<TypeParam>(), combine(Reset<TypeParam>(), Reset<TypeParam>(), haVar, lhsVar, rhsVar));

	// two non-empty resets
	firstMatrix = matrix_t<TypeParam>( 2, 2 );
	firstMatrix << 1, 2, 3, 4;
	firstConsts = vector_t<TypeParam>( 2 );
	firstConsts << 5, 6;
	secondMatrix = matrix_t<TypeParam>( 2, 2 );
	secondMatrix << 3, 1, 4, 2;
	secondConst = vector_t<TypeParam>( 2 );
	secondConst << 6, 7;
	resultMatrix = matrix_t<TypeParam>( 4, 4 );
	resultMatrix << 1, 0, 2, 0, 0, 3, 0, 1, 3, 0, 4, 0, 0, 4, 0, 2;
	resultConsts = vector_t<TypeParam>( 4 );
	resultConsts << 5, 6, 6, 7;
	EXPECT_EQ( Reset<TypeParam>( resultMatrix, resultConsts ),
			   combine( Reset<TypeParam>( firstMatrix, firstConsts ), Reset<TypeParam>( secondMatrix, secondConst ),
						haVar, lhsVar, rhsVar ) );
}

TYPED_TEST( HybridAutomataParallelCompositionTest, combineRest2 ) {
	std::vector<std::string> haVar;
	std::vector<std::string> lhsVar;
	std::vector<std::string> rhsVar;
	Reset<TypeParam> firstReset;
	Reset<TypeParam> secondReset;
	Reset<TypeParam> resultReset;
	matrix_t<TypeParam> firstMatrix;
	vector_t<TypeParam> firstConsts;
	matrix_t<TypeParam> secondMatrix;
	vector_t<TypeParam> secondConst;
	matrix_t<TypeParam> resultMatrix;
	vector_t<TypeParam> resultConsts;

	// shared and non-shared variables
	haVar = { "a", "b", "c" };
	lhsVar = { "a", "b" };
	rhsVar = { "b", "c" };

	// same reset for shared variable
	firstMatrix = matrix_t<TypeParam>( 2, 2 );
	firstMatrix << 1, 0, 0, 2;
	firstConsts = vector_t<TypeParam>( 2 );
	firstConsts << 3, 4;
	secondMatrix = matrix_t<TypeParam>( 2, 2 );
	secondMatrix << 2, 0, 0, 3;
	secondConst = vector_t<TypeParam>( 2 );
	secondConst << 4, 5;
	resultMatrix = matrix_t<TypeParam>( 3, 3 );
	resultMatrix << 1, 0, 0, 0, 2, 0, 0, 0, 3;
	resultConsts = vector_t<TypeParam>( 3 );
	resultConsts << 3, 4, 5;
	EXPECT_EQ( Reset<TypeParam>( resultMatrix, resultConsts ),
			   combine( Reset<TypeParam>( firstMatrix, firstConsts ), Reset<TypeParam>( secondMatrix, secondConst ),
						haVar, lhsVar, rhsVar ) );
}

TYPED_TEST( HybridAutomataParallelCompositionTest, labelledTransitions ) {
	using namespace hypro;
	auto ha1 = HybridAutomaton<TypeParam>();
	auto ha2 = HybridAutomaton<TypeParam>();
	ha1.setVariables( { "a", "b" } );
	ha2.setVariables( { "c" } );

	auto* loc11 = ha1.createLocation( "l11" );
	auto* loc12 = ha1.createLocation( "l12" );
	auto* loc21 = ha2.createLocation( "l21" );
	// set initial states since otherwise the cleanup of the ||-operator removes all non-reachable locations
	ha1.addInitialState( loc11, conditionFromIntervals<TypeParam>( { carl::Interval<TypeParam>{ 0, 1 }, carl::Interval<TypeParam>{ 0, 1 } } ) );
	ha2.addInitialState( loc21, conditionFromIntervals<TypeParam>( { carl::Interval<TypeParam>{ 0, 1 } } ) );
	// flow is not interesting, use identity flow for all variables here
	matrix_t<TypeParam> flow1 = matrix_t<TypeParam>::Identity( 3, 3 );
	flow1( 2, 2 ) = 0;
	matrix_t<TypeParam> flow2 = matrix_t<TypeParam>::Identity( 2, 2 );
	flow2( 1, 1 ) = 0;
	loc11->setFlow( flow1 );
	loc12->setFlow( flow1 );
	loc21->setFlow( flow2 );
	// create transitions, one self-loop and one transition from l11 to l12 in the first component, a synchronizing self-loop in the second component
	auto* t1 = loc11->createTransition( loc11 );
	auto* t2 = loc11->createTransition( loc12 );
	auto* t3 = loc21->createTransition( loc21 );

	t2->setLabels( { Label{ "label1" } } );
	t3->setLabels( { Label{ "label1" } } );

	auto res = ha1 || ha2;

	hypro::plotting::plot( ha1, "ha1" );
	hypro::plotting::plot( ha2, "ha2" );
	hypro::plotting::plot( res, "res" );

	EXPECT_EQ( 3, res.getVariables().size() );
	ASSERT_EQ( 2, res.getLocations().size() );
	std::vector<Label> expectedLabels{ Label( "label1" ) };
	EXPECT_EQ( 2, res.getLocations().front()->getTransitions().size() );
	EXPECT_EQ( 0, res.getLocations().back()->getTransitions().size() );

	EXPECT_TRUE( std::any_of( std::begin( res.getLocations().front()->getTransitions() ), std::end( res.getLocations().front()->getTransitions() ), [&]( auto& t ) { return t.get()->getLabels() == expectedLabels; } ) );
}

TYPED_TEST( HybridAutomataParallelCompositionTest, sharedVariablesAndlabelledTransitions ) {
	using namespace hypro;
	auto ha1 = HybridAutomaton<TypeParam>();
	auto ha2 = HybridAutomaton<TypeParam>();
	ha1.setVariables( { "a", "b" } );
	ha2.setVariables( { "a" } );

	auto* loc11 = ha1.createLocation( "l11" );
	auto* loc12 = ha1.createLocation( "l12" );
	auto* loc21 = ha2.createLocation( "l21" );
	auto* loc22 = ha2.createLocation( "l22" );
	// set initial states since otherwise the cleanup of the ||-operator removes all non-reachable locations
	ha1.addInitialState( loc11, conditionFromIntervals<TypeParam>( { carl::Interval<TypeParam>{ 1 }, carl::Interval<TypeParam>{ 0, 1 } } ) );
	ha2.addInitialState( loc21, conditionFromIntervals<TypeParam>( { carl::Interval<TypeParam>{ 1 } } ) );
	// flow is not interesting, use identity flow for all variables here
	matrix_t<TypeParam> flow1a = matrix_t<TypeParam>::Identity( 3, 3 );
	flow1a( 0, 0 ) = 1;
	matrix_t<TypeParam> flow2a = matrix_t<TypeParam>::Identity( 3, 3 );
	flow2a( 0, 0 ) = -1;
	matrix_t<TypeParam> flow1b = matrix_t<TypeParam>::Identity( 2, 2 );
	flow1a( 0, 0 ) = 1;
	matrix_t<TypeParam> flow2b = matrix_t<TypeParam>::Identity( 2, 2 );
	flow2a( 0, 0 ) = -1;
	loc11->setFlow( flow1a );
	loc12->setFlow( flow2a );
	loc21->setFlow( flow1b );
	loc22->setFlow( flow2b );
	// create transitions, one self-loop and one transition from l11 to l12 in the first component, a synchronizing self-loop in the second component
	auto* t1 = loc11->createTransition( loc12 );
	auto* t2 = loc12->createTransition( loc11 );
	auto* t3 = loc21->createTransition( loc22 );
	auto* t4 = loc22->createTransition( loc21 );

	t1->setLabels( { Label{ "label1" } } );
	t3->setLabels( { Label{ "label1" } } );
	t2->setLabels( { Label{ "label2" } } );
	t4->setLabels( { Label{ "label2" } } );

	auto res = hypro::parallelCompose( ha1, ha2, { { "a", { loc11, loc12 } }, { "b", { loc11, loc12 } } } );

	hypro::plotting::plot( ha1, "ha1" );
	hypro::plotting::plot( ha2, "ha2" );
	hypro::plotting::plot( res, "res" );

	EXPECT_EQ( 2, res.getVariables().size() );
	ASSERT_EQ( 2, res.getLocations().size() );
	EXPECT_EQ( 1, res.getLocations().front()->getTransitions().size() );
	EXPECT_EQ( 1, res.getLocations().back()->getTransitions().size() );

	EXPECT_TRUE( std::any_of( std::begin( res.getLocations().front()->getTransitions() ), std::end( res.getLocations().front()->getTransitions() ), [&]( auto& t ) { return t.get()->getLabels() == std::vector<Label>{ Label( "label1" ) }; } ) );
	EXPECT_TRUE( std::any_of( std::begin( res.getLocations().back()->getTransitions() ), std::end( res.getLocations().back()->getTransitions() ), [&]( auto& t ) { return t.get()->getLabels() == std::vector<Label>{ Label( "label2" ) }; } ) );
	EXPECT_TRUE( std::none_of( std::begin( res.getLocations().front()->getTransitions() ), std::end( res.getLocations().front()->getTransitions() ), [&]( auto& t ) { return t.get()->getLabels() == std::vector<Label>{ Label( "label1" ), Label( "label2" ) }; } ) );
	EXPECT_TRUE( std::none_of( std::begin( res.getLocations().front()->getTransitions() ), std::end( res.getLocations().front()->getTransitions() ), [&]( auto& t ) { return t.get()->getLabels() == std::vector<Label>{}; } ) );
	EXPECT_TRUE( std::none_of( std::begin( res.getLocations().back()->getTransitions() ), std::end( res.getLocations().back()->getTransitions() ), [&]( auto& t ) { return t.get()->getLabels() == std::vector<Label>{ Label( "label1" ), Label( "label2" ) }; } ) );
	EXPECT_TRUE( std::none_of( std::begin( res.getLocations().back()->getTransitions() ), std::end( res.getLocations().back()->getTransitions() ), [&]( auto& t ) { return t.get()->getLabels() == std::vector<Label>{}; } ) );
}