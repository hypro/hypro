
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/representations/GeometricObjectBase.h>

int main() {
	using Number = double;
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::Location<Number> loc = hypro::Location<Number>();
	hypro::Location<Number> loc2 = hypro::Location<Number>();

	std::unique_ptr<hypro::Location<Number>> unique_loc{ std::make_unique<hypro::Location<Number>>( loc ) };
	std::unique_ptr<hypro::Location<Number>> unique_loc2{ std::make_unique<hypro::Location<Number>>( loc2 ) };

	// flows
	Matrix flowMatrix = Matrix::Zero( 4, 4 );
	flowMatrix.col( 3 ) = Vector::Ones( 4 );
	flowMatrix( 3, 3 ) = 0;

	Matrix flowMatrix2 = Matrix::Zero( 4, 4 );
	flowMatrix2( 0, 3 ) = 1;

	// assign flows to locations
	unique_loc->setFlow( flowMatrix );
	unique_loc2->setFlow( flowMatrix2 );

	// transition
	hypro::Transition<Number> trans;
	trans.setAggregation( hypro::Aggregation::clustering );
	trans.setClusterBound( 5 );
	trans.setSource( unique_loc.get() );
	trans.setTarget( unique_loc2.get() );

	// write transition
	unique_loc->addTransition( std::make_unique<hypro::Transition<Number>>( trans ) );

	// initial state set
	Matrix initConstraints = Matrix( 6, 3 );
	Vector initConstants = Vector::Zero( 6 );

	initConstraints << 1, 0, 0,
		  -1, 0, 0,
		  0, 1, 0,
		  0, -1, 0,
		  0, 0, 1,
		  0, 0, -1;

	// create hybrid automaton
	hypro::HybridAutomaton<Number> ha;

	// write initial state
	ha.addInitialState( unique_loc.get(), hypro::Condition<Number>( initConstraints, initConstants ) );

	// write locations
	ha.addLocation( std::move( unique_loc ) );
	ha.addLocation( std::move( unique_loc2 ) );

	// call reachability analysis

	hypro::reachability::Reach<Number, hypro::reachability::ReachSettings, hypro::State_t<Number>> reacher{ ha };
	auto settings = reacher.settings();
	settings.timeStep = carl::convert<double, hypro::tNumber>( 0.5 );
	settings.timeBound = hypro::tNumber( 20 );
	settings.jumpDepth = 10;
	reacher.setSettings( settings );
	reacher.setRepresentationType( hypro::representation_name::polytope_h );

	std::vector<hypro::State_t<Number>> initialStates;
	for ( const auto& locationConditionPair : ha.getInitialStates() ) {
		hypro::State_t<Number> tmp{ locationConditionPair.first };
		tmp.setSet( hypro::HPolytope<Number>( locationConditionPair.second.getMatrix(),
											  locationConditionPair.second.getVector() ) );
		initialStates.emplace_back( std::move( tmp ) );
	}
	reacher.setInitialStates( std::move( initialStates ) );

	auto result = reacher.computeForwardReachability();

	return 0;
}
