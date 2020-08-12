#include "../defines.h"
#include "algorithms/reachability/Reach.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "gtest/gtest.h"
#include <cassert>

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
	hypro::reachability::Reach<Number, hypro::reachability::ReachQuiet, hypro::State_t<Number>> reacher =
		  hypro::reachability::Reach<Number, hypro::reachability::ReachQuiet, hypro::State_t<Number>>( this->bball_ha,
																									   this->settings );
	SUCCEED();
}

TEST_F( ReachabilityAnalysisTest, BoxReachability ) {
	hypro::reachability::Reach<Number, hypro::reachability::ReachQuiet, hypro::State_t<Number>> reacher =
		  hypro::reachability::Reach<Number, hypro::reachability::ReachQuiet, hypro::State_t<Number>>( this->bball_ha,
																									   this->settings );

	// create initial states - chose a state set representation, here: boxes
	for ( const auto& locSetPair : this->bball_ha.getInitialStates() ) {
		assert( locSetPair.second.constraints().size() == 1 );
		auto box = hypro::Converter<Number>::toBox( locSetPair.second.constraints().front() );
		auto state = hypro::State_t<Number>( locSetPair.first );
		state.setSet( box );
		reacher.addInitialState( std::move( state ) );
	}

	// run reacher. Return type explicit to be able to monitor changes
	auto flowpipes = reacher.computeForwardReachability();

	EXPECT_EQ( std::size_t( 3 ), flowpipes.size() );
	// the first jump happens somewhat around 1.45
	EXPECT_TRUE( flowpipes.begin()->second.back().getTimestamp().contains( hypro::tNumber( 1.45 ) ) );
}
