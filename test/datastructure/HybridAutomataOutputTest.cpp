/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Testfile for hybrid automata.
 * Author: ckugler
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/output/Flowstar.h>
#include <hypro/datastructures/HybridAutomaton/output/SpaceEx.h>
#include <hypro/flags.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/util/VariablePool.h>
#include <hypro/util/logging/Filewriter.h>

template <typename Number>
hypro::HybridAutomaton<Number> createSingularAutomaton() {
	// automaton created from a parametric location tree of a hybrid Petri net
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> res;

	// get location pointers
	auto* locAllOn = res.createLocation();
	locAllOn->setName( "allOn" );
	auto* locInOffFirst = res.createLocation();
	locInOffFirst->setName( "inOffFirst" );
	auto* locOutOffFirst = res.createLocation();
	locOutOffFirst->setName( "outOffFirst" );
	auto* locAllOff = res.createLocation();
	locAllOff->setName( "allOff" );
	auto* locRateAdaptationUp = res.createLocation();
	locRateAdaptationUp->setName( "rateAdaptationUp" );
	auto* locRateAdaptationLo = res.createLocation();
	locRateAdaptationLo->setName( "rateAdaptationLo" );

	// set dynamics, variable order: t,s,x,aff
	Eigen::Index aff = 3;
	Eigen::Index t = 0;
	Eigen::Index s = 1;
	Eigen::Index x = 2;
	Matrix dynamics = Matrix::Zero( 4, 4 );
	dynamics( t, aff ) = 1;	 // t' = 1

	dynamics( s, aff ) = 1;	 // s' = 1
	dynamics( x, aff ) = 1;	 // x' = 1
	locAllOn->setLinearFlow( { dynamics } );

	dynamics( s, aff ) = 0;	  // s' = 1
	dynamics( x, aff ) = -1;  // x' = -1
	locInOffFirst->setLinearFlow( { dynamics } );

	dynamics( s, aff ) = 1;	 // s' = 1
	dynamics( x, aff ) = 2;	 // x' = 2
	locOutOffFirst->setLinearFlow( { dynamics } );

	dynamics( s, aff ) = 0;	 // s' = 0
	dynamics( x, aff ) = 0;	 // x' = 0
	locAllOff->setLinearFlow( { dynamics } );
	locRateAdaptationLo->setLinearFlow( { dynamics } );

	dynamics( s, aff ) = 1;	 // s' = 1
	dynamics( x, aff ) = 0;	 // x' = 0
	locRateAdaptationUp->setLinearFlow( { dynamics } );

	// set invariants
	Matrix constraints = Matrix::Zero( 3, 3 );
	Vector constants = Vector::Zero( 3 );

	// global invariants: t <= 15, x in [0,10]
	constraints( 0, t ) = 1;
	constants( 0 ) = 15;
	constraints( 1, x ) = 1;
	constants( 1 ) = 10;
	constraints( 2, x ) = -1;
	constants( 2 ) = 0;

	locOutOffFirst->setInvariant( { constraints, constants } );
	locAllOff->setInvariant( { constraints, constants } );
	locRateAdaptationUp->setInvariant( { constraints, constants } );

	// t <= 5
	constraints = Matrix::Zero( 4, 3 );
	constants = Vector::Zero( 4 );
	constraints( 0, t ) = 1;
	constants( 0 ) = 15;
	constraints( 1, x ) = 1;
	constants( 1 ) = 10;
	constraints( 2, x ) = -1;
	constants( 2 ) = 0;
	constraints( 3, t ) = 1;
	constants( 3 ) = 5;

	locAllOn->setInvariant( { constraints, constants } );
	locInOffFirst->setInvariant( { constraints, constants } );
	locRateAdaptationLo->setInvariant( { constraints, constants } );

	// transitions with guards
	Matrix guardConstraints = Matrix::Zero( 2, 3 );
	Vector guardConstants = Vector::Zero( 2 );

	// guard t = 5
	guardConstraints( 0, t ) = 1;
	guardConstraints( 1, t ) = -1;
	guardConstants( 0 ) = 5;
	guardConstants( 1 ) = -5;

	locAllOn->createTransition( locInOffFirst );
	auto* t1 = locAllOn->createTransition( locOutOffFirst );
	auto* t2 = locInOffFirst->createTransition( locRateAdaptationLo );
	auto* t3 = locInOffFirst->createTransition( locAllOff );
	auto* t4 = locOutOffFirst->createTransition( locRateAdaptationUp );
	locOutOffFirst->createTransition( locAllOff );
	auto* t6 = locRateAdaptationLo->createTransition( locAllOff );
	locRateAdaptationUp->createTransition( locAllOff );

	t1->setGuard( { guardConstraints, guardConstants } );
	t3->setGuard( { guardConstraints, guardConstants } );
	t6->setGuard( { guardConstraints, guardConstants } );

	// guard x = 0
	guardConstraints = Matrix::Zero( 2, 3 );
	guardConstants = Vector::Zero( 2 );
	guardConstraints( 0, x ) = 1;
	guardConstraints( 1, x ) = -1;
	guardConstants( 0 ) = 0;
	guardConstants( 1 ) = -0;

	t2->setGuard( { guardConstraints, guardConstants } );

	// guard x = 10
	guardConstants( 0 ) = 10;
	guardConstants( 1 ) = -10;

	t4->setGuard( { guardConstraints, guardConstants } );

	// initial states: x=z=t=0, aff = 1
	Matrix initialConstraints = Matrix::Zero( 6, 3 );
	Vector initialConstants = Vector::Zero( 6 );
	initialConstraints( 0, t ) = 1;
	initialConstraints( 1, t ) = -1;
	initialConstraints( 2, x ) = 1;
	initialConstraints( 3, x ) = -1;
	initialConstraints( 4, s ) = 1;
	initialConstraints( 5, s ) = -1;

	res.addInitialState( locAllOn, { initialConstraints, initialConstants } );

	res.setVariables( { "t", "s", "x" } );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularAutomaton() {
	// automaton created from a parametric location tree of a hybrid Petri net
	using Interval = carl::Interval<Number>;

	hypro::HybridAutomaton<Number> res;

	// get location pointers
	auto* l1 = res.createLocation();
	l1->setName( "l1" );
	auto* l2 = res.createLocation();
	l2->setName( "l2" );

	// initialize variables
	hypro::VariablePool& pool = hypro::VariablePool::getInstance();
	auto& a = pool.newCarlVariable( "a" );
	auto& b = pool.newCarlVariable( "b" );
	auto& c = pool.newCarlVariable( "c" );

	typename hypro::rectangularFlow<Number>::flowMap flows;
	flows[a] = Interval( 2, 3 );
	flows[b] = Interval( 1, 6 );
	flows[c] = Interval( -2, 4 );
	l1->setFlow( hypro::rectangularFlow<Number>{ flows } );

	flows.clear();
	flows[a] = Interval( 2, 3 );
	flows[b] = Interval( 1, 6 );
	flows[c] = Interval( -2, 4 );
	l2->setFlow( hypro::rectangularFlow<Number>{ flows } );

	res.setVariables( { "a", "b", "c" } );

	auto initialValuations = hypro::conditionFromIntervals( std::vector<carl::Interval<Number>>{ carl::Interval<Number>{ 1, 2 }, carl::Interval<Number>{ 1, 2 }, carl::Interval<Number>{ 1, 2 } } );
	res.addInitialState( l1, initialValuations );

	return res;
}

/**
 * Hybrid Automaton Test
 */
TEST( HybridAutomataOutputTest, SingularHybridAutomatonFlowstar ) {
	hypro::LockedFileWriter out{ "tmp.model" };
	out.clearFile();
	auto automaton{ createSingularAutomaton<mpq_class>() };
	out << hypro::toFlowstarFormat( automaton, hypro::ReachabilitySettings{ 1, 1, 1 } );

	auto [automatonParsed, settings] = hypro::parseFlowstarFile<mpq_class>( std::string( "tmp.model" ) );

	auto otherLocs = automatonParsed.getLocations();
	for ( auto loc : automaton.getLocations() ) {
		bool found = false;
		for ( auto otherLoc : otherLocs ) {
			if ( *loc == *otherLoc ) {
				found = true;
				break;
			}
		}
		if ( !found ) {
			std::cout << "Could not find location " << *loc << std::endl;
		}
		ASSERT_TRUE( found );
	}
	out.deleteFile();

	EXPECT_EQ( automaton, automatonParsed );
	SUCCEED();
}

#ifdef HYPRO_USE_TINYXML
TEST( HybridAutomataOutputTest, SingularHybridAutomatonSpaceEx ) {
	hypro::LockedFileWriter out{ "tmp.xml" };
	out.clearFile();
	auto automaton{ createSingularAutomaton<mpq_class>() };
	std::string tmp = hypro::toSpaceExFormat( automaton, hypro::ReachabilitySettings{ 1, 1, 1 } );
	std::cout << "Obtained result " << tmp << std::endl;
	out << tmp;

	SUCCEED();
}
#endif

/*

TEST( HybridAutomataOutputTest, LinearHybridAutomatonTest ) {
	hypro::LockedFileWriter out{ "tmp.model" };
	out.clearFile();

	auto [automatonParsed, settings] = hypro::parseFlowstarFile<mpq_class>( hypro::getTestModelsPath() + "parser/test_bad_states.txt" );

	out << hypro::toFlowstarFormat( automatonParsed, hypro::ReachabilitySettings{ 1, 1, 1 } );

	std::cout << hypro::toFlowstarFormat( automatonParsed, hypro::ReachabilitySettings{ 1, 1, 1 } ) << std::endl;

	std::fstream f1, f2;
	int flag = 3;

	f1.open( hypro::getTestModelsPath() + "parser/test_bad_states.model", std::ios::in );
	f2.open( "tmp.model", std::ios::in );

	while ( true ) {
		auto c1 = f1.get();
		auto c2 = f2.get();
		if ( c1 != c2 ) {
			flag = 0;
			break;
		}
		if ( ( c1 == EOF ) || ( c2 == EOF ) )
			break;
	}

	out.deleteFile();

	EXPECT_TRUE( flag );
}

TEST( HybridAutomataOutputTest, RectangularHybridAutomatonTest ) {
	hypro::LockedFileWriter out{ "tmp.model" };
	out.clearFile();
	auto automaton{ createRectangularAutomaton<mpq_class>() };
	out << hypro::toFlowstarFormat( automaton, hypro::ReachabilitySettings{ 1, 1, 1 } );

	auto [automatonParsed, settings] = hypro::parseFlowstarFile<mpq_class>( std::string( "tmp.model" ) );

	auto otherLocs = automatonParsed.getLocations();
	TRACE( "hypro.datastructures", "############# START SEARCH" );
	for ( auto loc : automaton.getLocations() ) {
		bool found = false;
		for ( auto otherLoc : otherLocs ) {
			std::cout << "Other location: " << *otherLoc << std::endl;
			if ( *loc == *otherLoc ) {
				found = true;
				break;
			}
		}
		if ( !found ) {
			std::cout << "Could not find location " << *loc << std::endl;
			TRACE( "hypro.datastructures", "############# END SEARCH" );
		}
		ASSERT_TRUE( found );
	}
	TRACE( "hypro.datastructures", "############# END SEARCH" );
	out.deleteFile();

	EXPECT_EQ( automaton, automatonParsed );
	SUCCEED();
}
*/
