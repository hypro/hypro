#include "../../hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "../defines.h"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>

#include <unistd.h>	 //getcwd()

// using namespace antlr4;
using namespace hypro;

template <typename Number>
class AntlrParserTest : public ::testing::Test {
  protected:
	AntlrParserTest() {}
	~AntlrParserTest() {}
	virtual void setUp() {}
	virtual void tearDown() {}

	void cwd() {
		char cwd[1024];
		if ( getcwd( cwd, sizeof( cwd ) ) != NULL )
			fprintf( stdout, "Current working dir: %s\n", cwd );
		else
			std::cerr << "getcwd() error" << std::endl;
	}
	/*
		//Equality of Locations - without looking at transitions or id
		bool equals(const Location<Number>* lhs, const Location<Number>* rhs){
			return (lhs->getFlow() == rhs->getFlow() &&
					lhs->getExternalInput() == rhs->getExternalInput() &&
					lhs->getInvariant() == rhs->getInvariant() &&
					lhs->getName() == rhs->getName() );
		}

		//Equality of Transitions
		//bool equals(Transition<Number>* lhs, Transition<Number>* rhs){
		bool equals(std::unique_ptr<Transition<Number>> lhs, std::unique_ptr<Transition<Number>> rhs){
			if( (!equals(lhs->getSource(), rhs->getSource())) ||
				(!equals(lhs->getTarget(), rhs->getTarget())) ||
				(lhs->getUrgent() != rhs->getUrgent()) ||
				(lhs->getGuard() != rhs->getGuard()) ||
				(lhs->getReset() != rhs->getReset()) ) {
				return false;
			}
			return true;
		}

		//Equality of States
		bool equals(State_t<Number,Number> lhs, State_t<Number,Number> rhs){
			// quick checks first
			if (lhs.getNumberSets() != rhs.getNumberSets() || !equals(lhs.getLocation(),rhs.getLocation()) ||
	   lhs.getTimestamp() != rhs.getTimestamp()) { return false;
			}
			for(std::size_t i = 0; i < lhs.getNumberSets(); ++i) {
				if( lhs.getSetType(i) != rhs.getSetType(i)) {
					return false;
				}
				if(!std::visit(genericCompareVisitor(), lhs.getSet(i), rhs.getSet(i))) {
					return false;
				}
			}
			return true;
		}
	*/
};

TYPED_TEST( AntlrParserTest, JustTesting ) {
	// std::string path( "../../../../src/test/core/examples/test_bouncing_ball.txt" );
	std::string path("../src/test/core/examples/test_bouncing_ball.txt");
	// std::string path("../../src/test/core/examples/test_bouncing_ball.txt");
	// std::string path("/home/tobias/RWTH/8_WS2017/BA/hypro/src/test/core/examples/test_bouncing_ball.txt");

	this->cwd();
	try {
		std::pair<HybridAutomaton<TypeParam>, ReachabilitySettings> h = parseFlowstarFile<TypeParam>( path );
		SUCCEED();
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}
}

TYPED_TEST( AntlrParserTest, Settings ) {
	std::string path( "../src/test/core/examples/test_settings.txt" );
	//std::string path( "../../../../src/test/core/examples/test_settings.txt" );

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
	std::string path( "../src/test/core/examples/test_plain_rectangular.txt" );
	//std::string path( "../../../../src/test/core/examples/test_plain_rectangular.txt" );

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
	std::string path( "../src/test/core/examples/test_mixed_rectangular.txt" );
	//std::string path( "../../../../src/test/core/examples/test_mixed_rectangular.txt" );

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
	std::string path( "../src/test/core/examples/test_empty_file.txt" );
	//std::string path( "../../../../src/test/core/examples/test_empty_file.txt" );
	
	try {
		std::pair<HybridAutomaton<TypeParam>, ReachabilitySettings> h = parseFlowstarFile<TypeParam>( path );
		FAIL();
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		SUCCEED();
	}
}

TYPED_TEST( AntlrParserTest, TransitionParsing2 ) {
	std::string path( "../src/test/core/examples/test_transition_parsing_2.txt" );
	//std::string path( "../../../../src/test/core/examples/test_transition_parsing_2.txt" );
	// std::string path("/home/tobias/RWTH/8_WS2017/BA/hypro/src/test/core/examples/test_empty_file.txt");
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

	std::string path( "../src/test/core/examples/test_bracket_parsing.txt" );
	//std::string path( "../../../../src/test/core/examples/test_empty_file.txt" );
	
	try {
		std::pair<HybridAutomaton<TypeParam>, ReachabilitySettings> h = parseFlowstarFile<TypeParam>( path );
		Location<TypeParam>* loc = h.first.getLocation("negAngle");
		matrix_t<TypeParam> controlMatrix = matrix_t<TypeParam>::Zero(13,13);
		controlMatrix << 0,0,0,0,0,0,0,0,0,0,0,0,0.13453709720348,
						23.4,-0.5,3,0,0,0,0,0,0,0,0,0,0,
						1,0,0,0,0,0,0,0,0,0,0,0,0,
						1,-1,1,0,0,0,0,0,0,0,0,0,0,
						10,-10,10,0,0,0,0,0,0,0,0,0,0,
						-2,2,-2,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,
						1,0,0,0,0,0,0,0,0,0,0,0,0,
						1,-1,1,0,0,0,0,0,0,0,0,0,0,
						1,-1,10,0,0,0,0,0,0,0,0,0,0,
						1,-1,1,0,0,0,0,0,0,0,0,0,0,
						20,-25,10,40,0,0,-20,-10,0,0,0,0,30.3,
						6,3,0,0,0,0,0,0,0,0,0,0,4,
						0,0,0,0,0,0,0,0,0,0,0,0,0;
		if(std::is_same<TypeParam,double>::value){
			EXPECT_TRUE(controlMatrix.isApprox(loc->getLinearFlow().getFlowMatrix()));
		} else {
			SUCCEED();
		}
	} catch ( const std::runtime_error& e ) {
		std::cout << e.what() << std::endl;
		FAIL();
	}

}

//TYPED_TEST( AntlrParserTest, MinimalAcceptedFile ) {
	/*
	 * The simplest hybrid automaton HA that will be accepted by the parser is:
	 * - location l with x' = 1, no invariant, no transitions
	 * - initial state x in [0,0]
	 * - Settings for stepsize, maximum amount of jumps, duration of computation, output name, dimensions to plot
	 */
	/*
		std::string path("../../../../src/test/core/examples/test_minimal_accepted_file.txt");
		//std::string path("/home/tobias/RWTH/8_WS2017/BA/hypro/src/test/core/examples/test_minimal_accepted_file.txt");
		std::tuple<HybridAutomaton<TypeParam,State_t<TypeParam>>, ReachabilitySettings> h;
		try{
			h = parseFlowstarFile<TypeParam>(path);
		} catch(const std::runtime_error& e){
			std::cout << e.what() << std::endl;
			FAIL();
		}

		//Test if Settings were right
		ReachabilitySettings controlSettings;
		controlSettings.timeBound = TypeParam(3);
		controlSettings.jumpDepth = 1;
		controlSettings.timeStep = TypeParam(0.01);
		controlSettings.fileName = std::string("test_minimal_accepted_file");
		//std::vector<std::size_t> dimensions;
		//dimensions.push_back(0);
		std::vector<std::vector<std::size_t>> plotDims;
		//plotDims.push_back(dimensions);
		controlSettings.plotDimensions = plotDims;
		EXPECT_EQ(std::get<1>(h).plotDimensions.size(), size_t(0));
		EXPECT_EQ(std::get<1>(h).plotDimensions.size(), controlSettings.plotDimensions.size());
		EXPECT_EQ(std::get<1>(h), controlSettings);

		//Build hybrid automaton HA
		//The location
		matrix_t<TypeParam> flow = matrix_t<TypeParam>::Zero(2,2);
		flow(0,1) = TypeParam(1);
		LocationManager<TypeParam>& locManager = LocationManager<TypeParam>::getInstance();
		Location<TypeParam>* loc = locManager.create(flow);
		std::string name("l");
		loc->setName(name);
		//External Input
		//std::vector<carl::Interval<TypeParam>> ExtInput;
		//ExtInput.push_back(carl::Interval<TypeParam>(-1,4));
		//ExtInput.push_back(carl::Interval<TypeParam>());
		//loc->setExtInput(Box<TypeParam>(ExtInput));
		//Put location into locSet
		std::set<Location<TypeParam>*> locSet;
		locSet.insert(loc);
		//Initial state
		State_t<TypeParam> initState(loc);
		initState.setTimestamp(carl::Interval<TypeParam>(0));
		typename HybridAutomaton<TypeParam, State_t<TypeParam>>::locationStateMap lsMap;
		lsMap.insert(std::make_pair(loc, initState));
		//put everything together
		HybridAutomaton<TypeParam,State_t<TypeParam>> controlHA;
		controlHA.setLocations(locSet);
		controlHA.setInitialStates(lsMap);

		//Test if parsed HybridAutomaton has the same content as HA
		//NOTE: We cannot check for equality via operator== yet as locations differ in their id
		//EXPECT_EQ(std::get<0>(h), controlHA);

		//Check location - this hybrid automaton should only have one location
		HybridAutomaton<TypeParam, State_t<TypeParam>>& parsedHA = std::get<0>(h);
		EXPECT_EQ(parsedHA.getLocations().size(), std::size_t(1));
		EXPECT_TRUE(this->equals(parsedHA.getLocation(name), controlHA.getLocation(name)));
		//Check Transitions - this automaton has no transitions
		EXPECT_EQ(parsedHA.getTransitions().size(), std::size_t(0));
		EXPECT_EQ(controlHA.getTransitions().size(), std::size_t(0));
		//Check Initialstates - one init state with one state
		EXPECT_EQ(parsedHA.getInitialStates().size(), std::size_t(1));
		EXPECT_EQ(controlHA.getInitialStates().size(), std::size_t(1));
		EXPECT_NE(parsedHA.getInitialStates().find(parsedHA.getLocation(name)), parsedHA.getInitialStates().end());
		EXPECT_NE(controlHA.getInitialStates().find(controlHA.getLocation(name)), controlHA.getInitialStates().end());
		EXPECT_TRUE(this->equals(parsedHA.getInitialStates().begin()->first,
	   parsedHA.getInitialStates().begin()->first));
		EXPECT_TRUE(this->equals(parsedHA.getInitialStates().begin()->second,
	   parsedHA.getInitialStates().begin()->second));
		//Check local badstates - none
		EXPECT_EQ(parsedHA.getLocalBadStates().size(), std::size_t(0));
		//Check global badstates - none
		EXPECT_EQ(parsedHA.getGlobalBadStates().size(), std::size_t(0));
	*/
//}

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
