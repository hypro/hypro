/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Testfile for parallel composition of hybrid automata.
 */

#include "../include/test/defines.h"

#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomatonComp.h>
#include <hypro/util/plotting/HybridAutomatonPlotter.h>

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

TYPED_TEST( HybridAutomataParallelCompositionTest, sharedVariables ) {
	using namespace hypro;
	auto ha1 = HybridAutomaton<TypeParam>();
	auto ha2 = HybridAutomaton<TypeParam>();
	ha1.setVariables( { "a" } );
	ha2.setVariables( { "a" } );

	auto* loc11 = ha1.createLocation( "l11" );
	auto* loc12 = ha1.createLocation( "l12" );
	auto* loc21 = ha2.createLocation( "l21" );
	auto* loc22 = ha2.createLocation( "l22" );
	auto* loc23 = ha2.createLocation( "l23" );
	// set initial states since otherwise the cleanup of the ||-operator removes all non-reachable locations
	ha1.addInitialState( loc11, conditionFromIntervals<TypeParam>( { carl::Interval<TypeParam>{ 1 } } ) );
	ha2.addInitialState( loc21, conditionFromIntervals<TypeParam>( { carl::Interval<TypeParam>{ 1 } } ) );

	matrix_t<TypeParam> flow1a = matrix_t<TypeParam>::Identity( 2, 2 );
	flow1a( 0, 0 ) = 1;
	matrix_t<TypeParam> flow2a = matrix_t<TypeParam>::Identity( 2, 2 );
	flow2a( 0, 0 ) = -1;

	loc11->setFlow( flow1a );
	loc12->setFlow( flow2a );

	// x <= 0
	matrix_t<TypeParam> invariant_constraints = matrix_t<TypeParam>::Zero( 1, 1 );
	vector_t<TypeParam> invariant_constants = vector_t<TypeParam>::Zero( 1 );
	invariant_constraints( 0, 0 ) = 1;
	invariant_constants << 0;
	loc11->setInvariant( { invariant_constraints, invariant_constants } );

	// x <= 1
	invariant_constraints = matrix_t<TypeParam>::Zero( 1, 1 );
	invariant_constants = vector_t<TypeParam>::Zero( 1 );
	invariant_constraints( 0, 0 ) = 1;
	invariant_constants << 1;
	loc21->setInvariant( { invariant_constraints, invariant_constants } );

	// 1 <= x <= 4
	invariant_constraints = matrix_t<TypeParam>::Zero( 2, 1 );
	invariant_constants = vector_t<TypeParam>::Zero( 2 );
	invariant_constraints( 0, 0 ) = 1;
	invariant_constraints( 1, 0 ) = -1;
	invariant_constants << 4, -1;
	loc22->setInvariant( { invariant_constraints, invariant_constants } );

	// x >= 4
	invariant_constraints = matrix_t<TypeParam>::Zero( 1, 1 );
	invariant_constants = vector_t<TypeParam>::Zero( 1 );
	invariant_constraints( 0, 0 ) = -1;
	invariant_constants << -4;
	loc23->setInvariant( { invariant_constraints, invariant_constants } );

	// create transitions
	auto* t1 = loc11->createTransition( loc12 );
	auto* t2 = loc12->createTransition( loc11 );
	auto* t3 = loc21->createTransition( loc22 );
	auto* t4 = loc22->createTransition( loc21 );
	auto* t5 = loc22->createTransition( loc23 );
	auto* t6 = loc23->createTransition( loc22 );

	matrix_t<TypeParam> guard_constraints = matrix_t<TypeParam>::Zero( 1, 1 );
	guard_constraints( 0, 0 ) = -5;
	vector_t<TypeParam> guard_constants = vector_t<TypeParam>::Zero( 1 );
	guard_constants << -1;
	t1->setGuard( { guard_constraints, guard_constants } );

	guard_constraints = matrix_t<TypeParam>::Zero( 1, 1 );
	guard_constraints( 0, 0 ) = 1;
	guard_constants = vector_t<TypeParam>::Zero( 1 );
	guard_constants << 0;
	t2->setGuard( { guard_constraints, guard_constants } );

	guard_constraints = matrix_t<TypeParam>::Zero( 2, 1 );
	guard_constraints( 0, 0 ) = 1;
	guard_constraints( 1, 0 ) = -1;
	guard_constants = vector_t<TypeParam>::Zero( 2 );
	guard_constants << 1, -1;
	t3->setGuard( { guard_constraints, guard_constants } );

	guard_constraints = matrix_t<TypeParam>::Zero( 2, 1 );
	guard_constraints( 0, 0 ) = 1;
	guard_constraints( 1, 0 ) = -1;
	guard_constants = vector_t<TypeParam>::Zero( 2 );
	guard_constants << 1, -1;
	t4->setGuard( { guard_constraints, guard_constants } );

	guard_constraints = matrix_t<TypeParam>::Zero( 2, 1 );
	guard_constraints( 0, 0 ) = 1;
	guard_constraints( 1, 0 ) = -1;
	guard_constants = vector_t<TypeParam>::Zero( 2 );
	guard_constants << 4, -4;
	t5->setGuard( { guard_constraints, guard_constants } );

	guard_constraints = matrix_t<TypeParam>::Zero( 2, 1 );
	guard_constraints( 0, 0 ) = 1;
	guard_constraints( 1, 0 ) = -1;
	guard_constants = vector_t<TypeParam>::Zero( 2 );
	guard_constants << -4, 4;
	t6->setGuard( { guard_constraints, guard_constants } );

	auto res = hypro::parallelCompose( ha1, ha2, { { "a", { loc11, loc12 } } } );

	EXPECT_EQ( 1, res.getVariables().size() );
	ASSERT_EQ( 6, res.getLocations().size() );
	// TODO Add more assertions
}

TYPED_TEST( HybridAutomataParallelCompositionTest, onTheFlyCompSingle ) {
	using namespace hypro;
	matrix_t<TypeParam> flow = matrix_t<TypeParam>::Identity( 2, 2 );
	flow( 1, 1 ) = 0;
	auto ha1 = HybridAutomaton<TypeParam>();
	ha1.setVariables( { "a" } );
	// locations
	auto* l1 = ha1.createLocation( "l1" );
	l1->setFlow( flow );
	auto* l2 = ha1.createLocation( "l2" );
	l2->setFlow( flow );
	auto* l3 = ha1.createLocation( "l3" );
	l3->setFlow( flow );
	// transitions
	auto* t12 = l1->createTransition( l2 );
	auto* t23 = l2->createTransition( l3 );
	auto* t31 = l3->createTransition( l1 );
	// initial configuration: l1, a = 1
	ha1.setInitialStates( { { l1, conditionFromIntervals( std::vector<carl::Interval<TypeParam>>{ carl::Interval<TypeParam>{ 1 } } ) } } );
	auto ha2 = ha1;	 // copy for later
	{				 // composition
		auto cmp = HybridAutomatonComp<TypeParam>();
		cmp.setLazy( true );
		cmp.addAutomaton( std::move( ha1 ) );
		EXPECT_EQ( 0, cmp.getLocations().size() );
		EXPECT_EQ( 1, cmp.getVariables().size() );
		// access to the initial location should affect the locations size
		auto initialStates = cmp.getInitialStates();
		EXPECT_EQ( 1, cmp.getLocations().size() );
		EXPECT_EQ( "l1", ( std::begin( initialStates )->first )->getName() );
		EXPECT_EQ( 1, cmp.getLocations().size() );
		EXPECT_EQ( 1, ( std::begin( initialStates )->first )->getTransitions().size() );
		// accessing some property, e.g. the name of the target location of the first transition should also add the target location to the location set
		const auto& name = cmp.getLocations().front()->getTransitions().front()->getTarget()->getName();
		EXPECT_EQ( 2, cmp.getLocations().size() );
	}
	{
		auto cmp = HybridAutomatonComp<TypeParam>();
		cmp.setLazy( false );
		cmp.addAutomaton( std::move( ha2 ) );
		EXPECT_EQ( 3, cmp.getLocations().size() );
		// access to the initial location should affect the locations size
		auto initialStates = cmp.getInitialStates();
		EXPECT_EQ( "l1", ( std::begin( initialStates )->first )->getName() );
		EXPECT_EQ( 1, ( std::begin( initialStates )->first )->getTransitions().size() );
		// accessing some property, e.g. the name of the target location of the first transition should also add the target location to the location set
		const auto& name = cmp.getLocations().front()->getTransitions().front()->getTarget()->getName();
		EXPECT_EQ( 3, cmp.getLocations().size() );
	}
}

TYPED_TEST( HybridAutomataParallelCompositionTest, onTheFlyCompTwoAutomata ) {
	using namespace hypro;
	matrix_t<TypeParam> flow = matrix_t<TypeParam>::Identity( 2, 2 );
	flow( 1, 1 ) = 0;
	auto ha1 = HybridAutomaton<TypeParam>();
	ha1.setVariables( { "a" } );
	// locations
	auto* l1 = ha1.createLocation( "l1" );
	l1->setFlow( flow );
	auto* l2 = ha1.createLocation( "l2" );
	l2->setFlow( flow );
	auto* l3 = ha1.createLocation( "l3" );
	l3->setFlow( flow );
	// transitions
	auto* t12 = l1->createTransition( l2 );
	t12->addLabel( Label{ "label" } );
	auto* t23 = l2->createTransition( l3 );
	auto* t31 = l3->createTransition( l1 );
	// initial configuration: l1, a = 1
	ha1.setInitialStates( { { l1, conditionFromIntervals( std::vector<carl::Interval<TypeParam>>{ carl::Interval<TypeParam>{ 1 } } ) } } );
	// second automaton
	auto ha2 = HybridAutomaton<TypeParam>();
	ha2.setVariables( { "b" } );
	// locations
	auto* l4 = ha2.createLocation( "l4" );
	l4->setFlow( flow );
	auto* l5 = ha2.createLocation( "l5" );
	l5->setFlow( flow );
	auto* l6 = ha2.createLocation( "l6" );
	l6->setFlow( flow );
	// transitions
	auto* t12_2 = l4->createTransition( l5 );
	auto* t23_2 = l5->createTransition( l6 );
	t23_2->addLabel( Label{ "label" } );
	auto* t31_2 = l6->createTransition( l4 );
	// initial configuration: l1, a = 1
	ha2.setInitialStates( { { l4, conditionFromIntervals( std::vector<carl::Interval<TypeParam>>{ carl::Interval<TypeParam>{ 1 } } ) } } );
	// composition
	auto cmp = HybridAutomatonComp<TypeParam>();
	cmp.setLazy( true );
	using Ltype = typename decltype( cmp )::LocationType;
	cmp.addAutomaton( std::move( ha1 ) );
	cmp.addAutomaton( std::move( ha2 ) );
	EXPECT_EQ( 0, cmp.getLocations().size() );
	EXPECT_EQ( 2, cmp.getVariables().size() );
	// access to the initial location should affect the locations size
	auto initialStates = cmp.getInitialStates();
	EXPECT_EQ( 1, cmp.getLocations().size() );
	EXPECT_EQ( "l1_l4", ( std::begin( initialStates )->first )->getName() );
	EXPECT_EQ( 1, cmp.getLocations().size() );
	auto* l14 = std::begin( initialStates )->first;
	ASSERT_EQ( 1, l14->getTransitions().size() );
	// move to next location
	const auto& transitions = l14->getTransitions();
	EXPECT_TRUE( transitions.size() == 1 );
	auto* l15 = l14->getTransitions().front()->getTarget();
	EXPECT_EQ( "l1_l5", l15->getName() );
	EXPECT_EQ( 2, cmp.getLocations().size() );
	ASSERT_EQ( 1, l15->getTransitions().size() );
	ASSERT_EQ( 1, l15->getTransitions().front()->getLabels().size() );
	EXPECT_EQ( Label( "label" ), l15->getTransitions().front()->getLabels().front() );
	//
	auto* l26 = l15->getTransitions().front()->getTarget();
	EXPECT_EQ( "l2_l6", l26->getName() );
	EXPECT_EQ( 3, cmp.getLocations().size() );
	ASSERT_EQ( 2, l26->getTransitions().size() );
	//
	auto* tmp = l26->getTransitions().front()->getTarget();
	Ltype* l24 = nullptr;
	Ltype* l36 = nullptr;
	if ( tmp->getName() == "l2_l4" ) {
		l24 = tmp;
		l36 = l26->getTransitions().back()->getTarget();
	} else {
		l24 = l26->getTransitions().back()->getTarget();
		l36 = tmp;
	}
	//
	EXPECT_EQ( "l2_l4", l24->getName() );
	EXPECT_EQ( 5, cmp.getLocations().size() );
	ASSERT_EQ( 2, l24->getTransitions().size() );
	//
	EXPECT_EQ( "l3_l6", l36->getName() );
	EXPECT_EQ( 7, cmp.getLocations().size() );
	ASSERT_EQ( 2, l36->getTransitions().size() );
	//
	Ltype* l25 = nullptr;
	Ltype* l34 = nullptr;
	tmp = l24->getTransitions().front()->getTarget();
	if ( tmp->getName() == "l2_l5" ) {
		l25 = tmp;
		l34 = l24->getTransitions().back()->getTarget();
	} else {
		l25 = l24->getTransitions().back()->getTarget();
		l34 = tmp;
	}
	//
	EXPECT_EQ( "l2_l5", l25->getName() );
	EXPECT_EQ( 8, cmp.getLocations().size() );
	ASSERT_EQ( 1, l25->getTransitions().size() );
	//
	EXPECT_EQ( "l3_l4", l34->getName() );
	EXPECT_EQ( 9, cmp.getLocations().size() );
	ASSERT_EQ( 2, l36->getTransitions().size() );
	//
	auto* l35 = l25->getTransitions().front()->getTarget();
	EXPECT_EQ( "l3_l5", l35->getName() );
	EXPECT_EQ( 9, cmp.getLocations().size() );
	ASSERT_EQ( 1, l35->getTransitions().size() );
	// l15 is already known, checking for comparison and also checking its properties should not affect the number of locations
	EXPECT_EQ( l15->getName(), l35->getTransitions().front()->getTarget()->getName() );
	EXPECT_EQ( 9, cmp.getLocations().size() );
	//
	tmp = l34->getTransitions().front()->getTarget();
	if ( tmp->getName() == "l3_l5" ) {
		EXPECT_EQ( "l1_l4", l34->getTransitions().back()->getTarget()->getName() );
	} else {
		EXPECT_EQ( "l3_l5", l34->getTransitions().back()->getTarget()->getName() );
		EXPECT_EQ( "l1_l4", l34->getTransitions().front()->getTarget()->getName() );
	}
	EXPECT_EQ( 9, cmp.getLocations().size() );
	//
	tmp = l36->getTransitions().front()->getTarget();
	Ltype* l16 = nullptr;
	if ( tmp->getName() == "l3_l4" ) {
		l16 = l36->getTransitions().back()->getTarget();
		EXPECT_EQ( l34->getName(), tmp->getName() );
	} else {
		l16 = tmp;
		EXPECT_EQ( l34->getName(), l36->getTransitions().back()->getTarget()->getName() );
	}
	//
	EXPECT_EQ( "l1_l6", l16->getName() );
	EXPECT_EQ( 9, cmp.getLocations().size() );
	ASSERT_EQ( 1, l16->getTransitions().size() );
	EXPECT_EQ( l14->getName(), l16->getTransitions().front()->getTarget()->getName() );
}

TYPED_TEST( HybridAutomataParallelCompositionTest, onTheFlyCompSharedVariables ) {
	using namespace hypro;
	matrix_t<TypeParam> flow2 = matrix_t<TypeParam>::Identity( 3, 3 );
	flow2( 2, 2 ) = 0;
	flow2( 0, 0 ) = 2;
	flow2( 0, 2 ) = 3;
	matrix_t<TypeParam> flow1 = matrix_t<TypeParam>::Identity( 2, 2 );
	flow1( 1, 1 ) = 0;
	auto ha1 = HybridAutomaton<TypeParam>();
	ha1.setVariables( { "a", "b" } );
	// locations
	auto* l1 = ha1.createLocation( "l1" );
	l1->setFlow( flow2 );
	auto* l2 = ha1.createLocation( "l2" );
	l2->setFlow( flow2 );
	// transitions
	auto* t12 = l1->createTransition( l2 );
	// guard a >= 0
	matrix_t<TypeParam> guardConstr = matrix_t<TypeParam>::Zero( 1, 2 );
	auto guardConst = vector_t<TypeParam>::Zero( 1 );
	guardConstr( 0, 0 ) = TypeParam( -1 );
	t12->setGuard( { guardConstr, guardConst } );
	auto* t23 = l2->createTransition( l1 );
	t23->addLabel( Label{ "label" } );
	// guard a <= 1
	matrix_t<TypeParam> guardConstr1 = matrix_t<TypeParam>::Zero( 1, 2 );
	vector_t<TypeParam> guardConst1 = vector_t<TypeParam>::Ones( 1 );
	guardConstr1( 0, 0 ) = 1;
	t23->setGuard( { guardConstr1, guardConst1 } );
	// reset a := 2
	matrix_t<TypeParam> resetMatrix = matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> resetVector = vector_t<TypeParam>::Zero( 2 );
	resetMatrix( 0, 0 ) = 0;
	resetVector( 0 ) = 2;
	t23->setReset( Reset( resetMatrix, resetVector ) );
	// initial configuration: l1, a = 1
	ha1.setInitialStates( { { l1, conditionFromIntervals( std::vector<carl::Interval<TypeParam>>{ carl::Interval<TypeParam>{ 1 }, carl::Interval<TypeParam>{ 1 } } ) } } );
	// second automaton
	auto ha2 = HybridAutomaton<TypeParam>();
	ha2.setVariables( { "b" } );
	// locations
	auto* l4 = ha2.createLocation( "l4" );
	l4->setFlow( flow1 );
	// transitions
	auto* t11 = l4->createTransition( l4 );
	t11->addLabel( Label{ "label" } );
	t11->setUrgent();
	// guard b >= 2
	matrix_t<TypeParam> guardConstr2 = matrix_t<TypeParam>::Zero( 1, 1 );
	vector_t<TypeParam> guardConst2 = vector_t<TypeParam>::Ones( 1 );
	guardConstr2( 0, 0 ) = -1;
	guardConst2( 0 ) = -2;
	t11->setGuard( { guardConstr2, guardConst2 } );
	// initial configuration: l1, a = 1
	ha2.setInitialStates( { { l4, conditionFromIntervals( std::vector<carl::Interval<TypeParam>>{ carl::Interval<TypeParam>{ 1 } } ) } } );
	// composition
	auto cmp = HybridAutomatonComp<TypeParam>();
	cmp.setLazy( true );
	using Ltype = typename decltype( cmp )::LocationType;
	cmp.addAutomaton( std::move( ha1 ) );
	cmp.addAutomaton( std::move( ha2 ) );
	//
	EXPECT_EQ( 2, cmp.getVariables().size() );
	auto expectedVariables = std::vector<std::string>{ "a", "b" };
	EXPECT_EQ( expectedVariables, cmp.getVariables() );
	EXPECT_EQ( 0, cmp.getLocations().size() );
	//
	auto initialStates = cmp.getInitialStates();
	EXPECT_EQ( 1, cmp.getLocations().size() );
	EXPECT_EQ( "l1_l4", initialStates.begin()->first->getName() );
	EXPECT_EQ( 1, cmp.getLocations().size() );
	EXPECT_EQ( flow2, cmp.getLocations().front()->getLinearFlow().getFlowMatrix() );
	ASSERT_EQ( 1, cmp.getLocations().front()->getTransitions().size() );
	auto* t1 = cmp.getLocations().front()->getTransitions().front().get();
	EXPECT_TRUE( t1->getLabels().empty() );
	EXPECT_FALSE( t1->isUrgent() );
	EXPECT_EQ( "l2_l4", t1->getTarget()->getName() );
	auto* loc2 = t1->getTarget();
	EXPECT_EQ( 2, cmp.getLocations().size() );
	ASSERT_EQ( 1, loc2->getTransitions().size() );
	auto* t2 = loc2->getTransitions().front().get();
	EXPECT_TRUE( t2->isUrgent() );
	auto expectedLabels = std::vector<Label>{ Label{ "label" } };
	EXPECT_EQ( expectedLabels, t2->getLabels() );
	matrix_t<TypeParam> guardConstr3 = matrix_t<TypeParam>::Zero( 2, 2 );
	vector_t<TypeParam> guardConst3 = vector_t<TypeParam>::Zero( 2 );
	guardConstr3( 0, 0 ) = 1;
	guardConst3( 0 ) = 1;
	guardConstr3( 1, 1 ) = -1;
	guardConst3( 1 ) = -2;
	auto expectedGuard = hypro::Condition<TypeParam>{ guardConstr3, guardConst3 };
	EXPECT_EQ( expectedGuard, t2->getGuard() );
	EXPECT_FALSE( t2->getReset().isIdentity() );
	EXPECT_TRUE( t2->getReset().isIdentity( 1 ) );
	EXPECT_EQ( 0, t2->getReset().getMatrix()( 0, 0 ) );
	EXPECT_EQ( 2, t2->getReset().getVector()( 0 ) );
}

TYPED_TEST( HybridAutomataParallelCompositionTest, onTheFlyCompMasterLocations ) {
	using namespace hypro;
	matrix_t<TypeParam> flow2 = matrix_t<TypeParam>::Identity( 3, 3 );
	flow2( 2, 2 ) = 0;
	flow2( 0, 0 ) = 2;
	flow2( 1, 1 ) = 2;
	flow2( 0, 2 ) = 3;
	matrix_t<TypeParam> flow1 = matrix_t<TypeParam>::Identity( 2, 2 );
	flow1( 1, 1 ) = 0;
	auto ha1 = HybridAutomaton<TypeParam>();
	ha1.setVariables( { "a", "b" } );
	// locations
	auto* l1 = ha1.createLocation( "l1" );
	l1->setFlow( flow2 );
	auto* l2 = ha1.createLocation( "l2" );
	l2->setFlow( flow2 );
	// transitions
	auto* t12 = l1->createTransition( l2 );
	auto* t23 = l2->createTransition( l1 );
	t23->addLabel( Label{ "label" } );
	// initial configuration: l1, a = 1
	ha1.setInitialStates( { { l1, conditionFromIntervals( std::vector<carl::Interval<TypeParam>>{ carl::Interval<TypeParam>{ 1 }, carl::Interval<TypeParam>{ 1 } } ) } } );
	// second automaton
	auto ha2 = HybridAutomaton<TypeParam>();
	ha2.setVariables( { "b" } );
	// locations
	auto* l4 = ha2.createLocation( "l4" );
	l4->setFlow( flow1 );
	// transitions
	auto* t11 = l4->createTransition( l4 );
	t11->addLabel( Label{ "label" } );
	// initial configuration: l1, a = 1
	ha2.setInitialStates( { { l4, conditionFromIntervals( std::vector<carl::Interval<TypeParam>>{ carl::Interval<TypeParam>{ 1 } } ) } } );
	// composition
	auto cmp = HybridAutomatonComp<TypeParam>();
	cmp.setLazy( true );
	using Ltype = typename decltype( cmp )::LocationType;
	cmp.addAutomaton( std::move( ha1 ) );
	cmp.addAutomaton( std::move( ha2 ) );
	// set master locations: l1 in component 0 should be master for b. Since l2 has the same flow, the composition should throw an exception once l2_l4 is created
	cmp.addMasterLocations( 0, { { "b", { 0 } } } );
	//
	EXPECT_EQ( 2, cmp.getVariables().size() );
	auto expectedVariables = std::vector<std::string>{ "a", "b" };
	EXPECT_EQ( expectedVariables, cmp.getVariables() );
	EXPECT_EQ( 0, cmp.getLocations().size() );
	//
	auto initialStates = cmp.getInitialStates();
	EXPECT_EQ( 1, cmp.getLocations().size() );
	EXPECT_EQ( "l1_l4", initialStates.begin()->first->getName() );
	EXPECT_EQ( 1, cmp.getLocations().size() );
	auto* loc = cmp.getLocations().front();
	EXPECT_EQ( flow2, loc->getLinearFlow().getFlowMatrix() );
	ASSERT_EQ( 1, initialStates.begin()->first->getTransitions().size() );
	//
	// EXPECT_THROW( initialStates.begin()->first->getTransitions().front()->getTarget()->getName(), std::logic_error );
	// add second master, things should work then
	cmp.addMasterLocations( 0, { { "b", { 1 } } } );
	//
	EXPECT_EQ( 0, cmp.getLocations().size() );
	//
	initialStates = cmp.getInitialStates();
	EXPECT_EQ( 1, cmp.getLocations().size() );
	EXPECT_EQ( "l1_l4", initialStates.begin()->first->getName() );
	EXPECT_EQ( 1, cmp.getLocations().size() );
	loc = cmp.getLocations().front();
	EXPECT_EQ( flow2, loc->getLinearFlow().getFlowMatrix() );
	ASSERT_EQ( 1, initialStates.begin()->first->getTransitions().size() );
	//
	EXPECT_NO_THROW( initialStates.begin()->first->getTransitions().front()->getTarget()->getName() );
}

TYPED_TEST( HybridAutomataParallelCompositionTest, onTheFlyCompLocationOnDemand ) {
	using namespace hypro;
	matrix_t<TypeParam> flow2 = matrix_t<TypeParam>::Identity( 3, 3 );
	matrix_t<TypeParam> flow1 = matrix_t<TypeParam>::Identity( 2, 2 );
	auto ha1 = HybridAutomaton<TypeParam>();
	ha1.setVariables( { "a", "b" } );
	// locations
	auto* l1 = ha1.createLocation( "l1" );
	l1->setFlow( flow2 );
	auto* l2 = ha1.createLocation( "l2" );
	l2->setFlow( flow2 );
	// transitions
	auto* t12 = l1->createTransition( l2 );
	auto* t23 = l2->createTransition( l1 );
	// initial configuration: l1, a = 1
	ha1.setInitialStates( { { l1, conditionFromIntervals( std::vector<carl::Interval<TypeParam>>{ carl::Interval<TypeParam>{ 1 }, carl::Interval<TypeParam>{ 1 } } ) } } );
	// second automaton
	auto ha2 = HybridAutomaton<TypeParam>();
	ha2.setVariables( { "b" } );
	// locations
	auto* l4 = ha2.createLocation( "l4" );
	l4->setFlow( flow1 );
	auto* l5 = ha2.createLocation( "l5" );
	l5->setFlow( flow1 );
	// transitions
	l4->createTransition( l5 );
	l5->createTransition( l4 );
	// initial configuration: l1, a = 1
	ha2.setInitialStates( { { l4, conditionFromIntervals( std::vector<carl::Interval<TypeParam>>{ carl::Interval<TypeParam>{ 1 } } ) } } );
	// composition
	auto cmp = HybridAutomatonComp<TypeParam>();
	cmp.setLazy( false );
	using Ltype = typename decltype( cmp )::LocationType;
	cmp.addAutomaton( std::move( ha1 ) );
	cmp.addAutomaton( std::move( ha2 ) );
	EXPECT_EQ( 2, cmp.getVariables().size() );
	auto expectedVariables = std::vector<std::string>{ "a", "b" };
	EXPECT_EQ( expectedVariables, cmp.getVariables() );
	// query location on demand by name
	auto undiscoveredLocation = cmp.getLocation( "l2_l5" );
	cmp.setLazy( true );
	matrix_t<TypeParam> expectedFlow = matrix_t<TypeParam>::Identity( 3, 3 );
	expectedFlow( 2, 2 ) = 0;
	EXPECT_EQ( expectedFlow, undiscoveredLocation->getLinearFlow().getFlowMatrix() );
	for ( const auto locationPtr : cmp.getLocations() ) {
		std::cout << "Location " << locationPtr->getName() << std::endl;
	}
	EXPECT_EQ( 3, cmp.getLocations().size() );
	//
	auto initialStates = cmp.getInitialStates();
	EXPECT_EQ( 4, cmp.getLocations().size() );
	EXPECT_EQ( "l1_l4", initialStates.begin()->first->getName() );
	EXPECT_EQ( 4, cmp.getLocations().size() );
	auto* loc = cmp.getLocations().front();
	EXPECT_EQ( expectedFlow, loc->getLinearFlow().getFlowMatrix() );
	//
}
