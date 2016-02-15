#include <chrono>

#include "../lib/config.h"
#include "../lib/datastructures/hybridAutomata/LocationManager.h"
#include "../lib/datastructures/hybridAutomata/Transition.h"
#include "../lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../lib/datastructures/Point.h"
#include "../lib/representations/conversion/Converter.h"
#include "../lib/algorithms/reachability/Reach.h"
#include "../lib/util/Plotter.h"


int main(int argc, char const *argv[])
{
	using namespace hypro;
	using namespace carl;

	typedef cln::cl_RA Number;
	//carl::FLOAT_T<double>::setDefaultPrecision(FLOAT_PRECISION);
	//std::cout << "Set precision to " << carl::FLOAT_T<double>::defaultPrecision() << std::endl;
	typedef hypro::HPolytope<Number> Representation;

        std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
	LocationManager<Number>& lManager = LocationManager<Number>::getInstance();

	//Hybrid Automaton Objects: Locations, Transitions, Automaton itself
	Location<Number>* q1 = lManager.create();
	Location<Number>* q2 = lManager.create();
	Location<Number>* q3 = lManager.create();
	Location<Number>* q4 = lManager.create();
	Location<Number>* q5 = lManager.create();
	hypro::Transition<Number>* t12 = new hypro::Transition<Number>();
	hypro::Transition<Number>* t23 = new hypro::Transition<Number>();
	hypro::Transition<Number>* t34 = new hypro::Transition<Number>();
	hypro::Transition<Number>* t45 = new hypro::Transition<Number>();
	hypro::Transition<Number>* t51 = new hypro::Transition<Number>();
	HybridAutomaton<Number, Representation> hybrid = HybridAutomaton<Number, Representation>();

	//Other Objects: Vectors, Matrices, Guards...
	matrix_t<Number> q1Mat = matrix_t<Number>::Zero(6,6);
	matrix_t<Number> q2Mat = matrix_t<Number>::Zero(6,6);
	matrix_t<Number> q3Mat = matrix_t<Number>::Zero(6,6);
	matrix_t<Number> q4Mat = matrix_t<Number>::Zero(6,6);
	matrix_t<Number> q5Mat = matrix_t<Number>::Zero(6,6);

	struct hypro::Transition<Number>::Guard guard12;
	struct hypro::Transition<Number>::Guard guard23;
	struct hypro::Transition<Number>::Guard guard34;
	struct hypro::Transition<Number>::Guard guard45;
	struct hypro::Transition<Number>::Guard guard51;
	struct hypro::Transition<Number>::Reset reset12;
	struct hypro::Transition<Number>::Reset reset23;
	struct hypro::Transition<Number>::Reset reset34;
	struct hypro::Transition<Number>::Reset reset45;
	struct hypro::Transition<Number>::Reset reset51;

	hypro::Location<Number>* locations[5];
	std::set<hypro::Location<Number>*> locSet;

	hypro::Location<Number>* init[1];
	std::set<hypro::Location<Number>*> initLocSet;

	hypro::Transition<Number>* transition[5];
	std::set<hypro::Transition<Number>*> transSet;
	std::set<hypro::Transition<Number>*> transSet1;
	std::set<hypro::Transition<Number>*> transSet2;
	std::set<hypro::Transition<Number>*> transSet3;
	std::set<hypro::Transition<Number>*> transSet4;
	std::set<hypro::Transition<Number>*> transSet5;

	//Box for initial set
	vector_t<Number> boxVec = vector_t<Number>::Zero(10);
	matrix_t<Number> boxMat = matrix_t<Number>::Zero(10,5);

	/*
	 * Locations
	 */

	vector_t<Number> q1InvVec = vector_t<Number>::Zero(1);
	matrix_t<Number> q1InvMat = matrix_t<Number>::Zero(1,5);
  	vector_t<Number> q2InvVec = vector_t<Number>::Zero(1);
	matrix_t<Number> q2InvMat = matrix_t<Number>::Zero(1,5);
 	 vector_t<Number> q3InvVec = vector_t<Number>::Zero(1);
	matrix_t<Number> q3InvMat = matrix_t<Number>::Zero(1,5);
  	vector_t<Number> q4InvVec = vector_t<Number>::Zero(1);
	matrix_t<Number> q4InvMat = matrix_t<Number>::Zero(1,5);
  	vector_t<Number> q5InvVec = vector_t<Number>::Zero(1);
	matrix_t<Number> q5InvMat = matrix_t<Number>::Zero(1,5);
	operator_e invariantOp = LEQ;;

	q1InvVec(0) = Number(-3);
	q1InvMat(0,1) = Number(-1);
	q2InvVec(0) = Number(-2);
	q2InvMat(0,1) = Number(-1);
	q3InvVec(0) = Number(-1);
	q3InvMat(0,1) = Number(-1);
	q4InvVec(0) = Number(0);
	q4InvMat(0,1) = Number(-1);
	q5InvVec(0) = Number(1);
	q5InvMat(0,1) = Number(1);

	q1->setInvariant(q1InvMat,q1InvVec,invariantOp);
	q2->setInvariant(q2InvMat,q2InvVec,invariantOp);
	q3->setInvariant(q3InvMat,q3InvVec,invariantOp);
	q4->setInvariant(q4InvMat,q4InvVec,invariantOp);
	q5->setInvariant(q5InvMat,q5InvVec,invariantOp);

q1Mat(0,0) = Number(carl::rationalize<Number>(-0.8047));
q1Mat(0,1) = Number(carl::rationalize<Number>(+8.7420));
q1Mat(0,2) = Number(carl::rationalize<Number>(-2.4591));
q1Mat(0,3) = Number(carl::rationalize<Number>(-8.2714));
q1Mat(0,4) = Number(carl::rationalize<Number>(-1.8640));
q1Mat(0,5) = Number(carl::rationalize<Number>(-0.0845));

q1Mat(1,0) = Number(carl::rationalize<Number>(-8.6329));
q1Mat(1,1) = Number(carl::rationalize<Number>(-0.5860));
q1Mat(1,2) = Number(carl::rationalize<Number>(-2.1006));
q1Mat(1,3) = Number(carl::rationalize<Number>(+3.6035));
q1Mat(1,4) = Number(carl::rationalize<Number>(-1.8423));

q1Mat(2,0) = Number(carl::rationalize<Number>(2.4511));
q1Mat(2,1) = Number(carl::rationalize<Number>(+2.2394));
q1Mat(2,2) = Number(carl::rationalize<Number>(-0.7538));
q1Mat(2,3) = Number(carl::rationalize<Number>(-3.6934));
q1Mat(2,4) = Number(carl::rationalize<Number>(+2.4585));

q1Mat(3,0) = Number(carl::rationalize<Number>(8.3858));
q1Mat(3,1) = Number(carl::rationalize<Number>(-3.1739));
q1Mat(3,2) = Number(carl::rationalize<Number>(+3.7822));
q1Mat(3,3) = Number(carl::rationalize<Number>(-0.6249));
q1Mat(3,4) = Number(carl::rationalize<Number>(+1.8829));

q1Mat(4,0) = Number(carl::rationalize<Number>(1.8302));
q1Mat(4,1) = Number(carl::rationalize<Number>(+1.9869));
q1Mat(4,2) = Number(carl::rationalize<Number>(-2.4539));
q1Mat(4,3) = Number(carl::rationalize<Number>(-1.7726));
q1Mat(4,4) = Number(carl::rationalize<Number>(-0.7911));
q1Mat(4,5) = Number(carl::rationalize<Number>(-0.0845));


q2Mat(0,0) = Number(carl::rationalize<Number>(-0.8316));
q2Mat(0,1) = Number(carl::rationalize<Number>(+8.7658));
q2Mat(0,2) = Number(carl::rationalize<Number>(-2.4744));
q2Mat(0,3) = Number(carl::rationalize<Number>(-8.2608));
q2Mat(0,4) = Number(carl::rationalize<Number>(-1.9033));
q2Mat(0,5) = Number(carl::rationalize<Number>(-0.0845));

q2Mat(1,0) = Number(carl::rationalize<Number>(-0.8316));
q2Mat(1,1) = Number(carl::rationalize<Number>(-0.5860));
q2Mat(1,2) = Number(carl::rationalize<Number>(-2.1006));
q2Mat(1,3) = Number(carl::rationalize<Number>(+3.6035));
q2Mat(1,4) = Number(carl::rationalize<Number>(-1.8423));

q2Mat(2,0) = Number(carl::rationalize<Number>(2.4511));
q2Mat(2,1) = Number(carl::rationalize<Number>(+2.2394));
q2Mat(2,2) = Number(carl::rationalize<Number>(-0.7538));
q2Mat(2,3) = Number(carl::rationalize<Number>(-3.6934));
q2Mat(2,4) = Number(carl::rationalize<Number>(+2.4585));

q2Mat(3,0) = Number(carl::rationalize<Number>(8.3858));
q2Mat(3,1) = Number(carl::rationalize<Number>(-3.1739));
q2Mat(3,2) = Number(carl::rationalize<Number>(+3.7822));
q2Mat(3,3) = Number(carl::rationalize<Number>(-0.6249));
q2Mat(3,4) = Number(carl::rationalize<Number>(+1.8829));

q2Mat(4,0) = Number(carl::rationalize<Number>(1.5964));
q2Mat(4,1) = Number(carl::rationalize<Number>(+2.1936));
q2Mat(4,2) = Number(carl::rationalize<Number>(-2.5872));
q2Mat(4,3) = Number(carl::rationalize<Number>(-1.6812));
q2Mat(4,4) = Number(carl::rationalize<Number>(-1.1324));
q2Mat(4,5) = Number(carl::rationalize<Number>(-0.7342));


q3Mat(0,0) = Number(carl::rationalize<Number>(-0.9275));
q3Mat(0,1) = Number(carl::rationalize<Number>(+8.8628));
q3Mat(0,2) = Number(carl::rationalize<Number>(-2.5428));
q3Mat(0,3) = Number(carl::rationalize<Number>(-8.2329));
q3Mat(0,4) = Number(carl::rationalize<Number>(-2.0324));
q3Mat(0,5) = Number(carl::rationalize<Number>(-0.0845));

q3Mat(1,0) = Number(carl::rationalize<Number>(-0.8316));
q3Mat(1,1) = Number(carl::rationalize<Number>(-0.5860));
q3Mat(1,2) = Number(carl::rationalize<Number>(-2.1006));
q3Mat(1,3) = Number(carl::rationalize<Number>(+3.6035));
q3Mat(1,4) = Number(carl::rationalize<Number>(-1.8423));

q3Mat(2,0) = Number(carl::rationalize<Number>(2.4511));
q3Mat(2,1) = Number(carl::rationalize<Number>(+2.2394));
q3Mat(2,2) = Number(carl::rationalize<Number>(-0.7538));
q3Mat(2,3) = Number(carl::rationalize<Number>(-3.6934));
q3Mat(2,4) = Number(carl::rationalize<Number>(+2.4585));

q3Mat(3,0) = Number(carl::rationalize<Number>(8.3858));
q3Mat(3,1) = Number(carl::rationalize<Number>(-3.1739));
q3Mat(3,2) = Number(carl::rationalize<Number>(+3.7822));
q3Mat(3,3) = Number(carl::rationalize<Number>(-0.6249));
q3Mat(3,4) = Number(carl::rationalize<Number>(+1.8829));

q3Mat(4,0) = Number(carl::rationalize<Number>(0.7635));
q3Mat(4,1) = Number(carl::rationalize<Number>(+3.0357));
q3Mat(4,2) = Number(carl::rationalize<Number>(-3.1814));
q3Mat(4,3) = Number(carl::rationalize<Number>(-1.4388));
q3Mat(4,4) = Number(carl::rationalize<Number>(-2.2538));
q3Mat(4,5) = Number(carl::rationalize<Number>(-0.7342));


q4Mat(0,0) = Number(carl::rationalize<Number>(-1.4021));
q4Mat(0,1) = Number(carl::rationalize<Number>(+10.1647));
q4Mat(0,2) = Number(carl::rationalize<Number>(-3.3937));
q4Mat(0,3) = Number(carl::rationalize<Number>(-8.5139));
q4Mat(0,4) = Number(carl::rationalize<Number>(-2.9602));
q4Mat(0,5) = Number(carl::rationalize<Number>(-0.0845));

q4Mat(1,0) = Number(carl::rationalize<Number>(-0.8316));
q4Mat(1,1) = Number(carl::rationalize<Number>(-0.5860));
q4Mat(1,2) = Number(carl::rationalize<Number>(-2.1006));
q4Mat(1,3) = Number(carl::rationalize<Number>(+3.6035));
q4Mat(1,4) = Number(carl::rationalize<Number>(-1.8423));

q4Mat(2,0) = Number(carl::rationalize<Number>(2.4511));
q4Mat(2,1) = Number(carl::rationalize<Number>(+2.2394));
q4Mat(2,2) = Number(carl::rationalize<Number>(-0.7538));
q4Mat(2,3) = Number(carl::rationalize<Number>(-3.6934));
q4Mat(2,4) = Number(carl::rationalize<Number>(+2.4585));

q4Mat(3,0) = Number(carl::rationalize<Number>(8.3858));
q4Mat(3,1) = Number(carl::rationalize<Number>(-3.1739));
q4Mat(3,2) = Number(carl::rationalize<Number>(+3.7822));
q4Mat(3,3) = Number(carl::rationalize<Number>(-0.6249));
q4Mat(3,4) = Number(carl::rationalize<Number>(+1.8829));

q4Mat(4,0) = Number(carl::rationalize<Number>(-3.3585));
q4Mat(4,1) = Number(carl::rationalize<Number>(+14.3426));
q4Mat(4,2) = Number(carl::rationalize<Number>(-10.5703));
q4Mat(4,3) = Number(carl::rationalize<Number>(-3.8785));
q4Mat(4,4) = Number(carl::rationalize<Number>(-10.3111));
q4Mat(4,5) = Number(carl::rationalize<Number>(-0.7342));


q5Mat(0,0) = Number(carl::rationalize<Number>(-1.4021));
q5Mat(0,1) = Number(carl::rationalize<Number>(+10.1647));
q5Mat(0,2) = Number(carl::rationalize<Number>(-3.3937));
q5Mat(0,3) = Number(carl::rationalize<Number>(-8.5139));
q5Mat(0,4) = Number(carl::rationalize<Number>(-2.9602));
q5Mat(0,5) = Number(carl::rationalize<Number>(-0.0845));

q5Mat(1,0) = Number(carl::rationalize<Number>(-0.8316));
q5Mat(1,1) = Number(carl::rationalize<Number>(-0.5860));
q5Mat(1,2) = Number(carl::rationalize<Number>(-2.1006));
q5Mat(1,3) = Number(carl::rationalize<Number>(+3.6035));
q5Mat(1,4) = Number(carl::rationalize<Number>(-1.8423));

q5Mat(2,0) = Number(carl::rationalize<Number>(2.4511));
q5Mat(2,1) = Number(carl::rationalize<Number>(+2.2394));
q5Mat(2,2) = Number(carl::rationalize<Number>(-0.7538));
q5Mat(2,3) = Number(carl::rationalize<Number>(-3.6934));
q5Mat(2,4) = Number(carl::rationalize<Number>(+2.4585));

q5Mat(3,0) = Number(carl::rationalize<Number>(8.3858));
q5Mat(3,1) = Number(carl::rationalize<Number>(-3.1739));
q5Mat(3,2) = Number(carl::rationalize<Number>(+3.7822));
q5Mat(3,3) = Number(carl::rationalize<Number>(-0.6249));
q5Mat(3,4) = Number(carl::rationalize<Number>(+1.8829));

q5Mat(4,0) = Number(carl::rationalize<Number>(-3.3585));
q5Mat(4,1) = Number(carl::rationalize<Number>(+14.3426));
q5Mat(4,2) = Number(carl::rationalize<Number>(-10.5703));
q5Mat(4,3) = Number(carl::rationalize<Number>(-3.8785));
q5Mat(4,4) = Number(carl::rationalize<Number>(-10.3111));
q5Mat(4,5) = Number(carl::rationalize<Number>(-0.7342));

	q1->setActivityMat(q1Mat);
	q2->setActivityMat(q2Mat);
	q3->setActivityMat(q3Mat);
	q4->setActivityMat(q4Mat);
	q5->setActivityMat(q5Mat);

	/*
	 * Transition
	 */

  vector_t<Number> t12GuardVec = vector_t<Number>::Zero(1);
	matrix_t<Number> t12GuardMat = matrix_t<Number>::Zero(1,5);
  vector_t<Number> t23GuardVec = vector_t<Number>::Zero(1);
	matrix_t<Number> t23GuardMat = matrix_t<Number>::Zero(1,5);
  vector_t<Number> t34GuardVec = vector_t<Number>::Zero(1);
	matrix_t<Number> t34GuardMat = matrix_t<Number>::Zero(1,5);
  vector_t<Number> t45GuardVec = vector_t<Number>::Zero(1);
	matrix_t<Number> t45GuardMat = matrix_t<Number>::Zero(1,5);
  vector_t<Number> t51GuardVec = vector_t<Number>::Zero(1);
	matrix_t<Number> t51GuardMat = matrix_t<Number>::Zero(1,5);
	operator_e guardOp = LEQ;;
  t12GuardVec(0) = Number(carl::rationalize<Number>(3.01));
	t12GuardMat(0,1) = Number(carl::rationalize<Number>(1));
	t23GuardVec(0) = Number(carl::rationalize<Number>(2.01));
	t23GuardMat(0,1) = Number(carl::rationalize<Number>(1));
	t34GuardVec(0) = Number(carl::rationalize<Number>(1.01));
	t34GuardMat(0,1) = Number(carl::rationalize<Number>(1));
	t45GuardVec(0) = Number(carl::rationalize<Number>(0.01));
	t45GuardMat(0,1) = Number(carl::rationalize<Number>(1));
	t51GuardVec(0) = Number(carl::rationalize<Number>(-0.99));
	t51GuardMat(0,1) = Number(carl::rationalize<Number>(-1));

	guard12.op = guardOp;
	guard12.mat = t12GuardMat;
	guard12.vec = t12GuardVec;
  guard23.op = guardOp;
	guard23.mat = t23GuardMat;
	guard23.vec = t23GuardVec;
  guard34.op = guardOp;
	guard34.mat = t34GuardMat;
	guard34.vec = t34GuardVec;
  guard45.op = guardOp;
	guard45.mat = t45GuardMat;
	guard45.vec = t45GuardVec;
  guard51.op = guardOp;
	guard51.mat = t51GuardMat;
	guard51.vec = t51GuardVec;

	vector_t<Number> assignVec = vector_t<Number>::Zero(5,1);
	matrix_t<Number> assignMat = matrix_t<Number>::Identity(5,5);

  reset12.translationVec = assignVec;
	reset12.transformMat = assignMat;
  reset23.translationVec = assignVec;
	reset23.transformMat = assignMat;
  reset34.translationVec = assignVec;
	reset34.transformMat = assignMat;
  reset45.translationVec = assignVec;
	reset45.transformMat = assignMat;
  reset51.translationVec = assignVec;
	reset51.transformMat = assignMat;

	t12->setGuard(guard12);
	t12->setSource(q1);
	t12->setTarget(q2);
	t12->setReset(reset12);
	t23->setGuard(guard23);
	t23->setSource(q2);
	t23->setTarget(q3);
	t23->setReset(reset23);
	t34->setGuard(guard34);
	t34->setSource(q3);
	t34->setTarget(q4);
	t34->setReset(reset34);
	t45->setGuard(guard45);
	t45->setSource(q4);
	t45->setTarget(q5);
	t45->setReset(reset45);
	t51->setGuard(guard51);
	t51->setSource(q5);
	t51->setTarget(q1);
	t51->setReset(reset51);

	/*
	 * Hybrid Automaton
	 */
	locations[0] = q1;
	locations[1] = q2;
	locations[2] = q3;
	locations[3] = q4;
	locations[4] = q5;

	locSet = std::set<hypro::Location<Number>*>(locations, locations+5);

	init[0] = q1;

	initLocSet = std::set<hypro::Location<Number>*>(init, init+1);

	hybrid.setLocations(locSet);
	hybrid.setInitialLocations(initLocSet);

	transition[0] = t12;
	transition[1] = t23;
	transition[2] = t34;
	transition[3] = t45;
	transition[4] = t51;

	transSet = std::set<hypro::Transition<Number>*>(transition, transition+5);
	transSet1 = std::set<hypro::Transition<Number>*>(transition+0, transition+1);
	transSet2 = std::set<hypro::Transition<Number>*>(transition+1, transition+2);
	transSet3 = std::set<hypro::Transition<Number>*>(transition+2, transition+3);
	transSet4 = std::set<hypro::Transition<Number>*>(transition+3, transition+4);
	transSet5 = std::set<hypro::Transition<Number>*>(transition+4, transition+5);

	hybrid.setTransitions(transSet);
	q1->setTransitions(transSet1);
	q2->setTransitions(transSet2);
	q3->setTransitions(transSet3);
	q4->setTransitions(transSet4);
	q5->setTransitions(transSet5);

	// Polytope for InitialValuation & Guard Assignment

	// create Box (note: 3rd variable is for the constant factor)
	boxVec(0) = Number(carl::rationalize<Number>(-3.09));
	boxVec(1) = Number(carl::rationalize<Number>(3.11));
	boxVec(2) = Number(carl::rationalize<Number>(-3.99));
	boxVec(3) = Number(carl::rationalize<Number>(4.01));
	boxVec(4) = Number(carl::rationalize<Number>(0.01)); //Note: we want -0.01 <= x3,x4,x5 <= 0.01, so no sign here!
	boxVec(5) = Number(carl::rationalize<Number>(0.01));
	boxVec(6) = Number(carl::rationalize<Number>(0.01));
	boxVec(7) = Number(carl::rationalize<Number>(0.01));
	boxVec(8) = Number(carl::rationalize<Number>(0.01));
	boxVec(9) = Number(carl::rationalize<Number>(0.01));
	//boxVec(10) = Number(carl::rationalize<Number>(-1));
	//boxVec(11) = Number(carl::rationalize<Number>(1));

	boxMat(0,0) = Number(carl::rationalize<Number>(-1));
	boxMat(1,0) = Number(carl::rationalize<Number>(1));
	boxMat(2,1) = Number(carl::rationalize<Number>(-1));
	boxMat(3,1) = Number(carl::rationalize<Number>(1));
	boxMat(4,2) = Number(carl::rationalize<Number>(-1));
	boxMat(5,2) = Number(carl::rationalize<Number>(1));
	boxMat(6,3) = Number(carl::rationalize<Number>(-1));
	boxMat(7,3) = Number(carl::rationalize<Number>(1));
	boxMat(8,4) = Number(carl::rationalize<Number>(-1));
	boxMat(9,4) = Number(carl::rationalize<Number>(1));
	//boxMat(10,5) = Number(carl::rationalize<Number>(-1));
	//boxMat(11,5) = Number(carl::rationalize<Number>(1));

	Representation poly(boxMat,boxVec);

	hybrid.setInitialValuation(poly);

	std::vector<std::vector<Representation>> flowpipes;

	hypro::reachability::Reach<Number, Representation> reacher(hybrid);
	std::set<std::size_t> flowpipeIndices = reacher.computeForwardReachability();


        std::chrono::high_resolution_clock::time_point timeFlowPipeEnd = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds flowPipeTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeFlowPipeEnd - timeStart);
	std::cout << "Generated flowpipe in " << flowPipeTime.count() << " milliseconds." << std::endl;

        std::cout << "Generating Plot.." << std::endl;

	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	plotter.setFilename("out");

	for(auto& index : flowpipeIndices){
		std::vector<Representation> flowpipe = reacher.getFlowpipe(index);

		// Plot flowpipe
		unsigned count = 1;
		unsigned maxCount = flowpipe.size();
		for(auto& poly : flowpipe) {
			//std::cout << "Flowpipe segment to be converted: " << std::endl;
			//poly.removeRedundantPlanes();
			//poly.print();
			std::vector<Point<Number>> points = poly.vertices();
			//std::cout << "points.size() = " << points.size() << std::endl;
			if(!points.empty() && points.size() > 2) {
				//std::cout << "Polycount: " << count << std::endl;
				for(auto& point : points) {
		// 			std::cout << "reduce " << point << " to ";
					point.reduceDimension(2);
					// 			std::cout << point << std::endl;
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

        std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds overAllTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
	std::cout << "Generated flowpipe in " << flowPipeTime.count() << " milliseconds." << std::endl;
	std::cout << "OverAll Time is " << overAllTime.count() << " milliseconds." << std::endl;


	return 0;
}

