#include "../hypro/config.h"
#include "../hypro/datastructures/hybridAutomata/LocationManager.h"
#include "../hypro/datastructures/hybridAutomata/Transition.h"
#include "../hypro/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../hypro/datastructures/Point.h"
#include "../hypro/representations/conversion/Converter.h"
#include "../hypro/algorithms/reachability/Reach.h"
#include "../hypro/util/Plotter.h"

int main(int argc, char const *argv[])
{
	using namespace hypro;
	using namespace carl;

	typedef cln::cl_RA Number;
	//carl::FLOAT_T<double>::setDefaultPrecision(FLOAT_PRECISION);
	//std::cout << "Set precision to " << carl::FLOAT_T<double>::defaultPrecision() << std::endl;
	typedef hypro::HPolytope<Number> Representation;

	LocationManager<Number>& lManager = LocationManager<Number>::getInstance();

	//Hybrid Automaton Objects: Locations, Transitions, Automaton itself
	Location<Number>* locOn = lManager.create();
	Location<Number>* locOff = lManager.create();
	hypro::Transition<Number>* onOff = new hypro::Transition<Number>();
	hypro::Transition<Number>* offOn = new hypro::Transition<Number>();
	HybridAutomaton<Number, Representation> hybrid = HybridAutomaton<Number, Representation>();

	//Other Objects: Vectors, Matrices, Guards...

	matrix_t<Number> onMat = matrix_t<Number>(3,3);
	matrix_t<Number> offMat = matrix_t<Number>(3,3);

	struct hypro::Transition<Number>::Guard guardOn;
	struct hypro::Transition<Number>::Guard guardOff;
	struct hypro::Transition<Number>::Reset reset;

	hypro::Location<Number>* locations[2];
	std::set<hypro::Location<Number>*> locSet;

	hypro::Location<Number>* init[1];
	std::set<hypro::Location<Number>*> initLocSet;

	hypro::Transition<Number>* transition[2];
	std::set<hypro::Transition<Number>*> transSet;
	std::set<hypro::Transition<Number>*> transOnSet;
	std::set<hypro::Transition<Number>*> transOffSet;

	//Init
	vector_t<Number> boxVec = vector_t<Number>(4,1);
	matrix_t<Number> boxMat = matrix_t<Number>(4,2);

	/*
	 * Locations
	 */

	vector_t<Number> invariantVec = vector_t<Number>(3,1);
	operator_e invariantOp;
	matrix_t<Number> invariantMat = matrix_t<Number>(3,2);

	invariantVec(0) = Number(23);
	invariantVec(1) = Number(-17);
	invariantVec(2) = Number(0);

	invariantOp = LEQ;

	invariantMat(0,0) = Number(1);
	invariantMat(0,1) = Number(0);
	invariantMat(1,0) = Number(-1);
	invariantMat(1,1) = Number(0);
	invariantMat(2,0) = Number(0);
	invariantMat(2,1) = Number(-1);

	locOn->setInvariant(invariantMat,invariantVec,invariantOp);
	locOff->setInvariant(invariantMat,invariantVec,invariantOp);

	onMat(0,0) = Number(carl::rationalize<Number>(-0.5));
	onMat(0,1) = Number(0);
	onMat(0,2) = Number(15);
	onMat(1,0) = Number(0);
	onMat(1,1) = Number(0);
	onMat(1,2) = Number(1);
	onMat(2,0) = Number(0);
	onMat(2,1) = Number(0);
	onMat(2,2) = Number(0);

	locOn->setActivityMat(onMat);

	offMat(0,0) = Number(carl::rationalize<Number>(-0.5));
	offMat(0,1) = Number(0);
	offMat(0,2) = Number(0);
	offMat(1,0) = Number(0);
	offMat(1,1) = Number(0);
	offMat(1,2) = Number(1);
	offMat(2,0) = Number(0);
	offMat(2,1) = Number(0);
	offMat(2,2) = Number(0);

	locOff->setActivityMat(offMat);

	/*
	 * Transitions
	 */

	operator_e guardOp;
	vector_t<Number> guardOnVec = vector_t<Number>(1,1);
	matrix_t<Number> guardOnMat = matrix_t<Number>(1,2);
	vector_t<Number> guardOffVec = vector_t<Number>(1,1);
	matrix_t<Number> guardOffMat = matrix_t<Number>(1,2);

	guardOp = LEQ;

	guardOnVec(0) = Number(-22);
	guardOnMat(0,0) = Number(-1);
	guardOnMat(0,1) = Number(0);
	guardOffVec(0) = Number(18);
	guardOffMat(0,0) = Number(1);
	guardOffMat(0,1) = Number(0);

	guardOn.op = guardOp;
	guardOn.mat = guardOnMat;
	guardOn.vec = guardOnVec;

	guardOff.op = guardOp;
	guardOff.mat = guardOffMat;
	guardOff.vec = guardOffVec;

	vector_t<Number> assignVec = vector_t<Number>(2,1);
	matrix_t<Number> assignMat = matrix_t<Number>(2,2);

	assignVec(0) = Number(0);
	assignVec(1) = Number(0);

	assignMat(0,0) = Number(1);
	assignMat(0,1) = Number(0);
	assignMat(1,0) = Number(0);
	assignMat(1,1) = Number(1);

	reset.translationVec = assignVec;
	reset.transformMat = assignMat;

	onOff->setGuard(guardOn);
	onOff->setSource(locOn);
	onOff->setTarget(locOff);
	onOff->setReset(reset);

	offOn->setGuard(guardOff);
	offOn->setSource(locOff);
	offOn->setTarget(locOn);
	offOn->setReset(reset);

	/*
	 * Hybrid Automaton
	 */
	locations[0] = locOn;
	locations[1] = locOff;

	locSet = std::set<hypro::Location<Number>*>(locations, locations+2);

	init[0] = locOn;

	initLocSet = std::set<hypro::Location<Number>*>(init, init+1);

	hybrid.setLocations(locSet);
	hybrid.setInitialLocations(initLocSet);

	transition[0] = onOff;
	transition[1] = offOn;

	transSet = std::set<hypro::Transition<Number>*>(transition, transition+2);
	transOnSet = std::set<hypro::Transition<Number>*>(transition, transition+1);
	transOffSet = std::set<hypro::Transition<Number>*>(transition+1, transition+2);

	hybrid.setTransitions(transSet);
	locOn->setTransitions(transOnSet);
	locOff->setTransitions(transOffSet);

	// Polytope for InitialValuation & Guard Assignment

	// create Box (note: 3rd variable is for the constant factor)
	boxVec(0) = Number(carl::rationalize<Number>(20.01));
	boxVec(1) = Number(carl::rationalize<Number>(-19.99));
	boxVec(2) = Number(carl::rationalize<Number>(0.01));
	boxVec(3) = Number(carl::rationalize<Number>(0.01));

	boxMat(0,0) = Number(1);
	boxMat(0,1) = Number(0);
	boxMat(1,0) = Number(-1);
	boxMat(1,1) = Number(0);
	boxMat(2,0) = Number(0);
	boxMat(2,1) = Number(1);
	boxMat(3,0) = Number(0);
	boxMat(3,1) = Number(-1);

	Representation poly(boxMat,boxVec);

	hybrid.setInitialValuation(poly);

	std::vector<std::vector<Representation>> flowpipes;

	hypro::reachability::Reach<Number, Representation> reacher(hybrid);
	std::set<std::size_t> flowpipeIndices = reacher.computeForwardReachability();

	std::cout << "FP indices: " << flowpipeIndices << std::endl;

	std::cout << "Generated flowpipe, start plotting." << std::endl;

	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	plotter.setFilename("out");

	for(auto& index : flowpipeIndices){
		std::vector<Representation> flowpipe = reacher.getFlowpipe(index);

		// Plot flowpipe
		unsigned count = 1;
		unsigned maxCount = flowpipe.size();
		for(auto& poly : flowpipe) {
			//std::cout << "Flowpipe segment to be converted: " << std::endl;
			//poly.print();
			std::vector<Point<Number>> points = poly.vertices();
			//std::cout << "points.size() = " << points.size() << std::endl;
			if(!points.empty() && points.size() > 2) {
				//std::cout << "Polycount: " << count << std::endl;
				for(auto& point : points) {
		 			//std::cout << "reduce " << point << " to ";
					point.reduceDimension(2);
					//std::cout << point << std::endl;
				}
				plotter.addObject(points);
				std::cout << "\r Flowpipe "<< index <<": Added object " << count << "/" << maxCount << std::flush;
				points.clear();
				++count;
			}
		}
}

	std::cout << std::endl;
	plotter.plot2d();
	plotter.plotTex();

	return 0;
}
