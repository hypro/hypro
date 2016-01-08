#include <chrono>

#include "../lib/config.h"
#include "../lib/datastructures/hybridAutomata/LocationManager.h"
#include "../lib/datastructures/hybridAutomata/Transition.h"
#include "../lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../lib/datastructures/Point.h"
#include "../lib/algorithms/reachability/Reach.h"
#include "../lib/representations/Polytopes/HPolytope/HPolytope.h"
#include "../lib/representations/Polytopes/VPolytope/VPolytope.h"
#include "../lib/representations/SupportFunction/SupportFunctionContent.h"
#include "../lib/representations/Box/Box.h"
#include "../lib/util/Plotter.h"

int main(int argc, char const *argv[])
{
	using namespace hypro;
	using namespace carl;

	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::microseconds timeunit;

	typedef FLOAT_T<double> Number;
	//carl::FLOAT_T<mpfr_t>::setDefaultPrecision(FLOAT_PRECISION);
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

	invariantVec(0) = Number(20);
	invariantVec(1) = Number(0.1);
	invariantVec(2) = Number(20);
	invariantVec(3) = Number(20);
	//invariantVec(4) = 1;
	//invariantVec(5) = 1;

	invariantOp = LEQ;

	invariantMat(0,0) = Number(1);
	invariantMat(0,1) = Number(0);
	invariantMat(1,0) = Number(-1);
	invariantMat(1,1) = Number(0);
	invariantMat(2,0) = Number(0);
	invariantMat(2,1) = Number(1);
	invariantMat(3,0) = Number(0);
	invariantMat(3,1) = Number(-1);


	loc1->setInvariant(invariantMat,invariantVec,invariantOp);

	inv.op = invariantOp;
	inv.mat = invariantMat;
	inv.vec = invariantVec;

        /*locationMat << Number(0), Number(1), Number(0)
         *               Number(0), Number(0), Number(-9.81)
                         Number(0), Number(0), Number(0); */

	locationMat(0,0) = Number(0);
	locationMat(0,1) = Number(1);
	locationMat(0,2) = Number(0);
	locationMat(1,0) = Number(0);
	locationMat(1,1) = Number(0);
	locationMat(1,2) = Number(-9.81);
	locationMat(2,0) = Number(0);
	locationMat(2,1) = Number(0);
	locationMat(2,2) = Number(0);


	loc1->setActivityMat(locationMat);

	/*
	 * Transition
	 */

	vector_t<Number> guardVec = vector_t<Number>(3,1);
	operator_e guardOp;
	matrix_t<Number> guardMat = matrix_t<Number>(3,2);

	guardVec(0) = Number(0);
	guardVec(1) = Number(0.1);
	guardVec(2) = Number(0);

	guardOp = LEQ;

	guardMat(0,0) = Number(1);
	guardMat(0,1) = Number(0);
	guardMat(1,0) = Number(-1);
	guardMat(1,1) = Number(0);
	guardMat(2,0) = Number(0);
	guardMat(2,1) = Number(1);


	guard.op = guardOp;
	guard.mat = guardMat;
	guard.vec = guardVec;

	vector_t<Number> assignVec = vector_t<Number>(2,1);
	matrix_t<Number> assignMat = matrix_t<Number>(2,2);

	assignVec(0) = Number(0);
	assignVec(1) = Number(0);

	assignMat(0,0) = Number(1);
	assignMat(0,1) = Number(0);
	assignMat(1,0) = Number(0);
	assignMat(1,1) = Number(-0.9);

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

	// Polytope for InitialValuation & Guard Assignment

	// create Box (note: 3rd variable is for the constant factor)
	boxVec(0) = Number(10.2);
	boxVec(1) = Number(-10);
	boxVec(2) = Number(-0.009);
	boxVec(3) = Number(0.01);

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
	clock::time_point start = clock::now();
	std::set<std::size_t> flowpipeIndices = reacher.computeForwardReachability();
	double timeOfReachReduction = (double) std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
	std::cout << std::endl << "Total time for reduction(HYPRO): " << timeOfReachReduction << std::endl;

	std::cout << std::endl << "Test computed flowpipe ..." << std::endl;

	unsigned soFlowpipe = 0;
	for(auto& index : flowpipeIndices) {
		std::vector<Representation> flowpipe = reacher.getFlowpipe(index);
		flowpipes.push_back(flowpipe);
		for(auto& poly : flowpipe){
			soFlowpipe += poly.sizeOfHPolytope();
		}
	}
	std::cout << "Reduction of flowpipe with soFlowpipe ("<< soFlowpipe << "): "<<  ((double) soFlowpipe/480656.0)*100 << "%" << std::endl;
	std::cout << "Time of flowpipe with timeOfReachReduction ("<< timeOfReachReduction << "): "<<  ((double) timeOfReachReduction/2619)*100 << "%" << std::endl;

	std::cout << std::endl << ((double) soFlowpipe/480656.0)*100 << " " << ((double) timeOfReachReduction/2619)*100  << std::endl;
	// 4, 400: 480656, 2619
	// 5, 1000: 971456, 5463.16

	// for mpfr_t 1442384 2542...

	// test reduction if flowpipes intersect
	int flowpipe_one=-1, segment_one=-1, flowpipe_two=-1, segment_two=-1;
	bool intersect=false;

	if(true){
		std::cout << " Test (intersection)" << std::endl;
		for(unsigned i=0; i<flowpipes.size(); i++){
			if(intersect) break;
			for(unsigned ii=0; ii<flowpipes.at(i).size(); ii++){
				if(intersect) break;
				for(unsigned j=i+1; j<flowpipes.size(); j++){
					if(intersect) break;
					for(unsigned jj=0; jj<flowpipes.at(j).size(); jj++){
						std::cout << "\r  " << i <<"." << ii <<"/"<< flowpipes.size()-1 <<"." << flowpipes.at(i).size()-1  << " and " << j <<"." << jj  << std::flush;

						if(!flowpipes.at(i).at(ii).intersect(flowpipes.at(j).at(jj)).empty()){
							intersect=true;
							flowpipe_one = i;
							segment_one = ii;
							flowpipe_two = j;
							segment_two = jj;

							std::cout << "  " << ii << " of "<< i << " and "<< jj << " of " << j << " intersects" << std::endl;
							break;
						}
					}
				}
			}
		}
	}
	if(!intersect) std::cout << std::endl << "No intersection!" << std::endl;

	std::cout << "Generated flowpipe, start plotting." << std::endl;

	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	plotter.setFilename("out");

	int flowpipe_count=0;
	for(auto& index : flowpipeIndices) {
		std::vector<Representation> flowpipe = reacher.getFlowpipe(index);


		// Plot flowpipe
		int count=0;//, count_smoothed=1;
		unsigned maxCount = flowpipe.size();//, maxCount_smoothed = flowpipe_smoothed.size();;
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
				unsigned p=plotter.addObject(points);
				if((flowpipe_count==flowpipe_one && count==segment_one) || (flowpipe_count==flowpipe_two && count==segment_two)){
					plotter.setObjectColor(p, colors[green]);
				}
				else if(flowpipe_count==1){
					plotter.setObjectColor(p, colors[bordeaux]);
				}
				else if (flowpipe_count==2){
					plotter.setObjectColor(p, colors[red]);
				}
				else if (flowpipe_count==3){
					plotter.setObjectColor(p, colors[orange]);
				}
				//}
				std::cout << "\r Flowpipe "<< index <<": Added object " << count+1 << "/" << maxCount << std::flush;
				points.clear();
				++count;
			}
		}
		flowpipe_count++;
	}

	std::cout << std::endl;
	plotter.plot2d();

	return 0;
}
