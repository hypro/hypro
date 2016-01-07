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
	std::set<std::size_t> flowpipeIndices = reacher.computeForwardReachability(); // use_reduce in Reach.tpp must be false

	bool plotting=true;
	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	plotter.setFilename("out");

	std::cout << std::endl << "Generated flowpipe, start convexHull - reduce." << std::endl;

	unsigned CONVEXHULL_CONST = 50;
	unsigned REDUCE_CONST=100;

	//for(unsigned REDUCE_CONST=6; REDUCE_CONST<20; REDUCE_CONST++){
		//for(unsigned CONVEXHULL_CONST=57; CONVEXHULL_CONST<200; CONVEXHULL_CONST++){

			double soFlowpipe=0, soFlowpipeS=0; // sizeOf flowpipes
			std::vector<std::vector<Representation>>  flowpipes_smoothed;

			clock::time_point start = clock::now();

			// Reduce (convexHull and directed_template) ---------------------------------------- START
			for(auto& index : flowpipeIndices) {
				std::vector<Representation> flowpipe = reacher.getFlowpipe(index), flowpipe_smoothed;
				std::vector<Point<Number>> points_convexHull;
				unsigned flowpipe_count=0, flowpipe_total=1; // flowpipe_count for convexHull, flowpipe_total to notice the end


				for(auto& poly : flowpipe){
					// update points_convexHull
					if(CONVEXHULL_CONST==1){
						Representation poly_smoothed = poly.reduce_directed(computeTemplate<Number>(2, REDUCE_CONST), HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);
						soFlowpipe += poly.sizeOfHPolytope(); // update size of flowpipe
						soFlowpipeS += poly_smoothed.sizeOfHPolytope(); // update size of smoothed flowpipe
						flowpipe_smoothed.push_back(poly_smoothed); // update smoothed flowpipe
					}
					else {
						//std::cout << "update vertices of segment " << flowpipe_total-1 << std::endl;
						std::vector<Point<Number>> points = poly.vertices();
						for(Point<Number> point: points){
							if(std::find(points_convexHull.begin(), points_convexHull.end(), point)==points_convexHull.end()){
								points_convexHull.push_back(point);
							}
						}

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
							//poly_smoothed.removeRedundantPlanes();

							// test if every used segment is contained in convexHull
							//for(unsigned i=0; i<=CONVEXHULL_CONST; i++){
							//	std::cout << "Test " <<flowpipe_total-i-1  << std::endl;
							//	if(!convexHull.contains(flowpipe.at( flowpipe_total-i-1 ))){
							//		std::cout << "Segment " << flowpipe_total-i-1 << " is not contained in convexHull" << std::endl;
							//	}
							//	if(!poly_smoothed.contains(flowpipe.at( flowpipe_total-i-1 ))){
							//		std::cout << "Segment " << flowpipe_total-i-1 << " is not contained in poly_smoothed" << std::endl;
							//	}
							//}

							// test if every used point is contained in convexHull
							//for(auto point: points_convexHull){
							//	std::cout << "Test " <<point  << std::endl;
							//	if(!convexHull.contains(point)){
							//		std::cout << "point " << point << " is not contained in convexHull" << std::endl;
							//	}
							//	if(!poly_smoothed.contains(point)){
							//		std::cout << "point " << point << " is not contained in poly_smoothed" << std::endl;
							//	}
							//}

							soFlowpipeS += poly_smoothed.sizeOfHPolytope(); // update size of smoothed flowpipe
							flowpipe_smoothed.push_back(poly_smoothed); // update smoothed flowpipe

							// reset variables
							flowpipe_count=0;
							points_convexHull.clear();
						} else {
							flowpipe_count++;
						}

						soFlowpipe += poly.sizeOfHPolytope(); // update size of flowpipe
						flowpipe_total++;
					}
				}
				flowpipes.push_back(flowpipe);
				flowpipes_smoothed.push_back(flowpipe_smoothed);
			}
			// Reduce (convexHull and directed_template) ---------------------------------------- END

			std::cout << " Total time for reduction(HYPRO): " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;

			// Test flowpipes_smoothed if one segment of one flowpipe intersects with one segement of another flowpipe
			std::cout << " Test (intersect)" << std::endl;
			int flowpipe_one=-1, flowpipe_two=-1, segment_one=-1, segment_two=-1;
			bool intersect=false;

			for(unsigned i=0; i<flowpipes_smoothed.size(); i++){
				if(intersect) break;
				for(unsigned ii=0; ii<flowpipes_smoothed.at(i).size(); ii++){
					if(intersect) break;
					for(unsigned j=i+1; j<flowpipes_smoothed.size(); j++){
						if(intersect) break;
						for(unsigned jj=0; jj<flowpipes_smoothed.at(j).size(); jj++){
							std::cout << "\r  " << i <<"." << ii <<"/"<< flowpipes_smoothed.size()-2 <<"." << flowpipes_smoothed.at(i).size()-1  << " and " << j <<"." << jj  << std::flush;

							if(!flowpipes_smoothed.at(i).at(ii).intersect(flowpipes_smoothed.at(j).at(jj)).empty()){
								intersect=true;
								//CONVEXHULL_CONST=0;
								flowpipe_one = i; segment_one = ii; flowpipe_two = j; segment_two = jj;
								std::cout << std::endl << "  " << ii << " of "<< i << " and "<< jj << " of " << j << " intersects" << std::endl;
								break;
							}
						}
					}
				}
			}
			if(!intersect) std::cout << "  No intersection!" << std::endl;

			// Test if every segment of the original fowpipe is contained in the reduction
			std::cout << std::endl << " Test (contains)" << std::endl;
			int flowpipe_index=-1, segment_index=-1;
			bool contained=true;
			Point<Number> badPoint;

			for(unsigned i=0; i<flowpipes.size(); i++){
				for(unsigned ii=0; ii<flowpipes.at(i).size(); ii++){
					std::vector<Point<Number>> points = flowpipes.at(i).at(ii).vertices();
					// segment of flowpipe found

					for(unsigned j=0; j<flowpipes_smoothed.size(); j++){
						if(contained) break;
						for(unsigned jj=0; jj<flowpipes_smoothed.at(j).size(); jj++){
							// segment of flowpipe:smoothed found
							if(contained) break;

							contained=true;

							std::cout << "\r  " << i <<"." << ii <<"/"<< flowpipes.size()-1 <<"." << flowpipes.at(i).size()-1  << " and " << j <<"." << jj  << std::flush;

							for(Point<Number> point: points){
								if(!flowpipes_smoothed.at(j).at(jj).contains(point)){
									contained=false;
									badPoint = point;
									break;
								}
							}
						}
					}

					if(!contained){
						flowpipe_index = i; segment_index = ii;
						std::cout << "  "  << i << "."<< ii << " with " << badPoint << " is not contained in the reduction" << std::endl;
					}
					if(!contained) break;
				}
				if(!contained) break;
			}
			if(contained) std::cout << "  Every segment is contained in reduction!" << std::endl;


			std::cout << std::endl << std::endl << " Stats:"<< std::endl << "  CONVEXHULL_CONST:  " << CONVEXHULL_CONST << std::endl << "  REDUCE_CONST:      " << REDUCE_CONST << std::endl;
			std::cout  << "  flowpipe:          " << soFlowpipe << std::endl << "  flowpipe_smoothed: " << soFlowpipeS << std::endl;
			std::cout << "  reduction of       " << (soFlowpipeS/soFlowpipe)*100 << "%" << std::endl << std::endl;


			if(plotting){
				std::cout << std::endl << "Generated flowpipe, start plotting." << std::endl;

				int flowpipe_count=0;
				for(auto& flowpipe: flowpipes) {
					// Plot flowpipe
					int count=0;
					unsigned maxCount = flowpipe.size();
					for(auto& poly : flowpipe) {
						//std::cout << "Flowpipe segment to be converted: " << std::endl;
						poly.removeRedundantPlanes();
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
							if(flowpipe_count==flowpipe_index && count==segment_index){
								plotter.setObjectColor(p, colors[green]);
							}
							std::cout << "\r Flowpipe "<< flowpipe_count+1 <<": Added object " << count+1 << "/" << maxCount << std::flush;
							points.clear();
							++count;
						}
					}
					std::cout << std::endl;
					flowpipe_count++;
				}

				int flowpipe_smoothed_count=0;
				for(auto& flowpipe_smoothed: flowpipes_smoothed){
					// Plot flowpipe_smoothed
					int count_smoothed=0;
					unsigned maxCount_smoothed = flowpipe_smoothed.size();
					for(auto& poly : flowpipe_smoothed) {
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
							if((flowpipe_smoothed_count==flowpipe_one && count_smoothed==segment_one) || (flowpipe_smoothed_count==flowpipe_two && count_smoothed==segment_two)){
								plotter.setObjectColor(p, colors[red]);
							} else {
								plotter.setObjectColor(p, colors[orange]);
							}
							std::cout << "\r Flowpipe_smoothed "<< flowpipe_smoothed_count+1 <<": Added object " << count_smoothed+1 << "/" << maxCount_smoothed << std::flush;
							points.clear();
							++count_smoothed;
						}
					}
					std::cout << std::endl;
					flowpipe_smoothed_count++;
				}
			}
			//if(intersect) break;
		//}
	//}

	std::cout << std::endl;
	if(plotting) plotter.plot2d();

	return 0;
}
