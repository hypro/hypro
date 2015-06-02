#include "../lib/config.h"
#include "../lib/datastructures/hybridAutomata/Location.h"
#include "../lib/datastructures/hybridAutomata/Transition.h"
#include "../lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include <carl/core/VariablePool.h>
#include "../lib/datastructures/Point.h"
#include "../lib/algorithms/reachability/forwardReachability.h"
#include "../lib/util/Plotter.h"

int main(int argc, char const *argv[])
{
	using namespace hypro;
	using namespace carl;

	//Hybrid Automaton Objects: Locations, Transitions, Automaton itself
	Location<FLOAT_T<double>>* loc1 = new Location<FLOAT_T<double>>();
	Location<FLOAT_T<double>>* loc2 = new Location<FLOAT_T<double>>();
	hypro::Transition<FLOAT_T<double>>* trans = new hypro::Transition<FLOAT_T<double>>();
	HybridAutomaton<FLOAT_T<double>, hypro::valuation_t<FLOAT_T<double>>> hybrid = HybridAutomaton<FLOAT_T<double>, hypro::valuation_t<FLOAT_T<double>>>();

	//Other Objects: Vectors, Matrices, Guards...
	vector_t<FLOAT_T<double>> invariantVec = vector_t<FLOAT_T<double>>(3,1);
	operator_e invariantOp;
	matrix_t<FLOAT_T<double>> invariantMat = matrix_t<FLOAT_T<double>>(3,3);
	struct Location<FLOAT_T<double>>::invariant inv;
	matrix_t<FLOAT_T<double>> locationMat = matrix_t<FLOAT_T<double>>(3,3);

	struct hypro::Transition<FLOAT_T<double>>::guard guard;

	struct hypro::Transition<FLOAT_T<double>>::assignment assign;

	hypro::Location<FLOAT_T<double>>* locations[2];
	std::set<hypro::Location<FLOAT_T<double>>*> locSet;

	hypro::Location<FLOAT_T<double>>* init[1];
	std::set<hypro::Location<FLOAT_T<double>>*> initLocSet;

	hypro::Transition<FLOAT_T<double>>* transition[1];
	std::set<hypro::Transition<FLOAT_T<double>>*> transSet;

	vector_t<FLOAT_T<double>> coordinates = vector_t<FLOAT_T<double>>(2,1);
	Point<FLOAT_T<double>> p1;
	hypro::Polytope<FLOAT_T<double>> poly;
	hypro::Polytope<FLOAT_T<double>> pPoly;

	//Box
	vector_t<FLOAT_T<double>> boxVec = vector_t<FLOAT_T<double>>(6,1);
	matrix_t<FLOAT_T<double>> boxMat = matrix_t<FLOAT_T<double>>(6,3);

	/*
	 * Location
	 */
	invariantVec(0) = 16;
	invariantVec(1) = 16;
	invariantVec(2) = 1;

	invariantOp = LEQ;

	invariantMat(0,0) = 1;
	invariantMat(0,1) = 0;
	invariantMat(0,2) = 0;
	invariantMat(1,0) = 0;
	invariantMat(1,1) = 1;
	invariantMat(1,2) = 0;
	invariantMat(2,0) = 0;
	invariantMat(2,1) = 0;
	invariantMat(2,2) = 1;

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
	locationMat(0,2) = 0;
	locationMat(1,0) = 4;
	locationMat(1,1) = -1;
	locationMat(1,2) = 0;
	locationMat(2,0) = 0;
	locationMat(2,1) = 0;
	locationMat(2,2) = 0;


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

	locSet = std::set<hypro::Location<FLOAT_T<double>>*>(locations, locations+2);

	init[0] = loc1;

	initLocSet = std::set<hypro::Location<FLOAT_T<double>>*>(init, init+1);

	hybrid.setLocations(locSet);
	hybrid.setInitialLocations(initLocSet);

	transition[0] = trans;

	transSet = std::set<hypro::Transition<FLOAT_T<double>>*>(transition, transition+1);

	hybrid.setTransitions(transSet);
	loc1->setTransitions(transSet);

	//Polytope for InitialValuation & Guard Assignment

	//create Box (note: 3rd variable is for the constant factor)
	boxVec(0) = 1.1;
	boxVec(1) = -0.9;
	boxVec(2) = 0.1;
	boxVec(3) = 0.1;
	boxVec(4) = 1;
	boxVec(5) = -1;

	boxMat(0,0) = 1;
	boxMat(0,1) = 0;
	boxMat(0,2) = 0;
	boxMat(1,0) = -1;
	boxMat(1,1) = 0;
	boxMat(1,2) = 0;
	boxMat(2,0) = 0;
	boxMat(2,1) = 1;
	boxMat(2,2) = 0;
	boxMat(3,0) = 0;
	boxMat(3,1) = -1;
	boxMat(3,2) = 0;
	boxMat(4,0) = 0;
	boxMat(4,1) = 0;
	boxMat(4,2) = 1;
	boxMat(5,0) = 0;
	boxMat(5,1) = 0;
	boxMat(5,2) = -1;

	poly = Polytope<FLOAT_T<double>>(boxMat,boxVec);

	hybrid.setValuation(poly);

	std::vector<hypro::valuation_t<FLOAT_T<double>>> flowpipe;

   	std::cout << "original Polytope (Box): ";
    poly.print();

	flowpipe = forwardReachability::computeForwardTimeClosure(*loc1, poly);

   	//check size of flowpipe
   	int size = flowpipe.size();

   	std::cout <<  "Flowpipe size: ";
   	std::cout << size << std::endl;

   	hypro::Plotter<FLOAT_T<double>>& plotter = hypro::Plotter<FLOAT_T<double>>::getInstance();
	plotter.setFilename("out");

	unsigned count = 1;
   	for(auto& poly : flowpipe) {
   		std::cout << "Flowpipe segment to be converted: " << std::endl;
   		poly.print();
   		std::cout << std::endl;
   		std::vector<Point<FLOAT_T<double>>> points = poly.points();
   		if(!points.empty()) {
   			std::cout << "Polycount: " << count << std::endl;
   			for(auto& point : points) {
	   			point.reduceDimension(2);
	   			std::cout << point << std::endl;
	   		}
	   		plotter.addObject(points);
	   		points.clear();
	   		++count;
   		}
   	}

   	plotter.plot2d();

	return 0;
}