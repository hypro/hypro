/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <cassert>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/TreeUtil.h>

class ReachabilityAnalysisTest : public ::testing::Test {
  protected:
	using Number = double;
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;
	void SetUp() override {
		// initialize hybrid automaton
		bball_ha = hypro::HybridAutomaton<Number>();

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
		settings.jumpDepth = 2;
		settings.timeBound = hypro::tNumber( 4 );
		settings.timeStep = hypro::tNumber( 0.01 );
		settings.useBadStateTimingInformation = false;
		settings.useGuardTimingInformation = false;
		settings.useInvariantTimingInformation = false;
	}

	void TearDown() override {}

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

	// EXPECT_EQ( std::size_t( 3 ), flowpipes.size() );
	// the first jump happens somewhat around 1.45
	EXPECT_TRUE( roots.front().getFlowpipe().size() == 145 );
	EXPECT_EQ( std::size_t( 4 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );
}

TEST_F( ReachabilityAnalysisTest, BoxReachabilityUnsafe ) {
	// add bad states
	auto automaton = this->bball_ha;
	automaton.addLocalBadStates( automaton.getLocations().front(), hypro::Condition<Number>::True() );
	EXPECT_TRUE( automaton.getLocalBadStates().at( automaton.getLocations().front() ).isTrue() );
	// create initial states - chose a state set representation, here: boxes
	std::vector<hypro::ReachTreeNode<hypro::Box<Number>>> roots = hypro::makeRoots<hypro::Box<Number>>( automaton );

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

	auto reacher = hypro::reachability::Reach<hypro::Box<Number>>( automaton, settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();

	// EXPECT_EQ( std::size_t( 3 ), flowpipes.size() );
	// the first jump happens somewhat around 1.45
	EXPECT_TRUE( roots.front().getFlowpipe().size() == 1 );
	EXPECT_EQ( std::size_t( 1 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, reachabilityResult );
}

TEST_F( ReachabilityAnalysisTest, BoxReachabilityUnsafe2 ) {
	// add bad states
	auto automaton = this->bball_ha;
	automaton.addLocalBadStates(
		  automaton.getLocations().front(),
		  hypro::Condition<Number>( hypro::matrix_t<Number>::Zero( 2, 2 ), hypro::vector_t<Number>::Zero( 2 ) ) );
	EXPECT_TRUE( automaton.getLocalBadStates().at( automaton.getLocations().front() ).isTrue() );
	// create initial states - chose a state set representation, here: boxes
	std::vector<hypro::ReachTreeNode<hypro::Box<Number>>> roots = hypro::makeRoots<hypro::Box<Number>>( automaton );

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

	auto reacher = hypro::reachability::Reach<hypro::Box<Number>>( automaton, settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();

	// EXPECT_EQ( std::size_t( 3 ), flowpipes.size() );
	// the first jump happens somewhat around 1.45
	EXPECT_TRUE( roots.front().getFlowpipe().size() == 1 );
	EXPECT_EQ( std::size_t( 1 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, reachabilityResult );
}

TEST_F( ReachabilityAnalysisTest, BoxReachabilityInvalidInit ) {
	using I = carl::Interval<Number>;
	using IV = std::vector<I>;
	using Box = hypro::Box<Number>;

	// update initial states: they should not be contained in the invariant
	hypro::HybridAutomaton<Number>::locationConditionMap initialStatesMap;
	Box initialSet{ IV{ I{ -4, -3 }, I{ 0, 0 } } };
	initialStatesMap[this->bball_ha.getLocations().front()] = hypro::conditionFromIntervals( initialSet.intervals() );
	this->bball_ha.setInitialStates( initialStatesMap );
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

	// since the invariant is directly invalidated, not much should happen during analysis, i.e., no node should be expanded.
	EXPECT_TRUE( roots.front().getFlowpipe().size() == 0 );
	EXPECT_EQ( std::size_t( 1 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );
}

TEST_F( ReachabilityAnalysisTest, BoxReachabilityInvalidInvariant ) {
	// update invariant to something that is FALSE per se, here: x <= 0 and x >= 1
	Matrix invariantConstraints = Matrix::Zero( 2, 2 );
	Vector invariantOffsets = Vector::Zero( 2 );
	invariantConstraints( 0, 0 ) = Number( 1 );
	invariantConstraints( 1, 0 ) = Number( -1 );
	invariantOffsets << 0, -1;
	// assign new invariant to location
	this->bball_ha.getLocations().front()->setInvariant( hypro::Condition( invariantConstraints, invariantOffsets ) );
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

	// since the invariant is directly invalidated, not much should happen during analysis, i.e., no node should be expanded.
	EXPECT_TRUE( roots.front().getFlowpipe().size() == 0 );
	EXPECT_EQ( std::size_t( 1 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );
}

TEST_F( ReachabilityAnalysisTest, TrivialFixedPointCallback ) {
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
	analysisParameters.detectJumpFixedPoints = true;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::Box<Number>>( this->bball_ha, settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// create trivial callback, which always returns true
	std::function<bool( const hypro::Box<Number>&, const hypro::Location<Number>* )> fixedPointCallback = []( const hypro::Box<Number>&, const hypro::Location<Number>* ) -> bool { return true; };
	// test callback
	hypro::Box<Number> test;
	EXPECT_TRUE( fixedPointCallback( test, nullptr ) );
	// set up callback structure
	hypro::ReachabilityCallbacks<hypro::Box<Number>, hypro::Location<Number>> callbacks{ fixedPointCallback };
	// set callbacks
	reacher.setCallbacks( callbacks );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();

	EXPECT_EQ( std::size_t( 2 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_TRUE( std::all_of( std::begin( roots.front().getChildren() ), std::end( roots.front().getChildren() ), []( auto* node ) { return node->getFlowpipe().size() == 0; } ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );
}

TEST_F( ReachabilityAnalysisTest, SimpleGlobalTimeHorizon ) {
	// create initial states - chose a state set representation, here: boxes
	std::vector<hypro::ReachTreeNode<hypro::Box<Number>>> roots =
		  hypro::makeRoots<hypro::Box<Number>>( this->bball_ha );

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 3;
	fixedParameters.localTimeHorizon = 5;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 100 );
	fixedParameters.globalTimeHorizon = tNumber( 1 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;
	analysisParameters.detectJumpFixedPoints = true;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::Box<Number>>( this->bball_ha, settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();

	EXPECT_EQ( std::size_t( 1 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_TRUE( std::all_of( std::begin( roots.front().getChildren() ), std::end( roots.front().getChildren() ), []( auto* node ) { return node->getFlowpipe().size() == 100; } ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );
}

TEST_F( ReachabilityAnalysisTest, GlobalTimeHorizon ) {
	// create initial states - chose a state set representation, here: boxes
	std::vector<hypro::ReachTreeNode<hypro::Box<Number>>> roots =
		  hypro::makeRoots<hypro::Box<Number>>( this->bball_ha );

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 3;
	fixedParameters.localTimeHorizon = 5;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 100 );
	fixedParameters.globalTimeHorizon = tNumber( 2 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;
	analysisParameters.detectJumpFixedPoints = true;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::Box<Number>>( this->bball_ha, settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();

	EXPECT_EQ( std::size_t( 2 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_LE( roots.front().getFlowpipe().size(), hypro::SegmentInd( 200 ) );
	EXPECT_LE( ( *roots.front().getChildren().begin() )->getFlowpipe().size(), hypro::SegmentInd( 200 ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );
}

TEST_F( ReachabilityAnalysisTest, GlobalTimeHorizonOverrideLocal ) {
	// create initial states - chose a state set representation, here: boxes
	std::vector<hypro::ReachTreeNode<hypro::Box<Number>>> roots =
		  hypro::makeRoots<hypro::Box<Number>>( this->bball_ha );

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 3;
	fixedParameters.localTimeHorizon = 0.5;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 100 );
	fixedParameters.globalTimeHorizon = tNumber( 2 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;
	analysisParameters.detectJumpFixedPoints = true;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::Reach<hypro::Box<Number>>( this->bball_ha, settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();

	EXPECT_EQ( std::size_t( 2 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_LE( roots.front().getFlowpipe().size(), hypro::SegmentInd( 200 ) );
	EXPECT_LE( ( *roots.front().getChildren().begin() )->getFlowpipe().size(), hypro::SegmentInd( 200 ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );
}
