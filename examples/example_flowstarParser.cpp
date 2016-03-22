/**
 *
 */

#include <string>
#include "../src/lib/config.h"
#include "../src/lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../src/lib/algorithms/reachability/Reach.h"
#include "../src/lib/representations/GeometricObject.h"
#include "../src/lib/parser/flowstar/flowstarParser.h"
#include "../src/lib/util/Plotter.h"

int main(int argc, char** argv) {
	typedef cln::cl_RA number;
	typedef hypro::SupportFunction<number> sfValuation;
	typedef hypro::Box<number> hpValuation;

	std::string filename = "../examples/input/bouncing_ball.model";

	hypro::parser::flowstarParser<number> parser;
	hypro::HybridAutomaton<number> ha = parser.parseInput(filename);

	//hypro::reachability::Reach<number,sfValuation> sfReach(ha, parser.mSettings);
	//std::vector<std::vector<sfValuation>> sfFlowpipes = sfReach.computeForwardReachability();

	hypro::reachability::Reach<number,hpValuation> hpReach(ha, parser.mSettings);
	std::vector<std::vector<hpValuation>> hpFlowpipes = hpReach.computeForwardReachability();

	hypro::Plotter<number>& plotter = hypro::Plotter<number>::getInstance();
	plotter.setFilename(parser.mSettings.fileName);
	//for(const auto& flowpipe : sfFlowpipes){
	//	for(const auto& segment : flowpipe){
	//		unsigned tmp = plotter.addObject(segment.vertices());
	//		plotter.setObjectColor(tmp, hypro::colors[hypro::green]);
	//	}
	//}

	plotter.rSettings().color = hypro::colors[hypro::red];
	for(const auto& flowpipe : hpFlowpipes){
		for(const auto& segment : flowpipe){
			unsigned tmp = plotter.addObject(segment.vertices());
			plotter.setObjectColor(tmp, hypro::colors[hypro::red]);
		}
	}

	plotter.plot2d();
}
