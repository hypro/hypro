/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <bits/c++config.h>
#include <fstream>
#include <hypro/datastructures/HybridAutomaton/Condition.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/Location.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/representations/conversion/typedefs.h>
#include <hypro/types.h>
#include <iostream>
#include <unistd.h>	 //getcwd()

// using namespace antlr4;
using namespace hypro;

template <typename Number>
class AntlrParserTest : public ::testing::Test {
  protected:
	AntlrParserTest() = default;
	~AntlrParserTest() = default;
	virtual void setUp() {}
	virtual void tearDown() {}

	void cwd() {
		char cwd[1024];
		if ( getcwd( cwd, sizeof( cwd ) ) != nullptr )
			fprintf( stdout, "Current working dir: %s\n", cwd );
		else
			std::cerr << "getcwd() error" << std::endl;
	}
};

/// Test for parsing locations
TYPED_TEST( AntlrParserTest, LocationParsingTest ) {
	using Matrix = hypro::matrix_t<TypeParam>;
	using Vector = hypro::vector_t<TypeParam>;
	std::string path( getTestModelsPath() + "parser/test_location_parsing.txt" );

	this->cwd();
	try {
		auto [automaton, settings] = parseFlowstarFile<TypeParam>( path );
		EXPECT_EQ( automaton.getLocations().size(), std::size_t( 2 ) );
		hypro::Location<TypeParam>* loc0 = automaton.getLocations().front();
		hypro::Location<TypeParam>* loc1 = automaton.getLocations().back();
		EXPECT_EQ( std::size_t( 0 ), loc0->getTransitions().size() );
		EXPECT_EQ( std::size_t( 0 ), loc1->getTransitions().size() );
		if ( loc0->getName() == "rod1" ) {
			EXPECT_EQ( "rod2", loc1->getName() );
			EXPECT_FALSE( loc0->isUrgent() );
			EXPECT_TRUE( loc1->isUrgent() );
		} else if ( loc0->getName() == "rod2" ) {
			EXPECT_EQ( "rod1", loc1->getName() );
			EXPECT_FALSE( loc1->isUrgent() );
			EXPECT_TRUE( loc0->isUrgent() );
		} else {
			FAIL();
		}

		// test correct flow
		Matrix flow = Matrix::Zero( 4, 4 );
		flow( 0, 0 ) = TypeParam( 2 );
		flow( 0, 1 ) = TypeParam( -56 );
		flow( 0, 3 ) = TypeParam( 4 );
		flow( 1, 1 ) = TypeParam( 782 );
		flow( 2, 3 ) = TypeParam( 1 );
		EXPECT_EQ( flow, loc0->getLinearFlow().getFlowMatrix() );
		EXPECT_EQ( flow, loc1->getLinearFlow().getFlowMatrix() );
		// test correct invariants
		Matrix constraints = Matrix::Zero( 6, 3 );
		constraints( 0, 0 ) = TypeParam( 1 );
		constraints( 1, 0 ) = TypeParam( -1 );
		constraints( 2, 1 ) = TypeParam( 1 );
		constraints( 3, 0 ) = TypeParam( -11 );
		constraints( 3, 1 ) = TypeParam( -1 );
		constraints( 3, 2 ) = TypeParam( -1 );
		constraints( 4, 2 ) = TypeParam( -1 );
		constraints( 5, 2 ) = TypeParam( 1 );
		Vector constants = Vector::Zero( 6 );
		constants << TypeParam( 510 ), TypeParam( -510 ), TypeParam( 25 ), TypeParam( 0 ), TypeParam( 2 ),
			  TypeParam( 2 );
		hypro::Condition<TypeParam> invariant{ constraints, constants };
		EXPECT_EQ( invariant, loc0->getInvariant() );
		EXPECT_EQ( invariant, loc1->getInvariant() );
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}
}

/// Test for parsing the bouncing ball model
TYPED_TEST( AntlrParserTest, JustTesting ) {
	using Matrix = hypro::matrix_t<TypeParam>;
	using Vector = hypro::vector_t<TypeParam>;
	std::string path( getTestModelsPath() + "parser/test_bouncing_ball_obscured.txt" );

	this->cwd();
	try {
		auto [automaton, settings] = parseFlowstarFile<TypeParam>( path );
		EXPECT_EQ( automaton.getLocations().size(), std::size_t( 1 ) );
		hypro::Location<TypeParam>* loc = automaton.getLocations().front();
		EXPECT_EQ( loc->getTransitions().size(), std::size_t( 2 ) );
		EXPECT_FALSE( loc->isUrgent() );
		// test correct flow
		Matrix flow = Matrix::Zero( 3, 3 );
		flow( 0, 1 ) = TypeParam( 1 );
		flow( 1, 2 ) = TypeParam( -9.81 );
		EXPECT_EQ( flow, loc->getLinearFlow().getFlowMatrix() );
		// test correct invariants
		Matrix constraints = Matrix::Zero( 1, 2 );
		constraints( 0, 0 ) = TypeParam( -1 );
		Vector constants = Vector::Zero( 1 );
		hypro::Condition<TypeParam> invariant{ constraints, constants };
		EXPECT_EQ( invariant, loc->getInvariant() );
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}
}

TYPED_TEST( AntlrParserTest, BadStatesParsing ) {
	using Matrix = hypro::matrix_t<TypeParam>;
	using Vector = hypro::vector_t<TypeParam>;
	std::string path( getTestModelsPath() + "parser/test_bad_states.txt" );

	this->cwd();
	try {
		auto [automaton, settings] = parseFlowstarFile<TypeParam>( path );
		EXPECT_EQ( automaton.getLocations().size(), std::size_t( 3 ) );
		hypro::Location<TypeParam>* loc = automaton.getLocation( "location_with_under_scores" );
		hypro::Location<TypeParam>* loc1 = automaton.getLocation( "minimal_location" );
		hypro::Location<TypeParam>* loc2 = automaton.getLocation( "minimal_location_2" );
		EXPECT_EQ( loc->getTransitions().size(), std::size_t( 2 ) );
		EXPECT_FALSE( loc->isUrgent() );
		// test correct flow
		Matrix flow = Matrix::Zero( 3, 3 );
		flow( 0, 1 ) = TypeParam( 4 );
		flow( 0, 2 ) = TypeParam( -9.81 );
		flow( 1, 2 ) = TypeParam( 1 );
		EXPECT_EQ( flow, loc->getLinearFlow().getFlowMatrix() );
		// test correct invariants
		Matrix constraints = Matrix::Zero( 4, 2 );
		constraints( 0, 0 ) = TypeParam( -1 );
		constraints( 1, 1 ) = TypeParam( 1 );
		constraints( 2, 0 ) = TypeParam( -1 );
		constraints( 3, 1 ) = TypeParam( 1 );
		Vector constants = Vector::Zero( 4 );
		constants << TypeParam( 0 ), TypeParam( -8.81 ), TypeParam( -0.5 ), TypeParam( 123 );
		hypro::Condition<TypeParam> invariant{ constraints, constants };
		EXPECT_EQ( invariant, loc->getInvariant() );
		EXPECT_FALSE( automaton.getLocalBadStates().empty() );
		EXPECT_EQ( hypro::Condition<TypeParam>(), automaton.getLocalBadStates().at( loc1 ) );
		EXPECT_EQ( hypro::Condition<TypeParam>( { createUnboundedInterval<TypeParam>(),
												  carl::Interval<TypeParam>( TypeParam{ -2.5 }, TypeParam{ 0.0 } ) } ),
				   automaton.getLocalBadStates().at( loc2 ) );
		EXPECT_TRUE( automaton.getGlobalBadStates().size() == 4 );
		Matrix badSetConstraints = Matrix::Zero( 1, 2 );
		badSetConstraints( 0, 0 ) = TypeParam( 1 );
		Vector badSetConstants = Vector( 1 );
		badSetConstants( 0 ) = TypeParam( 3 );
		EXPECT_EQ( automaton.getGlobalBadStates()[1], hypro::Condition<TypeParam>( badSetConstraints, badSetConstants ) );
		EXPECT_EQ( automaton.getGlobalBadStates().back(), hypro::Condition<TypeParam>( badSetConstraints, badSetConstants ) );
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}
}

TYPED_TEST( AntlrParserTest, Settings ) {
	std::string path( getTestModelsPath() + "parser/test_settings.txt" );

	this->cwd();
	try {
		std::pair<HybridAutomaton<TypeParam>, ReachabilitySettings> h = parseFlowstarFile<TypeParam>( path );
		SUCCEED();
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}
}

TYPED_TEST( AntlrParserTest, PlainRectangular ) {
	std::string path( getTestModelsPath() + "parser/test_plain_rectangular.txt" );

	this->cwd();
	try {
		std::pair<HybridAutomaton<TypeParam>, ReachabilitySettings> h = parseFlowstarFile<TypeParam>( path );
		SUCCEED();
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}
}

TYPED_TEST( AntlrParserTest, MixedRectangular ) {
	std::string path( getTestModelsPath() + "parser/test_mixed_rectangular.txt" );

	this->cwd();
	try {
		std::pair<HybridAutomaton<TypeParam>, ReachabilitySettings> h = parseFlowstarFile<TypeParam>( path );
		SUCCEED();
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}
}

TYPED_TEST( AntlrParserTest, EmptyFile ) {
	std::string path( getTestModelsPath() + "parser/test_empty_file.txt" );

	try {
		std::pair<HybridAutomaton<TypeParam>, ReachabilitySettings> h = parseFlowstarFile<TypeParam>( path );
		FAIL();
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		SUCCEED();
	}
}

TYPED_TEST( AntlrParserTest, TransitionParsing2 ) {
	std::string path( getTestModelsPath() + "parser/test_transition_parsing_2.txt" );
	try {
		auto [automaton, settings] = parseFlowstarFile<TypeParam>( path );

		auto loc = *automaton.getLocation( "l1" );

		auto transition = std::find_if( loc.getTransitions().begin(), loc.getTransitions().end(),
										[]( auto& transPtr ) { return transPtr->getTarget()->getName() == "l2"; } );

		ASSERT_TRUE( transition != loc.getTransitions().end() );

		EXPECT_EQ( "sync_1", ( *transition )->getLabels().front().getName() );

		loc = *automaton.getLocation( "l3" );

		transition = std::find_if( loc.getTransitions().begin(), loc.getTransitions().end(),
								   []( auto& transPtr ) { return transPtr->getTarget()->getName() == "l1"; } );

		ASSERT_TRUE( transition != loc.getTransitions().end() );
		EXPECT_EQ( std::size_t( 2 ), ( *transition )->getLabels().size() );

		EXPECT_EQ( "sync_2", ( *transition )->getLabels().at( 0 ).getName() );
		EXPECT_EQ( "sync_3", ( *transition )->getLabels().at( 1 ).getName() );

		EXPECT_TRUE( std::find( ( *transition )->getLabels().begin(), ( *transition )->getLabels().end(),
								Label( "sync_2" ) ) != ( *transition )->getLabels().end() );

		EXPECT_TRUE( std::find( ( *transition )->getLabels().begin(), ( *transition )->getLabels().end(),
								Label( "sync_3" ) ) != ( *transition )->getLabels().end() );

		EXPECT_FALSE( std::find( ( *transition )->getLabels().begin(), ( *transition )->getLabels().end(),
								 Label( "sync_1" ) ) != ( *transition )->getLabels().end() );

		SUCCEED();
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}
}

TYPED_TEST( AntlrParserTest, BracketParsingTest ) {
	std::string path( getTestModelsPath() + "parser/test_bracket_parsing.txt" );

	try {
		std::pair<HybridAutomaton<TypeParam>, ReachabilitySettings> h = parseFlowstarFile<TypeParam>( path );
		Location<TypeParam>* loc = h.first.getLocation( "negAngle" );

		matrix_t<TypeParam> controlMatrix = matrix_t<TypeParam>::Zero( 14, 14 );
		controlMatrix( 0, 13 ) = TypeParam( 0.13453709720348 );
		controlMatrix( 1, 0 ) = TypeParam( 23.4 );
		controlMatrix( 1, 1 ) = -0.5;
		controlMatrix( 1, 2 ) = 3;
		controlMatrix( 1, 13 ) = 4;
		controlMatrix( 2, 0 ) = TypeParam( 1 );
		controlMatrix( 3, 0 ) = 1;
		controlMatrix( 3, 1 ) = -1;
		controlMatrix( 3, 2 ) = 1;
		controlMatrix( 4, 0 ) = 10;
		controlMatrix( 4, 1 ) = -10;
		controlMatrix( 4, 2 ) = 10;
		controlMatrix( 5, 0 ) = -2;
		controlMatrix( 5, 1 ) = 2;
		controlMatrix( 5, 2 ) = -2;
		controlMatrix( 6, 0 ) = 1;
		controlMatrix( 7, 0 ) = 1;
		controlMatrix( 7, 1 ) = -1;
		controlMatrix( 7, 2 ) = 1;
		controlMatrix( 8, 0 ) = 1;
		controlMatrix( 8, 1 ) = -1;
		controlMatrix( 8, 2 ) = 10;
		controlMatrix( 9, 0 ) = 1;
		controlMatrix( 9, 1 ) = -1;
		controlMatrix( 9, 2 ) = 1;
		controlMatrix( 10, 0 ) = 20;
		controlMatrix( 10, 1 ) = -25;
		controlMatrix( 10, 2 ) = 10;
		controlMatrix( 10, 3 ) = 40;
		controlMatrix( 10, 6 ) = -20;
		controlMatrix( 10, 7 ) = -10;
		controlMatrix( 10, 13 ) = 30.3;
		controlMatrix( 11, 0 ) = 6;
		controlMatrix( 11, 1 ) = 3;
		controlMatrix( 12, 0 ) = 6;
		controlMatrix( 12, 1 ) = 3;
		controlMatrix( 12, 13 ) = 4;
		if ( std::is_same<TypeParam, double>::value ) {
			std::cout << loc->getLinearFlow().getFlowMatrix() << std::endl;
			EXPECT_TRUE( controlMatrix.isApprox( loc->getLinearFlow().getFlowMatrix() ) );
		} else {
			SUCCEED();
		}
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}
}

TYPED_TEST( AntlrParserTest, MinimalAcceptedFile ) {
	/*
	 * The simplest hybrid automaton HA that will be accepted by the parser is:
	 * - location l with x' = 1, no invariant, no transitions
	 * - initial state x in [0,0]
	 * - Settings for stepsize, maximum amount of jumps, duration of computation, output name, dimensions to plot
	 */
	using Matrix = hypro::matrix_t<TypeParam>;
	std::string path( getTestModelsPath() + "parser/test_minimal_accepted_file.txt" );
	std::tuple<HybridAutomaton<TypeParam>, ReachabilitySettings> h;
	try {
		h = parseFlowstarFile<TypeParam>( path );
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}

	// Test if Settings were right
	ReachabilitySettings controlSettings;
	controlSettings.timeBound = TypeParam( 3 );
	controlSettings.jumpDepth = 1;
	controlSettings.timeStep = TypeParam( 0.01 );
	controlSettings.fileName = std::string( "test_minimal_accepted_file" );
	std::vector<std::vector<std::size_t>> plotDims;
	controlSettings.plotDimensions = plotDims;
	EXPECT_EQ( std::get<1>( h ).plotDimensions.size(), size_t( 0 ) );
	EXPECT_EQ( std::get<1>( h ).plotDimensions.size(), controlSettings.plotDimensions.size() );
	EXPECT_EQ( std::get<1>( h ), controlSettings );

	// Build hybrid automaton HA
	// The location
	Matrix flow = Matrix::Zero( 2, 2 );
	flow( 0, 1 ) = TypeParam( 1 );
	Location<TypeParam> loc{ flow };
	loc.setName( "l" );
	// Initial state
	hypro::Condition<TypeParam> initialValuation{
		  conditionFromIntervals( std::vector<carl::Interval<TypeParam>>{ carl::Interval<TypeParam>{ 0 } } ) };
	typename HybridAutomaton<TypeParam>::locationConditionMap lsMap;
	lsMap.insert( std::make_pair( &loc, initialValuation ) );

	// Check location - this hybrid automaton should only have one location
	HybridAutomaton<TypeParam>& parsedHA = std::get<0>( h );
	EXPECT_EQ( parsedHA.getLocations().size(), std::size_t( 1 ) );
	EXPECT_EQ( *parsedHA.getLocation( "l" ), loc );
	// Check Transitions - this automaton has no transitions
	EXPECT_EQ( parsedHA.getTransitions().size(), std::size_t( 0 ) );
	// Check Initialstates - one init state with one state
	EXPECT_EQ( parsedHA.getInitialStates().size(), std::size_t( 1 ) );
	EXPECT_NE( parsedHA.getInitialStates().find( parsedHA.getLocation( "l" ) ), parsedHA.getInitialStates().end() );
	EXPECT_EQ( *parsedHA.getInitialStates().begin()->first, loc );
	EXPECT_EQ( parsedHA.getInitialStates().begin()->second, initialValuation );
	// Check local badstates - none
	EXPECT_EQ( parsedHA.getLocalBadStates().size(), std::size_t( 0 ) );
	// Check global badstates - none
	EXPECT_EQ( parsedHA.getGlobalBadStates().size(), std::size_t( 0 ) );
}

/*
TYPED_TEST(AntlrParserTest, parallelComposition){
	std::string pathA("/home/tobias/RWTH/8_WS2017/BA/examples/A.model");
	std::string pathB("/home/tobias/RWTH/8_WS2017/BA/examples/B.model");

	try{
		std::cout << "Parser A" << std::endl;
		std::tuple<HybridAutomaton<TypeParam,State_t<TypeParam>>, ReachabilitySettings> hA =
parseFlowstarFile<TypeParam>(pathA);

		std::cout << "Parser B" << std::endl;
		std::tuple<HybridAutomaton<TypeParam,State_t<TypeParam>>, ReachabilitySettings> hB =
parseFlowstarFile<TypeParam>(pathB);

		HybridAutomaton<TypeParam,State_t<TypeParam>> haA = std::get<0>(hA);
		HybridAutomaton<TypeParam,State_t<TypeParam>> haB = std::get<0>(hB);

		haA||haB;

		SUCCEED();
	} catch(const std::runtime_error& e){
		std::cout << e.what() << std::endl;
		FAIL();
	}
}

TYPED_TEST(AntlrParserTest, bouncing_ball_with_label){
	std::string path("/home/tobias/RWTH/8_WS2017/BA/examples/bouncing_ball_with_label.model");

	try{
		std::tuple<HybridAutomaton<TypeParam,State_t<TypeParam>>, ReachabilitySettings> h =
parseFlowstarFile<TypeParam>(path); SUCCEED(); } catch(const std::runtime_error& e){ std::cout << e.what() << std::endl;
		FAIL();
	}
}

TYPED_TEST(AntlrParserTest, railraod_crossing){
	std::string path("/home/tobias/RWTH/8_WS2017/BA/examples/railraod_crossing.model");

	try{
		std::tuple<HybridAutomatonComp<TypeParam,State_t<TypeParam>>, ReachabilitySettings> h =
parseFlowstarCompFile<TypeParam>(path); SUCCEED(); } catch(const std::runtime_error& e){ std::cout << e.what() <<
std::endl; FAIL();
	}
}
*/

// TYPED_TEST(AntlrParserTest, VarNamesPrefixesOfEachOther){ } 	//x, x1, x10, x101 ...
// TYPED_TEST(AntlrParserTest, SettingsTest){}					//smth like maxjumps 0, maxjumps 1e-10...
// TYPED_TEST(AntlrParserTest, LocationsTest){}					//lots of locations, flows, extInputs, invariants
// TYPED_TEST(AntlrParserTest, TransitionsTest){}				//lots of transitions, weird guards, resets, ...
// TYPED_TEST(AntlrParserTest, InitialStatesTest){}
// TYPED_TEST(AntlrParserTest, LocalBadStatesTest){}
// TYPED_TEST(AntlrParserTest, GlobalBadStatesTest){}
// Tests to see if smth throws an exception

// TYPED_TEST(AntlrParserTest, OnlyStart){
//
//	std::string path("../../../../src/test/core/examples/test_only_start.txt");
//	//std::string path("../../src/test/core/examples/test_only_start.txt");
//	try{
//		std::tuple<HybridAutomaton<TypeParam,State_t<TypeParam>>, ReachabilitySettings> h =
// parseFlowstarFile<TypeParam>(path); 		FAIL(); 	} catch(const std::runtime_error& e){ 		std::cout <<
// e.what()
// << std::endl; 		SUCCEED();
//	}
//
//}

TYPED_TEST( AntlrParserTest, StochasticParsing ) {
	std::string path( getTestModelsPath() + "parser/test_stochastic_parsing.txt" );
	// std::string path( "../../../../src/test/core/examples/test_stochastic_parsing.txt" );

	try {
		auto [automaton, settings] = parseFlowstarFile<TypeParam>( path );

		auto loc = *automaton.getLocation( "l1" );

		auto transition = std::find_if( loc.getTransitions().begin(), loc.getTransitions().end(),
										[]( auto& transPtr ) { return transPtr->getTarget()->getName() == "l2"; } );

		ASSERT_TRUE( transition != loc.getTransitions().end() );

		EXPECT_EQ( "sync_1", ( *transition )->getLabels().front().getName() );

		SUCCEED();
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}
}
