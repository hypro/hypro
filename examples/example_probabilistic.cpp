#include "../lib/config.h"
#include "../lib/datastructures/hybridAutomata/LocationManager.h"
#include "../lib/datastructures/hybridAutomata/Transition.h"
#include "../lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../lib/datastructures/Point.h"
#include "../lib/algorithms/probabilistic/ReducedReach.h"
#include "../lib/representations/Polytopes/Polytope/Polytope.h"
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
	typedef hypro::Polytope<Number> Representation;

	LocationManager<Number>& lManager = LocationManager<Number>::getInstance();

	//Hybrid Automaton Objects: Locations, Transitions, Automaton itself
	Location<Number>* loc1 = lManager.create();
	HybridAutomaton<Number, Representation> hybrid = HybridAutomaton<Number, Representation>();

	//Other Objects: Vectors, Matrices, Guards...

	hypro::Location<Number>* locations[1];
	std::set<hypro::Location<Number>*> locSet;

	hypro::Location<Number>* init[1];
	std::set<hypro::Location<Number>*> initLocSet;

	/*
	 * Location
	 */

	vector_t<Number> invariantVec = vector_t<Number>(8,1);
	operator_e invariantOp;
	matrix_t<Number> invariantMat = matrix_t<Number>(8,4);
	struct Location<Number>::Invariant inv;

	invariantVec << 0,1,0,1,0,1,0,1;
	invariantOp = LEQ;
    invariantMat << 1,0,0,0,
                    -1,0,0,0,
                    0,1,0,0,
                    0,-1,0,0,
                    0,0,1,0,
                    0,0,-1,0,
                    0,0,0,1,
                    0,0,0,-1;

	loc1->setInvariant(invariantMat,invariantVec,invariantOp);

	inv.op = invariantOp;
	inv.mat = invariantMat;
	inv.vec = invariantVec;

    static const Number l = 2;
    static const Number m = 2;

    matrix_t<Number> locationMat = matrix_t<Number>(5,5);

	locationMat << -l-m, 0,0,0,0,
                    l,-m,0,0,0,
                    0,m,0,0,0,
                    m,0,0,0,0,
                    0,0,0,0,0;

	loc1->setActivityMat(locationMat);

	/*
	 * Hybrid Automaton
	 */
	locations[0] = loc1;
	locSet = std::set<hypro::Location<Number>*>(locations, locations+1);
	init[0] = loc1;
	initLocSet = std::set<hypro::Location<Number>*>(init, init+1);

	hybrid.setLocations(locSet);
	hybrid.setInitialLocations(initLocSet);

	//Polytope for InitialValuation
	vector_t<Number> initialVec = vector_t<Number>(8,1);
	matrix_t<Number> initialMat = matrix_t<Number>(8,4);
    initialVec << 1,-1,0,0,0,0,0,0;
    initialMat << 1,0,0,0,
                    -1,0,0,0,
                    0,1,0,0,
                    0,-1,0,0,
                    0,0,1,0,
                    0,0,-1,0,
                    0,0,0,1,
                    0,0,0,-1;

	Representation poly(initialMat,initialVec);

	hybrid.setInitialValuation(poly);

	std::vector<std::vector<Representation>> flowpipes;

	hypro::probabilistic::ReducedReach<Number, Representation> reacher(hybrid);
	std::size_t flowpipeIndex = reacher.check();

	std::cout << "Generated flowpipe, start plotting." << std::endl;

	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.setFilename("out");


	std::vector<Representation> flowpipe = reacher.getFlowpipe(flowpipeIndex);
	unsigned count = 1;
	unsigned maxCount = flowpipe.size();
	for(auto& poly : flowpipe) {
		std::cout << "Flowpipe segment to be converted: " << std::endl;
		poly.removeRedundantPlanes();
		poly.print();
		std::vector<Point<Number>> points = poly.vertices();
		std::cout << "points.size() = " << points.size() << std::endl;
		if(!points.empty() && points.size() > 2) {
			//std::cout << "Polycount: " << count << std::endl;
			for(auto& point : points) {
	// 			std::cout << "reduce " << point << " to ";
				point.reduceDimension(2);
				// 			std::cout << point << std::endl;
			}
			plotter.addObject(points);
			//std::cout << "\rAdded object " << count << "/" << maxCount << std::flush;
			points.clear();
			++count;
		}
	}
	std::cout << endl;

	plotter.plot2d();

	return 0;
}
