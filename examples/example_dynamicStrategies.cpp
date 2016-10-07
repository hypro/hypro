/**
 *
 */

#include <string>
#include "../src/hypro/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../src/hypro/algorithms/reachability/Reach.h"
#include "../src/hypro/representations/GeometricObject.h"
#include "../src/hypro/parser/flowstar/flowstarParser.h"
#include "../src/hypro/util/Plotter.h"

int main(int argc, char** argv) {
	typedef cln::cl_RA Number;
	typedef hypro::Box<Number> boxValuation;
	typedef hypro::SupportFunction<Number> sfValuation;
	typedef hypro::HPolytope<Number> hpValuation;

	std::string filename = "../examples/input/thermostat.model";

	hypro::parser::flowstarParser<Number> parser;
	hypro::HybridAutomaton<Number> ha = parser.parseInput(filename);

	hypro::reachability::Reach<Number,boxValuation> boxReach(ha, parser.mSettings);
	hypro::reachability::Reach<Number,hpValuation> hpReach(ha, parser.mSettings);
	std::vector<std::vector<boxValuation>> boxFlowpipes = boxReach.computeForwardReachability();
	std::vector<std::vector<hpValuation>> hpFlowpipes = hpReach.computeForwardReachability();
	std::vector<std::vector<sfValuation>> sfFlowpipes;

	//if(boxReach.reachedBadStates()) {
		hypro::reachability::Reach<Number,sfValuation> sfReach(ha, parser.mSettings);
		sfFlowpipes = sfReach.computeForwardReachability();
	//}

	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.setFilename(parser.mSettings.fileName);

	// bad states plotting
	hypro::HybridAutomaton<Number>::locationSetMap badStateMapping = ha.localBadStates();
	for(const auto& bsPair : badStateMapping) {
		unsigned bs = plotter.addObject(hpValuation(bsPair.second.first, bsPair.second.second).vertices());
		plotter.setObjectColor(bs, hypro::colors[hypro::red]);
	}

	// flowpipe plotting
	for(const auto& flowpipe : boxFlowpipes){
		for(const auto& segment : flowpipe){
			unsigned tmp = plotter.addObject(segment.vertices());
			plotter.setObjectColor(tmp, hypro::colors[hypro::orange]);
		}
	}

	for(const auto& flowpipe : hpFlowpipes){
		for(const auto& segment : flowpipe){
			unsigned tmp = plotter.addObject(segment.vertices());
			plotter.setObjectColor(tmp, hypro::colors[hypro::lila]);
		}
	}

	for(const auto& flowpipe : sfFlowpipes){
		for(const auto& segment : flowpipe){
			unsigned tmp = plotter.addObject(segment.vertices());
			plotter.setObjectColor(tmp, hypro::colors[hypro::green]);
		}
	}

	plotter.plot2d();
}
