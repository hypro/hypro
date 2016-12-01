/**
 * \example example_bouncingBall.cpp
 * An example file showing how to construct the automaton for a bouncing ball system and afterwards determine the set of reachable states
 * for this system using H-polytopes as a state set representation.
 */

#include "config.h"
#include "datastructures/hybridAutomata/LocationManager.h"
#include "datastructures/hybridAutomata/Transition.h"
#include "datastructures/hybridAutomata/HybridAutomaton.h"
#include "datastructures/Point.h"
#include "representations/GeometricObject.h"
#include "algorithms/reachability/Reach.h"
#include "util/Plotter.h"

int main()
{
	using namespace hypro;
	using namespace carl;

	// typedefs for simplification.
	typedef mpq_class Number;
	typedef hypro::HPolytope<Number> Representation;

	// LocationManager holds all created locations and allows to create new locations.
	LocationManager<Number>& lManager = LocationManager<Number>::getInstance();

	// create the discrete structure of the automaton and the automaton itself.
	Location<Number>* loc1 = lManager.create();
	hypro::Transition<Number>* trans = new hypro::Transition<Number>();
	HybridAutomaton<Number> bBallAutomaton = HybridAutomaton<Number>();

	// matrix defining the flow (note: 3rd dimension for constant parts).
	matrix_t<Number> flowMatrix = matrix_t<Number>(3,3);

	// location parameter setting.
	// creation of the invariant.
	matrix_t<Number> invariantMat = matrix_t<Number>(1,2);
	vector_t<Number> invariantVec = vector_t<Number>(1);
	struct Location<Number>::Invariant inv;

	invariantVec(0) = Number(0);

	invariantMat(0,0) = Number(-1);
	invariantMat(0,1) = Number(0);

	loc1->setInvariant(invariantMat,invariantVec);

	// setup flow matrix (3x3, we add an artificial dimension to cope with constants).
	flowMatrix(0,0) = Number(0);
	flowMatrix(0,1) = Number(1);
	flowMatrix(0,2) = Number(0);
	flowMatrix(1,0) = Number(0);
	flowMatrix(1,1) = Number(0);
	flowMatrix(1,2) = Number(carl::rationalize<Number>(-9.81));
	flowMatrix(2,0) = Number(0);
	flowMatrix(2,1) = Number(0);
	flowMatrix(2,2) = Number(0);

	loc1->setFlow(flowMatrix);

	// setup of the transition.
	// guard
	typename Transition<Number>::Guard guard;
	matrix_t<Number> guardMat = matrix_t<Number>(3,2);
	vector_t<Number> guardVec = vector_t<Number>(3);

	guardVec(0) = Number(0);
	guardVec(1) = Number(0);
	guardVec(2) = Number(0);

	guardMat(0,0) = Number(1);
	guardMat(0,1) = Number(0);
	guardMat(1,0) = Number(-1);
	guardMat(1,1) = Number(0);
	guardMat(2,0) = Number(0);
	guardMat(2,1) = Number(1);

	guard.mat = guardMat;
	guard.vec = guardVec;

	// reset function
	typename Transition<Number>::Reset reset;
	vector_t<Number> constantReset = vector_t<Number>(2,1);
	matrix_t<Number> linearReset = matrix_t<Number>(2,2);

	constantReset(0) = Number(0);
	constantReset(1) = Number(0);

	linearReset(0,0) = Number(1);
	linearReset(0,1) = Number(0);
	linearReset(1,0) = Number(0);
	linearReset(1,1) = Number(carl::rationalize<Number>(-0.9));

	reset.vec = constantReset;
	reset.mat = linearReset;

	// setup transition
	trans->setAggregation(Aggregation::parallelotopeAgg);
	trans->setGuard(guard);
	trans->setSource(loc1);
	trans->setTarget(loc1);
	trans->setReset(reset);


	// add defined location and transition to the automaton.
	bBallAutomaton.addLocation(loc1);
	bBallAutomaton.addTransition(trans);
	loc1->addTransition(trans);

	// create Box holding the initial set.
	matrix_t<Number> boxMat = matrix_t<Number>(4,2);
	vector_t<Number> boxVec = vector_t<Number>(4);

	boxVec(0) = Number(carl::rationalize<Number>(10.2));
	boxVec(1) = Number(-10);
	boxVec(2) = Number(0);
	boxVec(3) = Number(0);

	boxMat(0,0) = Number(1);
	boxMat(0,1) = Number(0);
	boxMat(1,0) = Number(-1);
	boxMat(1,1) = Number(0);
	boxMat(2,0) = Number(0);
	boxMat(2,1) = Number(1);
	boxMat(3,0) = Number(0);
	boxMat(3,1) = Number(-1);

	// create initial state.
	RawState<Number> initialState;
	initialState.location = loc1;
	initialState.set = std::make_pair(boxMat, boxVec);
	bBallAutomaton.addInitialState(initialState);

	// vector of sets to collect flowpipes (which are again a vector of sets).
	std::vector<std::vector<Representation>> flowpipes;

	// instanciate reachability analysis algorithm.
	hypro::reachability::Reach<Number, Representation> reacher(bBallAutomaton);
	hypro::reachability::ReachabilitySettings<Number> settings = reacher.settings();
	settings.timeStep = carl::convert<double,Number>(0.01);
	settings.timeBound = Number(3);
	settings.jumpDepth = 3;
	reacher.setSettings(settings);

	// perform reachability analysis.
	std::vector<std::pair<unsigned, reachability::flowpipe_t<Representation>>> flowpipeIndices = reacher.computeForwardReachability();

	// plot flowpipes.
	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	plotter.setFilename("bouncingBall");
	for(auto& indexPair : flowpipeIndices){
		std::vector<Representation> flowpipe = indexPair.second;
		// Plot single flowpipe
		for(auto& poly : flowpipe) {
			std::vector<Point<Number>> points = poly.vertices();
			if(!points.empty() && points.size() > 2) {
				for(auto& point : points) {
					point.reduceDimension(2);
				}
				plotter.addObject(points);
				points.clear();
			}
		}
	}

	// write output.
	plotter.plot2d();

	return 0;
}
