/*
 * Copyright (c) 2023-2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Testfile to test adding the time variable to an automaton.
 * 
 */

#include "test/defines.h"
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>


template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA() {
	// One-dimensional HA with one location
	using Matrix = hypro::matrix_t<Number>;
	using Interval = carl::Interval<Number>;
	using Vector = hypro::vector_t<Number>;
	using Point = hypro::Point<Number>;

	hypro::HybridAutomaton<Number> res;

	// Create location
	auto loc = res.createLocation();
    loc->setName("loc0");

	// Set flow x' = [1,2]
	Interval flow{ 1, 2 };
	typename hypro::rectangularFlow<Number>::flowMap fMap;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flow;
	loc->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set invariant x <= 10
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 10;
	loc->setInvariant( { invariantConstraints, invariantConstants } );

	// Set initial state x = 0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 0, 0;

	// set loc as initial location + add initial valuation
	res.addInitialState( loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}


TEST( TimeVariableAdditionTest, AutomatonDimensionDouble ) {
    hypro::VariablePool::getInstance().clear();
    using Number = double;
    auto automaton = createRectangularHA<Number>();

    auto loc0 = automaton.getLocation("loc0");

    ASSERT_EQ( automaton.dimension(), (unsigned)1 );
    ASSERT_EQ( loc0->getInvariant().dimension(), (unsigned)1 );
    ASSERT_EQ( automaton.getInitialStates().at(loc0).dimension(), (unsigned)1 );

    automaton.addTimeVariable();

    ASSERT_EQ( automaton.dimension(), (unsigned)2 );
    
    carl::Interval<Number> constInterval(1, 1);
    ASSERT_EQ( loc0->getRectangularFlow().getFlowIntervalForDimension(hypro::VariablePool::getInstance().getTimeVariable()), constInterval );

    ASSERT_EQ( loc0->getInvariant().dimension(), (unsigned)2 );

    ASSERT_EQ( automaton.getInitialStates().at(loc0).dimension(), (unsigned)2 );

    SUCCEED();
}

TEST( TimeVariableAdditionTest, AutomatonDimensionMPQ ) {
    hypro::VariablePool::getInstance().clear();
    using Number = mpq_class;
    auto automaton = createRectangularHA<Number>();

    auto loc0 = automaton.getLocation("loc0");

    ASSERT_EQ( automaton.dimension(), (unsigned)1 );
    ASSERT_EQ( loc0->getInvariant().dimension(), (unsigned)1 );
    ASSERT_EQ( automaton.getInitialStates().at(loc0).dimension(), (unsigned)1 );

    automaton.addTimeVariable();

    ASSERT_EQ( automaton.dimension(), (unsigned)2 );
    
    carl::Interval<Number> constInterval(1, 1);
    ASSERT_EQ( loc0->getRectangularFlow().getFlowIntervalForDimension(hypro::VariablePool::getInstance().getTimeVariable()), constInterval );

    ASSERT_EQ( loc0->getInvariant().dimension(), (unsigned)2 );

    ASSERT_EQ( automaton.getInitialStates().at(loc0).dimension(), (unsigned)2 );

    SUCCEED();
}