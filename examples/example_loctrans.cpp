#include "config.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/Point.h"
#include "parser/antlr4-flowstar/ParserWrapper.h"

#include <iostream>
int main() {
	// typedefs for simplification.
	typedef mpq_class Number;
	std::pair<hypro::HybridAutomaton<Number>, hypro::ReachabilitySettings> ha = std::move( hypro::parseFlowstarFile<Number>( "../examples/input/bouncing_ball.model" ) );
	hypro::HybridAutomaton<Number> bBallAutomaton = ha.first;
	auto loc = *bBallAutomaton.getLocation( "l" );
	std::cout << "num trans for loc state " << loc.getTransitions().size() << std::endl;
	loc = *bBallAutomaton.getLocation( "l" );
	std::cout << "num trans for loc state " << loc.getTransitions().size() << std::endl;
	return 0;
}