/**
 * Testfile for hybrid automata.
 * Author: ckugler
 */

#include "../defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/output/Flowstar.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
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
	Matrix constraints = Matrix::Zero( 4, 3 );
	Vector constants = Vector::Zero( 4 );

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

	return res;
}

/**
 * Hybrid Automaton Test
 */
TEST( HybridAutomataOutputTest, HybridAutomatonTest ) {
	hypro::LockedFileWriter out{ "tmp.model" };
	out.clearFile();
	auto automaton{ createSingularAutomaton<mpq_class>() };
	std::cout << hypro::toFlowstarFormat( automaton, hypro::ReachabilitySettings{ 1, 1, 1 } );
	out << hypro::toFlowstarFormat( automaton, hypro::ReachabilitySettings{ 1, 1, 1 } );

	auto [automatonParsed, settings] = hypro::parseFlowstarFile<mpq_class>( std::string( "tmp.model" ) );
	// std::remove( "tmp.model" );

	auto otherLocs = automatonParsed.getLocations();
	for ( auto loc : automaton.getLocations() ) {
		bool found = false;
		std::cout << "Compare loc " << *loc << " To " << std::endl << std::endl;
		for ( auto otherLoc : otherLocs ) {
			std::cout << *otherLoc << std::endl;
			if ( *loc == *otherLoc ) {
				found = true;
				std::cout << "Equal" << std::endl << std::endl;
				break;
			} else {
				std::cout << "NOT Equal" << std::endl << std::endl;
			}
		}
		EXPECT_TRUE( found );
	}

	EXPECT_EQ( automaton, automatonParsed );
	SUCCEED();
}
