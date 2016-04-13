/**
 *
 */

#include <string>
#include "../src/lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../src/lib/algorithms/reachability/Reach.h"
#include "../src/lib/representations/GeometricObject.h"
#include "../src/lib/parser/flowstar/flowstarParser.h"
#include "../src/lib/util/Plotter.h"

int main(int argc, char** argv) {
	typedef cln::cl_RA Number;
	typedef hypro::SupportFunction<Number> sfValuation;
	typedef hypro::HPolytope<Number> hpValuation;

	std::string filename = "../examples/input/bouncing_ball.model";

	hypro::parser::flowstarParser<Number> parser;
	hypro::HybridAutomaton<Number> ha = parser.parseInput(filename);

	hypro::reachability::Reach<Number,sfValuation> sfReach(ha, parser.mSettings);
	std::vector<std::vector<sfValuation>> sfFlowpipes = sfReach.computeForwardReachability();

	//hypro::reachability::Reach<Number,hpValuation> hpReach(ha, parser.mSettings);
	//std::vector<std::vector<hpValuation>> hpFlowpipes = hpReach.computeForwardReachability();

	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.setFilename(parser.mSettings.fileName);
	std::vector<unsigned> plottingDimensions = parser.mSettings.plotDimensions;
	plotter.rSettings().dimensions.first = plottingDimensions.front();
	plotter.rSettings().dimensions.second = plottingDimensions.back();

	// bad states plotting
	hypro::HybridAutomaton<Number>::locationSetMap badStateMapping = ha.localBadStates();
	for(const auto& bsPair : badStateMapping) {
		unsigned bs = plotter.addObject(hpValuation(bsPair.second.first, bsPair.second.second).vertices());
		plotter.setObjectColor(bs, hypro::colors[hypro::red]);
	}

	for(const auto& flowpipe : sfFlowpipes){
		for(const auto& segment : flowpipe){
			unsigned tmp = plotter.addObject(segment.vertices());
			plotter.setObjectColor(tmp, hypro::colors[hypro::green]);
		}
	}

	//for(const auto& flowpipe : hpFlowpipes){
	//	for(const auto& segment : flowpipe){
	//		unsigned tmp = plotter.addObject(segment.vertices());
	//		plotter.setObjectColor(tmp, hypro::colors[hypro::orange]);
	//	}
	//}

	plotter.plot2d();
}
