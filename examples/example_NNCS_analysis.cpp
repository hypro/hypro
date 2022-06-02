#include <iostream>
#include <chrono>
//#include <fstream>
//#include <graphviz/cgraph.h>
//#include <graphviz/gvc.h>
#include <string>
#include <typeinfo>
#include <vector>

#include "hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "hypro/datastructures/HybridAutomaton/Path.h"
#include "hypro/datastructures/HybridAutomaton/State.h"
#include "hypro/datastructures/reachability/Settings.h"
#include "hypro/neuralnets/parser/NNet.h"
#include "hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "hypro/algorithms/reachability/Reach.h"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"


using Number = double;
using tNumber = hypro::tNumber;

/*
// Add self loop that does nothing
void addSelfTransition( std::unique_ptr<Location<Number>>&& location, const hypro::Label label ){
	hypro::Transition<Number> transition;
	//transition.setAggregation( hypro::Aggregation::clustering );
	//transition.setClusterBound( 5 );
	transition.setSource( location.get() );
	transition.setTarget( location.get() );
	transition.addLabel( label );
	location->addTransition( std::make_unique<hypro::Transition<Number>>( transition ) );
}
*/

// Add label "a" to transitions if no labels present in entire automaton
// Subsequent labels by alphabetic order
void addLabels( hypro::HybridAutomaton<Number> automaton ){
	std::cout << "Number of labels: " << std::size(automaton.getLabels()) << std::endl;
	if( automaton.getLabels().empty() ){
		for( hypro::Transition<Number>* transition : automaton.getTransitions() ){
			std::cout << transition << std::endl;
			transition->addLabel( hypro::Label( "a" ) );
			//automaton.addTransition( transition );
		}
	}
}

inline const char * const BoolToString(bool b){
	return b ? "true" : "false";
}

/*
// Save dot graph as PNG image
bool saveImageGV( std::string file_path ){
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    gvc = gvContext();
    fp = fopen((file_path + ".dot").c_str(), "r");
    g = agread(fp, 0);
    gvLayout(gvc, g, "dot");
    gvRender(gvc, g, "png", fopen((file_path+".png").c_str(), "w"));
    gvFreeLayout(gvc, g);
    agclose(g);
    return (gvFreeContext(gvc));
}*/



// Simulates input-output behavior of NN controller
// Specifies jump for hybrid automaton to take from current location
/*
hypro::Transition<Number> nnController( const hypro::HybridAutomaton<Number>& automaton, const hypro::Location<Number>& loc ){
	// std::set<hypro::Label, std::less<hypro::Label>, std::allocator<hypro::Label>> labs = automaton.getLabels();
	// Or rather directly by checking temperature threshold?
	hypro::Label lab = hypro::Label( "a" );
	auto& transitions = loc.getTransitions();
	
	for(const auto& t : transitions){
		hypro::Condition<Number> jumpEnablingSet = t->getJumpEnablingSet();
		std::cout << "Jump enabling set " << jumpEnablingSet << std::endl;
		if(jumpEnablingSet.isTrue() && not jumpEnablingSet.empty()){
			return *t;
		} 
	}
		
	if( loc.getInvariant().isTrue() ){
		//applyTimeEvolution();
		// choose self-loop
		std::cout << "Invariant is true" << std::endl;
	}
	return *loc.getTransitions().at(0);
}*/


int main() {
	// Assume inside directory hypro/build/
	const std::string& filename = "../../examples/input/thermostat_basic.model";

	std::cout << "Reading input hybrid automaton from " << filename << std::endl;

	//hypro::plotting::gnuplotSettings settings;
	//hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();


	auto [automaton, parsedSettings] = hypro::parseFlowstarFile<Number>( filename );

	std::cout << typeid(automaton).name() << std::endl;

	hypro::Settings settings = hypro::convert( parsedSettings );
	auto roots = hypro::makeRoots<hypro::PolyT<Number>, Number>( automaton );

	hypro::Location<Number>* l_on = automaton.getLocations().at(0);
	hypro::Location<Number>* l_off = automaton.getLocations().at(1);

	std::unique_ptr<hypro::Location<Number>> unique_l_on{ std::make_unique<hypro::Location<Number>>( *l_on ) };
	std::unique_ptr<hypro::Location<Number>> unique_l_off{ std::make_unique<hypro::Location<Number>>( *l_off ) };

	std::cout << "Locations of automaton: " << l_on << ", " << l_off << std::endl;

	std::cout << "Labels of automaton: " << automaton.getLabels() << std::endl;

	for (const auto& t : automaton.getTransitions()) {
		std::cout << "Transition of automaton: " << *t << std::endl;
	}

	
	//addLabels( automaton ); 

	// Add labels because none present
	automaton.getTransitions().at(0)->addLabel(hypro::Label( "a" ));
	automaton.getTransitions().at(1)->addLabel(hypro::Label( "a" ));

	
	std::cout << "Labels of automaton: " << automaton.getLabels() << std::endl;

	// Add self-transitions
	hypro::Transition<Number> self_on, self_off;
	self_on.setSource( l_on );
	self_on.setTarget( l_on );
	self_on.addLabel( hypro::Label( "b" ) );
	self_off.setSource( l_off );
	self_off.setTarget( l_off );
	self_off.addLabel( hypro::Label( "b" ) );
	
	std::cout << "Arrived here 1" << std::endl;

	l_on->addTransition( std::move( std::make_unique<hypro::Transition<Number>>( self_on ) ) );
	l_off->addTransition( std::move( std::make_unique<hypro::Transition<Number>>( self_off ) ) );

	//std::cout << l_on->rGetTransitions() << std::endl;
	
	//automaton.addTransition( *std::make_unique<hypro::Transition<Number>>( trans_on ) );
	//automaton.addTransition( std::make_unique<hypro::Transition<Number>>( trans_off ) );
	std::cout << "Arrived here" << std::endl;

	for(const auto& t : automaton.getTransitions()) {
		std::cout << "Transition of automaton: " << *t << std::endl;
	}

	std::cout << "Labels of automaton: " << automaton.getLabels() << std::endl;

	hypro::reachability::Reach<hypro::PolyT<Number>> reacher( automaton, settings.fixedParameters(), settings.strategy().front(), roots );

	//hypro::reachability::Reach<Number, hypro::Settings, hypro::State_t<Number> > reacher{ ha };
	//auto settings = reacher.settings();
	//settings.timeStep = carl::convert<double, hypro::tNumber>( 0.5 );
	//settings.timeBound = hypro::tNumber( 20 );
	//settings.jumpDepth = 10;
	//reacher.setSettings( settings );
	//reacher.setRepresentationType( hypro::HPolytope<Number> );

	//auto result = reacher.computeForwardReachability();
/*
	std::string dot_str = automaton.getDotRepresentation();
	std::ofstream out( "out" );
    out << dot_str;
    out.close();

	std::cout << BoolToString( saveImageGV( "out" ) ) << std::endl;
*/
	// Flowpipe-construction based approach
	int time_horizon = 10;
	int step_size = 2;

	hypro::Location<Number> cur_loc = *l_on;
	//hypro::State initState = hypro::State( l_on );
	/*
	for(int k = 0; k < time_horizon / step_size; k++) {
		// Get transition from controller
		hypro::Transition<Number> nextStep = nnController( automaton, cur_loc );
		// Take transition
		carl::Interval<tNumber> interval = carl::Interval<tNumber>( tNumber( k * step_size ), tNumber( (k+1) * step_size )); 
		hypro::TPathElement<Number, tNumber> pathElem = hypro::TPathElement( &nextStep, interval );
		//hypro::Path path = hypro::Path( std::initializer_list());
		// Q: How to take transition / evolve time?
		// Store new state as current state
	} */

	return 0;
}