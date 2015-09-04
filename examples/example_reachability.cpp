#include "../lib/config.h"
#include "../lib/datastructures/hybridAutomata/Location.h"
#include "../lib/datastructures/hybridAutomata/Transition.h"
#include "../lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include <carl/core/VariablePool.h>
#include "../lib/datastructures/Point.h"
#include "../lib/algorithms/reachability/forwardReachability.h"
#include "../lib/representations/Polytopes/HPolytope/HPolytope.h"
#include "../lib/representations/Polytopes/VPolytope/VPolytope.h"
#include "../lib/representations/SupportFunction/SupportFunction.h"
#include "../lib/representations/Box/Box.h"
#include "../lib/util/Plotter.h"

int main(int argc, char const *argv[])
{
	using namespace hypro;
	using namespace carl;

	typedef FLOAT_T<mpfr_t> Number;
	carl::FLOAT_T<mpfr_t>::setDefaultPrecision(FLOAT_PRECISION);
	std::cout << "Set precision to " << carl::FLOAT_T<mpfr_t>::defaultPrecision() << std::endl;
	typedef hypro::HPolytope<Number> Representation;


	//Hybrid Automaton Objects: Locations, Transitions, Automaton itself
	Location<Number>* loc1 = new Location<Number>();
	Location<Number>* loc2 = new Location<Number>();
	hypro::Transition<Number>* trans = new hypro::Transition<Number>();
	HybridAutomaton<Number, Representation> hybrid = HybridAutomaton<Number, Representation>();

	//Other Objects: Vectors, Matrices, Guards...
	vector_t<Number> invariantVec = vector_t<Number>(4,1);
	operator_e invariantOp;
	matrix_t<Number> invariantMat = matrix_t<Number>(4,2);
	struct Location<Number>::invariant inv;
	matrix_t<Number> locationMat = matrix_t<Number>(2,2);

	struct hypro::Transition<Number>::guard guard;

	struct hypro::Transition<Number>::assignment assign;

	hypro::Location<Number>* locations[2];
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
	invariantVec(0) = 16;
	invariantVec(1) = 16;
	invariantVec(2) = 16;
	invariantVec(3) = 16;

	invariantOp = LEQ;

	invariantMat(0,0) = 1;
	invariantMat(0,1) = 0;
	invariantMat(1,0) = -1;
	invariantMat(1,1) = 0;
	invariantMat(2,0) = 0;
	invariantMat(2,1) = 1;
	invariantMat(3,0) = 0;
	invariantMat(3,1) = -1;

	loc1->setInvariant(invariantMat,invariantVec,invariantOp);

	inv.op = invariantOp;
	inv.mat = invariantMat;
	inv.vec = invariantVec;

	loc2->setInvariant(inv);

	//note: 3rd variable is for the encoded constant factor
	//here: x' = 2, y'= 2, z' = 0  (x' := derivative)
	// locationMat(0,0) = 0.69314718056;
	// locationMat(0,1) = 0;
	// locationMat(0,2) = 0;
	// locationMat(1,0) = 0;
	// locationMat(1,1) = 0.69314718056;
	// locationMat(1,2) = 0;
	// locationMat(2,0) = 0;
	// locationMat(2,1) = 0;
	// locationMat(2,2) = 0;

	locationMat(0,0) = -1;
	locationMat(0,1) = -4;
	locationMat(1,0) = 4;
	locationMat(1,1) = -1;

	loc1->setActivityMat(locationMat);
	loc2->setActivityMat(locationMat);

	/*
	 * Transition
	 */
	guard.op = inv.op;
	guard.mat = inv.mat;
	guard.vec = inv.vec;

	assign.translationVec = inv.vec;
	assign.transformMat = inv.mat;

	trans->setGuard(guard);
	trans->setStartLoc(loc1);
	trans->setTargetLoc(loc2);
	trans->setAssignment(assign);

	/*
	 * Hybrid Automaton
	 */
	locations[0] = loc1;
	locations[1] = loc2;

	locSet = std::set<hypro::Location<Number>*>(locations, locations+2);

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
	boxVec(0) = 1.1;
	boxVec(1) = -0.9;
	boxVec(2) = 0.1;
	boxVec(3) = 0.1;
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
	//boxMat(4,0) = 0;
	//boxMat(4,1) = 0;
	//boxMat(4,2) = 1;
	//boxMat(5,0) = 0;
	//boxMat(5,1) = 0;
	//boxMat(5,2) = -1;



	Representation poly(boxMat,boxVec);

	hybrid.setValuation(poly);

	std::vector<Representation> flowpipe;

   	//std::cout << "original Polytope (Box): ";
    //poly.print();

	flowpipe = forwardReachability::computeForwardTimeClosure(*loc1, poly);

   	//check size of flowpipe
   	//int size = flowpipe.size();

   	//std::cout <<  "Flowpipe size: ";
   	//std::cout << size << std::endl;

   	std::cout << "Generated flowpipe, start plotting." << std::endl;

   	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.setFilename("out");

	unsigned count = 1;
	unsigned maxCount = flowpipe.size();
   	for(auto& poly : flowpipe) {
   		//std::cout << "Flowpipe segment to be converted: " << std::endl;
   		//poly.print();
   		std::vector<Point<Number>> points = poly.vertices();
   		if(!points.empty()) {
   			//std::cout << "Polycount: " << count << std::endl;
   			//std::cout << "points.size() = " << points.size() << std::endl;
   			for(auto& point : points) {
   				//std::cout << "reduce " << point << " to ";
	   			point.reduceDimension(2);
	   			//std::cout << point << std::endl;
	   		}
	   		plotter.addObject(points);
			std::cout << "\rAdded object " << count << "/" << maxCount << std::flush;
	   		points.clear();
	   		++count;
   		}
   	}
	std::cout << endl;

   	plotter.plot2d();

	return 0;
}
