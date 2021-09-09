/**
 * \example example_bouncingBall.cpp
 * An example file showing how to construct the automaton for a bouncing ball
 * system and afterwards determine the set of reachable states for this system
 * using H-polytopes as a state set representation.
 */

#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/config.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/Point.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>

int main() {
	using namespace hypro;

	// typedefs for simplification.
	using Number = mpq_class;
	using Representation = hypro::HPolytope<Number>;

	// create the discrete structure of the automaton and the automaton itself.
	HybridAutomaton<Number> bBallAutomaton = HybridAutomaton<Number>();
	Location<Number>* loc1 = bBallAutomaton.createLocation();
	Transition<Number>* trans = loc1->createTransition(loc1);

	// matrix defining the flow (note: 3rd dimension for constant parts).
	matrix_t<Number> flowMatrix = matrix_t<Number>( 3, 3 );

	// location parameter setting.
	// creation of the invariant.
	matrix_t<Number> invariantMat = matrix_t<Number>( 1, 2 );
	vector_t<Number> invariantVec = vector_t<Number>( 1 );

	invariantVec( 0 ) = Number( 0 );

	invariantMat( 0, 0 ) = Number( -1 );
	invariantMat( 0, 1 ) = Number( 0 );

	Condition<Number> inv( invariantMat, invariantVec );

	loc1->setInvariant( inv );

	// setup flow matrix (3x3, we add an artificial dimension to cope with
	// constants).
	flowMatrix( 0, 0 ) = Number( 0 );
	flowMatrix( 0, 1 ) = Number( 1 );
	flowMatrix( 0, 2 ) = Number( 0 );
	flowMatrix( 1, 0 ) = Number( 0 );
	flowMatrix( 1, 1 ) = Number( 0 );
	flowMatrix( 1, 2 ) = Number( carl::rationalize<Number>( -9.81 ) );
	flowMatrix( 2, 0 ) = Number( 0 );
	flowMatrix( 2, 1 ) = Number( 0 );
	flowMatrix( 2, 2 ) = Number( 0 );

	loc1->setFlow( flowMatrix );

	// setup of the transition.
	// guard
	Condition<Number> guard;
	matrix_t<Number> guardMat = matrix_t<Number>( 3, 2 );
	vector_t<Number> guardVec = vector_t<Number>( 3 );

	guardVec( 0 ) = Number( 0 );
	guardVec( 1 ) = Number( 0 );
	guardVec( 2 ) = Number( 0 );

	guardMat( 0, 0 ) = Number( 1 );
	guardMat( 0, 1 ) = Number( 0 );
	guardMat( 1, 0 ) = Number( -1 );
	guardMat( 1, 1 ) = Number( 0 );
	guardMat( 2, 0 ) = Number( 0 );
	guardMat( 2, 1 ) = Number( 1 );

	guard.setMatrix( guardMat );
	guard.setVector( guardVec );

	// reset function
	Reset<Number> reset;
	vector_t<Number> constantReset = vector_t<Number>( 2, 1 );
	matrix_t<Number> linearReset = matrix_t<Number>( 2, 2 );

	constantReset( 0 ) = Number( 0 );
	constantReset( 1 ) = Number( 0 );

	linearReset( 0, 0 ) = Number( 1 );
	linearReset( 0, 1 ) = Number( 0 );
	linearReset( 1, 0 ) = Number( 0 );
	linearReset( 1, 1 ) = Number( carl::rationalize<Number>( -0.9 ) );

	reset.setVector( constantReset );
	reset.setMatrix( linearReset );

	// setup transition
	trans->setAggregation( Aggregation::aggregation );
	trans->setGuard( guard );
	trans->setSource( loc1 );
	trans->setTarget( loc1 );
	trans->setReset( reset );

	// create Box holding the initial set.
	matrix_t<Number> boxMat = matrix_t<Number>( 4, 2 );
	vector_t<Number> boxVec = vector_t<Number>( 4 );

	boxVec( 0 ) = Number( carl::rationalize<Number>( 10.2 ) );
	boxVec( 1 ) = Number( -10 );
	boxVec( 2 ) = Number( 0 );
	boxVec( 3 ) = Number( 0 );

	boxMat( 0, 0 ) = Number( 1 );
	boxMat( 0, 1 ) = Number( 0 );
	boxMat( 1, 0 ) = Number( -1 );
	boxMat( 1, 1 ) = Number( 0 );
	boxMat( 2, 0 ) = Number( 0 );
	boxMat( 2, 1 ) = Number( 1 );
	boxMat( 3, 0 ) = Number( 0 );
	boxMat( 3, 1 ) = Number( -1 );

	// create initial state.
	bBallAutomaton.addInitialState( loc1, Condition<Number>( boxMat, boxVec ) );

	// set settings
	hypro::FixedAnalysisParameters fixedParameters;
	fixedParameters.jumpDepth = 3;
	fixedParameters.localTimeHorizon = 5;
	fixedParameters.fixedTimeStep = tNumber( 1 ) / tNumber( 100 );

	hypro::AnalysisParameters analysisParameters;
	analysisParameters.timeStep = tNumber( 1 ) / tNumber( 100 );
	analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
	analysisParameters.representation_type = hypro::representation_name::polytope_h;

	hypro::Settings settings{ {}, fixedParameters, { analysisParameters } };

	// initialize reachability tree
	auto roots = makeRoots<Representation,Number>( bBallAutomaton );

	// instanciate reachability analysis class
	hypro::reachability::Reach<Representation> reacher{ bBallAutomaton, fixedParameters, analysisParameters, roots };

	// perform reachability analysis.
	REACHABILITY_RESULT res = reacher.computeForwardReachability();
	std::cout << "Reachability result: " << res << std::endl;

	// plot flowpipes.
	std::cout << "Start plotting ... ";
	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	plotter.setFilename( "bouncingBall" );
	for(const auto& node : preorder(roots)) {
		for(const auto& state_set : node.getFlowpipe()) {
			plotter.addObject(state_set.projectOn({0,1}).vertices());
		}
	}
	std::cout << "done." << std::endl;

	// write output.
	plotter.plot2d(PLOTTYPE::png);

	return 0;
}
