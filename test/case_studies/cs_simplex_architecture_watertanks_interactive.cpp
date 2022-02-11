/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by stefan on 04.08.21.
 */

#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/InteractivePlotter.h>
#include <string>

void Simplex_Watertanks_Reachability( std::size_t maxJumps = 5 ) {
    using Number = double;
    using Representation = hypro::Box<Number>;

    std::string filename{"21_simplex_watertanks_deterministic_monitor_dbg_init_ticks.model"};

    auto[automaton, reachSettings] = hypro::parseFlowstarFile<Number>(hypro::getCSModelsPath() + filename);

    // artificially bloat dimensions 0,1,3 to a width of 0.01
    auto initialStates = automaton.getInitialStates();
    for (auto &[loc, condition]: initialStates) {
        auto box = hypro::Box<Number>(condition.getMatrix(), condition.getVector());
        auto intervals = box.intervals();
        for (std::size_t i = 0; i < 5; ++i) {
			if ( i == 0 || i == 1 ) {  //|| i == 3) {
				intervals[i] = carl::Interval<Number>( intervals[i].lower() - 0.05, intervals[i].upper() + 0.05 );
			}
		}
        condition = hypro::Condition<Number>(intervals);
    }
    automaton.setInitialStates(initialStates);

    std::cout << "automaton \n" << automaton << std::endl;

    auto settings = hypro::convert(reachSettings);
    settings.rStrategy().front().detectJumpFixedPoints = true;
    settings.rStrategy().front().detectContinuousFixedPointsLocally = false;
    // settings.rFixedParameters().localTimeHorizon = 1;
    settings.rFixedParameters().jumpDepth = maxJumps;
    settings.rStrategy().begin()->aggregation = hypro::AGG_SETTING::AGG;

	auto roots = hypro::makeRoots<Representation>( automaton );
	auto reacher = hypro::reachability::Reach<Representation>( automaton, settings.fixedParameters(),
															   settings.strategy().front(), roots );
	auto result = reacher.computeForwardReachability();
	std::cout << "System is safe: " << result << std::endl;

	// invoke interactive plotter
	hypro::plotting::InteractivePlotter<Representation> ipl{ roots, settings.plotting() };
	ipl.run();
}

int main() {
    Simplex_Watertanks_Reachability(100);
	return 0;
}
