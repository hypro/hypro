/**
 *  Example for the usage of hypro::State, which allows to use several different representations internally (variant-based implementation).
 */

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <iostream>


int main( ) {
	using Number = double;
	// construct state directly with primary representation
	hypro::State<Number,hypro::Box<Number>,hypro::HPolytope<Number>> my_state{hypro::Box<Number>{carl::Interval<Number>(2,3)}};
	std::cout << "State set type of my_state is " << my_state.getSetType() << std::endl;

	// construct state from a h-polytope given as a matrix and a vector
	// set up constraints
	hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>::Zero(2,1);
	constraints << 1,-1;
	hypro::vector_t<Number>	constants = hypro::vector_t<Number>::Zero(2);
	constants << 3,-2;
	// cannot construct state directly, since box is the primary representation. Instead set state set afterwards
	hypro::State<Number,hypro::Box<Number>,hypro::HPolytope<Number>> my_other_state{};
	my_other_state.setSet(hypro::HPolytope<Number>{ constraints, constants });
	std::cout << "State set type of my_other_state is " << my_other_state.getSetType() << std::endl;

	exit( 0 );
}
