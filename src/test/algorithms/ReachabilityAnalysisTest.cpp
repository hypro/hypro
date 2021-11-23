#include "../defines.h"
#include "gtest/gtest.h"
#include <cassert>
//#include <hypro/src/tool/cli/cli.h>
//#include <hypro/src/tool/cli/settingsProcessing.h>
//#include <hypro/src/tool/preprocessing.h>
//#include <hypro/src/tool/analysis.h>

#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/statistics/statistics.h>
#include <hypro/datastructures/reachability/TreeUtil.h>

#include <hypro/datastructures/HybridAutomaton/StateUtil.h>
#include <hypro/util/logging/Logger.h>

#include <hypro/util/plotting/Plotter.h>
class ReachabilityAnalysisTest : public ::testing::Test {
  protected:
	using Number = double;
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;
	void SetUp() override {
		// initialize hybrid automaton
		bball_ha = hypro::HybridAutomaton<Number>();
		ha = hypro::parseFlowstarFile<Number>( "../examples/input/building.model" );
		// create location
		std::unique_ptr<hypro::Location<Number>> loc{
			  std::make_unique<hypro::Location<Number>>( hypro::Location<Number>{ "l0" } ) };
		// create flow
		Matrix flow = Matrix::Zero( 3, 3 );
		flow( 0, 1 ) = Number( 1 );
		flow( 1, 2 ) = Number( -9.81 );
		// assign flow to location
		loc->setFlow( flow );

		// create invariant
		Matrix invariantConstraints = Matrix::Zero( 1, 2 );
		Vector invariantOffsets = Vector::Zero( 1 );
		invariantConstraints( 0, 0 ) = Number( -1 );
		// assign invariant to location
		loc->setInvariant( hypro::Condition( invariantConstraints, invariantOffsets ) );

		// create transition
		hypro::Transition<Number> loop{ loc.get(), loc.get() };
		// create guard
		Matrix guardConstraints = Matrix::Zero( 3, 2 );
		Vector guardOffsets = Vector::Zero( 3 );
		guardConstraints( 0, 0 ) = Number( 1 );
		guardConstraints( 1, 0 ) = Number( -1 );
		guardConstraints( 2, 1 ) = Number( 1 );
		// assign guard to transition
		loop.setGuard( hypro::Condition<Number>( guardConstraints, guardOffsets ) );
		// create reset
		Matrix resetMatrix = Matrix::Zero( 2, 2 );
		Vector resetVector = Vector::Zero( 2 );
		resetMatrix( 0, 0 ) = Number( 1 );
		resetMatrix( 1, 1 ) = Number( -0.75 );
		// assign reset to transition
		loop.setReset( hypro::Reset<Number>( resetMatrix, resetVector ) );
		// set aggregation settings of transition to full aggregation
		loop.setAggregation( hypro::Aggregation::aggregation );
		// assign transition to location
		loc->addTransition( std::make_unique<hypro::Transition<Number>>( loop ) );

		// create initial configuration
		Matrix initialConstraints = Matrix::Zero( 4, 2 );
		Vector initialConstants = Vector::Zero( 4 );
		initialConstraints( 0, 0 ) = Number( 1 );
		initialConstraints( 1, 0 ) = Number( -1 );
		initialConstraints( 2, 1 ) = Number( 1 );
		initialConstraints( 3, 1 ) = Number( -1 );
		initialConstants << Number( 10.2 ), Number( -10 ), Number( 0 ), Number( 0 );

		// assemble hybrid automaton
		auto& locPtr = bball_ha.addLocation( std::move( loc ) );
		bball_ha.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

		// set settings
		settings.jumpDepth = 1;
		settings.timeBound = hypro::tNumber( 4 );
		settings.timeStep = hypro::tNumber( 0.01 );
		settings.useBadStateTimingInformation = false;
		settings.useGuardTimingInformation = false;
		settings.useInvariantTimingInformation = false;
	}

	void TearDown() override {}
	std::pair<hypro::HybridAutomaton<Number>, hypro::ReachabilitySettings> ha;
	hypro::HybridAutomaton<Number> bball_ha;
	hypro::ReachabilitySettings settings;
};

TEST_F( ReachabilityAnalysisTest, ReacherConstruction ) {
	using tNumber = hypro::tNumber;
	std::vector<hypro::ReachTreeNode<hypro::HPolytope<Number>>> roots{};
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 3;
	fixedParameters.localTimeHorizon = 5;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 100 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::HPolytope<Number>>( this->bball_ha, settings.fixedParameters(),
																		 settings.strategy().front(), roots );
	SUCCEED();
}

TEST_F( ReachabilityAnalysisTest, BoxReachability ) {
	// create initial states - chose a state set representation, here: boxes
	std::vector<hypro::ReachTreeNode<hypro::Box<Number>>> roots =
		  hypro::makeRoots<hypro::Box<Number>>( this->bball_ha );

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 3;
	fixedParameters.localTimeHorizon = 5;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 100 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::Box<Number>>( this->bball_ha, settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();
/*
  hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();
  plotter.setFilename("bouncingBall_Box");
  for (auto &node : preorder(roots)) {
    // Plot single flowpipe
    for (auto &set : node.getFlowpipe()) {
      plotter.addObject(set.vertices());
    }
  }
  
  // write output.
  plotter.plot2d();*/
	// EXPECT_EQ( std::size_t( 3 ), flowpipes.size() );
	// the first jump happens somewhat around 1.45
	EXPECT_TRUE( roots.front().getFlowpipe().size() == 145 );
	EXPECT_EQ( std::size_t( 4 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );
}

TEST_F( ReachabilityAnalysisTest, HPolytopeReachability ) {
	// create initial states - chose a state set representation, here: HPolytope
	std::vector<hypro::ReachTreeNode<hypro::HPolytope<Number>>> roots =
		  hypro::makeRoots<hypro::HPolytope<Number>>( this->bball_ha );

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 3;
	fixedParameters.localTimeHorizon = 3;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 100 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::HPolytope<Number>>( this->bball_ha, settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();

	// EXPECT_EQ( std::size_t( 3 ), flowpipes.size() );
	// the first jump happens somewhat around 1.45
/*	
  hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();
  plotter.setFilename("bouncingBall_Hpoly");
  for (auto &node : preorder(roots)) {
    // Plot single flowpipe
    for (auto &set : node.getFlowpipe()) {
      plotter.addObject(set.vertices());
    }
  }
    plotter.plot2d();
*/
	EXPECT_TRUE( roots.front().getFlowpipe().size() == 145 );
	EXPECT_EQ( std::size_t( 4 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );
}



TEST_F( ReachabilityAnalysisTest, StarsetReachabilitBenchmark ) {
	// create initial states - chose a state set representation, here: Starsets
		std::vector<hypro::ReachTreeNode<hypro::Starset<Number>>> roots =
		  hypro::makeRoots<hypro::Starset<Number>>( std::get<0>(this->ha) );

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 5;
	fixedParameters.localTimeHorizon = 20;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 200 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 200 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::Starset;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::Starset<Number>>( std::get<0>(this->ha), settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();
	std::cout<<"reachabilityresult"<<reachabilityResult<<std::endl;
	std::cout<< "flowsize"<<roots.front().getFlowpipe().size() <<std::endl;
	std::cout<<hypro::getNumberNodes( roots.front() ) <<std::endl;

/*
  hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();
  plotter.setFilename("doginono");
  for (auto &node : preorder(roots)) {
    // Plot single flowpipe
    for (auto &set : node.getFlowpipe()) {
      plotter.addObject(set.vertices());
    }
  }
  */
  // write output.
  //plotter.plot2d();
  
}
TEST_F( ReachabilityAnalysisTest, supportfunctionbench ) {
	// create initial states - chose a state set representation, here: Starsets
		std::vector<hypro::ReachTreeNode<hypro::SupportFunctionNew<Number>>> roots =
		  hypro::makeRoots<hypro::SupportFunctionNew<Number>>( std::get<0>(this->ha) );

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 5;
	fixedParameters.localTimeHorizon = 20;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 200 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 200 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::SFN;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::SupportFunctionNew<Number>>( std::get<0>(this->ha), settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();
std::cout<<"reachabilityresult"<<reachabilityResult<<std::endl;

		std::cout<< "flowsize"<<roots.front().getFlowpipe().size() <<std::endl;
	std::cout<<hypro::getNumberNodes( roots.front()  )<<std::endl;

/*
  hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();
  plotter.setFilename("doginono");
  for (auto &node : preorder(roots)) {
    // Plot single flowpipe
    for (auto &set : node.getFlowpipe()) {
      plotter.addObject(set.vertices());
    }
  }
  */
  // write output.
  //plotter.plot2d();
  
}

TEST_F( ReachabilityAnalysisTest, boxbench ) {
	// create initial states - chose a state set representation, here: Starsets
		std::vector<hypro::ReachTreeNode<hypro::Box<Number>>> roots =
		  hypro::makeRoots<hypro::Box<Number>>( std::get<0>(this->ha) );

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 10;
	fixedParameters.localTimeHorizon = 20;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 200 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 200 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::box;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::Box<Number>>( std::get<0>(this->ha), settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();
	std::cout<<"reachabilityresult"<<reachabilityResult<<std::endl;
	std::cout<< "flowsize"<<roots.front().getFlowpipe().size() <<std::endl;
	std::cout<<hypro::getNumberNodes( roots.front()  )<<std::endl;


  
}



TEST_F( ReachabilityAnalysisTest, StarsetReachability ) {
	// create initial states - chose a state set representation, here: Starsets
	std::cout<<"buraya geldi"<<std::endl;
	std::vector<hypro::ReachTreeNode<hypro::Starset<Number>>> roots =
		  hypro::makeRoots<hypro::Starset<Number>>( this->bball_ha );

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 3;
	fixedParameters.localTimeHorizon = 5;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 100 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::Starset;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::Starset<Number>>( this->bball_ha, settings.fixedParameters(),
																   settings.strategy().front(), roots );
	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();

// plot flowpipes.

  
  hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();
  plotter.setFilename("bouncingBall_Starrr");
  for (auto &node : preorder(roots)) {
    // Plot single flowpipe
    for (auto &set : node.getFlowpipe()) {
      plotter.addObject(set.vertices());
    }
  }
  
  // write output.
  plotter.plot2d();
	//EXPECT_EQ( std::size_t( 3 ), flowpipes.size() );
	// the first jump happens somewhat around 1.45
	std::cout<< roots.front().getFlowpipe().size()<<std::endl;

	EXPECT_TRUE( roots.front().getFlowpipe().size() == 145 );
	EXPECT_EQ( std::size_t( 4 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );
}


TEST_F( ReachabilityAnalysisTest, VPolytopeReachability ) {
	// create initial states - chose a state set representation, here: HPolytope
	std::vector<hypro::ReachTreeNode<hypro::VPolytope<Number>>> roots =
		  hypro::makeRoots<hypro::VPolytope<Number>>( std::get<0>(this->ha) );

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 10;
	fixedParameters.localTimeHorizon = 10;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 200 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 200 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::VPolytope<Number>>( std::get<0>(this->ha), settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();
/*
  hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();
  plotter.setFilename("bouncingBall_Vpoly");
  for (auto &node : preorder(roots)) {
    // Plot single flowpipe
    for (auto &set : node.getFlowpipe()) {
      plotter.addObject(set.vertices());
    }
  }
  
  // write output.
  plotter.plot2d();
  */
	// EXPECT_EQ( std::size_t( 3 ), flowpipes.size() );
	// the first jump happens somewhat around 1.45
	std::cout<< roots.front().getFlowpipe().size()<<std::endl;

	EXPECT_TRUE( roots.front().getFlowpipe().size() == 145 );
	EXPECT_EQ( std::size_t( 4 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );
}



TEST_F( ReachabilityAnalysisTest, StarsetReachabilitBenchmark2 ) {
	// create initial states - chose a state set representation, here: Starsets
		std::vector<hypro::ReachTreeNode<hypro::HPolytope<Number>>> roots =
		  hypro::makeRoots<hypro::HPolytope<Number>>( std::get<0>(this->ha) );

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 3;
	fixedParameters.localTimeHorizon = 3;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 100 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::HPolytope<Number>>( std::get<0>(this->ha), settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();

  hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();
  plotter.setFilename("dogi");
  for (auto &node : preorder(roots)) {
    // Plot single flowpipe
    for (auto &set : node.getFlowpipe()) {
      plotter.addObject(set.vertices());
    }
  }
  
  // write output.
  plotter.plot2d();
  
}


