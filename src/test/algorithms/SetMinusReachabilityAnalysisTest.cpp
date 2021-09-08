#include "../defines.h"
#include "gtest/gtest.h"
#include <cassert>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/algorithms/reachability/analyzer/LTISetMinusAnalyzer.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/TreeUtil.h>

class SetMinusReachabilityAnalysisTest : public ::testing::Test {
  protected:
	using Number = double;
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;
	void SetUp() override {

		// set settings
		settings.jumpDepth = 2;
		//settings.timeBound = hypro::tNumber( 4 );
		settings.timeBound = hypro::tNumber( 3 );
		//settings.timeStep = hypro::tNumber( 0.01 );
		settings.timeStep = hypro::tNumber( 0.01 );
		settings.useBadStateTimingInformation = false;
		settings.useGuardTimingInformation = false;
		settings.useInvariantTimingInformation = false;


		//------------ SetMinusTest automaton ------------
		// initialize hybrid automaton
		setminus_ha = hypro::HybridAutomaton<Number>();

		// create location l0
		std::unique_ptr<hypro::Location<Number>> loc0{
			  std::make_unique<hypro::Location<Number>>( hypro::Location<Number>{ "l0" } ) };
		// create flow
		Matrix flow0 = Matrix::Zero( 3, 3 );
		flow0( 0, 2 ) = Number( 1 );
		flow0( 1, 0 ) = Number( 0 );
		flow0( 1, 1 ) = Number( 0 );
		// assign flow to location
		loc0->setFlow( flow0 );

		// create invariant for l0
		Matrix invariantConstraints0 = Matrix::Zero( 1, 2 );
		Vector invariantOffsets0 = Vector::Zero( 1 );
		invariantConstraints0( 0, 0 ) = Number( 1 );
		invariantOffsets0(0) = Number(8);
		// assign invariant to location
		loc0->setInvariant( hypro::Condition( invariantConstraints0, invariantOffsets0 ) );

		// create transition
		hypro::Transition<Number> trans01{ loc0.get(), loc0.get() };
		// create guard
		Matrix guardConstraints01 = Matrix::Zero( 4, 2 );
		Vector guardOffsets01 = Vector::Zero( 4 );
		guardConstraints01( 0, 0 ) = Number( 1 );
		guardConstraints01( 1, 0 ) = Number( -1 );
		guardConstraints01( 2, 1 ) = Number( 1 );
		guardConstraints01( 3, 1 ) = Number( -1 );
		guardOffsets01(0) = Number(4);
		guardOffsets01(1) = Number(-3);
		guardOffsets01(2) = Number(3)/Number(2);
		guardOffsets01(3) = Number(0);
		//std::cout << guardOffsets01(0) << std::endl;
		// assign guard to transition
		trans01.setGuard( hypro::Condition<Number>( guardConstraints01, guardOffsets01 ) );
		// create reset
		Matrix resetMatrix01 = Matrix::Zero( 2, 2 );
		Vector resetVector01 = Vector::Zero( 2 );
		resetMatrix01( 0, 1 ) = Number( 1 );
		resetMatrix01( 1, 1 ) = Number( 1 );
		trans01.setReset( hypro::Reset<Number>( resetMatrix01, resetVector01 ) );
		// set aggregation settings of transition to full aggregation
		trans01.setAggregation( hypro::Aggregation::aggregation );
		//make transition urgent
		trans01.setUrgent();
		// assign transition to location
		loc0->addTransition( std::make_unique<hypro::Transition<Number>>( trans01 ) );

		// create initial configuration
		Matrix initialConstraints0 = Matrix::Zero( 4, 2 );
		Vector initialConstants0 = Vector::Zero( 4 );
		initialConstraints0( 0, 0 ) = Number( 1 );
		initialConstraints0( 1, 0 ) = Number( -1 );
		initialConstraints0( 2, 1 ) = Number( 1 );
		initialConstraints0( 3, 1 ) = Number( -1 );
		initialConstants0 << Number( 1 ), Number( -1 ), Number( 2 ), Number( -1 );

		// assemble hybrid automaton
		auto& locPtr0 = setminus_ha.addLocation( std::move( loc0 ) );
		setminus_ha.addInitialState( locPtr0.get(), hypro::Condition<Number>( initialConstraints0, initialConstants0 ) );


		//------------ lawnMower automaton ------------
		// initialize hybrid automaton
		lawnMower = hypro::HybridAutomaton<Number>();

		// create location north_east
		hypro::Location<Number>* north_east=lawnMower.createLocation();
		north_east->setName("North_East");
		// create flow
		Matrix flow_north_east = Matrix::Zero( 3, 3 );
		flow_north_east( 0, 2 ) = Number( 10 );
		flow_north_east( 1, 2 ) = Number( 9 );
		// assign flow to location
		north_east->setFlow( flow_north_east );
		// create invariant
		Matrix invariantmat = Matrix::Zero( 4, 2 );
		Vector invariantoff = Vector::Zero( 4 );
		invariantmat( 0, 0 ) = Number( 1 );
		invariantmat( 1, 0 ) = Number( -1 );
		invariantmat( 2, 1 ) = Number( 1 );
		invariantmat( 3, 1 ) = Number( -1 );
		invariantoff << Number( 100 ), Number( -0 ), Number( 200 ), Number( -0 );
		// assign invariant to location
		north_east->setInvariant( hypro::Condition( invariantmat, invariantoff ) );

		
		// create location north_west
		hypro::Location<Number>* north_west=lawnMower.createLocation();
		north_west->setName("North_West");
		// create flow
		Matrix flow_north_west = Matrix::Zero( 3, 3 );
		flow_north_west( 0, 2 ) = Number( -10 );
		flow_north_west( 1, 2 ) = Number( 9 );
		// assign flow to location
		north_west->setFlow( flow_north_west );
		// assign invariant to location
		north_west->setInvariant( hypro::Condition( invariantmat, invariantoff ) );

		
		// create location south_east
		hypro::Location<Number>* south_east=lawnMower.createLocation();
		south_east->setName("South_East");
		// create flow
		Matrix flow_south_east = Matrix::Zero( 3, 3 );
		flow_south_east( 0, 2 ) = Number( 10 );
		flow_south_east( 1, 2 ) = Number( -9 );
		// assign flow to location
		south_east->setFlow( flow_south_east );
		// assign invariant to location
		south_east->setInvariant( hypro::Condition( invariantmat, invariantoff ) );

		
		// create location south_west
		hypro::Location<Number>* south_west=lawnMower.createLocation();
		south_west->setName("South_West");
		// create flow
		Matrix flow_south_west = Matrix::Zero( 3, 3 );
		flow_south_west( 0, 2 ) = Number( -10 );
		flow_south_west( 1, 2 ) = Number( -9 );
		// assign flow to location
		south_west->setFlow( flow_south_west );
		// assign invariant to location
		south_west->setInvariant( hypro::Condition( invariantmat, invariantoff ) );


		// create transitions
		hypro::Transition<Number>* north_east_north_west=north_east->createTransition(north_west);
		// create guard
		Matrix guardmat_ne_nw = Matrix::Zero( 1, 2 );
		Vector guardoff_ne_nw = Vector::Zero( 1 );
		guardmat_ne_nw( 0, 0 ) = Number( -1 );
		guardoff_ne_nw(0) = Number(-100);
		// assign guard to transition
		north_east_north_west->setGuard( hypro::Condition<Number>( guardmat_ne_nw, guardoff_ne_nw ) );
		//create reset
		Matrix resetmat_ne_nw = Matrix::Zero( 2, 2 );
		Vector resetoff_ne_nw = Vector::Zero( 2 );
		resetmat_ne_nw( 0, 0 ) = Number( 1 );
		resetmat_ne_nw( 1, 1 ) = Number( 1 );
		// no assign reset to transition
		//north_east_north_west.setReset( hypro::Reset<Number>( resetmat_ne_nw, resetoff_ne_nw ) );
		// no set aggregation settings of transition to full aggregation
		//north_east_north_west->setAggregation( hypro::Aggregation::aggregation );
		//north_east->addTransition( std::make_unique<hypro::Transition<Number>>( north_east_north_west ) );


		hypro::Transition<Number>* north_west_north_east=north_west->createTransition(north_east);
		// create guard
		Matrix guardmat_nw_ne = Matrix::Zero( 1, 2 );
		Vector guardoff_nw_ne = Vector::Zero( 1 );
		guardmat_nw_ne( 0, 0 ) = Number( 1 );
		guardoff_nw_ne(0) = Number(0);
		// assign guard to transition
		north_west_north_east->setGuard( hypro::Condition<Number>( guardmat_nw_ne, guardoff_nw_ne ) );
		//create reset
		Matrix resetmat_nw_ne = Matrix::Zero( 2, 2 );
		Vector resetoff_nw_ne = Vector::Zero( 2 );
		resetmat_nw_ne( 0, 0 ) = Number( 1 );
		resetmat_nw_ne( 1, 1 ) = Number( 1 );
		// assign reset to transition
		//north_west_north_east.setReset( hypro::Reset<Number>( resetmat_nw_ne, resetoff_nw_ne ) );
		// set aggregation settings of transition to full aggregation
		north_west_north_east->setAggregation( hypro::Aggregation::aggregation );
		//north_west->addTransition( std::make_unique<hypro::Transition<Number>>( north_west_north_east ) );


		hypro::Transition<Number>* north_east_south_east=north_east->createTransition(south_east);
		// create guard
		Matrix guardmat_ne_se = Matrix::Zero( 1, 2 );
		Vector guardoff_ne_se = Vector::Zero( 1 );
		guardmat_ne_se( 0, 1 ) = Number( -1 );
		guardoff_ne_se(0) = Number(-200);
		// assign guard to transition
		north_east_south_east->setGuard( hypro::Condition<Number>( guardmat_ne_se, guardoff_ne_se ) );
		//std::cout << hypro::Condition<Number>( guardmat_ne_se, guardoff_ne_se ) << std::endl;
		//create reset
		Matrix resetmat_ne_se = Matrix::Zero( 2, 2 );
		Vector resetoff_ne_se = Vector::Zero( 2 );
		resetmat_ne_se( 0, 0 ) = Number( 1 );
		resetmat_ne_se( 1, 1 ) = Number( 1 );
		// assign reset to transition
		//north_east_south_east.setReset( hypro::Reset<Number>( resetmat_ne_se, resetoff_ne_se ) );
		// set aggregation settings of transition to full aggregation
		//north_east_south_east->setAggregation( hypro::Aggregation::aggregation );
		//north_east->addTransition( std::make_unique<hypro::Transition<Number>>( north_east_south_east ) );


		hypro::Transition<Number>* south_east_north_east= south_east->createTransition(north_east);
		// create guard
		Matrix guardmat_se_ne = Matrix::Zero( 1, 2 );
		Vector guardoff_se_ne = Vector::Zero( 1 );
		guardmat_se_ne( 0, 1 ) = Number( 1 );
		guardoff_se_ne(0) = Number(0);
		// assign guard to transition
		south_east_north_east->setGuard( hypro::Condition<Number>( guardmat_se_ne, guardoff_se_ne ) );
		//std::cout << hypro::Condition<Number>( guardmat_se_ne, guardoff_se_ne ) << std::endl;
		//create reset
		Matrix resetmat_se_ne = Matrix::Zero( 2, 2 );
		Vector resetoff_se_ne = Vector::Zero( 2 );
		resetmat_se_ne( 0, 0 ) = Number( 1 );
		resetmat_se_ne( 1, 1 ) = Number( 1 );
		// assign reset to transition
		//south_east_north_east.setReset( hypro::Reset<Number>( resetmat_se_ne, resetoff_se_ne ) );
		// set aggregation settings of transition to full aggregation
		south_east_north_east->setAggregation( hypro::Aggregation::aggregation );
		//south_east->addTransition( std::make_unique<hypro::Transition<Number>>( south_east_north_east ) );


		hypro::Transition<Number>* north_west_south_west= north_west->createTransition(south_west);
		// create guard
		Matrix guardmat_nw_sw = Matrix::Zero( 1, 2 );
		Vector guardoff_nw_sw = Vector::Zero( 1 );
		guardmat_nw_sw( 0, 1 ) = Number( -1 );
		guardoff_nw_sw(0) = Number(-200);
		// assign guard to transition
		north_west_south_west->setGuard( hypro::Condition<Number>( guardmat_nw_sw, guardoff_nw_sw ) );
		//std::cout << hypro::Condition<Number>( guardmat_nw_sw, guardoff_nw_sw ) << std::endl;
		//create reset
		Matrix resetmat_nw_sw = Matrix::Zero( 2, 2 );
		Vector resetoff_nw_sw = Vector::Zero( 2 );
		resetmat_nw_sw( 0, 0 ) = Number( 1 );
		resetmat_nw_sw( 1, 1 ) = Number( 1 );
		// assign reset to transition
		//north_west_south_west.setReset( hypro::Reset<Number>( resetmat_nw_sw, resetoff_nw_sw ) );
		// set aggregation settings of transition to full aggregation
		north_west_south_west->setAggregation( hypro::Aggregation::aggregation );
		//north_west->addTransition( std::make_unique<hypro::Transition<Number>>( north_west_south_west ) );


		hypro::Transition<Number>* south_west_north_west=south_west->createTransition(north_west);
		// create guard
		Matrix guardmat_sw_nw = Matrix::Zero( 1, 2 );
		Vector guardoff_sw_nw = Vector::Zero( 1 );
		guardmat_sw_nw( 0, 1 ) = Number( 1 );
		guardoff_sw_nw(0) = Number(0);
		// assign guard to transition
		south_west_north_west->setGuard( hypro::Condition<Number>( guardmat_sw_nw, guardoff_sw_nw ) );
		//std::cout << hypro::Condition<Number>( guardmat_sw_nw, guardoff_sw_nw ) << std::endl;
		//create reset
		Matrix resetmat_sw_nw = Matrix::Zero( 2, 2 );
		Vector resetoff_sw_nw = Vector::Zero( 2 );
		resetmat_sw_nw( 0, 0 ) = Number( 1 );
		resetmat_sw_nw( 1, 1 ) = Number( 1 );
		// assign reset to transition
		//south_west_north_west.setReset( hypro::Reset<Number>( resetmat_sw_nw, resetoff_sw_nw ) );
		// set aggregation settings of transition to full aggregation
		south_west_north_west->setAggregation( hypro::Aggregation::aggregation );
		//south_west->addTransition( std::make_unique<hypro::Transition<Number>>( south_west_north_west ) );


		hypro::Transition<Number>* south_east_south_west=south_east->createTransition(south_west);
		// create guard
		Matrix guardmat_se_sw = Matrix::Zero( 1, 2 );
		Vector guardoff_se_sw = Vector::Zero( 1 );
		guardmat_se_sw( 0, 0 ) = Number( -1 );
		guardoff_se_sw(0) = Number(-100);
		// assign guard to transition
		south_east_south_west->setGuard( hypro::Condition<Number>( guardmat_se_sw, guardoff_se_sw ) );
		//std::cout << hypro::Condition<Number>( guardmat_se_sw, guardoff_se_sw ) << std::endl;
		//create reset
		Matrix resetmat_se_sw = Matrix::Zero( 2, 2 );
		Vector resetoff_se_sw = Vector::Zero( 2 );
		resetmat_se_sw( 0, 0 ) = Number( 1 );
		resetmat_se_sw( 1, 1 ) = Number( 1 );
		// assign reset to transition
		//south_east_south_west.setReset( hypro::Reset<Number>( resetmat_se_sw, resetoff_se_sw ) );
		// set aggregation settings of transition to full aggregation
		south_east_south_west->setAggregation( hypro::Aggregation::aggregation );
		//south_east->addTransition( std::make_unique<hypro::Transition<Number>>( south_east_south_west ) );


		hypro::Transition<Number>* south_west_south_east=south_west->createTransition(south_east);
		// create guard
		Matrix guardmat_sw_se = Matrix::Zero( 1, 2 );
		Vector guardoff_sw_se = Vector::Zero( 1 );
		guardmat_sw_se( 0, 0 ) = Number( 1 );
		guardoff_sw_se(0) = Number(0);
		// assign guard to transition
		south_west_south_east->setGuard( hypro::Condition<Number>( guardmat_sw_se, guardoff_sw_se ) );
		//std::cout << hypro::Condition<Number>( guardmat_sw_se, guardoff_sw_se ) << std::endl;
		//create reset
		Matrix resetmat_sw_se = Matrix::Zero( 2, 2 );
		Vector resetoff_sw_se = Vector::Zero( 2 );
		resetmat_sw_se( 0, 0 ) = Number( 1 );
		resetmat_sw_se( 1, 1 ) = Number( 1 );
		// assign reset to transition
		//south_west_south_east.setReset( hypro::Reset<Number>( resetmat_sw_se, resetoff_sw_se ) );
		// set aggregation settings of transition to full aggregation
		south_west_south_east->setAggregation( hypro::Aggregation::aggregation );
		//south_west->addTransition( std::make_unique<hypro::Transition<Number>>( south_west_south_east ) );


		hypro::Transition<Number>* urgent_ne_nw=north_east->createTransition(north_west);
		// create guard
		Matrix urgent_guard_mat = Matrix::Zero( 4, 2 );
		Vector urgent_guard_off = Vector::Zero( 4 );
		urgent_guard_mat( 0, 0 ) = Number( -1 );
		urgent_guard_mat( 1, 0 ) = Number( 1 );
		urgent_guard_mat( 2, 1 ) = Number( -1 );
		urgent_guard_mat( 3, 1 ) = Number( 1 );
		urgent_guard_off(0) = Number(-30);
		urgent_guard_off(1) = Number(70);
		urgent_guard_off(2) = Number(-100);
		urgent_guard_off(3) = Number(150);
		// assign guard to transition
		urgent_ne_nw->setGuard( hypro::Condition<Number>( urgent_guard_mat, urgent_guard_off ) );
		//std::cout << hypro::Condition<Number>( urgent_guard_mat, urgent_guard_off ) << std::endl;
		//create reset
		Matrix urgent_resetmat_ne_nw = Matrix::Zero( 2, 2 );
		Vector urgent_resetoff_ne_nw = Vector::Zero( 2 );
		urgent_resetmat_ne_nw( 0, 1 ) = Number( 1 );
		urgent_resetmat_ne_nw( 1, 1 ) = Number( 1 );
		// assign reset to transition
		//urgent_ne_nw.setReset( hypro::Reset<Number>( urgent_resetmat_ne_nw, urgent_resetoff_ne_nw ) );
		// set aggregation settings of transition to full aggregation
		urgent_ne_nw->setAggregation( hypro::Aggregation::aggregation );
		urgent_ne_nw->setUrgent();
		//north_east->addTransition( std::make_unique<hypro::Transition<Number>>( urgent_ne_nw ) );


		hypro::Transition<Number>* urgent_nw_ne=north_west->createTransition(north_east);
		// assign guard to transition
		urgent_nw_ne->setGuard( hypro::Condition<Number>( urgent_guard_mat, urgent_guard_off ) );
		//std::cout << hypro::Condition<Number>( guardmat_sw_se, urgent_guardoff_nw_ne ) << std::endl;
		//create reset
		Matrix urgent_resetmat_nw_ne = Matrix::Zero( 2, 2 );
		Vector urgent_resetoff_nw_ne = Vector::Zero( 2 );
		urgent_resetmat_nw_ne( 0, 0 ) = Number( 1 );
		urgent_resetmat_nw_ne( 1, 1 ) = Number( 1 );	
		// assign reset to transition
		//urgent_nw_ne.setReset( hypro::Reset<Number>( urgent_resetmat_nw_ne, urgent_resetoff_nw_ne ) );
		// set aggregation settings of transition to full aggregation
		urgent_nw_ne->setAggregation( hypro::Aggregation::aggregation );
		urgent_nw_ne->setUrgent();
		//north_west->addTransition( std::make_unique<hypro::Transition<Number>>( urgent_nw_ne ) );


		hypro::Transition<Number>* urgent_ne_se=north_east->createTransition(south_east);
		// assign guard to transition
		Matrix urgent_guard_mat_test = Matrix::Zero( 4, 2 );
		Vector urgent_guard_off_test = Vector::Zero( 4 );
		urgent_guard_mat_test( 0, 0 ) = Number( -1 );
		urgent_guard_mat_test( 1, 0 ) = Number( 1 );
		urgent_guard_mat_test( 2, 1 ) = Number( -1 );
		urgent_guard_mat_test( 3, 1 ) = Number( 1 );
		urgent_guard_off_test(0) = Number(-70);
		urgent_guard_off_test(1) = Number(100);
		urgent_guard_off_test(2) = Number(-50);
		urgent_guard_off_test(3) = Number(100);
		urgent_ne_se->setGuard( hypro::Condition<Number>( urgent_guard_mat, urgent_guard_off ) );
		//std::cout << hypro::Condition<Number>( guardmat_sw_se, urgent_guardoff_ne_se ) << std::endl;
		//create reset
		Matrix urgent_resetmat_ne_se = Matrix::Zero( 2, 2 );
		Vector urgent_resetoff_ne_se = Vector::Zero( 2 );
		urgent_resetmat_ne_se( 0, 1 ) = Number( 1 );
		urgent_resetmat_ne_se( 1, 1 ) = Number( 1 );
		// assign reset to transition
		//urgent_ne_se.setReset( hypro::Reset<Number>( urgent_resetmat_ne_se, urgent_resetoff_ne_se ) );
		// set aggregation settings of transition to full aggregation
		urgent_ne_se->setAggregation( hypro::Aggregation::aggregation );
		urgent_ne_se->setUrgent();
		//north_east->addTransition( std::make_unique<hypro::Transition<Number>>( urgent_ne_se ) );


		hypro::Transition<Number>* urgent_se_ne=south_east->createTransition(north_east);
		// assign guard to transition
		urgent_se_ne->setGuard( hypro::Condition<Number>( urgent_guard_mat, urgent_guard_off ) );
		//std::cout << hypro::Condition<Number>( guardmat_sw_se, urgent_guardoff_se_ne ) << std::endl;
		//create reset
		Matrix urgent_resetmat_se_ne = Matrix::Zero( 2, 2 );
		Vector urgent_resetoff_se_ne = Vector::Zero( 2 );
		urgent_resetmat_se_ne( 0, 0 ) = Number( 1 );
		urgent_resetmat_se_ne( 1, 1 ) = Number( 1 );
		// assign reset to transition
		//urgent_se_ne.setReset( hypro::Reset<Number>( urgent_resetmat_se_ne, urgent_resetoff_se_ne ) );
		// set aggregation settings of transition to full aggregation
		urgent_se_ne->setAggregation( hypro::Aggregation::aggregation );
		urgent_se_ne->setUrgent();
		//south_east->addTransition( std::make_unique<hypro::Transition<Number>>( urgent_se_ne ) );

		hypro::Transition<Number>* urgent_nw_sw=north_west->createTransition(south_west);
		urgent_nw_sw->setGuard( hypro::Condition<Number>( urgent_guard_mat, urgent_guard_off ) );
		//urgent_nw_sw.setReset( hypro::Reset<Number>( urgent_resetmat_se_ne, urgent_resetoff_se_ne ) );
		urgent_nw_sw->setAggregation( hypro::Aggregation::aggregation );
		urgent_nw_sw->setUrgent();
		//north_west->addTransition( std::make_unique<hypro::Transition<Number>>( urgent_nw_sw ) );

		hypro::Transition<Number>* urgent_sw_nw=south_west->createTransition(north_west);
		urgent_sw_nw->setGuard( hypro::Condition<Number>( urgent_guard_mat, urgent_guard_off ) );
		//urgent_sw_nw.setReset( hypro::Reset<Number>( urgent_resetmat_se_ne, urgent_resetoff_se_ne ) );
		urgent_sw_nw->setAggregation( hypro::Aggregation::aggregation );
		urgent_sw_nw->setUrgent();
		//south_west->addTransition( std::make_unique<hypro::Transition<Number>>( urgent_sw_nw ) );


		hypro::Transition<Number>* urgent_se_sw=south_east->createTransition(south_west);
		urgent_se_sw->setGuard( hypro::Condition<Number>( urgent_guard_mat, urgent_guard_off ) );
		//urgent_se_sw.setReset( hypro::Reset<Number>( urgent_resetmat_se_ne, urgent_resetoff_se_ne ) );
		urgent_se_sw->setAggregation( hypro::Aggregation::aggregation );
		urgent_se_sw->setUrgent();
		//south_east->addTransition( std::make_unique<hypro::Transition<Number>>( urgent_se_sw ) );


		hypro::Transition<Number>* urgent_sw_se=south_west->createTransition(south_east);
		urgent_sw_se->setGuard( hypro::Condition<Number>( urgent_guard_mat, urgent_guard_off ) );
		//urgent_sw_se.setReset( hypro::Reset<Number>( urgent_resetmat_se_ne, urgent_resetoff_se_ne ) );
		urgent_sw_se->setAggregation( hypro::Aggregation::aggregation );
		urgent_sw_se->setUrgent();
		//south_west->addTransition( std::make_unique<hypro::Transition<Number>>( urgent_sw_se ) );


		
		// create initial configuration
		Matrix initialmatlawnmower = Matrix::Zero( 4, 2 );
		Vector initialofflawnmower = Vector::Zero( 4 );
		initialmatlawnmower( 0, 0 ) = Number( 1 );
		initialmatlawnmower( 1, 0 ) = Number( -1 );
		initialmatlawnmower( 2, 1 ) = Number( 1 );
		initialmatlawnmower( 3, 1 ) = Number( -1 );
		initialofflawnmower << Number( 65 ), Number( -65 ), Number( 95 ), Number( -95 );

		// assemble hybrid automaton
		//auto& locPtr2 = lawnMower.addLocation( std::move( north_east ) );
		lawnMower.addInitialState( north_east, hypro::Condition<Number>( initialmatlawnmower, initialofflawnmower ) );
	}

	void TearDown() override {}

	hypro::HybridAutomaton<Number> setminus_ha;
	hypro::HybridAutomaton<Number> lawnMower;
	hypro::ReachabilitySettings settings;
};


TEST_F( SetMinusReachabilityAnalysisTest, LawnMowerAutomatonBoxes ) {
	// create initial states - chose a state set representation, here: boxes
	std::vector<hypro::ReachTreeNode<hypro::Box<Number>>> roots =
		  hypro::makeRoots<hypro::Box<Number>>( this->lawnMower );

//std::cout << roots << std::endl;

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 1;
	fixedParameters.localTimeHorizon = 2;
	//fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 2 );
	fixedParameters.fixedTimeStep = 1;

	hypro::AnalysisParameters analysisParameters;
	//analysisParameters.timeStep = tNumber( 1 ) / tNumber( 2 );
	analysisParameters.timeStep = 1;
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto analyzer = hypro::LTISetMinusAnalyzer<hypro::Box<Number>>( this->lawnMower, settings.fixedParameters(),
																   settings.strategy().front(), roots );
	analyzer.run();
	/*auto reacher = hypro::reachability::Reach<hypro::Box<Number>>( this->lawnMower, settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();*/

	/*auto reacher = hypro::reachability::ReachUrgency<hypro::Box<Number>>( this->lawnMower, settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();*/

	// EXPECT_EQ( std::size_t( 3 ), flowpipes.size() );
	// the first jump happens somewhat around 1.45
	/*EXPECT_TRUE( roots.front().getFlowpipe().size() == 145 );
	EXPECT_EQ( std::size_t( 4 ), hypro::getNumberNodes( roots.front() ) );
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, reachabilityResult );*/
}

TEST_F( SetMinusReachabilityAnalysisTest, LawnMowerAutomatonPolytopes ) {
	// create initial states - chose a state set representation, here: boxes
	std::vector<hypro::ReachTreeNode<hypro::HPolytope<Number>>> roots =
		  hypro::makeRoots<hypro::HPolytope<Number>>( this->lawnMower );

//std::cout << roots << std::endl;

	EXPECT_TRUE( roots.size() == std::size_t( 1 ) );

	using tNumber = hypro::tNumber;
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 1;
	fixedParameters.localTimeHorizon = 2;
	//fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 2 );
	fixedParameters.fixedTimeStep = 1;

	hypro::AnalysisParameters analysisParameters;
	//analysisParameters.timeStep = tNumber( 1 ) / tNumber( 2 );
	analysisParameters.timeStep = 1;
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	auto reacher = hypro::reachability::ReachUrgency<hypro::HPolytope<Number>>( this->lawnMower, settings.fixedParameters(),
																   settings.strategy().front(), roots );

	// run reacher. Return type explicit to be able to monitor changes
	auto reachabilityResult = reacher.computeForwardReachability();
	std::cout << "ausgabetest" << std::endl;

}