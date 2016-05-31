/**
 *
 */

#include "datastructures/hybridAutomata/HybridAutomaton.h"
#include "algorithms/reachability/Reach.h"
#include "representations/GeometricObject.h"
#include "parser/flowstar/ParserWrapper.h"
#include "util/Plotter.h"
#include <chrono>
#include <string>

int main(int argc, char** argv) {

	#ifdef USE_CLN_NUMBERS
	typedef cln::cl_RA Number;
	#else
	typedef mpq_class Number;
	#endif
	//typedef hypro::SupportFunction<Number> sfValuation;
	typedef hypro::Box<Number> boxValuation;
	//typedef hypro::HPolytope<Number> hpValuation;
	typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::microseconds timeunit;

    if(argc < 2) {
    	std::cout << "No input file given." << std::endl;
    	exit(0);
    } else if (argc > 2) {
    	std::cout << "Too many arguments, require only the path to the input file." << std::endl;
    	exit(0);
    }

	std::string filename = std::string(argv[1]);

	//std::string filename = "../examples/input/bouncing_ball.model";
	//std::string filename = "../examples/input/simple_tank_plant.model";
	//std::string filename = "../examples/input/smoke_detector.model";

	clock::time_point start = clock::now();
	hypro::HybridAutomaton<Number> ha = hypro::parseFlowstarFile<Number>(filename);

	//hypro::reachability::Reach<Number,sfValuation> sfReach(ha, parser.mSettings);
	//std::vector<std::vector<sfValuation>> sfFlowpipes = sfReach.computeForwardReachability();

	//hypro::reachability::Reach<Number,hpValuation> hpReach(ha, ha.reachabilitySettings());
	//std::vector<std::vector<hpValuation>> hpFlowpipes = hpReach.computeForwardReachability();

	hypro::reachability::Reach<Number,boxValuation> hpReach(ha, ha.reachabilitySettings());
	std::vector<std::vector<boxValuation>> hpFlowpipes = hpReach.computeForwardReachability();

	std::cout << "Finished computation of reachable states: " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000.0 << " ms" << std::endl;

	clock::time_point startPlotting = clock::now();

	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.setFilename(ha.reachabilitySettings().fileName);
	std::vector<unsigned> plottingDimensions = ha.reachabilitySettings().plotDimensions;
	plotter.rSettings().dimensions.first = plottingDimensions.front();
	plotter.rSettings().dimensions.second = plottingDimensions.back();
	plotter.rSettings().cummulative = false;

	// bad states plotting
	//hypro::HybridAutomaton<Number>::locationStateMap badStateMapping = ha.localBadStates();
	//for(const auto& state : badStateMapping) {
	//	unsigned bs = plotter.addObject(hpValuation(state.second.constraints, state.second.constants).vertices());
	//	plotter.setObjectColor(bs, hypro::colors[hypro::red]);
	//}

	//for(const auto& flowpipe : sfFlowpipes){
	//	for(const auto& segment : flowpipe){
	//		unsigned tmp = plotter.addObject(segment.vertices());
	//		plotter.setObjectColor(tmp, hypro::colors[hypro::green]);
	//	}
	//}

	//std::cout << "Computed " << hpFlowpipes.size() << " flowpipes. Start plotting." << std::endl;
	//for(const auto& flowpipe : hpFlowpipes){
	//	for(const auto& segment : flowpipe){
	//		unsigned tmp = plotter.addObject(segment.vertices());
	//		plotter.setObjectColor(tmp, hypro::colors[hypro::orange]);
	//	}
	//}

	plotter.plot2d();
	plotter.plotTex();

	std::cout << "Finished plotting: " << std::chrono::duration_cast<timeunit>( clock::now() - startPlotting ).count()/1000.0 << " ms" << std::endl;
}
