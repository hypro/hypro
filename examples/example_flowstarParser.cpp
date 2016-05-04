/**
 *
 */

#include "../src/lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../src/lib/algorithms/reachability/Reach.h"
#include "../src/lib/representations/GeometricObject.h"
#include "../src/lib/parser/flowstar/flowstarParser.h"
#include "../src/lib/util/Plotter.h"
#include <chrono>
#include <string>

int main(int argc, char** argv) {
	typedef cln::cl_RA Number;
	typedef hypro::SupportFunction<Number> sfValuation;
	typedef hypro::HPolytope<Number> hpValuation;
	typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::microseconds timeunit;

	//std::string filename = "../examples/input/bouncing_ball.model";
	std::string filename = "../examples/input/simple_tank_plant.model";

	clock::time_point start = clock::now();
	hypro::parser::flowstarParser<Number> parser;
	hypro::HybridAutomaton<Number> ha = parser.parseInput(filename);

	//hypro::reachability::Reach<Number,sfValuation> sfReach(ha, parser.mSettings);
	//std::vector<std::vector<sfValuation>> sfFlowpipes = sfReach.computeForwardReachability();

	parser.mSettings.uniformBloating = false;

	hypro::reachability::Reach<Number,hpValuation> hpReach(ha, parser.mSettings);
	std::vector<std::vector<hpValuation>> hpFlowpipes = hpReach.computeForwardReachability();

	std::cout << "Finished computation of reachable states: " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000 << std::endl;

	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.setFilename(parser.mSettings.fileName);
	std::vector<unsigned> plottingDimensions = parser.mSettings.plotDimensions;
	plotter.rSettings().dimensions.first = plottingDimensions.front();
	plotter.rSettings().dimensions.second = plottingDimensions.back();
	plotter.rSettings().cummulative = true;

	// bad states plotting
	hypro::HybridAutomaton<Number>::locationStateMap badStateMapping = ha.localBadStates();
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
}
