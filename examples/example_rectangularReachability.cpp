/**
 * @brief Example file which shows how to instanciate a concrete worker out of
 * context handlers.
 */

#include <algorithms/reachability/analyzer/RectangularAnalyzer.h>
#include <iostream>
#include <representations/GeometricObjectBase.h>

int main() {
	// typedefs
	using Number = double;
	using State = hypro::State<Number, hypro::CarlPolytope<Number>>;
 	using Matrix = hypro::matrix_t<Number>;
  	using Vector = hypro::vector_t<Number>;

	// variables
	carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex( 0 );
	carl::Variable y = hypro::VariablePool::getInstance().carlVarByIndex( 1 );
	// rectangular dynamics
	std::map<carl::Variable, carl::Interval<Number>> dynamics;
	dynamics.emplace( std::make_pair( x, carl::Interval<Number>( 1, 2 ) ) );
	dynamics.emplace( std::make_pair( y, carl::Interval<Number>( 2, 3 ) ) );
	std::map<carl::Variable, carl::Interval<Number>> dynamics2;
	dynamics2.emplace( std::make_pair( x, carl::Interval<Number>( 3, 5 ) ) );
	dynamics2.emplace( std::make_pair( y, carl::Interval<Number>( 2, 4 ) ) );

	// hybrid automaton instance
	hypro::HybridAutomaton<Number> ha;

	// create one location with rectangular flow
	hypro::Location<Number> loc1;
	hypro::rectangularFlow<Number> flow( dynamics );
	loc1.setRectangularFlow( flow );
	hypro::Location<Number> loc2;
	hypro::rectangularFlow<Number> flow2( dynamics2 );
	loc2.setRectangularFlow( flow2 );

	// setup of the transition.
	std::unique_ptr<hypro::Transition<Number>> trans =
    	std::make_unique<hypro::Transition<Number>>();
	// guard
	hypro::Condition<Number> guard;
	Matrix guardMat = Matrix::Zero(4, 2);
	Vector guardVec = Vector::Zero(4);

	guardMat(0, 0) = Number(1);
	guardMat(1, 0) = Number(-1);
	guardVec(0, 0) = Number(10);
	guardVec(1, 0) = Number(-4);

	guard.setMatrix(guardMat);
	guard.setVector(guardVec);

	// reset function
	// hypro::Reset<Number> reset;
	// Matrix linearReset = Matrix::Zero(4, 2);
	// Vector constantReset = Vector::Zero(4);

	// linearReset(0, 0) = Number(1);
	// linearReset(1, 0) = Number(-1);
	// linearReset(2, 1) = Number(1);
	// linearReset(3, 1) = Number(-1);
	// constantReset(0, 0) = Number(0);
	// constantReset(1, 0) = Number(0);
	// constantReset(2, 0) = Number(0);
	// constantReset(3, 0) = Number(0);

	// reset.setMatrix(linearReset);
	// reset.setVector(constantReset);

	std::vector<carl::Interval<Number>> intervalReset;
	intervalReset.emplace_back( carl::Interval<Number>( -2, 2 ) );
	intervalReset.emplace_back( carl::Interval<Number>( -3, 3 ) );
	hypro::Reset<Number> reset;
	reset.setIntervals( intervalReset );

	// setup transition
	trans->setGuard(guard);
	trans->setSource(&loc1);
	trans->setTarget(&loc2);
	trans->setReset(reset);

	// add defined location and transition to the automaton.
	loc1.addTransition(std::move(trans));

	// setup of the transition.
	// std::unique_ptr<hypro::Transition<Number>> trans2 =
    // 	std::make_unique<hypro::Transition<Number>>();
	// // guard
	// hypro::Condition<Number> guard2;
	// Matrix guardMat2 = Matrix::Zero(4, 2);
	// Vector guardVec2 = Vector::Zero(4);

	// guardMat2(0, 0) = Number(1);
	// guardMat2(1, 0) = Number(-1);
	// guardVec2(0, 0) = Number(15);
	// guardVec2(1, 0) = Number(-6);

	// guard2.setMatrix(guardMat2);
	// guard2.setVector(guardVec2);

	// // reset function
	// std::vector<carl::Interval<Number>> intervalReset2;
	// intervalReset2.emplace_back( carl::Interval<Number>( -1, 1 ) );
	// intervalReset2.emplace_back( carl::Interval<Number>( -1, 1 ) );
	// hypro::Reset<Number> reset2;
	// // reset2.setIntervals( intervalReset2 );

	// // setup 
	// trans2->setGuard(guard2);
	// trans2->setSource(&loc2);
	// trans2->setTarget(&loc1);
	// trans2->setReset(reset2);

	// add defined location and transition to the automaton.
	// loc2.addTransition(std::move(trans2));

	// add location
	std::map<const hypro::Location<Number>*, std::size_t> locationMapping;
	ha.addLocation( loc1 );
	locationMapping[&loc1] = ha.getLocations().size() - 1;
	ha.addLocation( loc2 );
	locationMapping[&loc2] = ha.getLocations().size() - 1;

	// initial set is a unit box
	hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>( 4, 2 );
	constraints << 1, 0, -1, 0, 0, 1, 0, -1;
	hypro::vector_t<Number> constants = hypro::vector_t<Number>( 4 );
	constants << 1, 1, 1, 1;
	// hypro::matrix_t<Number> constraints2 = hypro::matrix_t<Number>( 4, 2 );
	// constraints2 << 1, 0, -1, 0, 0, 1, 0, -1;
	// hypro::vector_t<Number> constants2 = hypro::vector_t<Number>( 4 );
	// constants2 << 2, 2, 2, 2;

	// create and add initial state
	ha.addInitialState( ha.getLocations()[locationMapping[&loc1]], hypro::Condition<Number>( constraints, constants ) );
	// ha.addInitialState( ha.getLocations()[locationMapping[&loc2]], hypro::Condition<Number>( constraints2, constants2 ) );

	// std::cout << "HA is: " << ha << std::endl;

	// create settings
	hypro::Settings settings;
	settings.strategy[0] = hypro::AnalysisParameters{ mpq_class( 1 ) / mpq_class( 100 ), hypro::AGG_SETTING::AGG, -1, hypro::representation_name::carl_polytope };

	// call to analysis core
	hypro::RectangularAnalyzer<State> analyzer{ ha, settings };
	auto result = analyzer.run();

	if ( result == hypro::REACHABILITY_RESULT::UNKNOWN ) {
		std::cout << "Could not verify safety." << std::endl;
	} else {
		std::cout << "The model is safe." << std::endl;
	}

	// output computed sets
	for ( const auto& fp : analyzer.getFlowpipes() ) {
		for ( const auto& segment : fp ) {
			std::cout << segment << std::endl;
		}
	}

	return 0;
}
