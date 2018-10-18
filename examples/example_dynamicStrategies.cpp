/**
 *
 */

#include <string>
#include "../src/hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../src/hypro/algorithms/reachability/Reach.h"
#include "../src/hypro/representations/GeometricObject.h"
#include "../src/hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "../src/hypro/util/Plotter.h"

int main() {
	typedef mpq_class Number;
	typedef hypro::Box<Number> boxValuation;
	typedef hypro::SupportFunction<Number> sfValuation;
	typedef hypro::HPolytope<Number> hpValuation;

	//std::string filename = "../examples/input/thermostat.model";
	std::string filename = "../examples/input/bouncing_ball.model";

	std::pair<hypro::HybridAutomaton<Number>, hypro::ReachabilitySettings> ha = std::move(hypro::parseFlowstarFile<Number>(filename));

	//hypro::reachability::Reach<Number,boxValuation> boxReach(ha.first, ha.second);
	//hypro::reachability::Reach<Number,hpValuation> hpReach(ha.first, ha.second);
	hypro::reachability::Reach<Number> boxReach(ha.first, ha.second);
	boxReach.setRepresentationType(boxValuation::type());
	hypro::reachability::Reach<Number> hpReach(ha.first, ha.second);
	hpReach.setRepresentationType(hpValuation::type());
	hypro::reachability::Reach<Number> sfReach(ha.first, ha.second);
	sfReach.setRepresentationType(sfValuation::type());
	vector<std::pair<unsigned,hypro::reachability::flowpipe_t<Number>>> boxFlowpipes = boxReach.computeForwardReachability();
	vector<std::pair<unsigned,hypro::reachability::flowpipe_t<Number>>> hpFlowpipes = hpReach.computeForwardReachability();
	vector<std::pair<unsigned,hypro::reachability::flowpipe_t<Number>>> sfFlowpipes = sfReach.computeForwardReachability();

	//if(boxReach.reachedBadStates()) {
		//hypro::reachability::Reach<Number,sfValuation> sfReach(ha.first, ha.second);
		//sfFlowpipes = sfReach.computeForwardReachability();
	//}

	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	//plotter.setFilename(parser.mSettings.fileName);
	plotter.setFilename(ha.second.fileName);

	std::cout << "Plotting bad states...\n";

	// bad states plotting
	hypro::HybridAutomaton<Number>::locationConditionMap badStateMapping = ha.first.getLocalBadStates();
	for(const auto& bsPair : badStateMapping) {
		//unsigned bs = plotter.addObject(hpValuation(bsPair.second.set.first, bsPair.second.set.second).vertices());
		unsigned bs = plotter.addObject(hpValuation(bsPair.second.getMatrix(), bsPair.second.getVector()).vertices());
		plotter.setObjectColor(bs, hypro::plotting::colors[hypro::plotting::red]);
	}

	std::cout << "Bad states plotted! \nPlotting box flowpipes...\n";

	// flowpipe plotting
	for(const auto& flowpipe : boxFlowpipes){
		for(const auto& segment : flowpipe.second){
			unsigned tmp = plotter.addObject(segment.vertices());
			plotter.setObjectColor(tmp, hypro::plotting::colors[hypro::plotting::orange]);
		}
	}

	std::cout << "Box flowpipes plotted! \nPlotting hpoly flowpipes...\n";

	for(const auto& flowpipe : hpFlowpipes){
		for(const auto& segment : flowpipe.second){
			unsigned tmp = plotter.addObject(segment.vertices());
			plotter.setObjectColor(tmp, hypro::plotting::colors[hypro::plotting::lila]);
		}
	}

	std::cout << "Hpoly flowpipes plotted! \nPlotting SupportFunction flowpipes...\n";

	for(const auto& flowpipe : sfFlowpipes){
		for(const auto& segment : flowpipe.second){
			unsigned tmp = plotter.addObject(segment.vertices());
			plotter.setObjectColor(tmp, hypro::plotting::colors[hypro::plotting::green]);
		}
	}

	std::cout << "Finished!\n";

	plotter.plot2d();
}
