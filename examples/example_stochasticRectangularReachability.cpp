/**
 * @brief Example file which shows how to instanciate a concrete worker out of
 * context handlers.
 */

#include <algorithms/reachability/analyzer/StochasticRectangularAnalyzer.h>
#include <iostream>
#include <representations/GeometricObjectBase.h>
#include <typeinfo>

int main() {
	// typedefs
	using Number = double;
	using State = hypro::State<Number, hypro::CarlPolytope<Number>>;
 	// using Matrix = hypro::matrix_t<Number>;
  	// using Vector = hypro::vector_t<Number>;

	// variables
	carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex( 0 );
	// carl::Variable y = hypro::VariablePool::getInstance().carlVarByIndex( 1 );
	// rectangular dynamics
	std::map<carl::Variable, carl::Interval<Number>> dynamics;
	dynamics.emplace( std::make_pair( x, carl::Interval<Number>( 1, 2 ) ) );
	// dynamics.emplace( std::make_pair( y, carl::Interval<Number>( 0, 0 ) ) );
	std::map<carl::Variable, carl::Interval<Number>> dynamics2;
	dynamics2.emplace( std::make_pair( x, carl::Interval<Number>( 3, 5 ) ) );
	// dynamics2.emplace( std::make_pair( y, carl::Interval<Number>( 2, 4 ) ) );

	// hybrid automaton instance
	hypro::StochasticHybridAutomaton<Number> ha;

	// create locations with rectangular flow and probability distribution
	hypro::StochasticLocation<Number> loc1;
	hypro::rectangularFlow<Number> flow( dynamics );
	loc1.setRectangularFlow( flow );
    hypro::matrix_t<Number> probDistribution = hypro::matrix_t<Number>( 1, 2 );
    probDistribution << 0, 0.1;
    loc1.setLocationDistribution( probDistribution );

	hypro::StochasticLocation<Number> loc2;
	hypro::rectangularFlow<Number> flow2( dynamics2 );
	loc2.setRectangularFlow( flow2 );
    hypro::matrix_t<Number> probDistribution2 = hypro::matrix_t<Number>( 1, 2 );
    probDistribution2 << 0, 0.2;
    loc1.setLocationDistribution( probDistribution2 );

	// create transitions
	std::unique_ptr<hypro::StochasticTransition<Number>> trans =
    	std::make_unique<hypro::StochasticTransition<Number>>();
	
	// guard
	// hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>( 4, 2 );
	// guardConstraints << 1, 0, -1, 0, 0, 0, 0, 0;
	// hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>( 4 );
	// guardConstants << 10, -4, 0, 0;
	// hypro::Condition<Number> guard(guardConstraints,guardConstants);
	hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>( 4, 1 );
	guardConstraints << 1, -1;
	hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>( 4 );
	guardConstants << 10, -4;
	hypro::Condition<Number> guard(guardConstraints,guardConstants);

	// reset function
	
	// interval representation
	// std::vector<carl::Interval<Number>> intervalReset;
	// intervalReset.emplace_back( carl::Interval<Number>( -2, 2 ) );
	// intervalReset.emplace_back( carl::Interval<Number>( -3, 3 ) );
	// hypro::Reset<Number> reset;
	// reset.setIntervals( intervalReset );

	// matrix representation
	// hypro::matrix_t<Number> resetConstraints = hypro::matrix_t<Number>( 4, 2 );
	// resetConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
	// hypro::vector_t<Number> resetConstants = hypro::vector_t<Number>( 4 );
	// resetConstants << 1, 1, 2, 2;
	// hypro::Reset<Number> reset(resetConstraints,resetConstants);
	hypro::matrix_t<Number> resetConstraints = hypro::matrix_t<Number>( 2, 1 );
	resetConstraints << 1, -1;
	hypro::vector_t<Number> resetConstants = hypro::vector_t<Number>( 2 );
	resetConstants << 1, 1;
	hypro::Reset<Number> reset(resetConstraints,resetConstants);

    // weight
    Number weight = 2;

	// setup transition
	trans->setGuard(guard);
	trans->setSource(&loc1);
	trans->setTarget(&loc2);
	trans->setReset(reset);
    trans->setTransitionWeight(weight);

	std::unique_ptr<hypro::StochasticTransition<Number>> trans2 =
    	std::make_unique<hypro::StochasticTransition<Number>>();
	
	hypro::matrix_t<Number> guardConstraints2 = hypro::matrix_t<Number>( 2, 1 );
	guardConstraints2 << 1, -1;
	hypro::vector_t<Number> guardConstants2 = hypro::vector_t<Number>( 2 );
	guardConstants2 << 5, 0;
	hypro::Condition<Number> guard2(guardConstraints2,guardConstants2);

	// reset function
	hypro::Reset<Number> reset2(resetConstraints,resetConstants);

    // weight
    Number weight2 = 2;

	// setup transition
	trans2->setGuard(guard2);
	trans2->setSource(&loc1);
	trans2->setTarget(&loc1);
	trans2->setReset(reset2);
    trans2->setTransitionWeight(weight2);

	// add defined transition to location
	loc1.addTransition(std::move(trans));
	loc1.addTransition(std::move(trans2));

	// add location
	std::map<const hypro::StochasticLocation<Number>*, std::size_t> locationMapping;
	ha.addLocation( loc1 );
	locationMapping[&loc1] = ha.getLocations().size() - 1;
	ha.addLocation( loc2 );
	locationMapping[&loc2] = ha.getLocations().size() - 1;

	// initial set is a unit box
	// hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>( 4, 2 );
	// constraints << 1, 0, -1, 0, 0, 1, 0, -1;
	// hypro::vector_t<Number> constants = hypro::vector_t<Number>( 4 );
	// constants << 1, 1, 2, 2;
	hypro::matrix_t<Number> constraints = hypro::matrix_t<Number>( 2, 1 );
	constraints << 1, -1;
	hypro::vector_t<Number> constants = hypro::vector_t<Number>( 2 );
	constants << 1, 1;
	// hypro::matrix_t<Number> constraints2 = hypro::matrix_t<Number>( 4, 2 );
	// constraints2 << 1, 0, -1, 0, 0, 1, 0, -1;
	// hypro::vector_t<Number> constants2 = hypro::vector_t<Number>( 4 );
	// constants2 << 2, 2, 2, 2;

	// create and add initial state
    hypro::StochasticLocation<Number>* lptr1 = dynamic_cast<hypro::StochasticLocation<Number>*>(ha.getLocations()[locationMapping[&loc1]]);
    // std::cout << "l1 is: " << ha.getLocations()[locationMapping[&loc1]] << std::endl
    //           << "sto_l1 is: " << lptr1 <<std::endl;
	ha.addProbInitialState( lptr1, hypro::Condition<Number>( constraints, constants ), 1 );

	// setup local bad state
	// hypro::matrix_t<Number> localBadConstraints = hypro::matrix_t<Number>( 4, 2 );
	// localBadConstraints << 1, 0, -1, 0, 0, 0, 0, 0;
	// hypro::vector_t<Number> localBadConstants = hypro::vector_t<Number>( 4 );
	// localBadConstants << 6, -4, 0, 0;
	hypro::matrix_t<Number> localBadConstraints = hypro::matrix_t<Number>( 2, 1 );
	localBadConstraints << 1, -1;
	hypro::vector_t<Number> localBadConstants = hypro::vector_t<Number>( 2 );
	localBadConstants << 6, -4;
	ha.addLocalBadState( ha.getLocations()[locationMapping[&loc1]], hypro::Condition<Number>( localBadConstraints, localBadConstants ) );

	// setup global bad state
	hypro::matrix_t<Number> globalBadConstraints = hypro::matrix_t<Number>( 4, 2 );
	globalBadConstraints << 0, 0, -1, 0, 0, 0, 0, 0;
	hypro::vector_t<Number> globalBadConstants = hypro::vector_t<Number>( 4 );
	globalBadConstants << 0, -10, 0, 0;
	// ha.addGlobalBadState( hypro::Condition<Number>( globalBadConstraints, globalBadConstants ) );

	// std::cout << "HA is: " << std::endl  << ha << std::endl;
    
	// create settings
	std::vector<hypro::AnalysisParameters> strategy;
	strategy.emplace_back( hypro::AnalysisParameters{ mpq_class( 1 ) / mpq_class( 100 ), hypro::AGG_SETTING::NO_AGG, -1, hypro::representation_name::carl_polytope, 0, false, 0, hypro::REACH_SETTING::FORWARD } );
	hypro::Settings settings;
	settings.setStrategy( strategy );

	// call to analysis core
	hypro::StochasticRectangularAnalyzer<State> analyzer{ ha, settings };
	analyzer.run();

	// if ( result == hypro::REACHABILITY_RESULT::UNKNOWN ) {
	// 	std::cout << "Could not verify safety." << std::endl;
	// } else {
	// 	std::cout << "The model is safe." << std::endl;
	// }

	// output computed sets
	for ( const auto& fp : analyzer.getFlowpipes() ) {
		for ( const auto& segment : fp ) {
			std::cout << segment << std::endl;
		}
	}

	return 0;
}
