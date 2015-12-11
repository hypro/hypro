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
	std::set<std::size_t> flowpipeIndices = reacher.computeForwardReachability();

	std::cout << "Generated flowpipe, start plotting." << std::endl;

	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	plotter.setFilename("out");

	//unsigned CONVEXHULL_CONST = 300;
	//unsigned REDUCE_CONST=3;
	//std::cout << "Plotting computes with convexHull_const " << CONVEXHULL_CONST << " and reduce_const " << REDUCE_CONST << std::endl;

	for(unsigned REDUCE_CONST=3; REDUCE_CONST<11; REDUCE_CONST++){
		for(unsigned CONVEXHULL_CONST=3; CONVEXHULL_CONST<201; CONVEXHULL_CONST+=10){
			std::cout << "CONVEXHULL_CONST:  " << CONVEXHULL_CONST << std::endl << "REDUCE_CONST:      " << REDUCE_CONST << std::endl;
			double soFlowpipe=0, soFlowpipeS=0; // sizeOf flowpipes

			for(auto& index : flowpipeIndices) {
				std::vector<Representation> flowpipe = reacher.getFlowpipe(index);
				std::vector<Representation>  flowpipe_smoothed;

				std::vector<Point<Number>> points_convexHull;
				unsigned flowpipe_count=0, flowpipe_total=0; // flowpipe_count for convexHull, flowpipe_total to notice the end


				for(auto& poly : flowpipe){
					// update points_convexHull
					std::vector<Point<Number>> points = poly.vertices();
					for(Point<Number> point: points){
						if(std::find(points_convexHull.begin(), points_convexHull.end(), point)==points_convexHull.end()){
							points_convexHull.push_back(point);
						}
					}
					flowpipe_count++;

					// create convexHull if CONVEXHULL_CONST or end is reached
					if(flowpipe_count==CONVEXHULL_CONST || flowpipe_total==flowpipe.size()-1) {

						// Create convexHull of CONVEXHULL_CONST representations
						auto facets = convexHull(points_convexHull);
						std::vector<Hyperplane<Number>> hyperplanes;
						for(unsigned i = 0; i<facets.first.size(); i++){
							hyperplanes.push_back(facets.first.at(i)->hyperplane());
						}
						Representation convexHull = Representation(hyperplanes);

						// Reduce to REDUCE_CONST
						Representation poly_smoothed = convexHull.reduce_directed(computeTemplate<Number>(2, REDUCE_CONST), HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);

						soFlowpipeS += poly_smoothed.sizeOfHPolytope(); // update size of smoothed flowpipe
						flowpipe_smoothed.push_back(poly_smoothed); // update smoothed flowpipe

						// reset variables
						flowpipe_count=0;
						points_convexHull.clear();
					}

					soFlowpipe += poly.sizeOfHPolytope(); // update size of flowpipe
					flowpipe_total++;
				}

				//// Plot flowpipe
				//unsigned count=1, count_smoothed=1;
				//unsigned maxCount = flowpipe.size(), maxCount_smoothed = flowpipe_smoothed.size();;
				//for(auto& poly : flowpipe) {
				//	//std::cout << "Flowpipe segment to be converted: " << std::endl;
				//	poly.removeRedundantPlanes();
				//	//poly.print();
				//	std::vector<Point<Number>> points = poly.vertices();
				//	//std::cout << "points.size() = " << points.size() << std::endl;
				//	if(!points.empty() && points.size() > 2) {
				//		//std::cout << "Polycount: " << count << std::endl;
				//		for(auto& point : points) {
				//// 			std::cout << "reduce " << point << " to ";
				//			point.reduceDimension(2);
				//			// 			std::cout << point << std::endl;
				//		}
				//		unsigned p=plotter.addObject(points);
				//		plotter.setObjectColor(p, colors[red]);
				//		std::cout << "\r Flowpipe "<< index <<": Added object " << count << "/" << maxCount << std::flush;
				//		points.clear();
				//		++count;
				//	}
				//}

				//// Plot flowpipe_smoothed
				//for(auto& poly : flowpipe_smoothed) {
				//	//std::cout << "Flowpipe segment to be converted: " << std::endl;
				//	poly.removeRedundantPlanes();
				//	//poly.print();
				//	std::vector<Point<Number>> points = poly.vertices();
				//	//std::cout << "points.size() = " << points.size() << std::endl;
				//	if(!points.empty() && points.size() > 2) {
				//		//std::cout << "Polycount: " << count << std::endl;
				//		for(auto& point : points) {
				//// 			std::cout << "reduce " << point << " to ";
				//			point.reduceDimension(2);
				//			// 			std::cout << point << std::endl;
				//		}
				//		plotter.addObject(points);
				//		std::cout << "\r Flowpipe "<< index <<": Added object " << count_smoothed << "/" << maxCount_smoothed << std::flush;
				//		points.clear();
				//		++count_smoothed;
				//	}
				//}
				//std::cout << std::endl;
		}
		std::cout << "flowpipe:          " << soFlowpipe << std::endl << "flowpipe_smoothed: " << soFlowpipeS << std::endl;
		std::cout << "factor:            " << soFlowpipe/soFlowpipeS << std::endl << std::endl;
	}
}

std::cout << std::endl;
	plotter.plot2d();

	return 0;
}
