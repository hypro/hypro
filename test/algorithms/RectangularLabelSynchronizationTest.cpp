/*
 * Copyright (c) 2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/algorithms/automata/automataCreation.h"
#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/algorithms/reachability/analyzer/LabelSynchronization/RectangularSyncAnalyzer.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>

using Number = mpq_class;
using VPoly = hypro::VPolytope<Number>;
using Matrix = hypro::matrix_t<Number>;
using Interval = carl::Interval<Number>;
using Vector = hypro::vector_t<Number>;
using Point = hypro::Point<Number>;

template <typename Number>
class RectangularLabelSynchronizationTest : public testing::Test {
  protected:
	virtual void SetUp() {}
	virtual void TearDown() {}

  public:
};


/// Tests whether a point is contained in a flowpipe segment
template <typename Representation>
bool is_reachable_in( const hypro::Point<typename Representation::NumberType>& sample, const Representation& segment ) {
	return segment.contains( sample );
}

/// Tests whether a point is contained in a flowpipe
template <typename Representation>
bool is_reachable_in( const hypro::Point<typename Representation::NumberType>& sample,
					  const std::vector<Representation>& flowpipe ) {
	return std::any_of( flowpipe.begin(), flowpipe.end(),
						[&]( const auto& segment ) { return is_reachable_in( sample, segment ); } );
}


template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA1() {
	// One-dimensional reactangular automaton with one location and a loop
	hypro::HybridAutomaton<Number> res;

	// Create location
	auto loc = res.createLocation();

	// Set flow x' = [1,1]
	Interval flow{ 1, 1 };
	typename hypro::rectangularFlow<Number>::flowMap fMap;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flow;
	loc->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set invariant x <= 10
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 10;
	loc->setInvariant( { invariantConstraints, invariantConstants } );

	// Add loop transition in first location with no guard and no reset
	auto transition = loc->createTransition( loc );
    transition->addLabel( hypro::Label{"a"} );

	// Set initial state x = 0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 0, 0;

	// Create HA
	res.addInitialState( loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA2() {
	// One-dimensional reactangular automaton with one location and a loop
	hypro::HybridAutomaton<Number> res;

	// Create location
	auto loc = res.createLocation();

	// Set flow x' = [1,1]
	Interval flow{ 1, 1 };
	typename hypro::rectangularFlow<Number>::flowMap fMap;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flow;
	loc->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set invariant x <= 10
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 10;
	loc->setInvariant( { invariantConstraints, invariantConstants } );

	// Add loop transition in first location
	auto transition = loc->createTransition( loc );
    transition->addLabel( hypro::Label{"a"} );
    // add guard x in [3,5]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 5, -3;
    hypro::Condition<Number> guard(guardConstraints, guardConstants);

    // add reset function x' := 0
    // interval representation
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 0, 0 ) );
    hypro::Reset<Number> reset;
    reset.setIntervals( intervalReset );

    transition->setGuard( guard );
    transition->setReset( reset );

	// Set initial state x = [0,1], aff = 1
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 1, 0;

	// Create HA
	res.addInitialState( loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA3() {
	// One-dimensional reactangular automaton with one location and a loop
	hypro::HybridAutomaton<Number> res;

	// Create location
	auto loc = res.createLocation();

	// Set flow x' = [1,1]
	Interval flow{ 1, 1 };
	typename hypro::rectangularFlow<Number>::flowMap fMap;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flow;
	loc->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set invariant x <= 20
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 20;
	loc->setInvariant( { invariantConstraints, invariantConstants } );

	// Add loop transition in first location
	auto transition = loc->createTransition( loc );
    transition->addLabel( hypro::Label{"b"} );
    
    // add guard x in [14,16]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 16, -14;
    hypro::Condition<Number> guard(guardConstraints, guardConstants);

    // reset function x' := 10
    // interval representation
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 10, 10 ) );
    hypro::Reset<Number> reset;
    reset.setIntervals( intervalReset );

    transition->setGuard( guard );
    transition->setReset( reset );

	// Set initial state x = [10,11], aff = 1
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 11, -10;

	// Create HA
	res.addInitialState( loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA4() {
	// One-dimensional reactangular automaton with one location and a loop
	hypro::HybridAutomaton<Number> res;

	// Create location
	auto loc = res.createLocation();

	// Set flow x' = [1,1]
	Interval flow{ 1, 1 };
	typename hypro::rectangularFlow<Number>::flowMap fMap;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flow;
	loc->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set invariant x <= 20
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 20;
	loc->setInvariant( { invariantConstraints, invariantConstants } );

	// Add loop transition in first location
	auto transition = loc->createTransition( loc );
    transition->addLabel( hypro::Label{"a"} );
    
    // add guard x in [16,18]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 18, -16;
    hypro::Condition<Number> guard(guardConstraints, guardConstants);

    // reset function x' := 10
    // interval representation
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 10, 10 ) );
    hypro::Reset<Number> reset;
    reset.setIntervals( intervalReset );

    transition->setGuard( guard );
    transition->setReset( reset );

	// Set initial state x = [10,11], aff = 1
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 11, -10;

	// Create HA
	res.addInitialState( loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA5() {
	// One-dimensional reactangular automaton with one location and a loop
	hypro::HybridAutomaton<Number> res;

	// Create location
	auto loc = res.createLocation();

	// Set flow x' = [1,1]
	Interval flow{ 1, 1 };
	typename hypro::rectangularFlow<Number>::flowMap fMap;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flow;
	loc->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set invariant x <= 20
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 20;
	loc->setInvariant( { invariantConstraints, invariantConstants } );

	// Add loop transition in first location
	auto transition = loc->createTransition( loc );
    transition->addLabel( hypro::Label{"a"} );
    
    // add guard x in [16.3,18]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 18, -16.3;
    hypro::Condition<Number> guard(guardConstraints, guardConstants);

    // reset function x' := 10
    // interval representation
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 10, 10 ) );
    hypro::Reset<Number> reset;
    reset.setIntervals( intervalReset );

    transition->setGuard( guard );
    transition->setReset( reset );

	// Set initial state x = [10,11], aff = 1
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 11, -10;

	// Create HA
	res.addInitialState( loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA6() {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex(0);
	
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> oneDynamics;
    std::map<carl::Variable, carl::Interval<Number>> zeroDynamics;
    oneDynamics.emplace(std::make_pair(x, carl::Interval<Number>(1, 1)));
    zeroDynamics.emplace(std::make_pair(x, carl::Interval<Number>(0, 0)));

    // Create locations
	auto loc0 = res.createLocation("l00");
	auto loc1 = res.createLocation("l01");
	auto loc2 = res.createLocation("l02");
	auto loc3 = res.createLocation("l03");
	auto loc4 = res.createLocation("l04");
    
    hypro::rectangularFlow<Number> oneFlow(oneDynamics);
    hypro::rectangularFlow<Number> zeroFlow(zeroDynamics);

	loc0->setRectangularFlow(oneFlow);
	loc1->setRectangularFlow(oneFlow);
	loc2->setRectangularFlow(oneFlow);
	loc3->setRectangularFlow(zeroFlow);
	loc4->setRectangularFlow(zeroFlow);

	// Add transitions
    // loc0 -> loc1
	auto transition01 = loc0->createTransition( loc1 );
    transition01->addLabel( hypro::Label{"a"} );
    // guard x in [3,3]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 3, -3;
    hypro::Condition<Number> guard01(guardConstraints, guardConstants);
    transition01->setGuard( guard01 );
    // reset x' = 0
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 0, 0 ) );
    hypro::Reset<Number> reset01;
    reset01.setIntervals( intervalReset );
    transition01->setReset( reset01 );

    // loc0 -> loc2
	auto transition02 = loc0->createTransition( loc2 );
    transition02->addLabel( hypro::Label{"b"} );
    // guard x in [3,3]
    hypro::matrix_t<Number> guardConstraints02 = hypro::matrix_t<Number>(2, 1);
    guardConstraints02 << 1, -1;
    hypro::vector_t<Number> guardConstants02 = hypro::vector_t<Number>(2);
    guardConstants02 << 3, -3;
    hypro::Condition<Number> guard02(guardConstraints02, guardConstants02);
    transition02->setGuard( guard02 );
    // reset x' = 5
    std::vector<carl::Interval<Number>> intervalReset02;
    intervalReset02.emplace_back( carl::Interval<Number>( 5, 5 ) );
    hypro::Reset<Number> reset02;
    reset02.setIntervals( intervalReset02 );
    transition02->setReset( reset02 );

    // loc1 -> loc3
	auto transition13 = loc1->createTransition( loc3 );
    transition13->addLabel( hypro::Label{"d"} );
    // guard x in [1,1]
    hypro::matrix_t<Number> guardConstraints13 = hypro::matrix_t<Number>(2, 1);
    guardConstraints13 << 1, -1;
    hypro::vector_t<Number> guardConstants13 = hypro::vector_t<Number>(2);
    guardConstants13 << 1, -1;
    hypro::Condition<Number> guard13(guardConstraints13, guardConstants13);
    transition13->setGuard( guard13 );
    // reset x' = -1
    std::vector<carl::Interval<Number>> intervalReset13;
    intervalReset13.emplace_back( carl::Interval<Number>( -1, -1 ) );
    hypro::Reset<Number> reset13;
    reset13.setIntervals( intervalReset13 );
    transition13->setReset( reset13 );

    // loc2 -> loc4
	auto transition24 = loc2->createTransition( loc4 );
    transition24->addLabel( hypro::Label{"d"} );
    // guard x in [6,6]
    hypro::matrix_t<Number> guardConstraints24 = hypro::matrix_t<Number>(2, 1);
    guardConstraints24 << 1, -1;
    hypro::vector_t<Number> guardConstants24 = hypro::vector_t<Number>(2);
    guardConstants24 << 6, -6;
    hypro::Condition<Number> guard24(guardConstraints24, guardConstants24);
    transition24->setGuard( guard24 );
    // reset x' = 4
    std::vector<carl::Interval<Number>> intervalReset24;
    intervalReset24.emplace_back( carl::Interval<Number>( 4, 4 ) );
    hypro::Reset<Number> reset24;
    reset24.setIntervals( intervalReset24 );
    transition24->setReset( reset24 );


	// Set initial state x = [0,1]
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 1, -0;

	// Create HA
	res.addInitialState( loc0, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA7() {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable y = hypro::VariablePool::getInstance().carlVarByIndex(0);
	
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> oneDynamics;
    std::map<carl::Variable, carl::Interval<Number>> zeroDynamics;
    oneDynamics.emplace(std::make_pair(y, carl::Interval<Number>(1, 1)));
    zeroDynamics.emplace(std::make_pair(y, carl::Interval<Number>(0, 0)));
    // Flows
    hypro::rectangularFlow<Number> oneFlow(oneDynamics);
    hypro::rectangularFlow<Number> zeroFlow(zeroDynamics);
    
    // Create locations
	auto loc0 = res.createLocation("l10");
	auto loc1 = res.createLocation("l11");
	auto loc2 = res.createLocation("l12");    

	loc0->setRectangularFlow(oneFlow);
	loc1->setRectangularFlow(oneFlow);
	loc2->setRectangularFlow(zeroFlow);

    // transitions
    // loc0 -> loc1
	auto transition01 = loc0->createTransition( loc1 );
    transition01->addLabel( hypro::Label{"a"} );
    // guard y in [3,3]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 3, -3;
    hypro::Condition<Number> guard01(guardConstraints, guardConstants);
    transition01->setGuard( guard01 );
    // reset y' = 0
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 0, 0 ) );
    hypro::Reset<Number> reset01;
    reset01.setIntervals( intervalReset );
    transition01->setReset( reset01 );

    // loc1 -> loc2
	auto transition12 = loc1->createTransition( loc2 );
    transition12->addLabel( hypro::Label{"c"} );
    // guard y in [0,0]
    hypro::matrix_t<Number> guardConstraints12 = hypro::matrix_t<Number>(2, 1);
    guardConstraints12 << 1, -1;
    hypro::vector_t<Number> guardConstants12 = hypro::vector_t<Number>(2);
    guardConstants12 << 0, -0;
    hypro::Condition<Number> guard12(guardConstraints12, guardConstants12);
    transition12->setGuard( guard12 );
    // reset y' = 6
    std::vector<carl::Interval<Number>> intervalReset12;
    intervalReset12.emplace_back( carl::Interval<Number>( 6, 6 ) );
    hypro::Reset<Number> reset12;
    reset12.setIntervals( intervalReset12 );
    transition12->setReset( reset12 );


	// Set initial state y = [0,1]
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 1, -0;

	// Create HA
	res.addInitialState( loc0, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA8() {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable z = hypro::VariablePool::getInstance().carlVarByIndex(0);
	
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> oneDynamics;
    std::map<carl::Variable, carl::Interval<Number>> zeroDynamics;
    oneDynamics.emplace(std::make_pair(z, carl::Interval<Number>(1, 1)));
    zeroDynamics.emplace(std::make_pair(z, carl::Interval<Number>(0, 0)));
    // Flows
    hypro::rectangularFlow<Number> oneFlow(oneDynamics);
    hypro::rectangularFlow<Number> zeroFlow(zeroDynamics);
    
    // Create locations
	auto loc0 = res.createLocation("l20");
	auto loc1 = res.createLocation("l21");
	auto loc2 = res.createLocation("l22");    

	loc0->setRectangularFlow(oneFlow);
	loc1->setRectangularFlow(oneFlow);
	loc2->setRectangularFlow(zeroFlow);

    // transitions
    // loc0 -> loc1
	auto transition01 = loc0->createTransition( loc1 );
    transition01->addLabel( hypro::Label{"c"} );
    // guard z in [3,3]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 3, -3;
    hypro::Condition<Number> guard01(guardConstraints, guardConstants);
    transition01->setGuard( guard01 );
    // reset z' = 1
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 1, 1 ) );
    hypro::Reset<Number> reset01;
    reset01.setIntervals( intervalReset );
    transition01->setReset( reset01 );

    // loc1 -> loc2
	auto transition12 = loc1->createTransition( loc2 );
    transition12->addLabel( hypro::Label{"d"} );
    // guard z in [2,2]
    hypro::matrix_t<Number> guardConstraints12 = hypro::matrix_t<Number>(2, 1);
    guardConstraints12 << 1, -1;
    hypro::vector_t<Number> guardConstants12 = hypro::vector_t<Number>(2);
    guardConstants12 << 2, -2;
    hypro::Condition<Number> guard12(guardConstraints12, guardConstants12);
    transition12->setGuard( guard12 );
    // reset z' = 4
    std::vector<carl::Interval<Number>> intervalReset12;
    intervalReset12.emplace_back( carl::Interval<Number>( 4, 4 ) );
    hypro::Reset<Number> reset12;
    reset12.setIntervals( intervalReset12 );
    transition12->setReset( reset12 );


	// Set initial state z = [0,1]
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 1, -0;

	// Create HA
	res.addInitialState( loc0, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA9() {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex(0);
	
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> oneDynamics;
    oneDynamics.emplace(std::make_pair(x, carl::Interval<Number>(1, 1)));

    // Create locations
	auto loc0 = res.createLocation("l00");
	auto loc1 = res.createLocation("l01");
    
    hypro::rectangularFlow<Number> oneFlow(oneDynamics);

	loc0->setRectangularFlow(oneFlow);
	loc1->setRectangularFlow(oneFlow);

	// Add transitions
    // loc0 -> loc1
	auto transition01 = loc0->createTransition( loc1 );
    transition01->addLabel( hypro::Label{"a"} );
    // guard x in [2,3]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 3, -2;
    hypro::Condition<Number> guard01(guardConstraints, guardConstants);
    transition01->setGuard( guard01 );
    // reset x' = 4
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 4, 4 ) );
    hypro::Reset<Number> reset01;
    reset01.setIntervals( intervalReset );
    transition01->setReset( reset01 );

	// Set initial state x = [0,1]
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 1, -0;

	// Create HA
	res.addInitialState( loc0, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA10() {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable y = hypro::VariablePool::getInstance().carlVarByIndex(0);
	
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> oneDynamics;
    oneDynamics.emplace(std::make_pair(y, carl::Interval<Number>(1, 1)));
    // Flows
    hypro::rectangularFlow<Number> oneFlow(oneDynamics);
    
    // Create locations
	auto loc0 = res.createLocation("l10");
	auto loc1 = res.createLocation("l11");

	loc0->setRectangularFlow(oneFlow);
	loc1->setRectangularFlow(oneFlow);

    // transitions
    // loc0 -> loc1
	auto transition01 = loc0->createTransition( loc1 );
    transition01->addLabel( hypro::Label{"a"} );
    // guard y in [2,3]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 3, -2;
    hypro::Condition<Number> guard01(guardConstraints, guardConstants);
    transition01->setGuard( guard01 );
    // reset y' = 5
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 5, 5 ) );
    hypro::Reset<Number> reset01;
    reset01.setIntervals( intervalReset );
    transition01->setReset( reset01 );

	// Set initial state y = [0,1]
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 1, -0;

	// Create HA
	res.addInitialState( loc0, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA11() {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable z = hypro::VariablePool::getInstance().carlVarByIndex(0);
	
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> oneDynamics;
    oneDynamics.emplace(std::make_pair(z, carl::Interval<Number>(1, 1)));
    // Flows
    hypro::rectangularFlow<Number> oneFlow(oneDynamics);
    
    // Create locations
	auto loc0 = res.createLocation("l20");
	auto loc1 = res.createLocation("l21");
	auto loc2 = res.createLocation("l22");    

	loc0->setRectangularFlow(oneFlow);
	loc1->setRectangularFlow(oneFlow);
	loc2->setRectangularFlow(oneFlow);

    // transitions
    // loc0 -> loc1
	auto transition01 = loc0->createTransition( loc1 );
    transition01->addLabel( hypro::Label{"a"} );
    // guard z in [1,2]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 2, -1;
    hypro::Condition<Number> guard01(guardConstraints, guardConstants);
    transition01->setGuard( guard01 );
    // reset z' = 0
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 0, 0 ) );
    hypro::Reset<Number> reset01;
    reset01.setIntervals( intervalReset );
    transition01->setReset( reset01 );

    // loc0 -> loc2
	auto transition02 = loc0->createTransition( loc2 );
    transition02->addLabel( hypro::Label{"a"} );
    // guard z in [2,3]
    hypro::matrix_t<Number> guardConstraints12 = hypro::matrix_t<Number>(2, 1);
    guardConstraints12 << 1, -1;
    hypro::vector_t<Number> guardConstants12 = hypro::vector_t<Number>(2);
    guardConstants12 << 3, -2;
    hypro::Condition<Number> guard12(guardConstraints12, guardConstants12);
    transition02->setGuard( guard12 );
    // reset z' = 5
    std::vector<carl::Interval<Number>> intervalReset12;
    intervalReset12.emplace_back( carl::Interval<Number>( 5, 5 ) );
    hypro::Reset<Number> reset12;
    reset12.setIntervals( intervalReset12 );
    transition02->setReset( reset12 );


	// Set initial state z = [0,1]
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 1, -0;

	// Create HA
	res.addInitialState( loc0, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

TYPED_TEST( RectangularLabelSynchronizationTest, AnalyzerConstruction ) {
	
	// create first automaton with variable pool 0
    auto automaton1 = createRectangularHA1<typename TypeParam::NumberType>();
	automaton1.addTimeVariable();
	// create second automaton with variable pool 1
	hypro::VariablePool::getInstance().changeToPool(1);
    auto automaton2 = createRectangularHA1<typename TypeParam::NumberType>();
	automaton2.addTimeVariable();
	// change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

    std::vector<hypro::HybridAutomaton<typename TypeParam::NumberType>> automata{ automaton1, automaton2 };

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::NO_AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_v;

	hypro::Settings settings{ {},
							  hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
							  { analysisParameters } };

    auto analyzer = hypro::RectangularSyncAnalyzer<TypeParam, hypro::HybridAutomaton<typename TypeParam::NumberType>>( automata, settings );

	// clear variable pool
	hypro::VariablePool::getInstance().changeToPool(0);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(1);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(0);

	SUCCEED();
}

TYPED_TEST ( RectangularLabelSynchronizationTest, AnalyzerRun ) {
    
	// create first automaton with variable pool 0
    auto automaton1 = createRectangularHA1<typename TypeParam::NumberType>();
	automaton1.addTimeVariable();
	// create second automaton with variable pool 1
	hypro::VariablePool::getInstance().changeToPool(1);
    auto automaton2 = createRectangularHA1<typename TypeParam::NumberType>();
	automaton2.addTimeVariable();
	// change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

	std::vector<hypro::HybridAutomaton<typename TypeParam::NumberType>> automata{ automaton1, automaton2 };

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::NO_AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_v;

    hypro::Settings settings{ {},
                              hypro::FixedAnalysisParameters{ 5, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) },
                              { analysisParameters } };

    auto analyzer = hypro::RectangularSyncAnalyzer<TypeParam, hypro::HybridAutomaton<typename TypeParam::NumberType>>( automata, settings );

    auto result = analyzer.run();
	
	// clear variable pool
	hypro::VariablePool::getInstance().changeToPool(0);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(1);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(0);
    
	ASSERT_EQ( result, hypro::REACHABILITY_RESULT::SAFE );
}

TYPED_TEST (RectangularLabelSynchronizationTest, TwoAutomataNoSync ) {
	
	// create first automaton with variable pool 0
    auto automaton1 = createRectangularHA2<typename TypeParam::NumberType>();
	automaton1.addTimeVariable();
	// create second automaton with variable pool 1
	hypro::VariablePool::getInstance().changeToPool(1);
    auto automaton2 = createRectangularHA3<typename TypeParam::NumberType>();
	automaton2.addTimeVariable();
	// change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

	std::vector<hypro::HybridAutomaton<typename TypeParam::NumberType>> automata{ automaton1, automaton2 };

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::NO_AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_v;

    hypro::Settings settings{ {},
                              hypro::FixedAnalysisParameters{ 1, hypro::tNumber( 9 ), hypro::tNumber( 0.01 ) },
                              { analysisParameters } };

    auto analyzer = hypro::RectangularSyncAnalyzer<TypeParam, hypro::HybridAutomaton<typename TypeParam::NumberType>>( automata, settings );

    auto result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );

	// validate computed flowpipes for automaton 1
	std::vector<TypeParam> flowpipes1;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[0]).begin(), analyzer.getReachTreeForAutomaton(automata[0]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes1.insert( flowpipes1.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 2 ), flowpipes1.size() );
	EXPECT_TRUE( is_reachable_in( Point{ 0, 0 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 1, 0 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 10, 9 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 9, 9 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 0, 2 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 0, 5 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 9, 11 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 9, 14 }, flowpipes1 ) );

	EXPECT_FALSE( is_reachable_in( Point{ -0.1, 0 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 1.1, 0 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10.1, 9 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10, 9.1 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10, 9.1 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10.1, 9 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 0, 1.9 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 0, 5.1 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 9.1, 11 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 9, 14.1 }, flowpipes1 ) );

	// validate computed flowpipes for automaton 2
	std::vector<TypeParam> flowpipes2;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[1]).begin(), analyzer.getReachTreeForAutomaton(automata[1]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes2.insert( flowpipes2.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 2 ), flowpipes2.size() );
	EXPECT_TRUE( is_reachable_in( Point{ 10, 0 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 11, 0 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 20, 9 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 19, 9 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 10, 3 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 10, 6 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 19, 12 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 19, 15 }, flowpipes2 ) );

	EXPECT_FALSE( is_reachable_in( Point{ 9.9, 0 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 11.1, 0 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 20.1, 9 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 19.5, 9.1 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10, 2.9 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10, 6.1 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 19.1, 12 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 19, 15.1 }, flowpipes2 ) );

	// clear variable pool
	hypro::VariablePool::getInstance().changeToPool(0);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(1);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(0);
}

TYPED_TEST( RectangularLabelSynchronizationTest, TwoAutomataWithSync ) {
	
	// create first automaton with variable pool 0
    auto automaton1 = createRectangularHA2<typename TypeParam::NumberType>();
	automaton1.addTimeVariable();
	// create second automaton with variable pool 1
	hypro::VariablePool::getInstance().changeToPool(1);
    auto automaton2 = createRectangularHA3<typename TypeParam::NumberType>();
	for ( auto& trs : automaton2.getTransitions() ) {
		trs->setLabels( std::vector<hypro::Label>{hypro::Label{"a"}} );
	}
	automaton2.addTimeVariable();
	// change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

	std::vector<hypro::HybridAutomaton<typename TypeParam::NumberType>> automata{ automaton1, automaton2 };

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::NO_AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_v;

    hypro::Settings settings{ {},
                              hypro::FixedAnalysisParameters{ 1, hypro::tNumber( 9 ), hypro::tNumber( 0.01 ) },
                              { analysisParameters } };

    auto analyzer = hypro::RectangularSyncAnalyzer<TypeParam, hypro::HybridAutomaton<typename TypeParam::NumberType>>( automata, settings );

    auto result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );

	// validate computed flowpipes for automaton 1
	std::vector<TypeParam> flowpipes1;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[0]).begin(), analyzer.getReachTreeForAutomaton(automata[0]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes1.insert( flowpipes1.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 2 ), flowpipes1.size() );
	EXPECT_TRUE( is_reachable_in( Point{ 0, 0 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 1, 0 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 10, 9 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 9, 9 }, flowpipes1 ) );	
	EXPECT_TRUE( is_reachable_in( Point{ 0, 3 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 0, 5 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 9, 12 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 9, 14 }, flowpipes1 ) );

	EXPECT_FALSE( is_reachable_in( Point{ 9, 11 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 0, 2 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 5, 7.5 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ -0.1, 0 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 1.1, 0 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10.1, 9 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10, 9.1 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10, 9.1 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10.1, 9 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 0, 1.9 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 0, 5.1 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 9.1, 11 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 9, 14.1 }, flowpipes1 ) );

	// validate computed flowpipes for automaton 2
	std::vector<TypeParam> flowpipes2;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[1]).begin(), analyzer.getReachTreeForAutomaton(automata[1]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes2.insert( flowpipes2.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 2 ), flowpipes2.size() );
	EXPECT_TRUE( is_reachable_in( Point{ 10, 0 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 11, 0 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 20, 9 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 19, 9 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 10, 3 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 10, 5 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 19, 12 }, flowpipes2 ) );
	EXPECT_TRUE( is_reachable_in( Point{ 19, 14 }, flowpipes2 ) );

	EXPECT_FALSE( is_reachable_in( Point{ 19, 14.1 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10, 5.1 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 9.9, 0 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 11.1, 0 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 20.1, 9 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 19.5, 9.1 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 10, 2.9 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 19.1, 12 }, flowpipes2 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 14, 9.5 }, flowpipes2 ) );
	
	// clear variable pool
	hypro::VariablePool::getInstance().changeToPool(0);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(1);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(0);
}

TYPED_TEST ( RectangularLabelSynchronizationTest, TwoAutomataTimeGuardIntersectionEmpty ) {
	// create first automaton with variable pool 0
    auto automaton1 = createRectangularHA2<typename TypeParam::NumberType>();
	automaton1.addTimeVariable();
	// create second automaton with variable pool 1
	hypro::VariablePool::getInstance().changeToPool(1);
    auto automaton2 = createRectangularHA4<typename TypeParam::NumberType>();
	automaton2.addTimeVariable();
	// change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

	std::vector<hypro::HybridAutomaton<typename TypeParam::NumberType>> automata{ automaton1, automaton2 };

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::NO_AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_v;

    hypro::Settings settings{ {},
                              hypro::FixedAnalysisParameters{ 2, hypro::tNumber( 9 ), hypro::tNumber( 0.01 ) },
                              { analysisParameters } };

    auto analyzer = hypro::RectangularSyncAnalyzer<TypeParam, hypro::HybridAutomaton<typename TypeParam::NumberType>>( automata, settings );

    auto result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );

	// validate computed flowpipes for automaton 1
	std::vector<TypeParam> flowpipes1;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[0]).begin(), analyzer.getReachTreeForAutomaton(automata[0]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes1.insert( flowpipes1.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 2 ), flowpipes1.size() );

	// validate computed flowpipes for automaton 2
	std::vector<TypeParam> flowpipes2;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[1]).begin(), analyzer.getReachTreeForAutomaton(automata[1]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes2.insert( flowpipes2.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 2 ), flowpipes2.size() );
	

	// clear variable pool
	hypro::VariablePool::getInstance().changeToPool(0);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(1);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(0);
}

TYPED_TEST ( RectangularLabelSynchronizationTest, TwoAutomataNoCommonTime ) {
	// create first automaton with variable pool 0
    auto automaton1 = createRectangularHA2<typename TypeParam::NumberType>();
	automaton1.addTimeVariable();
	// create second automaton with variable pool 1
	hypro::VariablePool::getInstance().changeToPool(1);
    auto automaton2 = createRectangularHA5<typename TypeParam::NumberType>();
	automaton2.addTimeVariable();
	// change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

	std::vector<hypro::HybridAutomaton<typename TypeParam::NumberType>> automata{ automaton1, automaton2 };

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::NO_AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_v;

    hypro::Settings settings{ {},
                              hypro::FixedAnalysisParameters{ 2, hypro::tNumber( 9 ), hypro::tNumber( 0.01 ) },
                              { analysisParameters } };

    auto analyzer = hypro::RectangularSyncAnalyzer<TypeParam, hypro::HybridAutomaton<typename TypeParam::NumberType>>( automata, settings );

    auto result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );

	// validate computed flowpipes for automaton 1
	std::vector<TypeParam> flowpipes1;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[0]).begin(), analyzer.getReachTreeForAutomaton(automata[0]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes1.insert( flowpipes1.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 1 ), flowpipes1.size() );

	// validate computed flowpipes for automaton 2
	std::vector<TypeParam> flowpipes2;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[1]).begin(), analyzer.getReachTreeForAutomaton(automata[1]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes2.insert( flowpipes2.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 1 ), flowpipes2.size() );
	

	// clear variable pool
	hypro::VariablePool::getInstance().changeToPool(0);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(1);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(0);
}

TYPED_TEST ( RectangularLabelSynchronizationTest, ThreeAutomataTransitiveSync ) {
	// create first automaton with variable pool 0
    auto automaton1 = createRectangularHA6<typename TypeParam::NumberType>();
	automaton1.addTimeVariable();
	// create second automaton with variable pool 1
	hypro::VariablePool::getInstance().changeToPool(1);
    auto automaton2 = createRectangularHA7<typename TypeParam::NumberType>();
	automaton2.addTimeVariable();
    // create third automaton with variable pool 2
    hypro::VariablePool::getInstance().changeToPool(2);
    auto automaton3 = createRectangularHA8<typename TypeParam::NumberType>();
    automaton3.addTimeVariable();
	// change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

	std::vector<hypro::HybridAutomaton<typename TypeParam::NumberType>> automata{ automaton1, automaton2, automaton3 };

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::NO_AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_v;

    hypro::Settings settings{ {},
                              hypro::FixedAnalysisParameters{ 2, hypro::tNumber( 3 ), hypro::tNumber( 0.01 ) },
                              { analysisParameters } };

    auto analyzer = hypro::RectangularSyncAnalyzer<TypeParam, hypro::HybridAutomaton<typename TypeParam::NumberType>>( automata, settings );

    auto result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );

	// validate computed flowpipes for automaton 1
	std::vector<TypeParam> flowpipes1;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[0]).begin(), analyzer.getReachTreeForAutomaton(automata[0]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes1.insert( flowpipes1.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 4 ), flowpipes1.size() );
	EXPECT_TRUE( is_reachable_in( Point{ -1, 3 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ -1, 5 }, flowpipes1 ) );
	EXPECT_TRUE( is_reachable_in( Point{ -1, 7 }, flowpipes1 ) );

	EXPECT_FALSE( is_reachable_in( Point{ 4, 3.5 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 4, 5 }, flowpipes1 ) );
	EXPECT_FALSE( is_reachable_in( Point{ 4, 7 }, flowpipes1 ) );

	// clear variable pools
	hypro::VariablePool::getInstance().changeToPool(0);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(1);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(2);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(0);
}

TYPED_TEST ( RectangularLabelSynchronizationTest, ThreeAutomataMultiSync ) {
	// create first automaton with variable pool 0
    auto automaton1 = createRectangularHA9<typename TypeParam::NumberType>();
	automaton1.addTimeVariable();
	// create second automaton with variable pool 1
	hypro::VariablePool::getInstance().changeToPool(1);
    auto automaton2 = createRectangularHA10<typename TypeParam::NumberType>();
	automaton2.addTimeVariable();
    // create third automaton with variable pool 2
    hypro::VariablePool::getInstance().changeToPool(2);
    auto automaton3 = createRectangularHA11<typename TypeParam::NumberType>();
    automaton3.addTimeVariable();
	// change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

	std::vector<hypro::HybridAutomaton<typename TypeParam::NumberType>> automata{ automaton1, automaton2, automaton3 };

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::NO_AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_v;

    hypro::Settings settings{ {},
                              hypro::FixedAnalysisParameters{ 2, hypro::tNumber( 3 ), hypro::tNumber( 0.01 ) },
                              { analysisParameters } };

    auto analyzer = hypro::RectangularSyncAnalyzer<TypeParam, hypro::HybridAutomaton<typename TypeParam::NumberType>>( automata, settings );

    auto result = analyzer.run();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );

	// validate computed flowpipes for automaton 1
	std::vector<TypeParam> flowpipes1;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[0]).begin(), analyzer.getReachTreeForAutomaton(automata[0]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes1.insert( flowpipes1.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 3 ), flowpipes1.size() );

	// validate computed flowpipes for automaton 2
	std::vector<TypeParam> flowpipes2;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[1]).begin(), analyzer.getReachTreeForAutomaton(automata[1]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes2.insert( flowpipes2.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 3 ), flowpipes2.size() );

	// validate computed flowpipes for automaton 3
	std::vector<TypeParam> flowpipes3;
	std::for_each( analyzer.getReachTreeForAutomaton(automata[2]).begin(), analyzer.getReachTreeForAutomaton(automata[2]).end(), [&]( auto& root ) {
		auto fp = getFlowpipes( root );
		std::for_each( fp.begin(), fp.end(), [&]( const auto& flowpipe ) {
			flowpipes3.insert( flowpipes3.end(), flowpipe.begin(), flowpipe.end() );
		} );
	} );
	EXPECT_EQ( std::size_t( 3 ), flowpipes3.size() );

	// clear variable pools
	hypro::VariablePool::getInstance().changeToPool(0);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(1);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(2);
	hypro::VariablePool::getInstance().clear();
	hypro::VariablePool::getInstance().changeToPool(0);
}