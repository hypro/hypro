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

	// variables
	carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex( 0 );
	carl::Variable y = hypro::VariablePool::getInstance().carlVarByIndex( 1 );
	// rectangular dynamics
	std::map<carl::Variable, carl::Interval<Number>> dynamics;
	dynamics.emplace( std::make_pair( x, carl::Interval<Number>( 1, 2 ) ) );
	dynamics.emplace( std::make_pair( y, carl::Interval<Number>( 2, 3 ) ) );

	// hybrid automaton instance
	hypro::HybridAutomaton<Number> ha;

	// create one location with rectangular flow
	hypro::Location<Number> loc1;
	hypro::rectangularFlow<Number> flow( dynamics );
	loc1.setRectangularFlow( flow );

	// add location
	ha.addLocation( loc1 );

	// initial set is a unit box
	hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>( 4, 2 );
	constraints << 1, 0, -1, 0, 0, 1, 0, -1;
	hypro::vector_t<Number> constants = hypro::vector_t<Number>( 4 );
	constants << 1, 1, 1, 1;

	// create and add initial state
	ha.addInitialState( &loc1, hypro::Condition<Number>( constraints, constants ) );

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
