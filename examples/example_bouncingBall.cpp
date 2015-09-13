#include "../lib/config.h"
#include "../lib/datastructures/hybridAutomata/LocationManager.h"
#include "../lib/datastructures/hybridAutomata/Transition.h"
#include "../lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../lib/datastructures/Point.h"
#include "../lib/algorithms/reachability/Reach.h"
#include "../lib/representations/Polytopes/HPolytope/HPolytope.h"
#include "../lib/representations/Polytopes/VPolytope/VPolytope.h"
#include "../lib/representations/SupportFunction/SupportFunction.h"
#include "../lib/representations/Box/Box.h"
#include "../lib/util/Plotter.h"

int main(int argc, char const *argv[])
{
	using namespace hypro;
	using namespace carl;

	typedef FLOAT_T<double> Number;
	//carl::FLOAT_T<double>::setDefaultPrecision(FLOAT_PRECISION);
	//std::cout << "Set precision to " << carl::FLOAT_T<double>::defaultPrecision() << std::endl;
	typedef hypro::HPolytope<Number> Representation;

	LocationManager<Number>& lManager = LocationManager<Number>::getInstance();

	//Hybrid Automaton Objects: Locations, Transitions, Automaton itself
	Location<Number>* loc1 = lManager.create();
	hypro::Transition<Number>* trans = new hypro::Transition<Number>();
	HybridAutomaton<Number, Representation> hybrid = HybridAutomaton<Number, Representation>();

	//Other Objects: Vectors, Matrices, Guards...

	matrix_t<Number> locationMat = matrix_t<Number>(3,3);

	struct hypro::Transition<Number>::Guard guard;
	struct hypro::Transition<Number>::Reset reset;

	hypro::Location<Number>* locations[1];
	std::set<hypro::Location<Number>*> locSet;

	hypro::Location<Number>* init[1];
	std::set<hypro::Location<Number>*> initLocSet;

	hypro::Transition<Number>* transition[1];
	std::set<hypro::Transition<Number>*> transSet;

	vector_t<Number> coordinates = vector_t<Number>(2,1);
	Point<Number> p1;

	//Box
	//vector_t<Number> boxVec = vector_t<Number>(6,1);
	vector_t<Number> boxVec = vector_t<Number>(4,1);
	//matrix_t<Number> boxMat = matrix_t<Number>(6,3);
	matrix_t<Number> boxMat = matrix_t<Number>(4,2);

	/*
	 * Location
	 */

	//vector_t<Number> invariantVec = vector_t<Number>(6,1);
	vector_t<Number> invariantVec = vector_t<Number>(4,1);
	operator_e invariantOp;
	//matrix_t<Number> invariantMat = matrix_t<Number>(6,3);
	matrix_t<Number> invariantMat = matrix_t<Number>(4,2);
	struct Location<Number>::Invariant inv;

	invariantVec(0) = 20;
	invariantVec(1) = 0;
	invariantVec(2) = 20;
	invariantVec(3) = 20;
	//invariantVec(4) = 1;
	//invariantVec(5) = 1;

	invariantOp = LEQ;

	invariantMat(0,0) = 1;
	invariantMat(0,1) = 0;
	//invariantMat(0,2) = 0;
	invariantMat(1,0) = -1;
	invariantMat(1,1) = 0;
	//invariantMat(1,2) = 0;
	invariantMat(2,0) = 0;
	invariantMat(2,1) = 1;
	//invariantMat(2,2) = 0;
	invariantMat(3,0) = 0;
	invariantMat(3,1) = -1;
	//invariantMat(3,2) = 0;
	// invariantMat(4,0) = 0;
	// invariantMat(4,1) = 0;
	// invariantMat(4,2) = 1;
	// invariantMat(5,0) = 0;
	// invariantMat(5,1) = 0;
	// invariantMat(5,2) = -1;

	std::cout << invariantMat << std::endl;

	loc1->setInvariant(invariantMat,invariantVec,invariantOp);

	inv.op = invariantOp;
	inv.mat = invariantMat;
	inv.vec = invariantVec;


	locationMat(0,0) = 0;
	locationMat(0,1) = 1;
	locationMat(0,2) = 0;
	locationMat(1,0) = 0;
	locationMat(1,1) = 0;
	locationMat(1,2) = -9.81;
	locationMat(2,0) = 0;
	locationMat(2,1) = 0;
	locationMat(2,2) = 0;


	loc1->setActivityMat(locationMat);

	/*
	 * Transition
	 */

	vector_t<Number> guardVec = vector_t<Number>(3,1);
	operator_e guardOp;
	matrix_t<Number> guardMat = matrix_t<Number>(3,3);

	guardVec(0) = 0;
	guardVec(1) = 0;
	guardVec(2) = 0;

	guardOp = LEQ;

	guardMat(0,0) = 1;
	guardMat(0,1) = 0;
	guardMat(0,2) = 0;
	guardMat(1,0) = -1;
	guardMat(1,1) = 0;
	guardMat(1,2) = 0;
	guardMat(2,0) = 0;
	guardMat(2,1) = 1;
	guardMat(2,2) = 0;


	guard.op = guardOp;
	guard.mat = guardMat;
	guard.vec = guardVec;

	vector_t<Number> assignVec = vector_t<Number>(3,1);
	matrix_t<Number> assignMat = matrix_t<Number>(3,3);

	assignVec(0) = 0;
	assignVec(1) = 0;
	assignVec(2) = 0;

	assignMat(0,0) = 1;
	assignMat(0,1) = 0;
	assignMat(0,2) = 0;
	assignMat(1,0) = 0;
	assignMat(1,1) = -0.9;
	assignMat(1,2) = 0;
	assignMat(2,0) = 0;
	assignMat(2,1) = 0;
	assignMat(2,2) = 1;

	reset.translationVec = assignVec;
	reset.transformMat = assignMat;

	trans->setGuard(guard);
	trans->setSource(loc1);
	trans->setTarget(loc1);
	trans->setReset(reset);

	/*
	 * Hybrid Automaton
	 */
	locations[0] = loc1;

	locSet = std::set<hypro::Location<Number>*>(locations, locations+1);

	init[0] = loc1;

	initLocSet = std::set<hypro::Location<Number>*>(init, init+1);

	hybrid.setLocations(locSet);
	hybrid.setInitialLocations(initLocSet);

	transition[0] = trans;

	transSet = std::set<hypro::Transition<Number>*>(transition, transition+1);

	hybrid.setTransitions(transSet);
	loc1->setTransitions(transSet);

	//Polytope for InitialValuation & Guard Assignment

	//create Box (note: 3rd variable is for the constant factor)
	boxVec(0) = 10.2;
	boxVec(1) = -10;
	boxVec(2) = -0.009;
	boxVec(3) = 0.01;
	//boxVec(4) = 1;
	//boxVec(5) = -1;

	boxMat(0,0) = 1;
	boxMat(0,1) = 0;
	//boxMat(0,2) = 0;
	boxMat(1,0) = -1;
	boxMat(1,1) = 0;
	//boxMat(1,2) = 0;
	boxMat(2,0) = 0;
	boxMat(2,1) = 1;
	//boxMat(2,2) = 0;
	boxMat(3,0) = 0;
	boxMat(3,1) = -1;
	//boxMat(3,2) = 0;
	// boxMat(4,0) = 0;
	// boxMat(4,1) = 0;
	// boxMat(4,2) = 1;
	// boxMat(5,0) = 0;
	// boxMat(5,1) = 0;
	// boxMat(5,2) = -1;

	Representation poly(boxMat,boxVec);

	hybrid.setInitialValuation(poly);

	std::vector<std::vector<Representation>> flowpipes;

	//std::cout << "original Polytope (Box): ";
	//poly.print();

	// flowpipe = forwardReachability::computeForwardTimeClosure(*loc1, poly);
	// flowpipes = forwardReachability::computeForwardsReachability(hybrid);

	hypro::reachability::Reach<Number, Representation> reacher(hybrid);

	std::cout << "Generated flowpipe, start plotting." << std::endl;

	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.setFilename("out");

	for(auto& flowpipe : flowpipes) {
		unsigned count = 1;
		unsigned maxCount = flowpipe.size();
		for(auto& poly : flowpipe) {
			std::cout << "Flowpipe segment to be converted: " << std::endl;
			poly.print();
			std::vector<Point<Number>> points = poly.vertices();
			if(!points.empty() && points.size() > 2) {
				std::cout << "Polycount: " << count << std::endl;
				std::cout << "points.size() = " << points.size() << std::endl;
				for(auto& point : points) {
		// 			std::cout << "reduce " << point << " to ";
					point.reduceDimension(2);
					// 			std::cout << point << std::endl;
				}
				plotter.addObject(points);
				std::cout << "\rAdded object " << count << "/" << maxCount << std::flush;
				points.clear();
				++count;
			}
		}
	}
	std::cout << endl;

	plotter.plot2d();

	return 0;
}
